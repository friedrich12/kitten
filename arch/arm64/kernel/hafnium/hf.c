#include <lwk/spinlock.h>
#include <lwk/task.h>
#include <lwk/sched.h>
#include <arch-arm64/page.h>

#include <arch/hafnium/call.h>
#include <arch/hafnium/ffa.h>
#include <arch/hafnium/types.h>
#include <arch/hafnium/vm_ids.h>

#include "transport.h"
#include "hf.h"


#define FIRST_SECONDARY_VM_ID (1)

struct hf_vm   * hf_vms = NULL;
ffa_vm_count_t   hf_vm_count;

int64_t 
hf_call(uint64_t arg0, 
	uint64_t arg1, 
	uint64_t arg2, 
	uint64_t arg3)
{
	register uint64_t r0 __asm__("x0") = arg0;
	register uint64_t r1 __asm__("x1") = arg1;
	register uint64_t r2 __asm__("x2") = arg2;
	register uint64_t r3 __asm__("x3") = arg3;

	__asm__ volatile(
		"hvc #0"
		: /* Output registers, also used as inputs ('+' constraint). */
		"+r"(r0), "+r"(r1), "+r"(r2), "+r"(r3)
		:
		: /* Clobber registers. */
		"x4", "x5", "x6", "x7");

	return r0;
}

struct ffa_value
ffa_call(struct ffa_value args)
{
	register uint64_t r0 __asm__("x0") = args.func;
	register uint64_t r1 __asm__("x1") = args.arg1;
	register uint64_t r2 __asm__("x2") = args.arg2;
	register uint64_t r3 __asm__("x3") = args.arg3;
	register uint64_t r4 __asm__("x4") = args.arg4;
	register uint64_t r5 __asm__("x5") = args.arg5;
	register uint64_t r6 __asm__("x6") = args.arg6;
	register uint64_t r7 __asm__("x7") = args.arg7;

	__asm__ volatile(
		"hvc #0"
		: /* Output registers, also used as inputs ('+' constraint). */
		"+r"(r0), "+r"(r1), "+r"(r2), "+r"(r3), "+r"(r4), "+r"(r5),
		"+r"(r6), "+r"(r7));

	return (struct ffa_value) {
		          .func = r0,
				  .arg1 = r1,
				  .arg2 = r2,
				  .arg3 = r3,
				  .arg4 = r4,
				  .arg5 = r5,
				  .arg6 = r6,
				  .arg7 = r7};
}


static void 
hf_vcpu_sleep(struct hf_vcpu * vcpu)
{
	int abort;

	set_task_state(current, TASK_INTERRUPTIBLE);

	/* Check the sleep-abort flag after making thread interruptible. */
	abort = atomic_read(&vcpu->abort_sleep);
	if (!abort && !kthread_should_stop()) {
		schedule();
	}

	/* Set state back to running on the way out. */
	set_task_state(current, TASK_RUNNING);
}

static struct hf_vm *
hf_vm_from_id(ffa_vm_id_t vm_id)
{
	printk("vm_from_id vm_id=%d, count=%d\n", vm_id, hf_vm_count);

	if (vm_id < FIRST_SECONDARY_VM_ID ||
	    vm_id >= FIRST_SECONDARY_VM_ID + hf_vm_count)
		return NULL;

	return &hf_vms[vm_id - FIRST_SECONDARY_VM_ID];
}

static int 
hf_vcpu_wake_up(struct hf_vcpu * vcpu)
{
	/* Set a flag indicating that the thread should not go to sleep. */
	atomic_set(&vcpu->abort_sleep, 1);

	/* Set the thread to running state. */
	return sched_wakeup_task((vcpu->task), TASK_ALL);
}

static void 
hf_vcpu_timer_expired(struct hrtimer * timer)
{
	struct hf_vcpu * vcpu = container_of(timer, struct hf_vcpu, timer);

	/* TODO: Inject interrupt. */

	hf_vcpu_wake_up(vcpu);
}

