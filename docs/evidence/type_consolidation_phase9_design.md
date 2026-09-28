# r78 type consolidation phase 9 - design

Model: claude-opus-5-5[1m].  Lane: work/native_lane/r78_types_p9.  Nothing under src/, include/, config/, tools/ or ledger/
was edited; apply9.sh lands everything (payload9/: include/globals.h update + NEW include/shared/sound_volume.h +
names_add9.tsv; cand9/MANIFEST.tsv: 207 rows).  draft9/ is regenerated from the current src/ by `python3 tools/build9.py`
(it composes every stage per row), then `python3 tools/check9.py` (check() on every draft) and `python3 tools/manifest9.py`.

## 1. OPEN_ITEMS #17: the 0x80084808 group -> `short volumeScale[]` (include/shared/sound_volume.h)
- **What it is.** Three s16 read/written at 0x80084808 / 0x8008480A / 0x8008480C, each used as
  `level * x / 32767` (Q15): [0] func_8005560C (gain for func_8005B4D0, which starts voices for a program's tones),
  [1] func_800552C8 (D_800848F8's level -> func_8005B27C, two 7-bit values for sequence entry D_800847D0.field22),
  [2] func_80054D64 (D_80084858's level -> func_8005A56C mode 0, value*256).  func_800559B4 (sound state init) sets all
  three to 0x7FFF; the setters func_80053E14 / func_80053DF0 / func_80053DCC store the option words 0x80080A9C / 98 / 94
  (w_8003D5A4 at boot, w_8003D92C when the options change); func_80053E20 / func_80053E90 set / get by selector
  2 / 1 / 4.  Name `volumeScale` (a sound level multiplier set from the options; relatively high confidence);
  the individual sinks are described in the header, not named.  The "player stat" / "pitch bend" / "gauge" comments
  and variable names in the touched rows asserted the wrong thing and were rewritten (comment/identifier only).
- **One object, one type.**  w_800559B4 forms 0x80084808's base once and stores +0/+2/+4 from it; w_800552C8 reads
  element 1 from the same symbol.  An ARRAY (not a struct) because func_80053E20/90 select an element by number.
- **Declared size (measured, t1/ + tools/t1v.py: verify.py object identity against full include copies whose
  globals.h drops the old line):**  `[3]` / `[4]` (6 / 8 bytes) put it in $gp small data for the 2.7.2-cdk -G8 rows:
  w_80053E20 37 words off, w_8005560C 74, w_80054D64 5, w_800552C8 3.  Unsized `[]` and `[8]` both reproduce retail
  (only relocation-symbol differences, below).  So the original declaration those TUs saw was > 8 bytes or unsized;
  unsized is the honest choice (`[8]` - m2c's guess in globals.h - would claim 0x80084810..17, which belong to the
  separate table D_80084810).  The stock 2.7.2 row w_80053E90 (bare macro form) is size-insensitive (6 words = the
  three relocations at every size) - phase 8's "declared size <= 8 in that TU" is not supported.
- **D_80084810 is not a member**: its only user (w_800550E8, `[][16]` s16 rows indexed by D_800847D0.unk20) forms
  0x80084810's own base; nothing reaches it from 0x80084808.  It keeps its declaration.
- **Which tool proves what.**  check.py's SLUS path respells the readable name in the C text before compiling, so
  its listing merges the header's `[]` with the live globals.h `[8]` and shows `.extern D_80084808, 16` - a line the
  real build (ccproc renames after cc1) never emits; check() is NOT a -G proof for named SLUS data.  The -G proofs are
  t1v.py (verify.py against full include copies without the globals.h line) and listing9 (header spelled D_80084808);
  they cover the sample run too (an unused extern emits nothing).
- **Rebaseline rows.**  w_80053DF0 / E20 / E90 / 54D64 relocated against D_8008480A / D_8008480C in the pinned objects;
  they now say D_80084808+2 / +4 (same address, same image bytes: check.py abs_listing identical, verify.py 3-6
  relocation words).  apply9 lets them through the pre-gate verify, then runs `verify.py --rebaseline-slus` after
  the SLUS SHA-1 MATCH and requires verify exact (apply5's pattern).  No c_syms / recipe change: D_80084808 is in
  the module undefined-syms list.
- **globals.h** drops `extern short D_80084808[8];` (one definition per object).  Its only user through globals.h was
  slus/code (func_80053DCC / func_80053E14, plural partition; also declared a local `D_8008480C[8]`): now
  `volumeScale[2]` / `volumeScale[0]` with the shared header - `hdr` row, lands only with the update.  Six
  self-contained overlay rows carried a DEAD `extern short D_80084808[8];` copy (m2c-flattened globals.h; declared,
  never used): dropped (`pre`, listing identical).
- **Proof of the header update** (tools/listing9.py all: cc1 listing of src + live include vs draft9 + lane
  inc_full/ as the only include dir, volumeScale spelled D_80084808 in both text and header): 6,757 / 6,767 identical;
  the other 10 = 6 of the 7 task-1 rows (w_800559B4, -G0, is identical) + slus/code (identical once symbols are absolute addresses; only `.extern ... 16`
  lines differ, which drive $gp decisions only - measured above) + the 3 rows that never compile standalone
  (w_8003E758, w_8003F368, w_8003F624, as in phase 8).  slus/code is proven in the apply by verify.py's partition gate
  (whole SLUS image) and the SLUS SHA-1 gate; its stock 2.7.2 macro form is the same toolchain path as w_80053E90,
  which verify.py proved object-identical (modulo relocation names) with the unsized declaration.

## 2. OPEN_ITEMS #18: the D_8006DE24 "base-forming" rows - a records8 artifact, all 12 now on DefEntry
- Phase 8's 11 misses (retail `%hi(D_8006DE24)` + `lbu 18($r)` vs ours `%hi(D_8006DE24+18)`) and func_800A3D40
  ("sign-extension order") were produced by the phase-8 generator's fallback spelling, not by the struct type.
  Measured on func_80A1F0C4 with `DefEntry D_8006DE24[]` declared (tools/spell.py):
  `D_8006DE24[i].kind` EXACT; `(&D_8006DE24[i])->kind` EXACT; `((DefEntry *)((u8 *)D_8006DE24 + i*0x14))->kind`
  EXACT; but the byte views `((u8 *)D_8006DE24)[i*0x14 + 0x12]`, `((u8 *)&D_8006DE24[i])[0x12]`,
  `((u8 *)D_8006DE24 + i*0x14)[0x12]` MISS with exactly phase 8's diff.  Rule: under an aggregate declaration a
  byte view folds the constant into the symbol (%hi(D+18)); the field access keeps the base.  (Under the old
  `extern u8 D_8006DE24[]` the byte form was the base-forming one - the declaration, not the spelling, decides.)
- Result: `D_8006DE24[i].kind` (9 rows), `D_8006DE24[item].unk_10` (func_800BB400), func_8009E0C0
  `DefEntry *entry = &D_8006DE24[entry_index]; return entry->unk_13;` (the natural form moves the schedule by 4
  words there; the pointer local is exact), func_800A3D40 (its local S_8006DE24_Entry -> DefEntry: unk0/unk8 ->
  unk_00/unk_08, the `name_table` local typed DefEntry *; exact, its ASM_REG pin untouched).  12/12 exact.

## 3. Task 3: views folded onto shared types (census/views9.jsonl, tools/viewcensus.py)
Census of local struct typedefs cast onto a shared object (directly or via a local pointer initialised from it):
gameWork 149 rows (dungeon 94, town 32, slus 20, main 3), D_800814A8 138, dungeonStatus 127, D_80016000 58,
D_800E3D7C 40, D_80082E80 24, D_80083780 23, objectFlagBlock 13, D_800E2970 13, D_80083498 6.  Folded (every row exact):
- **EntityRec pointers (tools/drive9e.py, 120 rows).**  D_800814A8 / D_800E3D7C are `EntityRec *` (record_ptrs.h):
  `((V *)P)->m` with V a local view -> `P->field` (entity._emit: the EntityRec field at V.m's offset; a cast or a view
  at the use where width/sign disagree) - 15 rows; `((EntityRec *)P)->f` -> `P->f` (redundant casts) - 105 rows.
  Refused: 144 rows whose casts are pointer arithmetic (`(u8 *)P + 0xAC + i*4`, `(*(u16 *)((u8 *)P + 0xA6))--`: the
  field would be a view inside unk_A4 - no readability gain), 10 without record_ptrs.h, 1 local declaration.
- **Local view pointers (tools/drive9g.py OBJ = consolidate.rewrite_pointers + respell8):**  `V *p = (V *)&obj;
  p->m` -> `Obj *p = &obj; p->field` (typed) or `obj.field` (direct).  Lane fix in tools/consolidate.py: typed mode now
  maps `p->m` through a LOCAL view's members as well (it only handled `((V *)p)->m` casts, so 41 typed candidates
  failed to build with "structure has no member").  Changed rows: gameWork 45 (dungeon 25, town 11, slus 7, main 2),
  dungeonStatus 21, TileObject D_80082E80 7, EntityRec D_80083780 3.  The flat gameWork spec is respelled to the
  phase-8 member paths by respell8 (a `field_C8` view member becomes `view.viewAngle`).
- **tools/tidy9.py** drops a local view typedef nothing references after the fold (35 rows), re-checked exact.
- Not attempted (budget; see HOW TO CONTINUE): parameter-side views (caller -> callee propagation), the `(u8 *)&
  dungeonStatus.unk_XX` byte-pointer class (~110 sites), EntityRec pad-region members (need header fields first).

## 4. Pins
tools/pins2.py over every pinned draft9 row (58 rows, 162 pins; each pin alone and all together, migrated vs tree text):
no pin becomes removable.  No cell-only result (nothing to put through cell_retail_check.py).

## 5. Pre-flight of the full apply's verify step
tools/verify.py over ALL 6,767 rows of the current tree exactly as apply9 calls it (results/verify_baseline9.jsonl):
0 not exact (671 s at 16 workers).  Note: tools/verify.py in the working tree currently carries an uncommitted
`-iquote` change for overlay include roots (OPEN_ITEMS #16 in progress); this lane does not depend on it.

# HOW TO CONTINUE (cold start; supersedes phase 8's where they differ)
Start from docs/evidence/type_consolidation_pilot_design.md "HOW TO CONTINUE", docs/TYPE_CONSOLIDATION.md and the
phase-8 design's additions.  Phase 9 adds:
- **Compose, don't chain lanes.**  tools/build9.py applies every stage to the CURRENT src text per row (t1, t2, pre,
  e, p:<obj>:<mode>, tidy) and check9.py verifies the composition once; rows touched by several drivers need no
  special handling.  Copy the pattern: each driver only records which rows/modes were exact; build composes.
- **Declared size bound first** for any small global (<= 8 bytes): A/B `[N]` vs unsized with verify.py against a full
  include copy (tools/t1v.py writes one per variant and compiles SLUS rows with `-I` that copy only - SLUS non-module
  rows accept include_root; overlay rows need listing identity, tools/listing9.py).
- **Byte views under an aggregate declaration fold the offset into the symbol** (%hi(D+k)); field accesses keep the
  base.  Before calling a class "base-forming, keep the local declaration", try the plain field spelling and a
  `T *e = &D[i]; e->f` local (task 2: 12/12).
- **Redundant casts on typed pointer globals** (`((EntityRec *)D_800814A8)->f`) are free readability (105 rows here).
- **rewrite_pointers typed mode** (lane tools/consolidate.py, worth syncing to tools/consolidate/): maps local-view
  members; for gameWork run respell8 after it (the spec objects/gameWork.json is still the flat pre-phase-8 layout -
  regenerate it from game_work.h when convenient).
Ranked next (rows that USE the object; views9 census):
| rank | work | rows | note |
|---|---|---|---|
| 1 | remaining local views on gameWork / dungeonStatus | ~100 / ~100 | 190 + 120 refused by rewrite_pointers: pointer also assigned something else, `(u8 *)&dungeonStatus.unk_XX` byte pointers, declarators it cannot parse; 51 + 7 misses (schedule) |
| 2 | EntityRec pad members | - | name/declare fields views reach inside pads (0x2E, 0x34.., 0x74.., 0xB4.., 0xDC..) - a header update with listing proof - then re-run drive9e |
| 3 | D_80016000 (Rec_D_80016000, 262 casts in 175 town rows) | 176 | the generated record behind the town root pointer: hand-recover a type as EntityRec was |
| 4 | parameter-side views (EntityRec / GameView params) | many | needs caller -> callee type propagation |
| 5 | D_800DDE84, D_8006CCF8 (after dirStepY), D_8001E950, D_80170838/08 | 53, 51, 42, 42/36 | census uses first |
| - | sound state: D_800847D0 (24 SLUS rows, S_800847D0 re-declared per row), D_800848F8 / D_80084858 (one task type, two instances) | 24+ | the next SLUS readability win next to volumeScale |

## 6. FIX after the full run reverted twice (2026-09-28, after the sample landed as dd8a5c2b)
- **Symptom:** full apply9 -> verify: 59 not exact, every SLUS module/partition row "module gate baseline: NO MATCH,
  88082 words" (the gate's calibration build of the whole image).  Deterministic; not the build_slus resync and not
  verify.py's new include_root precedence (76ef38c5): the calibration builds build_slus's copy, whose include/ is a
  symlink to the live tree.
- **Root cause (reproduced in scratch SlusView copies, scratchpad repro*.py):** the UNSIZED `volumeScale[]` breaks
  slus/code.  code.c is stock 2.7.2 with bare store macros (`sh $4,D_...`); with `.extern D_8008480C, 16` the store
  is expanded via `lui $2` and scheduled into the jal / jr delay slot (retail), with no `.extern` size it goes through
  `$at` with a nop - func_80053DCC / func_80053E14 grow, the image shifts.  Views: live tree MATCH; globals.h update
  only MATCH; + new code.c with `[]` NO MATCH 88,082; `[4]` NO MATCH 88,120; `[5]` MATCH; `[8]` MATCH.
- **Where the lane proof failed:** DESIGN §1 took listing identity "modulo `.extern` sizes" as proof for slus/code,
  assuming `.extern` only drives $gp decisions.  For stock-2.7.2 macro stores it also drives the expansion and the
  delay-slot fill.  Rule for the kit: never discount an `.extern` difference on a stock (non-cdk) SLUS TU - build it.
  (w_80053E90, also stock 2.7.2, only loads; it is exact with either declaration.)
- **Fix:** the full run also UPDATES include/shared/sound_volume.h to `extern short volumeScale[8];` (payload9 +
  UPDATES.tsv; the header comment records the measurement and that the true extent is unknown).  Proof without
  landing: (1) the 7 landed w_ rows are verify.py-exact with include_root = the post-apply include copy (and with the
  live one); (2) a scratch SlusView of the COMPLETE post-apply SLUS state (post-apply include copy, all 16 cand9 SLUS
  texts incl. code.c, their objects deleted to force a rebuild) calibrates MATCH, words_diff 0 - that calibration is
  exactly the module/partition gate baseline that failed; (3) listing9 over all 6,767 rows against the post-apply
  include: identical except the 8 task-1 rows (proven by 1-2) and the 3 rows that never compile standalone.
