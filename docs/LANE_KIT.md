# Lane kit: what a blocker lane gets, and what to harvest from it

Owner rule (2026-09-13): astra when the other avenues struggle, or when it is likely to unlock a larger
piece of work. Use it sparingly, but get the most from each run: set it up for its best chance of
success, and harvest its techniques, advice, temporary tooling and anything it had to fetch. Row packs
and fence packs stay on luna. Lanes so far: `work/native_lane/sched_astra` (round 16, the first
scheduler, which produced `t51_sched_order`), `work/native_lane/reg_astra` (round 18, register pins:
`t53_reg_state`), `work/native_lane/page_astra` (round 18, page-base pins: `t54_pagebase`) and
`work/native_lane/keep_astra` (round 19, keeps outside page bases: the CSE hide).

Lane tooling (`tools/lanes/`, since round 24; it used to live in a session scratchpad):
`build_fence_lanes.py` and `build_keep_lanes.py` build luna row packs from a pool of row ids (each row's
nearest pin, its deciding pass or class, the lone erasure's residue), with the briefs `fence_lane_brief.md`
and `keep_lane_brief.md`; `launch_lane.sh <lane> luna|sol|astra` starts a lane (its PID in the lane
directory); `land_lanes.sh <tag> <lane>...` is the landing transaction (the lane filter, the cascade, tidy,
T2, one gate); `freeze_heldouts.py` freezes a blocker lane's held-out sets (item 6 below). A pool is a
file of row ids with no builder of its own: round 19's fence pools were the never-laned fence rows (a live
fence and no copy under `work/native_lane/fences*/base/`) ordered by pin count, and that pool is spent.
`tools/site_shapes.py` ranks every live pin site by the shape of its neighbourhood: where a recurring shape
(the source of every generator built from a lane win) still is.
Round 25 added `build_exemplars.py --family REG|KEEP|FENCE --since <commit> --out <dir>` (every landed diff
that lowered a family's count with a body change, with the generators journaled per row: the exemplar set a
brief cites), `build_alloc_lanes.py` with `alloc_lane_brief.md` (diagnosed register packs: each row carries the
stock allocator's actual reason for the pinned register, from `tools/alloc_trace.py`; the conflict and
preference strata paid 33-42% on rows with 1-3 pins in round 25's luna packs; re-read from every lane directory in round 28,
sol pays 37% on alloc1 and 56% on alloc2 rows with 4-8 pins, 37% on alloc1 rows with 9-20, and 9% on alloc1 rows with 2-3 -
the 4-8 band pays best; `--max-pins`, `--exclude`, `--as`), and the
observer `tools/alloc_trace.py` itself. A tool a lane builds is reviewed by an opus workflow against the
failure list in "After it finishes" item 2 before it is copied (t61 had the lane-path import; t60 dropped a
declaration's line remainder).
Round 26 added `served.py` (`served_rows()`, `assert_unserved()`: every builder refuses a pack holding a row any
lane has served unless `--repack`; all builders take `--dry-run`), `promote_honest.py` (an honest-C pack landed at
its true base in one command: promote, register, as_flags; `--decision-b` verifies every region mate first),
`tools/alloc_probe.py` (the allocator counterfactual probe: which ONE allocator input, changed under gdb, makes
the unpinned compile reproduce retail; a triage of register sites at 1.3 s each, `probe_rows.sh ROWS DIR` over a
list) and `build_probe_lanes.py` + `probe_lane_brief.md` (retry packs briefed with the measured knob).

Round 27 added `ledger.py` (the lane ledger: every lane's served/exact/landed/pins/rate read off the disk into
`ledger/lanes.jsonl`; `--by tier|family|stratum`, `--closed 0.2` prints the (family, stratum) groups no pack may be
built on again), `pools.py` (the pool table: every pinned row by family, register stratum, pin band, served or not,
near band over every `pin_search` tag, probe knob class, and the rate measured on that stratum; `--rows FAMILY
STRATUM --band 1-3 --unserved` feeds a builder; its TOTAL is asserted against the tree), and `tools/fixtures/memdep/`
(the five-cell microcompile fixture for gcc 2.x's `MEM_IN_STRUCT_P` dependence exemption, the pattern item 4 below
asks for). Rule since round 27: **a pack is launched from the pool table only, and never on a closed group.**

Round 28 added `reach.py` (the depth-2, rename-invariant replay of the whole menu over the lane-won exemplar diffs: 13 of
120 register texts reached where round 27's token-exact depth-1 replay reached 1 - run it with a new generator's candidates
added BEFORE any sweep, and read its ranking audit: a two-move fix's first step sits in a valley under both the screen and
the pass-stream distance), `declmoves.py` (the declaration-level inventory of what the lane diffs did: split, inline, merge,
retype, control flow), and the rule the round's biggest win taught: **when a pack wins several rows by one move, write
that move up as a generator the same day** (`probe4` 5 of 7 by a same-register merge -> `t66_sameregmerge`, 238 pins in a
two-minute sweep over a population no pack would have finished). A generator built that way still needs the adversarial
reviewer: t66's edited `#ifdef __mips__` arms, which `pin_census.arm_labels` cannot see (it labels only NON_MATCHING
conditions), so every landing must compare the non-mips arms before and after (round 28 did, 0 of 142 rows differed).

