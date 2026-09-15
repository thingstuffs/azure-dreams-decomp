# Opus workflow scripts (round 27)

The two Workflow-tool scripts that built round 27's tooling, kept as templates. Pattern: one opus implementer per
item, then one opus ADVERSARIAL reviewer that must rerun every command on the real repository and return only
demonstrated defects (schema-forced), then the implementer fixes the blocking/major ones; the session owner reviews
last and integrates. Every round-26/27 tool had a blocking defect its reviewer proved (ledger cache blind to code
changes, pool table reading one search tag, t63 dropping `volatile` invisibly to the assembly screen), so the reviewer
stage is not optional. Usage per workflow: ledger+pools 6 agents / 762k subagent tokens / 44 min; t63 3 agents /
598k tokens / 90 min (its evaluations ran inside the agents). Row-id list paths in the specs point at a session
scratchpad; regenerate them (`tools/lanes/pools.py --rows ...`) before reuse.

Round 28 added `r28_varset.js`: two generators in one `pipeline()` (item A `tools/xform/varset.py` + `t64_varset.py`, the
variable-set moves learned from the lane-won diffs; item B `t65_regroute.py`, the probe-directed register moves), each with
its own adversarial reviewer and fix stage, the implementers running in parallel and forbidden to import each other's new
module (a race). The EVIDENCE block names measurement files under `work/native_lane/r28_dev/` (the exemplar corpus from
`build_exemplars.py`, `tools/lanes/reach.py` and `declmoves.py` outputs, frozen row lists from `pools.py --json`): rebuild
those before reuse. Launched with `Workflow({scriptPath})` so the file in this directory IS the run's script.
`r28_samereg.js` (the same round): one implementer, one adversarial reviewer, one fix - the single-generator template (t66_sameregmerge,
the probe4 sol pack's move as a generator; 3 agents / 672k tokens / 89 min; its sweep removed 238 pins). Its MECHANISM block was
written from the pack's REPORT.md and diffs within the hour: the pattern to repeat whenever a pack wins several rows by one move.

Round 29 added `r29_tail_samereg2.js`: the two-item pipeline again (item A a new generator, `t67_tailform`; item B an OPENING of
an existing one, the two largest refusal classes of `t66_sameregmerge`, with the implementer owning that file for the run).
Usage 6 agents / 1.59M subagent tokens / 158 min. Item B paid (68 rows / 131 pins on the rows the refusals had named); item A
measured its own mechanism away (jump.c's cross_jump canonicalises most tail moves) and is kept as a small generator with the
finding in its docstring. The EVIDENCE blocks name `work/native_lane/r29_tail/` (row lists, the exemplar corpus, the
control-flow inventory from `tools/lanes/ctrlmoves.py`): rebuild them before reuse.

## r30_samereg3_addr.js (round 30, 2026-09-15 evening)

Two items, each implementer -> adversarial reviewer -> fix, all opus at effort high. Item A opened
`t66_sameregmerge` on its whole-tree refusal table (the brief carried the table and the code reading behind
the largest count: `decl-unparsed` was a scan stopper, not a parser gap): six openings, `T66_DECL_RUN`,
`T66_ASM_OPERAND`, `T66_COMPOUND`, `T66_INIT_PLACE`, `T66_SHADOW`, `T66_TRY_INTERFERENCE` (clashing pairs offered
under vf - the argument: both variables share one hard register in a byte-exact row). Evaluation 75 rows /
146 pins on 113 row-slots; the reviewer's three majors (a rename capturing an anonymous aggregate's member; a
crossed initialiser with a side effect; an ASM_* sub-expression spelled bare) fixed at zero cost, 117 tests.
Item B read the address-materialisation residue class (231 near sites from `erase_census.py --diff 4`) against
t54/t59: one mechanism at every cell (cse `fold_rtx` folds the kept page plus the offset into one CONST_INT), so
the repair is "name the symbol"; four openings of `t59_offsetsym`, 3 rows / 4 pins of 100, the remainder is the
scheduling class after respelling; three majors fixed (braceless control flow, a whole-line replacement span,
the keep-gap loop without a structural test), 75 tests. Usage: 6 agents / 1.46M subagent tokens / 142 min.
