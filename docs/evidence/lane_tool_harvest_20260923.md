# Lane tool harvest — 2026-09-23

Scope: `work/native_lane/r73_opus_*/`, `r74_*/`, `r75_*/`, depth <=2, `*.py`/`*.sh` under 200k,
excluding `base/`, `out/`, and kit-generated `BRIEF.md`/`TOOLS.md`/`PROMPT.txt`. Skipped (no
`last_message.txt`, still running): `r73_opus_p4`, `r73_opus_p5`, `r73_opus_s11_arms`,
`r73_opus_s24`, `r73_opus_s26`, `r73_opus_s27`, `r75_astra_p1`, `r75_astra_p3..p6`. The
"listing-diff viewer on func_819BF9F4" lead traces to `work/native_lane/r73_opus_p4/rows.md`,
which is one of the still-running lanes above — not inspected.

A raw `find` over the scope turned up 709 `.py`/`.sh` files. Two patterns dominate the census by
basename (`grep -E` over the saved file list, distinct lanes counted with `awk -F/ '{print $3}' |
sort -u`): a listing-diff wrapper (26 distinct lanes) and a `-da` dump-to-directory wrapper (23
distinct lanes). A third pattern, the per-row/per-family substitution-grid generator (~21 lanes,
9-65 files each), is the largest by file count though not by lane count. All three are grouped as
aggregate rows below rather than listed file-by-file, to keep this under the line budget. Every
named tool called out in the task brief was opened and read in full; the three dominant patterns
were verified by reading a spread of samples across differently-named lanes (`a`, `s`, `p`, `h`
prefixes) and cross-checked against the grep census rather than assumed from filename alone —
`er.py`, for instance, matched the cfg-score filename grep but turned out on reading to be an
"erase pins by index" wrapper, not a scorer, and was reclassified.

## 1. Table of every helper

