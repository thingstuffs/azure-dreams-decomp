	.file	1 "f240_owned.c"
gcc2_compiled.:
__gnu_compiled_c:
 #APP
	.include "include/labels.inc"

 #NO_APP
	.globl	D_800814D0
	.sdata
D_800814D0:
	.byte	0
	.globl	D_800814D4
D_800814D4:
	.byte	0
	.globl	D_800814CC
	.align	2
D_800814CC:
	.word	0
	.globl	D_80081450
	.align	2
D_80081450:
	.word	0
	.space	4
	.globl	D_80080AD0
D_80080AD0:
	.byte	0
	.globl	D_80080AD2
	.align	1
D_80080AD2:
	.half	0
	.globl	D_80080AD4
	.align	1
D_80080AD4:
	.half	0
	.globl	D_80080AD8
	.align	2
D_80080AD8:
	.word	0
	.globl	D_80080ADC
	.align	2
D_80080ADC:
	.word	0
	.globl	D_800814B0
	.align	2
D_800814B0:
	.word	0
	.globl	D_800814B4
	.align	2
D_800814B4:
	.word	0
	.text
	.align	2
	.globl	func_8003F240
	.text
	.ent	func_8003F240
func_8003F240:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	lbu	$2,D_800814D0
	#nop
	addu	$2,$2,31
	andi	$2,$2,0x001f
	sll	$3,$2,1
	addu	$3,$3,$2
	lui	$2,%hi(D_80083968) # high
	addiu	$2,$2,%lo(D_80083968) # low
	sll	$3,$3,3
	addu	$3,$3,$2
	lbu	$2,0($3)
	j	$31
	.end	func_8003F240

	.extern	D_80083968, 768
