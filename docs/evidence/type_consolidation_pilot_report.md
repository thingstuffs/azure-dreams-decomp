# r78 type-consolidation pilot - report

Model: claude-opus-5-5[1m] (provider anthropic; codex.log). No edits to src/, include/, config/ or tools/, no git,
no landers. BUSY_ROWS untouched.

## Deliverables (this directory)
- `DESIGN.md`: the mechanism, the header layout, the naming rule, the two recovered types with per-field
  evidence, the measured hazards, and the scaling recommendation.
- `apply.sh` (+ `payload/`): `payload/include/shared/{dir_step,dungeon_status}.h` and `payload/names_add.tsv`
  (3 data alias rows).
  - Dry run: `preflight: 243 rows to land, 0 skipped`. The dry run takes no lock.
  - The real run takes `build_ovl/work/land.lock` and checks each row's src sha256 (stale or busy rows are
    skipped). It refuses any pin or scaffolding growth and any name or type collision.
  - It then writes the headers, names.tsv and the rows, runs `verify.py` on all touched rows,
    `mk_ovl_root.sh` + `gate_all.py --workers 8`, and `build_slus.sh -j 8` with `gate_slus` MATCH. Any failure
    restores everything (REVERTED).
- The gate runs in `build_ovl_gate` by default (LAND_ISOLATED=1, as land_lanes.sh does), so build_ovl, which the
  pin lanes score in, is never rebuilt. `--rows blk_sample_rows.txt` lands the 20-row block sample first when a
  smaller first gate is wanted. names.tsv is appended newline-safely.
- `cand/<container>/<file>.c` + `.base_sha`, and `cand/MANIFEST.tsv`: 243 verified rows (row, candidate, verified
  src sha, how).
- `results/final.jsonl`: the final verification of each candidate (cc1 listing through ccproc with the lane
  names table vs the pinned listing, plus the `verify.py` byte score).
- Evidence and tools:
  - `census/*.jsonl`: every access to the targets in the pinned listings, via `tools/census.py` + `tools/flow.py`.
  - `results/*.jsonl`: every measured pass.
  - `tools/{rewrite,check,drive,finalize}.py`.
  - `hand/blk/`: the hand-written natural spellings.
  - `hand/pin/`: the pin tests, not in the apply set.

## Target 1: direction step tables -> `dirStepX` / `dirStepY` (231 rows: dungeon 224, town 7)
| outcome | rows | spelling / reason |
|---|---|---|
| exact, natural `short` array (`dirStepX[i]`) | 215 | includes rows that had declared `u16[]` |
| exact, view spelling | 10 | `((u16 *)dirStepX)[i]`: these rows' `lhu` feeds a compare or shift, so `short` gives `lh` |
| refused | 1 | dungeon/func_800B0770 (2.7.2-cdk, -G8): it declared `s8` (1 B, a small-data extern), so cc1 emits a `la` macro and retail matches that. With `short[8]` the row misses by 3. It keeps its local declaration |
| refused | 1 | dungeon/func_80D3CBF8 (2.8.1-G0): a `u8[16]` byte view; the cast view changes a register choice (9 differences) |
| not attempted (rewriter limit) | 2 | town/func_800C0D74 declares `s16 D_8006CCD8[][2]` (a pair view); dungeon/func_800C6C10 declares both tables on one line. Both are trivial hand edits and are not in the apply set |
| busy (not touched) | 2 | BUSY_ROWS |

## Target 2: the 0x80083460 block -> `DungeonGlobalStatus dungeonStatus` (size 0x20)
The rows that access 0x80083460..0x8008347F are all dungeon rows plus slus/w_80042BDC. Town touches only
0x80083498 / 0x800834B8, which are separate objects, so the "mixed containers" sample is dungeon + SLUS.

**Sample migrated (20 rows, all exact via verify.py; in the apply set)**

