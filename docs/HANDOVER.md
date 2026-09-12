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
- **Batched fidelity lane measured** (30 rows ≤ 200 B the per-row lane had left unchanged, batches of
  five): 20 s and 190k cumulative input tokens per row against 80 s and 232k per row, same verdicts;
  acceptance could not be compared on that population. Adopted for the ≤ 200 B band: `agent_task.py
  --mode fidelity --batch 5`; `tools/campaign_rows.py` writes `work/fidelity_rows_{small,large}.txt`
  and `work/fields_rows.txt` from the live census, and `work/campaign_plan_v3.json` is the next pass
  (small batched → large per row → fields → size tiers). Run `campaign_rows.py`, reset
  `work/campaign_state.json` to `{"tier": 0, "launch": <last launch>}` and launch the controller with
  v3 once v2 prints `plan complete`.
- **Module map drafted and accepted** (`ledger/modules.jsonl`, 5,861 rows): Astra analyses over
  `work/modules_input/*.json` (call graph + evidence per row, one file per sub-overlay group),
  validated by `tools/modules.py` (contiguity, one load base, assertion files, coverage). main 16
  modules (libcard `c_server.c` twice — the shipped and the devkit copy — and the card UI files, all
  proven by assertion sites); town resident 51 themed modules (`player_actions.c`, `town_map.c`,
  …, strong/weak) + 93 script-overlay modules (`main.c`/`lshop.c`/`memory.c` proven, the rest
  `ovl_<foff>.c`); dungeon engine 35 themed modules + 403 floor-overlay modules (mostly one or two
  rows, `ovl_<foff>.c`, weak). Names in the map are proposals until a header carries them; the
  confidence field says which ones rest on evidence. SLUS: 29 modules (`scene_runtime.c`, `message_script.c`, `object_display.c`, …; rows ordered by symbol address). Every counted row (6,745) has a module.

**Plan v2 finished 07:24 UTC:** fidelity 794 rows served (single 218 + multi 199 accepted, 344 rows
cleared of every blocking site, 656 sites removed); fields 96/96 accepted and landed, 0 `FIELD()`
left in them. The closing size tiers served nothing because `ledger/levels.jsonl` was stale (the
controller never regenerated it, so the freshly unblocked rows still read L0); `campaign.py` now runs
`levels.py` before every launch, and plan v3 serves them.

**Traps for the next session:** the controller commits `ledger/agents ledger/promotions.jsonl src`
after every launch — commit your own tree changes (tools, config, ledger) *before* launching it or
they get swept into a campaign commit without their config; a bash `a && b && nohup c &` backgrounds
the whole list, not just `c`; never print a set of window names.

## PICK UP HERE (2026-09-11, late) — then `docs/PIN_PATTERNS.md` section 10

**1,702 rows carry pins, 11,220 live sites** (1,715 / 11,527 at this session's start); **561 fences
in 428 rows** (708 in 505). This session, against c5ab67d1 over 268 rows: **307 pins off, 151 fences
off and 4 added — net −454**. First phase (t20 over every fenced row, the pinned-row pass, t2): 205
rows, net −337, 47 rows left with neither pins nor fences. Second phase (t18 resumed with the shapes
first, the census refresh, agy batches 4–6, the widened `basesym`, t20/t2 after each): 71 rows, net
−117. Every landing byte-exact through the scorer; every touched overlay window re-gated MATCH and
the SLUS SHA-1 gate MATCH after each phase.

### What this session did

- **The fence study's natural shapes are generators** (`tools/xform/natural.py`): `dropcopy`,
  `armstore`, `ret2break`, `ptr2index`, `postinc`, `gotoloop` and agy's base-page `basesym`, each
  written from the pre-images of the rows that shape closed by hand. **`t20_fencefree`** searches
  them per fence (take the fence off; the shapes over the whole function nearest the fence; one
  nearby pin erased too; then the shapes on the text itself where a shape deletes a pin) and lands
  only when pins do not grow and pins + fences strictly fall. Acceptance first: all nine hand-closed
  rows and both agy base-page rows close again from their pre-images, byte-exact, no fence, no new pin.
- **Over every fenced row** (503 rows / 692 scored fences): 122 rows, 151 fences + 21 pins off,
  nothing added, net −172. **123 of the 151 fences were dead** — exact with the fence simply taken
  off; 109 of those sit in rows no t15/t18 fence ever touched: agent lanes wrote them and nothing
  re-tested a fence the way t2 re-tests pins. 7 rows traded a fence for t15's `dup_after_if` (a
  statement written into both if-arms); **owner's call (2026-09-11): keep them** — the same statement
  in both branches is most likely the original's copy-paste, plausible 1997 source, where a fence never
  is (`grep dup_after_if ledger/sweeps/t20_fencefree.jsonl` lists them).
- **The shapes on the pinned rows with no fence** (585 rows where a shape deletes a pin, + 10 fenced
  rows re-run after a `_declare` fix): 83 rows, 121 pins off — `dropcopy` 67, `basesym` 29 (the
  base-page shape is a family: `p = (u8 *)0x80020000; ASM_KEEP(p); p += 0x61C0;` → `p = (u8
  *)&D_800261C0;`), `ptr2index` 3. Then t2 over all 205 touched rows: 39 rows, 44 more pins dead.
- A readability pass: `armstore` now tries `D |= K` first; the three rows it had landed as
  `D = D | K` were respelled (byte-identical, journalled under t20).
- **t15/t18 menus lead with the natural shapes and end with the fence family**
  (`t15_shapes.T._menu(cur, slus)`, `basesym` off for SLUS rows); t15's `dowhile2for` takes a counter
  started in its declaration and a `goto next` before the increment (→ `continue`).

### Start here, in order

1. **[Done]** t18 resumed with the natural shapes ahead of the fences (2,656 rows, 33 min at 16
   workers): **50 rows, 88 pins off, 4 fences added — net −84**. The first pass landed 232 fence
   steps against ~20 real shapes; this one 4 fences against 57 shape steps (`narrow` 34, `dropcopy`
   8, `dup_after_if` 4, `basesym` 3, `gotoloop` 2, `armstore` 1) plus 5 group erasures. t20 over its
   rows found no dead fence; t2 freed 2 more pins. Refusals: 1,684 rows with no pin left, 141 with no
   group within band, **165 with a per-site census stale for today's text** — re-measured
   (`pin_sites.py --sites`, `--subsets`, pairs for 6–10 pins; 10 min) and t18 re-run over them: 8
   rows, 11 pins off, no fence. Re-measure after any sweep that rewrites many pinned rows, or t18
   and the agy pack builder go blind on exactly the rows that just changed.
