.set noat
.set noreorder
.text
glabel func_800BD074
/* 800BD074 e8ffbd27 */ addiu $sp, $sp, -0x18
/* 800BD078 0880023c */ lui $v0, 0x8008
/* 800BD07C 6b2e4390 */ lbu $v1, 0x2e6b($v0)
/* 800BD080 11000224 */ addiu $v0, $zero, 0x11
/* 800BD084 1400bfaf */ sw $ra, 0x14($sp)
/* 800BD088 1a006214 */ bne $v1, $v0, .L800BD0F4
/* 800BD08C 1000b0af */ sw $s0, 0x10($sp)
/* 800BD090 0180103c */ lui $s0, 0x8001
/* 800BD094 9020028e */ lw $v0, 0x2090($s0)
/* 800BD098 00000000 */ nop 
/* 800BD09C 16004014 */ bnez $v0, .L800BD0F8
/* 800BD0A0 06000424 */ addiu $a0, $zero, 6
/* 800BD0A4 0880023c */ lui $v0, 0x8008
/* 800BD0A8 6c144384 */ lh $v1, 0x146c($v0)
/* 800BD0AC 28000224 */ addiu $v0, $zero, 0x28
/* 800BD0B0 12006214 */ bne $v1, $v0, .L800BD0FC
/* 800BD0B4 0e80053c */ lui $a1, 0x800e
/* 800BD0B8 f0ce000c */ jal func_80033BC0
/* 800BD0BC a2000424 */ addiu $a0, $zero, 0xa2
/* 800BD0C0 0d004014 */ bnez $v0, .L800BD0F8
/* 800BD0C4 06000424 */ addiu $a0, $zero, 6
/* 800BD0C8 8c20028e */ lw $v0, 0x208c($s0)
/* 800BD0CC 00000000 */ nop 
/* 800BD0D0 0a004014 */ bnez $v0, .L800BD0FC
/* 800BD0D4 0e80053c */ lui $a1, 0x800e
/* 800BD0D8 21000424 */ addiu $a0, $zero, 0x21
/* 800BD0DC 01000224 */ addiu $v0, $zero, 1
/* 800BD0E0 a802010c */ jal func_80040AA0
/* 800BD0E4 8c2002ae */ sw $v0, 0x208c($s0)
/* 800BD0E8 0e80023c */ lui $v0, 0x800e
/* 800BD0EC 44f40208 */ j .L800BD110
/* 800BD0F0 4ecf40a0 */ sb $zero, -0x30b2($v0)
.L800BD0F4:
/* 800BD0F4 06000424 */ addiu $a0, $zero, 6
.L800BD0F8:
/* 800BD0F8 0e80053c */ lui $a1, 0x800e
.L800BD0FC:
/* 800BD0FC d4f3a524 */ addiu $a1, $a1, -0xc2c
/* 800BD100 3ff9000c */ jal func_8003E4FC
/* 800BD104 21300000 */ move $a2, $zero
/* 800BD108 c8fc000c */ jal func_8003F320
/* 800BD10C 00000000 */ nop 
.L800BD110:
/* 800BD110 1400bf8f */ lw $ra, 0x14($sp)
/* 800BD114 1000b08f */ lw $s0, 0x10($sp)
/* 800BD118 1800bd27 */ addiu $sp, $sp, 0x18
/* 800BD11C 0800e003 */ jr $ra
/* 800BD120 00000000 */ nop 
