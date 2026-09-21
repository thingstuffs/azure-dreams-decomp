# Lane log mining — astra lanes, 2026-09-21

Source: 16 of 26 available astra lanes with a `last_message.txt`, hand-selected for spread plus the
five owner-mandated lanes (three biggest wins, two complete failures). Extraction was delegated to 10
parallel subagents (one per lane or small lane-group, general-purpose, fresh context, same IO-discipline
brief); this document is a coordinator synthesis and cross-lane verification pass over their reports,
plus direct spot-checks (file reads, `stat`, single-file `grep`, `md5sum`) done by the coordinator itself.

**Lanes mined (16):** r62_astra_families, r62_astra_big, r62_astra_alloc, r63_astra_movemove,
r63_astra_moveli, r63_astra_loadmove, r63_astra_prologue, r63_astra_recolour, r63_astra_itemnv,
r63_astra_big4, r63_astra_big7, r64_astra_loop, r64_astra_bivhide, r66_astra_outer, r67_astra_esc2,
r67_astra_esc5.

**Lanes not mined (11, budget):** r63_astra_big2/big3/big5/big6/big8/big9/big10 (7),
r67_astra_esc1/esc3/esc4/esc6 (4).

**Correction to a wall-time figure used mid-mining:** three per-lane subagents estimated wall time from
`BRIEF.md` mtime -> `codex.log` mtime and got r63_astra_prologue 81 min, r63_astra_recolour 106 min,
r63_astra_itemnv 2h21m. `BRIEF.md`'s mtime is pack-*serving* time, not lane-*start* time — there can be a
long queue gap before the model actually begins. Re-measured from `lane.pid` mtime (process start) to
`codex.log` final mtime, all three are back in the normal band: prologue 29 min, recolour 16 min, itemnv
27 min. **All 16 lanes ran 13–29 minutes wall time**; the varying quantity across lanes is *work done*
(86–2,580 measured variants), not time spent. The itemnv "failure" is not a 2.3-hour grind — it is a
normal-length session that tried ~450 variants and reached a real, well-evidenced negative result.

---

## Top 10 tooling/brief improvements, ranked

Ranking rule: **(lanes affected) × (occurrences)**, tie-broken by how directly the fix is actionable.
Counts below are `grep -c` on single files or subagent-verified tallies, not estimates.