| row | cfg | retail pattern | spelling | notes |
|---|---|---|---|---|
| dungeon/func_80087A70 | 2.7.2-cdk-G0 | base | plain fields (hand) | local view `S80083460` removed; 0x0C compared with an entity pointer, which is why it is typed `void *` |
| dungeon/func_800881EC | 2.7.2-cdk-G0 -fno-schedule-insns | base | plain field (hand) | `D_80083460[2] = D_80083460[2]*2` becomes `unk_04 = unk_04 * 2`; the automatic view cast missed by 3 |
| dungeon/func_8009612C | 2.7.2-cdk-G0 -fno-rerun-cse-after-loop | direct | plain field (auto) | also migrated for target 1 (both rewrites in one text) |
| dungeon/func_8009D47C | 2.7.2-cdk-G0 | base | plain fields (hand) + one `*(s32 *)&dungeonStatus.unk_08` | the one 32-bit read over 0x08..0x0B (the union site) |
| dungeon/func_800A05E4 | 2.7.2-G0 (macro) | direct | plain field (auto) | |
| dungeon/func_800A07D8 | 2.7.2-cdk-G0 | base | plain field (hand) | `D_80083460[5]--` becomes `dungeonStatus.unk_0A--`; the view cast missed by 3 |
| dungeon/func_800A1094 | 2.7.2-cdk-G0 | base | plain field (hand) | as above; the view missed by 6 |
| dungeon/func_800A42AC | 2.7.2-G0 (macro) | direct | plain field (auto) | |
| dungeon/func_800BC764 | 2.7.2-cdk-G0 | base | plain field (hand) | as above; the view missed by 6 |
| dungeon/func_800C23D8 | 2.8.1-G0 | base | plain field (hand) | the view missed by 6 |
| dungeon/func_800CED34 | 2.7.2-cdk-G0 | two direct symbols in one function | plain fields (hand) | separate luis are kept: the accesses are in different blocks |
| dungeon/func_80976E28 | 2.6.3-G0 (macro) | direct | plain field (auto) | |
| dungeon/func_80A71654 | 2.8.1-G0 | direct | plain field (auto) | |
| dungeon/func_80CC266C | 2.8.1-G0 | direct + base | plain fields (hand) | the local `u8 *global_state` alias and its view typedef are removed; `unk_0A` load+store forms the base itself |
| dungeon/func_80CE8CBC | 2.8.1 -G0 | direct | plain field (auto) | |
| dungeon/func_80F0C3B8 | 2.7.2-cdk-G0 | base | plain field (hand) | the view missed by 5 |
| dungeon/func_8125192C | 2.7.2-cdk-G0 | two direct | plain fields (hand) | needs `unk_0A` to be `short`: declared `unsigned short`, it misses by 1 (`lh`) |
| dungeon/func_81332EC0 | 2.7.2-cdk-G0 | two direct | plain fields (hand) | same |
| dungeon/func_818AAE60 | 2.8.0-G0 | direct | plain field (auto) | also migrated for target 1 |
| slus/w_80042BDC | 2.7.2-cdk -G16 | base | plain fields (hand) | local `S_80042BDC_83460` removed; the listing is identical, so no SLUS rebaseline is needed |

**Whole-population measurement (automatic, not landed; `results/blk_*_scored.jsonl`)**

| pass | exact |
|---|---|
| view mode (type-preserving casts) | 795 / 857 |
| plain-when-compatible, `unk_0A` unsigned | 786 |
| plain-when-compatible, `unk_0A` short (adopted) | 797 |

- Every row whose declarations map onto a field was exact (234/234).
- The 60 misses are all array/pointer-cast views: `u16[]` 27, `s32[]` 21, `s16[]` 4, `u8[]` 3, and a few
  others.
- 5 rows use a block symbol with no local declaration, and 1 view needs a hand edit.
- Hand natural spelling fixed 8 of 8 tried.

## Pins
Not a pin lane, so nothing was removed. Two rows show the type change can remove a pin:
- dungeon/func_800A065C (`ASM_KEEP(base)`, registered 2.7.2-G0 with -fno-schedule-insns*): the one-line
  `dungeonStatus.unk_0A += 1;` is exact at 2.7.2-cdk-G0 (with and without the -fno-schedule flags). The pinned
  text is not exact there (total 6).
- dungeon/func_800A4DA8 (`do {} while (0)` scaffold, pointer arithmetic, 2.7.2-G0): the natural spelling is exact
  at 2.7.2-cdk-G0; the pinned text misses by 7.

Both are rule-4b / 09-24 coherence repairs: the retail `la g` + `off($r)` form is the split-address fingerprint.
Land them with `land_coherence.sh`, with the struct in place. The texts are in `hand/pin/dungeon/`.

## Tool calls
About 155 tool calls, within the ~200 budget.

---

# Phase 2 report (r78)

Model: claude-opus-5-5[1m]. No edits to src/include/config/tools, no git, no landers.
- Busy rows: `BUSY_ROWS2.txt` (the 5 r78_* out rows with a fresh .base_sha). apply2.sh re-applies the one-hour
  rule at run time.
