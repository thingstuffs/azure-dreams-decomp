.set noat
.set noreorder
.text
glabel func_8016DEE8
/* 8016DEE8 e8ffbd27 */ addiu $sp, $sp, -0x18
/* 8016DEEC 1000bfaf */ sw $ra, 0x10($sp)
/* 8016DEF0 6eab050c */ jal func_8016ADB8
/* 8016DEF4 00000000 */ nop 
/* 8016DEF8 1000bf8f */ lw $ra, 0x10($sp)
/* 8016DEFC 1800bd27 */ addiu $sp, $sp, 0x18
/* 8016DF00 0800e003 */ jr $ra
/* 8016DF04 00000000 */ nop 
