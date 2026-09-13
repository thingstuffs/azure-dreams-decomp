# Lane kit: what a blocker lane gets, and what to harvest from it

Owner rule (2026-09-13): astra when the other avenues struggle, or when it is likely to unlock a larger
piece of work. Use it sparingly, but get the most from each run: set it up for its best chance of
success, and harvest its techniques, advice, temporary tooling and anything it had to fetch. Row packs
and fence packs stay on luna. Lanes so far: `work/native_lane/sched_astra` (round 16, the first
scheduler, which produced `t51_sched_order`), `work/native_lane/reg_astra` (round 18, register pins:
`t53_reg_state`), `work/native_lane/page_astra` (round 18, page-base pins: `t54_pagebase`) and
`work/native_lane/keep_astra` (round 19, keeps outside page bases: the CSE hide).

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
   whatever is reusable into `tools/`, and add anything it had to fetch to this kit.
5. **Its advice**, including what it would do next or better, goes into the next brief and
   `docs/HANDOVER.md`.
