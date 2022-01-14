	.arch armv8.3-a+crc
	.file	"asm-offsets.c"
// GNU C99 (Ubuntu 9.3.0-17ubuntu1~20.04) version 9.3.0 (aarch64-linux-gnu)
//	compiled by GNU C version 9.3.0, GMP version 6.2.0, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.22.1-GMP

// GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
// options passed:  -nostdinc -I include -I ofed/include
// -imultiarch aarch64-linux-gnu -D __KERNEL__ -D __LWK__ -D __KERNEL__
// -D TEXT_OFFSET=0x00080000 -D KBUILD_STR(s)=#s
// -D KBUILD_BASENAME=KBUILD_STR(asm_offsets)
// -D KBUILD_MODNAME=KBUILD_STR(asm_offsets)
// -isystem /usr/lib/gcc-cross/aarch64-linux-gnu/9/include
// -include include/lwk/autoconf.h -MD arch/arm64/kernel/.asm-offsets.s.d
// arch/arm64/kernel/asm-offsets.c -march=armv8.3-a -mlittle-endian
// -mabi=lp64 -auxbase-strip arch/arm64/kernel/asm-offsets.s -g -g -O2
// -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -Wno-sign-compare
// -Wno-unused-parameter -Wno-pointer-sign -w -std=gnu99
// -fno-strict-aliasing -fno-strict-overflow -fno-common -fno-pie
// -fno-stack-protector -fgnu89-inline -fno-omit-frame-pointer
// -fno-optimize-sibling-calls -fno-builtin -ffunction-sections
// -fno-reorder-blocks -funit-at-a-time -fverbose-asm
// -fasynchronous-unwind-tables -Wformat-security -fstack-clash-protection
// options enabled:  -faggressive-loop-optimizations -falign-functions
// -falign-jumps -falign-labels -falign-loops -fassume-phsa
// -fasynchronous-unwind-tables -fauto-inc-dec -fbranch-count-reg
// -fcaller-saves -fcode-hoisting -fcombine-stack-adjustments
// -fcompare-elim -fcprop-registers -fcrossjumping -fcse-follow-jumps
// -fdefer-pop -fdelete-null-pointer-checks -fdevirtualize
// -fdevirtualize-speculatively -fdwarf2-cfi-asm -fearly-inlining
// -feliminate-unused-debug-types -fexpensive-optimizations
// -fforward-propagate -ffp-int-builtin-inexact -ffunction-cse
// -ffunction-sections -fgcse -fgcse-lm -fgnu-runtime -fgnu-unique
// -fguess-branch-probability -fhoist-adjacent-loads -fident
// -fif-conversion -fif-conversion2 -findirect-inlining -finline
// -finline-atomics -finline-functions-called-once -finline-small-functions
// -fipa-bit-cp -fipa-cp -fipa-icf -fipa-icf-functions -fipa-icf-variables
// -fipa-profile -fipa-pure-const -fipa-ra -fipa-reference
// -fipa-reference-addressable -fipa-sra -fipa-stack-alignment -fipa-vrp
// -fira-hoist-pressure -fira-share-save-slots -fira-share-spill-slots
// -fisolate-erroneous-paths-dereference -fivopts -fkeep-static-consts
// -fleading-underscore -flifetime-dse -flra-remat -flto-odr-type-merging
// -fmath-errno -fmerge-constants -fmerge-debug-strings
// -fmove-loop-invariants -fomit-frame-pointer -foptimize-strlen
// -fpartial-inlining -fpeephole -fpeephole2 -fplt -fprefetch-loop-arrays
// -free -freg-struct-return -freorder-functions -frerun-cse-after-loop
// -fsched-critical-path-heuristic -fsched-dep-count-heuristic
// -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
// -fsched-pressure -fsched-rank-heuristic -fsched-spec
// -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fschedule-fusion
// -fschedule-insns -fschedule-insns2 -fsection-anchors
// -fsemantic-interposition -fshow-column -fshrink-wrap
// -fshrink-wrap-separate -fsigned-zeros -fsplit-ivs-in-unroller
// -fsplit-wide-types -fssa-backprop -fssa-phiopt -fstack-clash-protection
// -fstdarg-opt -fstore-merging -fstrict-volatile-bitfields -fsync-libcalls
// -fthread-jumps -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp
// -ftree-builtin-call-dce -ftree-ccp -ftree-ch -ftree-coalesce-vars
// -ftree-copy-prop -ftree-cselim -ftree-dce -ftree-dominator-opts
// -ftree-dse -ftree-forwprop -ftree-fre -ftree-loop-if-convert
// -ftree-loop-im -ftree-loop-ivcanon -ftree-loop-optimize
// -ftree-parallelize-loops= -ftree-phiprop -ftree-pre -ftree-pta
// -ftree-reassoc -ftree-scev-cprop -ftree-sink -ftree-slsr -ftree-sra
// -ftree-switch-conversion -ftree-tail-merge -ftree-ter -ftree-vrp
// -funit-at-a-time -funwind-tables -fvar-tracking
// -fvar-tracking-assignments -fverbose-asm -fwrapv -fwrapv-pointer
// -fzero-initialized-in-bss -mfix-cortex-a53-835769
// -mfix-cortex-a53-843419 -mglibc -mlittle-endian
// -momit-leaf-frame-pointer -mpc-relative-literal-loads

	.text
.Ltext0:
	.section	.text.startup.main,"ax",@progbits
	.align	2
	.p2align 3,,7
	.global	main
	.type	main, %function
main:
.LFB225:
	.file 1 "arch/arm64/kernel/asm-offsets.c"
	.loc 1 41 1 view -0
	.cfi_startproc
	.loc 1 43 3 view .LVU1
#APP
// 43 "arch/arm64/kernel/asm-offsets.c" 1
	
->	
// 0 "" 2
	.loc 1 45 3 view .LVU2
// 45 "arch/arm64/kernel/asm-offsets.c" 1
	
->TI_FLAGS 192 offsetof(struct task_struct, arch.flags)	//
// 0 "" 2
	.loc 1 53 3 view .LVU3
// 53 "arch/arm64/kernel/asm-offsets.c" 1
	
->	
// 0 "" 2
	.loc 1 58 3 view .LVU4
// 58 "arch/arm64/kernel/asm-offsets.c" 1
	
->TSK_ARCH_THREAD_CPU_CONTEXT_SP 296 offsetof(struct task_struct, arch) + offsetof(struct arch_task, thread) + offsetof(struct thread_struct, cpu_context) + offsetof(struct cpu_context, sp)	//
// 0 "" 2
	.loc 1 59 3 view .LVU5
// 59 "arch/arm64/kernel/asm-offsets.c" 1
	
->TSK_ARCH_THREAD_CPU_CONTEXT_USERSP 320 offsetof(struct task_struct, arch) + offsetof(struct arch_task, thread) + offsetof(struct thread_struct, cpu_context) + offsetof(struct cpu_context, usersp)	//
// 0 "" 2
	.loc 1 63 3 view .LVU6
// 63 "arch/arm64/kernel/asm-offsets.c" 1
	
