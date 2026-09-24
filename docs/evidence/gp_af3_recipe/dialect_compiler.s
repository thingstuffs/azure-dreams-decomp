	.file	1 "w_8004437C.c"
	.set	nobopt

 # -G value = 8, Cpu = 3000, ISA = 1
 # GNU C version cygnus-2.7.2-970404 SN32.3.7.0004 (SonyPSX) compiled by CC.
 # options passed:  -mmips-as -O2 -w
 # options enabled:  -fdefer-pop -fomit-frame-pointer -fcse-follow-jumps
 # -fcse-skip-blocks -fexpensive-optimizations -fthread-jumps
 # -fstrength-reduce -fpeephole -fforce-mem -ffunction-cse -finline
 # -fkeep-static-consts -fcaller-saves -fpcc-struct-return -fdelayed-branch
 # -frerun-cse-after-loop -fschedule-insns -fschedule-insns2 -fcommon
 # -fverbose-asm -fgnu-linker -mgpOPT -mgpopt -msoft-float -mcpu=3000

gcc2_compiled.:
__gnu_compiled_c:
 #APP
	.include "include/labels.inc"

 #NO_APP
	.text
	.align	2
	.globl	func_8004437C

	.extern	D_801BEE40, 16
	.extern	D_801C4640, 16
	.extern	D_80080AF3, 1
	.extern	D_80080AFC, 2
	.extern	D_80080AF4, 8

	.text
	.text
	.ent	func_8004437C
func_8004437C:
	.frame	$sp,40,$31		# vars= 0, regs= 5/0, args= 16, extra= 0
	.mask	0x800f0000,-8
	.fmask	0x00000000,0
	subu	$sp,$sp,40
	sw	$17,20($sp)
	move	$17,$5
	sw	$18,24($sp)
	move	$18,$4
	sw	$19,28($sp)
	sll	$4,$4,16
	la	$3,D_8006E704
	sra	$4,$4,14
	sw	$16,16($sp)
	addu	$16,$4,$3
	lh	$2,D_80080AFC
	la	$5,D_80080AF4
	sw	$31,32($sp)
	lw	$3,0($16)
	sll	$2,$2,2
	lw	$2,D_80080AF4($2)
	lhu	$4,D_80080AFC
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L2
	move	$19,$17
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L9
	li	$2,1			# 0x00000001
	.set	macro
	.set	reorder

$L2:
	xori	$4,$4,0x0001
	sll	$2,$4,16
	sra	$2,$2,14
	addu	$2,$2,$5
	lw	$3,0($16)
	lw	$2,0($2)
	sh	$4,D_80080AFC
	.set	noreorder
	.set	nomacro
	beq	$3,$2,$L11
	sll	$4,$19,16
	.set	macro
	.set	reorder

	jal	func_800542BC
	lb	$3,D_80080AF3
	sll	$2,$17,16
	sra	$2,$2,16
	beq	$3,$2,$L4
	jal	func_80044698
$L4:
	lw	$4,0($16)
	#nop
	lw	$2,0($4)
	li	$3,-8388608			# 0xff800000
	and	$2,$2,$3
	sw	$2,0($4)
	lw	$5,0($16)
	lh	$2,D_80080AFC
	lw	$4,0($5)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L5
	li	$3,8323072			# 0x007f0000
	.set	macro
	.set	reorder

	la	$2,D_801C4640
	.set	noreorder
	.set	nomacro
	j	$L10
	ori	$3,$3,0xffff
	.set	macro
	.set	reorder

$L5:
	ori	$3,$3,0xffff
	la	$2,D_801BEE40
$L10:
	and	$2,$2,$3
	or	$2,$4,$2
	li	$4,6			# 0x00000006
	sll	$16,$18,16
	sw	$2,0($5)
	la	$2,D_8006E704
	sra	$16,$16,14
	addu	$16,$16,$2
	lw	$5,0($16)
	.set	noreorder
	.set	nomacro
	jal	Control_CD
	move	$6,$0
	.set	macro
	.set	reorder

	lh	$2,D_80080AFC
	lw	$3,0($16)
	sll	$2,$2,2
	sw	$3,D_80080AF4($2)
	jal	func_8003F320
	sll	$4,$19,16
$L11:
	.set	noreorder
	.set	nomacro
	jal	func_8004450C
	sra	$4,$4,16
	.set	macro
	.set	reorder

	lh	$2,D_80080AFC
	#nop
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L7
	li	$4,33			# 0x00000021
	.set	macro
	.set	reorder

	li	$4,34			# 0x00000022
$L7:
	jal	SD_Call
	move	$2,$0
$L9:
	lw	$31,32($sp)
	lw	$19,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	addu	$sp,$sp,40
	j	$31
	.end	func_8004437C