static void 
hf_handle_wake_up_request(ffa_vm_id_t      vm_id,
		          ffa_vcpu_index_t vcpu)
{
	struct hf_vm * vm = hf_vm_from_id(vm_id);

	if (vm == NULL) {
		printk(KERN_WARNING "Request to wake up non-existent VM id: %u\n", vm_id);
		return;
	}

	if (vcpu >= vm->vcpu_count) {
		printk(KERN_WARNING "Request to wake up non-existent vCPU: %u.%u\n",
			vm_id, vcpu);
		return;
	}

	if (hf_vcpu_wake_up(&vm->vcpu[vcpu]) == 0) {
		/*
		 * The task was already running (presumably on a different
		 * physical CPU); interrupt it. This gives Hafnium a chance to
		 * inject any new interrupts.
		 */
		arch_xcall_reschedule(vm->vcpu[vcpu].task->cpu_id);
	}
}

/**
 * Injects an interrupt into a vCPU of the VM and ensures the vCPU will run to
 * handle the interrupt.
 */
static void 
hf_interrupt_vm(ffa_vm_id_t vm_id, uint64_t int_id)
{
	struct hf_vm *vm = hf_vm_from_id(vm_id);
	ffa_vcpu_index_t vcpu;
	int64_t ret;

	if (!vm) {
		printk("Request to wake up non-existent VM id: %u\n", vm_id);
		return;
	}

	/*
	 * TODO: For now we're picking the first vcpu to interrupt, but
	 * we want to be smarter.
	 */
	vcpu = 0;
	ret = hf_interrupt_inject(vm_id, vcpu, int_id);

	if (ret == -1) {
		printk("Failed to inject interrupt %lld to vCPU %d of VM %d",
			int_id, vcpu, vm_id);
		return;
	}

	if (ret != 1) {
		/* We don't need to wake up the vcpu. */
		return;
	}

	hf_handle_wake_up_request(vm_id, vcpu);
}

/**
 * Delivers a message to a VM.
 */
static void
hf_deliver_message(ffa_vm_id_t vm_id)
{
	struct hf_vm *vm = hf_vm_from_id(vm_id);
	ffa_vcpu_index_t i;

	if (!vm) {
		printk("Tried to deliver message to non-existent VM id: %u\n",
			vm_id);
		return;
	}

	/* Try to wake a vCPU that is waiting for a message. */
	for (i = 0; i < vm->vcpu_count; i++) {
		if (atomic_read(&vm->vcpu[i].waiting_for_message)) {
			hf_handle_wake_up_request(vm_id,
						  vm->vcpu[i].vcpu_index);
			return;
		}
	}

	/* None were waiting for a message so interrupt one. */
	hf_interrupt_vm(vm_id, HF_MAILBOX_READABLE_INTID);
}


static void 
swap(uint64_t *a, uint64_t *b)
{
	uint64_t t = *a;
	*a = *b;
	*b = t;
}

/**
 * Sends the message to the sender VM by calling Hafnium. It will also
 * trigger the wake up of a recipient VM.
 */
int 
hf_echo_test()
{
    /* Loop, echo messages back to the sender. */
    ffa_rx_release();

    for (;;) {
		struct ffa_value ret;

		/* Receive the packet. */
		ret = ffa_msg_wait();

                if(ret.func == FFA_MSG_SEND_32){
                        printk("WE GOT A MESSSAGE OF SIZE %d!\n", ffa_msg_send_size(ret));

                        char* msg = (char*) hf_recv_page;
            
                        for(int i = 0; i < ffa_msg_send_size(ret); i++){
                                printk("%c", msg[i]);
                        }
                        printk("\n");

                        printk("Kitten Got: %s\n", msg);
                }

		/* Echo the message back to the sender. */
		memcpy(hf_send_page, hf_recv_page, ffa_msg_send_size(ret));

		/* Swap the socket's source and destination ports */
		struct hf_msg_hdr *hdr = (struct hf_msg_hdr *)hf_send_page;
		swap(&(hdr->src_port), &(hdr->dst_port));

		/* Swap the destination and source ids. */
		ffa_vm_id_t dst_id = ffa_sender(ret);
		ffa_vm_id_t src_id = ffa_receiver(ret);

		ffa_rx_release();
		ffa_msg_send(src_id, dst_id, ffa_msg_send_size(ret), 0);
	}

	return 0;
}