->TSK_ARCH_FLAGS 192 offsetof(struct task_struct, arch) + offsetof(struct arch_task, flags)	//
// 0 "" 2
	.loc 1 66 3 view .LVU7
// 66 "arch/arm64/kernel/asm-offsets.c" 1
	
->	
// 0 "" 2
	.loc 1 67 3 view .LVU8
// 67 "arch/arm64/kernel/asm-offsets.c" 1
	
->S_X0 0 offsetof(struct pt_regs, regs[0])	//
// 0 "" 2
	.loc 1 68 3 view .LVU9
// 68 "arch/arm64/kernel/asm-offsets.c" 1
	
->S_X1 8 offsetof(struct pt_regs, regs[1])	//
// 0 "" 2
	.loc 1 69 3 view .LVU10
// 69 "arch/arm64/kernel/asm-offsets.c" 1
	
->S_X2 16 offsetof(struct pt_regs, regs[2])	//
// 0 "" 2
	.loc 1 70 3 view .LVU11
// 70 "arch/arm64/kernel/asm-offsets.c" 1
	
->S_X3 24 offsetof(struct pt_regs, regs[3])	//
// 0 "" 2
	.loc 1 71 3 view .LVU12
// 71 "arch/arm64/kernel/asm-offsets.c" 1
	
->S_X4 32 offsetof(struct pt_regs, regs[4])	//
// 0 "" 2
	.loc 1 72 3 view .LVU13
// 72 "arch/arm64/kernel/asm-offsets.c" 1
	
->S_X5 40 offsetof(struct pt_regs, regs[5])	//
// 0 "" 2
	.loc 1 73 3 view .LVU14
// 73 "arch/arm64/kernel/asm-offsets.c" 1
	
->S_X6 48 offsetof(struct pt_regs, regs[6])	//
// 0 "" 2
	.loc 1 74 3 view .LVU15
// 74 "arch/arm64/kernel/asm-offsets.c" 1
	
->S_X7 56 offsetof(struct pt_regs, regs[7])	//
// 0 "" 2
	.loc 1 75 3 view .LVU16
// 75 "arch/arm64/kernel/asm-offsets.c" 1
	
->S_LR 240 offsetof(struct pt_regs, regs[30])	//
// 0 "" 2
	.loc 1 76 3 view .LVU17
// 76 "arch/arm64/kernel/asm-offsets.c" 1
	
->S_SP 248 offsetof(struct pt_regs, sp)	//
// 0 "" 2
	.loc 1 80 3 view .LVU18
// 80 "arch/arm64/kernel/asm-offsets.c" 1
	
->S_PSTATE 264 offsetof(struct pt_regs, pstate)	//
// 0 "" 2
	.loc 1 81 3 view .LVU19
// 81 "arch/arm64/kernel/asm-offsets.c" 1
	
->S_PC 256 offsetof(struct pt_regs, pc)	//
// 0 "" 2
	.loc 1 82 3 view .LVU20
// 82 "arch/arm64/kernel/asm-offsets.c" 1
	
->S_ORIG_X0 272 offsetof(struct pt_regs, orig_x0)	//
// 0 "" 2
	.loc 1 83 3 view .LVU21
// 83 "arch/arm64/kernel/asm-offsets.c" 1
	
->S_SYSCALLNO 280 offsetof(struct pt_regs, syscallno)	//
// 0 "" 2
	.loc 1 84 3 view .LVU22
// 84 "arch/arm64/kernel/asm-offsets.c" 1
	
->S_FRAME_SIZE 288 sizeof(struct pt_regs)	//
// 0 "" 2
	.loc 1 85 3 view .LVU23
// 85 "arch/arm64/kernel/asm-offsets.c" 1
	
->	
// 0 "" 2
	.loc 1 87 3 view .LVU24
// 87 "arch/arm64/kernel/asm-offsets.c" 1
	
->	
// 0 "" 2
	.loc 1 90 3 view .LVU25
// 90 "arch/arm64/kernel/asm-offsets.c" 1
	
->	
// 0 "" 2
	.loc 1 92 3 view .LVU26
// 92 "arch/arm64/kernel/asm-offsets.c" 1
	
->	
// 0 "" 2
	.loc 1 93 3 view .LVU27
// 93 "arch/arm64/kernel/asm-offsets.c" 1
	
->PAGE_SZ 4096 PAGE_SIZE	//
// 0 "" 2
	.loc 1 94 3 view .LVU28
// 94 "arch/arm64/kernel/asm-offsets.c" 1
	
->	
// 0 "" 2
	.loc 1 99 3 view .LVU29
// 99 "arch/arm64/kernel/asm-offsets.c" 1
	
->	
// 0 "" 2
	.loc 1 105 3 view .LVU30
// 105 "arch/arm64/kernel/asm-offsets.c" 1
	
->	
// 0 "" 2
	.loc 1 114 3 view .LVU31
// 114 "arch/arm64/kernel/asm-offsets.c" 1
	
->NSEC_PER_SEC 1000000000 NSEC_PER_SEC	//
// 0 "" 2
	.loc 1 115 3 view .LVU32
// 115 "arch/arm64/kernel/asm-offsets.c" 1
	
->	
// 0 "" 2
	.loc 1 131 3 view .LVU33
// 131 "arch/arm64/kernel/asm-offsets.c" 1
	
->	
// 0 "" 2
	.loc 1 132 3 view .LVU34
// 132 "arch/arm64/kernel/asm-offsets.c" 1
	
->TVAL_TV_SEC 0 offsetof(struct timeval, tv_sec)	//
// 0 "" 2
	.loc 1 133 3 view .LVU35
// 133 "arch/arm64/kernel/asm-offsets.c" 1
	
->TVAL_TV_USEC 8 offsetof(struct timeval, tv_usec)	//
// 0 "" 2
	.loc 1 134 3 view .LVU36
// 134 "arch/arm64/kernel/asm-offsets.c" 1
	
->TSPEC_TV_SEC 0 offsetof(struct timespec, tv_sec)	//
// 0 "" 2
	.loc 1 135 3 view .LVU37
// 135 "arch/arm64/kernel/asm-offsets.c" 1
	
->TSPEC_TV_NSEC 8 offsetof(struct timespec, tv_nsec)	//
// 0 "" 2
	.loc 1 136 3 view .LVU38
// 136 "arch/arm64/kernel/asm-offsets.c" 1
	
->	
// 0 "" 2
	.loc 1 137 3 view .LVU39
// 137 "arch/arm64/kernel/asm-offsets.c" 1
	
->TZ_MINWEST 0 offsetof(struct timezone, tz_minuteswest)	//
// 0 "" 2
	.loc 1 138 3 view .LVU40
// 138 "arch/arm64/kernel/asm-offsets.c" 1
	
->TZ_DSTTIME 4 offsetof(struct timezone, tz_dsttime)	//
// 0 "" 2
	.loc 1 139 3 view .LVU41
// 139 "arch/arm64/kernel/asm-offsets.c" 1
	
->	
// 0 "" 2
	.loc 1 173 3 view .LVU42
