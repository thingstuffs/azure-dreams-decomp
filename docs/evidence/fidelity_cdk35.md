# Fidelity: the 35 "genuine-exact at cdk, not through maspsx" rows (census re-derivation follow-up)

Measurement only. Nothing under src/, include/, ledger/, config/, tools/maspsx, tools/gate, tools/build or
toolchain/ was edited, and no gate or landing was run. Git: one read-only `git status --short` at the end, a
slip against the brief; nothing was staged or committed. Scratch and outputs: `work/fidelity/cdk35/`.
Tool: `tools/fidelity/cell_retail_check.py` (+ `tools/tests/test_cell_retail_check.py`, 6 tests).

## Headline

**The premise does not hold: none of the 35 rows is retail-exact at `2.7.2-cdk` under genuine ASPSX either.**
At the cdk cfg, genuine ASPSX 2.67/2.77/2.79/2.81/2.86 produce the *same object as maspsx* on all 35 rows, and
both miss retail by the same number of words (2-357). There is no maspsx behaviour to attribute: no pass fires
and no dial matters (see "Ablation"). The "genuine-exact" label came from aspsx_diff's `exact_versions` field.
That field means *genuine object == maspsx object*. It equals "genuine reproduces retail" only when the maspsx
leg is itself retail-exact. That is true at a row's registered recipe (the gate). It is not true at a trial cell.
On these 35 rows at cdk, `maspsx_exact` is false and `exact_versions` lists all five versions.
`work/fidelity/cdk35_attrib.json` shows the same thing: entry[3] is the five-version list and the attribution
is empty, because aspsx_diff attributes only versions that differ from maspsx. The script that produced
`work/fidelity/census_redo_results.json` is not in the repo. A search of tools/, docs/, work/fidelity/ and the
r77_cdk362 and r77_cdkmod lane directories found only the plan's mention. So the criterion is inferred, from two
facts: `cdk35_attrib.json` entry[3] is the five-version list with an empty attribution, and every one of the 35
has `maspsx_exact: false` with a full `exact_versions` at cdk.

The differences are cc1 codegen, not assembly. **For 16 of the 35, a natural-C respelling built from 2 mechanisms
makes them retail-exact at cdk, both through maspsx and under genuine ASPSX 2.67-2.86** (candidates in
`work/fidelity/cdk35/cands/`). All 16 are currently `maspsx_dependent` (`_maybe_unfill_return_delay`) at their
2.8.x cells. The other 19 need lane work or stay at their cells.

