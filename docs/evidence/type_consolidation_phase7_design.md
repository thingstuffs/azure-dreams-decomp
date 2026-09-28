# r78 type consolidation phase 7 - design

Model: claude-opus-5-5[1m].  Lane: work/native_lane/r78_types_p7.  Nothing under src/, include/, config/, tools/ or
ledger/ was edited; apply7.sh lands everything under build_ovl/work/land.lock (payload7/, cand7/).

## 1. OPEN_ITEMS #2 (game.h struct S_80083178 vs GameWork): blocked - the +0x18 block is a real sub-type
All six rows that type a local `struct S_80083178 *` (dungeon/func_800C6654, func_800C1E70, func_800B2614,
func_8191696C, func_81984E94, slus/w_80044724) were A/B'd onto flat gameWork fields (draft7/, tools/fold18.py):
- func_800C6654: `gameWork.unk_0C0` -> 19 words; the row passes the +0x18 pointer to func_800997FC and
  func_80042900, and with a flat field gcc re-derives the gameWork base as `addu $7,$6,-24`.
- func_800C1E70 (41), func_800B2614 (63): retail keeps `%hi(D_80083160+24)` live in a callee-saved register
  across calls (regs 3 -> 2 / 8 -> 7 when folded).
- func_8191696C / func_81984E94 via the dispatch block at +0xD0 directly: 26 each (retail bases at +0x18 and adds
  184/188).  slus/w_80044724 via `struct S_80083178State *` at gameWork+0xAC: 118 (retail bases at +0x18, offset 148).
Conclusion: the original had a type for gameWork+0x18..+0x1DB (0x1C4 bytes: a header 0x18..0xCB, then four
0x44-byte dispatch slots at gameWork+0xCC/0x110/0x154/0x198 ending exactly at 0x1DC where unk_1DC starts), and
functions take pointers to it.  Removing the overlap properly means GameWork EMBEDS that block, which respells every
`gameWork.viewAngle` (634 rows) and every other 0x18..0x1DB field (gcc 2.7.2 has no anonymous structs: tested,
"structure has no member named"). That is an owner decision (readability of the hottest field vs one definition),
not done here.  game.h's S_80083178 / S_80083178State / S_80083178Vector stay: also used by D_80083CE8 (globals.h,
the saved copy of gameWork 0xAC..0xCB; 15 rows), slus/w_8004D5D0 (second declaration at 0x80083178) and
slus/code2 (plural partition).  Stale comment to fix at the next game_work.h update: game_work.h still says "folding
S_80083178 into this type is the next step" (phase 4 did fold 66/69 rows).

## 2. OPEN_ITEMS #3 (generated Rec headers)
- dungeon/func_810AFA04, func_81324774: `#include "records/Rec_D_800814A8.h"` is dead (record_ptrs.h already types
  D_800814A8 as EntityRec *; no code names Rec_D_800814A8): dropping it is listing-identical and verify exact.
  apply7 step D then deletes include/records/Rec_D_800814A8.h + its ledger/records.json entry when no includer is
  left.  Both rows are busy right now (r78_opus_w7 / r78_astra_b4 out/ base_sha 11:18 / 11:37): apply7 skips them
  until the hour passes; if those lanes land first the rows go stale - re-derive (one line drop) then.
