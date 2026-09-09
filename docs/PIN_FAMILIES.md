# Pin families (tools/pin_probe.py --strip)

Rows probed: 1962.  Every ASM_* site of the row erased at once; the scorer's aligned distance and the shape of the residue below.

- **strip-exact (pin-free for free): 6 rows**, 1,696 B, 12 pins

| strip damage | rows |
|---|---:|
| 0 | 6 |
| 1-3 | 134 |
| 4-8 | 295 |
| 9-20 | 471 |
| 21+ | 1045 |
| error | 11 |

| residue shape | rows | rows at damage<=8 |
|---|---:|---:|
| mixed | 1397 | 122 |
| ? | 308 | 0 |
| none | 123 | 19 |
| reg_perm | 60 | 47 |
| order | 39 | 30 |
| reg_local | 29 | 15 |

## The near band: 624 rows within 12 words of pin-free (218,804 B, 1199 pins)

A row here is byte-exact today and one C shape away from carrying no scaffolding at
all.  The class is the scorer's residue class for the row with every pin erased, and it
names the mechanism, so a lane that solves one row of a class usually solves its
neighbours.  `tools/pin_lane.py --band N` cuts this table into lane packs.

| class | rows | pins | bytes | what the residue says |
|---|---:|---:|---:|---|
| broad | 127 | 244 | 39,268 | no single named signal; read the row's regions view |
| length-drift | 94 | 210 | 28,344 | retail keeps or drops a word gcc does not |
| reg-rename | 85 | 121 | 35,768 | same instructions, two registers swapped: the variable map, not the register |
| reorder-only | 62 | 111 | 22,568 | same instructions, one moved by the scheduler |
| code-motion | 41 | 84 | 11,284 | a statement crossed a call or a branch |
| slus-diff | 36 | 53 | 24,828 | the SLUS object differs; check the row's TU, not its C |
| addressing | 33 | 62 | 9,280 | %hi/%lo against base+offset: how the address is formed |
| li-expansion | 33 | 66 | 9,688 | lui;ori against lui;addiu: an integer literal where retail has a symbol |
| const-remat | 30 | 73 | 14,788 | retail keeps a constant in a register that gcc recomputes |
| slot-rotation | 24 | 46 | 6,232 | a different instruction fills a delay slot |
| block-order | 16 | 26 | 3,656 | the basic blocks are laid out in another order |
| hold-set | 12 | 20 | 1,952 | a different callee-saved set / frame layout |
| polarity | 12 | 27 | 4,704 | a branch is inverted |
| dead-code-retention | 11 | 36 | 3,692 | retail keeps a computation gcc deletes |
| delay-slot | 8 | 20 | 2,752 | retail fills a slot this build leaves as nop |

### The closest rows (strip damage 1-2)

| row | size | cfg | pins | damage | class |
|---|---:|---|---:|---:|---|
| town/func_80875124 | 40 | 2.7.2 | 1 | 1 | li-expansion |
| town/func_8096B30C | 68 | 2.8.1-G0 | 2 | 1 | broad |
| town/func_8088116C | 72 | 2.7.2 | 1 | 1 | li-expansion |
| town/func_8087FD58 | 76 | 2.7.2 | 1 | 1 | li-expansion |
| dungeon/func_8132C638 | 76 | 2.8.1-G0 | 2 | 1 | broad |
| dungeon/func_8009D608 | 80 | 2.8.1 | 1 | 1 | broad |
| town/func_8087FE98 | 88 | 2.7.2 | 1 | 1 | li-expansion |
| town/func_808813CC | 88 | 2.7.2-G0 | 1 | 1 | li-expansion |
| town/func_800B9B58 | 92 | 2.91.66 | 1 | 1 | length-drift |
| town/func_806F1A40 | 104 | 2.7.2-cdk-G0 | 2 | 1 | delay-slot |
| dungeon/func_8009B0B8 | 136 | 2.7.2 | 1 | 1 | reg-rename |
| dungeon/func_800A3CA0 | 160 | 2.7.2-cdk-G0 | 2 | 1 | reg-rename |
| town/func_8051EF40 | 168 | 2.8.1 | 1 | 1 | reg-rename |
| dungeon/func_81811C20 | 172 | 2.8.1-G0 | 1 | 1 | reg-rename |
| dungeon/func_800A7828 | 208 | 2.7.2-cdk-G0 | 1 | 1 | broad |
| town/func_800A4A8C | 228 | 2.8.1-G0 | 1 | 1 | broad |
| town/func_804708B4 | 232 | 2.7.2-cdk-G0 | 1 | 1 | broad |
| slus/w_80042A80 | 232 | 2.7.2-cdk | 1 | 1 | slus-diff |
| main/func_80013B18 | 232 | 2.7.2-G0 | 2 | 1 | broad |
| town/func_8032E8C0 | 260 | 2.6.3-G0 | 1 | 1 | broad |
| town/func_80956C80 | 288 | 2.7.2-cdk-G0 | 1 | 1 | li-expansion |
| slus/w_8005D064 | 296 | 2.7.2 -G0 | 1 | 1 | slus-diff |
| dungeon/func_8184A800 | 304 | 2.7.2-cdk | 2 | 1 | reg-rename |
| dungeon/func_80DE6AAC | 436 | 2.7.2-cdk-G0 | 2 | 1 | delay-slot |
| slus/w_80059E94 | 480 | 2.8.1 -fno-schedule-insns | 1 | 1 | slus-diff |
| dungeon/func_800BE1A0 | 480 | 2.7.2-cdk-G0 | 1 | 1 | broad |
| dungeon/func_8108809C | 500 | 2.7.2-cdk-G0 | 1 | 1 | reg-rename |
| dungeon/func_80FB2B14 | 512 | 2.8.1-G0 | 2 | 1 | reg-rename |
| dungeon/func_8009D658 | 552 | 2.7.2-cdk-G0 | 2 | 1 | const-remat |
| dungeon/func_8196BA5C | 736 | 2.7.2-cdk-G0 | 2 | 1 | delay-slot |
| dungeon/func_807AEF8C | 832 | 2.7.2-cdk-G0 | 3 | 1 | delay-slot |
| dungeon/func_800976BC | 1020 | 2.8.1-G0 | 5 | 1 | reg-rename |
| dungeon/func_809CAE20 | 1028 | 2.7.2-cdk-G0 | 1 | 1 | reg-rename |
| town/func_80091840 | 64 | 2.7.2-cdk-G0 | 1 | 2 | broad |
| dungeon/func_800A1A94 | 64 | 2.7.2 | 1 | 2 | broad |
| dungeon/func_800AF9C8 | 64 | 2.7.2-cdk-G0 | 1 | 2 | broad |
| dungeon/func_800A22D8 | 68 | 2.8.1 | 2 | 2 | delay-slot |
| dungeon/func_8009A590 | 80 | 2.7.2-cdk | 1 | 2 | broad |
| town/func_8046BF44 | 88 | 2.7.2-cdk-G0 | 1 | 2 | reorder-only |
| dungeon/func_80CC2614 | 88 | 2.7.2 | 3 | 2 | reg-rename |
