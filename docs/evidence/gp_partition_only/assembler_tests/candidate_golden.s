
.file	1 "func_80011390.c"




gcc2_compiled.:
__gnu_compiled_c:
.include "include/labels.inc"

.text
.align	2
.globl	func_80011390


.text
.text
.ent	func_80011390
.set	noreorder
func_80011390:
.frame	$sp,72,$31		# vars= 16, regs= 9/0, args= 16, extra= 0
.mask	0x80ff0000,-8
.fmask	0x00000000,0
subu	$sp,$sp,72
sw	$19,44($sp)
addu	$19,$4,$zero
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
#nop # DEBUG: 'lw	$17,2892($19)' does not load from $4
lw	$17,2892($19)
#nop # DEBUG: 'jal	func_8003AD08' does not load from $17
jal	func_8003AD08
addu	$4,$4,1

la	$5,D_800282D8
jal	func_80069E38
addu	$4,$sp,16

addu	$4,$sp,16
lw	$5,124($19)
#nop # DEBUG: 'la	$2,D_80083EA4' does not load from $5
la	$2,D_80083EA4
sll	$5,$5,9
jal	func_80069E38
addu	$5,$5,$2

addu	$16,$19,132
addu	$4,$16,$zero
addu	$5,$sp,16
jal	func_8004DA74
ori	$6,$zero,1

la	$5,D_800282E8
lw	$3,4($17)
#nop # DEBUG: 'li	$2,0x000000a8		# 168' does not load from $3
ori	$2,$zero,168
sw	$16,0($17)
sh	$2,8($3)
lw	$2,4($17)
#nop # DEBUG: 'li	$18,0x00000110		# 272' does not load from $2
ori	$18,$zero,272
sh	$18,10($2)
lw	$16,2896($19)
#nop # DEBUG: 'jal	func_80069E78' does not load from $16
jal	func_80069E78
addu	$4,$sp,16

addu	$17,$19,516
addu	$4,$17,$zero
addu	$5,$sp,16
jal	func_8004DA74
ori	$6,$zero,1

lw	$3,4($16)
#nop # DEBUG: 'li	$2,0x000000a0		# 160' does not load from $3
ori	$2,$zero,160
sw	$17,0($16)
sh	$2,8($3)
lw	$2,4($16)
nop # DEBUG: Reuse of '$2'. 'sh	$18,10($2)' does not use $at
sh	$18,10($2)
lw	$2,124($19)
nop # DEBUG: Reuse of '$2'. 'sll	$2,$2,7' does not use $at
sll	$2,$2,7
# EXPAND_AT START
.set	noat
lui	$at,%hi(D_80083EA4-40)
addu	$at,$at,$2
lh	$2,%lo(D_80083EA4-40)($at)
.set	at
# EXPAND_AT END
#nop # DEBUG: 'la	$23,D_80083EA4-48' does not load from $2
la	$23,D_80083EA4-48
beq	$2,$0,$L2
nop  # DEBUG: branch/jump
lw	$5,D_800283A8+8
#nop # DEBUG: 'lw	$17,2900($19)' does not load from $5
lw	$17,2900($19)
#nop # DEBUG: 'jal	func_80069E78' does not load from $17
jal	func_80069E78
addu	$4,$sp,16

lw	$2,124($19)
#nop # DEBUG: 'addu	$16,$sp,20' does not load from $2
addu	$16,$sp,20
sll	$2,$2,7
addu	$2,$2,$23
lw	$4,52($2)
#nop # DEBUG: 'jal	func_8003AD08' does not load from $4
jal	func_8003AD08
addu	$5,$16,$zero

addu	$4,$sp,16
jal	func_80069E38
addu	$5,$16,$zero

lw	$5,D_800283A8+12
#nop # DEBUG: 'jal	func_80069E38' does not load from $5
jal	func_80069E38
addu	$4,$sp,16

addu	$16,$19,900
addu	$4,$16,$zero
addu	$5,$sp,16
jal	func_8004DA74
ori	$6,$zero,1