- 9 SLUS rows in plural-compilation partitions cannot be compiled alone: code, code2, w_8003E34C, w_8003E758,
  w_8003F2A4, w_8003F368, w_8003F624, w_80041134, w_80050E20. They were skipped for objectFlagBlock.

## Deliverables
- `apply2.sh` + `payload2/`:
  - `include/shared/object_flags.h` is new; `dungeon_status.h` and `dir_step.h` are unchanged.
  - `names_add.tsv` holds 1 row: `D_800814A0 -> objectFlagBlock`.
  - `cand2/<container>/*.c` + `.base_sha` and `cand2/MANIFEST.tsv`: 1,382 rows, each verify-exact in the lane.
  - apply2.sh is resumable in the same way as the patched apply.sh: identical names rows and headers count as done,
    and a row already equal to its candidate is skipped as landed.
  - Its restore also puts back any header it overwrote.
  - Dry run: `preflight: 1382 rows to land, 0 skipped`.
  - `p2_sample_rows.txt` (44 rows: every slus/main row plus 10 town and 10 dungeon) gives a smaller first gate:
    `apply2.sh --rows work/native_lane/r78_types_pilot/p2_sample_rows.txt`.
- The generator: `tools/consolidate.py` + `objects/*.json` + `tools/drive3.py` (DESIGN section 7).
- Evidence:
  - `census/g814a0.jsonl`, `census/blk2.jsonl`
  - `results/p2_multi.jsonl` (the final run)
  - `results/p2_multi_scalar.jsonl` (the scalar-int A/B)
  - `results/p2_objectFlagBlock_both.jsonl` (the A8-as-field A/B)
  - `results/pins2.jsonl`

## Rows
| object | rows exact (in apply2) | spelling | not migrated |
|---|---|---|---|
| dungeonStatus (rest of the population) | 825 (dungeon) | 669 pure fields, 26 with a sign/int cast, 130 with a pointer-variable view | 2 miss (dungeon/func_8008629C by 13, dungeon/func_80CEAF2C by 26); 5 with no local declaration (func_800A4AF8, func_800A52C8, func_800A7438, func_800B7CFC, func_800BF6A0) |
| objectFlagBlock | 681 (dungeon 537, town 120, main 15, slus 9) | `objectFlagBlock.flags \|= 0x8000`, `.unk_04`, `.unk_0C` | 21 miss (below); 12 declare it elsewhere (module/shared context); 7 have local view typedefs the generator does not lay out (`FlagBlock`, `S_800814A0`) or access +0x10; 9 plural-partition SLUS rows |

Rows touching both objects: 124, each with both rewrites in one verified text.

**The scalar-int rows**
- 19 rows were compiled against `extern int D_800814A0;`: every aggregate spelling misses them, and a scalar is
  exact. `scalar_rows.txt` lists all 21 misses; these 19 are the ones exact as a scalar:
  - slus: code10, code11, code5, konami_runtime_w_8003C520, w_800403BC, w_8004B298, w_8004B2E0, w_8004F558,
    w_8004FE78, w_80050CDC, w_800510DC, w_80052144, w_800530C4
  - main: func_80012D34, func_80014C90
  - town: func_800B2C54, func_800B9464, func_800BC078
  - dungeon: func_81811B94
- Two more misses are not explained by the scalar/aggregate choice: slus/w_800439F8 (A4/AC byte fields, by 12) and
  slus/w_80050E20 (a plural partition).
- Owner decision: one address declared two ways in the original. The options are to keep D_ in these rows or to
  add a second readable alias for the scalar view.

## Pins
- 256 migrated rows still carry pins. Each pin was erased alone and then all together, and the migrated text was
  byte-scored.
- **No pin becomes removable.** There is nothing to land from phase 2; the type change is pin-neutral here.
- From phase 1: func_800A065C and func_800A4DA8 are removable only through the cdk-G0 recipe (coherence).

## Recipe side finding (informational; nothing to land for the aggregate choice)
All 45 rows registered at the default -G8 on split cells are byte-exact at -G0 with their pinned text. This
matters only if a scalar declaration is ever chosen for 0x800814A0.

## Next objects
See DESIGN section 11. By row count: D_80083228 578, D_80045340 442, D_80083160 403 (all binaries),
D_80016000 313, D_80082E80 290, D_80083498 284, D_800814A8 236, D_800E3D7C 199, D_80083780 177.

## Tool calls
Phase 2 used about 50 tool calls.

---

# Phase 3 report (r78)

Model: claude-opus-5-5[1m]. No edits to src/include/config/tools, no git, no landers. Busy rows are the 3
listed in `BUSY_ROWS3.txt` plus the live one-hour rule in apply3.sh.

