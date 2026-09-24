	.file	1 "<repo>/work/wall_81811E30/candidate.c"
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
	move	$5,$6
	lui	$3,%hi(D_800157D2) # high
$L6:
	addiu	$3,$3,%lo(D_800157D2) # low
	sll	$2,$5,2
	addu	$2,$2,$5
	sll	$2,$2,2
	subu	$2,$2,$5
	addu	$2,$2,$3
	lbu	$2,0($2)
	#nop
	beq	$2,$0,$L3
	bne	$2,$4,$L4
	addu	$6,$6,1
$L4:
	addu	$5,$5,1
	slt	$2,$5,64
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L6
	lui	$3,%hi(D_800157D2) # high
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
