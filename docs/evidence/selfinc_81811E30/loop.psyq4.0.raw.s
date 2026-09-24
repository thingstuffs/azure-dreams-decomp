	.file	1 "<repo>/work/wall_81811E30/loop.c"

 # GNU C 2.7.2.SN32.3.7.0002 [AL 1.1, MM 40] Sony Playstation compiled by CC

 # Cc1 defaults:
 # -mgas -msoft-float

 # Cc1 arguments (-G value = 0, Cpu = 3000, ISA = 1):
 # -G0 -quiet -dumpbase -O2 -w -o

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
	la	$3,D_800157D2
	lbu	$2,0($3)
	#nop
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L3
	move	$5,$0
	.set	macro
	.set	reorder

$L5:
	andi	$2,$2,0x00ff
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
	bne	$2,$0,$L5
$L3:
	.set	noreorder
	.set	nomacro
	j	$31
	move	$2,$6
	.set	macro
	.set	reorder

	.end	func_80026E30