## Deliverables
- `apply3.sh` + `payload3/`:
  - `include/shared/game_work.h` and `include/shared/slus_callbacks.h` are new; the earlier headers are
    unchanged.
  - `names_add.tsv`: `D_80083160 -> gameWork`.
- `cand3f/<container>/*.c` + `.base_sha` and `cand3f/MANIFEST.tsv`: 1,487 rows, each verify-exact in the lane.
  - By binary: dungeon 1,274, town 159, slus 42, main 11, ovmovie 1.
  - apply3.sh is resumable in the same way as apply2.
  - Dry run: `preflight: 1487 rows to land, 0 skipped`.
- `p3_sample_rows.txt`: 40 rows across all five binaries (slus 6, main 6, ovmovie 1, town 12, dungeon 15),
  covering every plan kind. Use `apply3.sh --rows work/native_lane/r78_types_pilot/p3_sample_rows.txt`.
- Tools, written back to the lane (sync into tools/consolidate/):
  - `tools/consolidate.py`: `emit_field`, `rewrite_pointers`, `rewrite_funcaddr`, struct-tag and opaque views
  - `tools/drive3.py`: the pointer fold in every plan, and the ptr-only rows
  - `tools/layout.py`: layout from a census
  - `tools/drive_ptr.py`
  - `tools/pins2.py`: now takes PINRES/PINCAND/PINOUT
  - `objects/gameWork.json`, `objects/func_80045340.json`, `objects/dungeonStatus.json` (+type)
- Evidence:
  - `census/g83160w.jsonl`, `census/g83160_layout.json`, `census/g45340.jsonl`, `census/g83228.jsonl`
  - `results/p3_*.jsonl`
  - `results/pins3.jsonl`

## Rows
| work item | rows exact | notes |
|---|---|---|
| local-pointer fold onto dungeonStatus | 313 (287 direct, 26 typed) | 22 rows keep their pointer (a use the fold does not understand, several different assignments, or a register pin) |
| GameWork gameWork (0x80083160..0x8008335F, incl. D_80083228 -> gameWork.viewAngle, D_800832B4 -> unk_154, D_80083350 -> unk_1F0, ...) | 967 (dungeon 803, town 110, slus 42, main 11, ovmovie 1); 110 of them also fold a gameWork pointer (78 typed, 32 direct) | 147 still hold a `(u8 *)&gameWork` view pointer the fold could not take |
| D_80045340 -> func_80045340 | 434 of 442 | 1 register-allocation miss (dungeon/func_80E0D090, by 9); 1 combined declaration line (town/func_800CB660); 2 index/arithmetic uses; 3 no local declaration |

Not migrated:
- 36 rows verified not exact are listed in `p3_miss_rows.txt`: mostly SLUS 2.7.2-cdk rows declaring
  `void *D_80083160[3]` and friends, D_8008333C views, and 2 D_80083178 mixes.
- 235 rows were refused: 215 have no code reference; the rest have no local declaration, an unparsed foreign view
  (GridInfo, Palette, GlobalSlot, ...), or a combined declaration.

**No clean two-declarations case.** Unlike 0x800814A0, the gameWork misses do not split into a scalar class, and
the aggregate/scalar A/B on 0x80083228 found no row that needs the scalar. Nothing is kept on D_ for that reason.

## Pins
- **dungeon/func_80DE9000** (2.7.2-cdk-G0): `register void *arg3_part ASM_REG("17")` (line 118). Erased alone, the
  row is byte-exact at its registered cell, on the migrated text and on the current tree text alike. It is
  removable today, independent of the type change. Evidence: `results/pins3.jsonl` (`tree_also_exact: true`).
  Cell-only checking does not apply.
- No other pin in the 350 pinned migrated rows falls, singly or all together.
- Folding a register-pinned pointer to the object removed no pin.

## Next objects
See DESIGN section 16. First: D_80083178, which is gameWork + 0x18 and would retire game.h's provisional
S_80083178. Then D_80016000 (313), D_80082E80 (290), D_80083498 (284), D_800814A8 (236), D_800E3D7C (199) and
D_80083780 (177).

## Tool calls
Phase 3 used about 75 tool calls.

---

# Phase 4 report (r78)

Model: claude-opus-5-5[1m]. No edits to src/include/config/tools, no git, no landers. Busy rows: `BUSY_ROWS4.txt`
plus the live one-hour rule in apply4.sh.

