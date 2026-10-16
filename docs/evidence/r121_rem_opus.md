# r121_rem_opus: 36 remnant rows closed as exact C (3,124 B)

Lane r121_rem_opus (Opus escalation after r121_remnants continuation 5). It closes
36 queue pieces from `continue5_next.tsv`. Each is a complete function, registered as
a new row at its module's recipe, byte-exact under `lab.py baseline --score`, and
MATCH in every covering production window (18 windows). There are no pins, asm,
volatile, fake dependencies or masks.

| item | rows | bytes | route |
|---|---:|---:|---|
| A floor wrappers (active-engine-import) | 7 | 280 | stale-link bank: encoded import and resident byte map onto the shipped engine |
| B 1384-byte switch body | 1 | 1,384 | engine "message cursor" idiom for the return-copy pair |
| C 488-byte DUNGEON tail | 1 | 488 | byte-identical copy of the matched TOWN func_800BFFF4 |
| D transitive-import-contract (town) | 27 | 972 | stale town bank copies of a matched -O1 module |

## A. The monster-bank floor wrappers are stale-link copies

Each of the seven stale monster-bank windows (file 0x129B060 + k*0x6000, k = 0..6;
r121_hardholds found their +0x1348 engine shift) is a word-for-word relink of the
**current-link bank 0x2A000 bytes earlier**. Examples are 0x129B060 against 0x1271060
and 0x12BF060 against 0x1295060. All 3,467 words were compared per pair. 3,052 to
3,064 words are identical. Every differing word is a relocated field:

