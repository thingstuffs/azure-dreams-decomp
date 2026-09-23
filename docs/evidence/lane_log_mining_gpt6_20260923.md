# Round 73 GPT-6 A/B mining: why sol6/luna6 fail where astra succeeds (2026-09-23)

Source: `work/native_lane/r73_{sol6,luna6,astra}_*` REPORT.md + last_message.txt, read in full for
all 20 named lanes (every row's prose, not just the measurement tables), plus `rows.md`'s
`# Working DUCK restatements` for the two astra lanes. `lab_log.jsonl` line counts via `wc -l`,
`codex.log` sizes via `stat -c %s` (not read; see per-lane table in §1). All 20 lanes wrote the
`# Working DUCK restatements` heading correctly and returned `exact=true, total=0` on every
pinned-control baseline — brief mechanics were followed everywhere; the gap is in what happens
after.

**Sample coverage check.** Grepping `**Result:** solved` and `**Result:** partial` across every
report shows the astra sample (`r73_astra_a1` + `r73_astra_a2`, 5 rows each = 10 rows) contains
exactly 5 wins (1 solved, 4 partial) — this pair of lanes **is** the full "5/10" the task cites, not
a subset. The 10 sol6 lanes read contain exactly 4 staged wins (all partial), matching "4/40". The
8 luna6 lanes read (all fully, not just tables) contain exactly 3 confirmed staged wins (2 in `a2`:
`func_81327AE0`, `func_81845068`; 1 in `a6`: `func_81988C1C`); `a1`, `a3`, `a4`, `a5`, `a7`, `a8` are
open on every row. The task's "5/55" implies ~2 more wins in luna6 lanes outside this 8-lane sample.
**Zero full pin-clears ("solved") occur anywhere in the sol6 or luna6 sample** — every sol6/luna6
win is a partial reduction (1-3 pins off a 5-8 pin row); astra produced one full clear plus four
partials.

## 1. Per-model table

| | sol6 (gpt-6-sol) | luna6 (gpt-6-luna) | astra (gpt-6-astra) |
|---|---|---|---|
| Lanes read | 10 (a1-a8, h1, h3) | 8 (a1-a8) | 2 (a1, a2) |
| Rows sampled | ~51 | ~43 | 10 (= the full 5/10 band) |
| Wins (row has ≥1 staged byte-exact, fewer-pin file) | 4, all partial | ≥3 confirmed, all partial | 5 (1 solved, 4 partial) |
| `lab_log.jsonl` lines/lane (median) | 241.5 | 208 | 796 |
| REPORT.md size (median) | 32.9 KB | 29.3 KB | 126.7 KB |
| `codex.log` size (median, unread) | ~2.68 MB | ~0.88 MB | ~0.82 MB |
| Duck restatement heading present | 10/10 | 8/8 | 2/2 |
| Pass-level evidence used (`why`/`--pass`/`alloc_trace`) | every lane, inline pass names (`combine`, `greg`, `sched`, `lreg`); `alloc_trace.py` output cited in 1/10 lanes | every lane; `alloc_trace.py` output cited in 2/8 lanes (`a5`, `a6`), proposed as a next step in 2 more (`a2`, `a4`) but not run | every lane, but routed through **16-18 distinct saved evidence files per lane** (`evidence/957_step_sched.txt`, `why_record_greg.txt`, `record_alloc_trace.txt`...) cited by name, not by re-typing `--pass` |
| Most common "what didn't work" phrasing | **"stayed at [distance] N"** (41 occurrences across 10 lanes) | **"did not work"** (20) / "stayed at" (15) | neither phrase is templated — 2 "stayed at" total across both lanes; each row's failure prose is bespoke |

**Per-lane counts** (`lab_log.jsonl` lines = measurements taken; `codex.log` bytes not read;
REPORT.md bytes; wins = rows with a staged byte-exact, fewer-pin file, solved or partial):

| lane | lab_log lines | codex.log bytes | REPORT bytes | wins |
|---|---:|---:|---:|---:|
| sol6_a1 | 288 | 7,399,869 | 31,441 | 1 |
| sol6_a2 | 196 | 7,480,048 | 22,704 | 0 |
| sol6_a3 | 486 | 1,181,444 | 59,590 | 0 |
| sol6_a4 | 197 | 2,952,231 | 34,430 | 0 |
| sol6_a5 | 267 | 726,663 | 26,751 | 0 |
| sol6_a6 | 246 | 2,417,041 | 34,290 | 0 |
| sol6_a7 | 212 | 3,972,208 | 27,933 | 2 |
| sol6_a8 | 251 | 975,918 | 34,344 | 1 |
| sol6_h1 | 237 | 4,366,740 | 43,069 | 0 |
| sol6_h3 | 123 | 759,458 | 17,199 | 0 |
| luna6_a1 | 137 | 661,443 | 21,737 | 0 |
| luna6_a2 | 467 | 2,162,364 | 35,883 | 2 |
| luna6_a3 | 189 | 920,138 | 29,370 | 0 |
| luna6_a4 | 207 | 831,379 | 33,928 | 0 |
| luna6_a5 | 236 | 772,375 | 29,233 | 0 |
| luna6_a6 | 209 | 1,796,024 | 28,768 | 1 |
| luna6_a7 | 100 | 1,294,765 | 20,403 | 0 |
| luna6_a8 | 355 | 693,151 | 43,552 | 0 |
| astra_a1 | 831 | 855,984 | 135,197 | 3 |
| astra_a2 | 761 | 776,944 | 118,198 | 2 |

The codex.log sizes suggest astra used noticeably *less* raw model back-and-forth per byte of report
than its `lab_log` count would predict — its report is denser with distinct, addressable evidence
rather than templated narration.

## 2. Failure classes in sol6 / luna6

**Class A — measured the joint/coupled erasure `erase.py` names, but never followed it with a
root-cause source restructuring.** Both models do try multi-pin joint erasure when their own
census flags a group — this is not skipped — but when the joint result is a large residual
distance, both stop at reporting the number rather than diagnosing *why* and restructuring the
source around it (astra's wins are exactly that next step; see §3).
- `r73_luna6_a4`, `dungeon/func_8099F294`: "The actor-input/direction-index pair cannot be solved
  by independent copy edits: erasing sites 0+1 together leaves distance 109... `greg --top 24`
  shows `direction_index` as candidate-only rank 4 in `$s1`; this shifts `height_adjust`, `sprite_
  flags`, and `old_state`." The row correctly identifies this as one allocator-order group, measures
  the joint erasure, then spends the rest of its 16 variants on parameter/copy merges (116-257)
  instead of a source rewrite targeting the allocno order directly.
- `r73_luna6_a8`, `dungeon/func_800B39E4`: 14 byte-exact *same-pin-count* rewrites were composed
  with each of the 5 single-pin erasures — "60 T89 split-plus-one-pin combinations" — a genuine
  joint-search attempt, and still 0 of 74 compositions reduced pin count.
- `r73_sol6_a2`, `dungeon/func_81254460`: the two-keep joint erasure is measured and reaches
  distance 5 ("the closest *admissible* pin reduction ... with two pins erased"), but the row's own
  `why.py --pass greg` diagnosis (an extra `table_page` allocno at rank 3) is never turned into a
  candidate that removes that specific allocno instead of retrying declaration/width spellings.

**Class B — distance-worship: never scored a high-distance-but-plausible form once the low-distance
family plateaued.** Both models rank almost entirely by listing distance and stop generating once a
family's best member won't move; astra explicitly tests forms whose listing distance is *worse* but
whose expanded bytes are right (see §3).
- `r73_luna6_a6`, `town/func_800994DC` **and** `town/func_800AB37C`: both plateau at the identical
  residue "`+addiu $2,$2,0`" (a zero-immediate no-op from a relocation split) at listing distance 1;
  neither row tries the absolute-load/macro-collapse move that resolves the structurally identical
  case in astra's `func_80819B14`.
- `r73_sol6_h3`, `dungeon/func_800AA854`: 13 near candidates all cluster at distance 2 / score 1;
  the row's own "What I would need to know" names the exact falsifiable test (whether `combine`
  can be denied the "low two bits" fact) but no variant in the 20-row table attempts it.

**Class C — wrote the falsifiable next step, then the lane ended instead of running it** (budget
exhaustion, not idea exhaustion — these are not "ran out of variants" in the sense of no ideas
left).
- `r73_sol6_a2`, `dungeon/func_8180B064` ends: "measure the `sched` block-4 longest-path priority
  and ready-list order of the vertex `lh`, height `lhu` pair, and subtraction... the necessary
  dependency must be real and leave the final instruction multiset unchanged" — no such candidate
  appears among the 62 variants already logged for that row.
- `r73_sol6_a5`, `dungeon/func_80092824` ends the same way: "A falsifiable next test is a candidate
  whose `jump2` block 15 still sets `$2` with the first `plus`..." — not attempted in the 38-variant
  table for that row.

No lane in the sample shows the other three suggested classes cleanly: nobody skipped `why.py`-class
evidence entirely (pass-level tables appear in nearly every row even where the literal string
`why.py` doesn't), nobody visibly misread the scorer (every baseline verified `exact=true,total=0`
first), and no row shows a hypothesis pointed in the provably wrong direction — the hypotheses in
both models' reports are consistently *correct but unexecuted or unescalated*.

## 3. What astra did differently, concretely

**Joint removal over incremental removal** — astra's only full solve, `town/func_8032CE94`
(`r73_astra_a2`):
> "individually dropping the fourth-argument pair while retaining the first-argument pin still
> misses by 2, whereas jointly removing all three remaining argument sites is exact. **This is a
> measured interaction, not three independently exact deletions.**"

The mechanism diagnosis went further than "which pins fall together" (both cheap models compute
that with `erase.py`) to *why*: a single global hard-register variable was quietly doing two
unrelated jobs (staging a constant return value, and forwarding call arguments), and naively erasing
it created new memory stores instead of removing the register conflict — "The global register was
hiding two independent source problems."

**Explicitly distrusting listing distance** — `town/func_80819B14` (`r73_astra_a1`):
> "The byte scorer is essential here. Erasing only the fence produces listing distance 0 but byte
> total 26... Conversely, the winning absolute load has listing distance 3 because the screen
> compares one macro with the split symbol sequence, yet its expanded binary is exact."

Generator rule for that row states the lesson directly: "**RESOLVES:** ... byte-score its register
expansion and preserved delay-slot NOP; **do not accept listing identity as proof.**" The cheap
models do sometimes *observe* the same divergence — luna6_a4's `func_807B040C` scores one
distance-2 candidate (`sched_scoped_loads`) at byte total 13 alongside other distance-2 candidates
at total 1-2 — but neither report turns that observation into a deliberate search for a
higher-distance form; they log the number and move to the next variant.

**Choosing a semantically-different spelling over the closest one, on purpose** —
`town/func_8032FD1C` (`r73_astra_a2`), partial 1/4:
> "The key is expression expansion/combining and the resulting local-allocation lifetimes, not the
> final shift opcode alone... The multiply spelling creates this form; writing the otherwise similar
> temporary with `<< 1` misses by 8."

The pinned source computed the offset as `(dst_index << 1) + (s32)dst_base` — the shift is the
"obvious" spelling to keep when de-pinning. Astra tried it, it missed by 8 listing lines, and astra
then deliberately tried the value-equal but syntactically different `dst_index * 2` — which combines
differently and lands exact. The same move appears once in the cheap samples — sol6_h3's
`dungeon/func_800AA854` tests `aa_scale_mul` (a multiply spelling) against the pinned add, explicitly
because `combine` folds the add to `or` — and it does not land (§2 Class B). The difference is that
astra's report states *why* the multiply form expands differently (a disposable pseudo instead of a
hard-register set), which turns a lucky spelling into a stated, checkable rule rather than one more
entry in a spelling sweep.