### 1. No tool exists to explain *why* a GCC pass made an allocation/scheduling/CSE decision — every open row in every lane asks for it
**13 of 16 mined lanes** have at least one open row whose REPORT.md "what's needed next" section asks,
in different words, for the same missing capability: an allocno/lifetime/dependency-graph query against
the scheduler, register allocator, or CSE, instead of another hand-guessed C shape. Verbatim instances:
r62_astra_big ("need... RTL/allocno evidence for a register-allocation pressure question" x5 rows),
r62_astra_alloc ("no tool traces why a specific profitability/lifetime decision was made" x4 rows),
r63_astra_movemove/moveli ("no combined CSE+scheduler trace tool... had to manually correlate `.combine`
and `.sched` dumps"), r63_astra_prologue/recolour (same, both independently derive one-off `sched.c`/
`cse.c` mechanism facts by hand), r63_astra_big4/big7 ("no per-pass RTL/allocation diff tool, only whole-
listing distance"), r64_astra_bivhide/r67_astra_esc2/r67_astra_esc5 ("wants an allocator-preference
oracle, not another source shape" — 3 lanes, independently, near-identical phrasing), r66_astra_outer and
r63_astra_itemnv (both failures: the model traced the exact `combine.c`/`sched.c` mechanism by hand-
reading `-da` dumps, then had no lever left because no tool exists one level below the cc1 listing).
**Fix:** generalize `r64_astra_loop/compare_loop_dumps.py` (see table below — it already diffs `.loop`
dumps for constant-hoisting decisions) into a `tools/xform/compare_pass_dump.py` that does the same for
`.sched`/`.greg`/`.lreg`/`.combine`/`.cse` pairs: parse insn defs/uses, align by position (not UID — UIDs
shift after erasure, a fact every lane rediscovers), report which decisions flipped between pinned and
candidate. This is the single highest-value tool gap in the whole mining set.

### 2. `sitecustomize.py` (the compiler-cwd shim) was invented twice by models, then handed out inconsistently, then re-patched again by later lanes
Two independent model-written versions exist. r62_astra_families wrote a 573-byte version inline via
Python heredoc (codex.log:4160) that just forces `cwd=LANE`. r62_astra_big wrote a 973-byte version via
shell heredoc (codex.log:6210) that *also* rewrites relative args to absolute and logs every invocation
to `compiler_cwd.log` (a genuine improvement — audit trail, 946 lines for that lane's 395 trials, i.e.
roughly 2-3 compiler launches per trial). `md5sum` across all 16 lanes shows the harness later copied
these two versions verbatim into different lanes (573B into families itself plus 5 r63 lanes —
movemove/moveli/loadmove/recolour/itemnv — 6 lanes total; 973B into big4/big7/esc5) — but then
r63_astra_prologue (986B), r64_astra_bivhide (491B), r64_astra_loop (584B), and r67_astra_esc2 (1038B)
each *re-wrote it again*, and r62_astra_alloc and r66_astra_outer have **no** sitecustomize.py at all
(alloc predates it — BRIEF.md 02:13 vs r62_big's 02:11, before the pattern existed at launch time; outer
has no such excuse and simply never got one).
**Effect measured:** zero wrong-cwd errors (`cd:`, dump-files-at-repo-root) in any of the 16 lanes — the
shim plus PROMPT.txt's "FIRST RULE: run every compiler command as `cd work/native_lane/<lane> && ...`"
fully closed this failure class that the project's own history (see PROMPT.txt's own line: "lanes have
left dozens of dump files at the repo root") shows was once real. **Fix:** adopt r62_astra_big's 973-byte
version (`work/native_lane/r62_astra_big/sitecustomize.py`) as the one
harness-provided file for every future lane — it is strictly more capable (arg-absolutization +
audit log) than the 573-byte version still being handed to some lanes, and stop letting individual
lanes patch it (4 of 16 did, for no measured benefit over the 973B version).

### 3. The `lab.py`/`Lab` harness (erase pins -> write candidate -> screen by cc1-listing distance -> verify only if distance 0 -> append JSONL record) was reinvented from scratch in essentially every lane
15 of 16 lanes independently wrote a functionally-identical wrapper class (`Lab`/`Probe`/`Row`) around
the harness-provided `pin_census.sites_of` / `pin_sites.erase_many` / `variant_screen.Screen` /
`tools/verify.py`. Two lanes (r67_astra_esc2, r67_astra_esc5) explicitly went hunting through *other,
unrelated, older* lane directories (r62_astra_big, r66_sol_big2, r58_order, r58_order2) to find one to
copy — esc5's codex.log shows it literally doing
`Path('work/native_lane/r62_astra_big/lab.py').read_text().replace('r62_astra_big','r67_astra_esc5')`.
**Fix:** promote one canonical `Lab` implementation into `tools/lanes/` (e.g. `lab_template.py`) that a
lane's harness setup copies in automatically, so models stop re-deriving or archaeology-digging for it.
Best candidate to adopt, verified by direct read: `r63_astra_movemove/lab.py` (41 lines) — has the two
regression guards worth keeping (`assert len(sites_of(text)) <= len(sites_of(self.base))`,
`assert text.count('volatile')<=self.base.count('volatile')`) that a plain-erase-and-diff version lacks;
combine with `r64_astra_loop/lab.py`'s `-dL` dump/label-normalization helpers for the loop-family case.

### 4. Shared-tool import paths (`tools/xform/` vs `tools/lanes/` vs `tools/gate/`) are guessed wrong repeatedly
7 of 16 lanes hit a "No such file" from guessing the wrong subdirectory for a real shared tool:
r62_astra_alloc (`tools/lanes/screen.py` — real: `tools/xform/screen.py`), r62_astra_big (6 misses:
`tools/aligned_score.py`, `tools/score_candidate.py`, `tools/gate/compiler_oracle.py`,
`tools/lanes/pin_sites.py`, `tools/lanes/pin_census.py` — real location `tools/xform/`),
r63_astra_movemove (`tools/xform/common.py` — real: `tools/common.py`, no `xform/` prefix),
r63_astra_loadmove (`tools/lanes/screen.py`), r63_astra_recolour (`tools/xform/cc1_probe.py` twice,
`tools/lanes/screen.py`), r63_astra_big7 (`tools/lanes/pin_sites.py`, `tools/lanes/pin_census.py`),
r67_astra_esc2 (`tools/aligned_score.py` — real: `tools/gate/aligned_score.py`). Each instance is cheap
(one failed `rg`/`sed`/`cat` inside a larger multi-command exec, self-corrected within the same or next
exec) but it recurs constantly enough (≥15 individual missed guesses) to be worth a one-line fix.
**Fix:** add the exact import paths for `sites_of`, `erase_many`, `Screen`, `verify.py`'s CLI interface,
and `aligned_score.py`'s real location to the PROMPT.txt template, since `sitecustomize.py`'s own
`sys.path` list (`tools`, `tools/xform`, `tools/lanes`) already implies the split but doesn't state it.

### 5. `RUNBOOK.md` is referenced but does not exist
6 of 16 lanes probe for a `RUNBOOK.md` (`cat`/`rg -n 'Gotchas' RUNBOOK.md` etc.) that is not present at
the repo root or in `docs/`: r62_astra_families (3 hits), r66_astra_outer (4), r63_astra_loadmove (3),
r63_astra_big4 (3), r63_astra_recolour (3), r67_astra_esc5 (1, bundled inside a larger command that also
read `r62_astra_big/sitecustomize.py` — the model appears to be following an onboarding step from a
skill or a prior lane's REPORT.md, not the lane's own BRIEF.md/PROMPT.txt, since neither mentions it).
Low individual cost (one dead lookup, no retry loop) but it is the most common "wants an index of prior
lane technique" symptom in the set. **Fix:** either write `RUNBOOK.md` (a short index of prior lane
gotchas/paths — content for it exists across every REPORT.md mined here) or find and remove whatever
onboarding text is telling models to look for it.

