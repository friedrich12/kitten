#include "unified.h"

.globl _find_first_bit_le
_find_first_bit_le:
	teq	%r1, $0	
	beq	3f
	mov	$0, %r2
1:
 ARM(	ldrb	%r3, [%r0, %r2, %lsr $3]	)
 THUMB(	lsr	%r3, %r2, $3		)
 THUMB(	ldrb	%r3, [%r0, %r3]		)
	movs	%r3, %r3
	bne	.L_found		// any now set - found zero bit
	add	%r2, %r2, $8		// next bit pointer
2:	cmp	%r2, %r1			// any more?
	blo	1b
3:	mov	%r0, %r1			// no free bits
	ret	%lr

.globl _find_next_bit_le
_find_next_bit_le:
	teq	%r1, $0
	beq	3b
	ands	%ip, %r2, $7
	beq	1b			// If new byte, goto old routine
 ARM(	ldrb	%r3, [%r0, %r2, lsr $3]	)
 THUMB(	lsr	%r3, r2, $3		)
 THUMB(	ldrb	%r3, [%r0, %r3]		)
	movs	%r3, %r3, lsr ip		// shift off unused bits
	bne	.L_found
	orr	%r2, %r2, $7		// if zero, then no bits here
	add	%r2, %r2, $1		// align bit pointer
	b	2b		        // loop for next bit

.L_found:
$if __LINUX_ARM_ARCH__ >= 5
	rsb	%r0, %r3, $0
	and	%r3, %r3, %r0
	clz	%r3, %r3
	rsb	%r3, %r3, $31
	add	%r0, %r2, %r3
$else
	tst	%r3, $0x0f
	addeq	%r2, %r2, $4
	movne	%r3, %r3, lsl $4
	tst	%r3, $0x30
	addeq	%r2, %r2, $2
	movne	%r3, %r3, lsl $2
	tst	%r3, $0x40
	addeq	%r2, %r2, $1
	mov	%r0, %r2
$endif
	cmp	%r1, %r0			// Clamp to maxbit
	movlo	%r0, %r1
	ret	%lr