2. **Make t20 a standing sweep after every lane or campaign landing**, the way t2 is for pins: a
   fence is scaffolding census counts like a pin, and nothing else re-tests one.
3. **[Done]** agy batches 4–6 (owner-launched, Gemini 3.8 Flash High): lanes claimed 7 of 24, the
   harvest accepted 6 (the 7th, `town/func_8081E410`, was cut from a text a sweep rewrote today),
   all 6 landed through `apply_candidates --transform t13_depin` from a fresh dir: an over-declared
   callee prototype trimmed to the argument it takes (`dungeon/func_80092658`), a load folded into
   its consumer (`town/func_800B1544`), a hand-expanded `/4` written back as `/`
   (`town/func_800BF718`), the division bias as explicit branch arms (`town/func_800C242C`), block
   temps folded into the store (`town/func_800C5DFC`), and the base-page shape on an INTEGER local
   (`town/func_8080C324`) — which `basesym` now takes too (uncast literal, integer local): over the
   128 pinned rows it then reached, 8 more rows, 9 pins off. Pack totals: 11 of 48 rows landed.
   **Pack 2 is built: `work/agy_groups2`, 793 rows in 100 batches of 8, best-first** (batch 1's
   rows are one word from pin-free), cut after every landing and gate of 2026-09-11 with the 48
   served rows excluded; its brief lists what the machine already tries. Launch (owner):
   `! AGY_PACK=work/agy_groups2 bash ~/agy_lane/go.sh "Gemini 3.8 Flash (High)" batch1 batch2 …`,
   then `python3 ~/agy_lane/harvest.py --model "Gemini 3.8 Flash (High)" --pack <repo>/work/agy_groups2`.
   **Land only from a fresh dir** — harvest stages into a cand dir shared with older candidates —
   through `apply_candidates.py <dir> --transform t13_depin`, then t20 + t2 over the landed rows.
4. Unchanged from the section below: the shared control-flag unit (`dungeon/func_80091258`,
   `func_80087054`) and the address-materialisation second handle (`dungeon/func_8098D5A8`).

### 2026-09-12 (owner's standing goal: keep working the pins, free rein, decisions documented)

- **Research:** `work/research/sotn_findings.md` (sotn-decomp, ygofm-decomp, permuter forks; BFM not
  repeated) — levers summarised in PIN_PATTERNS section 10. First one mechanised:
  `natural.splitcursor` (one name per chain step): 3 rows, 3 pins.
- **The permuter is wired to this tree:** `tools/permute_pins.py` (strip a close row's pins, build
  `target.o` from its own pinned byte-exact text with `tools/permute_cc.sh`, run the old
  decomp-permuter (the old checkout's patched copy and venv; `$PERMUTER_DIR` / `$PERMUTER_PY`), judge score-0 outputs with
  `verify.py`, transplant the function back into the file). **Trial: 0 of 12** close rows (1-4-word
  strip residue, 10 min x 3 threads each, `work/permute_trial/`): best scores 5 on three rows, but
  one needs a behaviour-changing `u8` truncation and two are the known ASPSX `ori $rx,$zero,imm`
  dialect (an assembler dial, not C). Not scaled into a long job; kept for targeted use - its real
  yield was a generator gap (`((u8 *)v) + K`, `basesym` now takes it).
- **The long CPU job instead:** t18 deep and fence-free - `T15_WIDE=1 T15_NOFENCE=1` (t15's whole
  generator set, the natural shapes first, no barrier at all) with raised budgets, over every row with
  a pin group in band.
- **Controversial-in-waiting, not done:** sotn's `FAKE` convention (plain-C stand-ins for allocator
  ties). Not mechanised - census cannot see it; adopting it needs a counted `FAKE` note first.
- **`t21_crossjump` (an Opus agent built it from the native lane's rewrite; report
  `work/native_lane/crossjump/REPORT.md`):** m2c's cross-jump gotos undone at statement level (sink the
  shared tail into every predecessor, forward-substitute the temporaries, substitute link-time
  constants, try the swapped arm order). Acceptance 7/7; **102 rows landed, 107 pins off**, then t2 over
  them freed more in 20 rows; 98 touched windows MATCH, SLUS MATCH. Misses worth a lane: a 17-row
  family (one function, 17 overlays) 2 words off where the erased variable serves a second use.
- **The scratchpad class (native lane, `work/native_lane/scratchpad/REPORT.md`):** mechanism found
  (combine folds `addu base,K` into `ori` on a constant base; a REAL loop, not m2c's phony goto loop,
  lets loop.c substitute first). One row closed, `dungeon/func_800942BC` - its landing waits for the
  deep t18 pass to finish (a sweep overwrites a file it read earlier).

### Rules learned today

- **The harvest proves the scorer, never the window.** Pack 2 batch 1 (owner-launched): the lane
  claimed 1 of 8 and the harvest accepted it (`dungeon/func_8185CE28`, 4 pins and an asm clobber
  gone), but its window gate failed — the lane had respelled a `noreturn` jump to the row's own
  epilogue (`func_800247B4()`, listed in `config/noreturn_syms.dungeon.txt`) as `return`. The row has
  no true name, so the gate links it at its synthetic address, where the local epilogue jump encodes
  a different target from retail's absolute one. Reverted (journal `t13_depin`, `gate-mismatch`);
  **batch 1's yield is 0 of 8.** Batches 2–3: each lane claimed 1 of 8; one was refused by the
  harvest (a raw asm body), one landed and gated MATCH — `dungeon/func_8132A730`, the base-page
  shape through an integer cast (`resource_addr = (s32)0x80170000; … += 0x1D90;` →
  `(s32)D_80171D90`), which widened `basesym` again (integer cast on the literal): 9 more rows, 9
  pins and 2 fences off. Pack 2 so far: 1 of 24 — against 11 of 48 for pack 1, whose rows had not yet
  been through the natural shapes. Measure a few more batches before spending real capacity on it.
  Gemini on pack 2 batches 4–5 is on hold (owner, on advice): every row there is one word off, mostly
  `broad`, and the batch 2 report shows those last words are operand order and register-source ties.