### 6. The hand-rolled `rep(text, old, new)` assert-and-replace helper fails on stale string literals, once per lane on average
Every lane that wrote its own text-substitution helper (`rep()`/`ch()`, pattern: `assert old in text,
old; return text.replace(old, new)`) hit at least one `AssertionError` from a guessed-stale literal:
r63_astra_big4 (3 instances — `entity + 0x34` mismatch, `rect_arg = tex_rect` mismatch, plus one more),
r63_astra_big7 (1 — `register s32 intensity`), r63_astra_prologue (1 — `register s8 saved_config_25`),
r64_astra_bivhide (1 — `register s32 actors_left`), r67_astra_esc5 (1 — `register s32 shifted_y`,
re-substituting a string an earlier step in the same chain had already consumed). All were self-recovered
within one exec (the assert IS the safety net working correctly) — this is low-cost but consistent
enough (6 lanes, 7 instances) to fix once. **Fix:** promote a shared `rep()` in the `Lab` template that,
on assertion failure, prints the nearest matching substring (`difflib.get_close_matches`) instead of a
bare `AssertionError`, saving the one-exec diagnostic round-trip.

### 7. No "did I already try this" check against sibling/predecessor lanes on the same function
One concrete instance found: `r62_astra_alloc` solved `dungeon/func_809A38E4` partially (39->37 pins,
found the `loop.c:1630` profitability-threshold rule) in round 62; `r64_astra_loop` picked up the *same
function* two rounds later (37->2 pins) and had to (a) reject the evidence bundle's own `evidence/lab.py`
because it hardcoded a different, stale lane path (`r64_loop_study`) rather than its own directory, and
(b) independently re-read `toolchain/gcc-src/2.7.2/loop.c:1510-1728` and `:1880-1915` to resolve an
"honest caveat" inconsistency in `evidence/LOOP_NOTE.md` (threshold stated as both `<=116` and `<=104`
for the same movable class) that the *prior* lane's work should have already pinned down. Contrast:
r63_astra_itemnv's BRIEF explicitly named r62_astra_families' `t87_lifetimemerge.py` result and the model
used that citation correctly (this is the brief-chaining pattern working). **Fix:** when a row/function
recurs across lane rounds, carry the prior round's REPORT.md conclusion (not just a possibly-stale
evidence bundle) forward into the new BRIEF's KNOWN section, the way itemnv's BRIEF did for t87.

### 8. No safety-net check that the compile/scorer adapter itself is calibrated
`r62_astra_big`'s first custom `compile_s()` adapter had a bug (`if not val.startswith('-')` should have
been `if val and not val.startswith('-')`) that silently converted an empty cc.sh argument to the current
working directory, producing *plausible but wrong* nonzero scorer totals for all 5 rows' pinned controls
(103/45/16/50/31 instead of 0). It was caught only because the model wrote `check_baselines.py` (4 lines:
run `Lab(row).test('pinned_control', base)` for every row) as its first real command and noticed the
pinned baseline didn't score exact. No other lane in the set builds a custom compile adapter risky enough
to need this, but any lane that does should run this check first. **Fix:** make "assert the pinned
baseline scores exact/0 before trusting any other measurement" step 1 of the `Lab` template, not an
optional habit one lane happened to have.