// 173 "arch/arm64/kernel/asm-offsets.c" 1
	
->ARM_SMCCC_RES_X0_OFFS 0 offsetof(struct arm_smccc_res, a0)	//
// 0 "" 2
	.loc 1 174 3 view .LVU43
// 174 "arch/arm64/kernel/asm-offsets.c" 1
	
->ARM_SMCCC_RES_X2_OFFS 16 offsetof(struct arm_smccc_res, a2)	//
// 0 "" 2
	.loc 1 175 3 view .LVU44
// 175 "arch/arm64/kernel/asm-offsets.c" 1
	
->ARM_SMCCC_QUIRK_ID_OFFS 0 offsetof(struct arm_smccc_quirk, id)	//
// 0 "" 2
	.loc 1 176 3 view .LVU45
// 176 "arch/arm64/kernel/asm-offsets.c" 1
	
->ARM_SMCCC_QUIRK_STATE_OFFS 8 offsetof(struct arm_smccc_quirk, state)	//
// 0 "" 2
	.loc 1 178 3 view .LVU46
// 178 "arch/arm64/kernel/asm-offsets.c" 1
	
->__NR_syscall_max 534 sizeof(syscalls) - 1	//
// 0 "" 2
	.loc 1 179 3 view .LVU47
// arch/arm64/kernel/asm-offsets.c:180: }
	.loc 1 180 1 is_stmt 0 view .LVU48
#NO_APP
	mov	w0, 0	//,
	ret	
	.cfi_endproc
.LFE225:
	.size	main, .-main
	.text