- **Targeted Opus pack, launched 22:37 UTC (agent-launched; go.sh was not blocked):**
  `work/agy_opus1`, 12 pack-2 rows in 3 batches of 4 — groups of 3+ pins or a row's only pins
  (one win frees several), residue ≤ 2, not `reg-rename`, every row with a true name (no batch-1
  gate trap); up to 40 pins if every group falls. Harvest when it exits:
  `python3 ~/agy_lane/harvest.py --model "Claude Opus 4.6 (Thinking)" --pack <repo>/work/agy_opus1`,
  land from a fresh dir (`--transform t13_depin`), t20 + t2, **window-gate before committing**.
  **Result: the agy Claude quota ran out during batch 1** (`Individual quota reached … Resets in
  135h45m` at ~23:07 UTC, i.e. about 2026-09-17 14:50 UTC; Gemini's pool is separate). Batch 1 left no
  candidate; before the quota hit, the lane named one blocker — an `ASM_KEEP_NV(scratch)` pin that
  keeps the `0x1F800000` scratchpad base from being constant-folded, with no C equivalent found.
  Batches 2–3 never ran (the run was stopped). Re-run them after the reset if still wanted.
- **Native lane (owner: "if 4.6 opus doesn't find any value, use an agent here natively"):**
  launched 23:08 UTC on `dungeon/func_8098D5A8` pin site 3 (`anim_table ASM_REG("$5")`, the
  address-materialisation second handle, PIN_PATTERNS 8a) with `work/native_lane/func_8098D5A8/BRIEF.md`.
  **Result: closed, byte-exact, 27 scorer runs** (`work/native_lane/func_8098D5A8/REPORT.md`). m2c's
  `goto` was its rendering of jump2's cross-jumping between two separate calls; each arm making its
  own call, with the temporaries substituted into the call, makes the arm one block, and
  local-alloc's priority order then gives the address `$a1` by exclusion. The same rewrite
  (`scratch/xform.py`) closed the row's six siblings: **7 rows, 7 pins, journal `t21_crossjump`**.
  **Next: build it as a statement-level generator in `tools/xform`** — 90 pinned pointers sit behind a
  goto whose label starts with a call (the cross-jump rendering); the template only matches these 7.
  Undoing the goto and substituting are mechanical; whether the register lands right is a post-sched1
  priority margin, so every candidate must be scored (the oracle's block trace is a cheap pre-filter). Gate every agy landing before committing it, and expect this on any
  row with no `true_name` whose pins sit on a noreturn/label-as-call jump — those pins are fidelity,
  not shape.
- **A fence is re-testable debt, like a pin**: 18 % of the fenced rows' fences were dead.
- **The smallest closing step is often less than the lane's edit** (8009A874: the lane rewrote the
  goto/return structure; `ptr2index` alone closes it) — test a lane win one piece at a time on its
  own pre-image before building the generator.
- **The study's sample over-states a shape's reach**: "a third are natural shapes" became 4 % of the
  corpus's fences; the shapes that carry are the ones that are also pin shapes (`dropcopy`, `basesym`).
- **A generator that edits and then checks its own output checks nothing**: `_declare` looked for the
  new symbol in the edited text and never declared it (every candidate needing a fresh `extern` failed
  to build until the fix; 10 rows re-run).

## PICK UP HERE (2026-09-11, evening) — then `docs/PIN_PATTERNS.md` sections 4, 8 and 9

**1,715 rows carry pins, 11,527 live sites** (1,717 / 11,872 at the afternoon's start); every
landing gated (every touched window re-gated MATCH, no SLUS row touched). **Read the fence line
before quoting a pin count:** `census.py` counts a `do { stmt; } while (0)` fence "like a pin", and
most of the day's removals were that trade. This session, measured against 019f5c9a over 174
rows: **345 pins out, 221 fences in — net −124**; 3 rows now carry neither; STATUS's
`do{}while(0)` row went from 365 to 502 rows. Report the net, never the raw pin count.

### What this session did

- **Pairs census for the 6–10-pin rows** (`pin_sites.py --subsets --min-pins 6 --max-pins 10
  --max-k 2`: 9,528 pairs / 368 rows, 18 min at 12 workers) and **pin groups**
  (`pin_sites.pin_groups`; `--groups` prints the histogram): two pins are one unit when their pair
  erasure shares (almost) all of the smaller one's residue AND their retail word ranges meet —
  the report's `joint < sum` chains a ten-pin row into one group, i.e. the strip again. 980
  multi-pin groups, 417 within 12 words.
- **t18_groups** (erase the cheapest group; then t15's menu nearest the group; then each pin
  alone) reached rows t15's whole-row band never admits: **164 rows** before the owner stopped it
  at ~4,200 of 6,767 — but 232 of its steps were fences. It now tries real shapes first
  (`_is_fence`). It resumes where it stopped (`sweep.py t18_groups --workers 16`; the journal
  skips rows it already tried) — **do not resume it until the natural-shape generators (below)
  run ahead of its fences.** Three in-flight writes of the killed sweep had no journal record and
  were reverted to HEAD.
- **t19_modpow2** (`%` on `idiom_search`): 2 rows / 2 pins; the arm-reads-the-copy rule does not
  predict a row (PIN_PATTERNS 6). t2 over everything t18/t19 touched: 19 rows of newly dead pins.
- **The fence study** (PIN_PATTERNS 9; an Opus lane, 22 rows, every exact re-verified here): the
  owner's compiled-out debug-hook theory is byte-compatible (an empty fence matches at 22 of 24
  sites) but not supported by position (one specific side of one statement; function entry 0/20;
  two fences work through allocation weight, which no empty loop can). **9 of 22 rows (8, then 1 more on a follow-up over five near misses) hide a
  natural shape — landed as `t20_fencefree`**, two rows now free of pins and fences; 2 share a
  macro-like unit (only worth it as a real named macro); ~55 % are barriers and nothing else.
  `census.py` now also counts `while (0) { }` and `for (;0;)` (byte-identical barriers).
- **Measured before any lane:** address materialisation (PIN_PATTERNS 8a — the pin ties the `%hi`
  pseudo by `sugg=5`; m2c's one-variable-for-two-arms is what loses the tie; a second handle for
  the register choice is still missing) and the sign-extension copy (8b — on the traced row the
  site is held by the row's other `ASM_REG` pins, not a `narrow` case).
- **agy group packs:** `pin_lane.py --groups` → `work/agy_groups` (48 rows, 6 batches; 217
  qualify), `GROUP_MODE` understood by `~/agy_lane/go.sh` and `harvest.py`; the briefs forbid
  fences and the harvest rejects any candidate with more fences than its base. **Batches 1–3 ran
  (Gemini 3.8 Flash High): lanes claimed 5 of 24, all 5 landed and gated — 6 pins and 2 fences
  off, nothing added.** Shapes: a direct symbol for hand-built base-page arithmetic
  (`town/func_8050E100`, `func_8077DC0C` — `(u8 *)0x80010000 + 0x601C` → `&D_8001601C`: the
  literal-page family `litsym` never closed); a value-preserving `(s16)` at the use
  (`town/func_800B63B8`); a local widened to its partner's mode (`main/func_80010258`); the outer
  return variable instead of a block temp (`town/func_805D3370`, accepted by hand — the lane had
  to rename a marker pin's argument, which the harvest's strict check rejects). Batches 4–6 are
  unrun: `! AGY_PACK=work/agy_groups bash ~/agy_lane/go.sh "Gemini 3.8 Flash (High)" batch4
  batch5 batch6`, then `python3 ~/agy_lane/harvest.py --model "Gemini 3.8 Flash (High)" --pack
  <repo>/work/agy_groups`.
- **Arm collapse lands** (`pin_census.landing_refusal`): `town/func_8050E100`'s lane dropped the
  `#ifdef NON_MATCHING` split because the port arm's own `D_80017618 = func_80017560;` is
  byte-exact for retail too — the row is now free of pins and fences. The guard used to refuse any
  change to port text; it now accepts one when `port_view` (what `-DNON_MATCHING` compiles, minus
  barrier wrappers and no-op pins) is identical and no `#if 0` text changed. Tested both ways.

### Start here, in order

1. **[Done — see the late section above.]** **Build the fence study's six natural shapes as generators** and run them over every fenced
   row BEFORE any new fence: drop a copy and use its source; the store / `|=` / `&=` in both
   if-arms instead of a join temp (extend `dup_after_if`); `return` in a loop → `break` + return
   after it; a pointer walk → an array-indexed `for`; the post-increment folded into its use; a
   goto loop whose increment m2c duplicated into each arm → a real `do { } while` with the
   increment once (`town/func_800B6514`). The nine `t20_fencefree` rows are their test cases. Then
   put them ahead of the fence family in t15/t18's menu and resume t18.
2. **[Generator done — `basesym`, 29 rows, late section; agy batches 4–6 still unrun.]** **A generator for the base-page shape** agy found twice: a pointer built as a page literal plus
   an offset (`p = (void *)0x80010000; p += 0x601C;`, or `base + 0x7618` through a cast) becomes
   the symbol at the sum (`&D_8001601C`), declared if missing; try it with the neighbouring pins
   and fences erased too, as the lane did. Then agy batches 4–6. **Land only from a fresh dir:**
   `harvest.py` stages into a cand dir SHARED with older staged candidates — copy the new rows and
   their `.base_sha` into a fresh dir and `apply_candidates.py` that, never the whole cand dir.
3. The shared control-flag unit (`dungeon/func_80091258`, `func_80087054`): decide whether a named
   macro in a shared header is honest (it frees a pin in 80091258; inline it is net zero).
4. Address materialisation: the second handle on `dungeon/func_8098D5A8` with the instrumented
   cc1 (kept with the compiler sources in the old checkout — the in-tree `toolchain/compiler-src`
   path in older notes is stale; drive it by hand: this tree's `gcc -E`, then it and the shipped
   cc1 on the `.i`).

### Rules learned today

- **The net scaffolding change is the figure**, not pins removed.
- **A killed sweep can leave a written file with no journal record** — reconcile `git diff` against
  the journal's `out_sha` before gating; gate by the tree, not the journal.
- **Inlining a symbol while its variable stays is inert** (cse folds the uses back into it).
- **An equivalence the census cannot see is a way to hide debt** — count every spelling of a
  barrier (the `while (0)` / `for (;0;)` fix).

## PICK UP HERE (2026-09-11, afternoon) — then read `docs/PIN_PATTERNS.md`

**1,717 rows carry pins** (1,729 live at this session's start), every landing gated (window gate +
SLUS SHA-1). STATUS's "Pin sites" line now prints the live count next to the at-the-pin count;
the old line (25,788) was the frozen text at the pin, not the remaining debt (12,041 live at the
start of this session).

### What this session did (≈148 pins off, 12 rows cleared)

- **Plumbing first, as the section below says** (a04b050a). Three pin tools refused a row outright
  when the text contained the substring `NON_MATCHING` (189 pinned rows; in 105 every pin sat
  outside any such arm; 52 within 12 words of pin-free) and on an asm-body regex that matched asm
  LABELS (`__asm__("func_…")`, 80 of 82 refusals). Now `pin_census.arm_labels` labels every line
  match/port/dead/both; a pin in a port-only arm is not a pin (21 phantom sites in 12 rows); a
  candidate that edits code no byte gate compiles is refused in `sweep.py` and at landing, where
  the port front end (`portability_lint.port_compile_refusals`) also runs.
- **The "~109 race rows" lead below was a record count**: 90 distinct rows were ever refused by
  the race, 9 still were, all outside the band. Spent.
- t2 over the 95 rows its journal was stale for: 13 landings (the standing rule holds again).
  t15 over the 280 unlocked rows + the refreshed ones (`T15_BAND=20`, WIDE, budget 140): 9 closes -
  6 from the NON_MATCHING unlock (2 `narrow`, 2 `fence2`, 2 `fence`), 3 from rows t2 had just
  refreshed, none from the asm-label rows (4 in band).
- **`tools/pin_sites.py`** — the per-site census on the live text (9,249 sites, each erased alone,
  scored with word positions, next to what the site is) and every subset of the 2..5-pin rows
  (5,018). Its analysis is `docs/PIN_PATTERNS.md`.
- **t16_absidiom** — found by reading the census's largest one-word cluster, not harvested from a
  lane: m2c's `d = s; if (s < 0) d = -d;` is MIPS `abssi2` (one insn, invisible to cse); written
  back as `abs()`, **36 rows, 75 pins off, 3 rows pin-free**, on rows t15's band never looks at.
  Its greedy search is `idiom_search`, shared by the next idiom plugin.
- **t17_divpow2** — the signed power-of-two division idiom, 108 rows eligible, **2 rows**. Kept as
  the measurement: m2c's bias spelling reads the SOURCE in its arm, so cse has nothing to fold and
  the text already reproduces retail (in 64 rows the `/` rewrite is byte-identical).
- **`pin_subsets`** — 12 exact proper subsets (pairs/triples of 4–5-pin rows) that no tool had
  tried; the largest per row landed: 10 rows, 22 pins.

### The owner's three questions, answered by measurement (details: PIN_PATTERNS.md)

- *20–30 patterns?* Yes at the level of mechanism — 24 macro-family × residue-class clusters
  cover 80 % of the live sites, 37 cover 90 %. No at the level of fix: the exact instruction
  change has a long tail, so a pattern needs its APPEARS condition, not just its label.
- *Do nearby pins interact?* 40 % of pin pairs hold the same instructions (52 % within 3 lines),
  and 32 % of pairs 16+ lines apart still do. 29 pairs fall only together.
- *Is one pin of many progress?* Yes, and it compounds: half of t16's rows shed pins the rewrite
  did not touch (`dead:` steps), and partial landings move rows into the band that closes.

### Start here, in order

1. **Group-aware search.** Pairs for the 6–10-pin rows (`pin_sites.py --subsets` with a pairs-only
   mode, ~9,000 scorer runs), then feed t15/idiom plugins/lanes a pin GROUP.
2. **The `%` idiom** on `idiom_search` (33 remainder sites) — check the arm-reads-the-copy
   precondition first.
3. **Address materialisation** (FOLD-`addiu`, 124 sites / 99 rows, mostly `ASM_REG` on pointers
   from globals): measure with the instrumented cc1 which cells split `%hi` into its own pseudo
   before briefing any lane (lanes 0/4 on `addressing`).
4. **FOLD-`sll`** (43 sites): widen `narrow` after finding its missing precondition by hand.
5. Before targeting from the census, re-run `pin_sites.py --sites` on the rows landed today: its
   records are keyed by `in_sha` and the analysis ignores stale ones.

### Rules learned today

- **Count the sites where the hand spelling's branch arm reads the copy**, not the sites where an
  idiom appears: that is what decides whether a compiler-idiom rewrite frees pins (abs: 36 rows;
  division: 2).
- **A candidate built from an older text must be checked against the row's current sha before it
  lands** — `apply_candidates` only checks exactness, so a stale candidate silently reverts a
  later landing. Now built in: `pin_sites.py --land-dir` writes a `.base_sha` sidecar next to each
  candidate and `apply_candidates.py` refuses one whose sidecar differs from the row's current
  sha. Lane packs (`pin_lane.py`) do not write the sidecar yet - add it before the next pack.
- **A substring test is a blind spot.** `"NON_MATCHING" in text` hid 189 rows from three tools for
  weeks. Grep the tools for `in text` refusals before trusting any "refused" count.

### Checked, in proportion, and left over

- **In proportion:** 148 pins is 1.2 % of the live sites and 12 rows 0.7 % of the pinned rows. What
  carries is the method: a generator built from a census cluster's MECHANISM (t16) transferred to
  36 rows, where ten of eleven lane-harvested generators had closed zero; and the pattern question
  has a measured answer at two granularities instead of an opinion.
- **Port arms:** 20 rows landed today carry a NON_MATCHING arm. In 13 an edited line names an
  identifier the port arm also uses - every one a pin erasure (a no-op in the port build) or a
  fence around a macro call; neither `narrow` retype in those rows touches a port-arm identifier.
  The byte gate proves the matching arm and the landing guard proves the port arm still compiles;
  neither proves the meaning of a declaration both arms share, so a retype of a port-shared
  variable should be checked by hand.
- **Phantom pins:** the 21 port-arm pins are no longer counted but are still in the text. Erasing
  them is pure cleanup, but the landing guard (rightly) refuses edits to port arms, so it needs a
  one-off script.
- **Lane pack ready:** `pin_lane.py` now sees the unlocked near-band rows; a pack over what t15 left
  is one command for the next agy launch (recipe in the section below).
- **Tables regenerate:** `python3 tools/pin_patterns.py --history > docs/PIN_PATTERNS_DATA.md`
  (coverage, signatures, rename kinds, linkage, and every landed pin removal replayed from git).
- **Trap fixed: rebuilding the gate root broke the scorer.** `mk_ovl_root.sh` symlinked
  `build_ovl/work/g3/overlay_func_compare.py`; that module finds `match.py` as
  `Path(__file__).resolve().parents[2]/tools`, which through the symlink is the repo root, so after
  a rebuild every `verify.py` run returned `HARNESS-ERROR ... tools/match.py`. The window gate does
  not use that path (it passed 51/51 throughout), and nothing landed through the broken scorer.
  The standing root had kept a real-file copy since 09-07 and was not rebuilt until today; the
  experiment roots (`build_ovl_pins/_lac/_passthru`) had the symlink. The script now copies a real
  file, and the three experiment roots were repaired in place.

## Earlier the same day (2026-09-11, ~05:00 UTC)

Tree is clean, fully gated (2,172/2,172 windows + SLUS SHA-1 MATCH) and everything below is
committed. **1,732 rows carry pins**, from 1,968 at the start of the 09-10 session.
`STATUS.md`, `docs/PIN_FAMILIES.md` and the census are current and now agree with the pin
machinery by construction.

### Start here, in this order

1. **Re-sweep the ~109 remaining race-recovered rows.** This is the highest-value lead and it is
   pure recovered ground, not retries. `strip_census()` had a lazy-init race (fixed b54533ce) that
   refused **136 rows** across every threaded sweep - including 13 in the 11-hour full pass - with
   the message "no strip probe for this row", which reads like missing data. Those rows were never
   searched at all. Of the 27 that were in band and swept afterwards, **one closed outright**
   (`main/func_8000F160`, 1 -> 0) and another (`town/func_800A383C`) fell to the first model that
   looked at it. Find them with: journal entries whose `reason` is "no strip probe for this row"
   and whose latest record still says so.
2. **Point agy/Gemini at the fresh screen.** `tools/pin_probe.py --strip` is current; the screen at
   `strip <= 6, residue <= 8, size <= 1600` gives **45 boost / 88 stop / 43 ok**. The `boost`
   marker (retail's residue register set a strict SUPERSET of ours -> "fold the load") is a real
   selector: the packs built from it went 3/27 and then **8/17**. Build a pack with
   `tools/pin_lane.py --only-rows <file> --band 8 --size 8 --out work/<name>`, launch with
   `! AGY_PACK=work/<name> bash ~/agy_lane/go.sh "Gemini 3.8 Flash (High)" batch1 batch2 ...`,
   harvest with `~/agy_lane/harvest.py --model "..." --pack <abs path>`.
3. **Mine the six unmechanised shapes** in the 2026-09-11 wins (logs in `~/agy_lane/log/`):
   early-exit/branch-polarity restructuring, m2c's `var = 0; ... return;` written back as
   `return 0;`, pointer-decrement idiom -> array indexing in a loop, a cascaded `if` tree written
   back as the `switch` it came from (defeats extended-basic-block CSE), and an internal-jump
   epilogue retype. **Count the population before writing a generator** - see below.

### Per-class hit rate (agy/Gemini, 44 rows served across two packs)

| pays | | dead loss |
|---|---|---|
| block-order 1/1, code-motion 1/1 | dead-code-retention 2/3 | delay-slot **0/7** |
| length-drift 3/8 | li-expansion 1/2 | addressing **0/4** |
| | const-remat 0/2 | slot-rotation **0/1** |

Drop the three zero classes from any launch order. `ASM_TAILSLOT_PIN` is 460 sites at **0%
removable** in the census, and the delay-slot rows keep reconstructing that same wall.

### The lesson that should change what you build next

**Harvesting a hand win into a sweep generator does not pay; auditing the pattern-matching layer
does.** Three generators were built this session - `litsym` (8d10909a), `livetie` (a55c8b6c),
`dowhile2for` (8e89f6c6). Each reproduces its source row(s) byte-exact, and **all three closed zero
new rows.** `dowhile2for` was even built to a counted population (41 matching rows, 9 in band) and
still returned nothing. That is now ten of eleven harvested shapes at zero, and the file's own menu
comment says the same. Keep them in the WIDE menu as hill-climb contributors - partial removals are
real wins, and 64 of the main sweep's 89 landings were partials - but do not expect a close.

Every genuine gain this session came from fixing the plumbing that decides **which rows get looked
at**, not from new shapes:

- `DECL_RE` could not see `register u32 x;`, hiding locals from maskfold/narrow/retype (57569692).
- `pin_census.sites_of` could not see a pin wrapped in a local macro: **127 sites invisible to
  every tool**, 30 files de-macroed byte-exact, two rows entirely invisible (548963e9). That
  immediately produced the first strip-exact rows and two free landings (53bf9cb4).
- `census.py`/`status.py` counted `ASM_x(` over raw text, so a pin NOTE in a comment kept a freed
  row counted as pinned - drift that grew with every success (31f87591).
- the `strip_census` race above (b54533ce), worth 136 rows.

So: before building another shape, ask what the tooling cannot currently see.

### Rules for mechanising, if you do it anyway

State all three before writing code, and count the third:
**APPEARS** under what textual condition · **RESOLVES** by what compiler mechanism · **POPULATION**
how many other pinned rows match. `dowhile2for`'s docstring is the worked example. A population of
one means it is a row, not a class.

### Traps hit this session

- **`pgrep` self-match cost two hours.** `while pgrep -f "[s]weep.py t15_shapes"; do sleep 30; done`
  inside a `bash -c` matches **itself**, because the waiting shell's own command line contains the
  pattern. The bracket trick only protects against the `pgrep` process. Put the work in a script
  FILE and wait on recorded PIDs - `~/agy_lane/finish.sh` is the working shape.
- The scrub hook rejects an absolute home path anywhere outside `raw/` and `src/`, including in a
  code comment that merely quotes one. `apply_candidates.py` now records an out-of-tree lane's
  directory NAME (e8440498).
- Two lanes on one pack overwrite each other's candidates; `go.sh` now writes `out_<model>`.
- `gate_all.py` covers overlay windows ONLY. Always follow with `tools/build/build_slus.sh -j 6`.

### Lanes (both outside this repo, by owner instruction)

`~/agy_lane/` (agy = Antigravity CLI; `go.sh`, `harvest.py`, `compare.py`, `finish.sh`) and
`~/or_lane/` (OpenRouter; `or_agent.py` 3-tool loop, `or_key.sh`). READMEs in each. Claude Code's
classifier blocks agent-side agy spawns from a plain foreground call - launching via
`nohup env ... bash ~/agy_lane/go.sh ... &` worked. **Quota:** Gemini 3.8 Flash (High) sustained
~3 h of lane work; **Opus 4.6 gets ~27 minutes per ~4.5 h window - give it ONE batch, never three**,
and in its one window it made **zero `verify.py` calls** and landed nothing, which is why the brief
now orders a lane to score within its first few minutes. Cheap OpenRouter models (qwen3-coder-next,
agentic, 16 turns/row) went **0/6 for $0.17** and never beat the text they started from.

## Session 2026-09-09 (evening) — the pin burn-down, after the Codex credit ran out

The Astra plan finished (`work/campaign_state.json` tier 6, `plan complete`) and the Codex credit is
gone, so the pin population is now worked with Opus/Sonnet lanes on top of machine measurement.
**Start at `docs/PIN_FAMILIES.md`** (generated by `tools/pin_probe.py --report`).

**The measurement that was missing.** `tools/pin_census.py` scores one pin at a time against the
*frozen* pinned text, and T2's journal scores one pin at a time against the reduced text. Neither
answers what a family campaign needs: erase **every** pin of the row at once and score what is left.
`tools/pin_probe.py --strip` does that for all 1,962 pinned rows and journals the residue in
`ledger/pins_strip.jsonl`: the strip damage, the scorer's residue class, and inside 12 words the
aligned-**regions** view (`--regions`, never `--diff`: a one-word insertion reads as one region there
instead of hundreds of shifted positional rows). Result: 6 rows at damage 0, 134 at 1-3, 295 at 4-8,
471 at 9-20, 1,045 at 21+. **624 rows are within 12 words of pin-free** and that is the worklist; a
row 40 words out is a rebuild and costs the same to attempt as one 2 words out.

**Journal staleness was worth 65 rows for free.** T2 and T9 both gate on journals keyed by `in_sha`,
and the Layer-2 campaign replaced 4,346 bodies: 905 of the 1,968 pinned rows carried text T2 had
never seen, so T9's per-site classes were fiction (12,247 refusals against 13 applications).
`sweep.py t2_pins --only <the stale rows>` erased 191 more sites in 65 rows. **Standing rule: re-run
t2, then t9, after any wave that rewrites bodies.**

**T2 is greedy, so a pin set that only falls together survives it** — the strip probe found 6 such
rows (12 pins), landed through `apply_candidates.py --transform t13_depin`.

**The wrong-cell family pays.** `tools/pin_probe.py --cells` scores a row's *stripped* text at all
14 stock cells in ONE scorer run (pass `cfg` as a comma-joined list, each entry carrying its own
`-I`; the scorer reports BEST). About 8 % of the near band is pin-free at another cell — nearly all
`2.7.2-cdk(-G0)` — and in every case the row's *pinned* text is exact there too. Those pins were
describing the wrong compiler, not the source. `tools/pin_cells_land.py` lands them under a written
rule: the pin-free text is exact at B, the pinned text is exact at B as well so no byte evidence is
lost, and the module's cell distribution is reported alongside. (This is the campaign's old K2
"config reroute" found mechanically rather than by hand.)

**Lane results (five packs, ten rows each, one residue class per lane).** Sonnet on `broad`,
`reorder-only`, `length-drift` and `li-expansion`; Opus on `reg-rename`:

| class | exact | what closed the rows |
|---|---|---|
| reorder-only | 6/10 | `do { stmt; } while (0)` as a zero-byte scheduling barrier (see below); the same wrapper on a `return` keeps the value-to-`$v0` move ahead of the callee-saved restores |
| reg-rename | 5/10 | m2c's hand-expanded `x % (1<<n)` written back as `%` (gcc's `expand_divmod` re-emits it with its own `copy_to_mode_reg`); giving the two operands of an equality test different modes to stop `record_jump_equiv` merging their cse class; declaring a mask temp at the load's width |
| broad | 4/10 | folding a load into the expression that consumes it instead of pre-loading an accumulator - that is what flips which pseudo becomes `rs` vs `rt`; symbol substitution for `ori`->`addiu` **when the value is not later a call argument** (it regressed two rows where it was) |
| length-drift | 4/10 | a `u32` local plus an explicit `& 0xFF` on an `lbu` result (the mask folds away - declare the local `u8` and drop it; two sibling rows fell to it unchanged); a "dead" store before a call that is really an argument to an under-declared callee; duplicating a call into both arms with literal arguments to dodge gcc's if-conversion |
| li-expansion | 2/10 | the page-base substitution plus a second non-folding set, chosen by score rather than assumed |

**The `reg-rename` class is reachable, and the mechanism is now known.** This matters because the
class is the largest in the near band (85 rows) and because a cheap probe makes it look impossible:
25+ variable-map shapes across five rows (split, merge, drop the local, move or block-scope the
declaration, swap which name is tested against returned, copies in both arms, self round-trip, dead
init, operand-order flips, same-mode retyping) returned **byte-identical output every time**.  The
reason is that the residue is not a colouring preference at all: retail's build holds *two live
pseudos carrying the same value*, and gcc-2.7/2.8's cse collapses a plain `b = a;` into one pseudo
whenever both stay live, after which the allocator has no choice left.  That is what `ASM_KEEP_NV`
and `ASM_REG` were standing in for.  Two handles defeat the collapse:

1. **A value-preserving *mode* change on one side of the copy.**  `u16 x = <s32 expr>` is not a
   REG-REG set in RTL, so cse never enters the two into one quantity and both keep their own
   colours.  Pick a narrowing the code already pays for - `(u16)(angle + 0x100) & 0xE00` hides the
   re-widening inside a mask that was already there and costs zero words, where the `s16` spelling
   costs two because `sll/sra` cannot be folded.  The same idea stops `record_jump_equiv` merging
   the cse class of an equality test's two operands when they are given different modes.
2. **The copy is an m2c artifact of a compiler-generated idiom.**
   `q = x; q >>= n; if (x < 0) q = (x + m) >> n; r = x - (q << n)` is `x % (1 << n)`.  Written back
   as `%`, gcc's own `expand_divmod` re-emits the sequence with its internal `copy_to_mode_reg`,
   which is immune to the collapse, and gcc picks the duplicated-shift or shared-shift form per site
   by itself - do not hand-write one form.  One edit each closed two rows.  **When a reg-rename
   residue sits inside an arithmetic sequence, look for a hand-expanded compiler idiom before
   touching any variable.**  (A deliberately narrow regex for this shape finds only 5 rows corpus
   wide; widened to the spellings gcc's bias-then-shift lowering actually takes -
   `if (x < 0) x += K;` before a `>>`, and the `- (q << n)` that reconstructs the remainder - it is
   **35 rows that still carry pins**, and one lane of ten contained two of them.  That is the
   population for a sweep; the loose half of the matcher needs a false-positive check first.)

The rows that resist are the ones where neither handle exists: full-width same-value copies where
narrowing is not value-preserving, and branch-derived *constant* knowledge from `record_jump_equiv`,
which is not register naming at all despite the class label.

Two things the lanes taught that change how to run the next one:

- **`--regions` is a free exact oracle.** It prints the same `TOTAL` line as a scored run and says
  `*** MATCH ***` at zero, so a whole search can run at zero budget with one scored verify for
  confirmation - two lanes closed their rows on **4 scored verifies out of a possible 120**. The
  caveat is that a *build failure* also produces no `TOTAL` line, so distinguish "no TOTAL" from
  "MATCH" explicitly or a syntax error reads as a win.
- **The class label is not always the mechanism.** Two rows labelled `reg-rename` are really
  constant propagation (`move $v0,$zero` against `move $v0,$s0`): cse choosing between a literal and
  a register it has proved holds the same constant, knowledge that comes from `record_jump_equiv` on
  the guarding branch. Reshaping variables cannot reach them.

**`do { one statement } while (0)` is scaffolding, and it is now counted.** It is a zero-byte
scheduling barrier that pins a definition point, and it closed five of the six `reorder-only` rows.
A bare block does **not** reproduce it - only the loop note does - so it is compiler-steering in C
clothing, not a recovered source shape. It is landed anyway (ordinary portable C beats a
non-portable asm pin for the port), but `census.py` and `status.py` now count it so the debt appears
in STATUS.md instead of vanishing from the pin count. It is not new: 226 rows carried it at the pin.

**T9 was re-run over all 1,918 pinned rows with `--force` after the T2 refresh, and applied 0.**
Every row refused at *eligibility*, in 31 s, without spending a single verify - so T9's binding
constraint is its **menu**, not the stale gate that made its old 12,247-refusal figure look damning.
The refusal histogram is the shopping list for extending it: `ASM_KEEP` outside the menu 258,
`ASM_REG` class `addressing` 222, `broad` without a colouring signature 152, `reorder-only` 102.
Three of those four now have measured recipes from the lanes above.

**`pin_probe.py --report` is self-cleaning.** It counts only records whose `in_sha` still matches the
row's current text, so a row landed pin-free drops out of the worklist instead of lingering as a
phantom candidate.  After this session's landings the near band is **586 rows** (112 at damage 1-3,
279 at 4-8), down from 624.

