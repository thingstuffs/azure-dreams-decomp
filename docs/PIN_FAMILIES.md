# Pin families (tools/pin_probe.py --strip)

Rows probed: 1918.  Every ASM_* site of the row erased at once; the scorer's aligned distance and the shape of the residue below.

- **strip-exact (pin-free for free): 0 rows**, 0 B, 0 pins

| strip damage | rows |
|---|---:|
| 1-3 | 112 |
| 4-8 | 279 |
| 9-20 | 471 |
| 21+ | 1045 |
| error | 11 |

| residue shape | rows | rows at damage<=8 |
|---|---:|---:|
| mixed | 1391 | 116 |
| ? | 284 | 0 |
| none | 123 | 19 |
| reg_perm | 57 | 44 |
| order | 35 | 26 |
| reg_local | 28 | 14 |

## The near band: 586 rows within 12 words of pin-free (211,956 B, 1150 pins)

A row here is byte-exact today and one C shape away from carrying no scaffolding at
all.  The class is the scorer's residue class for the row with every pin erased, and it
names the mechanism, so a lane that solves one row of a class usually solves its
neighbours.  `tools/pin_lane.py --band N` cuts this table into lane packs.

| class | rows | pins | bytes | what the residue says |
|---|---:|---:|---:|---|
| broad | 117 | 233 | 37,692 | no single named signal; read the row's regions view |
| length-drift | 85 | 198 | 26,896 | retail keeps or drops a word gcc does not |
| reg-rename | 79 | 112 | 34,384 | same instructions, two registers swapped: the variable map, not the register |
| reorder-only | 54 | 102 | 21,180 | same instructions, one moved by the scheduler |
| code-motion | 41 | 84 | 11,284 | a statement crossed a call or a branch |
| slus-diff | 36 | 53 | 24,828 | the SLUS object differs; check the row's TU, not its C |
| addressing | 31 | 58 | 8,884 | %hi/%lo against base+offset: how the address is formed |
| li-expansion | 31 | 63 | 9,344 | lui;ori against lui;addiu: an integer literal where retail has a symbol |
| const-remat | 30 | 73 | 14,788 | retail keeps a constant in a register that gcc recomputes |
| slot-rotation | 24 | 46 | 6,232 | a different instruction fills a delay slot |
| block-order | 15 | 25 | 3,344 | the basic blocks are laid out in another order |
| hold-set | 12 | 20 | 1,952 | a different callee-saved set / frame layout |
| polarity | 12 | 27 | 4,704 | a branch is inverted |
| dead-code-retention | 11 | 36 | 3,692 | retail keeps a computation gcc deletes |
| delay-slot | 8 | 20 | 2,752 | retail fills a slot this build leaves as nop |

### The closest rows (strip damage 1-2)

| row | size | cfg | pins | damage | class |
|---|---:|---|---:|---:|---|
| town/func_80875124 | 40 | 2.7.2 | 1 | 1 | li-expansion |
| town/func_8088116C | 72 | 2.7.2 | 1 | 1 | li-expansion |
| town/func_8087FD58 | 76 | 2.7.2 | 1 | 1 | li-expansion |
| dungeon/func_8132C638 | 76 | 2.8.1-G0 | 2 | 1 | broad |
| town/func_8087FE98 | 88 | 2.7.2 | 1 | 1 | li-expansion |
| town/func_808813CC | 88 | 2.7.2-G0 | 1 | 1 | li-expansion |
| town/func_800B9B58 | 92 | 2.91.66 | 1 | 1 | length-drift |
| town/func_806F1A40 | 104 | 2.7.2-cdk-G0 | 2 | 1 | delay-slot |
| town/func_8051EF40 | 168 | 2.8.1 | 1 | 1 | reg-rename |
| dungeon/func_800A7828 | 208 | 2.7.2-cdk-G0 | 1 | 1 | broad |
| town/func_804708B4 | 232 | 2.7.2-cdk-G0 | 1 | 1 | broad |
| slus/w_80042A80 | 232 | 2.7.2-cdk | 1 | 1 | slus-diff |
| main/func_80013B18 | 232 | 2.7.2-G0 | 2 | 1 | broad |
| town/func_8032E8C0 | 260 | 2.6.3-G0 | 1 | 1 | broad |
| slus/w_8005D064 | 296 | 2.7.2 -G0 | 1 | 1 | slus-diff |
| dungeon/func_80DE6AAC | 436 | 2.7.2-cdk-G0 | 2 | 1 | delay-slot |
| slus/w_80059E94 | 480 | 2.8.1 -fno-schedule-insns | 1 | 1 | slus-diff |
| dungeon/func_80FB2B14 | 512 | 2.8.1-G0 | 2 | 1 | reg-rename |
| dungeon/func_8009D658 | 552 | 2.7.2-cdk-G0 | 2 | 1 | const-remat |
| dungeon/func_8196BA5C | 736 | 2.7.2-cdk-G0 | 2 | 1 | delay-slot |
| dungeon/func_807AEF8C | 832 | 2.7.2-cdk-G0 | 3 | 1 | delay-slot |
| dungeon/func_800976BC | 1020 | 2.8.1-G0 | 5 | 1 | reg-rename |
| dungeon/func_809CAE20 | 1028 | 2.7.2-cdk-G0 | 1 | 1 | reg-rename |
| dungeon/func_800A1A94 | 64 | 2.7.2 | 1 | 2 | broad |
| dungeon/func_800AF9C8 | 64 | 2.7.2-cdk-G0 | 1 | 2 | broad |
| dungeon/func_800A22D8 | 68 | 2.8.1 | 2 | 2 | delay-slot |
| dungeon/func_8009A590 | 80 | 2.7.2-cdk | 1 | 2 | broad |
| dungeon/func_80CC2614 | 88 | 2.7.2 | 3 | 2 | reg-rename |
| main/func_8001F2F4 | 100 | 2.7.2-cdk | 1 | 2 | reg-rename |
| town/func_800A2F44 | 100 | 2.95.2-G0 | 1 | 2 | reg-rename |
| town/func_800C8810 | 108 | 2.8.1-G0 | 2 | 2 | reorder-only |
| town/func_805D3700 | 108 | 2.7.2-cdk-G0 | 1 | 2 | delay-slot |
| town/func_800995F8 | 112 | 2.7.2-cdk-G0 | 3 | 2 | broad |
| slus/w_800405E8 | 132 | 2.7.2 | 1 | 2 | slus-diff |
| dungeon/func_800A0D20 | 136 | 2.8.1-G0 | 3 | 2 | reg-rename |
| dungeon/func_800B4C24 | 144 | 2.7.2-cdk-G0 | 1 | 2 | broad |
| town/func_800CEC24 | 152 | 2.7.2-cdk-G0 | 1 | 2 | reg-rename |
| town/func_806973CC | 168 | 2.8.1-G0 | 2 | 2 | delay-slot |
| dungeon/func_800BAA20 | 176 | 2.7.2 | 3 | 2 | broad |
| dungeon/func_81338144 | 188 | 2.8.1-G0 | 3 | 2 | code-motion |
