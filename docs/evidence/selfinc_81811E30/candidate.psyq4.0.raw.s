	.file	1 "<repo>/work/wall_81811E30/candidate.c"

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
	move	$5,$0
	move	$3,$0
$L2:
	sll	$2,$3,2
	addu	$2,$2,$3
	sll	$2,$2,2
	subu	$2,$2,$3
	lbu	$2,D_800157D2($2)
	#nop
	beq	$2,$0,$L3
	bne	$2,$4,$L4
	addu	$5,$5,1
$L4:
	addu	$3,$3,1
	slt	$2,$3,64
	bne	$2,$0,$L2
$L3:
	.set	noreorder
	.set	nomacro
	j	$31
	move	$2,$5
	.set	macro
	.set	reorder

	.end	func_80026E30