**Sweep tuning, measured over 4,368 row-attempts (for the run after this one).**  A win is found
after a median of **19** probes; 78 of 141 wins landed within 20 and 119 within 60.  A miss costs a
median of 50 and a p90 of 140.  Across the corpus that is **315,865 probes burned on misses against
5,674 on wins - 98.2 % of the compute buys nothing.**  Raising the budget from 60 to 400 did buy
real rows (9 wins past 140 probes), so the tail is not empty; it is just very expensive.

The fix is scheduling, not accuracy - every candidate still gets tried, only the order across passes
changes:

  * **Pass 1, budget ~25 over every pinned row.**  Captures the ~55 % of wins that land inside 20
    probes at roughly a sixteenth of the cost: 1,769 rows x 25 is about 44k probes, a couple of
    hours at ten workers rather than thirty-five.
  * **Pass 2, budget 400, only on rows pass 1 missed AND that `tools/pin_target.py` ranks highly**
    (`pins_in == 1` and size <= 256 wins at 23.4 % against a 5.79 % base).  That band is a few
    hundred rows, so the deep search runs where it converts.
  * **Pass 3 for the rest, whenever there is idle machine time.**  Nothing is skipped permanently;
    the low-yield tail is simply not what the first hours should be spent on.

The partial-removal path changes this arithmetic in its own right: a row with three or more pins
wins at 0.4 %, one with a single pin at 21.4 %, so every partial landing moves a row between those
bands and makes the next pass cheaper as well as likelier.

