# Toolchain fidelity step 4 preparation: recipe-move lander, slus cache re-baseline, natural-C measurement (2026-09-24)

Brief `work/fidelity/STEP4_BRIEF.md`; plan `docs/TOOLCHAIN_FIDELITY_PLAN.md` step 4. Tooling and measurement only:
nothing under `src/`, `include/`, `ledger/`, `config/`, recipes, `tools/maspsx` or `tools/build` was written (one
function + CLI flag ADDED to `tools/verify.py`, no behaviour change for existing callers); no landing, no gate, no git.
Measured at HEAD 559b8f5a (maspsx and tools/build unchanged since ca253080; re-checked at 2d8c9ce3). Per-row data
`work/fidelity/step4/results.jsonl` (72 records); candidates `work/fidelity/step4/cands/`; hand spellings
`work/fidelity/step4/hand/`; staged lane `work/native_lane/r77_step4/` (out/ + cells.jsonl).

## Headline

- **10 of the 72 rows are staged**, each byte-exact at its retail-proven recipe through the STOCK pipeline and
  passing `landing_refusal`; the lander's own dry run re-verifies all 10 (overlay scorer; isolated SLUS link for the
  slus row). Landing them would remove **10 pins** (5 rows: `dungeon/func_800A1984` 2->0, `dungeon/func_8092192C`
  3->0, `main/func_8000F488` 1->0, `town/func_8046FF64` 5->2, `town/func_8032C8B8` 1->0), **1 inline-asm
  statement** (`main/func_800112D8`: `lui %hi / addiu %lo` asm -> `packet_tags = D_80027FD0;`), and move **4 more
  rows with their text unchanged** (rule 2 holds: `dungeon/func_809F6D74` 1 pin and `town/func_8046C048` 5 pins keep
  their pins, `town/func_8032F794` and `slus/w_800423C0` are pin-free). 6 of the 10 are `recipe-switch` trades (the
  pinned text is exact at the target too), 4 are `coherence` trades.
- **Rule 2 (pinned text exact at an evidenced recipe): 7 rows** - the 6 above plus `slus/w_8005A1D0`, already landed
  at cdk (ca253080; exact at 2.8.1 as well; not staged).