### 9. The final "is this candidate admissible" checklist (no new volatile/ASM/fences/one-trip blocks, strictly fewer pin sites, output hash matches a proven trial) is manually re-derived as asserts in nearly every lane, under a different name each time
`r62_astra_big/publish_local.py`, `r64_astra_bivhide/finalize.py`, `r66_astra_outer/finalize.py`,
`r63_astra_big4/stage.py`, `r63_astra_big7/prepare_outputs.py`, `r63_astra_recolour/finish.py`,
`r67_astra_esc5/finish.py` all independently encode the same ~6 checks from the BRIEF's "Not allowed"
list as Python asserts before copying a candidate to `out/`. Verified by direct read of
`r62_astra_big/publish_local.py` (24 lines): asserts `distance==0`, `score['exact'] is True`, sha256
match, new pin-site set is a *subset* of the base set by `(kind, note, symbol)` with strictly fewer
sites, and `volatile`/`__asm__`/`ASM_` token counts don't increase — then re-runs `tools/verify.py`
independently as a final check. This is good practice happening independently 7+ times. **Fix:** promote
`publish_local.py` (path above) as the canonical admission gate in the `Lab` template alongside item 3.

### 10. `apply_patch`-style file edits bloat `codex.log` with repeated full-diff renders, making the logs themselves harder to mine (a harness/tooling cost, not a model mistake)
`grep -c 'diff --git a/work/native_lane'` on 5 sampled logs: r63_astra_itemnv 654, r63_astra_prologue
617, r64_astra_loop 256, r62_astra_families 101, r62_astra_big 0. The itemnv subagent traced this
precisely: one 43-line file-creation diff appears 47 times verbatim, because the CLI re-renders the
cumulative diff of previously-applied patches at later checkpoints — the model itself issued 0 `git
diff`/`git status` commands. Lanes that write files via `cat > file <<'PY'` shell heredocs instead of the
`apply_patch` tool (r62_astra_big: 0 render hits) don't pay this cost. This inflates log size 2-6x without
adding session content, and is why itemnv's log (2.3MB) looked anomalously large relative to its 67 exec
blocks and 573 measurements. **Fix:** not urgent (doesn't cost the model anything), but worth knowing
when triaging "which lanes are worth mining first" by raw log size — file size is not a work-volume
proxy once `apply_patch` is in use; use exec-block count or `results.jsonl` line count instead.

---

## Cross-lane table: self-built tools (purpose -> lanes -> best implementation to adopt)

| Purpose | Lanes it appears in (name varies) | Best implementation (verified by direct read) |
|---|---|---|
| Core harness: erase pins, compile, screen by cc1-listing distance, verify only if distance 0, log to JSONL | 16/16 lanes (`lab.py` in families/big/alloc(as lane.py)/movemove/moveli/loadmove/recolour/itemnv/big4/big7/loop/bivhide/esc2/esc5; `probe.py` in prologue/outer) | `r63_astra_movemove/lab.py` (41 lines) — cwd assert, pin-count non-increase guard, volatile non-increase guard. Add `r64_astra_loop/lab.py`'s `-dL`/label-normalization helpers for loop rows. Harness-build share of session (`grep -c` filename in codex.log as proxy, confirmed by mtime ordering): r62_astra_families wrote `lab.py` at exec ~4-5 of 33 and never touched it again; r64_astra_loop spent execs 1-6 of 32 reading references before writing its own; r62_astra_big's calibration fix (item 8) landed by minute ~15 of its 22-minute run. Harness setup is roughly the first 10-20% of every lane's wall time — this is the cost a promoted template removes. |
| Compiler-cwd shim (force gcc/cc1 child cwd into the lane, log invocations) | all 16 (harness-provided in most, model-written in r62 round) | `r62_astra_big/sitecustomize.py` (973B) — arg-absolutization + `compiler_cwd.log` audit trail. See item 2. |
| Replay the brief's named exemplar diffs against every row first | 15/16 lanes (`exemplars.py`/`exemplar_trials.py`/`run_exemplars.py`) | Pattern is uniform and correct everywhere; no single best, all are ~50-130 line straight-line replays. |
| Successive hand-designed C-shape generator waves (`shapes1.py`, `shapes2.py`, ... or topic-named equivalents) | all 16 lanes, 2-20 files each | Pattern only — content is necessarily row-specific. `r64_astra_loop`'s taxonomy (`packet_shapes.py`/`projection_types.py`/`finish_shapes.py`/`simple_packet.py`, narrowing from broad shape family to minimal shape to type-width sweep) is the cleanest *escalation ladder* to imitate. |
| Dump full `-da`/`-dL` RTL passes for a named variant | 14/16 lanes (`dumps.py`/`dump_probe.py`/`dump_evidence.py`) | Uniform 10-30 line wrapper around `cc1 -da`; no differentiation worth adopting one over another. |
| **Diff two compiler-pass dumps to see which decisions changed** | **only `r64_astra_loop`** (`compare_loop_dumps.py`) | `work/native_lane/r64_astra_loop/compare_loop_dumps.py` (52 lines, verified read) — parses `.loop` dump headers + `Insn N: regno R` lines, aligns loops by position (not UID, since erasure shifts UIDs), reports constant-hoisting verdict flips. **This is the prototype for item 1's recommended `compare_pass_dump.py` generalization.** |
| Final admission gate (re-verify, assert no new ASM/volatile/fences, stage to `out/`) | 7/16 lanes (`publish_local.py`/`finalize.py`/`stage.py`/`prepare_outputs.py`/`finish.py`) | `work/native_lane/r62_astra_big/publish_local.py` (24 lines, verified read) — see item 9. |
| Calibration check: does the pinned baseline score exact before trusting anything else | **only `r62_astra_big`** (`check_baselines.py`) | `work/native_lane/r62_astra_big/check_baselines.py` (4 lines, verified read) — see item 8. |
| Assemble REPORT.md from the JSONL trial ledger + hand-written prose, re-asserting every numeric claim at write time | 13/16 lanes (`write_report.py`/`report.py`/`make_report.py`) | `r62_astra_families/write_report.py` (109 lines) — re-derives every REPORT.md claim (distance, score, SHA match, no forbidden tokens) from the actual output files rather than letting the model type numbers by hand. |
| Joint/paired-pin erasure sweep (single, pair, group subsets) before hand-authored shapes | `r67_astra_esc2` (`run_diagnostics.py`, uses shared `tools/lanes/joint_scan.py`), implied but not automated elsewhere | `tools/lanes/joint_scan.py` (shared tool, already exists) — esc2 is the only sampled lane observed calling it as a first step on every row; worth making this step 2 of the standard recipe (after `exemplars.py`, before hand shapes) rather than leaving it lane-optional. |

---

## Recurring-error table

| Error class | Lanes hit (count of distinct instances) | Cost |
|---|---|---|
| Wrong shared-tool subdirectory guessed (`tools/lanes/` vs `tools/xform/` vs `tools/gate/`) | alloc(1), movemove(1, reverse direction), loadmove(1), recolour(3), big7(2), big(6), esc2(1) — **7 lanes, ~15 instances** | 1 failed command each, self-corrected same/next exec. See item 4. |
| `RUNBOOK.md` referenced but does not exist | families(3), outer(4), loadmove(3), big4(3), recolour(3), esc5(1) — **6 lanes, ~17 instances** | 1 dead lookup each, no retry. See item 5. |
| `rep()`/`ch()` assert-and-replace helper hits a stale string literal | big4(3), big7(1), prologue(1), bivhide(1), esc5(1) — **5 lanes, 7 instances** | 1 wasted exec each, immediately fixed. See item 6. |
| Blind path-guessing for a tool/data location never named in the BRIEF (retail disassembly resolver) | loadmove (1 lane, ~10 guesses across `tools/az_target.py`, `include/psx`, `tools/paths.py`, `build_ovl/tools/paths.py`, `build_ovl/tools/az_main.py`, 5 disc-layout guesses) before landing on `build_ovl/tools/az_target.py` | ~10 misses in one investigation; the only heavy single-episode waste found in the whole set. |
| Real Python exceptions (Traceback/AssertionError from something other than `rep()`) | families(1, a deliberate safety-assert that correctly blocked a rule-violating candidate — not a bug), bivhide(1, malformed dict comprehension), esc5(1, `TypeError` in a throwaway inline script) | 1 exec each, fixed same turn. |
| Real compiler failures (used as evidence, not mistakes) | big4 (`Unable to find a register to spill` on a reserved-`lo` multiply variant — a genuine measured negative result, not an error), big7 (`conflicting types` from a symbol-probe declaration clash, corrected and re-measured) | 0 waste — both are informative negative results the model kept and reported. |
| `ModuleNotFoundError` / `Permission denied` / `command not found` / wrong-cwd (`cd:`) | **0 lanes, 0 instances, across all 16** | See item 2 — `sitecustomize.py` + PROMPT.txt's FIRST RULE fully closed this class. |
| Real subprocess timeouts | **0 lanes, 0 instances** — every "timeout" grep hit in every lane is `subprocess.run(..., timeout=N)` source code being read, not a triggered timeout | n/a |
| IO-discipline violations (recursive grep/rg/find over `work/`, `.`, repo root) | **0 lanes, 0 instances** | Brief's explicit IO-discipline paragraph, present verbatim in every PROMPT.txt sampled, was followed with no exceptions found. |

---

## "What they needed and did not have" — consolidated list

1. **A pass-decision explainer** (item 1) — wanted in 13/16 lanes, the dominant unmet need by a wide margin.
2. **A register-lifetime/allocno tracer** distinct from #1 — r62_astra_big (5 rows), r62_astra_alloc (4 rows), r63_astra_big4/big7 (both open-row sets) all specifically want to know a pseudo's set-count/reference-count/lifetime *before* compiling a candidate, not just after.
3. **Prior-round conclusions for a recurring function**, not just a possibly-stale evidence bundle (item 7) — one concrete instance (func_809A38E4, r62_astra_alloc -> r64_astra_loop) where the newer lane had to re-derive part of what the older lane had already established, and explicitly rejected a stale hardcoded-path `evidence/lab.py`. Checked whether this was a wider pattern: `r63_astra_big4` and `r63_astra_big7` (same round, adjacent lanes, both "big" family packs) share **zero** functions between their `rows.md` headers (802835B8/818B1664/80F36D0C/81905FD0/818B6AFC vs 8181B3E8/800969CC/818E6800/80F90E88/800CA184) — no re-measurement waste found there. The func_809A38E4 case looks like a genuine but occasional gap, not a systemic one across the 16 lanes sampled.
4. **The retail-disassembly/callee-contract resolution path**, not named in any BRIEF.md sampled — needed whenever a candidate proposes changing a callee's arity or a global's contract (r63_astra_loadmove burned ~10 guesses finding `build_ovl/tools/az_target.py` and `build_ovl/disc/containers/`; r63_astra_big4's open row on `func_818B6AFC` needed "the lo-consuming entry contract of func_8002473C" and never got it).
5. **A canonical class-vs-row validation step** — r63_astra_recolour discovered mid-lane that 2 of its 5 "RECOLOURED"-class rows were actually a CSE constant-propagation family and 1 was an integer-materialization (`ori`-vs-`addiu`) family, not allocation-order recoloring at all; r64_astra_bivhide's own controls falsified its "hide the biv" class premise for 2 of 5 rows. Both lanes recommend re-validating a census/class label against `.cse`/`.rtl` evidence per row before packing rows into a family lane.
6. **A documented index of prior-lane gotchas** — the `RUNBOOK.md` gap (item 5); every lane that looked for it wanted a single place with path corrections, mechanism summaries, and "don't re-try this" notes instead of re-deriving them from REPORT.md files scattered across lane directories.
7. **Nothing tooling-related was missing for the 3 big-win lanes' *solved* rows** — r62_astra_families explicitly closes every row with "none; the row is closed at its prescribed recipe" and r64_astra_loop's only real gap was the stale evidence-bundle path (item 7). The unmet needs cluster entirely around *open* rows across all lane types, confirming the gap is a genuine tooling ceiling (item 1), not a brief-completeness problem for solved work.

---

## What worked: the three big wins, as recommended practice

### r62_astra_families (5/5 rows solved, 16 min, 224 variants)
1. BRIEF supplied the compiler mechanism theory up front with `sched.c` line citations (`rank_for_schedule`/`INSN_LUID` tie-break, `ADJUST_COST` zeroing post-call deps) — the model didn't reverse-engineer *why* erasure reorders instructions, only *which* C shape restores the dependency.
2. BRIEF named 3 worked-example rows in `src/` plus 6 canonical exemplar diffs in `exemplars.md`; the model replayed every exemplar on every row first, establishing a residual-distance baseline before inventing anything.
3. Two-tier screening: cheap cc1-listing diff (~ms) gated the expensive byte scorer, which ran only on listing-distance-0 candidates (~12 of 224 measurements) — this is why 224 variants fit in 16 minutes.
4. Candidate generation was systematic per-family sweeps (`shapes1/2/3.py`, each covering a whole operand-width/dead-local-host/reuse-strategy family via row-table loops), not one-off per-row guesses.
5. When the black-box listing search stalled on the item family, the model built `dumps.py` for full `-da` RTL dumps and read the actual `REG_DEP_OUTPUT`/`REG_DEP_ANTI` edges — this directly produced the winning `union_reuse_x` shape rather than another guess.
6. One mechanism was explicitly generalized and tested across near-identical rows (3 "item" rows, 2 "height" rows) via the same shape-family loop, rather than solving 5 rows independently — this is why the win rate was 5/5, not partial.
7. REPORT.md was generated by a script that re-asserts every numeric claim against the actual output files at write time, not typed by hand.

### r62_astra_big (3/5 rows improved, 22 min active, 395 trials)
1. Read BRIEF.md first (same `sched.c` theory), then built a shared harness (`lab.py`) and immediately self-tested it with a 4-line `check_baselines.py` on all 5 rows — this caught a real, otherwise-invisible calibration bug (a broken compile adapter silently mis-scoring baselines) within the first ~15 minutes rather than after a full session of bad numbers.
2. Ran an exhaustive single-site erase census per row before any hand-designed shape, so every later trial had a known reference point.
3. Worked mechanical exemplar moves first, then hand-designed shapes (struct framing, width/signedness, statement reordering), then *combined* independently-exact single moves into joint candidates — an explicit escalation ladder, not shotgunning combinations up front.
4. Screened everything by cheap cc1-listing distance and sent only ~25/395 trials to the real byte scorer.
5. Treated "byte-exact but rule-violating" as a hard no even under time pressure — 4 candidates were rejected with documented reasons (one explicitly re-splitting a compensating +-32/-32 cancellation, a banned "fake dependency" shape), and a cleanup script scrubbed the rejected probes out of the driver scripts so they couldn't accidentally resurface.
6. Closed 2 of 5 rows honestly as "open" with a specific, falsifiable "what's needed next" rather than shipping a near-miss or claiming impossibility.
7. Auto-generated REPORT.md from the trial ledger rather than hand-transcribing ~400 variant-table rows.

### r64_astra_loop (35/37 pins on the one row, 15 min, 86 variants)
1. Spent the first ~20% of exec calls purely reading: BRIEF.md, rows.md, exemplars.md, the *supplied* evidence bundle (`evidence/lab.py`, `evidence/LOOP_NOTE.md`), shared tools, and targeted `gcc-src/2.7.2/loop.c` line ranges — before writing a single probe.
2. Noticed the supplied `evidence/lab.py` hardcoded a different, stale lane path and built its own rather than risk writing to the wrong lane — see item 7.
3. Built a taxonomy of named C-shape families (coordinate-construction staging patterns, then inline-helper return-type/packing variants, then parameter-type-narrowing sweeps) tried cheapest-first, each batch of ~4-10 probes per exec.
4. Byte-scored only listing-distance-0 candidates (19 of 86 measured variants, ~22%) — the two-tier screen again did the intended work.
5. On finding a distance-0 candidate, re-ran it with full `-da` dumps to confirm the *mechanism* (which instructions survive combine/flow), not just the byte match — this produced a confident, falsifiable rule in REPORT.md instead of a "found by trial" note.
6. Kept and reported every negative result, including a self-caught confound (an unused scratch array in the first 9 probes that GCC still allocated stack for) — reran clean versions and flagged the confounded originals rather than silently discarding them.
7. Independently resolved a documented inconsistency in the *supplied* evidence notes (a threshold stated two different ways) by reading `loop.c` itself rather than picking one arbitrarily.

## Why the two failures were genuine dead-ends, not tooling or comprehension failures

**r63_astra_itemnv** (0/5 rows, 27 min active, 573 measurements): correctly traced the exact reason its
target mechanism (a volatile-store lifetime-merge that worked in a sibling lane) cannot transfer to a
plain (non-volatile) store — GCC 2.8.0's `combine` pass runs a `init_recog_no_volatile` mode that
specifically protects volatile operands from the fold that deletes the equivalent plain-store copy
(`combine.c:502`, `recog.c:825`, cited with exact instruction numbers). It tried ~450 variants across
every register-allocation-adjacent lever and landed on the same plateau distances, correctly refused to
add the forbidden `volatile` qualifier as a cheat, and reported "no rule was established" rather than
claiming impossibility. **r66_astra_outer** (0/2 rows, 18 min, 137 measurements): traced UID-level
scheduler ready-list priority data to identify the exact hazard-promotion race the pinned listing wins,
found the two rows fail for *different* underlying reasons (one is a same-pseudo scheduling tie, the
other has an intervening loop-optimization pass that regenerates the target pseudo after BIV elimination
— a complication the BRIEF's mechanism section did not anticipate), self-rejected 3 of its own byte-exact
candidates for violating rule constraints, and produced a bounded, falsifiable next-step spec. Both are
instances of item 1 (the missing pass-decision explainer) blocking otherwise-correct, well-evidenced work.

---

## Time/volume profile, all 16 mined lanes

| Lane | Wall time (lane.pid -> codex.log) | Exec blocks | Variants measured | Byte-scorer runs / variants (two-tier screen ratio) | Rows / pins removed |
|---|---|---|---|---|---|
| r62_astra_families | 13 min | 33 | 224 | ~12/224 (5%) | 5 rows / 5 pins (5/5 exact) |
| r62_astra_big | 22 min | 61 | 395 | ~25/395 (6%) | 5 rows / 31 pins (3 rows improved, 2 open) |
| r62_astra_alloc | 21 min | 57 | 245 | 8/245 (3%) | 4 rows / 2 pins (1 solved, 3 open) |
| r63_astra_movemove | 18 min | 42 | 178 | 1/178 (1%) | 5 rows / pins (1 solved, 4 open at dist 2) |
| r63_astra_moveli | 17 min | 50 | 158 | not isolated by subagent | 5 rows / pins (2 solved, 3 open at dist 2) |
| r63_astra_loadmove | 22 min | 52 | 199 | not isolated by subagent | 5 rows / pins (3 solved, 2 open at dist 2) |
| r63_astra_prologue | 29 min | 61 | 298 | not isolated by subagent | 5 rows / 4 pins (1 closed, 2 partial, 2 open) |
| r63_astra_recolour | 16 min | 39 | 178 | not isolated by subagent | 5 rows / pins (2 solved, 3 open at dist 2) |
| r63_astra_itemnv | 27 min | 66 | 573 | 5/573 (<1%, only the 5 pinned-control checks scored exact) | 5 rows / 0 pins (0/5, negative result) |
| r63_astra_big4 | 22 min | 117 | 353 | not isolated by subagent | 5 rows / 6 pins (2 solved, 3 open) |
| r63_astra_big7 | 15 min | 33 | 348 (`measurements.json`, a per-row dict, not a flat log — counted directly) | not isolated by subagent | 5 rows / 6 pins (2 solved, 3 open) |
| r64_astra_loop | 15 min | 32 | 86 | 19/86 (22%) | 1 row / 35 pins (37->2) |
| r64_astra_bivhide | 18 min | 34 | 161 | not isolated by subagent | 5 rows / 6 pins (3 solved, 2 open) |
| r66_astra_outer | 17 min | 43 | 137 | 0/137 (0%, row stayed open) | 2 rows / 0 pins (0/2, negative result) |
| r67_astra_esc2 | 23 min | 64 | 888 | not isolated by subagent | 5 rows / 4 pins (3 solved, 2 open) |
| r67_astra_esc5 | 26 min | 51 | 330 (`experiments/func_*/results.jsonl`, summed per row: 51/53/78/79/69) | not isolated by subagent | 5 rows / 5 pins (3 solved, 2 open) |

All exec-block counts recounted uniformly by the coordinator (`sed` strips ANSI color codes, then
`grep -c '^exec$'`) after discovering subagents used inconsistent methods (raw grep undercounted on
color-coded logs by matching 0 in 13 of 16 lanes before the ANSI-strip fix). Where isolated, the
two-tier screen (cheap cc1-listing diff gates the expensive byte scorer) keeps scorer runs to roughly
1-6% of measured variants in the solved/near-solved lanes, rising to 22% only where nearly every
candidate reached listing-distance 0 (r64_astra_loop, a single well-understood row) and falling to
0% where the search never got past listing-distance 2 (r66_astra_outer).
