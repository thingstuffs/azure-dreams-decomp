	.file	1 "w_8003FAD4.c"

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
	.globl	func_8003FAD4

	.extern	D_80081490, 4
	.extern	D_80081498, 4
	.extern	D_80083360, 128
	.extern	D_800833E0, 128
	.extern	D_801EAFE8, 74752

	.text
	.text
	.ent	func_8003FAD4
func_8003FAD4:
	.frame	$sp,32,$31		# vars= 0, regs= 4/0, args= 16, extra= 0
	.mask	0x80070000,-4
	.fmask	0x00000000,0
	subu	$sp,$sp,32
	lui	$2,%hi(D_801EAFE8) # high
	sw	$18,24($sp)
	addiu	$18,$2,%lo(D_801EAFE8) # low
	sw	$16,16($sp)
	move	$16,$0
	sw	$17,20($sp)
	move	$17,$18
	sw	$31,28($sp)
$L5:
	move	$4,$17
	.set	noreorder
	.set	nomacro
	jal	func_8003DB4C
	li	$5,73			# 0x00000049
	.set	macro
	.set	reorder

	addu	$16,$16,1
	slt	$2,$16,256
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L5
	addu	$17,$17,292
	.set	macro
	.set	reorder

	li	$16,254			# 0x000000fe
$L10:
	addu	$2,$18,292
	sw	$2,0($18)
	addu	$16,$16,-1
	.set	noreorder
	.set	nomacro
	bgez	$16,$L10
	move	$18,$2
	.set	macro
	.set	reorder

	li	$16,31			# 0x0000001f
	lui	$2,%hi(D_800833E0) # high
	addiu	$2,$2,%lo(D_800833E0) # low
	addu	$4,$2,124
	lui	$2,%hi(D_80083360) # high
	addiu	$2,$2,%lo(D_80083360) # low
	addu	$3,$2,124
	lui	$2,%hi(D_801EAFE8) # high
	addiu	$2,$2,%lo(D_801EAFE8) # low
	sw	$0,0($18)
	sw	$0,D_80081498
	sw	$2,D_80081490
$L15:
	sw	$0,0($3)
	sw	$0,0($4)
	addu	$4,$4,-4
	addu	$16,$16,-1
	.set	noreorder
	.set	nomacro
	bgez	$16,$L15
	addu	$3,$3,-4
	.set	macro
	.set	reorder

	lw	$31,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	addu	$sp,$sp,32
	j	$31
	.end	func_8003FAD4