- **Genuine-ASPSX small-data model (step-3 decision 3), slus only: 6 more rows become exact** that cannot pass the
  SLUS gate today: `slus/w_8003D92C` (5 -> 0 pins, the sceptic's text), `slus/w_8003FAD4` (3 -> 0), `slus/w_80041588`
  (3 -> 3, externs respelled), `slus/w_80041AB0`, `slus/w_80043CD0` and `slus/w_8004AB7C` (pin-free, maspsx-dependent:
  their `_split_funcaddr_la` / `_sink_call_separated_la` dependence disappears at cdk once the externs are declared at
  their real size). In every case the stock-pipeline miss is the same mechanism: an extern that cc1 sees as small (<= 8 bytes
  at -G8, so it is NOT split) must be addressed absolutely, and maspsx `$gp`-relativises it; the current texts inflate
  such externs (`extern struct { s32 v; s32 pad[2]; } D_X;`, `extern u8 D_X[16];`; `w_80043CD0`'s own comment says
  so) to dodge maspsx, which then makes cdk split them. **Decision 3 unlocks these 6 rows (8 pins, three
  maspsx-pass dependents) and makes the inflated declarations removable.**
- **61 rows have no natural text exact at the evidenced recipe through the stock pipeline** (6 of them are the
  `$gp` rows above; 55 have none under either model in this menu): best-candidate residue <= 2 words on 4 rows, 3-6
  on 12, 7-15 on 26, > 15 on 19; 43 of those 61 best candidates are already pin-free.
  The largest single class is **9 dungeon clones at exactly 12 words, all `reorder-only`**
  (`func_809753B0`, `80AC5958`, `80AEF73C`, `80C69880`, `80C9325C`, `80DBA050`, `80E618E0`, `80EDFF18`,
  `8102F674`): the split pair is retail at cdk/2.8.0, and the 12 words are the prologue order of six parameter
  copies (the sceptic's `func_80AEF73C` reading). One lane on one clone should pay for all nine.
- A near-band second pass (the 16 rows within 6 words: five best candidates at the evidenced cell with every subset of
  the row's own flags) found nothing - a bounded negative; the near rows are allocation/scheduling differences
  (`const-remat`, `reg-rename`, `code-motion`), i.e. port-style lane work at the right recipe.

## Part A - tooling

### A1. `tools/fidelity/land_recipe_move.py` (recipe-move lander, overlay AND slus rows)
`python3 tools/fidelity/land_recipe_move.py <tag> <lane_dir>` is a DRY RUN (verify + plan, nothing written);
`--apply` lands. Input = the lane kit's staging (`out/<container>/<file>.c` + `.c.base_sha`, `cells.jsonl`
`{"id","to","coherence",...}`). One landing at a time (`build_ovl/work/land.lock`); refuses while a codex lane or sweep
runs unless `LAND_ISOLATED=1` (then the overlay gate runs in `build_ovl_gate`, as `land_coherence.sh`).
1. **Verify first, nothing written**: stale `.base_sha` / same recipe / non-stock or non-splitting target skipped;
   candidate byte-exact at the target (overlay: `verify.py` with the cfg overridden in memory; slus: ONE isolated
   SLUS link with every moved TU swapped and re-recipe'd - `tools/fidelity/slus_iso.py`; if the batch fails, the rows
   are tried one by one and the ones that link exact alone are re-linked together); `landing_refusal`; the pinned text
   scored at the target -> trade kind `recipe-switch` (rule 2 holds) or `coherence`.
2. **Snapshot** every file the switch touches (rows.jsonl, recipe_trades.jsonl, the journal, overlay split tables,
   slus.jsonl + slus.build.ninja, tools/build/configure.py, build_slus/build.ninja, each src text).
3. **Record the trades first** (`ledger/recipe_trades.jsonl`: round, date, id, cfg_from/to, kind, how, rule2, evidence
   {fingerprint kinds, census recipe or "retail-proven", neighbour cells}, pins before/after, shas, applied_via, lander,
   why), then **switch**: overlay rows through `common.set_row_cfgs`; slus rows: the TU's `CC_VER` line in
   `tools/build/configure.py` replaced (or added when the TU used `DEFAULT_CC`), `build_slus/build.ninja` regenerated
   by `tools/configure.py` and REQUIRED to differ from the pinned `ledger/splits/slus.build.ninja` only on the moved
   TUs' `ccver`/`ccflags` lines, copied over the pinned copy, `ledger/splits/slus.jsonl` re-derived from it
   (`row_db.edges_of`; the cc edges must differ only on the moved TUs), `ledger/rows.jsonl` cfg/cell/flags +
   `cfg_corrected`. Then the candidate texts go to `src/`, journalled in `ledger/sweeps/recipe_move_<tag>.jsonl`.
4. **Gate**: overlay windows (`gate_all.py`) when an overlay row moved; the SLUS SHA-1 gate (`build_slus.sh`, whose
   new `gate_slus.jsonl` record must be MATCH on a recipe identical to the pinned copy) when a slus row moved.
5. **Any failure after step 2 restores every snapshot** (text, recipe, tables, trades, journal) and re-exports the
   build roots - unlike `land_coherence.sh`, which restores only the recipe of a row whose text did not apply. On
   success the moved slus rows' verify reference is re-baselined (A2), gated on the SLUS gate just run.

Tests `tools/tests/test_land_recipe_move.py` (14): pure text functions (CC_VER replace/insert/duplicate, recipe diff
only on the moved TU's lines, edge diff, splitting targets); a throwaway tree (copies of every file the lander writes,
`build_slus/` as a view whose `tools/` and `src/` point into the copy) with the gates replaced by `true`/`false`:
dry run writes nothing; `--apply` moves an overlay row and a slus row together (tables, configure.py diff = one line,
pinned recipe diff = the TU's ccver line, slus.jsonl edge, trades `coherence`/`recipe-switch`, journal); a SLUS-gate
failure and an overlay-gate failure each restore the tree byte-identically; stale / non-splitting / not-exact
refusals; real verification (no stubs) of `slus/w_8005A1D0` at 2.8.1 through the isolated link, and a non-exact
candidate refused. Every test asserts the real tree unchanged.

**Dry run on the real tree** over `work/native_lane/r77_step4` (the staged set): all 10 rows pass verification; the
plan is printed above; nothing written.

### A2. `tools/verify.py` `rebaseline_slus(ids)` / `--rebaseline-slus IDS [--dry-run]` (added, no behaviour change)
The slus reference (`ledger/cache/slus_obj.json` + `slus_dis/<tu>.txt`) is built once from `raw/` at the registered
recipe, so a deliberate text or recipe change leaves it stale (`slus/w_8005A1D0` reads `length-drift` 43/39 although
the SLUS gate matches). The re-baseline re-derives the NAMED rows only, from the landed `src/` text at the landed
recipe, and only when: (1) the last `ledger/gate_slus.jsonl` record is MATCH on a recipe identical to the pinned copy,
whose sha256 it carries; (2) `build_slus/build.ninja` is the pinned recipe and its cc edge for the TU carries the row's
cell/flags; (3) the gated object `build_slus/build/src/<tu>.o` is older than the image's sha1 stamp; (4) the object
compiled now (`compile_slus`, `include/`) disassembles (objdump -d -r, readable names canonicalised through
config/names.tsv, as the gate's ccproc does) identically to the gated object. Any failed check refuses that row.
Writes are atomic (tmp + os.replace); the entry keeps `src_sha` and gains `rebaselined` {at, cfg, clean_sha, gate_at,
obj_sha_was}. Tests `tools/tests/test_verify_rebaseline_slus.py` (7) on a COPY of the cache: w_8005A1D0 not exact
before, exact after; dry run writes nothing; refused on a NO MATCH / DIFFERS gate record, a pinned recipe changed after
the gate, a gated object that is not the landed text, an object newer than the sha1 stamp, an overlay row.
`python3 tools/verify.py --rebaseline-slus slus/w_8005A1D0 --dry-run` on the real tree: passes all four checks
(obj f89877ba -> 8801f44a); NOT run for real (brief: no ledger writes).

### Supporting tools
- `tools/fidelity/slus_iso.py` - the isolated SLUS link (a private `build_slus/` copy, one TU swapped + re-recipe'd,
  ninja, compared with the baserom; residue = aligned word diff of the TU's functions; restores itself), with the
  genuine-ASPSX small-data model as a measurement switch. Used by the lander and the measurement.
- `tools/fidelity/step4_measure.py` - part B (below); `--table` prints this document's table; `--nearband N` the
  second pass. Tests `tools/tests/test_step4_measure.py` (9: recipes, smallext, inline-asm count, the isolated link's
  calibrate / NO MATCH / restore / 2.8.1 switch, `gp_symbols`).

## Part B - measurement

## Method

### Evidenced recipe per row
- **Overlay rows in a module whose census `best_recipe` splits** (48 of the 55 overlay rows): the census recipe
  (`census`), plus the census cell with the row's own flags (`census_cell+row_flags`: the census label carries only
  cell + `-G`, so a row flag such as `-fno-schedule-insns` would otherwise be dropped silently), plus `2.7.2-cdk` with
  the row's flags where that differs (`cdk+row_flags`, for the three 2.8.0-census rows).
- **Rows without a census recipe** (17 slus, 5 dungeon): `2.7.2-cdk` and `2.8.1`, both with the row's flags (charter
  ruling 2026-09-24 (later) item 1: the cell at which the natural C is exact; exact at both -> the TU neighbours' cell,
  `neighbour_cells` in results.jsonl = the cells of the other rows of the row's module in `ledger/modules.jsonl`).
- `-mmips-as` / `-mno-split-addresses` are dropped: they are the switches that turn a splitting cell off
  (`slus/w_8003E39C` is registered `2.7.2-cdk -mmips-as -G0`).
- **Near-band pass** (`--nearband 6`): rows whose best candidate missed by <= 6 words are re-scored with their five
  best candidates at the evidenced cell with every subset of the row's own flags (a flag is a per-row loan; charter
  rule 4 allows pin-for-flag trades; reported separately).

### Candidates per row (tools/fidelity/step4_measure.py `candidates`)
1. the current text (rule 2: exact at the evidenced recipe = a byte-neutral switch);
2. the current text with every pin erased (`pin_sites.erase_many`, notes cleaned);
3. `tools/xform/t86_symaddr.menu` over EVERY address base in the scored arm (t86's own `bases()` keeps only
   pin-reachable ones; the `page_literal` class has no pin on the page), each with t86's erasure ladder (window pins
   jointly, singly, all pins) - up to 160 texts a row. The menu reaches most page-literal rows (4-39 texts) but not
   all: `dungeon/func_80DFB054` got none (current + erase_all only), `main/func_8000F488`/`F934` only through the hand
   spellings below (their page is the symbol `D_80030000` with a `-=` bump, a shape t86 does not parse);
4. the r77 sceptic lane's hand candidates for its five rows (`work/native_lane/r77_fable_splitaddr/cands`);
5. hand-written natural spellings for rows no generator reaches (`work/fidelity/step4/hand/`): `main/func_8000F488`
   (`D_80030000 - 0x7F4C` is `D_800280B4`, which the file already declares), `main/func_8000F934` (same base),
   `main/func_800112D8` (inline `lui %hi / addiu %lo` asm -> `packet_tags = D_80027FD0;`), `slus/w_80043CD0` (the
   two externs its comment says were oversized for maspsx, declared `s32`);
6. slus only: `smallext` of every text above - the small-data spelling of externs a text inflated past `-G8` so that
   maspsx would not address them through `$gp` (`extern struct { s32 v; s32 pad[2]; } D_X;` read only as `D_X.v`,
   a padded typedef read only as its first field, `extern T D_X[16];` read only as `D_X[0]` -> `extern T D_X;`).
   Scored under the genuine-ASPSX model only (below).

Ties among exact texts: fewest pins, then fewest inline-asm statements (hidden scaffolding the census does not count),
then recipe priority.

### Scoring
- **Overlay rows:** `tools/verify.py` (the per-row aligned scorer in `build_ovl/`), the row's cfg overridden in
  memory (`kitlib.score_at`); nothing under `ledger/` is written.
- **Slus rows:** `tools/fidelity/slus_iso.py` - a private copy of `build_slus/` (8 MB) whose `src/` is a directory of
  symlinks, the TU swapped for the candidate and its `ccver`/`ccflags` lines rewritten, rebuilt by ninja (one TU +
  link + objcopy, ~1 s) and compared with `baserom/slus_006.14`. Residue = aligned word diff of the TU's functions
  against their retail words. `verify.py` cannot score these rows: its slus reference is the pinned object, whose page
  constants are literal immediates, so any symbol spelling reads as ~100 "differences" even when the linked bytes are
  identical (the sceptic's 95/97/187 against 0/7/40 resolved words). Calibration: every view reproduces retail before
  any change (`calibrate()`); `d92c_cdk.c` reproduces the sceptic (stock pipeline 43 words off at cdk; exact under the
  genuine model).
- **Genuine-ASPSX small-data model (slus, measurement only):** the swapped TU's `.extern` lines are withheld from
  maspsx (AZURE_MASPSX_COMPANION wrapper) except the symbols the pinned, retail-exact object addresses through `$gp`
  (`R_MIPS_GPREL16` in `ledger/cache/slus_dis`, i.e. symbols the original TU defined). This is step-3 decision 3's
  behaviour ("every `.extern` absolute; TU-defined small symbols `$gp`"); a text exact only under it does NOT pass the
  SLUS gate today and is never staged.

### Per-row results (best natural candidate at the evidenced recipe; stock pipeline)
`pinned text there` = the current text scored at that recipe (`exact` = rule 2 holds; else its residue). `residue` =
words (overlay: the scorer's aligned total and class; slus: aligned word diff of the linked TU against retail).
`genuine-$gp model` = the best candidate under step-3 decision 3's assembler behaviour (slus only; never staged).

| row | registered | evidenced recipe | pinned text there | best natural candidate | pins | exact | residue | genuine-$gp model (slus) |
|---|---|---|---|---|---|---|---|---|
| dungeon/func_80093898 | `2.7.2` | `2.7.2-cdk-G0` (census) | 4 | `erase_all` | 1 -> 0 | no | 4 length-drift |  |
| dungeon/func_800A1984 | `2.7.2-G0 -fno-schedule-insns` | `2.7.2-cdk-G0` (census) | 15 | `t86:result:allsym` | 2 -> 0 | **yes** |  |  |
| dungeon/func_800B8F90 | `2.7.2-G0` | `2.7.2-cdk-G0` (census) | 14 | `t86:message:opsym@120/all` | 6 -> 0 | no | 10 const-remat |  |
| dungeon/func_800C4A80 | `2.7.2-G0 -fno-expensive-optimizations -fno-cse-follow-jumps` | `2.7.2-cdk-G0 -fno-expensive-optimizations -fno-cse-follow-jumps` (census_cell+row_flags) | 36 | `t86:bounds_page:inplace@91/one89` | 19 -> 18 | no | 40 li-expansion |  |
| dungeon/func_80283F70 | `2.7.2-G0 -fno-strength-reduce` | `2.7.2-cdk-G0 -fno-strength-reduce` (census_cell+row_flags) | 11 | `t86:page:inplace@42/all` | 2 -> 0 | no | 11 length-drift |  |
| dungeon/func_808CB16C | `2.7.2-G0 -fno-strength-reduce -fno-schedule-insns -fno-rerun-cse-after-loop` | `2.7.2-cdk-G0 -fno-strength-reduce -fno-schedule-insns -fno-rerun-cse-after-loop` (census_cell+row_flags) | 15 | `t86:record_base:inplace@60/all` | 3 -> 0 | no | 2 const-remat |  |
| dungeon/func_8092192C | `2.7.2-G0` | `2.7.2-cdk-G0` (census) | exact | `t86:sprite_data_addr:inplace@85/all` | 3 -> 0 | **yes** |  |  |
| dungeon/func_809753B0 | `2.7.2-G0` | `2.8.0-G0` (census) | 12 | `t86:page:inplace@89/one87` | 1 -> 0 | no | 12 reorder-only |  |
| dungeon/func_809F6D74 | `2.7.2-G0 -fno-schedule-insns` | `2.7.2-cdk-G0 -fno-schedule-insns` (census_cell+row_flags) | exact | `current` | 1 -> 1 | **yes** |  |  |
| dungeon/func_80A4AA14 | `2.7.2-G0 -fno-schedule-insns` | `2.8.0-G0 -fno-schedule-insns` (census_cell+row_flags) | 36 | `t86:init_data:opsym@127/one124` | 6 -> 5 | no | 35 hold-set |  |
| dungeon/func_80AC5958 | `2.6.3-G0` | `2.7.2-cdk-G0` (census) | 12 | `t86:page:inplace@87/one85` | 1 -> 0 | no | 12 reorder-only |  |
| dungeon/func_80AEF73C | `2.6.3-G0` | `2.7.2-cdk-G0` (census) | 12 | `hand:ef73c_sym.c` | 1 -> 0 | no | 12 reorder-only |  |
| dungeon/func_80B91054 | `2.7.2` | `2.7.2-cdk` (cdk+row_flags) | 4 | `t86:initial_callback:inplace@98/one93` | 1 -> 0 | no | 5 code-motion |  |
| dungeon/func_80C69880 | `2.6.3-G0` | `2.8.0-G0` (census) | 12 | `t86:page:inplace@87/one85` | 1 -> 0 | no | 12 reorder-only |  |
| dungeon/func_80C9325C | `2.6.3-G0` | `2.7.2-cdk-G0` (census) | 12 | `t86:page:inplace@87/one85` | 1 -> 0 | no | 12 reorder-only |  |
| dungeon/func_80D150D0 | `2.7.2-G0 -fno-schedule-insns` | `2.7.2-cdk-G0 -fno-schedule-insns` (census_cell+row_flags) | 8 | `t86:call_data:inplace@241/one240` | 16 -> 15 | no | 8 broad |  |
| dungeon/func_80DBA050 | `2.6.3-G0` | `2.7.2-cdk-G0` (census) | 12 | `t86:page:inplace@87/one85` | 1 -> 0 | no | 12 reorder-only |  |
| dungeon/func_80DFB054 | `2.7.2` | `2.7.2-cdk` (cdk+row_flags) | 17 | `erase_all` | 1 -> 0 | no | 22 addressing |  |
| dungeon/func_80E07054 | `2.7.2` | `2.7.2-cdk` (cdk+row_flags) | 13 | `t86:callback_page:inplace@83/one83` | 3 -> 2 | no | 13 addressing |  |
| dungeon/func_80E0EAE4 | `2.7.2-G0` | `2.7.2-cdk-G0` (census) | 5 | `t86:angle_page:defsym/one79` | 1 -> 0 | no | 7 code-motion |  |
| dungeon/func_80E618E0 | `2.6.3-G0` | `2.7.2-cdk-G0` (census) | 12 | `t86:page:inplace@87/one85` | 1 -> 0 | no | 12 reorder-only |  |
| dungeon/func_80EDFF18 | `2.6.3-G0` | `2.7.2-cdk-G0` (census) | 12 | `t86:page:inplace@87/one85` | 1 -> 0 | no | 12 reorder-only |  |
| dungeon/func_8102F674 | `2.6.3-G0` | `2.7.2-cdk-G0` (census) | 12 | `t86:page:inplace@87/one85` | 1 -> 0 | no | 12 reorder-only |  |
| dungeon/func_818CEB58 | `2.6.3-G0 -fno-schedule-insns` | `2.7.2-cdk-G0` (census) | 41 | `t86:descriptor_page:opsym@95/one94` | 4 -> 3 | no | 41 hold-set |  |
| dungeon/func_818CFB74 | `2.7.2-G0 -fforce-addr` | `2.7.2-cdk-G0 -fforce-addr` (census_cell+row_flags) | 29 | `t86:template_page:allsym/one363` | 30 -> 26 | no | 29 length-drift |  |
| dungeon/func_818D4E68 | `2.7.2-G0` | `2.7.2-cdk-G0` (census) | 166 | `t86:jump_table:allsym/one201` | 37 -> 35 | no | 166 hold-set |  |
| dungeon/func_818FECCC | `2.6.3-G0 -fno-schedule-insns` | `2.8.1-G0 -fno-schedule-insns` (2.8.1+row_flags) | 40 | `t86:effect_data:opsym@126/one123` | 4 -> 3 | no | 39 hold-set |  |
| dungeon/func_8195EF44 | `2.7.2` | `2.7.2-cdk-G0` (census) | 24 | `t86:page:inplace@96/one75` | 7 -> 6 | no | 15 li-expansion |  |
| dungeon/func_81978428 | `2.7.2` | `2.7.2-cdk-G0` (census) | 15 | `t86:init_page:defsym/one184` | 19 -> 18 | no | 15 broad |  |
| dungeon/func_819B3414 | `2.7.2-G0` | `2.7.2-cdk-G0` (census) | 13 | `t86:render_globals_m:opsym@239/one238` | 35 -> 34 | no | 10 const-remat |  |
| main/func_8000F488 | `2.7.2` | `2.7.2-cdk-G0` (census) | 16 | `hand:symbase` | 1 -> 0 | **yes** |  |  |
| main/func_8000F934 | `2.7.2` | `2.7.2-cdk-G0` (census) | 14 | `hand:symbase` | 1 -> 0 | no | 16 code-motion |  |
| main/func_80014684 | `2.7.2 -fno-expensive-optimizations` | `2.7.2-cdk-G0` (census) | 3 | `t86:dispatch_result:allsym/all` | 2 -> 0 | no | 5 polarity |  |
| slus/w_8003D92C | `2.7.2` | `2.7.2-cdk` (cdk+row_flags) | 35 | `hand:d92c_cdk.c` | 5 -> 0 | no | 43 size-drift | exact (hand:d92c_cdk.c, pins 0) |
| slus/w_8003E39C | `2.7.2-cdk -mmips-as -G0` | `2.7.2-cdk -G0` (cdk+row_flags) | 47 | `t86:slot_data:opsym@72/one38` | 4 -> 3 | no | 49 size-drift | 46 |
| slus/w_8003FAD4 | `2.7.2` | `2.7.2-cdk` (cdk+row_flags) | 15 | `t86:pool_page:inplace@48/all` | 3 -> 0 | no | 15 words | exact (smallext+t86:pool_page:inplace, pins 0) |
| slus/w_80041588 | `2.7.2` | `2.7.2-cdk` (cdk+row_flags) | 5 | `erase_all` | 3 -> 0 | no | 36 words | exact (smallext+current, pins 3) |
| slus/w_80046E38 | `2.6.3 -G0` | `2.7.2-cdk -G0` (cdk+row_flags) | 29 | `hand:6e38_sym.c` | 3 -> 0 | no | 29 size-drift | 29 |
| slus/w_8004E6F4 | `2.6.3` | `2.7.2-cdk` (cdk+row_flags) | 80 | `t86:table_page:defanchor-8007162C/all` | 6 -> 0 | no | 79 size-drift | 79 |
| slus/w_80051228 | `2.7.2` | `2.7.2-cdk` (cdk+row_flags) | 81 | `t86:dest_base:opsym@142/all` | 4 -> 0 | no | 87 size-drift | 81 |
| slus/w_80052144 | `2.7.2 -G0` | `2.7.2-cdk -G0` (cdk+row_flags) | 90 | `t86:event_page:defanchor-80082E60/win` | 18 -> 15 | no | 87 words | 87 |
| town/func_800ABBF8 | `2.7.2-G0 -fno-expensive-optimizations -fno-schedule-insns` | `2.7.2-cdk-G0 -fno-expensive-optimizations -fno-schedule-insns` (census_cell+row_flags) | 2 | `t86:segment_counts:opsym@51/one50` | 15 -> 14 | no | 2 reg-rename |  |
| town/func_800B0930 | `2.7.2` | `2.7.2-cdk` (census_cell+row_flags) | 2 | `erase_all` | 2 -> 0 | no | 12 li-expansion |  |
| town/func_800B0ED0 | `2.7.2-G0` | `2.7.2-cdk-G0` (census) | 1 | `t86:page:opsym@79/one78` | 1 -> 0 | no | 1 broad |  |
| town/func_800B50D4 | `2.7.2-G0` | `2.7.2-cdk-G0` (census) | 4 | `t86:table_page:inplace@20/win` | 4 -> 0 | no | 4 broad |  |
| town/func_800BB264 | `2.7.2` | `2.7.2-cdk-G0` (census) | 5 | `t86:state:defsym/one28` | 3 -> 2 | no | 7 li-expansion |  |
| town/func_800BC8AC | `2.7.2-G0 -fno-schedule-insns -fno-rerun-cse-after-loop` | `2.7.2-cdk-G0 -fno-schedule-insns -fno-rerun-cse-after-loop` (census_cell+row_flags) | 8 | `t86:init_data:opsym@243/win` | 12 -> 10 | no | 8 reorder-only |  |
| town/func_800C3800 | `2.6.3-G0` | `2.7.2-cdk-G0` (census) | 2 | `erase_all` | 1 -> 0 | no | 2 length-drift |  |
| town/func_8032DE74 | `2.7.2` | `2.7.2-cdk-G0` (census) | 4 | `t86:dispatch_result:inplace@12/one7` | 1 -> 0 | no | 6 const-remat |  |
| town/func_8032E720 | `2.6.3-G0 -fno-schedule-insns2 -fno-rerun-cse-after-loop -fno-strength-reduce` | `2.7.2-cdk-G0 -fno-schedule-insns2 -fno-rerun-cse-after-loop -fno-strength-reduce` (census_cell+row_flags) | 1 | `t86:page:defsym/one119` | 3 -> 2 | no | 4 code-motion |  |
| town/func_8032E8C0 | `2.6.3-G0` | `2.7.2-cdk-G0` (census) | 4 | `erase_all` | 1 -> 0 | no | 5 li-expansion |  |
| town/func_8033077C | `2.7.2-G0 -fno-strength-reduce -O1` | `2.7.2-cdk-G0 -fno-strength-reduce -O1` (census_cell+row_flags) | 12 | `erase_all` | 7 -> 0 | no | 10 length-drift |  |
| town/func_8046C048 | `2.7.2-G0 -fno-schedule-insns` | `2.7.2-cdk-G0 -fno-schedule-insns` (census_cell+row_flags) | exact | `current` | 5 -> 5 | **yes** |  |  |
| town/func_8046FF64 | `2.7.2-G0` | `2.7.2-cdk-G0` (census) | 6 | `t86:status_or_base:allsym` | 5 -> 2 | **yes** |  |  |
| town/func_8051F4AC | `2.7.2` | `2.7.2-cdk-G0` (census) | 4 | `erase_all` | 1 -> 0 | no | 6 li-expansion |  |
| town/func_808213CC | `2.7.2` | `2.7.2-cdk-G0` (census) | 17 | `t86:image:opsym@51/one73` | 2 -> 1 | no | 16 li-expansion |  |
| dungeon/func_800938EC | `2.7.2-G0` | `2.7.2-cdk-G0` (census) | 5 | `current` | 0 -> 0 | no | 5 code-motion |  |
| dungeon/func_80B97094 | `2.6.3` | `2.8.1` (2.8.1+row_flags) | 17 | `current` | 0 -> 0 | no | 17 addressing |  |
| dungeon/func_81917234 | `2.7.2` | `2.7.2-cdk-G0` (census) | 3 | `current` | 0 -> 0 | no | 3 reorder-only |  |
| main/func_800112D8 | `2.7.2 -fno-strength-reduce` | `2.7.2-cdk -fno-strength-reduce` (census_cell+row_flags) | exact | `hand:inline_asm_to_symbol` | 0 -> 0 | **yes** |  |  |
| slus/code | `2.7.2` | `2.7.2-cdk` (cdk+row_flags) | 61 | `current` | 0 -> 0 | no | 61 size-drift | 61 |
| slus/konami_runtime_w_8003B7C8 | `2.7.2` | `2.7.2-cdk` (cdk+row_flags) | 5 | `current` | 0 -> 0 | no | 5 size-drift | 5 |
| slus/w_80041AB0 | `2.7.2` | `2.7.2-cdk` (cdk+row_flags) | 9 | `current` | 0 -> 0 | no | 9 words | exact (smallext+current, pins 0) |
| slus/w_800423C0 | `2.7.2` | `2.7.2-cdk` (cdk+row_flags) | exact | `current` | 0 -> 0 | **yes** |  | exact (current, pins 0) |
| slus/w_80043CD0 | `2.7.2` | `2.7.2-cdk` (cdk+row_flags) | 9 | `hand:small_externs` | 0 -> 0 | no | 5 size-drift | exact (hand:small_externs, pins 0) |
| slus/w_80048224 | `2.7.2` | `2.7.2-cdk` (cdk+row_flags) | 9 | `current` | 0 -> 0 | no | 9 words | 9 |
| slus/w_8004A6C0 | `2.7.2` | `2.7.2-cdk` (cdk+row_flags) | 4 | `current` | 0 -> 0 | no | 4 size-drift | 4 |
| slus/w_8004AB7C | `2.7.2` | `2.7.2-cdk` (cdk+row_flags) | 10 | `current` | 0 -> 0 | no | 10 size-drift | exact (smallext+current, pins 0) |
| slus/w_8005A1D0 | `2.7.2-cdk` | `2.8.1` (2.8.1+row_flags) | exact | `current` | 0 -> 0 | **yes** |  | exact (current, pins 0) |
| town/func_8032F794 | `2.7.2 -fno-schedule-insns2` | `2.7.2-cdk -fno-schedule-insns2` (census_cell+row_flags) | exact | `current` | 0 -> 0 | **yes** |  |  |
| main/func_80013B18 | `2.7.2-G0` | `2.7.2-cdk-G0` (census) | 33 | `t86:global_data:opsym@44/one42` | 1 -> 0 | no | 46 hold-set |  |
| town/func_8032C8B8 | `2.7.2` | `2.7.2-cdk-G0` (census) | 2 | `t86:dispatch_result:allsym` | 1 -> 0 | **yes** |  |  |


### Staged (work/native_lane/r77_step4/cells.jsonl)
| row | from | to | pins | text | trade | evidence |
|---|---|---|---|---|---|---|
| dungeon/func_800A1984 | `2.7.2-G0 -fno-schedule-insns` | `2.7.2-cdk-G0` | 2 -> 0 | t86 `result` allsym | coherence | census 2.7.2-cdk-G0; lo_other_reg:2 |
| dungeon/func_8092192C | `2.7.2-G0` | `2.7.2-cdk-G0` | 3 -> 0 | t86 `sprite_data_addr` in place | recipe-switch | census; interleaved:1 |
| dungeon/func_809F6D74 | `2.7.2-G0 -fno-schedule-insns` | `2.7.2-cdk-G0 -fno-schedule-insns` | 1 -> 1 | unchanged | recipe-switch | census cell + row flag |
| main/func_8000F488 | `2.7.2` | `2.7.2-cdk-G0` | 1 -> 0 | hand: `table_base = (s32)D_800280B4;` (page `D_80030000 - 0x7F4C`), unused `.set` dropped | coherence | census; interleaved:1 |
| main/func_800112D8 | `2.7.2 -fno-strength-reduce` | `2.7.2-cdk -fno-strength-reduce` | 0 -> 0 (-1 inline asm) | hand: inline `lui/addiu` asm -> `packet_tags = D_80027FD0;` | recipe-switch | census cell + row flag (not exact at `2.7.2-cdk-G0`: 18) |
| town/func_8046C048 | `2.7.2-G0 -fno-schedule-insns` | `2.7.2-cdk-G0 -fno-schedule-insns` | 5 -> 5 | unchanged | recipe-switch | census cell + row flag |
| town/func_8046FF64 | `2.7.2-G0` | `2.7.2-cdk-G0` | 5 -> 2 | t86 `status_or_base` allsym | coherence | census; high_in_slot/lo_other_reg/slot_lo |
| town/func_8032F794 | `2.7.2 -fno-schedule-insns2` | `2.7.2-cdk -fno-schedule-insns2` | 0 -> 0 | unchanged | recipe-switch | census cell + row flag (-G8; `2.7.2-cdk-G0`: 4) |
| town/func_8032C8B8 | `2.7.2` | `2.7.2-cdk-G0` | 1 -> 0 | t86 `dispatch_result` allsym | coherence | census; weak tier (slot_lo only) |
| slus/w_800423C0 | `2.7.2` | `2.7.2-cdk` | 0 -> 0 | unchanged | recipe-switch | exact at cdk AND 2.8.1 -> neighbours' cell (entity_state.c: cdk 14, 2.7.2 8, 2.8.1 3) |

Five of the ten land at the census CELL with the row's own flag(s), not at the census label (the label is cell + `-G`
only): the orchestrator decides whether "the census recipe" means the label or the cell. `town/func_8032C8B8` is a
weak-tier row (the owner's step-2 decision (3): weak rows wait for step 1 - step 1 is done; staged, flagged).

### Residue by class (the 61 rows not exact through the stock pipeline; best candidate)
- **Prologue parameter-copy order, 9 dungeon clones, 12 words each** (listed above): one mechanism.
- **slus, the `$gp` extern model, 6 rows** (listed above): exact under decision 3.
- **slus maspsx-dependent rows not yet exact at cdk under either model** (step 1's attributed pass in brackets):
  `w_8004A6C0` / `konami_runtime_w_8003B7C8` (`_fold_selfinc_la`, 4-5 words: retail folds `%lo` into a
  self-incremented HIGH register), `w_80048224` (`_prefer_lui_over_sll_branch_delay`, 9), `code` (61 at cdk, 170 at
  2.8.1; step 1: the `$gp` model + delay slots). Retail's shapes are cdk-like; these texts are not yet the cdk source.
- **slus pinned rows far off at cdk** (`w_8003E39C` 49 - tuned for `-mmips-as`; `w_80046E38` 29; `w_8004E6F4` 79;
  `w_80051228` 87; `w_80052144` 87): re-tuning at cdk (the sceptic's per-row notes stand).
- **Overlay near band (<= 6 words, 16 rows)**: `const-remat`, `reg-rename`, `code-motion`, `li-expansion` - lane work
  at the evidenced recipe; e.g. `town/func_800B0ED0` is 1 word (cdk narrows `unk_34` to `lhu`, retail `lw`).
- **Large pinned rows** (`dungeon/func_818D4E68` 37 pins, `func_819B3414` 35, `func_818CFB74` 30, `func_800C4A80`
  19, `func_81978428` 19, `town/func_800ABBF8` 15): no natural text in reach; residue recorded.

## Findings the orchestrator must act on

1. **`ledger/splits/slus.jsonl` is stale for `slus/w_8005A1D0`** (still `"ccver":"2.7.2"`; the pinned recipe and
   rows.jsonl say `2.7.2-cdk`). `tools/registry.py` rebuilds rows.jsonl FROM slus.jsonl, so a registry run would
   silently revert that landing's recipe in the row table. The lander re-derives slus.jsonl from the pinned recipe on
   every slus move (and logs the drift it repairs); until one runs, `python3 -c` over `row_db.edges_of` (or the
   lander's first slus move) fixes it.
2. **Re-baseline `slus/w_8005A1D0`'s verify reference**: `python3 tools/verify.py --rebaseline-slus slus/w_8005A1D0`
   (dry run passes all four checks). Every later slus move does it itself.
3. **Decision 3 (`$gp` small externs)** now has a per-row price: 6 slus rows / 8 pins (3 of them maspsx-pass
   dependents) are exact under it and not otherwise; the natural texts are in `work/fidelity/step4/cands/slus/*.gp.*.c`.
4. **Staging policy questions**: (a) five staged rows move to the census CELL with their own flags, not the census
   label; (b) four staged rows move with their TEXT unchanged (byte-neutral switches toward the retail-proven
   recipe): `func_809F6D74` (1 pin) and `func_8046C048` (5 pins) keep their pins, and `slus/w_800423C0` (literals
   `0x80012094` / `0x80010000` / `0x80012096`) and `town/func_8032F794` (`0x80020000`) keep their page constants -
   landing them is a recipe CORRECTION, not a cleanup: they stay `cell_imitation` residue, now at the right cell,
   where a natural spelling can be worked (none of their 9 / 4 menu texts was exact); (c) `town/func_8032C8B8` is weak
   tier; (d) `main/func_800112D8` keeps its `__asm__(".set D_80027FD0, ...")` symbol definition (dropping it too is
   scorer-exact but unproven in the window link; 90 files use the same `.set` convention).
5. `slus/w_8003D92C`'s wrong ADDR_ALIAS comment (plan step 4) goes with its landing, which waits on decision 3.

## Reproduce
```
python3 tools/fidelity/step4_measure.py --workers 6                    # 72 rows, ~13 min; stages at the end
python3 tools/fidelity/step4_measure.py --rows <slus ids> --redo       # re-measure rows (hand/ files are candidates)
python3 tools/fidelity/step4_measure.py --nearband 6                   # the flag-subset second pass
python3 tools/fidelity/step4_measure.py --table                        # the table above
python3 tools/fidelity/land_recipe_move.py step4 work/native_lane/r77_step4          # dry run
python3 -m unittest tools/tests/test_land_recipe_move.py tools/tests/test_verify_rebaseline_slus.py tools/tests/test_step4_measure.py
```