- dungeon/func_8133AD74 (sole user of Rec_D_800E3D7C.h): `D_80083780.x.v` / `.y.v` without volatile misses by 2
  words (the `#.set volatile` load schedules differently); `*(volatile s32 *)&D_80083780.x.v` at the use is exact
  but adds a `volatile` token to the row text (the lander's scaffolding count grows).  Kept; the header stays.
  (A zero-growth spelling exists - reusing the row's own local view S_80171D74_3's volatile member at00u on
  &D_80083780 - but it would name the player entity through a motion view, i.e. a false type; not done.)

## 3. New shared objects
### D_800E296C + D_800E2970 -> include/shared/dungeon_floor.h (dungeon .bss)
- Census (census/c800E29.jsonl, 159 rows): D_800E296C is word-only (lw/sw, direct, bit tests/sets); D_800E2970 is
  an array of 0x14-byte records reached by index (based_i offsets 0..0x10).  Every row that uses both forms its
  own lui for each -> separate declarations, not one struct.
- DungeonRoom (x, y u16; w, h s16; unk_08; unk_0A; flags u16; unk_0E; unk_10 int).  "Room": the corridor builder
  func_80287C4C walks the table as a grid (idx % D_8001F660) and joins room rectangles; tiles/actors carry an s8
  room index (-1 = none) that 30+ rows check against `flags & 2`.  x/y/w/h from the rect uses; the other fields
  stay unk_ (0x0A is "non-zero = a real room in the cell" in the corridor builder - not named).
- D_800E296C: scalar `int` (58 rows exact).  The 2 -G8 rows (func_800AFA68, func_812A524C) need a declared size
  > 8 and keep their local declarations (as phase 2's scalar rows).
- tools/room.py: semantics-preserving rewrite (element accesses through a 0x14-byte view -> `D_800E2970[i].field`,
  a cast at the use where width/sign differ; every other use keeps its old element type via `((T *)D_800E2970)`,
  value-only uses stay plain); drops a local view only when this rewrite removed its last use.
- drive7.py: 140/143 rows exact (296C 58, 2970 85); misses: func_800AFA68 (6, -G8), func_812A524C (73, -G8
  u8[16]), func_80286AF8 (128, Room view with tint/link members: register allocation); refused: func_8009499C and
  func_800BF6A0 (no local declaration), func_80285464 (view member Room.tiles has no field), func_81005858 (no
  common.h include - self-contained m2c text).
### D_80083120 -> include/shared/transition_slots.h (TransitionSlot[8])
- 8 slots x 8 bytes, 0x80083120..0x8008315F, no row reaches gameWork from this base.  func_8003F794(type, param)
  allocates the highest free slot (type == 0); w_8003F6F4 services type 5/6 slots.  Names: type (0 = free), param
  (the allocator's 2nd argument), unk_2 / unk_6.  The "Transition" in TransitionSlot is inherited from the existing
  slot_transition module/header name (SlotTransitionSlot), not new evidence from this phase.  include/slus/slot_transition.h already declared it
  (SlotTransitionSlot field0..field6) for the slot_transition modules: it now includes the shared header (header
  update B, its includers verified).  11 rows: 6 standalone exact; the 5 module members (w_80041B98, w_80041BE4,
  w_80041C64, w_80043DB8, w_80043E60) cannot compile in the lane against the live module header, so they were proven
  by composing both modules (slot_transition.c, _secondary.c) old vs new: cc1 listing identical at the module cfg;
  apply7 verifies them for real after B and refuses to run B without all five.
### D_80013714 -> include/shared/sys_flags.h (`extern unsigned short D_80013714;`)
- lhu/sh at offset 0 only (86 census rows); meaning of bits unproven, name stays D_.  drive3 scalar spec: 72 exact
  (all -G0 rows but 4, plus the -G8 SLUS rows that match small-data form); misses: slus/w_80042560 and
  konami_runtime_w_8003BAF8 (-G8: retail forms `lui %hi` - the TU declared it larger; w_80042560 even declares it
  twice on purpose), dungeon/func_800A665C, func_812A524C, func_81325730, func_81337D98 (aggregate/view-dependent
  codegen).  tidy137.py collapsed consolidate's decayed-array cast chains ((*(s16 *)((s16 *)(&D))) -> D) on 9 rows,
  each re-verified exact.  Several rows lose a `volatile` declaration (the volatile was not load-bearing).
## 4. Pins
pins2 over the 64 pinned rows among the 201 lane-verified candidates: no pin became removable.  (pins2 ran before
tidy137.py rewrote 9 D_80013714 rows; the tidy is cast-only and each tidied text re-verified exact, so no re-run.)  The 5 module rows
carry no pins.  Tasks 1-2 free nothing (task 2's texts are listing-identical).

# HOW TO CONTINUE (cold start; supersedes the pilot design's section where they differ)
Start from docs/evidence/type_consolidation_pilot_design.md "HOW TO CONTINUE" (workflow, tools, hazards) and
docs/TYPE_CONSOLIDATION.md.  Additions from phase 7:
- **Arrays of records** (D_800E2970-like, variable index): consolidate.rewrite does not handle them; use
  tools/room.py as the template (a FIELDS table + SYM; semantics-preserving by construction).  Drive: drive7.py.
  Several objects in one row: combine7.py applies every transform to the current src text and verifies once
  (writes cand7/ + MANIFEST.tsv).
- **Module rows** (a SLUS row that is `#include`d by a module .c): if a header update changes a member's spelling,
  the row cannot be verified in the lane through kitlib (the module compiles the live header).  Prove it by
  composing the module old vs new (tools/module_check.py) and let the apply verify it for real; the
  apply must refuse the header update unless every such row travels with it.
- **Lane check.py** inlines `slus/slot_transition.h` from lane inc/ as well (regex in inline_and_respell).
- **-G8/-G12 rows** decide declared size per TU (again: D_800E296C, D_80013714).  Scalar objects: expect 2-4 rows
  per object to keep their local declaration; record them.
- **Busy rows**: drive with a 2-hour busy window, apply with 1 hour (apply re-checks at run time).
Ranked next objects (fresh census 2026-09-28, rows whose code names the symbol, consolidated objects excluded):
| rank | object(s) | rows | note |
|---|---|---|---|
| 1 | D_80081550/54/58, D_80084808, D_80084130, D_800814C8, D_800712B4/98/50 | ~50 each, the SAME rows (town 24, dungeon 23, main 1, slus 1-6) | one clone family: census the nine together; probably one library routine per binary |
| 2 | D_80082660 | 72 | town 64 |
| 3 | D_8006DE24 | 61 | dungeon 59 |
| 4 | D_800DDE84, D_8006CCF8 | 53, 51 | dungeon (D_8006CCF8 sits after dirStepY: check whether it is a third step table) |
| 5 | D_8001E950, D_800CFCB4, D_800FE488 | 43, 32, 36 | town |
| 6 | D_80170838 / D_80170808, D_800E3548, D_800DDC40, D_8008ACDC | 42/37, 38, 36, 34 | dungeon |
| - | GameWork embedding the +0x18 block (removes game.h S_80083178) | 634+ | owner decision first (section 1) |
| - | the phase-7 misses above; D_80083498's 4 misses; D_800834B8 record | - | by hand |