.Letext0:
	.file 2 "include/arch/posix_types.h"
	.file 3 "include/arch/types.h"
	.file 4 "include/lwk/types.h"
	.file 5 "include/lwk/init.h"
	.file 6 "include/lwk/idspace.h"
	.file 7 "include/arch/bitops.h"
	.file 8 "include/lwk/cpumask.h"
	.file 9 "include/arch/page.h"
	.file 10 "include/arch/pgtable-3level-types.h"
	.file 11 "include/arch/pgtable.h"
	.file 12 "include/arch/pda.h"
	.file 13 "include/lwk/task.h"
	.file 14 "include/lwk/utsname.h"
	.file 15 "include/lwk/kernel.h"
	.file 16 "include/lwk/delay.h"
	.file 17 "include/lwk/reboot.h"
	.file 18 "include/arch/system.h"
	.file 19 "include/arch/uapi_ptrace.h"
	.file 20 "include/arch/fpsimd.h"
	.file 21 "include/arch/processor.h"
	.file 22 "include/lwk/list.h"
	.file 23 "include/arch/signal.h"
	.file 24 "include/lwk/signal.h"
	.file 25 "include/arch/task.h"
	.file 26 "include/lwk/sched.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xc45
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF149
	.byte	0xc
	.4byte	.LASF150
	.4byte	.LASF151
	.4byte	.Ldebug_ranges0+0
	.8byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF0
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF1
	.uleb128 0x4
	.4byte	0x37
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF2
	.uleb128 0x5
	.4byte	.LASF9
	.byte	0x2
	.byte	0x15
	.byte	0x17
	.4byte	0x29
	.uleb128 0x6
	.byte	0x8
	.4byte	0x5c
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF3
	.uleb128 0x7
	.4byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF4
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF6
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF7
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x5
	.4byte	.LASF10
	.byte	0x3
	.byte	0x18
	.byte	0x16
	.4byte	0x37
	.uleb128 0x5
	.4byte	.LASF11
	.byte	0x3
	.byte	0x1b
	.byte	0x1d
	.4byte	0xa3
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF12
	.uleb128 0x5
	.4byte	.LASF13
	.byte	0x3
	.byte	0x1d
	.byte	0x1c
	.4byte	0xa3
	.uleb128 0x8
	.string	"u32"
	.byte	0x3
	.byte	0x31
	.byte	0x16
	.4byte	0x37
	.uleb128 0x5
	.4byte	.LASF14
	.byte	0x4
	.byte	0x72
	.byte	0x11
	.4byte	0x8b
	.uleb128 0x5
	.4byte	.LASF15
	.byte	0x4
	.byte	0x75
	.byte	0x11
	.4byte	0x97
	.uleb128 0x5
	.4byte	.LASF16
	.byte	0x4
	.byte	0x83
	.byte	0x11
	.4byte	0xe6
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF17
	.uleb128 0x5
	.4byte	.LASF18
	.byte	0x4
	.byte	0x90
	.byte	0x1c
	.4byte	0x4a
	.uleb128 0x9
	.4byte	0x5c
	.4byte	0x10a
	.uleb128 0xa
	.4byte	0x29
	.2byte	0x3ff
	.byte	0
	.uleb128 0xb
	.4byte	.LASF19
	.byte	0x5
	.byte	0x4d
	.byte	0xd
	.4byte	0xf9
	.uleb128 0xb
	.4byte	.LASF20
	.byte	0x5
	.byte	0x55
	.byte	0x10
	.4byte	0xed
	.uleb128 0x5
	.4byte	.LASF21
	.byte	0x6
	.byte	0x10
	.byte	0x16
	.4byte	0x37
	.uleb128 0xc
	.4byte	.LASF24
	.byte	0x4
	.byte	0x7
	.byte	0x18
	.byte	0x10
	.4byte	0x149
	.uleb128 0xd
	.4byte	.LASF26
	.byte	0x7
	.byte	0x19
	.byte	0x18
	.4byte	0x3e
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF22
	.byte	0x7
	.byte	0x1a
	.byte	0x3
	.4byte	0x12e
	.uleb128 0x9
	.4byte	0x149
	.4byte	0x165
	.uleb128 0xe
	.4byte	0x29
	.byte	0x3
	.byte	0
	.uleb128 0xb
	.4byte	.LASF23
	.byte	0x7
	.byte	0x2a
	.byte	0x17
	.4byte	0x155
	.uleb128 0xc
	.4byte	.LASF25
	.byte	0x8
	.byte	0x8
	.byte	0x91
	.byte	0x10
	.4byte	0x18c
	.uleb128 0xd
	.4byte	.LASF27
	.byte	0x8
	.byte	0x91
	.byte	0x1a
	.4byte	0x18c
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	0x29
	.4byte	0x19c
	.uleb128 0xe
	.4byte	0x29
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF28
	.byte	0x8
	.byte	0x91
	.byte	0x3b
	.4byte	0x171
	.uleb128 0xb
	.4byte	.LASF29
	.byte	0x8
	.byte	0x92
	.byte	0x12
	.4byte	0x19c
	.uleb128 0xf
	.4byte	.LASF30
	.byte	0x8
	.2byte	0x1d3
	.byte	0x12
	.4byte	0x19c
	.uleb128 0xf
	.4byte	.LASF31
	.byte	0x8
	.2byte	0x1d4
	.byte	0x12
	.4byte	0x19c
	.uleb128 0xf
	.4byte	.LASF32
	.byte	0x8
	.2byte	0x1d5
	.byte	0x12
	.4byte	0x19c
	.uleb128 0x9
	.4byte	0x5c
	.4byte	0x1eb
	.uleb128 0xe
	.4byte	0x29
	.byte	0x1f
	.byte	0
	.uleb128 0xb
	.4byte	.LASF33
	.byte	0x9
	.byte	0x4c
	.byte	0x14
	.4byte	0xaa
	.uleb128 0x5
	.4byte	.LASF34
	.byte	0xa
	.byte	0x15
	.byte	0x12
	.4byte	0xce
	.uleb128 0x5
	.4byte	.LASF35
	.byte	0xa
	.byte	0x17
	.byte	0x12
	.4byte	0xce
	.uleb128 0x5
	.4byte	.LASF36
	.byte	0xa
	.byte	0x33
	.byte	0x12
	.4byte	0x203
	.uleb128 0x5
	.4byte	.LASF37
	.byte	0xa
	.byte	0x34
	.byte	0x12
	.4byte	0x1f7
	.uleb128 0x6
	.byte	0x8
	.4byte	0x22d
	.uleb128 0x10
	.4byte	.LASF81
	.uleb128 0xb
	.4byte	.LASF38
	.byte	0xb
	.byte	0x47
	.byte	0x11
	.4byte	0x21b
	.uleb128 0xb
	.4byte	.LASF39
	.byte	0xb
	.byte	0x80
	.byte	0x15
	.4byte	0x227
	.uleb128 0x9
	.4byte	0x20f
	.4byte	0x25b
	.uleb128 0xa
	.4byte	0x29
	.2byte	0x1ff
	.byte	0
	.uleb128 0xf
	.4byte	.LASF40
	.byte	0xb
	.2byte	0x136
	.byte	0xe
	.4byte	0x24a
	.uleb128 0xf
	.4byte	.LASF41
	.byte	0xb
	.2byte	0x137
	.byte	0xe
	.4byte	0x24a
	.uleb128 0x9
	.4byte	0x285
	.4byte	0x285
	.uleb128 0xe
	.4byte	0x29
	.byte	0x1f
	.byte	0
	.uleb128 0x2
	.byte	0x10
	.byte	0x7
	.4byte	.LASF42
	.uleb128 0xc
	.4byte	.LASF43
	.byte	0x50
	.byte	0xc
	.byte	0x1a
	.byte	0x8
	.4byte	0x350
	.uleb128 0xd
	.4byte	.LASF44
	.byte	0xc
	.byte	0x1b
	.byte	0x17
	.4byte	0x4c2
	.byte	0
	.uleb128 0xd
	.4byte	.LASF45
	.byte	0xc
	.byte	0x1c
	.byte	0x10
	.4byte	0x29
	.byte	0x8
	.uleb128 0xd
	.4byte	.LASF46
	.byte	0xc
	.byte	0x1d
	.byte	0x10
	.4byte	0x29
	.byte	0x10
	.uleb128 0xd
	.4byte	.LASF47
	.byte	0xc
	.byte	0x1e
	.byte	0x10
	.4byte	0x29
	.byte	0x18
	.uleb128 0xd
	.4byte	.LASF48
	.byte	0xc
	.byte	0x22
	.byte	0xd
	.4byte	0x30
	.byte	0x20
	.uleb128 0xd
	.4byte	.LASF49
	.byte	0xc
	.byte	0x23
	.byte	0x6
	.4byte	0x30
	.byte	0x24
	.uleb128 0xd
	.4byte	.LASF50
	.byte	0xc
	.byte	0x24
	.byte	0x8
	.4byte	0x56
	.byte	0x28
	.uleb128 0xd
	.4byte	.LASF51
	.byte	0xc
	.byte	0x25
	.byte	0x6
	.4byte	0x30
	.byte	0x30
	.uleb128 0xd
	.4byte	.LASF52
	.byte	0xc
	.byte	0x26
	.byte	0xf
	.4byte	0x37
	.byte	0x34
	.uleb128 0xd
	.4byte	.LASF53
	.byte	0xc
	.byte	0x27
	.byte	0xf
	.4byte	0x37
	.byte	0x38
	.uleb128 0xd
	.4byte	.LASF54
	.byte	0xc
	.byte	0x28
	.byte	0x6
	.4byte	0x30
	.byte	0x3c
	.uleb128 0xd
	.4byte	.LASF55
	.byte	0xc
	.byte	0x29
	.byte	0x11
	.4byte	0x4cd
	.byte	0x40
	.uleb128 0xd
	.4byte	.LASF56
	.byte	0xc
	.byte	0x2a
	.byte	0xf
	.4byte	0x37
	.byte	0x48
	.uleb128 0xd
	.4byte	.LASF57
	.byte	0xc
	.byte	0x2b
	.byte	0xb
	.4byte	0x37
	.byte	0x4c
	.byte	0
	.uleb128 0x11
	.4byte	.LASF58
	.2byte	0x3c0
	.byte	0xd
	.byte	0x6c
	.byte	0x8
	.4byte	0x4c2
	.uleb128 0x12
	.string	"id"
	.byte	0xd
	.byte	0x6d
	.byte	0x9
	.4byte	0x122
	.byte	0
	.uleb128 0xd
	.4byte	.LASF59
	.byte	0xd
	.byte	0x6e
	.byte	0xc
	.4byte	0x122
	.byte	0x4
	.uleb128 0xd
	.4byte	.LASF60
	.byte	0xd
	.byte	0x70
	.byte	0x9
	.4byte	0x1db
	.byte	0x8
	.uleb128 0xd
	.4byte	.LASF61
	.byte	0xd
	.byte	0x72
	.byte	0xf
	.4byte	0x960
	.byte	0x28
	.uleb128 0x12
	.string	"uid"
	.byte	0xd
	.byte	0x74
	.byte	0x9
	.4byte	0x122
	.byte	0x2c
	.uleb128 0x12
	.string	"gid"
	.byte	0xd
	.byte	0x75
	.byte	0x9
	.4byte	0x122
	.byte	0x30
	.uleb128 0xd
	.4byte	.LASF62
	.byte	0xd
	.byte	0x77
	.byte	0x13
	.4byte	0x4cd
	.byte	0x38
	.uleb128 0xd
	.4byte	.LASF63
	.byte	0xd
	.byte	0x78
	.byte	0x13
	.4byte	0x85d
	.byte	0x40
	.uleb128 0xd
	.4byte	.LASF64
	.byte	0xd
	.byte	0x7a
	.byte	0x14
	.4byte	0x902
	.byte	0x50
	.uleb128 0xd
	.4byte	.LASF65
	.byte	0xd
	.byte	0x7b
	.byte	0xc
	.4byte	0x8f6
	.byte	0x68
	.uleb128 0xd
	.4byte	.LASF66
	.byte	0xd
	.byte	0x7d
	.byte	0x9
	.4byte	0x122
	.byte	0x70
	.uleb128 0xd
	.4byte	.LASF67
	.byte	0xd
	.byte	0x7e
	.byte	0xd
	.4byte	0x19c
	.byte	0x78
	.uleb128 0xd
	.4byte	.LASF68
	.byte	0xd
	.byte	0x7f
	.byte	0x9
	.4byte	0x122
	.byte	0x80
	.uleb128 0xd
	.4byte	.LASF69
	.byte	0xd
	.byte	0x82
	.byte	0x10
	.4byte	0x987
	.byte	0x88
	.uleb128 0xd
	.4byte	.LASF70
	.byte	0xd
	.byte	0x83
	.byte	0x10
	.4byte	0x987
	.byte	0x90
	.uleb128 0xd
	.4byte	.LASF71
	.byte	0xd
	.byte	0x85
	.byte	0x11
	.4byte	0x29
	.byte	0x98
	.uleb128 0xd
	.4byte	.LASF72
	.byte	0xd
	.byte	0x86
	.byte	0xc
	.4byte	0xc2
	.byte	0xa0
	.uleb128 0xd
	.4byte	.LASF73
	.byte	0xd
	.byte	0x87
	.byte	0xb
	.4byte	0x8f6
	.byte	0xa8
	.uleb128 0xd
	.4byte	.LASF74
	.byte	0xd
	.byte	0x89
	.byte	0x8
	.4byte	0x30
	.byte	0xb0
	.uleb128 0xd
	.4byte	.LASF75
	.byte	0xd
	.byte	0x8b
	.byte	0x13
	.4byte	0x92a
	.byte	0xc0
	.uleb128 0x13
	.4byte	.LASF76
	.byte	0xd
	.byte	0x8c
	.byte	0x13
	.4byte	0x992
	.2byte	0x370
	.uleb128 0x13
	.4byte	.LASF77
	.byte	0xd
	.byte	0x8d
	.byte	0x13
	.4byte	0x85d
	.2byte	0x378
	.uleb128 0x14
	.string	"rr"
	.byte	0xd
	.byte	0x90
	.byte	0x4
	.4byte	0x96c
	.2byte	0x388
	.uleb128 0x13
	.4byte	.LASF78
	.byte	0xd
	.byte	0xb6
	.byte	0x9
	.4byte	0xda
	.2byte	0x398
	.uleb128 0x13
	.4byte	.LASF79
	.byte	0xd
	.byte	0xb8
	.byte	0xb
	.4byte	0x56
	.2byte	0x3a0
	.uleb128 0x14
	.string	"mm"
	.byte	0xd
	.byte	0xb9
	.byte	0x13
	.4byte	0x4cd
	.2byte	0x3a8
	.uleb128 0x13
	.4byte	.LASF80
	.byte	0xd
	.byte	0xbc
	.byte	0x1a
	.4byte	0x88b
	.2byte	0x3b0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.4byte	0x350
	.uleb128 0x10
	.4byte	.LASF62
	.uleb128 0x6
	.byte	0x8
	.4byte	0x4c8
	.uleb128 0x9
	.4byte	0x4de
	.4byte	0x4de
	.uleb128 0x15
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.4byte	0x28c
	.uleb128 0xb
	.4byte	.LASF82
	.byte	0xc
	.byte	0x2e
	.byte	0x1a
	.4byte	0x4d3
	.uleb128 0x9
	.4byte	0x28c
	.4byte	0x4fb
	.uleb128 0x15
	.byte	0
	.uleb128 0xb
	.4byte	.LASF83
	.byte	0xc
	.byte	0x2f
	.byte	0x19
	.4byte	0x4f0
	.uleb128 0x11
	.4byte	.LASF84
	.2byte	0x186
	.byte	0xe
	.byte	0x6
	.byte	0x8
	.4byte	0x566
	.uleb128 0xd
	.4byte	.LASF85
	.byte	0xe
	.byte	0x7
	.byte	0x7
	.4byte	0x566
	.byte	0
	.uleb128 0xd
	.4byte	.LASF86
	.byte	0xe
	.byte	0x8
	.byte	0x7
	.4byte	0x566
	.byte	0x41
	.uleb128 0xd
	.4byte	.LASF87
	.byte	0xe
	.byte	0x9
	.byte	0x7
	.4byte	0x566
	.byte	0x82
	.uleb128 0xd
	.4byte	.LASF88
	.byte	0xe
	.byte	0xa
	.byte	0x7
	.4byte	0x566
	.byte	0xc3
	.uleb128 0x13
	.4byte	.LASF89
	.byte	0xe
	.byte	0xb
	.byte	0x7
	.4byte	0x566
	.2byte	0x104
	.uleb128 0x13
	.4byte	.LASF90
	.byte	0xe
	.byte	0xc
	.byte	0x7
	.4byte	0x566
	.2byte	0x145
	.byte	0
	.uleb128 0x9
	.4byte	0x5c
	.4byte	0x576
	.uleb128 0xe
	.4byte	0x29
	.byte	0x40
	.byte	0
	.uleb128 0xb
	.4byte	.LASF91
	.byte	0xe
	.byte	0xf
	.byte	0x17
	.4byte	0x507
	.uleb128 0xb
	.4byte	.LASF92
	.byte	0xf
	.byte	0x1c
	.byte	0xc
	.4byte	0x30
	.uleb128 0x9
	.4byte	0x63
	.4byte	0x599
	.uleb128 0x15
	.byte	0
	.uleb128 0x7
	.4byte	0x58e
	.uleb128 0xb
	.4byte	.LASF93
	.byte	0xf
	.byte	0x21
	.byte	0x13
	.4byte	0x599
	.uleb128 0xb
	.4byte	.LASF94
	.byte	0xf
	.byte	0x40
	.byte	0x1
	.4byte	0xda
	.uleb128 0xb
	.4byte	.LASF95
	.byte	0x10
	.byte	0xa
	.byte	0x16
	.4byte	0x29
	.uleb128 0x16
	.4byte	.LASF101
	.byte	0x7
	.byte	0x4
	.4byte	0x37
	.byte	0x11
	.byte	0xb
	.byte	0x6
	.4byte	0x5f3
	.uleb128 0x17
	.4byte	.LASF96
	.byte	0
	.uleb128 0x17
	.4byte	.LASF97
	.byte	0x1
	.uleb128 0x17
	.4byte	.LASF98
	.byte	0x2
	.uleb128 0x17
	.4byte	.LASF99
	.byte	0x3
	.uleb128 0x17
	.4byte	.LASF100
	.byte	0x4
	.byte	0
	.uleb128 0xb
	.4byte	.LASF101
	.byte	0x11
	.byte	0x12
	.byte	0x19
	.4byte	0x5c2
	.uleb128 0x16
	.4byte	.LASF102
	.byte	0x7
	.byte	0x4
	.4byte	0x37
	.byte	0x11
	.byte	0x14
	.byte	0x6
	.4byte	0x63c
	.uleb128 0x17
	.4byte	.LASF103
	.byte	0x74
	.uleb128 0x17
	.4byte	.LASF104
	.byte	0x6b
	.uleb128 0x17
	.4byte	.LASF105
	.byte	0x62
	.uleb128 0x17
	.4byte	.LASF106
	.byte	0x61
	.uleb128 0x17
	.4byte	.LASF107
	.byte	0x65
	.uleb128 0x17
	.4byte	.LASF108
	.byte	0x70
	.uleb128 0x17
	.4byte	.LASF109
	.byte	0x71
	.byte	0
	.uleb128 0xb
	.4byte	.LASF102
	.byte	0x11
	.byte	0x1d
	.byte	0x19
	.4byte	0x5ff
	.uleb128 0xb
	.4byte	.LASF110
	.byte	0x11
	.byte	0x1f
	.byte	0xc
	.4byte	0x30
	.uleb128 0xb
	.4byte	.LASF111
	.byte	0x11
	.byte	0x20
	.byte	0xc
	.4byte	0x30
	.uleb128 0xb
	.4byte	.LASF112
	.byte	0x11
	.byte	0x21
	.byte	0xc
	.4byte	0x30
	.uleb128 0x18
	.4byte	0x67c
	.uleb128 0x19
	.4byte	0x5c2
	.uleb128 0x19
	.4byte	0x67c
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.4byte	0x63
	.uleb128 0xb
	.4byte	.LASF113
	.byte	0x12
	.byte	0x7e
	.byte	0xf
	.4byte	0x68e
	.uleb128 0x6
	.byte	0x8
	.4byte	0x66c
	.uleb128 0x11
	.4byte	.LASF114
	.2byte	0x210
	.byte	0x13
	.byte	0x4a
	.byte	0x8
	.4byte	0x6cc
	.uleb128 0xd
	.4byte	.LASF115
	.byte	0x13
	.byte	0x4b
	.byte	0xe
	.4byte	0x275
	.byte	0
	.uleb128 0x13
	.4byte	.LASF116
	.byte	0x13
	.byte	0x4c
	.byte	0x9
	.4byte	0x8b
	.2byte	0x200
	.uleb128 0x13
	.4byte	.LASF117
	.byte	0x13
	.byte	0x4d
	.byte	0x9
	.4byte	0x8b
	.2byte	0x204
	.byte	0
	.uleb128 0x1a
	.2byte	0x210
	.byte	0x14
	.byte	0x22
	.byte	0x3
	.4byte	0x700
	.uleb128 0xd
	.4byte	.LASF115
	.byte	0x14
	.byte	0x23
	.byte	0x10
	.4byte	0x275
	.byte	0
	.uleb128 0x13
	.4byte	.LASF116
	.byte	0x14
	.byte	0x24
	.byte	0x8
	.4byte	0xb6
	.2byte	0x200
	.uleb128 0x13
	.4byte	.LASF117
	.byte	0x14
	.byte	0x25
	.byte	0x8
	.4byte	0xb6
	.2byte	0x204
	.byte	0
	.uleb128 0x1b
	.2byte	0x210
	.byte	0x14
	.byte	0x20
	.byte	0x2
	.4byte	0x71c
	.uleb128 0x1c
	.4byte	.LASF143
	.byte	0x14
	.byte	0x21
	.byte	0x1c
	.4byte	0x694
	.uleb128 0x1d
	.4byte	0x6cc
	.byte	0
	.uleb128 0x11
	.4byte	.LASF118
	.2byte	0x210
	.byte	0x14
	.byte	0x1f
	.byte	0x8
	.4byte	0x731
	.uleb128 0x1e
	.4byte	0x700
	.byte	0
	.byte	0
	.uleb128 0xc
	.4byte	.LASF119
	.byte	0x78
	.byte	0x15
	.byte	0xd1
	.byte	0x8
	.4byte	0x7ff
	.uleb128 0x12
	.string	"x19"
	.byte	0x15
	.byte	0xd2
	.byte	0x13
	.4byte	0x29
	.byte	0
	.uleb128 0x12
	.string	"x20"
	.byte	0x15
	.byte	0xd3
	.byte	0x13
	.4byte	0x29
	.byte	0x8
	.uleb128 0x12
	.string	"x21"
	.byte	0x15
	.byte	0xd4
	.byte	0x13
	.4byte	0x29
	.byte	0x10
	.uleb128 0x12
	.string	"x22"
	.byte	0x15
	.byte	0xd5
	.byte	0x13
	.4byte	0x29
	.byte	0x18
	.uleb128 0x12
	.string	"x23"
	.byte	0x15
	.byte	0xd6
	.byte	0x13
	.4byte	0x29
	.byte	0x20
	.uleb128 0x12
	.string	"x24"
	.byte	0x15
	.byte	0xd7
	.byte	0x13
	.4byte	0x29
	.byte	0x28
	.uleb128 0x12
	.string	"x25"
	.byte	0x15
	.byte	0xd8
	.byte	0x13
	.4byte	0x29
	.byte	0x30
	.uleb128 0x12
	.string	"x26"
	.byte	0x15
	.byte	0xd9
	.byte	0x13
	.4byte	0x29
	.byte	0x38
	.uleb128 0x12
	.string	"x27"
	.byte	0x15
	.byte	0xda
	.byte	0x13
	.4byte	0x29
	.byte	0x40
	.uleb128 0x12
	.string	"x28"
	.byte	0x15
	.byte	0xdb
	.byte	0x13
	.4byte	0x29
	.byte	0x48
	.uleb128 0x12
	.string	"fp"
	.byte	0x15
	.byte	0xdc
	.byte	0x13
	.4byte	0x29
	.byte	0x50
	.uleb128 0x12
	.string	"sp"
	.byte	0x15
	.byte	0xdd
	.byte	0x13
	.4byte	0x29
	.byte	0x58
	.uleb128 0x12
	.string	"pc"
	.byte	0x15
	.byte	0xde
	.byte	0x13
	.4byte	0x29
	.byte	0x60
	.uleb128 0x12
	.string	"sp0"
	.byte	0x15
	.byte	0xdf
	.byte	0x13
	.4byte	0x29
	.byte	0x68
	.uleb128 0xd
	.4byte	.LASF120
	.byte	0x15
	.byte	0xe0
	.byte	0x13
	.4byte	0x29
	.byte	0x70
	.byte	0
	.uleb128 0x11
	.4byte	.LASF121
	.2byte	0x2a0
	.byte	0x15
	.byte	0xe3
	.byte	0x8
	.4byte	0x843
	.uleb128 0xd
	.4byte	.LASF119
	.byte	0x15
	.byte	0xe4
	.byte	0x19
	.4byte	0x731
	.byte	0
	.uleb128 0xd
	.4byte	.LASF122
	.byte	0x15
	.byte	0xe5
	.byte	0x19
	.4byte	0x29
	.byte	0x78
	.uleb128 0xd
	.4byte	.LASF118
	.byte	0x15
	.byte	0xe6
	.byte	0x19
	.4byte	0x71c
	.byte	0x80
	.uleb128 0x13
	.4byte	.LASF123
	.byte	0x15
	.byte	0xe7
	.byte	0x19
	.4byte	0x29
	.2byte	0x290
	.byte	0
	.uleb128 0xf
	.4byte	.LASF124
	.byte	0x15
	.2byte	0x1a6
	.byte	0x16
	.4byte	0x29
	.uleb128 0xf
	.4byte	.LASF125
	.byte	0x15
	.2byte	0x1a8
	.byte	0xc
	.4byte	0x30
	.uleb128 0xc
	.4byte	.LASF126
	.byte	0x10
	.byte	0x16
	.byte	0x1f
	.byte	0x8
	.4byte	0x885
	.uleb128 0xd
	.4byte	.LASF127
	.byte	0x16
	.byte	0x20
	.byte	0x14
	.4byte	0x885
	.byte	0
	.uleb128 0xd
	.4byte	.LASF128
	.byte	0x16
	.byte	0x20
	.byte	0x1b
	.4byte	0x885
	.byte	0x8
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.4byte	0x85d
	.uleb128 0x1f
	.4byte	.LASF129
	.byte	0x8
	.byte	0x16
	.2byte	0x19b
	.byte	0x8
	.4byte	0x8a8
	.uleb128 0x20
	.4byte	.LASF130
	.byte	0x16
	.2byte	0x19c
	.byte	0x15
	.4byte	0x8d3
	.byte	0
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF131
	.byte	0x10
	.byte	0x16
	.2byte	0x19f
	.byte	0x8
	.4byte	0x8d3
	.uleb128 0x20
	.4byte	.LASF127
	.byte	0x16
	.2byte	0x1a0
	.byte	0x15
	.4byte	0x8d3
	.byte	0
	.uleb128 0x20
	.4byte	.LASF132
	.byte	0x16
	.2byte	0x1a0
	.byte	0x1d
	.4byte	0x8d9
	.byte	0x8
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.4byte	0x8a8
	.uleb128 0x6
	.byte	0x8
	.4byte	0x8d3
	.uleb128 0x21
	.byte	0x8
	.byte	0x17
	.byte	0x45
	.byte	0x9
	.4byte	0x8f6
	.uleb128 0xd
	.4byte	.LASF133
	.byte	0x17
	.byte	0x46
	.byte	0x10
	.4byte	0x18c
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF134
	.byte	0x17
	.byte	0x47
	.byte	0x3
	.4byte	0x8df
	.uleb128 0xc
	.4byte	.LASF64
	.byte	0x18
	.byte	0x18
	.byte	0xc
	.byte	0x8
	.4byte	0x92a
	.uleb128 0xd
	.4byte	.LASF135
	.byte	0x18
	.byte	0xd
	.byte	0x13
	.4byte	0x85d
	.byte	0
	.uleb128 0xd
	.4byte	.LASF136
	.byte	0x18
	.byte	0xe
	.byte	0xd
	.4byte	0x8f6
	.byte	0x10
	.byte	0
	.uleb128 0x11
	.4byte	.LASF137
	.2byte	0x2b0
	.byte	0x19
	.byte	0x1e
	.byte	0x8
	.4byte	0x960
	.uleb128 0xd
	.4byte	.LASF72
	.byte	0x19
	.byte	0x1f
	.byte	0xc
	.4byte	0xc2
	.byte	0
	.uleb128 0xd
	.4byte	.LASF138
	.byte	0x19
	.byte	0x20
	.byte	0x11
	.4byte	0x29
	.byte	0x8
	.uleb128 0xd
	.4byte	.LASF139
	.byte	0x19
	.byte	0x21
	.byte	0x18
	.4byte	0x7ff
	.byte	0x10
	.byte	0
	.uleb128 0x5
	.4byte	.LASF140
	.byte	0xd
	.byte	0x5f
	.byte	0x16
	.4byte	0x37
	.uleb128 0xc
	.4byte	.LASF141
	.byte	0x10
	.byte	0xd
	.byte	0x8e
	.byte	0x9
	.4byte	0x987
	.uleb128 0xd
	.4byte	.LASF142
	.byte	0xd
	.byte	0x8f
	.byte	0x14
	.4byte	0x85d
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.4byte	0x30
	.uleb128 0x10
	.4byte	.LASF76
	.uleb128 0x6
	.byte	0x8
	.4byte	0x98d
	.uleb128 0x22
	.4byte	.LASF152
	.2byte	0x2000
	.byte	0xd
	.byte	0xc0
	.byte	0x7
	.4byte	0x9bf
	.uleb128 0x1c
	.4byte	.LASF144
	.byte	0xd
	.byte	0xc1
	.byte	0x15
	.4byte	0x350
	.uleb128 0x1c
	.4byte	.LASF145
	.byte	0xd
	.byte	0xc2
	.byte	0x11
	.4byte	0x9bf
	.byte	0
	.uleb128 0x9
	.4byte	0x29
	.4byte	0x9d0
	.uleb128 0xa
	.4byte	0x29
	.2byte	0x3ff
	.byte	0
	.uleb128 0xb
	.4byte	.LASF146
	.byte	0xd
	.byte	0xc6
	.byte	0x19
	.4byte	0x998
	.uleb128 0xb
	.4byte	.LASF147
	.byte	0xd
	.byte	0xc7
	.byte	0x16
	.4byte	0x4c8
	.uleb128 0xb
	.4byte	.LASF148
	.byte	0x1a
	.byte	0x13
	.byte	0x15
	.4byte	0x37
	.uleb128 0x9
	.4byte	0x5c
	.4byte	0xa05
	.uleb128 0xa
	.4byte	0x29
	.2byte	0x216
	.byte	0
	.uleb128 0x23
	.4byte	.LASF153
	.byte	0x1
	.byte	0x24
	.byte	0xd
	.4byte	0x9f4
	.2byte	0x217
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.uleb128 0x24
	.4byte	.LASF154
	.byte	0x1
	.byte	0x28
	.byte	0x5
	.4byte	0x30
	.8byte	.LFB225
	.8byte	.LFE225-.LFB225
	.uleb128 0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x17
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0x3
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x2c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x8
	.byte	0
	.2byte	0
	.2byte	0
	.8byte	.LFB225
	.8byte	.LFE225-.LFB225
	.8byte	0
	.8byte	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.8byte	.LFB225
	.8byte	.LFE225
	.8byte	0
	.8byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF24:
	.string	"_raw_spinlock_t"
