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