Round 29 added `ctrlmoves.py` (the control-flow inventory of the lane diffs: tail merge/dup, loop form, return split, arm
swap) and four rules: **sweep a new generator over the WHOLE tree before the near band** (t64: 10.7% off the near band, 4.7%
on it - the band the search worked hardest pays least); **`sweep.py --processes` for any generator that parses compiler
dumps** (threads crawled at 5 rows a minute under the GIL, processes ran 35); **check an inventory class against the pass
dumps and the reachability delta before briefing it as a mechanism** (t67: `jump.c` cross_jump canonicalises 92% of tail
sinks away - the inventory had counted co-occurrence); **never start a sweep of a module a fix agent still owns** (a
half-edited t66 applied 47 rows before it was stopped; they verified byte-exact and were audited afterwards, but the order
was wrong). And the cheapest lever seen so far: **open a paying generator's largest refusal classes before building a new
generator** - t66's two spelling refusals paid 75 rows through two sweeps for one workflow item.

Round 30 added `erase_census.py` (every live site erased alone and screened against the pinned listing, 23 s for the whole
tree; `--diff 4` keeps the residue lines so the near sites group by what one erasure changes: moved / recoloured / an
operation changed, then by opcode pattern) and the rule it enforces: **census the residues before briefing a class** - the
handover's maspsx-screen item died in 23 seconds (21 of 6,480 sites are cc1-invisible), and the census named the
address-materialisation pattern (231 sites) that no inventory of the lane diffs had. A refusal table is read the same way:
`pairs_of` + `candidates_for` over every family row with a skips Counter (three lines) gave t66's table for the whole tree,
and the largest class turned out to be a scan stopper hiding declarations, not a parser gap - read the CODE behind the
largest count before writing the brief. And the round's largest lesson: **a program-level refusal can be a
measurement of the wrong program** - t66's `interference` class (224 pairs, a real live-out edge at the C level) paid 37 of 43
rows once the clashing pairs were simply offered under vf, because both variables share one hard register in a byte-exact row
and the compiled program never holds both values; when a refusal argues from C semantics on m2c text, try it under the byte
verdict on its whole population before composing a work-around. Landing pattern that held for rounds 29 and 30: lane outputs
first (all fresh), then the forced tree sweep of the opened module (two passes), then `land_lanes.sh` for the cascade and the
one gate; the arm check on every changed row before the commit.

