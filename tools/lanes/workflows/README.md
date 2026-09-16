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

## r32_t69tail.js (round 32, 2026-09-16 morning - the owner's "next batch")

The owner: "for the next batch you can use a workflow, use opus to implement and review then you do a final check". One
item, implementer -> adversarial reviewer -> fix, opus at effort high: the three t69_prologue refusals that round 32's
refusal table (pins behind each refusal) left with pins behind them - a copy spelled through a cast (`T69_CAST_COPY`), an
ERASABLE pin as the only use before the copy (`T69_PIN_BEFORE_COPY`), two locals copying one parameter (`T69_TWICE`) - plus
the DROP_REG residue classified on its 228 missing rows and one t66 composition screened. Result: three honest negatives
(0 verified pins on 35 rows; the switches stay off; menu identity with them off proved over all 1,300 pinned rows and the
whole-tree refusal table reproduced byte-for-byte), 85 tests. The reviewer's one major was a false sentence in the report,
not the code: `T69_TWICE` is the ONLY way t69 reaches a class that sits one register word from retail on 10 rows (`move
$7,$4` in retail, `move $7,$19` in the candidate: the argument taken from the incoming register, not the callee-saved copy
the ASM_REG holds) - next round's lead, to compose with a register-assignment lever. Measurement D: the DROP_REG misses
are 65 ordering-only (50 of them `-move,sw +move,sw` at d=4), 20 colouring-only, 86 both, 55 changed; the t66 composition
is structurally impossible there (no row has two ASM_REG declarations on one register). The parent's final check: tests,
the diff, the docs. Usage: 3 agents / 631k subagent tokens / 71 min.

## r31_prologue.js (round 31, 2026-09-16)

One item, implementer -> adversarial reviewer -> fix, opus at effort high: the PROLOGUE scheduling class that
`tools/lanes/sched_map.py` isolated (89 sites / 65 rows where a body statement's instructions exchange order with the
`$sp` adjust or a callee-saved store). The brief carried the site list, five listing diffs read in context, and the
priority hypothesis; the implementer found the mechanism one pass earlier than the census said (sched1's
`adjust_priority` -> `birthing_insn_p`: a single-set producer is promoted to LAUNCH_PRIORITY, and `ASM_KEEP(x)` is a
second set of x) and the lever: a function's redundant m2c parameter copies dropped TOGETHER - one of four leaves the
listing 132 lines away, all four reach 0, which is why one-copy-at-a-time `dropcopy` never saw it. `t69_prologue`: 8 of
45 rows / 24 pins, held-out 0 of 20; the reviewer's two majors (directive lines rewritten, a retype without a use guard)
fixed with 25 new tests. The harness refused the subagents' REPORT.md writes; the parent assembled the report from the
returned text. Usage: 3 agents / 613k subagent tokens / 86 min.
