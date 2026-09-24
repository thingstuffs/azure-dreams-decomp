	.file	1 "<repo>/work/wall_81811E30/loop.c"

 # -G value = 0, Cpu = 3000, ISA = 1
 # GNU C version cygnus-2.7.2-970404 SN32.3.7.0004 (SonyPSX) compiled by CC.
 # options passed:  -G0 -O2 -w
 # options enabled:  -fdefer-pop -fomit-frame-pointer -fcse-follow-jumps
 # -fcse-skip-blocks -fexpensive-optimizations -fthread-jumps
 # -fstrength-reduce -fpeephole -fforce-mem -ffunction-cse -finline
 # -fkeep-static-consts -fcaller-saves -fpcc-struct-return -fdelayed-branch
 # -frerun-cse-after-loop -fschedule-insns -fschedule-insns2 -fcommon
 # -fverbose-asm -fgnu-linker -mgas -msoft-float -mcpu=3000

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