.LASF104:
	.string	"BOOT_KBD"
.LASF39:
	.string	"empty_zero_page"
.LASF84:
	.string	"utsname"
.LASF31:
	.string	"cpu_online_map"
.LASF59:
	.string	"rank"
.LASF22:
	.string	"raw_spinlock_t"
.LASF108:
	.string	"BOOT_CF9_FORCE"
.LASF72:
	.string	"flags"
.LASF70:
	.string	"clear_child_tid"
.LASF100:
	.string	"REBOOT_GPIO"
.LASF51:
	.string	"nodenumber"
.LASF111:
	.string	"reboot_cpu"
.LASF37:
	.string	"pgprot_t"
.LASF101:
	.string	"reboot_mode"
.LASF1:
	.string	"unsigned int"
.LASF127:
	.string	"next"
.LASF88:
	.string	"version"
.LASF69:
	.string	"set_child_tid"
.LASF82:
	.string	"_cpu_pda"
.LASF18:
	.string	"paddr_t"
.LASF125:
	.string	"bootloader_type"
.LASF143:
	.string	"user_fpsimd"
.LASF114:
	.string	"user_fpsimd_state"
.LASF128:
	.string	"prev"
.LASF63:
	.string	"aspace_link"
.LASF21:
	.string	"id_t"
