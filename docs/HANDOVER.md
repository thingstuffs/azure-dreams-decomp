# Handover (written 2026-09-07 late evening UTC) — start here in a fresh session

Repo: https://github.com/thingstuffs/azure-dreams-decomp (private; renamed from azure-clean on
2026-09-08, the old URL redirects), local `~/azure-clean`, branch `master`.
Dashboard: http://<lan-host>:8002/ (`tools/dashboard_serve.sh`; restart it if the box rebooted).

## Where things stand

- **Goal:** readable, better-structured C for all of Azure Dreams that still rebuilds byte-exact.
  Strategy and level definitions: `docs/PLAN.md`. Day-one results: `docs/REPORT_20260907.md`.
- **The swap-over is done (`docs/SWAPOVER.md`, last section).** This tree owns everything that
  proves bytes: the seven stock compilers, the vendored function-blind assembler front end,
  mkpsxiso, splat, the disc extract, the row database (`ledger/splits/`), the gates. No standing
  tool reads another checkout; `.upstream` is gone; `tools/pin_bump.py` is history.
  `tools/setup.sh --check` must say OK before anything else is trusted.
- **Pin `82f20568`:** `raw/` is the frozen snapshot of the matched sources at that commit.
  Registry 6,767 rows / 2,558,124 B (the engine-only row folded in), every row stock and
  byte-exact; the three proofs from this tree alone: SLUS SHA-1 OK from a fresh split; overlay
  windows 2,172 / 2,172 byte-identical; whole containers SHA-1 OK and the disc rebuilt byte-identical from the gated windows plus the built SLUS; every transformed row re-verified
  through the local scorer, **4,620 / 4,620 exact, 0 drift**, every one by the scorer (no window fallback needed; `ledger/reverify.jsonl`, 624 s at 6 workers).
- **Levels (bytes, ovmovie parked):** see `STATUS.md` (L3 has grown with the campaign).
- **Machine layers done corpus-wide:** T1 boilerplate hoist, T4 raw offsets → typed local structs,
  T2 dead-pin erasure, T6 pin notes. T3a retired (window gate caught it).
- **Scaffolding debt campaign (2026-09-08, `docs/FIDELITY.md`):** measured through the shipped Psy-Q
  toolchain, every pin, marker and noreturn tail-call spelling stands for a source shape; the plan
  attempts removal at L1 (sweeps), in every L3 lane (Astra's prompt now tries and journals
  `pins_in/out`, `sites_in/out`) and in a dedicated L5 pass. Landed: `t8_passthru` 109 rows,
  `t10_epilogue` 453 rows (979 sites; 13 cells corrected via `common.set_row_cfg`), `t9_regpins`
  8 rows, mid-row reader lanes 10 rows (Sonnet, `work/lac_lane/`, landed with
  `tools/apply_candidates.py`, journal `t11_midrow`). Continue the mid-row lane over the remaining
  single-site rows (`work/lac_lane/batchN/rows.tsv` + the pilot brief), then multi-site rows; the
  census is live so STATUS shows the burn-down.
- **Layer 2 agent campaign (Astra, gpt-6-astra high) — orchestration state (2026-09-08 03:30 UTC):**
  one process at a time, always `tools/agent_task.py --model gpt-6-astra --effort high --all
  --min-size A --max-size B --workers 3 --limit 900 --commit --tag campaign` (log
  `work/astra_campaignN.log`, journal `ledger/agents/gpt-6-astra-high-campaign.jsonl`, resumable;
  the prompt now attempts scaffolding removal and journals `pins_in/out`, `sites_in/out`).
  All-time (2026-09-08 03:00 UTC): 3,460 accepted, 15 rejected. The 1000–2000 B tier completed
  (222 rows served, commit `e83a229b`). **Running now: the 2000–4000 B tier (79 rows, log
  `work/astra_campaign9.log`).** Pools still to serve (eligible = level ≥ 1, ovmovie excluded), in
  order: 4000+ B (13), then **100–1000 B again (305 rows: 288 in 100–600 and 17 in 600–1000 became
  eligible when the burn-down cleared their blocking sites)**, then 0–100 B (2,004 tiny rows; cheap,
  mostly pin-removal attempts). Since 03:00 UTC the prompt also carries the row's evidence block
  (`docs/EVIDENCE.md`; journal field `evidence`); the 562 evidence rows already accepted before
  that are to be re-served once with `--rows $(python3 -c "import json;print(','.join(json.loads(l)['id'] for l in open('ledger/evidence/rows.jsonl')))")`
  after the size tiers (one process at a time). When a tier prints `0 rows`, launch the next; when the log shows
  `quota` outcomes the harness stops cleanly after three in a row — relaunch after the reset.
  Commit campaign output separately: `git add ledger/agents refine && git commit -m "campaign: …"`
  (the scrub hook runs; push after). Kill only by PID (`pgrep -f '[a]gent_task.py --model'`).
