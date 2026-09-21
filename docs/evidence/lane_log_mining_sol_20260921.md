# Lane log mining: sol packs, 2026-09-21

Model: claude-sonnet-5. Scope: 14 sol (`gpt-5.6-sol`) lanes read from `work/native_lane/<lane>/codex.log`,
`REPORT.md`, `rows.md`, `BRIEF.md`, `PROMPT.txt`, `last_message.txt` and every self-built file in the
lane directory. No `src/` writes, no commits; this file is the only thing created.

**Lanes analyzed** — 5 early exemplar-briefed class packs (no duck) + 9 duck-briefed big-row packs:

| group | lane | wall (mtime `last_message.txt` − `BRIEF.md`) | rows in pack | candidates (`out/*/*.c`) | self-built files | exec blocks | `variant_screen.py` calls | `verify.py` calls |
|---|---|---:|---:|---:|---:|---:|---:|---:|
| early | r59_sol_large3 | 51.4 min | 15 | **5** | 31 | 59 | 29 | 15 |
| early | r59_sol_large4 | 37.9 min | 15 | 1 | 17 | 36 | 14 | 4 |
| early | r59_sol_mid | 373.7 min | 15 | 2 | 22 | 119 | 56 | 5 |
| early | r59_sol_far | 431.3 min | 15 | 1 | 40 | 59 | 24 | 6 |
| early | r61_sol_gemmid_1 | 26.6 min | 15 | **0** | 36 | 44 | 22 | 6 |
| duck | r66_sol_big1 | 24.2 min | 5 | 1 | 23 | 71 | 34 | 7 |
| duck | r66_sol_big6 | 24.9 min | 5 | 1 | **209** | 57 | 2 | 3 |
| duck | r66_sol_big10 | 48.0 min | 5 | 2 | 38 | 45 | 13 | 3 |
| duck | r66_sol_big12 | 23.5 min | 5 | **0** | 67 | 113 | 7 | 3 |
| duck | r67_sol_big2 | 26.0 min | 5 | 2 | 40 | 68 | 33 | 4 |
| duck | r67_sol_big5 | 32.1 min | 5 | **4** | 3 | 45 | 1 | 2 |
| duck | r67_sol_big7 | 41.6 min | 5 | 3 | 47 | 60 | 1 | 4 |
| duck | r67_sol_big9 | 26.9 min | 5 | 2 | 16 | 63 | 34 | 2 |
| duck | r67_sol_big12 | 25.0 min | 5 | 2 | 22 | 44 | 21 | 4 |

Total shell-command execution time (sum of every `succeeded/failed in Nms`) is 0.2–2.8 minutes per
lane in every case — session wall time is dominated by `reasoning effort: xhigh` thinking between
tool calls, not compute. r59_sol_mid/r59_sol_far's 6–7 h wall times are genuine session length, not
a queueing artifact.

**Candidate definition**: a row counts as a candidate iff it has a file under `out/<container>/func_*.c`
(independently re-verified byte-exact per each lane's own REPORT.md). This underclaims slightly for
r66_sol_big1 (1 file removes 2 pins in 1 row) vs r66_sol_big10 (2 files, 1 pin each) — "candidates" is
rows landed, not pins landed.

**Methodology note that is itself a finding**: `rows.md`'s duck-restatement marker has at least three
different forms across lanes — a trailing `# Working DUCK restatements` section (r66_sol_big1/6/10,
r67_sol_big2/12), an upfront `# Working DUCK restatements (written before any compilation)` section
before any row content (r67_sol_big5), and inline `**WORKING RESTATEMENT (date).**` paragraphs stitched
into each row's own DUCK block (r67_sol_big9). All 9 duck lanes did restate every row (9/9, once all
three phrasings are matched) — restatement compliance is universal, but its unspecified format meant a
first pass of this mining run (regex on the single known marker) mis-scored 3 lanes as non-compliant.
If the brief wants restatements to be machine-harvestable later, it should fix the exact heading.