.LASF147:
	.string	"bootstrap_aspace"
.LASF135:
	.string	"list"
.LASF14:
	.string	"uint32_t"
.LASF30:
	.string	"cpu_possible_map"
.LASF42:
	.string	"__int128 unsigned"
.LASF52:
	.string	"__softirq_pending"
.LASF123:
	.string	"fault_address"
.LASF93:
	.string	"lwk_banner"
.LASF57:
	.string	"apic_timer_irqs"
.LASF12:
	.string	"long long unsigned int"
.LASF95:
	.string	"loops_per_jiffy"
.LASF98:
	.string	"REBOOT_HARD"
.LASF152:
	.string	"task_union"
.LASF23:
	.string	"__atomic_hash"
.LASF119:
	.string	"cpu_context"
.LASF35:
	.string	"pgdval_t"
.LASF56:
	.string	"timer_reload_value"
.LASF136:
	.string	"sigset"
.LASF144:
	.string	"task_info"
.LASF20:
	.string	"init_elf_image"
.LASF17:
	.string	"_Bool"
.LASF75:
	.string	"arch"
.LASF150:
	.string	"arch/arm64/kernel/asm-offsets.c"
.LASF137:
	.string	"arch_task"
.LASF36:
	.string	"pgd_t"
.LASF120:
	.string	"usersp"