Consequence for the census re-derivation (measured over all 214 rows of the 23 modules, below): 16 of the 22
dungeon modules re-derived to cdk contain at least one of the 35. Their `rederived.basis` ("every row
genuine-exact at 2.7.2-cdk") therefore overstates the evidence. The 153 moved rows themselves are sound: they
are maspsx-exact at cdk, the gate checked them, and at their new registered recipe genuine == maspsx is
meaningful.

## 1. Where an overlay row's maspsx arguments come from

The chain, in order, for the per-row scorer (`tools/gate/overlay_func_compare.py`; aspsx_diff drives the
`build_ovl/` mirror of the same code):

1. **Fixed arguments** from `match.build_text` (`tools/gate/match.py` ~l.433-440):
   `--aspsx-version=<aspsx>` (the caller passes `2.79`), `--dont-force-G0`, `-I` paths, `-EL -march=r3000 -G8`,
   then the row's as-flags string. `$AZURE_MASPSX` can replace the driver for measurement runs. `MASPSX_LEAD*`
   environment switches are stripped.
2. **Row as-flags**: `overlay_func_compare.default_as_flags` re-exports `tools/gate/overlay_as_flags.py`
   `default_as_flags` -> `resolve_as_flags`. The ladder runs: records in `config/overlays/<overlay>.as_flags.jsonl`
   (by synthetic row key, then `(family, foff)` identity, then an unambiguous bare name), then
   `match.DEFAULT_FUNC_AS_FLAGS` (derived from `tools/configure.py` `AS_FLAGS`, the main-EXE route), then "".
3. **Per-container default, folded in after the ladder, for every row of the family**:
   `resolve_as_flags` returns `_merge_container_default(flags, family)` (`overlay_as_flags.py` l.529), and
   `_CONTAINER_DEFAULT_AS_FLAGS = {"dungeon": "--fill-shadowed-return-delay"}` (l.423). **This is what adds
   `--fill-shadowed-return-delay` to every dungeon row**, although no as_flags.jsonl record names it (the
   2026-09-06 "general return delay" install; its comment records that the switch moved only 2 rows' bytes in the
   corpus when it was installed).
4. **Evidence env**: `overlay_evidence.evidence_env_with_candidate` sets the noreturn and sibcall evidence the
   cc1 wrapper reads. It changes the cc1 input, not the maspsx argv.
5. **No per-cell defaults exist.** Nothing keys a maspsx argument on the compiler cell. The epilogue helpers
   (`_maybe_unfill_return_delay`, `_unfill_via_load_delay`) fire on the *shape* of the cc1 output: gcc's
   `.set noreorder` filled return, which only the 2.8.x/2.9x cells emit. They fire on no cdk output (cdk emits a
   reorder-mode `j $31`).

`aspsx_diff.py --asflags ""` bypasses step 2-3 entirely (the override replaces `default_as_flags`), which is why
it removed the flag; it did not help because the flag is inert here (next section).

Side note: the `build_ovl/` mirrors still carry the literal `2.56`: `build_ovl/tools/match.py` has it as the CLI
default, and `build_ovl/work/g3/overlay_func_compare.py` has it at l.597. The `tools/gate/` copies say `2.79`.
This is harmless for aspsx_diff, which passes `"2.79"` explicitly, and the ASPSX trial showed 2.56 and 2.79 are
byte-identical on all 6,767 rows. It is a stale mirror nonetheless.

## 2. Attribution per row (ablation)

Instrument: `cell_retail_check.py` runs aspsx_diff's own `process_row` (the scorer pipeline, traced maspsx, and
the genuine legs) at the trial cfg. The trial cfg is the registered cfg with only the cell replaced, keeping -G0
and every flag. The tool also records what aspsx_diff does not surface: the maspsx leg's positional word
differences against retail, and each genuine version's direct relocation-resolved difference against retail.
`--asflags-variants` re-runs the maspsx leg with each row as-flag dropped and with all of them dropped.

Controls:
- `--registered` on the 35 rows: all maspsx-exact, 0 differing words.
- The 14 rows at 2.6.3/2.7.2: genuine 0 differing words at the registered cfg (80A4AA14 has 3 masked
  relocations and equals the scorer-exact maspsx leg).
- The 21 rows at 2.8.x/2.9x: genuine 3-5 words off at the registered cfg, which is the known epilogue dependence.
  All 21 are in `ledger/maspsx_dependence.jsonl` with cause `_maybe_unfill_return_delay`.
- At cdk, 177 of the 214 module rows come out genuine retail-exact.

So the instrument reports exactness when it is there. Outputs: `check_cdk.jsonl`, `check_registered.jsonl`,
`check_modules_cdk.jsonl`, `check_cands_cdk.jsonl`.

