# r78 type consolidation phase 10 - design

Model: claude-opus-5-5[1m].  Lane: work/native_lane/r78_types_p10.  Nothing under src/, include/, config/, tools/ or ledger/
was edited; apply10.sh lands everything (payload10/: include/shared/game_work.h + include/shared/dir_step.h updates,
names_add10.tsv; cand10/MANIFEST.tsv: 327 rows).  Re-derive from the current src/:
`python3 tools/build10.py && python3 tools/manifest10.py` (build10 composes every stage per row and check()s it).

## 0. Starting point
views9.jsonl (458 rows) was taken before phase 9 landed; the fresh census on the current tree (tools/viewcensus.py ->
census/views10.jsonl) has 415 rows with a local view on a shared object.  Re-running phase 9's drivers (drive9e/drive9g)
on the current tree folds nothing new: every "ok" they report is a candidate identical to src (already landed).  The
tail needed two tool fixes and two header updates.

## 1. Tools (lane tools/)
- **views10.py**: a union-aware parser of m2c view typedefs (inline `union { s16 s; u16 u; } unk_08;`, nested structs,
  arrays, function pointers).  consolidate.parse_views drops any struct containing a union, which is why phase 9 refused
  every `->m.s` / `->m.u` site ("view X.X unknown").  `leaf(view, chain)` resolves `->m.s[2].t` to offset/size/sign.
- **shtypes.py**: field tables of the shared types parsed from the lane inc/shared headers (`/* 0xOFF */ type name;`),
  nested sub-objects expanded (GameWork.view.slot[i], GameWork.map), Fixed1616 as .v / .w.frac / .w.i.
- **fold10.py**: the fold.  (A) a local pointer whose EVERY assignment resolves to one shared sub-object
  (`&obj`, `&obj.path`, `(u8 *)&obj + K` -> the struct-typed member at that offset; or the EntityRec pointer globals) is
  retyped to that shared type and every view access through it (`((V *)p)->m.u`, `p->m` for a view-typed p,
  `*(T *)((u8 *)p + k)`, `((T *)p)[k]`, `p[k]`, `*p`) becomes `p->field`; (B) direct casts `((V *)&obj)->m`,
  `((V *)(&obj.path))->m`, `((V *)D_800814A8)->m` become `obj.field` / `D_800814A8->field`.  A field is used only
  where one starts at the exact offset with the exact size; sign/pointer disagreement keeps a cast (rvalue) or a view
  (compound lvalue) at the use.  Refusals are recorded per pointer (table in REPORT).  Unused local views are dropped;
  the includes the new spelling needs are added.  NON_MATCHING arms are retyped in lockstep.
- **respell10.py**: `respell` (GameWork flat members -> map.* / randSeed / buttons, incl. `GameWork *` locals and
  `((GameWork *)x)->`), `pre8333C` (a TU's own `extern V D_8008333C;` -> gameWork.map), `t3flag` (D_8008333C..:
  D_8006CCF8 -> dirSpriteFlag).
- **build10.py** (composition + check + PINFREE), **manifest10.py**, **check10old.py** (opt rows vs the live include),
  **listing10.py** (whole-tree listing identity), **vbase10.py** (whole-tree verify baseline), **t3size.py**
  (declared-size A/B), **sites10.py** / **viewcensus_after.py** (census).

## 2. Header update A: GameWork (include/shared/game_work.h) - offsets and size unchanged (0x200)
- **`MapGrid map` at 0x1DC..0x1FB** (a sub-object like `view`).  Retail forms 0x8008333C (= gameWork+0x1DC) as a base
  register: the phase-3 census (r78_types_pilot/census/g83160w.jsonl) has 173 accesses based at the D_8008333C symbol
  (89 rows touch 0x1DC..0x1FF), 12 TUs name D_8008333C themselves, 13 cast `(u8 *)&gameWork + 476` or form
  `&gameWork.unk_1DC` as a pointer.  Fields: cells (void *), unk_04/08/0C (void *; func_800BCB04 reads them as a
  primitive-pointer table and two vertex arrays - one function, so unnamed), unk_10, shiftX/shiftY/maskX/maskY/
  spanX/spanY (s16) - evidence in REPORT.  0x1FC (`randSeed`) stays outside: MapGrid's views all end at +0x20.
