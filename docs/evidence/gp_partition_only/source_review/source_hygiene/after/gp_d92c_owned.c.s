	.file	1 "gp_d92c_owned.c"

 # -G value = 8, Cpu = 3000, ISA = 1
 # GNU C version cygnus-2.7.2-970404 SN32.3.7.0004 (SonyPSX) compiled by CC.
 # options passed:  -O2 -w
 # options enabled:  -fdefer-pop -fomit-frame-pointer -fcse-follow-jumps
 # -fcse-skip-blocks -fexpensive-optimizations -fthread-jumps
 # -fstrength-reduce -fpeephole -fforce-mem -ffunction-cse -finline
 # -fkeep-static-consts -fcaller-saves -fpcc-struct-return -fdelayed-branch
 # -frerun-cse-after-loop -fschedule-insns -fschedule-insns2 -fcommon
 # -fverbose-asm -fgnu-linker -mgas -mgpOPT -mgpopt -msoft-float -mcpu=3000

gcc2_compiled.:
__gnu_compiled_c:
 #APP
	.include "include/labels.inc"

 #NO_APP
	.text
	.align	2
	.globl	func_8003D92C
	.globl	D_80080ABC
	.sdata
	.align	1
D_80080ABC:
	.half	0
	.globl	D_80080ABE
	.align	1
D_80080ABE:
	.half	0

	.extern	D_80080A9C, 2
	.extern	D_80080A98, 2
	.extern	D_80080AA0, 1
	.extern	D_80080A88, 1
	.extern	D_80080A8A, 1
	.extern	D_80082E60, 16
	.extern	D_80080A94, 2
	.extern	D_80080A84, 1
	.extern	D_80082E6F, 16
	.extern	D_80083160, 20

	.text
	.text
	.ent	func_8003D92C
func_8003D92C:
	.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, extra= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	subu	$sp,$sp,24
	lui	$3,%hi(D_80083160) # high
	lui	$2,%hi(D_80082E6F) # high
	lbu	$2,%lo(D_80082E6F)($2)
	addiu	$3,$3,%lo(D_80083160) # low
	sw	$31,20($sp)
	andi	$2,$2,0x0080
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L14
	sw	$16,16($sp)
	.set	macro
	.set	reorder

	lw	$4,16($3)
	#nop
	andi	$2,$4,0x0100
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L3
	andi	$2,$4,0x0800
	.set	macro
	.set	reorder

	lw	$2,8($3)
	#nop
	andi	$2,$2,0x0800
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L5
	li	$2,1			# 0x00000001
	.set	macro
	.set	reorder

	j	$L23
$L3:
	beq	$2,$0,$L5
	lw	$2,8($3)
	#nop
	andi	$2,$2,0x0100
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L22
	li	$2,1			# 0x00000001
	.set	macro
	.set	reorder

$L23:
	sh	$2,D_80080ABE
$L5:
	lw	$3,8($3)
	#nop
	andi	$2,$3,0x0100
	bne	$2,$0,$L9
$L22:
	sh	$0,D_80080ABE
	sh	$0,D_80080ABC
	.set	noreorder
	.set	nomacro
	j	$L21
	move	$2,$0
	.set	macro
	.set	reorder

$L9:
	lh	$2,D_80080ABE
	#nop
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L10
	andi	$2,$3,0x0800
	.set	macro
	.set	reorder

	beq	$2,$0,$L11
	lbu	$3,D_80080A84
	lhu	$2,D_80080ABC
	#nop
	addu	$2,$2,$3
	sh	$2,D_80080ABC
	sll	$2,$2,16
	sra	$2,$2,16
	slt	$2,$2,361
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L10
	li	$2,360			# 0x00000168
	.set	macro
	.set	reorder

	sh	$2,D_80080ABC
	j	$L10
$L11:
	sh	$0,D_80080ABC
$L10:
	lbu	$3,D_80080A84
	li	$2,120			# 0x00000078
	div	$2,$2,$3
	lh	$3,D_80080ABC
	#nop
	slt	$2,$2,$3
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L21
	move	$2,$0
	.set	macro
	.set	reorder

	sh	$0,D_80080ABE
	sh	$0,D_80080ABC
	.set	noreorder
	.set	nomacro
	jal	func_8003F320
	li	$16,256			# 0x00000100
	.set	macro
	.set	reorder

$L15:
	.set	noreorder
	.set	nomacro
	jal	func_80053EF0
	li	$4,4			# 0x00000004
	.set	macro
	.set	reorder

	bne	$2,$16,$L16
	jal	func_8003E758
	.set	noreorder
	.set	nomacro
	jal	func_80044618
	li	$4,2			# 0x00000002
	.set	macro
	.set	reorder

	j	$L15
$L16:
	.set	noreorder
	.set	nomacro
	jal	SD_Call
	li	$4,116			# 0x00000074
	.set	macro
	.set	reorder

$L18:
	.set	noreorder
	.set	nomacro
	jal	func_80053EF0
	li	$4,4			# 0x00000004
	.set	macro
	.set	reorder

	beq	$2,$0,$L19
	jal	func_8003E758
	.set	noreorder
	.set	nomacro
	jal	func_80044618
	li	$4,2			# 0x00000002
	.set	macro
	.set	reorder

	j	$L18
$L19:
	jal	func_8003F320
	.set	noreorder
	.set	nomacro
	jal	func_80040AA0
	li	$4,3			# 0x00000003
	.set	macro
	.set	reorder

	lui	$5,%hi(D_80082E60) # high
	lh	$4,D_80080A94
	lw	$2,%lo(D_80082E60)($5)
	li	$3,-3			# 0xfffffffd
	sb	$0,D_80080A8A
	sb	$0,D_80080A88
	sb	$0,D_80080AA0
	and	$2,$2,$3
	.set	noreorder
	.set	nomacro
	jal	func_80053DCC
	sw	$2,%lo(D_80082E60)($5)
	.set	macro
	.set	reorder

	lh	$4,D_80080A98
	jal	func_80053DF0
	lh	$4,D_80080A9C
	jal	func_80053E14
	.set	noreorder
	.set	nomacro
	jal	SD_Call
	li	$4,127			# 0x0000007f
	.set	macro
	.set	reorder

	jal	func_8003D468
	li	$3,2			# 0x00000002
	sb	$3,D_80080A84
	.set	noreorder
	.set	nomacro
	j	$L21
	li	$2,1			# 0x00000001
	.set	macro
	.set	reorder

$L14:
	move	$2,$0
$L21:
	lw	$31,20($sp)
	lw	$16,16($sp)
	addu	$sp,$sp,24
	j	$31
	.end	func_8003D92C