## Deliverables
- `apply4.sh` + `payload4/`:
  - `include/shared/record_ptrs.h` is new; every other shared header is unchanged; there are no new names.tsv
    rows.
  - **game.h / globals.h are not touched: the removal of S_80083178 is blocked** (DESIGN section 17).
  - Resumable in the same way as apply3.
  - New: rows flagged `rebaseline` in the manifest (11 SLUS rows, relocation-symbol-only differences) are exempt
    from the per-row verify. After the SLUS image MATCH they get `verify.py --rebaseline-slus` and then a strict
    verify; any failure restores everything.
  - Dry run: `preflight: 763 rows to land, 0 skipped`.
- `cand4f/<container>/*.c` + `.base_sha`, and `cand4f/MANIFEST.tsv`, whose 5th column is `rebaseline`.
  - 763 rows: dungeon 432, town 314, slus 16, main 1.
- `p4_sample_rows.txt`: 40 rows (slus 9 including rebaseline rows, main 1, town 11, dungeon 19).
- `pins4/`: three pin-removal candidates (below), each with a `.base_sha` of its apply4 text.

## Rows
| work item | rows exact | not migrated |
|---|---|---|
| D_80083178 onto gameWork (+0x18) | 66 of 69 (5 via SLUS rebaseline) | dungeon/func_800AFA68 (miss 9); slus/w_8004D5D0 (miss 5: retail's base is 0x80083178, a second declaration, so it keeps D_80083178); slus/code2 (plural partition) |
| D_800814A8 as `struct Rec_D_800814A8 *` | 230 | a few misses, see results |
| D_800E3D7C as `struct Rec_D_800E3D7C *` | 188 | |
| D_80016000 as `struct Rec_D_80016000 *` | 294 | |
| more local-pointer folds (the 147 `(u8 *)&gameWork` rows, plus dungeonStatus leftovers) | 10 | 128 folded texts are not exact (the pointer is load-bearing); 75 have no foldable pointer, 55 unmodelled uses, 26 reassigned |

Rows touching several objects are migrated in one verified text; the plans are listed in the manifest.
Evidence: `results/p3_dungeonStatus_gameWork_D_800814A8_D_800E3D7C_D_80016000_final.jsonl`, `results/p3_*_ptrs.jsonl`,
`results/p3_gameWork_s78.jsonl`.

## Pins (land after apply4)
Candidates are in `pins4/`. Each is byte-exact at the registered cell (SLUS object identity) with the pins
erased. The same erasure on today's tree text is not exact, so the type change is what frees them. None is
cell-only exact, so no cell_retail_check was needed.

| row | pin | line | via | tree erasure total |
|---|---|---|---|---|
| slus/w_8004FAA4 | `ASM_SCHED_BARRIER()` x2 | 79, 86 | D_800814A8 as a scalar pointer | 51 |
| slus/w_800492B0 | `ASM_KEEP(index)` | 16 | D_800814A8 | 11 |
| slus/w_80042BDC | `ASM_KEEP_NV(owned_ent)` | 268 | D_800E3D7C | 3 |

The mechanism is the same in all three: m2c declared the pointer global as an array (the aggregate alias class),
and the pins compensated for it. Declared as the scalar pointer retail used, the schedule comes out right with
no pin.

## Tool write-back (lane -> tools/consolidate/)
- `tools/consolidate.py`:
  - parse_views: nested views, function-pointer members, `known` views, struct tags
  - member chains `a.b[k].c`
  - `global_decls`, `extra_views`, `drop_views` + `agg_addr`, `collapse_casts`
  - the placeholder for objects that keep their D_ name
  - `ptype` view casts
  - `_addr_off` accepting `(u8 *)&var + k`
  - rewrite_pointers: known views, struct-tag pointee types, `allow_pinned`
- `tools/check.py`: `abs_listing` for SLUS rebaseline detection; reads names_add4.tsv.
- `tools/drive3.py`: `rebaseline_slus`, the ptr-only fallback plan, BUSY_ROWS4.
- `tools/census.py`: BUSY_ROWS4.
- `objects/gameWork.json` (+global_decls/extra_views/drop_views), `objects/D_800814A8.json`,
  `objects/D_800E3D7C.json`, `objects/D_80016000.json`.

## Next objects
See DESIGN section 21. D_80082E80 (290), D_80083498 (284) and D_80083780 (177) are all instances of the entity
record class. The next step is a hand-recovered entity type that supersedes the generated Rec_D_800E3D7C (resolving
its unions), then those three objects and Rec_D_800814A8 onto it.

## Tool calls
Phase 4 used about 45 tool calls.