**Tried and did not pay inside this session's budget.** None of these is a reachability verdict —
every terminal verdict this project has issued has later been overturned, and a lane that spends a
12-verify budget without a hit has measured its budget, not the class. Read the list as "start
somewhere else", not as "unreachable":
- *Twin transplant*: only 10 pinned rows have a byte-identical pin-free twin (1,788 B). Row
  duplication is already collapsed by the registry's `instances` field.
- *Blind statement-order search* (`tools/xform/t12_stmtorder.py`, kept as the record): 0/3 on the
  `reorder-only` rows it was built for. The C order is already right; the **scheduler** moved the
  instruction, so the lever is the dependence, not the slot.
- *The obvious colouring menu* on a damage-2 `reg-rename` row (the Opus lane later closed 5 of 10
  rows in this very class, so read this as "these ten shapes are spent", nothing more): dropping the local, declaring it
  first or second, block-scoping it, self-assignment, an extra unused local, splitting the constant,
  changing the divide's signedness and two statement moves were all inert at total 2. That is ten
  shapes, not the space — the levers that have historically moved a colouring (splitting a local by
  use-group, merging short-lived values, changing what competes across a call) are barely touched.
- *The fake page-base idiom* (`extern u8 D_800X0000[]; __asm__(".set D_800X0000, 0x800X0000")` plus
  an offset) is genuine scaffolding — 103 rows, 56 of them still pinned. `.set` makes an **absolute**
  symbol, so gcc folds the arithmetic and emits `lui;ori` where retail has a relocated `lui;addiu`;
  the source shape is just the symbol (`page - 0x7f4c` **is** `D_800280B4`). Substituting it is
  mechanical, but it does not close on its own: a local set once from an address constant is a
  `reg_equiv_constant`, so `update_equiv_regs` rematerialises it at each use instead of holding it
  live the way retail does. A second, non-folding set on the local is the documented cure and it is
  cell-dependent (free at 2.7.2, real bytes at 2.8.1-G0), so any sweep must try both spellings and
  keep whichever the scorer prefers. A plugin doing exactly that was written and **withdrawn**: with
  guards tight enough to be safe (one page symbol, used once, target extern already declared in the
  file) only **1** of the 56 rows matched, and on that row the two variants moved the residue 3 -> 2,
  not to 0. The population that a broader matcher would reach is measured: 15 rows spell the offset
  inline rather than as `local -= K`, 11 carry more than one page symbol, 8 use the page symbol more
  than once. Broaden the matcher over those 34 before writing the sweep again; the lane that worked
  this class closed 2 of 10 by hand, so expect single digits, and expect per-row register-colouring
  work after the substitution.

**Lane packs.** `tools/pin_lane.py --band 8 --size 10` cuts the near band into self-contained packs
under `work/pin_lane/batchN/`: `base/` (the row with every pin already erased — the lane's start),
`residue/` (that text's aligned-regions view against retail, so the lane spends no probes finding
it), `rows.tsv`, and a `BRIEF.md` carrying what each residue class means and the shapes known to
move it. One residue class per batch, because rows of a class share a mechanism. A lane writes
exact candidates to `out/<container>/<file>.c`; landing is
`python3 tools/apply_candidates.py work/pin_lane/batchN/out --transform t13_depin` followed by
`tools/build/gate_all.py`.

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
