	.file	1 "func_80011390.c"

 # GNU C 2.7.2 [AL 1.1, MM 40] Sony Playstation compiled by GNU C

 # Cc1 defaults:
 # -mgas -msoft-float

 # Cc1 arguments (-G value = 8, Cpu = R3000, ISA = 1):
 # -quiet -dumpbase -O2 -w -o

gcc2_compiled.:
__gnu_compiled_c:
 #APP
	.include "include/labels.inc"

 #NO_APP
	.text
	.align	2
	.globl	func_80011390

	.extern	D_80027FD4, 4
	.extern	D_800200A4, 4
	.extern	D_800283A8, 4
	.extern	D_800282E8, 4
	.extern	D_80083EA4, 4
	.extern	D_800282D8, 4

	.text
	.text
	.ent	func_80011390
func_80011390:
	.frame	$sp,72,$31		# vars= 16, regs= 9/0, args= 16, extra= 0
	.mask	0x80ff0000,-8
	.fmask	0x00000000,0
	subu	$sp,$sp,72
	sw	$19,44($sp)
	move	$19,$4
	addu	$5,$sp,16
	sw	$31,64($sp)
	sw	$23,60($sp)
	sw	$22,56($sp)
	sw	$21,52($sp)
	sw	$20,48($sp)
	sw	$18,40($sp)
	sw	$17,36($sp)
	sw	$16,32($sp)
	lw	$4,124($19)
	lw	$17,2892($19)
	.set	noreorder
	.set	nomacro
	jal	func_8003AD08
	addu	$4,$4,1
	.set	macro
	.set	reorder

	la	$5,D_800282D8
	.set	noreorder
	.set	nomacro
	jal	func_80069E38
	addu	$4,$sp,16
	.set	macro
	.set	reorder

	addu	$4,$sp,16
	lw	$5,124($19)
	la	$2,D_80083EA4
	sll	$5,$5,9
	.set	noreorder
	.set	nomacro
	jal	func_80069E38
	addu	$5,$5,$2
	.set	macro
	.set	reorder

	addu	$16,$19,132
	move	$4,$16
	addu	$5,$sp,16
	.set	noreorder
	.set	nomacro
	jal	func_8004DA74
	li	$6,0x00000001		# 1
	.set	macro
	.set	reorder

	la	$5,D_800282E8
	lw	$3,4($17)
	li	$2,0x000000a8		# 168
	sw	$16,0($17)
	sh	$2,8($3)
	lw	$2,4($17)
	li	$18,0x00000110		# 272
	sh	$18,10($2)
	lw	$16,2896($19)
	.set	noreorder
	.set	nomacro
	jal	func_80069E78
	addu	$4,$sp,16
	.set	macro
	.set	reorder

	addu	$17,$19,516
	move	$4,$17
	addu	$5,$sp,16
	.set	noreorder
	.set	nomacro
	jal	func_8004DA74
	li	$6,0x00000001		# 1
	.set	macro
	.set	reorder

	lw	$3,4($16)
	li	$2,0x000000a0		# 160
	sw	$17,0($16)
	sh	$2,8($3)
	lw	$2,4($16)
	#nop
	sh	$18,10($2)
	lw	$2,124($19)
	#nop
	sll	$2,$2,7
	lh	$2,D_80083EA4-40($2)
	la	$23,D_80083EA4-48
	beq	$2,$0,$L2
	lw	$5,D_800283A8+8
	lw	$17,2900($19)
	.set	noreorder
	.set	nomacro
	jal	func_80069E78
	addu	$4,$sp,16
	.set	macro
	.set	reorder

	lw	$2,124($19)
	addu	$16,$sp,20
	sll	$2,$2,7
	addu	$2,$2,$23
	lw	$4,52($2)
	.set	noreorder
	.set	nomacro
	jal	func_8003AD08
	move	$5,$16
	.set	macro
	.set	reorder

	addu	$4,$sp,16
	.set	noreorder
	.set	nomacro
	jal	func_80069E38
	move	$5,$16
	.set	macro
	.set	reorder

	lw	$5,D_800283A8+12
	.set	noreorder
	.set	nomacro
	jal	func_80069E38
	addu	$4,$sp,16
	.set	macro
	.set	reorder

	addu	$16,$19,900
	move	$4,$16
	addu	$5,$sp,16
	.set	noreorder
	.set	nomacro
	jal	func_8004DA74
	li	$6,0x00000001		# 1
	.set	macro
	.set	reorder

	lw	$3,4($17)
	li	$2,0x000000b8		# 184
	sw	$16,0($17)
	sh	$2,8($3)
	lw	$3,4($17)
	li	$2,0x00000140		# 320
	sh	$2,10($3)
