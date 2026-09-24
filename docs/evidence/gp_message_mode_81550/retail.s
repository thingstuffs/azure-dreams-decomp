8004df8c: addiu $sp, $sp, -0x20
8004df90: move $a1, $a0
8004df94: sw $s0, 0x10($sp)
8004df98: lui $s0, 0x8008
8004df9c: sw $s1, 0x14($sp)
8004dfa0: addiu $s1, $s0, 0x3e18
8004dfa4: addiu $s1, $s1, 1
8004dfa8: move $a0, $s1
8004dfac: addiu $v0, $zero, 8
8004dfb0: sw $ra, 0x1c($sp)
8004dfb4: sw $s2, 0x18($sp)
8004dfb8: jal 0x69e78
8004dfbc: sb $v0, 0x3e18($s0)
8004dfc0: move $a0, $s1
8004dfc4: lui $a1, 0x8007
8004dfc8: jal 0x69e38
8004dfcc: addiu $a1, $a1, 0x1404
8004dfd0: addiu $s0, $s0, 0x3e18
8004dfd4: move $a0, $s0
8004dfd8: jal 0x69eb8
8004dfdc: move $a1, $zero
8004dfe0: move $s1, $v0
8004dfe4: addiu $v0, $zero, 0x19
8004dfe8: sb $v0, ($s1)
8004dfec: addiu $s1, $s1, 1
8004dff0: addiu $v0, $zero, 2
8004dff4: sb $v0, ($s1)
8004dff8: addiu $s1, $s1, 1
8004dffc: addiu $v0, $zero, 0x1a
8004e000: sb $v0, ($s1)
8004e004: addiu $s1, $s1, 1
8004e008: lui $s2, 0x8008
8004e00c: addiu $s2, $s2, 0x1548
8004e010: srl $v0, $s2, 8
8004e014: sb $v0, 1($s1)
8004e018: srl $v0, $s2, 0x10
8004e01c: sb $v0, 2($s1)
8004e020: srl $v0, $s2, 0x18
8004e024: sb $s2, ($s1)
8004e028: sb $v0, 3($s1)
8004e02c: addiu $s1, $s1, 4
8004e030: lui $s2, 0x8008
8004e034: addiu $s2, $s2, 0x154c
8004e038: srl $v0, $s2, 8
8004e03c: sb $v0, 1($s1)
8004e040: srl $v0, $s2, 0x10
8004e044: sb $v0, 2($s1)
8004e048: srl $v0, $s2, 0x18
8004e04c: lui $v1, 0x8007
8004e050: sb $s2, ($s1)
8004e054: sb $v0, 3($s1)
8004e058: lw $v0, 0xbbc($gp)
8004e05c: addiu $v1, $v1, 0x14a4
8004e060: sll $v0, $v0, 2
8004e064: addu $v0, $v0, $v1
8004e068: lw $v0, ($v0)
8004e06c: nop
8004e070: jalr $v0
8004e074: move $a0, $s0
8004e078: lui $v1, 0x2300
8004e07c: ori $v1, $v1, 0x30c
8004e080: lui $v0, 0x2300
8004e084: ori $v0, $v0, 0x40c
8004e088: sw $v1, -4($s2)
8004e08c: sw $v0, 0xbb8($gp)
8004e090: lw $ra, 0x1c($sp)
8004e094: lw $s2, 0x18($sp)
8004e098: lw $s1, 0x14($sp)
8004e09c: lw $s0, 0x10($sp)
8004e0a0: addiu $sp, $sp, 0x20
8004e0a4: jr $ra
8004e0a8: nop