| lane | file | lines | purpose | builds on | kit already has? | gap class |
|---|---|---:|---|---|---|---|
| r73_opus_s10 | `ldiff.py` | 11 | unified diff of cc1 listing, pinned vs candidate | `screen.compile_s` | partial (`Lab.screen.diff` exists internally, no CLI) | listing diff w/ context |
| r73_opus_s10 | `cellscore.py` | 10 | byte-score a candidate under a row-cfg override, no ledger write | `tools/verify.verify` | no | score under another cfg |
| r73_opus_a8 | `lst.py` | 13 | listing diff, optional ref file | `screen.compile_s` | partial | listing diff w/ context |
| r73_opus_a8 | `dump.py` | 11 | write every `-da` pass dump for a candidate to a dir | `kitlib.dumps` | yes, just no CLI | dump fetch to dir |
| r73_opus_a8 | `mk.py` | 8 | apply an ordered `[old,new]` sub list to a base file | plain str.replace | yes (`kitlib.apply_subs`/`lab.py --subs`) | none (kit covers) |
| r73_opus_a8 | `gp.sh` | 7 | batch: listing-dist + grep `why.py --pass greg` section-2 rows across variant files | `lst.py`, `why.py` | partial | priority table, batched |
| r73_opus_s1 | `sd.py` | 12 | listing diff, batched over N candidate files vs one pinned base | `screen.compile_s` | partial | listing diff w/ context |
| r73_opus_s1 | `dumpit.sh` | 9 | raw gcc/cc1 `-da` dump to a dir (hand-rolled, not via kit) | nothing (direct compiler calls) | yes (`kitlib.dumps`, unused) | dump fetch to dir |
| r73_opus_s6 | `tools/ldiff.py` | 13 | listing diff pinned vs candidate | `screen.compile_s` | partial | listing diff w/ context |
| r73_opus_s6 | `tools/dumps.py` | 13 | write `-da` dumps for a candidate to a dir | `sched_trace.compile_text(dumps=True)` | yes, just no CLI | dump fetch to dir |
| r73_opus_s6 | `tools/pri.py` | 18 | lreg refs/live/calls-crossed + greg priority table, per candidate, batched over N files | `sched_trace.compile_text` | partial (`why.py --pass greg/lreg` is pairwise, not batched) | priority table, batched |
| r73_opus_p1 | `exp/dd.py` | 22 | listing diff; candidate file OR a named sub-list from a shared `subs.json` | `screen.compile_s` | partial | listing diff w/ context |
| r73_opus_p1 | `exp/dump.sh` | 6 | raw cc1 `-da` dump to a dir, cell/flags as args (hand-rolled) | nothing | yes (`kitlib.dumps`, unused) | dump fetch to dir |
| r73_opus_p1 | `exp/stmtmove.py` | 42 | exhaustive legal single-statement-move search (def/use check), screened via `Lab.test` | `lab.Lab` | no | local-search variant explorer |
| r73_opus_a6 | `work/common_run.py` | 23 | tiny `Lab` + ordered-sub-list runner shared by ~39 sibling scripts in the lane | `lab.Lab` | yes (this *is* a hand re-derivation of `test_subs`) | variant-family generator |
| r73_opus_a6 | `work/r_b9.py` (+ 38 siblings `r_*.py`) | 9-40 each | one family per row: `itertools.product` over boolean/enum toggles -> `common_run.run` | `common_run.py` | partial (`--subs` has no cartesian grid) | variant-family generator |
| r73_opus_a6 | `work/ls.py` | 9 | listing diff | `screen.compile_s` | partial | listing diff w/ context |
| r73_opus_s9 | `exp/cellscore.py` | 7 | score under a cfg override, no ledger write | `tools/verify.verify_overlay` | no | score under another cfg |
| r73_opus_h1, r73_opus_p2 | `er.py`, `w/er.py` | 8-9 | erase a chosen list of pin indices (or `all`) to a new file | `pin_census.sites_of` + `pin_sites.erase_many` | partial (`kitlib.erase`/`erase.py` exist; no indexed-subset-to-file CLI) | erase chosen pins by index |
| r73_opus_s2 | `exp/xcell.py` | 12 | compile a candidate under another cell/cfg and diff vs the pinned listing under the row's own recipe | `screen.compile_s` | no | score/check under another cfg |
| r73_opus_a5, r73_opus_s19, r73_opus_a2 | `exp/loopcount.sh`, `exp/loopcount.py`, `exp/loopdump.py` | 8-18 | fetch the `-dL` loop-pass dump and print real-insn counts + movable verdicts per candidate | raw compiler calls / `loop_census.dump_loop` | partial (`why.py --pass loop` does this pairwise; `loop_census` exists but was probed via `inspect.signature` rather than known) | loop verdict fetch, batched |
| r73_opus_s9 | `exp/d.py` | 10 | listing diff | `screen.compile_s` | partial | listing diff w/ context |
| r73_opus_s9 | `exp/dc.py` | 13 | listing diff across two (file,cfg) pairs, with a distance count | `screen.compile_s` | partial | listing diff w/ context |
| r73_opus_s9 | `exp/disp.py` | 10 | dump + regex-grep register facts (lreg lines, greg dispositions) | `sched_trace.compile_text` | partial | dump fetch + grep by register |
| r73_opus_s9 | `exp/blk0.py` | 25 | dump one RTL pass, print first records after the note header, truncated | `sched_trace.compile_text` | partial | dump fetch + grep by insn |
| r73_opus_a3 | `gen/perm_81326794.py` | 56 | randomised topological-order search over a dependency partial order, `lab.screen.distance` as fitness | `lab.Lab.screen` | no | local-search variant explorer |
| r73_opus_a3 | `gen/swap_810592A4.py` | 38 | (same family; pairwise-swap variant of the search) | `lab.Lab.screen` | no | local-search variant explorer |
| r73_opus_a3 | `gen/anneal_810592A4.py` | 36 | plateau-accepting local search (simulated annealing) over a binary choice set, `lab.screen.distance` as fitness | `lab.Lab.screen` | no | local-search variant explorer |
| r74_astra_a1 (+8 more) | `write_report.py` | 265 | build `REPORT_TABLE.md` via kit's `lab.report()`, split into per-row blocks, wrap in lane narrative | `lab.report()` | yes (core table); narrative/split layer is not | report pipeline |
| r74_astra_a1 | `replay.py` | 41 | replay each pin site erasure + known exemplar moves on this lane's specific rows | `lab.Lab`, `kitlib.erase` | yes (assembles existing primitives) | none (recipe, not gap) |
| r74_astra_a3 (+5 more) | `finalize_candidates.py` | 12 | strip leftover pin-marker comments via regex, re-score as `final_clean` | `lab.Lab.test` | partial (regex is hand-rolled per lane) | report pipeline |
| r74_astra_a3 (+3 more) | `family_lifetimes.py` | 62 | one-off grid of typed-readback substitutions per row, screened via `Lab.test` | `lab.Lab`, `kitlib.erase` | partial | variant-family generator |
| r74_astra_a2 (+5 more) | `replay_exemplars.py` | 18 | replay literal `exemplars.md` diffs + generic per-site erasures over every row in the lane | `lab.Lab.test_subs`, `kitlib.erase` | yes (assembles existing primitives) | none (recipe, not gap) |
| r74_astra_pre1 (+1 more) | `residual_forms.py` | 29 | hand-anchored family of substitutions across 3 rows (initialization-boundary, type, host-var choices) | `lab.Lab`, `kitlib.erase` | partial | variant-family generator |
| ~21 lanes (`r74_astra_*`, `r73_opus_{a2,a6,h1,s4,s19,...}`, `r74_sol6v3_*`, `r75_astra_p2`) | `gen_*.py` / `fam_*.py` / `shapes_*.py` / `vertex2_*.py` / `family_*.py` / `r_*.py` (9-65 files/lane) | 9-60 each | per-row/per-family substitution grid, `itertools.product` or hand-enumerated, screened via `Lab.test` | `lab.Lab`, `kitlib.erase`/`apply_subs` | partial (no cartesian-grid CLI) | variant-family generator |
| 26 distinct lanes total (see §2 gap 1) | `ldiff.py`/`lst.py`/`sd.py`/`ld.py`/`d.py`/`ls.py`/`dd.py`/`dc.py`/`show.py`/`showdiff.py` | 7-25 each | same shape confirmed on a spread of 10 samples across `a`/`s`/`p`/`h` lanes: unified cc1-listing diff, pinned vs candidate | `screen.compile_s` or `variant_screen.Screen.diff` | partial | listing diff w/ context |
| 23 distinct lanes total (see §2 gap 2) | `dump.py`/`dumps.py`/`dumpit.sh`/`dump.sh` | 6-14 each | same shape confirmed on 5 samples: write every `-da` pass dump for a candidate to a dir | `kitlib.dumps` or `sched_trace.compile_text` (2 lanes reimplement raw gcc/cc1 instead) | mostly yes, no CLI | dump fetch to dir |