$L2:
	li	$5,0x0000000a		# 10
	lw	$2,124($19)
	#nop
	sll	$2,$2,7
	addu	$2,$2,$23
	lw	$4,36($2)
	lw	$16,2904($19)
	.set	noreorder
	.set	nomacro
	jal	func_8004E5A0
	addu	$6,$sp,16
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jal	func_8004E69C
	addu	$4,$sp,16
	.set	macro
	.set	reorder

	addu	$17,$19,1284
	move	$4,$17
	addu	$5,$sp,16
	.set	noreorder
	.set	nomacro
	jal	func_8004E298
	li	$6,0x00000001		# 1
	.set	macro
	.set	reorder

	lw	$3,4($16)
	li	$2,0x00000148		# 328
	sw	$17,0($16)
	sh	$2,8($3)
	lw	$2,4($16)
	#nop
	sh	$18,10($2)
	lw	$2,124($19)
	li	$16,-2004353024			# 0x88880000
	sll	$2,$2,7
	addu	$2,$2,$23
	lw	$3,28($2)
	ori	$16,$16,0x8889
	mult	$3,$16
	mfhi	$8
	#nop
	li	$2,-1688731648			# 0x9b580000
	ori	$2,$2,0x3739
	mult	$3,$2
	li	$6,0x000003e7		# 999
	lw	$21,2908($19)
	sra	$4,$3,31
	addu	$2,$8,$3
	sra	$2,$2,5
	subu	$20,$2,$4
	mfhi	$5
	#nop
	#nop
	addu	$3,$5,$3
	sra	$3,$3,17
	subu	$18,$3,$4
	slt	$2,$18,1000
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L3
	sra	$22,$20,31
	.set	macro
	.set	reorder

	move	$6,$18
$L3:
	move	$4,$6
	li	$5,0x00000003		# 3
	.set	noreorder
	.set	nomacro
	jal	func_8004E5A0
	addu	$6,$sp,16
	.set	macro
	.set	reorder

	la	$5,D_800200A4
	.set	noreorder
	.set	nomacro
	jal	func_80069E38
	addu	$4,$sp,16
	.set	macro
	.set	reorder

	mult	$20,$16
	li	$5,0x00000002		# 2
	addu	$17,$sp,20
	move	$6,$17
	sll	$4,$18,4
	subu	$4,$4,$18
	sll	$4,$4,2
	mfhi	$9
	#nop
	#nop
	addu	$16,$9,$20
	sra	$16,$16,5
	subu	$16,$16,$22
	subu	$16,$16,$22
	.set	noreorder
	.set	nomacro
	jal	func_8004E5E8
	subu	$4,$16,$4
	.set	macro
	.set	reorder

	addu	$4,$sp,16
	.set	noreorder
	.set	nomacro
	jal	func_80069E38
	move	$5,$17
	.set	macro
	.set	reorder

	la	$5,D_800200A4
	.set	noreorder
	.set	nomacro
	jal	func_80069E38
	addu	$4,$sp,16
	.set	macro
	.set	reorder

	sll	$4,$16,4
	subu	$4,$4,$16
	sll	$4,$4,2
	subu	$4,$20,$4
	li	$5,0x00000002		# 2
	.set	noreorder
	.set	nomacro
	jal	func_8004E5E8
	move	$6,$17
	.set	macro
	.set	reorder

	addu	$4,$sp,16
	.set	noreorder
	.set	nomacro
	jal	func_80069E38
	move	$5,$17
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jal	func_8004E69C
	addu	$4,$sp,16
	.set	macro
	.set	reorder

	addu	$16,$19,1668
	move	$4,$16
	addu	$5,$sp,16
	.set	noreorder
	.set	nomacro
	jal	func_8004E298
	li	$6,0x00000001		# 1
	.set	macro
	.set	reorder

	lw	$3,4($21)
	li	$2,0x00000150		# 336
	sw	$16,0($21)
	sh	$2,8($3)
	lw	$2,4($21)
	li	$18,0x00000120		# 288
	sh	$18,10($2)
	lw	$2,124($19)
	#nop
	sll	$2,$2,7
	addu	$2,$2,$23
	lw	$3,44($2)
	lw	$17,2912($19)
	sltu	$2,$3,1000
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L4
	li	$4,0x000003e7		# 999
	.set	macro
	.set	reorder

	move	$4,$3