/* 
 * Sends a message to another VM
 * The Consumer of a buffer owns it when it is full.
 * The Producer writes to the buffer when it is empty.
 * See Arm Firmware Framework for Arm A-profile Section Buffer states and ownership
 * for reference
 */
int 
hf_send_message(char* msg, size_t msglen, ffa_vm_id_t recipient_vm_id){
      
        /* TODO Clean up */
        ffa_rx_release();

        bool done = false;
        while(!done){
                struct ffa_value ret;

                /* Receive the packet. */
                ret = ffa_msg_wait();

                if(ret.func == FFA_MSG_SEND_32){
                        printk("WE GOT A MESSSAGE OF SIZE %d!\n", ffa_msg_send_size(ret));
                        char* msg = (char*) hf_recv_page;
                        done = true;
                }

	        /* Send our message back to the sender. */
		memcpy(hf_send_page, hf_recv_page, ffa_msg_send_size(ret));
                memcpy(hf_send_page + sizeof(struct hf_msg_hdr), msg, msglen);
	        
                /* Swap the socket's source and destination ports */
	        struct hf_msg_hdr *hdr = (struct hf_msg_hdr *)hf_send_page;
	        swap(&(hdr->src_port), &(hdr->dst_port));

	        /* Swap the destination and source ids. */
	        ffa_vm_id_t dst_id = ffa_sender(ret);
	        ffa_vm_id_t src_id = ffa_receiver(ret);

	        ffa_rx_release();
	        ffa_msg_send(src_id, dst_id, msglen, 0);
        }

        return 0;
}

/*
 * Recieves a message from this VM and stores in ret_msg. 
 * This will block unil a message is received.
 * Right now there is no message queue. Pending messages will be not be able to be 
 * delivered until the buffer is empty (ownership is transfered from consumer to producer).
 */
int 
hf_recv_message(char* ret_msg)
{
    /* Transfer ownership to producer (So they can write to our recv page). */
    ffa_rx_release();

    for(;;){
	    struct ffa_value ret;

	    /* Receive the message. */
	    ret = ffa_msg_wait();

        if(ret.func == FFA_MSG_SEND_32){
            int ffa_msg_size, copy_size;
            ffa_msg_size = copy_size = ffa_msg_send_size(ret);

            if(ffa_msg_send_size(ret) > FFA_MSG_PAYLOAD_MAX){
                printk("Message is too big to be copied cutting.\n");
                copy_size = FFA_MSG_PAYLOAD_MAX;
            }

            memcpy(ret_msg, hf_recv_page, copy_size);
            break;
        }
    }
	return 0;
}

