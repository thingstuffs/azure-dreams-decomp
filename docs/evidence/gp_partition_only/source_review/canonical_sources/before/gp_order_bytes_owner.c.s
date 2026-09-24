	.file	1 "gp_order_bytes_owner.c"

 # -G value = 8, Cpu = 3000, ISA = 1
 # GNU C version cygnus-2.7.2-970404 SN32.3.7.0004 (SonyPSX) compiled by CC.
 # options passed:  -O2 -w -fno-strength-reduce
 # options enabled:  -fdefer-pop -fomit-frame-pointer -fcse-follow-jumps
 # -fcse-skip-blocks -fexpensive-optimizations -fthread-jumps -fpeephole
 # -fforce-mem -ffunction-cse -finline -fkeep-static-consts -fcaller-saves
 # -fpcc-struct-return -fdelayed-branch -frerun-cse-after-loop
 # -fschedule-insns -fschedule-insns2 -fcommon -fverbose-asm -fgnu-linker
 # -mgas -mgpOPT -mgpopt -msoft-float -mcpu=3000

gcc2_compiled.:
__gnu_compiled_c:
 #APP
	.include "include/labels.inc"

 #NO_APP
	.globl	D_80080B30
	.sdata
	.align	2
D_80080B30:
	.byte	1
	.byte	3
	.byte	2
	.byte	4
	.text
	.align	2
	.globl	func_80049F68

	.extern	D_8002E5E8, 12
	.extern	D_8002E5D8, 16

	.text
	.text
	.ent	func_80049F68
func_80049F68:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	move	$7,$0
	lui	$9,%hi(D_8002E5D8) # high
	addiu	$8,$9,%lo(D_8002E5D8) # low
	lui	$2,%hi(D_8002E5E8) # high
	addu	$10,$4,160
	lw	$3,%lo(D_8002E5E8)($2)
	addiu	$2,$2,%lo(D_8002E5E8) # low
	sw	$3,160($4)
 #APP
 #NO_APP
	lw	$3,4($2)
	li	$6,32			# 0x00000020
	sw	$3,164($4)
	lw	$2,8($2)
	move	$5,$4
	sw	$2,168($4)
$L2:
	lw	$2,%lo(D_8002E5D8)($9)
	#nop
	sw	$2,32($5)
	lw	$2,4($8)
	addu	$3,$4,$6
	sw	$2,36($5)
	lw	$2,8($8)
	addu	$6,$6,32
	sw	$2,40($5)
	lw	$2,12($8)
	addu	$7,$7,1
	sw	$3,52($5)
	sw	$10,56($5)
	sw	$2,44($5)
	slt	$2,$7,4
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L2
	addu	$5,$5,32
	.set	macro
	.set	reorder

	lbu	$3,D_80080B30
	li	$2,4			# 0x00000004
	.set	noreorder
	.set	nomacro
	beq	$3,$2,$L6
	addu	$6,$4,48
	.set	macro
	.set	reorder

	move	$7,$2
	la	$5,D_80080B30
$L7:
	lbu	$2,0($5)
	addu	$5,$5,1
	sll	$2,$2,5
	addu	$2,$2,$4
	addu	$2,$2,48
	sw	$2,12($6)
	lbu	$3,0($5)
	#nop
	.set	noreorder
	.set	nomacro
	bne	$3,$7,$L7
	move	$6,$2
	.set	macro
	.set	reorder

$L6:
	.set	noreorder
	.set	nomacro
	j	$31
	sw	$0,12($6)
	.set	macro
	.set	reorder

	.end	func_80049F68