## 2. Gap classes ranked by lanes that independently rebuilt them

Lane counts below are from the saved file census (`grep` by basename pattern over the 709-file
list, distinct lane directories via `awk -F/ '{print $3}' | sort -u`), not eyeballed — each
pattern was confirmed by reading a spread of samples before trusting the grep match (this caught
and fixed one misclassification: `er.py`, below, is an index-based eraser, not a scorer).

1. **Listing diff with context / side-by-side** (pinned vs candidate, via `screen.compile_s`/
   `variant_screen.Screen.diff` + `difflib.unified_diff`) — **26 distinct lanes**: `r73_opus_{a1,
   a2,a4,a5,a6,a8,h1,p1,p2,p3,s1,s10,s11,s13,s15,s17,s18,s19,s2,s20,s22,s4,s5,s6,s8,s9}`. The
   single most-rebuilt tool in the harvest. `Lab.screen.diff(text, 4)` already computes this
   internally (used by `lab.py test` to log distance); there is simply no CLI that prints it.
2. **Pass dump fetch to a directory** (+ grep/parse by register or insn) — **23 distinct lanes**:
   `r73_opus_{a2,a3,a8,p1,p2,p3,s1,s11,s13,s14,s15,s16,s17,s18,s19,s22,s23,s25,s3,s5,s6,s7,s8}`.
   Almost as duplicated as #1, and the individual files are nearly byte-identical (11-14 lines)
   across lanes that call `kitlib.dumps`/`sched_trace.compile_text` — meaning ~21 of the 23 lanes
   already had the capability one import away and still wrote their own CLI wrapper for it; only
   `r73_opus_s1` (`dumpit.sh`) and `r73_opus_p1` (`exp/dump.sh`) reimplement raw `gcc`/`cc1 -da`
   from scratch, evidence those two didn't know `kitlib.dumps` existed.