- **`int buttons` at 0x008** (was `void *unk_008`; union resolved: 103 reads cast it to s32, 21 to u32, 5 to a pointer).
- **`int randSeed` at 0x1FC.**
- Every src row that spells an old member is respelled in the same landing (`hdr` rows, 101); the apply's preflight
  refuses the full run while any src row outside the landing would still be changed by respell10.
- Header comments name functions by their DEFINED symbol, never by row id: lane check() inlines shared headers, and
  verify.normalise_definition skips its stale-rowbase rename when the row id appears anywhere in the text - a header
  comment naming "func_800A15D0" made that row unscoreable in the lane (real verify keeps the #include, unaffected).

## 3. Header update B: dirSpriteFlag (include/shared/dir_step.h + names.tsv alias of D_8006CCF8)
Retail bytes at 0x8006CCF8 (build_slus ELF) = {1,1,0,0,0,0,0,1}; 51 rows use it the same way (REPORT).  Declared-size
A/B (tools/t3size.py): 49 of 51 rows are -G0 and exact at [], [8] and [16]; the -G8 row dungeon/func_812A524C is
exact at [] / [9] / [16] and misses at [8] (small data) - the original declaration was above 8 bytes or unsized; the
extent past the eight direction bytes is unknown (0x8006CD00 holds an s16 angle table), so it is declared unsized.
No SLUS row uses it and every use is a load (the phase-9 store-macro hazard does not apply) - and the SLUS image was
built anyway (section 5).  50 rows drop their local declaration; town/func_800C2BFC (`extern M2C_UNK D_8006CCF8;`,
scalar) keeps it.

## 4. Row classes (cand10/MANIFEST.tsv; stages r respell10, p pre8333C, f fold10, s dirSpriteFlag, pin)
- `opt` 156: fold10 only; compile identically against the old and the new headers (check10old: 156/156 exact against
  the live include) - these form the 40-row sample.
- `hdr` 101: the src spells a renamed GameWork member; must land with the header update (refused if busy/stale).
- `post` 70: need the new headers (gameWork.map / buttons / dirSpriteFlag spellings) but their old src still compiles
  after the update; full run only, skipped when busy/stale (dungeon/func_80A473B8 is busy in r78_astra_b11 today).
- The 3 rows whose only gain would be `((V *)&gameWork.map)->m` with their local view kept (func_80284BEC,
  func_8028A5D8, func_807AEF8C) are NOT in the manifest: less readable than their own D_8008333C declaration.

## 5. Proofs
- Per row: check() = cc1 listing (lane inc/) through ccproc with the lane names table + verify.py byte score (kitlib) -
  327/327 exact (no SLUS rebaseline row).
- Whole tree: listing10.py all (every row: draft or src, against inc_full = live include + both updated headers,
  dirSpriteFlag spelled D_8006CCF8 as ccproc does) vs src + live include: 6,761 / 6,767 identical; the other 6 = 2 drafts
  whose relocations name gameWork+476 for D_8008333C (same address, byte-exact by check), dungeon/func_812A524C (drops
  `.extern D_8006CCF8, 16`: overlay 2.7.2-cdk -G8 row, loads only, byte-exact by check - built, not discounted), and the
  3 rows that never compile standalone (slus/w_8003E758, w_8003F368, w_8003F624; none spells a changed name).
- SLUS image (phase 9's method): a scratch SlusView copy of build_slus with include/ = the post-apply include tree,
  config/names.tsv + the new row, all 13 SLUS drafts (incl. the module sources gp_d92c_owned / konami_runtime_w_80038A10_owned
  that include w_8003D92C / w_80038A10), EVERY object deleted: calibrate() = MATCH, words_diff 0 (862 objects rebuilt).
- Verify baseline: tools/verify.py over all 6,767 rows of the current tree exactly as apply10's full mode calls it:
  0 not exact (results/verify_baseline10.jsonl).
- Pins: pins2 over every pinned migrated row (88 rows): one pin freed - dungeon/func_8195A480's ASM_MEM_BARRIER before
  `linked_global->flags |= 0x8000` is byte-exact erased on the migrated text at the row's own cell (2.7.2-cdk, the recorded
  recipe) and NOT on the tree text (`tree_also_exact: False`): the typed objectFlagBlock access (was `s32 *` onto
  `&objectFlagBlock.flags`) keeps the order the barrier forced.  Not a cell-only result, so no cell_retail_check needed.

# HOW TO CONTINUE (cold start; supersedes phase 9's where they differ)
Start from docs/evidence/type_consolidation_pilot_design.md HOW TO CONTINUE, docs/TYPE_CONSOLIDATION.md and phase 9's
design.  Phase 10 adds:
- **Sync the lane tools** into tools/consolidate/: views10.py (use it instead of consolidate.parse_views wherever a view
  may hold a union), shtypes.py, fold10.py (the general fold: any shared type, sub-objects by offset), respell10.py as the
  pattern for a header rename.  fold10's AGG / PTRG / HDR tables list the objects; add a new shared object there.
- **Lane loop:** `python3 tools/viewcensus.py` (census) -> `python3 tools/build10.py` (compose r/p/f/s + check) ->
  `python3 tools/listing10.py all` (whole tree vs inc_full) -> SLUS scratch SlusView build (section 5) ->
  `python3 tools/manifest10.py` -> `bash apply10.sh --dry-run`.  Keep lane inc/ and inc_full/shared in sync.
- **A header rename needs three flags**: hdr (src breaks without the landing: refuse when busy/stale), post (needs the new
  header, optional), opt (either header) - check the opt set against the LIVE include (check10old.py), since the sample
  lands before the header.
- **Header comments:** defined function names only, never row ids (section 2).
- **Remaining views after this landing** (census/views10_after.jsonl, 269 rows by the census heuristic; most are views of
  what a pointer FIELD points to, not of the shared object).  Refusal table in REPORT; next, by value:
| rank | work | rows | how |
|---|---|---|---|
| 1 | entity locals also assigned from `->target`-shaped fields / call results | 55 | type-propagate: a `void *` local assigned only from EntityRec pointers (D_800814A8, `x->target` where x is an EntityRec, func_8003FC64 returns) is an EntityRec *; extend fold10.resolve with those sources |
| 2 | D_80016000 (Rec_D_80016000, 58 town rows) | 58 | hand-recover the town root record as EntityRec was (phase-9 rank 3, unchanged) |
| 3 | gameWork.unk_000 / MapGrid.cells pointee types | many | the "view of a pointee" class: a state record (+0x8D0 packet cursor) and a 6-byte map cell {kind/f0, value, flags@+4}; recover both types, then retype the fields |
| 4 | EntityRec pads / halves | 10 | unk_A4 read as two halves (+0xA6: 10 rows) - Fixed1616 if the evidence says 16.16; pads 0xF0 (s32/pointer), 0x124 (pointer), 0xFB, 0x114 |
| 5 | pointer arithmetic / union-used-whole / `[-1]` header views | 26 | `((V_pre *)p)[-1].m` is the 0x20-byte object header before a record: map onto ObjectNodeHeader where the view size and offsets line up |
| 6 | leftover second declarations | 5 | D_8008333C in dungeon/func_8180B064 (s8[]), dungeon/func_819602D8 (`__asm__` alias), slus/w_80040CBC (S_pad9[] - a SLUS -G16 page row), town/func_800AE78C (GridInfo[]); D_8006CCF8 in town/func_800C2BFC (scalar) |
| 7 | next unshared objects (fresh census) | - | D_800DDE84 (53, u16[]), D_8001E950 (43 town, Rec_D_8001E950), D_80170838/08 (42/37 dungeon pointer tables), D_800E3548 (38), D_80080000 (36), D_800FE488 (36 town), D_800DDC40 (36), D_8008ACDC (34), D_80082E60 (32, ALL binaries: struct S_80082E60 in 9 rows - the best cross-binary candidate), D_800847D0 (24 SLUS sound state, S_800847D0 re-declared per row) |
