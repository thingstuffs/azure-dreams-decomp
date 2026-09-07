# Handover (written 2026-09-07 ~14:20 UTC) — start here in a fresh session

Repo: https://github.com/thingstuffs/azure-clean (private), local `~/azure-clean`, branch `master`.
Upstream (private byte-matching tree) path is in the gitignored `.upstream` file. Dashboard:
http://<lan-host>:8002/ (`tools/dashboard_serve.sh`; restart it if the box rebooted).

## Where things stand

- **Goal:** readable, better-structured C for all of Azure Dreams that still rebuilds byte-exact.
  Strategy and level definitions: `docs/PLAN.md`. Day-one results: `docs/REPORT_20260907.md`.
- **Pin `82f20568` (2026-09-07 14:00 UTC): upstream's bridge lane is at zero and this tree took it.**
  Every registered row is stock and byte-exact at the pin: 6,766 / 6,766 rows, 2.56 MB, L0 100 %.
  Gates from this tree: SLUS SHA-1 OK from the transformed tree; overlay window gate 2,172 / 2,172
  byte-identical (`ledger/gate.jsonl`, fresh at the pin). Reverify 4,619 transformed rows, 0 drift.
  Report `ledger/pin_bumps/82f20568.json`; what the bump found and fixed: `docs/SWAPOVER.md`
  "Pin bump to 82f20568" (five recipe gaps, two verifier lessons, the superseded seed windows).
- **Levels (bytes, ovmovie parked):** L0 100 % · L1 73.1 % · L2 69.4 % · L3 12.9 % · L4/L5 0.
- **Machine layers done corpus-wide:** T1 boilerplate hoist, T4 raw offsets → typed local structs,
  T2 dead-pin erasure, T6 pin notes. T3a retired (window gate caught it). The eight rows the
  per-row scorer could not measure until today (page rows with a data prefix, data rows written
  as C) are exact but refuse every transform: they stay L0.
- **Layer 2 agent campaign:** Astra (gpt-6-astra high) via `tools/agent_task.py --model gpt-6-astra
  --effort high --all --workers 3 --limit 900 --commit --tag campaign`; 1,782 rows accepted, 5
  rejected; journal `ledger/agents/gpt-6-astra-high-campaign.jsonl`. Relaunch the same command
  after a Codex quota reset; it resumes (quota casualties are journalled and retried; a row whose
  refine body a pin bump set aside is served again). Bake-off evidence: `docs/BAKEOFF.md`.
- **Layer 3 groundwork:** `docs/STRUCT_CENSUS.md` / `tools/struct_census.py` — record classes by
  provenance (biggest: D_80083780 596 rows, D_800848F8 436, D_80126000 128, D_800814A8 105,
  D_80082D58 91; dungeon handler ABI as parameter classes).

## What happens next (in order)

1. **Swap-over** to this repo as the only tree: `docs/SWAPOVER.md` §3 (freeze `raw/`, retire the
   mirror step, ledger becomes the row database) and the §2 gaps: disc round-trip script,
   whole-container link, the 17 windowless rows (9 ovmovie, 8 main). The maspsx name-table gap
   closed upstream (tables and dials deleted; maspsx is name-blind). Until the toolchain, venv,
   disc extract and `bin/` are provisioned here, `build_slus/` and `build_ovl/` still symlink
   them from the upstream checkout (`tools/build/mk_*_root.sh`).
2. **T7 shared headers** from the struct census (majority types, union views for hard conflicts,
   verified per row **through the window gate**), then modules and names (L4), pin documentation
   complete (L5). Layer-2 campaign keeps running underneath.
3. A later upstream commit, if any: `python3 tools/pin_bump.py <commit>` (README "Syncing with
   upstream"), campaign paused, ~80 min.

## Rules learned the hard way (all recorded in docs/SWAPOVER.md)

- **The window gate's compile command is the only compile command.** The per-row scorer is a
  dev tool: it once passed a header via `C_INCLUDE_PATH`, it normalises relocation targets, and
  its stale-name rename manufactured eight "drift" rows. Anything the scorer cannot prove is
  gated through the row's window (`verify.py::gate_fallback`); nothing is kept on the scorer's
  word against the gate's.
- **Never derive pinned state from the live upstream tree.** The pinned `build.ninja` is what the
  pinned `configure.py` generates; imported config/tool copies are re-copied at every bump.
- **A baseline record does not survive a pin.** The rows compile through the live toolchain;
  the baseline, reverify and gate journals are rebuilt in full at every bump.
- **Byte equality does not prove struct honesty:** T4 once merged bases across functions in
  multi-function SLUS units and still matched. Scope per function (done).
- **Every row keeps a file** in `src/`: run `tools/complete_tree.py` after any re-derivation.
- **Scrub before push:** `work/scrub_check.sh` is the pre-commit hook (index-based); no absolute
  home-directory paths, no upstream repo name, no personal email; imported upstream files get
  their schema tags renamed consistently (`tools/pin_bump.py::scrub`).
- **Process hygiene:** never `pkill -f` / loop-kill with a pattern that also appears in your own
  command line; use `ps -eo pid,args | grep '[a]gent_task'` in a call that contains no launch
  text, then launch separately. `ps etime` is unreliable here; the dashboard reads `/proc/<pid>`.
- ovmovie is parked (owner): listed, not counted (`PARKED_CONTAINERS` in `tools/common.py`).

## Files a new session needs

`PIN`, `.upstream`, `ledger/rows.jsonl` (registry), `ledger/levels.jsonl`, `ledger/gate.jsonl`,
`ledger/baseline.jsonl`, `ledger/reverify.jsonl`, `ledger/pin_bumps/*.json`, `ledger/sweeps/*.jsonl`,
`ledger/agents/*.jsonl`, `STATUS.md` (generated), `docs/*.md`.
Background work is journalled and resumable; nothing depends on a running process.
