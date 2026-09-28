# r78 type consolidation phase 10 - report

Model: claude-opus-5-5[1m].  Deliverable: apply10.sh + payload10/ (UPDATES.tsv: include/shared/game_work.h and
include/shared/dir_step.h updated; names_add10.tsv: dirSpriteFlag -> D_8006CCF8) + cand10/MANIFEST.tsv (327 rows:
156 `opt`, 101 `hdr`, 70 `post`; dungeon 260, town 47, slus 13, main 7) + sample10_rows.txt (40 opt rows: dungeon 31,
town 7, slus 2 - main's 7 rows all need the header update, so the no-header sample cannot include main).
`bash work/native_lane/r78_types_p10/apply10.sh --dry-run` -> 326 to land, 1 skipped (dungeon/func_80A473B8, busy in
r78_astra_b11; a `post` row, it just stays as it is); with `--no-hdr --rows .../sample10_rows.txt` -> 40, 0 skipped.

Run order (from the repo root; the script takes build_ovl/work/land.lock itself):
1. `bash work/native_lane/r78_types_p10/apply10.sh --no-hdr --rows work/native_lane/r78_types_p10/sample10_rows.txt`
   (40 opt rows; headers untouched; verify.py on the landed rows, gate_all, SLUS SHA-1).
2. `VERIFY_WORKERS=16 bash work/native_lane/r78_types_p10/apply10.sh` (both header updates + names row + every other row;
   verify.py on EVERY row ~11 min, gate_all, SLUS SHA-1).  Resumable.  A stale/busy `opt`/`post` row is skipped; a
   stale/busy `hdr` row (or any src row outside the landing that still spells an old GameWork member) refuses the run -
   re-derive: `cd work/native_lane/r78_types_p10 && python3 tools/build10.py && python3 tools/manifest10.py`.

| task | result |
|---|---|
| 1 fold views onto shared types | 327 rows (every row verify-exact): 227 local pointers retyped onto a shared type (EntityRec 81, DungeonGlobalStatus 73, MapGrid 32, GameWork 24, TileObject 7, GameView 6, ObjectFlagBlock 4) + direct casts; 413 distinct pointer/field mappings (260 plain, 84 keep a sign/pointer cast at the use, 69 a view at a compound store); 328 local view typedefs dropped.  101 rows respelled onto the renamed GameWork members, 50 rows onto dirSpriteFlag.  Census: 415 rows with a local view on a shared object -> 269 after landing (most of the rest are views of what a pointer field points to). |
| 2 fields named | GameWork.map (MapGrid: cells, shiftX, shiftY, maskX, maskY, spanX, spanY), GameWork.randSeed, GameWork.buttons, dirSpriteFlag - evidence below |
| 3 next objects | fresh census only (budget went to the two header updates): see DESIGN HOW TO CONTINUE rank 7 |
| pins | one freed: dungeon/func_8195A480 ASM_MEM_BARRIER (in the manifest, stage f+pin) |

## Newly named fields and their evidence
| name | where | evidence |
|---|---|---|
| `GameWork.map` (MapGrid, 0x20 bytes) | gameWork+0x1DC | a real sub-object: retail forms 0x8008333C as a base register (173 accesses based at that symbol in the phase-3 census; 12 TUs name D_8008333C themselves; func_800A0548's MECHANISM note "a named base holds &D_8008333C"); 13 rows cast `(u8 *)&gameWork + 476`, 26 spell `gameWork.unk_1DC` (mostly its address, as a pointer) |
| `MapGrid.cells` | +0x00 | the map cell array: `cells + (x + (y << shiftX)) * 6` (func_80017EBC counts cells whose flags word at +4 has no 0x8500 bits; func_80018464 writes cell kind / value) |
| `shiftX` / `shiftY` | +0x14 / +0x16 | func_80018464 (map load) sets them from the map data; row stride is `1 << shiftX`; func_800A0548 bounds-checks `x < 1 << shiftX`, `y < 1 << shiftY` |
| `maskX` / `maskY` | +0x18 / +0x1A | func_80018464: `maskX = (1 << shiftX) - 1` (same for y) |
| `spanX` / `spanY` | +0x1C / +0x1E | func_80018464: `spanX = 64 << shiftX`; world coordinates are 64 units per cell (EntityRec x = tile * 64 + 32), so the map size in world units |
| `GameWork.randSeed` | +0x1FC | func_800A6D30: `seed = seed * 0x41C64E6D + 0x3039; return (seed >> 16) & 0x7FFF` (the ANSI rand() LCG); func_800A6D60 saves / restores it through D_800DD87C |
| `GameWork.buttons` (int; was `void *unk_008`) | +0x008 | the PS1 pad bit layout in 53+ rows' tests: 0x1000/0x2000/0x4000/0x8000 d-pad (0xF000 "any direction", 0x5000 up+down), 0x10/0x20/0x40/0x80 face buttons, 0x100 select, 0x800 start, 1/2/4/8 shoulders.  Held vs newly pressed is NOT established (the header says so).  Union resolved: 103 s32 casts vanish, 21 u32 and 5 pointer casts stay |
| `dirSpriteFlag` (names.tsv alias of D_8006CCF8, `unsigned char[]`) | SLUS .data 0x8006CCF8 | retail bytes {1,1,0,0,0,0,0,1} (directions 7, 0, 1 - dirStepX = +1); 51 rows: `if (dirSpriteFlag[(viewAngle + facing + 0x100) >> 9 & 7]) sprite->flags14 |= 1; else &= ~1`.  Plausibly a horizontal mirror of the side views - unproven, so the name says what it does.  Unsized: the -G8 row func_812A524C needs > 8 bytes |
Left unnamed (typed only): MapGrid.unk_04 / unk_08 / unk_0C (void *; func_800BCB04 alone reads them as a primitive-pointer
table and two vertex arrays), MapGrid.unk_10.

## What blocks the rest (census rows not in the manifest; one reason per row)
| rows | reason |
|---|---|
| 82 | nothing to fold: the pointer is already typed, or the view is of a POINTEE (gameWork.unk_000's state record, MapGrid.cells' 6-byte cells) - needs those types recovered |
| 55 | the local pointer is also assigned a non-object value (actor->target / `*(void **)(actor + 0x60)`, func_8003FC64 results) - needs caller/field type propagation |
| 19 | folded but not byte-exact (schedule: e.g. `%hi(D_80083460+10)` vs retail's base form; register choice) or a build error in the fold |
| 16 | fold produced nothing to change |
| 12 | pointer arithmetic on the pointer itself |
| 8 / 6 / 6 | a union member used whole / a `[-1]` object-header view (not dereferenced) / reaches EntityRec padding (0xF0, 0x124, 0xFB, 0x114, 0x92) |
| 4 / 4 | direct cast form not understood / a narrower read inside a field (EntityRec unk_A4's +2 half, TileObject tileX/tileY as one u16) |
| ~10 | single cases (declaration forms, several objects in one pointer, sub-object offsets outside the type) |
| 3 | D_8008333C-only rows whose result would keep `((V *)&gameWork.map)->m` - deliberately not landed (less readable) |
Second declarations that remain: 0x8008333C in dungeon/func_8180B064, dungeon/func_819602D8, slus/w_80040CBC, town/func_800AE78C
(array / asm-alias forms); 0x8006CCF8 in town/func_800C2BFC (scalar).

## Proofs (DESIGN section 5)
Per row check() 327/327 exact; opt rows 156/156 exact against the LIVE include too (sample lands before the headers);
whole-tree listing 6,761/6,767 identical (the other 6 explained: 3 byte-exact drafts, 3 never-standalone rows);
SLUS scratch SlusView build of the complete post-apply state, every object rebuilt: MATCH, words_diff 0; whole-tree
verify.py baseline on the current tree: 0 of 6,767 not exact; pins2 over 88 pinned migrated rows.

## Pin freed
dungeon/func_8195A480: `ASM_MEM_BARRIER();` before `linked_global->flags |= 0x8000;` - exact without it on the migrated
text at the row's own recipe (2.7.2-cdk), not on the tree text (`tree_also_exact: False`): the typed objectFlagBlock
pointer (was an `s32 *` onto `&objectFlagBlock.flags`) keeps the store order the barrier forced.  Own-cell result, no
cell_retail_check needed.  In the manifest (stage `f+pin`, opt, also in the sample).

## Kit lessons
- consolidate.parse_views silently drops any view containing a union (the whole "->m.s" class): use views10.
- Header comments name functions by their defined symbol, not by row id (lane scoring inlines headers; verify's
  stale-rowbase rename is skipped when the row id appears in the text).
- A header rename needs hdr / post / opt flags, and the opt set must be checked against the live include.