.LASF53:
	.string	"__nmi_count"
.LASF130:
	.string	"first"
.LASF41:
	.string	"idmap_pg_dir"
.LASF109:
	.string	"BOOT_CF9_SAFE"
.LASF99:
	.string	"REBOOT_SOFT"
.LASF74:
	.string	"exit_status"
.LASF121:
	.string	"thread_struct"
.LASF3:
	.string	"char"
.LASF115:
	.string	"vregs"
.LASF110:
	.string	"reboot_default"
.LASF117:
	.string	"fpcr"
.LASF131:
	.string	"hlist_node"
.LASF10:
	.string	"__u32"
.LASF89:
	.string	"machine"
.LASF27:
	.string	"bits"
.LASF73:
	.string	"saved_sigmask"
.LASF58:
	.string	"task_struct"
.LASF148:
	.string	"sched_hz"
.LASF132:
	.string	"pprev"
.LASF4:
	.string	"long long int"
.LASF116:
	.string	"fpsr"
.LASF46:
	.string	"kernelstack"
.LASF92:
	.string	"__flag"
.LASF81:
	.string	"page"
.LASF103:
	.string	"BOOT_TRIPLE"
.LASF16:
	.string	"bool"
.LASF83:
	.string	"boot_cpu_pda"
.LASF33:
	.string	"memstart_addr"