3. **Variant-family generator over a substitution grid** — ~21+ lanes, both Opus (`r73_opus_a2`,
   `a6`, `h1`, `s4`, `s19`, ...) and codex (`r74_astra_*`, `r74_sol6v3_*`, `r75_astra_p2`). Largest
   by file count (up to 65 files in one lane) though slightly behind #1/#2 by lane count. Every
   instance hand-writes an `itertools.product`/nested-loop grid and a name-and-replace loop around
   `Lab`/`kitlib.erase`, because `lab.py --subs` takes a flat `{name: [[old,new],...]}` dict, not a
   cartesian product of independent axes.
4. **End-of-run report + candidate-finalize + exemplar-replay pipeline** — `write_report.py` (9
   lanes), `finalize_candidates.py` (6), `replay_exemplars.py`/`exemplar_replay.py` (6),
   `family_lifetimes.py` (4), `build_report.py` (3), `residual_forms.py` (2); all `r74_astra_*` +
   `r75_astra_p2`. `write_report.py` already imports kit's own `lab.report()` and just adds a
   narrative wrapper + `REPORT_TABLE.md` block-splitting — a thinner duplication than #1-#3, but
   ~265 lines reproduced independently 9 times.
5. **Score/check a candidate under another compiler cell or cfg without touching the ledger** — 3
   lanes: `r73_opus_s10` (`cellscore.py`, byte-score via `verify.verify`), `r73_opus_s9`
   (`exp/cellscore.py`, byte-score via `verify.verify_overlay`), `r73_opus_s2` (`exp/xcell.py`,
   listing-diff-only, no byte score). All three override `row['cfg']` and call a different existing
   entry point (`verify.verify`, `verify.verify_overlay`, `screen.compile_s`) rather than a common one.
6. **Loop-pass verdict fetch, batched over candidates** — 3 lanes: `r73_opus_a5`
   (`exp/loopcount.sh`, raw `-dL` compile), `r73_opus_s19` (`exp/loopcount.py`, raw `-dL` compile),
   `r73_opus_a2` (`exp/loopdump.py`, probes `tools/lanes/loop_census.dump_loop` via
   `inspect.signature` rather than a known call). Overlaps `why.py --pass loop`, which is pairwise
   (two texts) rather than a batched table over N candidate files.
7. **Erase a chosen subset of pins by index to a file** — 2 lanes: `r73_opus_h1` and `r73_opus_p2`
   (both named `er.py`, both `pin_census.sites_of` + `pin_sites.erase_many` over an explicit index
   list or `all`). `kitlib.erase`/`erase.py` already do the erasing; there is no indexed-subset
   CLI, so both lanes wrote one independently, in nearly identical form.