---

## Top 10 tooling/brief improvements, ranked by evidence

**1. Expose `tools/xform/sched_trace.py` / `reg_state.py` as a lane-callable RTL/allocation-phase dump — 0/9 duck lanes ever ran them.**
Both modules already exist and already parse cc1's per-pass dumps (`rtl, cse, combine, sched, lreg,
greg, sched2, ...`) into instruction/register-lifetime structures — exactly the evidence models ask
for. Across the 9 duck `REPORT.md`s, "what is needed next" says, verbatim: "the relevant pseudo's
refs/live range and rematerialisation cost in `.greg`/`.flow`" (r66_sol_big10), "cc1 `-dL` dump...
compare scheduler dependencies and LUIDs" (r66_sol_big12, func_819613A8), "RTL scheduling-dependence
dump for that block, plus the set/ref counts" (r66_sol_big1), "local-alloc quantity tables for pinned
versus erased vertex" (r66_sol_big1), "compare the relevant pseudo's refs/live range... in `.greg`/`.flow`"
(r66_sol_big10). That is the terminal blocker in at least 14 of the ~24 duck-answered row paragraphs
sampled across r66_sol_big1 (5/5), r66_sol_big10 (5/5), r66_sol_big12 (4/4). `grep -c "sched_trace"` /
`"reg_state"` over all 9 duck `codex.log`s returns 0 and 0 (the 3 `reg_state` hits in r67_sol_big7 are
`rows.md` provenance text — "other transforms that changed this row: t53_reg_state" — not an invocation).
Models instead hand-parse raw `cc1 -dL` output 1–13 times/lane. BRIEF.md mentions `-dL` in one line
("prints each loop's real insns and the movables it moved") and never names either module.

**2. Document `variant_screen.py --context N` in BRIEF.md — reinvented as a wrapper script in 5/14 lanes.**
`tools/xform/variant_screen.py` already takes `--context N` to print a diff. Five lanes independently
wrote a ~12-line script that does nothing but `Screen(row).diff(text, context=N); print(...)`:
`r59_sol_large4/showdiff.py`, `r59_sol_mid/show_variant_diff.py`, `r59_sol_far/show_diff.py`,
`r61_sol_gemmid_1/show_listing.py`, `r66_sol_big1/show_variant_diff.py`. Each is near-identical
boilerplate (`sys.path[:0] = [ROOT/"tools", ROOT/"tools/xform"]; from variant_screen import Screen`).
A one-line callout in BRIEF.md removes 5 independent reimplementations of a flag that already ships.

**3. Give `variant_screen.py` a `--subsets`/`--joint N` mode — reimplemented independently in 5 lanes.**
`r59_sol_mid/probe_subsets.py`, `r66_sol_big10/pair_scan.py` + `search_orders.py`,
`r67_sol_big2/joint_local.py`, `r67_sol_big12/subset_scan.py` all hand-roll
`itertools.combinations(range(len(sites)), k)` over `pin_sites.erase_many` + `variant_screen.Screen.distance`.
`tools/lanes/joint_scan.py` already does this exact scan repo-wide, but BRIEF.md forbids lane sessions
from running it ("never run... `pin_search.py` or `apply_candidates.py`") and it writes to
`ledger/pins_joint_<mode>.jsonl`, the wrong scope for a sandboxed lane candidate. The capability exists
twice over (once at repo scale, 5 times at lane scale) and is available to models in neither documented
form.

**4. Pull `r67_sol_big7`'s compiler-cwd `sitecustomize.py` shim into the shared tool.**
`r67_sol_big7/sitecustomize.py` (20 lines) monkeypatches `subprocess.Popen` so that any `gcc`/`cc1`
launch by a repository scoring tool gets its relative arguments resolved and its `cwd` forced back to
the lane directory — solving exactly the problem BRIEF.md's FIRST RULE warns every lane about ("gcc -da
writes its dumps into the current directory, and lanes have left dozens of dump files at the repo
root"). This is real, working defensive engineering that only 1 of 14 lanes produced; the other 13 rely
on manual `cd work/native_lane/<lane> && ...` discipline instead. Move the fix into `verify.py`/
`variant_screen.py` so the FIRST RULE sentence becomes unnecessary.

**5. Fix the exact relative tool paths in BRIEF.md/PROMPT.txt — 4/14 lanes hit a literal path error.**
`r59_sol_mid`: `sed: can't read ../../../tools/lanes/pin_sites.py` (real path is `tools/xform/pin_sites.py`).
`r59_sol_far`: `sed: can't read tools/lanes/screen.py` (real path
`tools/xform/screen.py`). `r66_sol_big12`: `sed: can't read ../../../../tools/xform/variant_screen.py`
(one `../` too many from a 5-row lane 3 levels deep). `r67_sol_big7`: `sed: can't read
../r58_order/REPORT.md` — the brief's own cross-reference to a prior lane's `out/`/REPORT (see #9) used
a relative path that doesn't resolve from inside the sandbox. All four are one-line fixes: state the
tool path once, verbatim, relative to the lane root.

**6. Give self-built harness code a canonical 3-line import header, and treat any uncaught Traceback as a hard stop-and-fix.**
`r67_sol_big9/score_variants.py` threw `ModuleNotFoundError: No module named 'common'` and exited 1 on
its first run even though the file (as later read back) does contain the three correct
`sys.path.insert(...)` lines every other self-built script hand-copies — i.e. it was run once before the
path-fix line existed. `r67_sol_big5/lab.py` threw an uncaught `AssertionError` from `sibling_shapes` at
line 290 mid-run. `r67_sol_big7/exemplar_trials.py` threw an uncaught `AssertionError: old in text` from
its own `replace_once` helper. All three are bugs in self-authored scaffolding, not in the provided
tools — 3 of 9 duck lanes (33%) lost at least one full command-turn to debugging generated code the
harness should have supplied pre-tested.

**7. Cap combinatorial self-built variant generation per row, or warn when it fires.**
`r66_sol_big6` produced 209 self-built files in a 24.9-minute lane, almost all
`probe_probe_func_819611CC_t83_1_d1_*_d2.c` / `probe_probe_func_8187B1F4_t83_1_d3_*_d2.c` — roughly 17
named shapes × up to 5 numbered copies each, concentrated on 2 of its 5 rows, generated by a self-built
`probe_variants.py` wrapping the same `Screen`/`erase_many` primitives as #3. The other 3 rows in the
same pack (`town/func_800AED64`, `dungeon/func_81977584`, `dungeon/func_819602D8`) got comparatively
little of that effort. `tools/xform/variant_screen.py`'s `--verify` batch mode is the closer fit for
sweeping many named shapes against one target; the self-built path both duplicates it and skews effort
within the pack.

**8. Treat "rows with zero real measurement" as a named lane failure mode, checked automatically.**
`r67_sol_big7`: `dungeon/func_800AA854` and `dungeon/func_8009BEB8` (2 of 5 rows, 40%) never appear in
any `variant_screen.py`/`verify.py`/self-built-scorer invocation anywhere in the 4.3 MB log —
REPORT.md's own words confirm it ("AA854 and BEB8 remain open") with no measurement trail at all, not
even a failed one, inside a 41.6-minute lane that spent time instead on `sitecustomize.py`/`lab.py`
infrastructure (#4, #6) for the other 3 rows. No other lane in the sample had an unmeasured row (see
table in §5) but the harness gives no signal that this happened — it reads identically to "measured and
still open" in the final one-line-per-row report format the prompt requests.

**9. Make the "read the prior lane's `out/`/REPORT first" instruction mechanically resolvable, and check it actually happened.**
`r59_sol_large3`'s BRIEF.md tells the model to "read them against `src/` first" — `r58_order/out/`,
`r58_order2/out/`, with 7 named example rows — but never gives the path relative to the lane's own cwd.
`r67_sol_big7` tried `sed -n ... ../r58_order/REPORT.md` and got `No such file or directory` (see #5):
the one lane in this sample that attempted the cross-lane read did so with a broken relative path and
silently moved on. There is no positive evidence in any of the 14 logs that a model actually opened a
named prior lane's `REPORT.md`/`out/*.c` before generating its own variants — the instruction exists in
BRIEF.md but nothing in the transcript confirms compliance one way or the other for the other 13 lanes,
and the identifiable attempt failed.

**10. State the duck's measured payoff in BRIEF.md/PROMPT.txt itself, not just the instruction to restate it.**
Candidate rate across all 37 r59/r60/r61 early class-pack sol lanes (no duck): 70 landed rows /
~555 pack rows (15/lane) ≈ **12.6%** (`ls out/*/*.c` per lane, summed: r59 block 45/255,
r60 block 16/165, r61 block 9/135). Candidate rate across all 23 r66/r67 duck-briefed big-row sol lanes:
35 landed rows / 115 pack rows (5/lane) ≈ **30.4%** (r66 12/60, r67 23/55, excluding `r67_sol_big6`
which has no `last_message.txt`). That is a ~2.4x higher per-row candidate rate on rows that were
selected specifically *because* they were hard enough to need the duck brief — the opposite of what
row-difficulty selection alone would predict, and reasonably strong evidence the duck brief is earning
its keep. PROMPT.txt currently only says restating "is the point of the brief" without stating this
number; putting it in the brief gives the model (and future auditors) a reason to trust the exercise
instead of a bare instruction.

---

## Cross-lane table of self-built tools

| purpose | lanes (count) | reimplementations | best implementation to adopt |
|---|---|---|---|
| diff variant vs. pinned/target listing | 5 lanes | `showdiff.py`, `show_variant_diff.py` (×2), `show_diff.py`, `show_listing.py` | none needed — `tools/xform/variant_screen.py --context N` already does this; see rec #2 |
| subset/pair/joint pin-erasure enumeration | 5 lanes | `probe_subsets.py`, `pair_scan.py`, `search_orders.py`, `joint_local.py`, `subset_scan.py` | `work/native_lane/r67_sol_big12/subset_scan.py` — cleanest, single-purpose, docstring says "writes nothing", correct `sys.path` header; closest to a mergeable CLI addition |
| named-shape variant sweep + probe explosion | 2 lanes | `r66_sol_big6/probe_variants.py` + `probe_t83.py` (209 files); `r66_sol_big10/probe_variant.py`, `search_fade_818761D8.py` | `r66_sol_big6/probe_variants.py` has the cleanest CLI (`row_id target seed variants.json`) but the *usage pattern* (209 files for 2 rows) is the anti-pattern to avoid, not adopt |
| candidate/output scoring wrapper | 3 lanes | `r67_sol_big9/score_variants.py`, `r66_sol_big12/probe.py`, `r67_sol_big12/candidate_diff.py` + `debug_variant.py` | none stand out; all just call `Screen`/`verify.py` with different argument shapes |
| compiler subprocess cwd/path shim | 1 lane | `r67_sol_big7/sitecustomize.py` + `lab.py` | `work/native_lane/r67_sol_big7/sitecustomize.py` — the only lane that actually fixed the FIRST RULE problem programmatically; see rec #4 |
| per-row trial runner (one script per row) | 1 lane | `r67_sol_big7/row_trials1.py` … `row_trials6.py`, `exemplar_trials.py`, `joint_trials.py`, `post_exact_joint.py`, `write_report.py`, `publish_local.py` (10 scripts) | anti-pattern: 6 near-duplicate `row_trialsN.py` files for a 5-row pack; a single parameterized script was available (`lab.py` in the same lane) and unused for this part |

---

## Recurring errors (real command failures, not tool source text)

`grep`-based error counts over raw `codex.log` produced a false-positive category worth flagging first:
a naive `\btimed out\b|Timeout` regex matched 3–5 times in nearly every lane, but every hit traced back
to the model `sed`/`cat`-reading `verify.py`'s own source (`timeout=900`, `except
subprocess.TimeoutExpired:`) — not a real timeout. Checked with `grep -c "TimeoutExpired"` for genuine
raised exceptions: **zero real subprocess timeouts** in any of the 14 lanes. Dropped from the table below.

| lane | error | count | example |
|---|---|---:|---|
| r59_sol_large3 | wrong file/path | 1 | `sed: can't read variant_typed_arg0_direct.c: No such file or directory` |
| r59_sol_large3 | `out/` dir missing before `cp` | 1 | `cp: cannot create regular file 'out/dungeon/func_800B3F64.c': No such file or directory` |
| r59_sol_mid | wrong tool path | 1 | `sed: can't read ../../../tools/lanes/pin_sites.py` (real: `tools/xform/`) |
| r59_sol_mid | uncaught traceback | 1 | (own script) |
| r59_sol_far | wrong tool path | 1 | `sed: can't read tools/lanes/screen.py` (real: `tools/xform/`) |
| r66_sol_big12 | wrong tool path, extra `../` | 2 | `sed: can't read ../../../../tools/xform/variant_screen.py` |
| r67_sol_big5 | uncaught traceback | 1 | `lab.py:290` in `sibling_shapes`, `run_siblings` |
| r67_sol_big7 | wrong cross-lane path | 4 | `sed: can't read ../r58_order/REPORT.md` |
| r67_sol_big7 | uncaught traceback | 1 | `exemplar_trials.py:7`, `assert old in text, old` |
| r67_sol_big9 | `ModuleNotFoundError` | 1 | `score_variants.py:11: from common import ... ModuleNotFoundError: No module named 'common'` |
| r67_sol_big9 | uncaught traceback | 1 | (same event as above) |

Totals: 4/14 lanes (29%) hit a wrong-tool-path error; 3/14 lanes (21%) hit an uncaught exception in
self-authored code; every failure above happened in either a hand-typed path guess or hand-written
harness code — none in the provided `variant_screen.py`/`verify.py`/`pin_sites.py` themselves.

---

## Duck effect: early class packs vs. duck-briefed big-row packs

| metric | early (5 lanes sampled, r59/r61) | duck (9 lanes sampled, r66/r67) |
|---|---:|---:|
| rows per pack | 15 | 5 |
| candidate rate (this 14-lane sample) | 9/75 = 12.0% | 17/45 = 37.8% |
| candidate rate (full population: all 37 early sol lanes / all 23 duck sol lanes) | 70/555 ≈ 12.6% | 35/115 ≈ 30.4% |
| self-built files/lane (median) | 31 | 23 |
| `variant_screen.py` calls/lane (median) | 24 | 21 |
| explicit "what is needed next" / RTL-level ask per row | not applicable (no DUCK section) | present in ≥14 of ~24 sampled row paragraphs across 3 lanes alone (r66_sol_big1, r66_sol_big10, r66_sol_big12) |
| joint-erasure / generator-verdict facts from `rows.md`'s DUCK block reused in the model's own restatement | n/a | yes, consistently — e.g. r67_sol_big2's restatement of `func_80BD3BA8` repeats the DUCK block's own framing ("Strong cancellation means the base is overconstrained and the useful unit is a coupled group") almost verbatim rather than re-deriving it |

**Is there evidence the duck changed behaviour?** Yes, on two independent axes. (1) Candidate rate is
2.4x higher on duck-briefed rows despite those rows having already resisted earlier generator passes —
selection bias runs the other way (duck rows are the *harder* leftovers), so the gap is a lower bound on
the duck's effect. (2) Every duck lane's restatement text incorporates the DUCK block's own STATE/ISSUE
facts (pin counts, listing-distance baselines, which generators already tried and failed) rather than
re-deriving them from scratch — e.g. r66_sol_big12's restatement of `dungeon/func_809542B8` opens with
the DUCK block's own erase-census figures verbatim. None of the 5 early (non-duck) lanes had anything to
restate, and none of them quote a prior lane's specific numeric baseline before starting to compile —
each begins from a fresh `cc1` diff of its own.

**What in the duck was ignored or wrong?** The duck's "coupled group" framing consistently gets accepted
and acted on (models do test joint/multi-pin subsets, see rec #3), but the duck's suggested *next
measurement* — almost always framed as "need an RTL/scheduler-phase dump" — was never actually taken up
with the tool built for it (rec #1: 0/9 lanes ran `sched_trace.py`/`reg_state.py`). The duck correctly
diagnoses what's missing; the model correctly repeats that diagnosis in its own words; and then no lane
in the sample closes the loop with the one tool that could supply the missing fact. That gap — not a
wrong duck fact, but an unexercised correct one — is the single most repeated pattern in this mining
pass.

---

## Rows never given a real attempt

Checked per row for at least one `variant_screen.py`/`verify.py` invocation naming that row's function
symbol anywhere in the log (self-built wrappers that call `Screen`/`erase_many` directly, like
`probe_variants.py`, count as a real attempt if they name the row — see r66_sol_big6 below, where all 5
rows got at least one hit once the self-built path is counted, even though 209 of those files served
only 2 of the 5 rows).

| lane | rows in pack | rows with zero measurement | which |
|---|---:|---:|---|
| r59_sol_large3 | 15 | 0 | — |
| r59_sol_large4 | 15 | 0 | — |
| r59_sol_mid | 15 | 0 | — |
| r59_sol_far | 15 | 0 | — |
| r61_sol_gemmid_1 | 15 | 0 | — |
| r66_sol_big1 | 5 | 0 | — |
| r66_sol_big6 | 5 | 0 (but 3/5 got only self-built-tool hits, 2/5 never touched via the provided `variant_screen.py`/`verify.py` at all) | `town/func_800AED64`, `dungeon/func_81977584`, `dungeon/func_819602D8` — provided-tool coverage only |
| r66_sol_big10 | 5 | 0 | — |
| r66_sol_big12 | 5 | 0 | — |
| r67_sol_big2 | 5 | 0 | — |
| r67_sol_big5 | 5 | 0 | — |
| **r67_sol_big7** | 5 | **2 (40%)** | `dungeon/func_800AA854`, `dungeon/func_8009BEB8` — confirmed by REPORT.md's own "AA854 and BEB8 remain open" with no measurement trail |
| r67_sol_big9 | 5 | 0 | — |
| r67_sol_big12 | 5 | 0 | — |

Across the 14-lane sample: **13/14 lanes measured every row at least once**; the one exception
(r67_sol_big7) spent a disproportionate share of its 47 self-built files and 41.6-minute session on
infrastructure (`sitecustomize.py`, `lab.py`, 6 `row_trialsN.py` scripts) for 3 of its 5 rows, leaving
2 rows with no attempt at all rather than a failed one.

---

## Files referenced

- `tools/xform/sched_trace.py`, `tools/xform/reg_state.py` — rec #1
- `tools/xform/variant_screen.py` — recs #2, #3
- `tools/lanes/joint_scan.py` — rec #3
- `work/native_lane/r67_sol_big7/sitecustomize.py` — rec #4
- `work/native_lane/r67_sol_big12/subset_scan.py` — cross-lane tools table
- `work/native_lane/r66_sol_big6/probe_variants.py` — cross-lane tools table, rec #7
