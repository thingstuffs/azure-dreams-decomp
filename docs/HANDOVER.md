# Handover (2026-09-07, updated 2026-09-09) — start here in a fresh session

Repo: https://github.com/thingstuffs/azure-dreams-decomp (private; renamed from azure-clean on
2026-09-08, the old URL redirects), local `~/azure-clean`, branch `master`.
Dashboard: served on the LAN by `tools/dashboard_serve.sh` (port 8002; restart it if the box rebooted).

Efficiency follow-up: [Astra and Claude usage advice](AGENT_EFFICIENCY_HANDOVER.md) records the
2026-09-08 live-lane review. **Pilot run the same day** (40 frozen rows ≤ 100 B, same model and
effort, no landing until judged): the standing single-row prompt cost 45 s and 88k input tokens per
row; readability-only single rows 32 s / 60k; readability-only batches of ten **8.3 s / 12.9k input
/ 1.8k uncached / 175 output tokens per row**, with the same acceptance (39–40 of 40), the same
readability outcome (m2c locals 70→10) and summaries of equal quality. Adopted: the ≤ 100 B band
and the evidence re-serve run `--mode readability --batch 10`; larger rows keep the full prompt;
usage now comes from `codex exec --json` events; completions are journalled as they arrive; a row
that failed twice at the same text is not served a third time (`--retry-all` re-opens it); landing
skips the duplicate scorer run. The pin-removal obligation for tiny rows lives in the tracked queue
`work/pin_queue_tiny.txt` (PLAN.md L3 definition). Orchestration is now `tools/campaign.py` with
`work/campaign_plan.json` (tiers → commits → quota back-off), PID in `work/campaign_controller.pid`.

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
- **One gated tree (2026-09-08):** `refine/` is gone. Every accepted Layer-2 body is landed in `src/`
  by `tools/promote.py`: scorer-exact → written → **the row's window gate must MATCH** (under the
  cross-process window lock `verify.window_lock`) → `ledger/promotions.jsonl` `landed`; otherwise the
  text is reverted and the record says `gate-mismatch`. The campaign's `--commit` lands through the
  same call, and the prompt makes the model run `verify.py … --gate` once before DONE. L3 means
  "landed". The 4,369 bodies the campaign had written to `refine/` were promoted in one pass (4,346
  landed; 10 build-failed against today's headers; 13 gate-mismatch: lane rewrites that respelled
  an internal jump in a row the gate links at its synthetic address), the standing sweeps re-run
  over them (`sweep.py --force` for rows whose text was reverted to a pre-transform state — the
  journals key on the input sha and would otherwise skip them), and every gate re-run: 2,172/2,172
  windows MATCH, SLUS MATCH, reverify 6,072/6,072. The 23 unlanded rows are served again by the
  campaign (`done` = landed).
- **Layer 2 agent campaign (Astra, gpt-6-astra high) — orchestration state (2026-09-08 03:30 UTC):**
  one process at a time, always `tools/agent_task.py --model gpt-6-astra --effort high --all
  --min-size A --max-size B --workers 3 --limit 900 --commit --tag campaign` (log
  `work/astra_campaignN.log`, journal `ledger/agents/gpt-6-astra-high-campaign.jsonl`, resumable;
  the prompt now attempts scaffolding removal and journals `pins_in/out`, `sites_in/out`).
  All-time (2026-09-08 05:30 UTC): 3,857 accepted, 15 rejected. Tiers completed and committed:
  1000–2000 B (`e83a229b`), 2000–4000 B (79/79, `83cfa91d`), 4000+ B (13/13, `8e9b81e7`),
  100–1000 B (305/305, `3be8e7cc`). **Running now: the 0–100 B tail (2,004 tiny rows, served 900
  per launch because of `--limit 900`; relaunch the same command until it prints `0 rows`; logs
  `work/astra_campaign12.log` onward).** Since 03:00 UTC the prompt carries the row's evidence block
  (`docs/EVIDENCE.md`; journal field `evidence`); the evidence rows accepted before that are to be
  re-served once with `--rows $(python3 -c "import json;print(','.join(json.loads(l)['id'] for l in open('ledger/evidence/rows.jsonl')))")`
  after the size tiers (one process at a time). When a tier prints `0 rows`, launch the next; when the log shows
  `quota` outcomes the harness stops cleanly after three in a row — relaunch after the reset.
  Commit campaign output separately: `git add ledger/agents ledger/promotions.jsonl src && git commit -m "campaign: …"`
  (the scrub hook runs; push after). Kill only by PID (`pgrep -f '[a]gent_task.py --model'`).
