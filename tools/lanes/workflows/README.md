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
