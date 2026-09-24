	.file	1 "w_8004AB7C.c"

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
	.globl	func_8004AB7C

	.extern	D_80012090, 4
	.extern	D_80013628, 4

	.text
	.text
	.ent	func_8004AB7C
func_8004AB7C:
	.frame	$sp,32,$31		# vars= 0, regs= 3/0, args= 16, extra= 0
	.mask	0x80030000,-8
	.fmask	0x00000000,0
	subu	$sp,$sp,32
	sw	$31,24($sp)
	sw	$17,20($sp)
	.set	noreorder
	.set	nomacro
	jal	func_8003E1FC
	sw	$16,16($sp)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jal	func_8003F320
	move	$16,$0
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jal	func_800A6D60
	li	$4,1			# 0x00000001
	.set	macro
	.set	reorder

	lw	$4,D_80013628
	jal	func_800A6D98
	lui	$2,%hi(itemCategoryTable) # high
	addiu	$17,$2,%lo(itemCategoryTable) # low
$L5:
	lbu	$2,1($17)
	lw	$3,D_80012090
	#nop
	sra	$2,$2,$3
	andi	$2,$2,0x0001
	beq	$2,$0,$L4
	.set	noreorder
	.set	nomacro
	jal	func_8004AA78
	move	$4,$16
	.set	macro
	.set	reorder

$L4:
	addu	$16,$16,1
	slt	$2,$16,20
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L5
	addu	$17,$17,20
	.set	macro
	.set	reorder

	jal	func_8004A940
	.set	noreorder
	.set	nomacro
	jal	func_800A6D60
	move	$4,$0
	.set	macro
	.set	reorder

	lw	$31,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	addu	$sp,$sp,32
	j	$31
	.end	func_8004AB7C