- **T7 shared headers: done for every class with ≥ 10 rows** (`docs/STRUCT_CENSUS.md`, "T7
  result"). `tools/gen_records.py` writes `include/records/Rec_*.h` (12 records) and
  `ledger/records.json` from the census; `tools/xform/t7_headers.py` (sweep `t7_headers`)
  converted 1,014 rows at the ≥ 10-row threshold, then 1,168 rows / 659,544 B (25.8 %) on 88
  of 102 records at `--min-rows 2`, 0 mismatches, every touched window re-gated byte-identical
  (562 then 103 / 103 windows byte-identical), SLUS gate MATCH. Re-running the census carries converted structs
  forward, so headers only ever gain views. Scalar globals read through one-member structs are
  deliberately not records (typed-global work for L4).

## What happens next (in order)

1. **Names and modules (L4).** The 12 record headers are the place to name things: a member
   name changed in `include/records/Rec_*.h` reaches every user, and the gate proves it. **Start
   from `docs/EVIDENCE.md`** (2026-09-08): every source of real names is in-tree and joined to rows
   in `ledger/evidence/rows.jsonl` — Konami's assertion sites (15 real source file names with
   line numbers, 39 rows), the developer identifiers the debug prints kept (`OSETDT`, `ost_w`,
   `osel_w`, `cdhd_cnt`, `ov_work.kind`, `gsw->check_sum`, …; the `main.c` triple sits in all 54
   TOWN event-script modules), the randomizer address map (data tables with record layouts, 52
   code sites), the event-script VM handler table (opcode numbering, 72 SLUS rows) and 281 prior
   notes. The lane prompt carries the row's block; `levels.jsonl` carries `evidence: [...]`; the
   L4 module gate must place a row with an assertion file in that file's module. Then call-site
   roles and the parameter classes (dungeon handler ABI). Then modules: group rows by record/dispatcher into `src/<container>/
   <module>.c` in retail order (the per-row ledger stays the unit of proof).
2. Lower the T7 threshold (`tools/gen_records.py --min-rows 5`, then the sweep and the gate)
   once the ≥ 10 classes have names, so small classes inherit them.
3. Whole-container link (every fragment C or checked-in data) as the L4/L5-era standing gate.
The campaign keeps running underneath (next tier 1000–2000 B).

## Commands that prove things

```sh
tools/setup.sh --check                                   # provisioning and hashes
python3 tools/disc.py check                              # disc round trip (after extract + rebuild)
tools/build/build_slus.sh [--fresh]                      # SLUS SHA-1 gate
bash tools/build/mk_ovl_root.sh && python3 tools/build/gate_all.py   # every overlay window (skips up-to-date ones)
python3 tools/build/container_check.py --rebuild-disc    # containers from gated windows + SLUS, then the disc
python3 tools/reverify.py 6                              # every transformed row through the scorer (+ gate fallback)
python3 tools/row_db.py check                            # row database consistency
python3 tools/registry.py && python3 tools/levels.py && python3 tools/status.py
```

## Rules learned the hard way (all recorded in docs/SWAPOVER.md)

- **The window gate's compile command is the only compile command.** The per-row scorer is a
  dev tool; anything it cannot prove is gated through the row's window (`verify.py::gate_fallback`).
- **A row is gated by range, not by name.** The gate compiles every matched row inside a
  window's file range; `gate_config` is derived when the split table did not name one, and
  `gate_all.py` hashes inputs by range. "Windowless" rows do not exist (`row_db.py check`).
- **Never rebuild `build_ovl/` under running gates or campaign workers** (`mk_ovl_root.sh`
  replaces the tools copy); `verify.py` only creates a missing root.
- **Byte equality does not prove struct honesty:** scope structs per function (done).
- **Every row keeps a file** in `src/`: run `tools/complete_tree.py` after any re-derivation.
- **Scrub before push:** `work/scrub_check.sh` is the pre-commit hook (index-based); no absolute
  home-directory paths, no other repo names, no personal email.
- **Process hygiene:** never `pkill -f` with a pattern that also appears in your own command
  line; a compound shell command that launches X also matches `pgrep -f X`. `ps etime` is
  unreliable here; the dashboard reads `/proc/<pid>`. A `grep … $f` with an empty `$f` waits on
  stdin forever.
- ovmovie is parked (owner): listed, not counted (`PARKED_CONTAINERS` in `tools/common.py`).

## Files a new session needs

`PIN`, `tools/toolchain.lock.json`, `ledger/splits/*`, `ledger/rows.jsonl`, `ledger/levels.jsonl`,
`ledger/gate.jsonl`, `ledger/gate_slus.jsonl`, `ledger/containers.jsonl`, `ledger/baseline.jsonl`,
`ledger/reverify.jsonl`, `ledger/sweeps/*.jsonl`, `ledger/agents/*.jsonl`, `STATUS.md` (generated),
`docs/*.md`. Not in git: `bin/` (the disc), `toolchain/`, `.venv/`, `baserom/`, `work/disc/`, the
build roots — `tools/setup.sh` recreates all of them from the lock and the disc.
Background work is journalled and resumable; nothing depends on a running process.