8. **Allocno/register priority table across many candidates in one batch** — 2 lanes: `r73_opus_s6`
   (`tools/pri.py`), `r73_opus_a8` (`gp.sh`, which greps `why.py --pass greg` output across files).
   Overlaps `why.py --pass greg`/`lreg`, which is pairwise rather than batched over N candidates.
9. **Combinatorial/local-search variant explorer using `lab.screen.distance` directly** (bypassing
   per-candidate logging) — 2 lanes: `r73_opus_a3` (topo-random permutation, pairwise swap, and
   simulated annealing — three scripts, one search algorithm each), `r73_opus_p1` (`stmtmove.py`,
   exhaustive legal-reordering search via a def/use check).

## 3. Top-4 promotion proposals

Ordered by the corrected lane counts from §2 (listing-diff 26, dump-fetch 23, variant-grid ~21,
report-pipeline 9) — the same four scripts originally selected, reordered.

**1. `lanekit/diff.py <row> <candidate.c> [--vs pinned|erased|FILE] [--ctx N]`** (promote listing
diff — 26 lanes, the single most-rebuilt tool found). Prints the unified cc1-listing diff that
`Lab.screen.diff` already computes internally but never surfaces on stdout. **Seed**:
`r73_opus_s6/tools/ldiff.py` (13 lines, cleanest of the sample read) or `r73_opus_p1/exp/dd.py` (22
lines, most feature-complete: also replays a named entry from a shared `subs.json`). **Changes for
lane-agnostic**: replace the hardcoded `base/<rid>.c` path and literal
`sys.path.insert("...")` with `kitlib.bootstrap()` + `Lab(row).base`/
`.erased`, so it runs unmodified from any lane dir; add `--vs erased` since `Lab.erased` is already
computed and most of the 26 lanes re-derived "erase every pin" by hand or skipped it. **Test**:
point it at an already-staged `out/` candidate and confirm it prints an empty diff, matching that
row's `exact=true` verdict in `lab_log.jsonl`.

**2. `lanekit/dump.py <row> <candidate.c> <outdir> [--cfg CFG]`** (promote dump-to-dir — 23 lanes).
**Seed**: `r73_opus_a8/dump.py` (11 lines) — already calls `kitlib.dumps` directly, so it is nearly
the promoted form already, unlike `r73_opus_s1/dumpit.sh` and `r73_opus_p1/exp/dump.sh`, which
reimplement raw `gcc -E`/`cc1 -da` because those two lanes never discovered `kitlib.dumps`.
**Changes**: swap its manual `sys.path.insert` pair for `kitlib.bootstrap()`; add a `--cfg`
passthrough so it doubles as the "another cell" dump path (closing gap #5's read side too — only
the byte-score half of gap 5 would remain separate, via `tools/verify.verify_overlay`). **Test**: run
it on a row with a known-good candidate and diff its `lreg` dump against `why.py --pass lreg` run
on the same pair — the register facts must match, since both call the same dumps machinery.

