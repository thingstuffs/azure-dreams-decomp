func_8004DCA8:
8004DCA8 move     $a1, $a0
8004DCAC bnez     $a1, 0x8004dcbc
8004DCB0 lui      $v0, 0x8008
8004DCB4 lui      $a1, 0x8008
8004DCB8 addiu    $a1, $a1, 0xb68
8004DCBC lw       $a0, 0xbc0($gp)
8004DCC0 addiu    $v0, $v0, 0x3d98
8004DCC4 sll      $v1, $a0, 2
8004DCC8 addiu    $a0, $a0, 1
8004DCCC addu     $v1, $v1, $v0
8004DCD0 sw       $a1, ($v1)
8004DCD4 sw       $a0, 0xbc0($gp)
8004DCD8 jr       $ra
8004DCDC nop
func_8004DD2C:
8004DD2C addiu    $sp, $sp, -0x18
8004DD30 lui      $a1, 0x1508
8004DD34 ori      $a1, $a1, 0x707
8004DD38 sw       $s0, 0x10($sp)
8004DD3C lui      $s0, 0x8008
8004DD40 lw       $v1, 0xbc0($gp)
8004DD44 addiu    $s0, $s0, 0x3d98
8004DD48 sw       $ra, 0x14($sp)
8004DD4C andi     $v1, $v1, 0xf
8004DD50 sll      $v0, $v1, 2
8004DD54 addu     $v0, $v0, $s0
8004DD58 sw       $v1, 0xbc0($gp)
8004DD5C sw       $v1, 0xbc4($gp)
8004DD60 addiu    $v1, $v1, 1
8004DD64 sw       $a1, ($v0)
8004DD68 sw       $v1, 0xbc0($gp)
8004DD6C jal      0x8004dca8
8004DD70 nop
8004DD74 addiu    $v0, $zero, 0x23
8004DD78 lw       $a1, 0xbc0($gp)
8004DD7C lw       $a0, 0xbc4($gp)
8004DD80 sll      $v1, $a1, 2
8004DD84 addiu    $a1, $a1, 1
8004DD88 sll      $a0, $a0, 2
8004DD8C addu     $v1, $v1, $s0
8004DD90 sw       $v0, ($v1)
8004DD94 sw       $a1, 0xbc0($gp)
8004DD98 jal      0x8003528c
8004DD9C addu     $a0, $a0, $s0
8004DDA0 lw       $ra, 0x14($sp)
8004DDA4 lw       $s0, 0x10($sp)
8004DDA8 addiu    $sp, $sp, 0x18
8004DDAC jr       $ra
8004DDB0 nop
func_8004DDB4:
8004DDB4 sw       $zero, 0xbc0($gp)
8004DDB8 sw       $zero, 0xbc4($gp)
8004DDBC jr       $ra
8004DDC0 nop
func_8004DDE4:
8004DDE4 addiu    $sp, $sp, -0x18
8004DDE8 lui      $a1, 0x1508
8004DDEC ori      $a1, $a1, 0x707
8004DDF0 sw       $s0, 0x10($sp)
8004DDF4 lui      $s0, 0x8008
8004DDF8 lw       $v1, 0xbc0($gp)
8004DDFC addiu    $s0, $s0, 0x3d98
8004DE00 sw       $ra, 0x14($sp)
8004DE04 andi     $v1, $v1, 0xf
8004DE08 sll      $v0, $v1, 2
8004DE0C addu     $v0, $v0, $s0
8004DE10 sw       $v1, 0xbc0($gp)
8004DE14 sw       $v1, 0xbc4($gp)
8004DE18 addiu    $v1, $v1, 1
8004DE1C sw       $a1, ($v0)
8004DE20 sw       $v1, 0xbc0($gp)
8004DE24 jal      0x8004dca8
8004DE28 nop
8004DE2C lui      $v1, 2
8004DE30 ori      $v1, $v1, 0xc11
8004DE34 lw       $a1, 0xbc0($gp)
8004DE38 lw       $a0, 0xbc4($gp)
8004DE3C sll      $v0, $a1, 2
8004DE40 addiu    $a1, $a1, 1
8004DE44 sll      $a0, $a0, 2
8004DE48 addu     $v0, $v0, $s0
8004DE4C sw       $v1, ($v0)
8004DE50 sll      $v0, $a1, 2
8004DE54 addu     $v0, $v0, $s0
8004DE58 addiu    $v1, $zero, 1
8004DE5C sw       $a1, 0xbc0($gp)
8004DE60 addiu    $a1, $a1, 1
8004DE64 sw       $v1, ($v0)
8004DE68 sw       $a1, 0xbc0($gp)
8004DE6C jal      0x8003528c
8004DE70 addu     $a0, $a0, $s0
8004DE74 lw       $ra, 0x14($sp)
8004DE78 lw       $s0, 0x10($sp)
8004DE7C addiu    $sp, $sp, 0x18
8004DE80 jr       $ra
8004DE84 nop
func_8004E130:
8004E130 addiu    $sp, $sp, -0x18
8004E134 lui      $v0, 0x8008
8004E138 lw       $v1, 0xbc0($gp)
8004E13C addiu    $v0, $v0, 0x3d98
8004E140 sw       $ra, 0x10($sp)
8004E144 andi     $v1, $v1, 0xf
8004E148 sll      $a0, $v1, 2
8004E14C addu     $a0, $a0, $v0
8004E150 addiu    $v0, $zero, 1
8004E154 sw       $v1, 0xbc0($gp)
8004E158 sw       $v1, 0xbc4($gp)
8004E15C addiu    $v1, $v1, 1
8004E160 sw       $v0, ($a0)
8004E164 sw       $v1, 0xbc0($gp)
8004E168 jal      0x8003528c
8004E16C nop
8004E170 jal      0x800352b4
8004E174 nop
8004E178 lw       $ra, 0x10($sp)
8004E17C addiu    $sp, $sp, 0x18
8004E180 jr       $ra
8004E184 nop
