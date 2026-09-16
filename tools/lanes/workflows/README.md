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

## r33_catalog.js, r33_oracle.js, r33b_widen.js (round 33, 2026-09-16)

The round-32 plan's step 1, the forward perturbation catalogue, as three Workflows the parent orchestrated and checked.
`r33_catalog.js`: two opus implementers in parallel to one fixed contract (A: `residue.py`, `perturb_basic.py`,
`perturb_catalog.py`, `erase_census.py --fp`; B: `perturb_struct.py`), each with an adversarial reviewer and a fix stage,
then one opus RUNNER (a barrier is right here: it needs both modules) for the census with fingerprints, the 1,000-row and
whole-population catalogues, the match, a calibration and a negative control. 7 agents / 1.98M tokens / 169 min. The
reviewers found three blocking defects in A and two in B (a jump parsed as a declaration; a store/load pair called
independent; a read hoisted across a call; the varset wrappers renaming inside a pin), all fixed with regression tests
proven to fail pre-fix. `r33_oracle.js`: one opus measurer and one adversarial reviewer (the advisor's idea, run before
sizing the widening): the text oracle over the 152 rows a generator landed - which kinds reproduce the pre-landing text
minus its pins, and the missing shapes named from the nearest misses. 3 agents / 817k / 104 min; its report sized the next
script. `r33b_widen.js`: the same two-item shape (C the text-level kinds, the cause table and the bucket-a split; D the
structural kinds and one keyword parameter in `varset.py` with its default proven unchanged), then a runner for the
whole-population re-run, the re-match, the oracle re-run with a control column and the gate re-read. 7 agents / 2.22M /
198 min. Pattern that held across all three: the runner's report ends with a recommendation the parent reads before the
next script is written, and the parent's own fix afterwards (the `__typeof__` declaration scanner) was the only edit not
made by an agent. Row lists and evidence live in `work/native_lane/r33_catalog/`; rebuild `scratch/census_fp2.jsonl` and
the catalogues under `work/perturb_catalog/` before reuse (both behind `.ignore`).

## r34_wave.js (round 34, 2026-09-16 evening)

The targeted wave's CPU items, sized by round 33's buckets read against the sweep journals: item A, t69_prologue's 72 rows
where its candidate was produced and vf refused it, composed with a register or ordering lever; item B, the address family
(t29_addrsym's refusal table with the pins behind it, its missed candidates composed with a copy drop, t54's `noop` rows
read for their shape). Two opus implementers in parallel, two adversarial reviewers, two fixes; no runner - the parent
swept the opened modules over the tree, landed with `land_lanes.sh` and gated once. 6 agents / 1.40M tokens / 118 min.
Result: four honest negatives on A (the residue is decided at `greg`: which copies are parameters) and one opening
(`T69_ADDR_MEMBER`, 5 rows / 14 pins tree-wide), two openings and three negatives on B (`T29_DEREF_USE` 2 rows / 17 pins;
`T29_SYMDEF` 1 pin of 297, off; NONRAM off; the composition 0; t54 not blind); -33 pins. The row lists came from
`work/native_lane/r33_catalog/rows/match3/` and the parent's journal scan (`r34_wave/rows/wave_*.txt`); rebuild them
before reuse.