**3. `lab.py --grid grid.json`** (extend `lab.py` — ~21 lanes, the largest gap by file volume). New argparse option beside
the existing `--subs`: `--grid GRID.JSON` where the file is
`{"axis_name": {"label": [["old","new"],...], ...}, ...}`; the tool takes the cartesian product of
one choice per axis, composes each combination through the existing `kitlib.apply_subs`/`rep`
(so a miss gets the "nearest lines" error, not a bare `AssertionError`), names the variant by
joined axis labels, and screens it exactly as `--subs` already does (respecting `VARIANT_CAP`/
`--more` and `lab_log.jsonl`, which the ad hoc `r_*.py`/`gen_*.py` scripts do not — their misses
vanish silently instead of being logged as refused). **Seed**: `r73_opus_a6/work/common_run.py`
(23 lines: the `R()`+`Lab` runner already used by that lane's 39 sibling scripts) plus
`r73_opus_a6/work/r_b9.py` as the worked example of the grid shape (4 axes, `itertools.product`).
**Changes for lane-agnostic**: read the grid from JSON instead of a hardcoded `S` dict; take the
row id from `argv` instead of `"dungeon/func_80B9D094"`; replace the boolean-tuple variant name
with axis-label joining; drop straight `str.replace` for `kitlib.rep`. **Test**: feed it the
4-axis grid transcribed from `r_b9.py` and confirm it reproduces the same 16 variant texts (and
distances) that the hand-written `itertools.product` loop produced.

**4. `lanekit/finalize.py <lane>`** (promote the report/finalize pipeline — 9 lanes). Pulls the two reusable
halves out of `write_report.py`/`finalize_candidates.py`: (a) call `lab.report(lane)`, write
`REPORT_TABLE.md`, and split it into per-row blocks via the `re.split(r'(?=^### dungeon/)', ...)`
pattern already in every lane's `write_report.py` — expose that split as `lab.report_blocks(lane)`
so lanes quote blocks instead of re-deriving the regex; (b) a `strip_pin_comments(text)` helper
generalizing `finalize_candidates.py`'s two hardcoded regexes (`/* UNRESOLVED C shape (pin): ... */`
variants), then re-score via `Lab.test` before staging. **Seed**: `r74_astra_a1/write_report.py`
lines 1-10 (the block-split) + `r74_astra_a3/finalize_candidates.py` (12 lines; the regex pair is
the generalizable part, currently hardcoded to two specific row ids). **Changes**: take rows from
the lane's own `rows.md`/CLI instead of a literal `[('80AC7A30', ...), ('80CEBD74', ...)]` list;
keep the prose narrative itself lane-authored — only the table/split/strip mechanics are common.
**Test**: run it on `r74_astra_a3`'s own two finalized rows and diff against the output already
committed to `out/`, expecting a byte-identical result.

## 4. Other things worth preserving

- **The DUCK/erasure-census/exemplar-replay pre-flight order was checked, not assumed lane
  invention.** `r74_astra_a1/write_report.py`'s narrative claims every row got a baseline check,
  "fixed-heading DUCK restatement", "15-listing erasure census", and exemplar replay before deep
  work. `grep -n -i 'duck\|erasure census\|exemplar replay' r74_astra_a1/BRIEF.md PROMPT.txt`
  confirms this is prescribed, not invented: `BRIEF.md` states the round-62 rule directly ("Every
  row gets its duck restated and at least its baseline + erasure census + exemplar replay...") with
  a measured payoff (30.4% vs 12.6% landed-candidate rate, duck-briefed vs not). It is already in
  the per-lane brief; `write_report.py`'s only contribution is reporting *against* the checklist,
  not the checklist itself — no `docs/LANE_KIT.md` change needed here.
- **`r73_opus_p1/exp/stmtmove.py`'s legal-move check**: a compact def/use extractor (`lhs`/`rhs`
  split on `=`, identifier regex) used to test whether swapping two statements' order is safe
  before ever compiling — the same idea `r73_opus_a3/gen/perm_81326794.py` reinvented via an
  explicit `before:` dependency dict. A shared "is this reorder legal" primitive would serve both
  the grid generator (proposal 3) and any future permutation search.
- **`r73_opus_s6/tools/pri.py`'s call-crossing filter**: `"crosses" not in rest` on the `lreg` dump
  line is a small but exact way to isolate the pseudos that matter for a register-pressure
  argument; worth folding into `why.py --pass lreg`'s existing table as an optional filter rather
  than left as a one-lane grep.
- **`kitlib.rep`'s "nearest lines" error** is already exactly the fix needed for the raw
  `str.replace`/`text.replace(old, new, 1)` calls scattered through nearly every one-off generator
  above (`mk.py`, `r_b9.py`, `family_lifetimes.py`, ...) — those scripts predate or bypassed it;
  routing proposal 3 through `kitlib.rep` fixes this for all future grid scripts at once.