- **T7 shared headers: done for every class with ≥ 10 rows** (`docs/STRUCT_CENSUS.md`, "T7
  result"). `tools/gen_records.py` writes `include/records/Rec_*.h` (12 records) and
  `ledger/records.json` from the census; `tools/xform/t7_headers.py` (sweep `t7_headers`)
  converted 1,014 rows at the ≥ 10-row threshold, then 1,168 rows / 659,544 B (25.8 %) on 88
  of 102 records at `--min-rows 2`, 0 mismatches, every touched window re-gated byte-identical
  (562 then 103 / 103 windows byte-identical), SLUS gate MATCH. Re-running the census carries converted structs
  forward, so headers only ever gain views. Scalar globals read through one-member structs are
  deliberately not records (typed-global work for L4).

## Session 2026-09-09 (start here; the sections above are the 09-07/08 baseline)

**Levels (bytes):** L3 74.4 %, L2 1.3 %, L1 4.0 % (96 rows whose `M2C_FIELD` accesses the T4 sweep
could not type), L0 20.4 % (rows still carrying a blocking fidelity site). `STATUS.md` is current.

**Done this session**

- `tools/xform/t8b_passthru_params.py` (sweep `t8b_passthru_params`): the pass-through repair for
  callers that declare fewer parameters than the callee reads (or name them differently) and for
  files where t8 found the call ordinal ambiguous — resolved by the audited target name. 190 of the
  277 single-site `PASSTHRU_NO_ARGS` rows applied, windows re-gated MATCH.
- Reader lanes for single-site `LABEL_AS_CALL` rows (`work/lac_lane/BRIEF.md`, batches 3–7, Sonnet
  subagents, 15 rows each): 13+11+14+15+14 exact of 75, landed through `tools/apply_candidates.py
  --transform t11_midrow`. New levers are in the batch REPORTs and in the Astra prompt
  (`ASM_SCHED_BARRIER()` before a guard clause / after an arm's store; guard order = hot/cold
  layout; the tail-slot-sink loop is an unpinned `do/while` + `continue`). **Trap:** a row whose
  target is called as a plain `f(args)` is NOT resolved when `f` is listed in
  `config/sibcall_syms.<container>.txt` / `noreturn_syms.<container>.txt` — the assembler front
  end converts that `jal` to `j` by name; the census (`census.py::live_sites`) is right to keep
  counting it, and a lane must restructure the call away.
- `tools/verify.py --diff` prints the scorer's positional disasm diff (free iteration for lanes).
- **Names (L4a) are live.** `tools/apply_names.py <tsv>` applies evidence-backed renames: one
  names.tsv line per function, every `src/` mention rewritten, every touched row re-verified, any
  failure reverts the whole name (journal `ledger/names.jsonl`). 125 script-dump names applied
  (`config/names.tsv` 145 lines; SLUS SHA-1 gate MATCH; windows MATCH). Mechanism, learned the hard
  way: **names are a C-level alias layer and nothing below C ever sees them.** `tools/ccproc.py`
  (gate pipeline) and `match.py::_canonicalise_names` (scorer pipeline) spell every renamed
  identifier in the `gcc -S` listing back to its `func_<addr>` original, so the assembler's
  name-keyed tables (sibcall/noreturn lists — the first attempt with a `.set` alias broke the SLUS
  gate exactly there), the linker scripts and the slices work on the pre-rename symbols;
  `verify.py::canonical_spelling` additionally scores a renamed *definition* under its func_ symbol.
  The names.tsv row must carry the **true-space** symbol the C defines (`rows.jsonl true_name`),
  not the synthetic row name the evidence may quote; `apply_names.py` resolves that.
- `tools/agent_task.py --mode fidelity` (facts + recipes per row: class, target, landing word,
  needed registers, rowbase coverage) and `--mode fields` (type the `M2C_FIELD` accesses);
  `tools/campaign.py` takes per-tier `tag`/`limit`/`workers`. Plan `work/campaign_plan_v2.json`:
  the three size tiers (picks up every row the sweeps and lanes unblocked), then the fidelity lane
  over `work/fidelity_rows_single.txt` (311 rows) and `work/fidelity_rows_multi.txt` (483), then
  the fields lane (`work/fields_rows.txt`, 96), then the size tiers again. Journals
  `ledger/agents/gpt-6-astra-high-{campaign,fidelity,fields}.jsonl`. Relaunch after a quota stop:
  `nohup python3 tools/campaign.py --plan work/campaign_plan_v2.json > work/campaign_controller.out 2>&1 &`
  (state in `work/campaign_state.json`; delete it to start the plan from the first tier).
- `levels.py`: a pin named only in a comment is not a pin; sweep journals without an `id` are skipped.
- **Module map drafted and accepted** (`ledger/modules.jsonl`, 5,861 rows): Astra analyses over
  `work/modules_input/*.json` (call graph + evidence per row, one file per sub-overlay group),
  validated by `tools/modules.py` (contiguity, one load base, assertion files, coverage). main 16
  modules (libcard `c_server.c` twice — the shipped and the devkit copy — and the card UI files, all
  proven by assertion sites); town resident 51 themed modules (`player_actions.c`, `town_map.c`,
  …, strong/weak) + 93 script-overlay modules (`main.c`/`lshop.c`/`memory.c` proven, the rest
  `ovl_<foff>.c`); dungeon engine 35 themed modules + 403 floor-overlay modules (mostly one or two
  rows, `ovl_<foff>.c`, weak). Names in the map are proposals until a header carries them; the
  confidence field says which ones rest on evidence. SLUS proposal pending (`work/modules_proposed/slus.json`).

**Traps for the next session:** the controller commits `ledger/agents ledger/promotions.jsonl src`
after every launch — commit your own tree changes (tools, config, ledger) *before* launching it or
they get swept into a campaign commit without their config; a bash `a && b && nohup c &` backgrounds
the whole list, not just `c`; never print a set of window names.

## What happens next (in order)

0. **Keep the Astra plan running** (above) until every tier prints `0 rows`; re-run `gate_all.py`
   + `build_slus.sh`, `levels.py`, `status.py` and commit between relaunches. Lanes that stay
   refused after two attempts at the same text are the residue for the L5 shape pass.
0b. **Declarations (L4b), the measured prerequisite for modules** (`tools/decl_census.py`, output
   `work/decl_census/<container>.json`): callers' prototypes disagree with the definition for 820
   of town's 3,656 functions, 1,042 of dungeon's 4,836, 577 of slus's 1,260, 168 of main's 800;
   data symbols are declared under several types for 350 / 517 / 152 / 57 of them (the L3 lanes
   invented per-file struct names for shared globals; only 30 sit on a T7 record). Build `tools/gen_decls.py`: one canonical prototype per
   function from its definition, one canonical extern per data symbol (record headers where T7
   has one, the widest consistent scalar/array view otherwise, union views for real conflicts),
   into `include/<container>/decls.h`; then a T12 sweep that replaces a row's local declarations
   with the include, verified per row, refusals journalled (conflicting rows are reader work).
0c. **Module map** (`tools/modules.py check|accept <proposal.json>` validates a proposal —
   contiguity, one load base per module, assertion files respected, full coverage — and writes
   `ledger/modules.jsonl`; inputs per container with call graph + evidence in
   `work/modules_input/<container>.json`, prompt `work/modules_input/PROMPT.md`, Astra proposals
   land in `work/modules_proposed/`): every container splits into sub-overlays by load base (`ledger/splits/*.jsonl`
   `load_base`: town 1,414 rows resident + 46 script modules; dungeon 808 engine + 183 floor
   overlays + 620 unbased rows in `dungeon_deep_t8_*` windows; main 2 halves + card UI); within
   the big resident groups cut at the proven object boundaries (`docs/EVIDENCE.md` §2) and by
   call-graph clusters; `tools/modules.py` writes `ledger/modules.jsonl` and the `l4_modules`
   journal `levels.py` already reads.
1. **Names and modules (L4).** The 12 record headers are the place to name things: a member
   name changed in `include/records/Rec_*.h` reaches every user, and the gate proves it. **Start
   from `docs/EVIDENCE.md`** (2026-09-08): every source of real names is in-tree and joined to rows
   in `ledger/evidence/rows.jsonl` — Konami's assertion sites (15 real source file names with
   line numbers, 39 rows), the developer identifiers the debug prints kept (`OSETDT`, `ost_w`,
   `osel_w`, `cdhd_cnt`, `ov_work.kind`, `gsw->check_sum`, …; the `main.c` triple sits in all 54
   TOWN event-script modules), the randomizer address map (data tables with record layouts, 52
   code sites), the event-script VM handler table (opcode numbering, 72 SLUS rows), 281 prior
   notes, and **the script symbol dump found in the TOWN.BIN devkit blob** (3,587 developer
   constants: `S_` + `FNO_` call numbers → 125 functions named through the script call table at
   `0x800D3CC8` (entry = number + 1; proven by the 2026-09-08 research workflow,
   `docs/evidence/script_call_table_20260908.md`), ready in `ledger/evidence/names_proposed.tsv`; `F_` flags, `SSTP_` steps, `S_`
   system calls, `IMG_`, `PSN_DM_*` ... in `include/script_symbols.h`; `docs/SYMBOLS.md` §5).
   Open (research record §Critic): the 13 shop entries 0–13 that hold group-slot addresses in
   `0x80110E80..` (the bytecode VM's table-of-tables `D_80110E98`), `S_printf` = 34 vs the assert
   macro calling number 89, `FNO_func_sn_casino` = 3 / `S_open_buy_dougu` = 5327, the polymorphic
   word at `0x80016000`, the resident scene registry records at `0x8006ADC0`, and which resident
   routine consumes the `F_` flag numbers. The lane prompt carries the row's block; `levels.jsonl` carries `evidence: [...]`; the
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
  **And scorer-exact is not proof either** (2026-09-08): the scorer links every row at its true
  base, the gate links a row with no recorded true name at its synthetic address (the legacy
  population), so a body whose internal jumps changed spelling (a `goto` where the pinned text
  spelled the jump as a pseudo-call to an absolute symbol) is scorer-exact and wrong in the window.
  Ten dungeon windows failed after the first promotion; `tools/promote.py` now runs the row's
  window gate before a body counts as landed, and the campaign lands through it. `verify.py::
  gate_window` caches per process: never test two texts of one window in one process.
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
