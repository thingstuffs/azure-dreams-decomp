	.file	1 "<repo>/work/wall_81811E30/loop.c"
gcc2_compiled.:
__gnu_compiled_c:
 #APP
	.include "include/labels.inc"

 #NO_APP
	.text
	.align	2
	.globl	func_80026E30
	.ent	func_80026E30
func_80026E30:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	move	$6,$0
	lui	$3,%hi(D_800157D2) # high
	lbu	$2,%lo(D_800157D2)($3)
	#nop
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L3
	move	$5,$6
	.set	macro
	.set	reorder

	addiu	$3,$3,%lo(D_800157D2) # low
	andi	$2,$2,0x00ff
$L9:
	bne	$2,$4,$L6
	addu	$6,$6,1
$L6:
	addu	$5,$5,1
	slt	$2,$5,64
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L3
	addu	$3,$3,19
	.set	macro
	.set	reorder

	lbu	$2,0($3)
	#nop
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L9
	andi	$2,$2,0x00ff
	.set	macro
	.set	reorder

$L3:
	.set	noreorder
	.set	nomacro
	j	$31
	move	$2,$6
	.set	macro
	.set	reorder

	.end	func_80026E30
