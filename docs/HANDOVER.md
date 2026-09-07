# Handover (written 2026-09-07 ~12:00 UTC) — start here in a fresh session

Repo: https://github.com/thingstuffs/azure-clean (private), local `~/azure-clean`, branch `master`.
Upstream (private byte-matching tree) path is in the gitignored `.upstream` file. Dashboard:
http://<lan-host>:8002/ (`tools/dashboard_serve.sh`; restart it if the box rebooted).

## Where things stand

- **Goal:** readable, better-structured C for all of Azure Dreams that still rebuilds byte-exact.
  Strategy and level definitions: `docs/PLAN.md`. Day-one results: `docs/REPORT_20260907.md`.
- **Levels (bytes, ovmovie parked):** L0 97.4 % · L1 71.2 % · L2 67.6 % · L3 ≈ 4.5 % and rising · L4/L5 0.
- **Machine layers done corpus-wide:** T1 boilerplate hoist, T4 raw offsets → typed local structs
  (both `M2C_FIELD` and the local `FIELD` macro; unions, prefix records, per-function scoping,
  delta-debugging fallback to explicit casts), T2 dead-pin erasure (11.8 k of 25.6 k sites),
  T6 pin notes (every surviving pin annotated with its measured class). **T3a is retired** (every
  "epilogue" target is a resident shared tail; the window gate caught it).
- **Layer 2 agent campaign:** Astra (gpt-6-astra high) via `tools/agent_task.py --all --workers 3
  --limit 900 --commit --tag campaign`; 1622 rows accepted so far, 0 rejected; journal
  `ledger/agents/gpt-6-astra-high-campaign.jsonl`. Relaunch the same command after a Codex quota
  reset; it resumes (quota casualties are journalled as `quota` and retried). Bake-off evidence:
  `docs/BAKEOFF.md`.
- **Gates imported and proven from this tree:** SLUS build (`tools/build/`, view root
  `build_slus/`) and the overlay window gate (`tools/gate/`, `config/overlays/`, view root
  `build_ovl/`). `tools/build/gate_all.py` gates every window (10 min): 2,139 / 2,181
  byte-identical; the rest is upstream drift at the pin (retired bridge compiler cells, an
  assembler change) — see `docs/SWAPOVER.md` and `ledger/gate.jsonl`.
- **Layer 3 groundwork:** `docs/STRUCT_CENSUS.md` / `tools/struct_census.py` — record classes by
  provenance (biggest: D_80083780 596 rows, D_800848F8 436, D_80126000 128, D_800814A8 105,
  D_80082D58 91; dungeon handler ABI as parameter classes).

## What happens next (in order)

1. **Pin bump when the upstream bridge lane is at zero** (owner will name the commit; last rows
   were in progress). Recipe in README "Syncing with upstream" (`PIN`, refresh, registry,
   baseline, census, sweeps T1/T4/T2/T6, complete_tree, levels, status), then
   `tools/build/mk_slus_root.sh` + `splat split` + `ninja` in `build_slus` (SHA-1 gate) and
   `tools/build/mk_ovl_root.sh` + `gate_all.py`. Every drift class should go green. The four
   stale-name dungeon rows are already fixed upstream.
2. **Swap-over** to this repo as the only tree: `docs/SWAPOVER.md` §3 (freeze `raw/`, retire the
   mirror step, ledger becomes the row database); open gaps in §2 (disc round-trip script,
   whole-container link, 17 windowless rows, maspsx name tables).
3. **T7 shared headers** from the struct census (majority types, union views for hard conflicts,
   verified per row **through the window gate**), then modules and names (L4), pin documentation
   complete (L5). Layer-2 campaign keeps running underneath.

## Rules learned the hard way (all recorded in docs/SWAPOVER.md)

- **The window gate's compile command is the only compile command.** The per-row scorer once
  passed a header via `C_INCLUDE_PATH` (system header → typedef redefinitions tolerated) and
  normalises relocation targets (hid T3a's changed jump targets). `tools/verify.py` now uses
  `-I`; anything that can move a jump/call target is proven by `gate_all`, never per row.
- **Byte equality does not prove struct honesty:** T4 once merged bases across functions in
  multi-function SLUS units and still matched. Scope per function (done).
- **Every row keeps a file** in `src/`: run `tools/complete_tree.py` after any re-derivation.
- **Scrub before push:** `work/scrub_check.sh` is the pre-commit hook (index-based); no absolute home-directory paths, no upstream repo name, no personal email; imported upstream files get their
  schema tags renamed consistently.
- **Process hygiene:** never `pkill -f` / loop-kill with a pattern that also appears in your own
  command line (it killed the shell twice); use `ps -eo pid,args | grep '[a]gent_task'` in a
  call that contains no launch text, then launch separately. `ps etime` is unreliable here;
  the dashboard reads `/proc/<pid>` mtime.
- ovmovie is parked (owner): listed, not counted (`PARKED_CONTAINERS` in `tools/common.py`).

## Files a new session needs

`PIN`, `.upstream`, `ledger/rows.jsonl` (registry), `ledger/levels.jsonl`, `ledger/gate.jsonl`,
`ledger/sweeps/*.jsonl`, `ledger/agents/*.jsonl`, `STATUS.md` (generated), `docs/*.md`.
Background work is journalled and resumable; nothing depends on a running process.