Round 31 added `sched_map.py` (every scheduling residue mapped to its C statement through `-g` line notes and classified
with t51's own tests - a class table in seconds, the prologue class from it) and one lesson the owner named first: **a
move that only works jointly is invisible to every one-site-at-a-time generator ranked by screen distance**. Dropping one
of four parameter copies screens at 132 where dropping all four screens at 0, so `dropcopy` (one copy per candidate),
t64's per-definition moves, t51's single statement moves and t53's per-site rewrites all sit in that valley, while the
generators that try the family jointly (t36's joint widening, t57's all-sites form, t62's family erasure, t63's grouped
flips, now t69) are the ones that paid. Before building a family mode into a generator, measure it: one candidate per
move kind that applies the move to every eligible site of the function at once, screened beside the singles on the near
band, counting sites where the joint form reaches 0 and no single does.

Round 32 measured that rule with `tools/lanes/family_measure.py` (a fresh `erase_census.py` census -> the near band -> per
move kind one folded joint candidate beside the singles): dropcopy 1 row of 281, `inline_def` 0 of 1,436 bases, `retype_ptr`
0 of 382 - the family mode pays only where the sites share one mechanism (t69's parameter copies), so measure the population
ceiling text-only first (`scratch/population.py` in `work/native_lane/r32_family/`) and the joint's "worse than the best
single" column beside its "reaches 0" column. A refusal table is read the same way: a `Detail` counter (`t69_prologue.Detail`)
ties each refusal to the local it was about, so the pins BEHIND a refusal can be counted and the largest opening screened in
seconds (`scratch/dropreg_screen.py`) before any verify - and the order of a generator's refusals matters, because a test
that fires before the class test (t69's `declared-twice`) counts records that were never the generator's.

Round 33 added the forward perturbation catalogue (`tools/lanes/residue.py`, `perturb_basic.py`, `perturb_struct.py`,
`perturb_catalog.py`, `erase_census.py --fp`): every pin-free byte-exact row perturbed one m2c-style move at a time (each a
generator's move reversed), the residue fingerprinted by the same function as the census, so a pinned site gets its ranked
CAUSES and a row its bucket (`match`; bucket a split by the sweep journals into noop / refused / unseen). Four rules from it:
**run the text oracle before sizing a widening** (`work/native_lane/r33_catalog/scratch/oracle.py`: on the rows a generator
landed, does a kind on the landed text reproduce the pre-landing text minus its pins, rename-invariantly? 3 min, no compiles;
it named the missing shapes the compile gate could not); **report a kind's zero-instance rate on its own generator's rows
beside any coverage number** (48 of 152 rows had a reversing kind that produced nothing); **never quote coverage without the
band, and never beyond the band where the key covers the catalogue's own other half** (L1 means something at d <= 4 only);
**split "a cause with a generator" by the journals before opening a refusal table, and read the journal's words against
`tools/sweep.py`** - `noop` is "no candidate", `refused` is a textual refusal OR "candidates produced, none verified" (the
reason string says which): t69's 94 bucket-a rows are 72 missed candidates (a composition target, not a table), t29's
47 are 31 missed + 16 textual, and 105 of the address rows had never been offered to t29 at their current text (a sweep).

## Before launch: give it everything it would otherwise fetch or rebuild

1. **GCC sources for every cell.** `bash tools/fetch_gcc_src.sh` writes `toolchain/gcc-src/<version>/`
   (gitignored with `toolchain/`). It holds 2.6.3, 2.7.2, 2.8.0, 2.8.1, 2.91.66 (egcs-1.1.2) and
   2.95.2, keeping only the compiler's own sources (top-level `*.c *.h *.def *.md` and
   `config/mips/`). 2.7.2-cdk has no public source: read 2.7.2 and confirm behaviour by
   observation. Two lanes fetched single files from GitHub mid-run before this existed. Search one
   version directory at a time, with `--max-filesize 4M`.

   | `-da` dump | pass | sources |
   |---|---|---|
   | `.rtl` | expansion | expr.c, stmt.c, calls.c, expmed.c, explow.c, optabs.c, emit-rtl.c, function.c, c-typeck.c, c-decl.c, fold-const.c |
   | `.jump`, `.jump2` | jump optimisation | jump.c |
   | `.cse`, `.cse2` | common subexpressions | cse.c |
   | `.loop` | loop optimisation | loop.c, unroll.c |
   | `.flow` | life analysis | flow.c |
   | `.combine` | instruction combination | combine.c |
   | `.sched`, `.sched2` | scheduling | sched.c (haifa-sched.c where present, 2.91.66 and 2.95.2) |
   | `.lreg` | local allocation | local-alloc.c, regclass.c |
   | `.greg` | global allocation, reload | global.c, reload.c, reload1.c, caller-save.c |
   | `.dbr` | delay slots | reorg.c |
   | assembly | output | final.c, config/mips/mips.c, mips.md, mips.h |

2. **Dumps and comparisons.** `tools/xform/sched_trace.py`: `compile_text(row, text, dumps=True)`,
   `instructions()`, `decisions()` (the scheduler's ready lists), `diagnose()` and `distance()`.
3. **A census of the blocker, from data.** `tools/phase_census.py run --out <file>` erases one pin at a
   time on a random sample and records the first pass that differs, in three ways (operations, order,
   wiring), with a class at combine. Lane anecdotes mislead. Round 18's census found that only a third
   of register pins change operations, where a lane's wiring-inclusive measure implied about 80%.
   **Read the wiring (`abs`) table for the deciding pass, never the operations (`ms`) table.** `ms`
   drops registers, so allocation effects fall through to the last pass, and dbr `sequence` patterns
   carry insn UIDs that shift whenever an insn is erased: in round 19's census the `ms` table put 121
   of 250 keeps at dbr, the wiring table 5. Cross-tabulate the class at combine against the first
   wiring difference at or after combine, per family and per macro. A sweep journal that records
   per-site erasures (t53's `sites[]`) is a larger census for free: t53k's covered 2,958 keeps.
   **A near miss by assembly distance is not a near miss in C.** Round 23's keep lanes took 48 rows whose
   single keep erasure was within 3 instructions of retail and made 2 exact (4%): the few instructions were
   equivalences CSE is entitled to use (a shared constant, a coalesced copy, a folded offset). Pick a lane's
   pool by CLASS as well as distance: for fences the deciding pass (sched1, dbr, jump2); for any family,
   not `wiring` first differing at cse. Register pins are the exception to the wiring rule: the declared hard
   register changes the first-appearance numbering the renamed stream uses, so `abs` differs from `rtl` on
   (and at cse) in almost every row, even where combine is identical. Read register pins in the
   register-anonymised tables (`ms`, `seq`): operations and order identical through the first scheduler
   mean the pin only chooses registers (206 of 300 in round 24's census).
4. **Exemplars.** The source diffs of the wins already landed for the mechanism. Write them into the
   lane's `evidence/` yourself: a lane may not run git.
5. **The contracts.** The generator contract (`class T`, `eligible`, `apply_verified(text, row,
   census, vf)`), `tools/verify.py`, `tools/sweep.py`, and the existing generators that target the
   blocker, so it can find out why they miss before designing.
6. **Held-out sets, frozen before it starts.** Stratify one set by the census classes and draw one
   from the population, and write a manifest with each selection rule.
7. **The evaluator.** `tools/lane_eval.py --lane <dir> --module <tNN.py> --rows <ids> --tag <name>`
   measures any generator on a row list the same way every time. It verifies the baseline, uses a
   cached vf, and re-verifies each hit outside the cache. Its `out/` files with `.base_sha` land
   through `tools/apply_candidates.py`. It came from sched_astra's `run_t51.py`.
8. **The brief.** Templates: `work/native_lane/sched_astra/BRIEF.md` and
   `work/native_lane/reg_astra/BRIEF.md`. A brief needs:
   - the cd rule as line 1 of `PROMPT.txt`;
   - write only inside the lane directory, with bulk dumps under `scratch/` behind a `.ignore`;
   - never `src/`, git, gates, sweeps, `pin_search.py` or `apply_candidates.py`;
   - the IO discipline, and at most 8 compiles at a time;
   - **the scaffolding list, verbatim: no new `ASM_*`, `__asm__`, `volatile`, fake dependencies, and no
     `do { } while (0)`, `while (0) { }`, `for (;0;)` or any other one-trip block.** census.py counts a
     one-trip block like a pin, so a keep traded for one removes nothing. keep_astra (round 19) was not
     told this and built its whole tool on one-trip blocks around the kept value's producer (their loop
     notes stop the first CSE and the scheduler): 40 exact outputs, every one a keep traded for a block;
   - freedom of approach;
   - the question, with the census numbers;
   - hypotheses to TEST, not assume;
   - a clause that an unreachable class is a finding;
   - the deliverables: a REPORT written before building and refreshed hourly, the tool in the
     contract, measured held-out rates, and a closing summary.
   Put the harness helpers in the lane's `tools/` before launch, with the lane path changed:
   `sitecustomize.py` (on `PYTHONPATH` it runs every Python-launched gcc/cc1 inside the lane, verify's
   included, and refuses writes outside it; reg_astra wrote it, page_astra hardened it) and
   `evaluate.sh` (lane_eval on H1 then H2). The cd rule still has to cover its shell commands.
9. **While it scores:** no gate and no publish, because `verify.py` scores inside `build_ovl` and
   `mk_ovl_root.sh` replaces the tools copy there. Sweeps may run, but must skip its held-out rows. Wait
   on its PID with `kill -0`, never on `pgrep -f` of your own pattern.

## After it finishes: harvest everything

1. **The analysis** goes into `docs/PIN_MECHANISMS` and the next brief: the mechanism, the taxonomy
   with counts, the failed hypotheses, and the bounded unreachable classes. CPU cannot redo this part.
2. **The tool.** Review it before copying it into `tools/xform/`. t51 needed four fixes: a
   declaration's trailing comment, a doubled cast, a lane-path dependency, and `u8 * x` spacing.
   Unit-test it on the lane's own outputs. If it changes a shared tool, check that it behaves the same
   as before (as t51's `groups` refactor was checked).
3. **Its outputs.** `python3 tools/apply_candidates.py <lane>/out --transform <name>` (guarded by base
   sha), then the cascade and one gate.
4. **Its temporary tooling.** A technique both astra lanes used, worth asking for by name: a
   five-cell microcompile fixture. Compile one minimal C shape in every stock cell and compare the
   pass dumps, which bounds an "unreachable" claim to a tested family (see sched_astra's
   `tools/audit_t51.py --mode invariance` and page_astra's `tools/value_probes.py`). Evaluators, fixtures, audit scripts and fetched sources: generalise
   whatever is reusable into `tools/`, and add anything it had to fetch to this kit. Generalised from
   alloc_astra: `python3 tools/alloc_trace.py <row_id> [--source cand.c] [--site N]` runs the cell's own
   unstripped cc1 under gdb and prints, per ASM_REG site, the allocator's real reason for the pinned
   register (local quantity refs/live/suggestions and attempt order, or global allocno
   preferences/conflicts and the deciding `find_reg` attempt) — analysis only, ~0.4-2 s per site.
5. **Its advice**, including what it would do next or better, goes into the next brief and
   `docs/HANDOVER.md`.

## Duck briefs (round 62)

The owner's rule of 2026-09-21: **every pack row carries a rubber-duck brief** - the state stated
plainly, with no prose and no salesmanship. `tools/lanes/duck_brief.py` writes one:

    python3 tools/lanes/duck_brief.py dungeon/func_80A9D4E8 [more rows ...] [--notes NOTES.md]
    from duck_brief import duck; md = duck(row_id)          # markdown for one row

Three sections per row, all measured fresh against the row's current text (its sha is in the header;
the cached census `erase_r61.jsonl` carries no input sha, so it is never trusted for a duck):

- **STATE** - every live pin site (`pin_census.sites_of`) with its trailing `/* ... */` note, the
  residue class of erasing it ALONE (`lanes/residue.fingerprint`, the same fingerprint
  `erase_census.py --fp` records) and the changed listing lines; then the JOINT picture: all pins
  erased together and, on rows with 2-6 pins, each PAIR - so the duck can say which pins **fall
  together** (a pair whose joint residue is no larger than either pin alone) and which are
  independent. Bounded at about fifteen cc1 listings a row: every pair up to five pins, the
  same-macro / same-variable pairs at six, none above that (use `joint_scan.py` there). Rows with
  more than ten pins switch to a grouped census - alike pins on one line, smallest residue first.
- **KNOWN** - one sentence of mechanism hypothesis per pin from its kind and class (callee-saved
  register = global.c allocation order; `ASM_MEM_BARRIER` = the cse store rule; `ASM_SCHED_BARRIER` =
  the sched.c tie rule; and so on), the generators that cover that mechanism with their newest
  verdict on this row (`ledger/sweeps/*.jsonl`, marked *(on earlier text)* when the sha differs, and
  the `work/native_lane/r6*_*/journal.jsonl` record when the generator was swept with `gen_drive`),
  the `alloc_sim` order-site verdict for callee-saved ASM_REG pins (t85's APPEARS test, imported),
  and the lanes that already served the row with the **distances** their REPORT.md quotes - not the
  prose. A kind and class that match no documented mechanism are written "unknown".
- **NEEDED** - what must change in the C in plain words, whether the pins must fall together, and
  what is still UNKNOWN.

`tools/lanes/build_class_pack.py` gained two flags; without them its output is byte-identical to
every earlier run (checked by building the same class pack with both versions):

- `--duck` appends each row's duck under its `rows.md` section.
- `--rows id,id,...` builds a pack of exactly these rows whatever their class, pin count or served
  state - a family or whole-function pack. `rows.md` then carries a served-history line per row, the
  joint listing diff is capped at 200 lines, and BRIEF.md/PROMPT.txt gain the paragraph from
  `tools/lanes/duck_pack_brief.md`: restate each row's duck in your own words before compiling
  anything, and end REPORT.md with the duck answered (what was tried, the distances, what you would
  need to know). `--notes FILE.md` copies hand probe notes into the lane's `evidence/` and quotes
  each row's section of them verbatim inside its duck.

Textual unit tests: `tools/tests/test_duck_brief.py` (note regex, both REPORT.md shapes, the
distance-sentence filter, the fall-together rule, the mechanism table's "unknown" default).

## Orchestration kit (round 68)

The pipeline below ran for three days out of a session scratchpad: `pool.sh`, `codex59f.sh ...
codex59m.sh`, `land_r63.sh ... land_r68.sh`, `land_t91.sh`, `clone_watch.sh`, `autocommit.sh`,
`add_exemplars.py`, `add_cascade.sh` - rewritten every few hours, lost with the session, and each
copy carrying a different, silently stale generator list. It is now in `tools/lanes/`. Start from
these instead of writing new ones; when one is not good enough, change it here.

**The round as it runs.** A census class or a big-row list -> a duck-briefed pack -> an astra/sol
pool -> ONE landing transaction when the pool drains -> an Opus harvest of the lanes' REPORT.md
moves into generators -> a `gen_drive` sweep of each new generator -> gap landing -> clone transfer
onto the siblings -> refreshed exemplars for the next pack.

| Tool | One line |
|---|---|
| `tools/lanes/pool.py` | `python3 tools/lanes/pool.py big --model sol -c 3 --rows-json rows.json --paragraphs big_rows,new_findings [--dry-run]` - build the packs, probe capacity, run N lanes at a time, journal each lane's candidate count, land the winners together |
| `tools/lanes/land_gap.sh` | `bash tools/lanes/land_gap.sh <tag> <lane>...` - wait for a codex gap, one `land_lanes.sh` transaction with the cascade extras, then the `arm_restore` twins |
| `tools/lanes/cascade_extra.txt` | the ONE list of generators passed as `EXTRA_T`; add a generator here the day it lands its first row |
| `tools/lanes/refresh_exemplars.py` | `python3 tools/lanes/refresh_exemplars.py` - rebuild `ledger/pack_inputs/solved_exemplars.json` from every r5*/r6* lane (2026-09-21: 144 -> 434 rows), with each row's `lane` and the `move` that solved it |
| `tools/lanes/brief_paragraphs/` | named paragraphs appended to a pack brief: `build_class_pack.py ... --paragraphs big_rows,new_findings` (`class_question.md` is a template to fill by hand) |
| `tools/lanes/clone_watch.sh` | `nohup bash tools/lanes/clone_watch.sh &` - every 25 min, replay finished lanes' moves on their clone siblings and gap-land what comes out exact |
| `tools/lanes/autocommit.sh` | `nohup bash tools/lanes/autocommit.sh &` - commit `src`/`STATUS.md`/`ledger` whenever the landing lock is free and no gate runs |
| `tools/lanes/gen_drive.py` | `--fresh` re-sweeps a CHANGED generator over rows its journal already answered; `--journal-refusals` writes the refusal table its next version is written from |

**Landing contention is the rule that shapes all of it.** `land_lanes.sh` refuses to run while any
`codex exec` lane or any `sweep.py` is running (`verify.py` scores inside `build_ovl`, which
`mk_ovl_root.sh` replaces under it), and it holds `build_ovl/work/land.lock` from apply through gate.
So a lane that finishes while its siblings are still thinking cannot land, and a pool's whole point
is to do ONE landing when they have all exited. `land_gap.sh` is the only thing that should wait for
that gap: it queues on `build_ovl/work/land_gap.lock`, so two landers take the floor in turn instead
of refusing each other (round 61's chain H lanes were refused under contention and re-landed by
hand), and it RETRIES a refusal until its deadline instead of leaving the lanes staged.  That
contention rule is the default; `LAND_ISOLATED=1` (added to `land_lanes.sh` alongside this kit) lifts
it by gating in `build_ovl_gate`, and `land_gap.sh` passes it through and then stops waiting.

**The pkill/pgrep self-match trap** (three orchestrator shells killed on 2026-09-19/21, and one lane
chain that sat fifteen hours). `pgrep -f`/`pkill -f` match the WHOLE command line of every process,
including the shell that is doing the matching and the `bash -c "... > my_sweep.py.log"` wrapper that
started it - the redirect is part of that command line. So:

- wait on PIDs you own: `work/native_lane/<lane>/lane.pid` with `kill -0`, or `$!`, never a pattern
  (`pool.py` waits with `os.kill(pid, 0)` on the pids it launched, and adopts a lane that is already
  running instead of launching a second codex on the same pack);
- for foreign processes only, use the bracket trick - `pgrep -f "[c]odex exec"` - so the pattern
  cannot match the text of the pattern;
- never name a log file after a process something greps for;
- never `pkill -f` from a shell whose own command line contains the pattern.

**Exemplars are the strongest lever in a pack and they go stale silently.** `build_class_pack.py
--exemplars N` cites the solved diffs of the pack's own residue classes and the brief tells the model
to try each one first. The index had not been rebuilt for a day and a half while ~250 rows were
solved. Rebuild it at the start of a round (`refresh_exemplars.py`, ~30 s); it keeps a timestamped
backup, carries forward the hand-maintained rows no lane covers, and refuses candidates that edit a
NON_MATCHING arm, grow scaffolding or were exact only at another stock recipe (a `cells.jsonl`
switch is not a C move), so a pack is never briefed with a move that would be refused at landing.

Tests: `tools/tests/test_pool_plan.py` (plan and `--dry-run`, no launches), `test_land_gap.py` (a
fake `land_lanes.sh` records the tag, lanes, `EXTRA_T`, the twins, the queue lock and the max wait),
`test_refresh_exemplars.py` (base recovery, the legitimacy rules, the per-row pick, the carry
forward), `test_gen_drive_flags.py` (`--fresh`, `--journal-refusals`, with a stub generator that
refuses everything so nothing compiles).

## Isolated landing (round 68)

Until round 68 a landing and a lane could not overlap: `land_lanes.sh` gates by running
`tools/build/mk_ovl_root.sh`, which does `rm -rf build_ovl/tools` + `cp -rL tools/gate/.` and
rewrites `build_ovl/work/g3/overlay_func_compare.py` and the exported row tables - **inside the very
root a lane's `tools/verify.py` is scoring in**. A scorer that loses `match.py` or
`overlay_func_compare.py` for those seconds does not crash the lane, it returns HARNESS-ERROR /
"not exact": a false negative on real work. Hence the refusal at the top of `land_lanes.sh` ("a
codex lane is running: wait for it") and the wait loop in `land_gap.sh`. With six lanes around the
clock, finished work waited hours for a gap.

What is actually shared is smaller than the refusal assumed:

- the **scorer** (`verify.py` -> `tools/aligned_score.py`, run with `cwd=build_ovl`) resolves
  everything from its own root and compiles the candidate in a temp dir. It never reads `src/`:
  a lane scores one candidate FILE against retail bytes, so a landing rewriting other rows cannot
  move its verdict;
- the **window gate** (`overlay_local_gate.py`) is the only thing that reads `src/`, through
  `<root>/overlays/<ov>/first_pass_matched -> src/<ov>`, and builds in `<root>/work/s3_splat/<window>/build`
  under a per-window `fcntl` lock inside that root (`.gate.lock`), so two gates in the same root
  already queue;
- `gate_all.py`'s `inputs_sha` reads `src/` directly, so **the verdict does not depend on which root
  ran it**.

So the gate can simply run somewhere else. `LAND_ISOLATED=1`:

    LAND_ISOLATED=1 bash tools/lanes/land_gap.sh <tag> <lane>...      # or land_lanes.sh directly

- `land_lanes.sh` skips the "a codex lane is running" refusal (lanes score throughout) and gates with
  `EXP=gate SRCROOT=$PWD/src bash tools/build/mk_ovl_root.sh` +
  `GATE_BUILD_ROOT=build_ovl_gate python3 tools/build/gate_all.py`; `build_ovl` is never touched.
  `build_ovl_gate` costs ~250 MB and ~1 s to (re)make - the window build dirs are `--clean`ed per run
  anyway, so nothing is lost by gating in a fresh root;
- a second landing **queues** on `build_ovl/work/land.lock` instead of exiting, and a sweep that is
  not this landing's own no longer refuses the landing: it is waited for (`LAND_POLL`,
  `LAND_WAIT_MAX`). The self-match filter excludes this shell, its ancestors (the wrapper whose
  command line names a `*sweep.py*` log) and its descendants (the cascade's own sweeps);
- `land_gap.sh`'s `busy()` returns "free" at once under `LAND_ISOLATED=1`: there is no gap to wait for;
- `GATE_BUILD_ROOT` also steers `tools/build/container_check.py`, whose whole-container statement
  reads the `.window.bin` files the gate left behind.

Without the variable every one of these files behaves exactly as before (that is what
`tools/tests/test_land_isolated.py` pins). Rollback is `unset LAND_ISOLATED`; `rm -rf build_ovl_gate`
reclaims the disk.

Two things to keep in mind. A landing still rewrites `src/` under a running lane, so a lane holding a
row the landing changes loses that row at landing time ("stale base" - the `.base_sha` guard, which is
what keeps the tree honest); keep a round's pending landings and its live packs on disjoint rows where
possible. And an isolated landing no longer refreshes `build_ovl`, so if `tools/gate/*` changes,
`build_ovl/tools` goes stale (the landing prints a note when it does): run
`bash tools/build/mk_ovl_root.sh` in the next real lane gap.

## L0 / fidelity-site lanes (2026-09-22 Opus wave)

A lane whose whole row list is L0-blocked (LABEL_AS_CALL, PASSTHRU_NO_ARGS or an intra-row noreturn
tail-call) needs a class-specific brief, not a generic pin brief — `docs/L0_BLOCKED_PLAN_20260922.md`
section 6 has the templates that actually paid (ITC pseudo-call deletion / relabelled goto / THREAD-FILL
HOIST / page-base-to-symbol; LAC "init join" / backward-`j`-as-loop / shared-increment join / mid-row
`else`) and the named refusal classes (reg-rename, maspsx LEAD-18 broad, length-drift, hold-set) so a
lane doesn't re-discover them per row. Most rowbase-less LAC/ITC rows are blocked on a missing rowbase
record, not on the rewrite itself: mint one first (`tools/lanes/mint_rowbase.py`, or by hand — region
`[foff, foff+size)`, delta from `ledger/splits/<fam>.jsonl`, `solved` + j-solve proof, regression-verify,
land, then `build_ovl/tools/rowbase.py promote` with an **absolute** path — relative paths CFAIL
silently, cwd is `build_ovl/`) before sending a lane at the row at all.