lw	$3,4($17)
#nop # DEBUG: 'li	$2,0x000000b8		# 184' does not load from $3
ori	$2,$zero,184
sw	$16,0($17)
sh	$2,8($3)
lw	$3,4($17)
#nop # DEBUG: 'li	$2,0x00000140		# 320' does not load from $3
ori	$2,$zero,320
sh	$2,10($3)
$L2:
ori	$5,$zero,10
lw	$2,124($19)
nop # DEBUG: Reuse of '$2'. 'sll	$2,$2,7' does not use $at
sll	$2,$2,7
addu	$2,$2,$23
lw	$4,36($2)
#nop # DEBUG: 'lw	$16,2904($19)' does not load from $4
lw	$16,2904($19)
#nop # DEBUG: 'jal	func_8004E5A0' does not load from $16
jal	func_8004E5A0
addu	$6,$sp,16

jal	func_8004E69C
addu	$4,$sp,16

addu	$17,$19,1284
addu	$4,$17,$zero
addu	$5,$sp,16
jal	func_8004E298
ori	$6,$zero,1

lw	$3,4($16)
#nop # DEBUG: 'li	$2,0x00000148		# 328' does not load from $3
ori	$2,$zero,328
sw	$17,0($16)
sh	$2,8($3)
lw	$2,4($16)
nop # DEBUG: Reuse of '$2'. 'sh	$18,10($2)' does not use $at
sh	$18,10($2)
lw	$2,124($19)
#nop # DEBUG: 'li	$16,-2004353024			# 0x88880000' does not load from $2
lui	$16,(-2004353024 >> 16) & 0xFFFF
sll	$2,$2,7
addu	$2,$2,$23
lw	$3,28($2)
#nop # DEBUG: 'ori	$16,$16,0x8889' does not load from $3
ori	$16,$16,0x8889
mult	$3,$16
mfhi	$8
lui	$2,(-1688731648 >> 16) & 0xFFFF
ori	$2,$2,0x3739
mult	$3,$2
ori	$6,$zero,999
lw	$21,2908($19)
#nop # DEBUG: 'sra	$4,$3,31' does not load from $21
sra	$4,$3,31
addu	$2,$8,$3
sra	$2,$2,5
subu	$20,$2,$4
mfhi	$5
addu	$3,$5,$3
sra	$3,$3,17
subu	$18,$3,$4
slt	$2,$18,1000
beq	$2,$0,$L3
sra	$22,$20,31

addu	$6,$18,$zero
$L3:
addu	$4,$6,$zero
ori	$5,$zero,3
jal	func_8004E5A0
addu	$6,$sp,16

la	$5,D_800200A4
jal	func_80069E38
addu	$4,$sp,16

mult	$20,$16
ori	$5,$zero,2
addu	$17,$sp,20
addu	$6,$17,$zero
sll	$4,$18,4
subu	$4,$4,$18
sll	$4,$4,2
mfhi	$9
addu	$16,$9,$20
sra	$16,$16,5
subu	$16,$16,$22
subu	$16,$16,$22
jal	func_8004E5E8
subu	$4,$16,$4

addu	$4,$sp,16
jal	func_80069E38
addu	$5,$17,$zero

la	$5,D_800200A4
jal	func_80069E38
addu	$4,$sp,16

sll	$4,$16,4
subu	$4,$4,$16
sll	$4,$4,2
subu	$4,$20,$4
ori	$5,$zero,2
jal	func_8004E5E8
addu	$6,$17,$zero

addu	$4,$sp,16
jal	func_80069E38
addu	$5,$17,$zero

jal	func_8004E69C
addu	$4,$sp,16

addu	$16,$19,1668
addu	$4,$16,$zero
addu	$5,$sp,16
jal	func_8004E298
ori	$6,$zero,1

lw	$3,4($21)
#nop # DEBUG: 'li	$2,0x00000150		# 336' does not load from $3
ori	$2,$zero,336
sw	$16,0($21)
sh	$2,8($3)
lw	$2,4($21)
#nop # DEBUG: 'li	$18,0x00000120		# 288' does not load from $2
ori	$18,$zero,288
sh	$18,10($2)
lw	$2,124($19)
nop # DEBUG: Reuse of '$2'. 'sll	$2,$2,7' does not use $at
sll	$2,$2,7
addu	$2,$2,$23
lw	$3,44($2)
#nop # DEBUG: 'lw	$17,2912($19)' does not load from $3
lw	$17,2912($19)
#nop # DEBUG: 'sltu	$2,$3,1000' does not load from $17
sltu	$2,$3,1000
beq	$2,$0,$L4
ori	$4,$zero,999

addu	$4,$3,$zero
$L4:
ori	$5,$zero,3
jal	func_8004E5A0
addu	$6,$sp,16