$L4:
	li	$5,0x00000003		# 3
	.set	noreorder
	.set	nomacro
	jal	func_8004E5A0
	addu	$6,$sp,16
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jal	func_8004E69C
	addu	$4,$sp,16
	.set	macro
	.set	reorder

	addu	$16,$19,2052
	move	$4,$16
	addu	$5,$sp,16
	.set	noreorder
	.set	nomacro
	jal	func_8004E298
	li	$6,0x00000001		# 1
	.set	macro
	.set	reorder

	lw	$3,4($17)
	li	$2,0x00000100		# 256
	sw	$16,0($17)
	sh	$2,8($3)
	lw	$2,4($17)
	li	$5,0x00000002		# 2
	sh	$18,10($2)
	lw	$2,124($19)
	#nop
	sll	$2,$2,7
	addu	$2,$2,$23
	lw	$4,40($2)
	lw	$16,2916($19)
	.set	noreorder
	.set	nomacro
	jal	func_8004E5A0
	addu	$6,$sp,16
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jal	func_8004E69C
	addu	$4,$sp,16
	.set	macro
	.set	reorder

	addu	$17,$19,2436
	move	$4,$17
	addu	$5,$sp,16
	.set	noreorder
	.set	nomacro
	jal	func_8004E298
	li	$6,0x00000001		# 1
	.set	macro
	.set	reorder

	move	$4,$0
	li	$7,0x00000034		# 52
	la	$6,D_80027FD4
	move	$5,$19
	lw	$3,4($16)
	li	$2,0x00000188		# 392
	sw	$17,0($16)
	sh	$2,8($3)
	lw	$3,4($16)
	li	$2,0x00000130		# 304
	sh	$2,10($3)
$L5:
	lw	$2,124($19)
	#nop
	sll	$2,$2,7
	addu	$2,$23,$2
	lw	$2,48($2)
	lw	$8,2920($5)
	sra	$2,$2,$4
	andi	$2,$2,0x0001
	beq	$2,$0,$L6
	sll	$7,$7,16
	.set	noreorder
	.set	nomacro
	jal	func_800247B8
	sra	$7,$7,16
	.set	macro
	.set	reorder

	j	$L1
$L6:
	addu	$6,$6,16
	addu	$5,$5,4
	lw	$2,D_80027FD4+32
	lw	$3,4($8)
	addu	$4,$4,1
	sw	$2,0($8)
	sh	$7,8($3)
	lw	$3,4($8)
	li	$2,0x000000b0		# 176
	sh	$2,10($3)
	slt	$2,$4,8
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L5
	addu	$7,$7,16
	.set	macro
	.set	reorder

$L1:
	lw	$31,64($sp)
	lw	$23,60($sp)
	lw	$22,56($sp)
	lw	$21,52($sp)
	lw	$20,48($sp)
	lw	$19,44($sp)
	lw	$18,40($sp)
	lw	$17,36($sp)
	lw	$16,32($sp)
	addu	$sp,$sp,72
	j	$31
	.end	func_80011390
