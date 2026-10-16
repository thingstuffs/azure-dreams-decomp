# Pin families (tools/pin_probe.py --strip)

Rows probed: 1706.  Every ASM_* site of the row erased at once; the scorer's aligned distance and the shape of the residue below.

- **strip-exact (pin-free for free): 0 rows**, 0 B, 0 pins

| strip damage | rows |
|---|---:|
| 1-3 | 89 |
| 4-8 | 206 |
| 9-20 | 409 |
| 21+ | 996 |
| error | 6 |

| residue shape | rows | rows at damage<=8 |
|---|---:|---:|
| mixed | 1267 | 77 |
| ? | 252 | 0 |
| none | 95 | 9 |
| reg_perm | 40 | 30 |
| order | 29 | 20 |
| reg_local | 23 | 11 |

## The near band: 458 rows within 12 words of pin-free (161,732 B, 926 pins)

A row here is byte-exact today and one C shape away from carrying no scaffolding at
all.  The class is the scorer's residue class for the row with every pin erased, and it
names the mechanism, so a lane that solves one row of a class usually solves its
neighbours.  `tools/pin_lane.py --band N` cuts this table into lane packs.

| class | rows | pins | bytes | what the residue says |
|---|---:|---:|---:|---|
| broad | 97 | 195 | 32,748 | no single named signal; read the row's regions view |
| length-drift | 72 | 176 | 21,276 | retail keeps or drops a word gcc does not |
| reg-rename | 59 | 83 | 29,776 | same instructions, two registers swapped: the variable map, not the register |
| reorder-only | 42 | 84 | 15,356 | same instructions, one moved by the scheduler |
| addressing | 28 | 55 | 8,492 | %hi/%lo against base+offset: how the address is formed |
| code-motion | 26 | 56 | 6,536 | a statement crossed a call or a branch |
| li-expansion | 25 | 60 | 7,600 | lui;ori against lui;addiu: an integer literal where retail has a symbol |
| slus-diff | 24 | 32 | 14,984 | the SLUS object differs; check the row's TU, not its C |
| const-remat | 19 | 41 | 7,188 | retail keeps a constant in a register that gcc recomputes |
| slot-rotation | 18 | 37 | 4,544 | a different instruction fills a delay slot |
| block-order | 12 | 18 | 2,812 | the basic blocks are laid out in another order |
| polarity | 10 | 24 | 3,128 | a branch is inverted |
| hold-set | 10 | 17 | 1,720 | a different callee-saved set / frame layout |
| dead-code-retention | 8 | 28 | 2,820 | retail keeps a computation gcc deletes |
| delay-slot | 8 | 20 | 2,752 | retail fills a slot this build leaves as nop |

### The closest rows (strip damage 1-2)

| row | size | cfg | pins | damage | class |
|---|---:|---|---:|---:|---|
| town/func_80875124 | 40 | 2.7.2 | 1 | 1 | li-expansion |
| dungeon/func_81811EC0 | 68 | 2.7.2-G0 | 2 | 1 | reg-rename |
| town/func_8088116C | 72 | 2.7.2 | 2 | 1 | li-expansion |
| town/func_8087FD58 | 76 | 2.7.2 | 2 | 1 | li-expansion |
| town/func_8087FE98 | 88 | 2.7.2 | 1 | 1 | li-expansion |
| town/func_808813CC | 88 | 2.7.2-G0 | 1 | 1 | li-expansion |
| town/func_800B9B58 | 92 | 2.91.66 | 1 | 1 | length-drift |
| town/func_806F1A40 | 104 | 2.7.2-cdk-G0 | 2 | 1 | delay-slot |
| dungeon/func_800A7828 | 208 | 2.7.2-cdk-G0 | 1 | 1 | broad |
| slus/w_80042A80 | 232 | 2.7.2-cdk | 1 | 1 | slus-diff |
| town/func_8032E8C0 | 260 | 2.6.3-G0 | 1 | 1 | broad |
| dungeon/func_80DE6AAC | 436 | 2.7.2-cdk-G0 | 2 | 1 | delay-slot |
| slus/w_80059E94 | 480 | 2.8.1 -fno-schedule-insns | 1 | 1 | slus-diff |
| town/func_8008EFF8 | 556 | 2.7.2-cdk-G0 | 1 | 1 | reg-rename |
| dungeon/func_8196BA5C | 736 | 2.7.2-cdk-G0 | 2 | 1 | delay-slot |
| dungeon/func_807AEF8C | 832 | 2.7.2-cdk-G0 | 3 | 1 | delay-slot |
| dungeon/func_809CAE20 | 1028 | 2.7.2-cdk-G0 | 1 | 1 | reg-rename |
| dungeon/func_800A1A94 | 64 | 2.7.2 | 1 | 2 | broad |
| dungeon/func_800A22D8 | 68 | 2.8.1 | 2 | 2 | delay-slot |
| dungeon/func_80CC2614 | 88 | 2.7.2 | 3 | 2 | reg-rename |
| main/func_8001F2F4 | 100 | 2.7.2-cdk | 1 | 2 | reg-rename |
| town/func_800A2F44 | 100 | 2.95.2-G0 | 1 | 2 | reg-rename |
| town/func_800C8810 | 108 | 2.8.1-G0 | 2 | 2 | reorder-only |
| town/func_8032F4D8 | 108 | 2.7.2-cdk-G0 | 1 | 2 | reorder-only |
| town/func_805D3700 | 108 | 2.7.2-cdk-G0 | 1 | 2 | delay-slot |
| town/func_800995F8 | 112 | 2.7.2-cdk-G0 | 1 | 2 | broad |
| slus/w_800565D8 | 124 | 2.7.2 | 1 | 2 | slus-diff |
| slus/w_800405E8 | 132 | 2.7.2 | 1 | 2 | slus-diff |
| dungeon/func_800A0D20 | 136 | 2.8.1-G0 | 3 | 2 | reg-rename |
| town/func_800CEC24 | 152 | 2.7.2-cdk-G0 | 1 | 2 | reg-rename |
| town/func_806973CC | 168 | 2.8.1-G0 | 2 | 2 | delay-slot |
| dungeon/func_800BAA20 | 176 | 2.7.2 | 3 | 2 | broad |
| dungeon/func_81338144 | 188 | 2.8.1-G0 | 3 | 2 | code-motion |
| dungeon/func_813292EC | 192 | 2.8.1-G0 | 1 | 2 | reg-rename |
| dungeon/func_818C2E40 | 208 | 2.7.2-cdk-G0 | 3 | 2 | broad |
| dungeon/func_800C96AC | 232 | 2.7.2-cdk-G0 | 1 | 2 | broad |
| town/func_800B63B8 | 236 | 2.7.2-cdk-G0 | 2 | 2 | reg-rename |
| town/func_800B0BC4 | 240 | 2.8.1-G0 | 1 | 2 | code-motion |
| dungeon/func_800B4204 | 276 | 2.8.1-G0 | 1 | 2 | reorder-only |
| dungeon/func_81881CC4 | 280 | 2.8.1 | 1 | 2 | reorder-only |
