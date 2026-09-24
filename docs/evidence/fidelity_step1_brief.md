# Toolchain fidelity plan, STEP 1: genuine-ASPSX differential over the whole tree (measurement only)

Read first: docs/TOOLCHAIN_FIDELITY_PLAN.md and docs/evidence/r77_splitaddr_verdict.md.

## Question
For every row (function) in the tree: does the row's CURRENT source, compiled by its registered recipe (cell + flags),
reproduce retail when assembled by GENUINE ASPSX instead of maspsx - and with which ASPSX version(s)? Every landed row
is byte-exact through the project pipeline (cpp/cc1 -> tools/build/ccproc.py -> tools/maspsx --aspsx-version=2.56
--dont-force-G0 ... -> GNU as; see tools/build/cc.sh and tools/verify.py). Rows exact under maspsx but under NO genuine
ASPSX version are maspsx-dependent: fidelity debt. Where maspsx and genuine ASPSX differ, which maspsx pass made the
difference?

## Material you can reuse (do not rebuild what exists)
- Genuine ASPSX: <sibling decomp repo>/toolchain/psyq/psyq4.{0,1,3,4,5,6}/ASPSX.EXE = 2.56/2.67/2.77/2.79/2.81/2.86,
  run under <sibling decomp repo>/toolchain/bin/wibo, `-q -o OUT.OBJ IN.S`, CRLF line endings, `.include`/`#APP`
  stripped; ASPSX 2.56 cannot parse %hi/%lo. The LNK (.OBJ) reader and runner:
  work/native_lane/r77_fable_splitaddr/cands/aspsx_run.py (from work/tailslot_aspsx/ts_harness.py); a relocation-
  resolving comparator: .../cands/pipe.py. Earlier genuine-vs-maspsx studies: work/tailslot_aspsx/REPORT.md,
  work/maspsx_jtbl/REPORT.md (maspsx casesi gap - a known, real maspsx-vs-genuine difference: use it as a positive
  control). `-0` matters for div expansion (see the verdict doc).
- Retail truth: overlay rows are scored by tools/gate/aligned_score.py against the retail slice (tools/verify.py
  verify_overlay shows how); slus rows are byte-exact by the SLUS SHA-1 gate, so the pinned TU object is the reference
  (verify_slus). Row database: tools/common.py rows(), clean_path(row), parse_cfg.
- maspsx: tools/maspsx (look for pass names / a way to trace which passes fired or to disable one).

## Deliverables
1. tools/fidelity/aspsx_diff.py - the differential, resumable, hash-keyed journal (never recompute a row whose text,
   recipe and tool versions are unchanged), --workers, --only, --container, --limit. Keep it runnable later as a
   regression instrument. A small test in tools/tests/ for its word comparator.
2. work/fidelity/aspsx_diff.jsonl (one record per row: row, container, cfg, pins, maspsx_exact, per genuine version:
   exact / differing word count / assemble error, difference classes, attributed maspsx pass(es) where you can).
3. docs/evidence/fidelity_step1_aspsx_diff.md - method, validation, and the tables: rows exact under genuine ASPSX
   per version x cell x container; the maspsx-dependent rows (count, list file, by attributed pass); the ASPSX version
   each TU needs (and whether one global version could work per container); the small-extern `$gp` model difference
   (decision 3 in the plan) measured; anything surprising.

## Validation before the full run
- positive controls: the casesi rows from work/maspsx_jtbl/REPORT.md must show a maspsx-vs-genuine difference;
  work/native_lane/r77_fable_splitaddr/cands/d92c_genuine.c must be exact under genuine 2.67/2.77 at 2.7.2-cdk.
- a handful of plain pin-free rows at each cell must come out exact under some genuine version; if almost nothing is
  exact, your comparison is wrong (relocation fields, section alignment, trailing nops, CRLF, symbol names) - fix it
  before scaling.

## Rules
- Measurement only: never edit src/, include/, ledger/, config/, recipes, tools/maspsx, tools/build; never run gates,
  landings, sweeps or git. New files only under tools/fidelity/, tools/tests/, work/fidelity/, docs/evidence/.
- Shared-disk IO rule: never grep/rg recursively over work/, the repo root or <home>; use `rg --max-filesize 4M`
  on narrow directories only. Run heavy jobs under `nice -n10 ionice -c2 -n7`, at most 16 workers. A full-tree run is
  one background command with one completion (no polling with pgrep on your own pattern).
- Temp files under work/fidelity/tmp (cleaned up), not /tmp.
- Report at the end: the headline numbers, where the evidence doc is, and any finding the orchestrator must decide on.