static int 
hf_vcpu_thread(void * data)
{
	struct hf_vcpu * vcpu = data;
	struct ffa_value ret;

	vcpu->timer.function = &hf_vcpu_timer_expired;
	vcpu->timer.data     = &(vcpu->timer);

	while (!kthread_should_stop()) {
		ffa_vcpu_index_t i;

//        printk("I'M looping baby\n");
		/*
		 * We're about to run the vcpu, so we can reset the abort-sleep
		 * flag.
		 */


		atomic_set(&vcpu->abort_sleep, 0);

		/* Call into Hafnium to run vcpu. */
		ret = ffa_run(vcpu->vm->id, vcpu->vcpu_index);

		switch (ret.func) {
		/* Preempted. */
		case FFA_INTERRUPT_32:
			if (test_bit(TF_NEED_RESCHED_BIT, &(current->arch.flags))) {
				schedule();
			}
			break;

		/* Yield. */
		case FFA_YIELD_32:
			if (!kthread_should_stop()) {
				schedule();
			}
			break;

		/* WFI. */
		case HF_FFA_RUN_WAIT_FOR_INTERRUPT:
			if (ret.arg2 != FFA_SLEEP_INDEFINITE) {
				vcpu->timer.expires = get_time() + ret.arg2;
				timer_add(&vcpu->timer);
			}
			
			hf_vcpu_sleep(vcpu);
			timer_del(&vcpu->timer);
			
			break;

		/* Waiting for a message. */
		case FFA_MSG_WAIT_32:
			atomic_set(&vcpu->waiting_for_message, 1);

			if (ret.arg2 != FFA_SLEEP_INDEFINITE) {
				vcpu->timer.expires = get_time() + ret.arg2;
				timer_add(&vcpu->timer);
			}
			
			hf_vcpu_sleep(vcpu);
			timer_del(&vcpu->timer);

			atomic_set(&vcpu->waiting_for_message, 0);
			break;

		/* Wake up another vcpu. */
		case HF_FFA_RUN_WAKE_UP:
			hf_handle_wake_up_request(ffa_vm_id(ret),
						  ffa_vcpu_index(ret));
			break;

		/* Response available.*/
		/*case FFA_MSG_SEND_32:
            printk("FFA_MSG_SEND_32\n");
		 	if (ffa_receiver(ret) == HF_PRIMARY_VM_ID) { 
                //hf_handle_msg();
		 	} else {
                // Focus on just sending messaegs for now
		 		hf_deliver_message(ffa_receiver(ret));
		 	} 
		 	break;*/

		/* /\* Notify all waiters. *\/ */
		/* case FFA_RX_RELEASE_32: */
		/* 	hf_notify_waiters(vcpu->vm->id); */
		/* 	break; */

		case FFA_ERROR_32:
			printk(KERN_WARNING "FF-A error %d running VM %d vCPU %d", 
				ret.arg2,
				vcpu->vm->id, 
				vcpu->vcpu_index);

			switch (ret.arg2) {
			/* Abort was triggered. */
			case FFA_ABORTED:
				for (i = 0; i < vcpu->vm->vcpu_count; i++) {
					if (i == vcpu->vcpu_index) {
						continue;
					}

					hf_handle_wake_up_request(vcpu->vm->id,
								  i);
				}
				hf_vcpu_sleep(vcpu);
				break;
			default:
				/* Treat as a yield and try again later. */
				if (!kthread_should_stop()) {
					schedule();
				}
				break;
			}
			break;
		}
	}

	return 0;
}


int 
hf_launch_vm(ffa_vm_id_t vm_id)
{
    struct hf_vm      * vm = &hf_vms[vm_id - 1];

   	ffa_vcpu_index_t j;

    int ret;

    /* Adjust the index as only the secondaries are tracked. */
    vm->id         = partition_info[vm_id - 1].vm_id;
    vm->vcpu_count = partition_info[vm_id - 1].vcpu_count;
    vm->vcpu       = kmem_alloc(vm->vcpu_count * sizeof(struct hf_vcpu));

    if (vm->vcpu == NULL) {
        ret = -ENOMEM;
        goto err;
    }

	printk("Launching VM (vm->id = %d)\n", vm->id);

    for (j = 0; j < vm->vcpu_count; j++) {
        struct hf_vcpu * vcpu = &vm->vcpu[j];
				vcpu->task = kthread_create_on_cpu(j,
											hf_vcpu_thread, 
											vcpu,
											"vcpu_thread_%u_%u", 
											vm->id, 
											j);

				vcpu->task = (struct task_struct*)(PAGE_OFFSET | (long unsigned int)vcpu->task);

        if (vcpu->task == NULL) {
            pr_err("Error creating task (vm = %u, vcpu = %u): %lu\n",
                vm->id, j, vcpu->task);

            vm->vcpu_count = j;
            ret            = vcpu->task;
            goto err;
        }

        vcpu->vm         = vm;
        vcpu->vcpu_index = j;

        atomic_set(&vcpu->abort_sleep,         0);
        atomic_set(&vcpu->waiting_for_message, 0);
    }

    for (j = 0; j < vm->vcpu_count; j++) {
        sched_wakeup_task(vm->vcpu[j].task, TASK_STOPPED);
    }

    printk("hafnium initialized\n");


    return 0;

err:
    return ret;
}


