# Toolchain fidelity plan, STEP 2: split-address fingerprint census in every container (measurement only)

Read first: docs/TOOLCHAIN_FIDELITY_PLAN.md and docs/evidence/r77_splitaddr_verdict.md (and
work/native_lane/r77_fable_splitaddr/REPORT.md, which measured slus only).

## Question
Which rows' RETAIL bytes show compiler-level address splitting - evidence the original was built by an address-
splitting cell (2.7.2-cdk; 2.8.x) and not by 2.6.3/2.7.2 (their mips.c has no split_addresses path) - and how does
that line up with each row's registered cell, its pins, and its module's census recipe?

## Fingerprint (sharpen it; document exactly what you count)
A `lui rX,%hi(A)` and its `%lo(A)` user(s) where the pair CANNOT be an assembler `la`/macro expansion: the halves are
separated by an unrelated instruction; the LO_SUM writes a register other than the HIGH's; the `lui` sits in a branch
delay slot; one `lui` base feeds several accesses (%lo folded into loads/stores) where a macro would re-materialise.
Genuine ASPSX never splits an `la` (verdict doc), so assembler macro forms - `lui $at` + adjacent use, adjacent
`lui rX/addiu rX,rX` - are NOT the fingerprint. Beware integer page constants (`lui/ori`, `lui/addiu` of a literal
page): classify them separately rather than as symbol splits, and say how you tell them apart in raw words (you have
only retail words + the row's address range; symbol maps in config/ and the linker scripts may help).

## Material
- Retail bytes per row: the overlay scorer's retail slices (tools/gate/aligned_score.py, tools/verify.py
  verify_overlay) and the slus reference (verify_slus; the sceptic used "556 cached retail disassemblies" - find that
  cache rather than re-deriving). Row database: tools/common.py rows(); pins: tools/pin_census.sites_of.
- Module census: ledger/module_recipe_census.jsonl (best_recipe per module); cells: tools/common.py STOCK_CELLS.
- Calibration from the sceptic (slus): 185 of 317 pin-free 2.7.2-cdk rows show it; 66/107 at 2.8.1; 6/364 pin-free
  2.7.2 rows (all traced to maspsx passes, not cc1 - but RETAIL is your input, so a 2.7.2-registered row whose retail
  shows the fingerprint is a recipe question). Reproduce these numbers first; if you cannot, find out why.
- The page-constant pin class: work/native_lane/r77_fable_splitaddr/cands/page_pin_rows.txt (150 rows / 332 sites).

## Deliverables
1. tools/fidelity/split_fingerprint.py (resumable, hash-keyed on retail bytes; --container/--only) + a small test.
2. work/fidelity/split_fingerprint.jsonl - per row: container, module, cfg, cell, pins, fingerprint counts by kind,
   2-3 example word offsets per kind.
3. docs/evidence/fidelity_step2_split_fingerprint.md - method + validation + tables: fingerprint rate by container x
   registered cell x pinned/pin-free; per module: fingerprint rate vs the census best_recipe (agreements and
   contradictions); the page-constant pin rows with their fingerprint status and registered cell - i.e. the STEP 4
   candidate list (rows whose retail proves a splitting cell but are registered at a non-splitting one), as a file.

## Rules
- Measurement only: never edit src/, include/, ledger/, config/, recipes, tools/maspsx, tools/build; never run gates,
  landings, sweeps or git. New files only under tools/fidelity/, tools/tests/, work/fidelity/, docs/evidence/.
- Shared-disk IO rule: never grep/rg recursively over work/, the repo root or <home>; `rg --max-filesize 4M` on
  narrow directories only. Heavy jobs under `nice -n10 ionice -c2 -n7`, at most 12 workers (step 1 runs alongside).
  One background command per full run, one completion (no pgrep polling on your own pattern).
- Temp files under work/fidelity/tmp2 (cleaned up).
- Report at the end: headline numbers, the evidence doc path, the step-4 candidate list path, decisions for the
  orchestrator.