jal	func_8004E69C
addu	$4,$sp,16

addu	$16,$19,2052
addu	$4,$16,$zero
addu	$5,$sp,16
jal	func_8004E298
ori	$6,$zero,1

lw	$3,4($17)
#nop # DEBUG: 'li	$2,0x00000100		# 256' does not load from $3
ori	$2,$zero,256
sw	$16,0($17)
sh	$2,8($3)
lw	$2,4($17)
#nop # DEBUG: 'li	$5,0x00000002		# 2' does not load from $2
ori	$5,$zero,2
sh	$18,10($2)
lw	$2,124($19)
nop # DEBUG: Reuse of '$2'. 'sll	$2,$2,7' does not use $at
sll	$2,$2,7
addu	$2,$2,$23
lw	$4,40($2)
#nop # DEBUG: 'lw	$16,2916($19)' does not load from $4
lw	$16,2916($19)
#nop # DEBUG: 'jal	func_8004E5A0' does not load from $16
jal	func_8004E5A0
addu	$6,$sp,16

jal	func_8004E69C
addu	$4,$sp,16

addu	$17,$19,2436
addu	$4,$17,$zero
addu	$5,$sp,16
jal	func_8004E298
ori	$6,$zero,1

addu	$4,$0,$zero
ori	$7,$zero,52
la	$6,D_80027FD4
addu	$5,$19,$zero
lw	$3,4($16)
#nop # DEBUG: 'li	$2,0x00000188		# 392' does not load from $3
ori	$2,$zero,392
sw	$17,0($16)
sh	$2,8($3)
lw	$3,4($16)
#nop # DEBUG: 'li	$2,0x00000130		# 304' does not load from $3
ori	$2,$zero,304
sh	$2,10($3)
$L5:
lw	$2,124($19)
nop # DEBUG: Reuse of '$2'. 'sll	$2,$2,7' does not use $at
sll	$2,$2,7
addu	$2,$23,$2
lw	$2,48($2)
#nop # DEBUG: 'lw	$8,2920($5)' does not load from $2
lw	$8,2920($5)
#nop # DEBUG: 'sra	$2,$2,$4' does not load from $8
sra	$2,$2,$4
andi	$2,$2,0x0001
beq	$2,$0,$L6
nop  # DEBUG: branch/jump
sll	$7,$7,16
j	func_800247B8	# maspsx: arg sibcall jal->j (LEAD 22)
sra	$7,$7,16

# j	$L1	# maspsx: LEAD 22 dead j-to-epilogue removed
# nop  # DEBUG: branch/jump	# maspsx: LEAD 22 dead j-to-epilogue removed
$L6:
addu	$6,$6,16
addu	$5,$5,4
lw	$2,D_80027FD4+32
#nop # DEBUG: 'lw	$3,4($8)' does not load from $2
lw	$3,4($8)
#nop # DEBUG: 'addu	$4,$4,1' does not load from $3
addu	$4,$4,1
sw	$2,0($8)
sh	$7,8($3)
lw	$3,4($8)
#nop # DEBUG: 'li	$2,0x000000b0		# 176' does not load from $3
ori	$2,$zero,176
sh	$2,10($3)
slt	$2,$4,8
bne	$2,$0,$L5
addu	$7,$7,16

$L1:
lw	$31,64($sp)
#nop # DEBUG: 'lw	$23,60($sp)' does not load from $31
lw	$23,60($sp)
#nop # DEBUG: 'lw	$22,56($sp)' does not load from $23
lw	$22,56($sp)
#nop # DEBUG: 'lw	$21,52($sp)' does not load from $22
lw	$21,52($sp)
#nop # DEBUG: 'lw	$20,48($sp)' does not load from $21
lw	$20,48($sp)
#nop # DEBUG: 'lw	$19,44($sp)' does not load from $20
lw	$19,44($sp)
#nop # DEBUG: 'lw	$18,40($sp)' does not load from $19
lw	$18,40($sp)
#nop # DEBUG: 'lw	$17,36($sp)' does not load from $18
lw	$17,36($sp)
#nop # DEBUG: 'lw	$16,32($sp)' does not load from $17
lw	$16,32($sp)
#nop # DEBUG: 'addu	$sp,$sp,72' does not load from $16
addu	$sp,$sp,72
j	$31
nop  # DEBUG: branch/jump
.end	func_80011390
