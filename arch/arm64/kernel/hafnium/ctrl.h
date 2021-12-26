/* 
 * 2021, Jack Lange <jacklange@cs.pitt.edu>
 */

#ifndef __CTRL_H__
#define __CTRL_H__

#define HAFNIUM_IOCTL_HYP_INIT      100
#define HAFNIUM_IOCTL_LAUNCH_VM     101
#define HAFNIUM_IOCTL_STOP_VM       102
#define HAFNIUM_IOCTL_ECHO          103
#define HAFNIUM_IOCTL_SEND_MSG      104                             
#define HAFNIUM_IOCTL_RECV_MSG      105                             

struct hafnium_cmd {
    uint64_t cmd;
    uint32_t data_len;
    uint8_t  data[0];
} __attribute__((packed));


extern void * hf_send_page;
extern void * hf_recv_page;
extern ffa_vm_id_t current_vm_id;

#endif