**Adding the exact new dependency the fence was providing, verified against the RTL edge list** —
`dungeon/func_800995D0` (`r73_astra_a1`), partial 1/5, required two changes applied together
(pointer/scalar separation *and* a fresh single-load field transfer):
> "the third load UID 95 ... [precursor] load links ... `[(68,'true'),(41,'REG_DEP_ANTI')]`, versus
> the winner's `[(68,'true'),(51,'true'),(59,'true'),(65,'true'),(71,'true'),(74,'true'),(83,'true'),
> (89,'true'),(92,'true'),(41,'REG_DEP_ANTI')]`. The new links include the preceding halfword stores
> ... so the third load cannot be hoisted past them... The two successful source changes must be
> applied together."

And `dungeon/func_80099EE4` (`r73_astra_a1`), partial 1/5, resolved a scheduler tie by quoting the
raw ready-list flip: `"T-4: 119 (7f000001) 125 (7f000001), now 125 119"` — then wrote the fix as one
cast expression (`shifted_action = (s16)action_code`) that reproduces that exact tie-break, rather
than search over shift/mask spellings.

All five astra wins share this shape: the report names the specific RTL dependency edge or ready-list
tie the fence/keep was providing, then writes *one* source form engineered to reproduce that edge
without the pin — not a family of nearby spellings screened for the closest match.

**Duck restatements already carry the erasure-census numbers and the specific open question**, not
just the brief's prose template. From `r73_astra_a2/rows.md`:
> "STATE: A global $v0 register variable, a local $v0 first argument, a $a3 fourth argument and its
> nonvolatile keep make four sites. Lone erasures cost 10/4/2/2, all cost 10; fourth_arg and its
> keep form a coupled distance-2 pair. ISSUE: Erasing the global register naively creates a memory
> global, explaining stores that are not a width problem... NEEDED: Recover a local/direct symbolic
> return and separately reproduce argument moves..."

This duck already names the eventual fix's two halves before any candidate is compiled.

**Evidence is saved and cited by filename, not summarized inline** — 16-18 distinct
`evidence/*.txt` / `why_*.txt` files per astra lane vs. ad hoc inline pass citations in sol6/luna6.
This means astra's own later rows (and any downstream reviewer) can re-open the exact RTL dump that
grounded a claim; sol6/luna6 reports are self-contained prose that would need re-running to verify.

## 4. Ranked brief/tooling changes (most to least promising)

1. **After the joint/coupled erasure, require a named-allocno-or-edge diagnosis before any more
   spelling variants**: both models already measure the coupled group's joint-erasure distance
   (§2 Class A shows this), so the brief doesn't need to ask for that step — it needs to require
   that the *next* candidate targets the specific allocno rank, dependency edge, or scheduler tie
   the joint measurement exposed, not another width/order/declaration permutation of the same group.
   *Evidence:* astra's only full solve did exactly this — having measured the coupled group, it
   diagnosed the residual as "two independent source problems" and wrote one candidate for each
   (`func_8032CE94`, §3); luna6's `func_8099F294` measured the same kind of joint erasure (distance
   109, allocno ranks named) but spent its remaining budget on parameter merges instead of a
   candidate aimed at the named rank.
   *A/B:* re-run sol6/luna6 on rows where a joint erasure was already measured with the added rule
   "your next trial must name, and target, one allocno/edge from that measurement"; compare full- or
   partial-clear rate against the unmodified brief on the same rows.

2. **Add a "distance can lie" escalation step**: once the lowest-distance family in a row plateaus
   without an exact score, require scoring at least one candidate whose listing distance is *worse*
   but whose form matches a known macro/relocation/delay-slot divergence (absolute load, symbol
   split, `dbr` sequence).
   *Evidence:* astra's `func_80819B14` explicit reversal ("do not accept listing identity as
   proof", §3); luna6's `func_800994DC`/`func_800AB37C` both stuck on the identical
   `+addiu $2,$2,0` relocation artifact without ever trying that escalation.
   *A/B:* on rows where every scored near-candidate is distance ≤4 and none is exact, force one
   scored trial from the "absolute-load / symbol-relocation" family per row; compare exact rate.

3. **Escalate to `alloc_trace.py` before generating more source variants, whenever `why.py --pass
   greg`/`lreg` shows an unchanged flow vector.** Register-only residues (same refs/live/calls,
   different hard register) are the single largest distance-2/4 bucket in both cheap models' tables,
   and `alloc_trace.py` (the actual allocator's stated preference/reason) was cited as evidence in
   only 1/10 sol6 lanes and 2/8 luna6 lanes (proposed but not run in 2 more) vs. being load-bearing
   evidence in both astra wins that turned on register choice.
   *Evidence:* astra's `record_alloc_trace.txt` quote ("preferences $a0... attempt reasons:
   target-register-already-selected") pinpointed the fix target directly; sol6/luna6 rows with the
   same symptom (e.g. luna6's `func_80099038`, `func_800B7CEC`) stop at "the pseudo gets `$v0`
   instead of pinned `$v1`" without asking the allocator why.
   *A/B:* add a lanekit reminder ("same flow vector, different register -> run `alloc_trace.py`
   next, not another spelling") and compare variant count vs. exact rate on register-residue rows.

4. **Cap combinatorial width/order sweeps once they stop moving distance, and redirect that budget
   to a new-intermediate-variable restructuring.** sol6/luna6 rows repeatedly burn 60-300 variants on
   `ord_*`/`topo_*`/`perm_*`/width-tuple families that never leave a flat distance plateau (e.g.
   luna6's `func_813236DC` 293 variants sitting on a 2-8 plateau, sol6's `func_819715D4` 134 variants
   mostly at distance 15+); astra's wins instead introduce a fresh local to hold a value at its real
   lifetime boundary (`field_z` in `func_800995D0`, the temporary offset in `func_8032FD1C`).
   *Evidence:* quantitative — see the variant tables cited in Class A above and astra's diffs in §3.
   *A/B:* after N variants in one family produce no distance improvement, require the next trial to
   add a declared intermediate variable rather than permute existing statements; compare rows solved
   per 100 variants spent.

5. **Give sol6 lanes (not luna6) more wall-clock budget specifically to close out the falsifiable
   hypothesis they already wrote**, rather than more rows. Class C shows sol6 correctly identifies
   the exact next measurement and then the lane ends before running it, well short of any variant
   cap — sol6 finished 10 lanes in ~26 min against luna6's ~60 min for a comparable win rate (4 wins
   /10 lanes vs. 3 confirmed/8 lanes in the fully-read sample), so the extra luna6 wall-clock is not
   currently buying extra quality; sol6 is the better base for a cheap first pass, and the freed
   luna6 budget is better spent as extra sol6 time.
   *Evidence:* `func_8180B064` and `func_80092824` closing paragraphs (§2, Class C) name a specific,
   executable next trial that never appears in that row's own variant table.
   *A/B:* re-run 5 open sol6 rows with 2x the wall-clock budget and no new rows added; measure
   whether the row's own stated "what I would need to know" trial gets executed and whether it
   lands exact.

## 5. Verdict

sol6 (and, at over twice its wall-clock cost for the same win rate in this sample, luna6) is worth
running as a cheap first pass over a large retry population — it reliably executes the brief's
prerequisite work (baseline, census, exemplar replay, joint-erasure measurement, mechanism tagging)
correctly and lands the brief's known single-family mechanisms (arm sink, split-into-fresh-local,
switch-ladder rewrite, direct-field comparison) at a fraction of astra's time and lab-log footprint,
producing real if narrow partial wins (4/40 sol6, ~5/55 luna6, both zero full clears in the sample
read here). Neither cheap model is worth running *alone* on a row whose own report already shows a
named joint-erasure residual (an allocno rank, a dependency-edge count, a scheduler tie) that stops
at "unresolved" — every one of astra's 5/10 wins on this exact band closed precisely that kind of
gap, by turning the cheap-model-style diagnosis into one engineered source form instead of another
spelling sweep. The efficient design is a triage pipeline: run sol6 first across the full retry
population for the cheap calibration, census, and mechanism-tagging work (skip or shrink luna6's
share given its cost), then route only the rows whose own reports name a coupled multi-pin
allocator/scheduler residual or a plateaued nonzero-score near-miss to astra — the cheap lane's own
output already identifies exactly which rows need what astra supplies.