.LASF96:
	.string	"REBOOT_COLD"
.LASF44:
	.string	"pcurrent"
.LASF66:
	.string	"cpu_id"
.LASF112:
	.string	"reboot_force"
.LASF67:
	.string	"cpu_mask"
.LASF77:
	.string	"migrate_link"
.LASF76:
	.string	"fdTable"
.LASF49:
	.string	"cpunumber"
.LASF65:
	.string	"sigblocked"
.LASF113:
	.string	"arm_pm_restart"
.LASF54:
	.string	"mmu_state"
.LASF78:
	.string	"sched_irqs_on"
.LASF55:
	.string	"active_aspace"
.LASF80:
	.string	"preempt_notifiers"
.LASF50:
	.string	"irqstackptr"
.LASF32:
	.string	"cpu_present_map"
.LASF11:
	.string	"__u64"
.LASF13:
	.string	"phys_addr_t"
.LASF134:
	.string	"sigset_t"
.LASF140:
	.string	"taskstate_t"
.LASF149:
	.ascii	"GNU C99 9.3.0 -march=armv8.3-a -mlittle-endian -mabi=lp64 -g"
	.ascii	" -g -O2 -std=gnu99 -fno-strict-aliasi"
	.string	"ng -fno-strict-overflow -fno-common -fno-pie -fno-stack-protector -fgnu89-inline -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-builtin -ffunction-sections -fno-reorder-blocks -funit-at-a-time -fasynchronous-unwind-tables -fstack-clash-protection"
.LASF94:
	.string	"per_cpu__umem_only"
.LASF8:
	.string	"short int"
.LASF2:
	.string	"long int"
.LASF28:
	.string	"cpumask_t"
.LASF26:
	.string	"slock"
.LASF68:
	.string	"cpu_target_id"
.LASF15:
	.string	"uint64_t"
.LASF71:
	.string	"ptrace"
.LASF19:
	.string	"lwk_command_line"
.LASF29:
	.string	"_unused_cpumask_arg_"
.LASF142:
	.string	"sched_link"
.LASF91:
	.string	"linux_utsname"
.LASF25:
	.string	"cpumask"
.LASF138:
	.string	"addr_limit"
.LASF60:
	.string	"name"
.LASF145:
	.string	"stack"
.LASF141:
	.string	"task_rr"
.LASF124:
	.string	"boot_option_idle_override"
.LASF153:
	.string	"syscalls"
.LASF105:
	.string	"BOOT_BIOS"
.LASF0:
	.string	"long unsigned int"
.LASF48:
	.string	"irqcount"
.LASF86:
	.string	"nodename"
.LASF139:
	.string	"thread"
.LASF129:
	.string	"hlist_head"
.LASF7:
	.string	"unsigned char"
.LASF133:
	.string	"bitmap"
.LASF90:
	.string	"domainname"
.LASF38:
	.string	"pgprot_default"
.LASF118:
	.string	"fpsimd_state"
.LASF102:
	.string	"reboot_type"
.LASF45:
	.string	"data_offset"
.LASF62:
	.string	"aspace"
.LASF126:
	.string	"list_head"
.LASF61:
	.string	"state"
.LASF43:
	.string	"ARM64_pda"
.LASF146:
	.string	"bootstrap_task_union"
.LASF106:
	.string	"BOOT_ACPI"
.LASF47:
	.string	"oldsp"
.LASF107:
	.string	"BOOT_EFI"
.LASF6:
	.string	"signed char"
.LASF5:
	.string	"short unsigned int"
.LASF87:
	.string	"release"
.LASF9:
	.string	"__kernel_uintptr_t"
.LASF154:
	.string	"main"
.LASF97:
	.string	"REBOOT_WARM"
.LASF34:
	.string	"pteval_t"
.LASF151:
	.string	"/home/friedy/XPHOTON/kitten"
.LASF79:
	.string	"comm"
.LASF85:
	.string	"sysname"
.LASF64:
	.string	"sigpending"
.LASF122:
	.string	"tp_value"
.LASF40:
	.string	"swapper_pg_dir"
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