Ablation result (all 35, at cdk):
- **fired passes/helpers: none** on any row.
- **`--fill-shadowed-return-delay` dropped: no change** on any row.
- **`--expand-div`** (func_7FFE7804's own dial) is load-bearing the other way: dropping it takes the row from 43
  to 88 differing words.
- **genuine == maspsx** at every version 2.67-2.86 on every row. 2.56 cannot assemble cdk's `%hi/%lo`.
  aspsx_diff's attribution therefore has no version to explain.

What the words are (maspsx diff positions, disassembled):
- **A, lo-fold (7 rows, plus 810AF0B4)**: `D_8006DE24[i * 20 + 0x12]`.
  - cdk folds the +18 into the address: `addiu $3,%lo(D_8006DE24+18)` / `lbu $3,0($2)`.
  - Retail keeps the offset on the load: `%lo(D_8006DE24)` / `lbu $3,18($2)`, the 2.8.0 shape.
  - A 20-byte record type gives retail's words at cdk: `typedef struct { u8 pad[0x12]; u8 kind; u8 pad2; }`,
    accessed as `D_8006DE24[i].kind`.
- **B, label-array switch index (8 rows, plus 810AF0B4)**: `if ((u32)(x - 1) >= N) ...; goto *D_801708xx[(u32)(x - 1)];`.
  - cdk re-derives `x - 1` twice and folds the `-1` into the table base: `%lo(D_80170808) - 4`, with swapped
    `andi/addiu/sltiu` registers.
  - Computing the index once, `u32 idx = x - 1; if (idx >= N) ...; goto *D_801708xx[idx];`, gives retail's words.
- **C, small cc1 differences (3 rows, open)**:
  - 80CC266C: retail tests `andi v0,s1,0xffff` before `beqz`. cdk drops the mask because it knows
    `reference_found` is 0 or 1.
  - 80CC2828: one `sw`/`sh` store pair comes out in swapped order.
  - 80CC2494 (a 2.7.2 row): a 7-word `li`/branch ordering difference.
- **D, rows at non-splitting cells with no split fingerprint (12 rows)**: all 11 of `ovl_7804.c`'s 2.6.3/2.7.2
  rows and 80976E28. Each is 21-122 words off at cdk and genuine-exact at its registered 2.6.3/2.7.2 cell.
  Step 2 records `ovl_7804.c` with fp = 0 on 12 addressing rows and a census recipe of 2.7.2-G0.
- **E, large (4 rows)**:
  - 80A49908: 117 words off.
  - 818AAE60: 357 words off.
  - 80BEE104: 113 words off (registered at 2.95.2).
  - 80A4AA14: 67 words off (registered at 2.7.2 `-fno-schedule-insns`, and it shows the split fingerprint).
  These are candidates for the "post-970404 codegen" group of step 1c, or for rewrites.

| row | module | registered cfg | words | maspsx vs retail @cdk | genuine 2.79 vs retail @cdk | genuine == maspsx @cdk | genuine 2.79 vs retail @registered | split fp | class | natural-C candidate @cdk |
|---|---|---|---|---|---|---|---|---|---|---|
| dungeon/func_7FFE7804 | ovl_7804.c | `2.6.3-G0` | 122 | 43 | 43 | 5/5 | 0 | no | D non-split cell | - |
| dungeon/func_7FFE79F4 | ovl_7804.c | `2.7.2-G0` | 124 | 122 | 122 | 5/5 | 0 | no | D non-split cell | - |
| dungeon/func_7FFE7CBC | ovl_7804.c | `2.7.2-G0` | 65 | 21 | 21 | 5/5 | 0 | no | D non-split cell | - |
| dungeon/func_7FFE8154 | ovl_7804.c | `2.7.2-G0` | 108 | 106 | 106 | 5/5 | 0 | no | D non-split cell | - |
| dungeon/func_7FFE89B0 | ovl_7804.c | `2.7.2-G0` | 118 | 118 | 118 | 5/5 | 0 | no | D non-split cell | - |
| dungeon/func_7FFE9150 | ovl_7804.c | `2.7.2-G0` | 110 | 42 | 42 | 5/5 | 0 | no | D non-split cell | - |
| dungeon/func_7FFE99BC | ovl_7804.c | `2.7.2-G0` | 92 | 45 | 45 | 5/5 | 0 | no | D non-split cell | - |
| dungeon/func_7FFEA1CC | ovl_7804.c | `2.7.2-G0` | 93 | 45 | 45 | 5/5 | 0 | no | D non-split cell | - |
| dungeon/func_7FFEA9D4 | ovl_7804.c | `2.7.2-G0 -fno-schedule-insns` | 103 | 87 | 87 | 5/5 | 0 | no | D non-split cell | - |
| dungeon/func_7FFEB1CC | ovl_7804.c | `2.7.2-G0` | 95 | 45 | 45 | 5/5 | 0 | no | D non-split cell | - |
| dungeon/func_7FFEBA30 | ovl_7804.c | `2.7.2-G0` | 113 | 111 | 111 | 5/5 | 0 | no | D non-split cell | - |
| dungeon/func_80976E28 | ovl_7f7db800.c | `2.6.3-G0` | 82 | 49 | 49 | 5/5 | 0 | no | D non-split cell | - |
| dungeon/func_80977248 | ovl_7f7db800.c | `2.8.0-G0` | 531 | 2 | 2 | 5/5 | 3 | yes | A lo-fold | exact (maspsx + genuine 0/0) |
| dungeon/func_809A1D60 | ovl_7f7b1800.c | `2.8.0-G0` | 350 | 2 | 2 | 5/5 | 3 | yes | A lo-fold | exact (maspsx + genuine 0/0) |
| dungeon/func_80A49170 | ovl_7f709800.c | `2.8.0-G0` | 280 | 2 | 2 | 5/5 | 3 | yes | A lo-fold | exact (maspsx + genuine 0/0) |
| dungeon/func_80A49908 | ovl_7f709800.c | `2.8.0-G0` | 202 | 117 | 117 | 5/5 | 3 | yes | E large | - |
| dungeon/func_80A4AA14 | ovl_7f709800.c | `2.7.2-G0 -fno-schedule-insns` | 68 | 67 | 67 | 5/5 | 0 (+3 masked) | yes | E large | - |
| dungeon/func_80A9B67C | ovl_7f6b5800.c | `2.8.0-G0` | 462 | 4 | 4 | 5/5 | 3 (+1 masked) | yes | B jtbl index | exact (maspsx + genuine 0/1 masked) |
| dungeon/func_80BC21DC | ovl_7f58f800.c | `2.8.0-G0` | 379 | 4 | 4 | 5/5 | 3 | yes | B jtbl index | exact (maspsx + genuine 0/0) |
| dungeon/func_80BEB814 | ovl_7f565800.c | `2.8.0-G0` | 344 | 4 | 4 | 5/5 | 3 | yes | B jtbl index | exact (maspsx + genuine 0/0) |
| dungeon/func_80BEE104 | ovl_7f565800.c | `2.95.2-G0 -fno-expensive-optimizations` | 123 | 113 | 113 | 5/5 | 3 (+1 masked) | yes | E large | - |
| dungeon/func_80C6B878 | ovl_7f4e7800.c | `2.8.0-G0` | 383 | 2 | 2 | 5/5 | 3 (+5 masked) | yes | A lo-fold | exact (maspsx + genuine 0/5 masked) |
| dungeon/func_80CBEF98 | ovl_7f493800.c | `2.8.1-G0` | 286 | 2 | 2 | 5/5 | 3 | yes | A lo-fold | exact (maspsx + genuine 0/0) |
| dungeon/func_80CC0398 | ovl_7f493800.c | `2.8.1-G0` | 305 | 4 | 4 | 5/5 | 3 | yes | B jtbl index | exact (maspsx + genuine 0/0) |
| dungeon/func_80CC2494 | ovl_7f493800.c | `2.7.2-G0` | 68 | 7 | 7 | 5/5 | 0 | no | C small cc1 | - |
| dungeon/func_80CC266C | ovl_7f493800.c | `2.8.1-G0` | 111 | 2 | 2 | 5/5 | 3 | yes | C small cc1 | - |
| dungeon/func_80CC2828 | ovl_7f493800.c | `2.8.1-G0` | 166 | 2 | 2 | 5/5 | 5 | yes | C small cc1 | - |
| dungeon/func_80D6671C | ovl_7f3eb800.c | `2.8.0-G0` | 357 | 4 | 4 | 5/5 | 3 | yes | B jtbl index | exact (maspsx + genuine 0/0) |
| dungeon/func_80D68308 | ovl_7f3eb800.c | `2.8.0-G0` | 460 | 2 | 2 | 5/5 | 3 | yes | A lo-fold | exact (maspsx + genuine 0/0) |
| dungeon/func_80EB59A4 | ovl_ed506c.c | `2.8.0-G0` | 330 | 4 | 4 | 5/5 | 3 | yes | B jtbl index | exact (maspsx + genuine 0/0) |
| dungeon/func_80EB6FC8 | ovl_7f29b800.c | `2.8.0-G0` | 341 | 4 | 4 | 5/5 | 3 | yes | B jtbl index | exact (maspsx + genuine 0/0) |
| dungeon/func_81007034 | ovl_7f14b800.c | `2.8.1-G0` | 299 | 2 | 2 | 5/5 | 3 | yes | A lo-fold | exact (maspsx + genuine 0/0) |
| dungeon/func_810AF0B4 | ovl_7f0a3800.c | `2.8.0-G0` | 362 | 6 | 6 | 5/5 | 3 | yes | A+B | exact (maspsx + genuine 0/0) |
| dungeon/func_812A67A4 | ovl_7eeab800.c | `2.8.0-G0` | 347 | 4 | 4 | 5/5 | 3 | yes | B jtbl index | exact (maspsx + genuine 0/0) |
| dungeon/func_818AAE60 | ovl_18ca83c.c | `2.8.0-G0` | 434 | 357 | 357 | 5/5 | 3 | yes | E large | - |

(Columns: words = the maspsx leg's unit; "genuine == maspsx" = aspsx_diff's `exact_versions` count;
"split fp" = the row is in `ledger/split_fingerprint_rows.jsonl`; "masked" = relocations the direct resolver
cannot place.)

## 3. Proposed change, and byte-neutrality

**No maspsx or dial change is proposed, because none can work.** At cdk, maspsx already equals genuine ASPSX on
all 35 rows. A maspsx change that made them exact would be a new non-genuine behaviour (fidelity debt), not a
fix. Keying `--fill-shadowed-return-delay` or the epilogue helpers to the 2.8.x cells would be byte-neutral but
pointless: the flag is inert on all 35 at cdk and the helpers do not fire on cdk output.

**The change that works is source-level (step 4, a recipe move with natural C).** 16 candidate texts are in
`work/fidelity/cdk35/cands/func_<X>.c`, one mechanism each:
- A: the record-type declaration plus `.kind`.
- B: the index computed once.

At `2.7.2-cdk-G0` all 16 are scorer-exact through maspsx and genuine retail-exact under 2.67-2.86:
- 14 rows: 0/0 against retail.
- func_80A9B67C: 0 differing, 1 masked relocation.
- func_80C6B878: 0 differing, 5 masked relocations.

In both masked cases the genuine object equals the scorer-exact maspsx object (`check_cands_cdk.jsonl`). Pin
counts are unchanged (4 / 3 / 1 on 80977248 / 80D68308 / 81007034, 0 elsewhere). The 80CC0398 candidate's
indentation is cosmetic and needs tidying before landing. The class-A candidates each carry a local copy of the
same `ItemDef20` typedef (8 files). A landing lane should move it to a shared record header under include/,
which this measurement could not touch, and should not treat the per-file typedef as the final shape. A landing would move the 16 rows off
`maspsx_dependent` (`_maybe_unfill_return_delay`).

Byte-neutrality:
- Each candidate is its row's own translation unit (`src/dungeon/func_<X>.c`). A landing changes only that row's
  text and recipe, and its words equal retail (measured). No other row's input changes.
- The windows gate of `tools/fidelity/land_recipe_move.py` is the proof of record at landing.
- No maspsx, config or dial change is involved, so no other landed row can move.

## 4. The census re-derivation, re-measured (all 214 rows of the 23 modules, at cdk)

| | rows |
|---|---|
| genuine retail-exact at cdk (170 clean + 7 exact with masked relocations only, genuine == scorer-exact maspsx) | 177 |
| not exact at cdk under either assembler (the 35) | 35 |
| town/ovl_3fe0d0.c (not re-derived): 8047E0D8 maspsx-exact only (genuine 1 word off); 8047E1C0 23 words off | 2 |

Per re-derived dungeon module (the 22):
- **6 are genuinely all-cdk-exact**: 7f637800, 7f5e3800, 7f3c1800, 7f247800, 10a30bc, 7e6b7800.
- **16 contain 1-11 of the 35.**
- Once the 16 candidates land, 10 of those 16 become all-cdk-exact: 7f7b1800, 7f6b5800, 7f58f800, 7f4e7800,
  7f3eb800, ed506c, 7f29b800, 7f14b800, 7f0a3800, 7eeab800. That makes 16 of 22 in total.
- **6 would remain mixed**:
  - `ovl_7804.c`: 11 of 13 rows off (D).
  - `ovl_7f7db800.c`: 80976E28 (D).
  - `ovl_7f709800.c`: 80A49908 and 80A4AA14 (E).
  - `ovl_7f565800.c`: 80BEE104 (E).
  - `ovl_7f493800.c`: 80CC2494, 80CC266C and 80CC2828 (C).
  - `ovl_18ca83c.c`: 818AAE60 (E).

`ovl_7804.c` stands out. Its original census recipe was 2.7.2-G0. 11 of its 13 rows are genuine-exact at
2.6.3/2.7.2, and step 2 found no split fingerprint in the module. The other 2 rows (func_7FFE7BE8 and
func_7FFEF6A8) are now at cdk. They are in step 1c's cdk-exact list and were epilogue-dependent at 2.8.1, so a
plain revert to 2.7.2-G0 would leave them nonconforming with no cell to go to. With the current texts the module
is genuinely mixed: 11 rows need the 2.7.2 shape and 2 need the cdk shape. The re-derivation's "every row"
basis is false here. Under the owner's "one compiler per TU" rule (as applied to town/ovl_3fe0d0.c), one side's
texts must be re-derived. The evidence (fp = 0 on 12 addressing rows) points at re-deriving the 2, not the 11.

## Instrument hazard (for any future trial-cell run)

`exact_versions` / `genuine[v].exact` in `work/fidelity/aspsx_diff.jsonl` compare genuine with maspsx. Read them
as retail evidence only together with `maspsx_exact: true`. At a trial cell, use `genuine[v].retail == [0, 0]`
(the direct resolver). `cell_retail_check.py` does this by default: `genuine_retail_exact` accepts masked words
only when the genuine object also equals a scorer-exact maspsx leg. `aspsx_diff.py` itself was not edited,
because it feeds `tool_fingerprint()` and an edit would invalidate the 6,767-row journal.

## Decisions for the owner

1. **Correct the census basis.**
   - Keep cdk for the 6 clean modules.
   - Hold or annotate the other 16: either land the 16 candidates first (10 more modules then satisfy "every
     row") or mark them mixed.
   - `ovl_7804.c` is a mixed module (11 rows 2.7.2-shape, 2 cdk-shape). Choose which side to re-derive; the
     evidence favours re-deriving the 2 cdk rows at 2.7.2 rather than the 11 at cdk (section 4).
   - Rename `census_redo_needdial.json` / "needdial": there is no dial.
2. **Land the 16 natural-C candidates at `2.7.2-cdk-G0`** through `land_recipe_move.py`. They are coherence
   trades, and they retire 16 `maspsx_dependent` rows.
3. **Route the 19 others.**
   - C: three small Opus lanes.
   - D: stay at 2.6.3/2.7.2. No fingerprint argues for cdk, and these are mixed-recipe modules unless the owner
     rules "one compiler per TU" applies.
   - E: the post-970404 codegen group.
4. **Refresh the stale `build_ovl/` 2.56 literals** when `tools/gate` mirrors are next synced.