- jal +0x1348 (61 per bank), +0x1210, +0x1330, +0x1200, +0x464, +0x43C;
- lo16 and lui carries for resident data (-0x2530, +0x10CC, +0x19F0, ...);
- +0x1000/+0x400 for the bank's own link address;
- in 0x12AD060, 11 absolute pointer words, each +0x1000 (the bank's local pointer table).

`evidence/dungeon_bank_pairs.json` has the per-class counts. **Exactly one `sb` lo16
per bank differs by +0x13B0**: it is in the wrapper.

The wrapper at bank+0x3360 (file 0x129E3C0 ...) is
`27bdffe8 afbf0010 0c0290e6 240400b4 3c03800e 2402ffff 8fbf0010 a062bb9d 03e00008 27bd0018`.
Its current-link twin (file 0x12743C0 ...; the same body as row func_800F67A4,
`src/dungeon/func_809217A4.c`, file 0x9417A4) differs only in two places. Its jal is
0x800A56E0, which is 0x800A4398 + 0x1348. Its store is to D_800DCF4D, which is
0x800DBB9D + 0x13B0. The shipped callee is `s32 func_800A56E0(s32 query_value)`
(`src/dungeon/func_8009FF80.c`): a0 only, no stack arguments. The rows therefore
keep the encoded names, since retail encodes them:

    extern void func_800A4398(s32 query_value);   /* = func_800A56E0 */
    extern s8 D_800DBB9D;                         /* = D_800DCF4D */
    void func_80172BC0(void) { func_800A4398(0xB4); D_800DBB9D = -1; }

**Generalisation.** A stale bank's whole import contract can be read from its
current-link twin. The rule is: find the twin by masked word comparison (relocation
fields masked), then require that every differing word belongs to a relocation
class. The 7 stale windows still hold 6 raw segments each. Each raw segment can be
checked against the twin bank's rows at -0x2A000; this is the next lane's
whole-bank route.

## B. func_800255D0: the message-cursor idiom

The v8 reconstruction (r121_remnants continuation 5) differed only at the
return-copy pair at 0x80025A78/0x80025A80. Retail has `move a1,v0 ; jal 99734 ;
move s0,a1`, and v8 produced `move s0,v0 ; jal ; move a1,s0`. Twelve spellings
with one buffer variable all collapse to the same listing. CSE keeps the
longer-lived equivalent as the canonical register, so the argument copy always reads
the saved register. `alloc_need.py` reports a LOCAL qty with no single mover.

The retail pair occurs at 99 call sites of func_800990FC -> func_80099734 in
DUNGEON. Matched rows spell it with a reassigned cursor (`src/dungeon/func_800BB400.c`,
`func_800940E4.c`):

    message_end = func_800990FC();
    message_start = message_end;
    message_end = func_80099734(owner, message_end);
    message_end = func_80099194(D_80024024, message_end);
    func_80099290(message_end);
    func_800A5720(message_start);

`message_end` has several sets, so it is not CSE-equivalent to `message_start`.
That spelling is exact (scorer total 0, switch table words checked), and the new
window `dungeon_r121o_1943DD0_true_800255D0` is MATCH.

Placement evidence:
- rowbase img_1942998_80024198 ends exactly at 0x1943DD0;
- the bank header word at file 0x1942800 (0x80024000) is the entry pointer 0x800255D0;
- the 5-entry table at file 0x1942858 targets five labels inside the function at
  delta 0x7E6E1800.

All 11 callee prototypes agree with the matched definitions: SLUS `func_8003DB94`,
`func_8003FD64`, `func_8004491C` and `func_80047784`, and engine `func_800990FC`,
`func_80099194`, `func_80099290`, `func_80099734`, `func_800A48F0`, `func_800A5720`
and `func_800A6D30`.

Review note: the bank-header data (entry pointer, D_80024004 direction table,
D_80024024 message, jump table; file 0x1942800..0x194286C) stays the existing raw
data row `func_81922800`. Turning it into owned C .rodata is a module-level task.

## C. func_80024740 is TOWN func_800BFFF4

The 488 retail bytes at DUNGEON 0x1954F40 equal TOWN file 0x42894 word for word.
That is the matched row func_800BFFF4 (`src/town/func_800C2894.c`): its calls are
to resident MAIN functions, it uses gameWork, and it has no absolute local jumps.
The same source, renamed, is exact. The row lies in the selector-49 read
(r103_1954800_loader49: 12 sectors from 0x1954800 to 0x80024000). A new rowbase
region r121o_1954F40_loader49 and window dungeon_r121o_1954F40_true_80024740 cover
it. The prior lane's best candidate, an ObjectNodeHeader variant with 3 subs, was
the wrong source family.

## D. Town "transitive-import-contract" pieces: stale copies of a matched module

The refused pieces sit in eight town banks. Each bank contains a copy of the
matched -O1 module at TOWN file 0x2AE254..0x2AFD1C (rowbase sweep_2AB9C0, delta
0x7FD6A800). The copies are identical except for relocated fields, over 2,192 to
6,856 bytes.

Bank-local jal targets land on the mirrored function starts only at one delta:
0x7FC16000, 0x7FAF8000, 0x7FA95000, 0x7FA81800, 0x7FA17000, 0x7F9FF000, 0x7F9D1000
or 0x7F989000. That is 21 of 21 calls in the large copies and 11 of 12 in the small
ones. These are the deltas the earlier contract audit had recorded.
`evidence/town_bank_identity.json` has the per-bank data.

The unresolved callees named in the queue are this module's own functions:
- 0x800171DC/0x80017100 are the mirrors of func_80019308/func_8001922C;
- 0x80016D08/0x80016D7C are the mirrors of func_80018E34/func_80018EA8.

Their helper's service-table slots +0x168/+0x174 are the ones the matched module
already calls (`src/town/func_8032E514.c`, `func_8032E8C0.c`). The wrappers'
prototypes therefore come from the matched callee bodies:

- `func_80018E34(s32 slotIndex)` indexes with a0;
- `func_80018EA8(void)`;
- `func_8001922C(void *entries, s32 entry_mode)`.

Three wrappers per bank mirror func_800191C4, func_800192E8 and func_80019308
(-O1). 0x40050C and 0x5FF850 are `void f(void) { mirror_of_80019308(D_list); }`.
0x3EAB90 has the shape of func_800162A4, a selector that reads only a2. Its local
`j` pins delta 0x7FC31000, which is the existing sweep_3EA000.

New rowbase regions: 8 town regions r121o_<file>. New windows: 9 town windows
town_r121o_*.

## Verification

- `lab.py baseline <row> --score`: 36/36 `exact=true total=0`.
- `tools/overlay_local_gate.py --clean`: 18/18 MATCH. That is the 7 existing bank
  windows, 2 new dungeon windows and 9 new town windows. Each manifest lists the new
  rows as C segments.
- `tools/row_db.py check` OK. `overlay_module_gate.py --graph` adds 36 singleton
  edges.
- The new windows do not overlap, even partially, any existing window.
