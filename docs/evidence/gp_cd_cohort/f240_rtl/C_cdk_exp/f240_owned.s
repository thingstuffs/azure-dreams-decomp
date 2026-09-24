	.file	1 "f240_owned.c"

 # -G value = 32, Cpu = 3000, ISA = 1
 # GNU C version cygnus-2.7.2-970404 SN32.3.7.0004 (SonyPSX) compiled by CC.
 # options passed:  -G32 -O2 -w
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

	.extern	D_80083968, 768

	.text
	.text
	.ent	func_8003F240
func_8003F240:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	lui	$4,%hi(D_80083968) # high
	lbu	$3,D_800814D0
	addiu	$4,$4,%lo(D_80083968) # low
	addu	$3,$3,31
	andi	$3,$3,0x001f
	sll	$2,$3,1
	addu	$2,$2,$3
	sll	$2,$2,3
	addu	$2,$2,$4
	lbu	$2,0($2)
	j	$31
	.end	func_8003F240
