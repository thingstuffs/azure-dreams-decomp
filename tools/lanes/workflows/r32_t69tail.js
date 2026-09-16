export const meta = {
  name: 'r32-t69tail',
  description: 'Opus opens the three t69_prologue refusals that round 32\'s refusal table left with pins behind them (a copy spelled through a cast, a pin as the only use before the copy, two locals copying one parameter), measures the DROP_REG residue, and is reviewed adversarially; implementer -> reviewer -> fix, the parent does the final check.',
  phases: [
    { title: 'Implement', detail: 'one opus implementer: three openings behind env switches, unit tests, lane_eval on the frozen rows, one measurement' },
    { title: 'Review', detail: 'adversarial opus reviewer reruns everything and returns demonstrated defects only' },
    { title: 'Fix', detail: 'implementer fixes blocking/major defects and re-measures' },
  ],
}

const RULES = `
Repository: the git checkout that holds tools/common.py (your working directory; run everything from there with python3 -B).
Read first: docs/LANE_KIT.md; docs/PIN_MECHANISMS_20260912.md "Round 32" and "Round 31" (the prologue mechanism: sched1's
adjust_priority -> birthing_insn_p promotes a single-set producer, ASM_KEEP(x) is a second set of x, so a function's
redundant parameter copies are dropped TOGETHER); work/native_lane/r32_family/REPORT.md (this morning's refusal table read
with the pins behind each refusal, the two openings already landed - T69_DROP_REG, now default on - and the negatives);
tools/xform/t69_prologue.py in full (entry_copies is the refusal chain, first-match; merge applies a chosen set; Detail is the
counter that records (refusal, local); the T69_* env switches and their tests); tools/tests/test_t69_prologue.py (62 tests:
the style to extend); tools/xform/t36_paramwidth.py functions(); tools/xform/screen.py (compile_s/sdiff: the free cc1
screen against the pinned listing - ranking only, vf decides); tools/pin_census.py (sites_of, unscored_text, asm_blocker);
tools/pin_sites.py (erase_many); tools/lane_eval.py --help; work/native_lane/r32_family/scratch/dropreg_screen.py (screen an
opening over every row it applies to, OPEN_NOTE selects the journal note), scratch/t69_refusals.py and scratch/t69_silent.py
(how the tables were built).
HARD RULES: never write under src/, ledger/, config/, build_ovl/; never run sweep.py, gates, pin_search.py,
apply_candidates.py, land_lanes.sh, launch_lane.sh, codex or agy; never run state-changing git (read-only git show/log/diff
is fine). The IO discipline in CLAUDE.md applies: no recursive search over work/ or the repo root; grep only tools/, include/,
docs/, your lane directory and src/ (small) with --max-filesize 4M. Write only under tools/xform/t69_prologue.py,
tools/tests/test_t69_prologue.py and your lane directory. At most 8 compiles at a time (lane_eval --jobs 6). No scaffolding
may ever appear in a candidate: no new ASM_* macro, __asm__, volatile, fake dependency, do{}while(0), while(0), for(;0;) or
any one-trip block, no new #pragma or attribute, no edit inside ANY preprocessor arm (#ifdef NON_MATCHING, #ifdef __mips__,
#if 0 ...; the mips build compiles one arm and the gate cannot see the other - t69 keeps its own _pp_depth map, keep using
it). A candidate must compile at the row's cell; it may never drop or add a qualifier (volatile/const), change a width, a
signedness, an offset or a symbol; a pointer retype is allowed only where t69's _retype_safe already allows it. Only vf
accepts a candidate; everything else is ranking. Every opening is behind an env switch with a journalled note
(opened-<name>), written refusals first and tested; every opening must leave the menu of every row it does not apply to
byte-identical (prove it: prologue_candidates with the switch on and off over 40 pinned rows without the shape). The
harness may refuse writes of .md files: write your report as <lane>/report_impl.txt and ALSO return its full text.
An honest negative (the opening reaches 0 on none of its rows, with the screen table) is a complete deliverable.`

const SPEC = `YOUR LANE DIRECTORY: work/native_lane/r32_t69tail/ (exists: rows/, scratch/, tmp/). YOU OWN tools/xform/t69_prologue.py
and tools/tests/test_t69_prologue.py.
THE POPULATIONS (round 32's refusal table, work/native_lane/r32_family/rows/t69_refusals.txt and t69_silent.txt; every row
list is frozen in rows/):
  A. rows/castcopy_rows.txt (5 rows, 7 keeps behind): the redundant copy is spelled through a cast to the LOCAL'S OWN type -
     \`u8 *render_bytes = (u8 *)render_data;\` (dungeon/func_80AE9000), \`copy_src = (CopyBlock *) sprite_template;\`
     (dungeon/func_8132B300) - which t69's DECL regex and copy regex (a bare identifier initialiser) never enumerate, so no
     refusal is journalled. Opening T69_CAST_COPY: accept \`(T) p\` / \`(T)p\` as the initialiser or the copy's right side when
     T, whitespace-normalised and stripped of \`register\`, equals the local's declared type; the merge then retypes the
     parameter to T through the existing _compatible/_retype_safe path (every surviving use a bare value) and the cast goes
     with the copy. A cast to any OTHER type is not this opening (refuse: cast-type-differs).
  B. rows/usebefore_rows.txt (3 rows, 11 keeps behind): \`register void *view ASM_REG("$8"); ... ASM_SET(view); view = segment;
     ASM_KEEP_NV(view);\` (dungeon/func_800AA49C) - the only occurrence of the local before its copy is an ERASABLE pin
     statement (ASM_SET / ASM_KEEP / ASM_KEEP_NV naming exactly that local), which the merge erases anyway. Opening
     T69_PIN_BEFORE_COPY: the use-before-copy test ignores occurrences that lie inside an ERASABLE pin statement naming the
     local alone; any other occurrence before the copy keeps the refusal. These rows are also REG-pinned (T69_DROP_REG,
     default on, handles that part). Note that ASM_SET(v) BEFORE the copy is a set of v that makes reg_n_sets 2 or 3 - read
     Round 31's mechanism paragraph and say in the report what erasing it does to the promotion.
  C. rows/copiedtwice_rows.txt (8 rows, 8 keeps behind; seven are one template family, dungeon/func_80BC1BA8 ... func_80BE5BA8):
     two locals both copy the same never-written parameter (\`void *entry_entity = entity;\` and \`void *callback_entity =
     entity;\` in one function); t69 merges the first and refuses the second (param-copied-twice), and after the merge the
     second copy reads \`callback_entity = entry_entity;\`, a local-to-local copy whose keep stays. Opening T69_TWICE: when the
     parameter is never written and neither local is (the existing checks), BOTH locals are the parameter: the parameter
     takes the first local's name, every occurrence of the second local is renamed to it too, both declarations and both
     copies go, and the ERASABLE pins naming either local are erased (a pin that names both, or a multi-variable pin, keeps
     the row refused as today). Types: the parameter may take a local's type only where _compatible/_retype_safe allow it
     today; if the two locals' types differ from each other, refuse (twice-types-differ).
  D. MEASUREMENT ONLY, no building: rows/dropreg_miss_rows.txt lists the 228 rows where T69_DROP_REG produces a candidate
     whose best screen distance is above 0 (11 rows reached 0 and landed). For each row take the best candidate (t69's own
     ranking, prologue_candidates + compile_s/sdiff against the pinned listing), and classify the residue lines the way
     tools/lanes/erase_census.py's --diff records let round 30 do it: the same instructions MOVED (order only), the same
     instructions RECOLOURED (registers differ, opcodes and operands otherwise equal), an operation CHANGED (anything else).
     Report the table (class x count, and the five most common residue shapes in each class with a row each). Then, on the
     RECOLOURED rows only, screen ONE composition: the best DROP_REG candidate followed by tools/xform/t66_sameregmerge.py's
     candidates (its own menu function; read the module for its name and contract) and report how many reach 0 (screen
     only; do not verify). If the composition reaches 0 on three or more rows, say so and stop: that is the next round's
     item, not yours.
DELIVERABLES, in order:
  1. The three openings (A, B, C) in tools/xform/t69_prologue.py, each behind its env switch (default OFF), with the refusals
     written first, journalled notes, and unit tests for every move and every must-refuse case (extend the Refusals class;
     mock.patch.dict(os.environ, ...) as the existing tests do). All existing tests must still pass unchanged.
  2. The menu-identity proof: prologue_candidates with all three switches on vs off over 40 pinned rows that carry none of
     the three shapes - identical candidate lists (labels and texts). Put the script in scratch/ and its output in rows/.
  3. Evaluation under vf: tools/lane_eval.py --lane work/native_lane/r32_t69tail --module tools/xform/t69_prologue.py
     --rows rows/<list> --tag <cast1|usebefore1|twice1> --jobs 6 with the relevant switch set in the environment (one run
     per opening on its own row list). Report rows / hits / pins per opening, the refusal counts, and for every hit the
     candidate label and the C diff (git diff --no-index src/<id>.c out/<id>.c) read by you: no width, signedness, qualifier,
     offset or symbol change, no edit in a preprocessor arm.
  4. The measurement D as a table.
  5. report_impl.txt in the lane: what each opening is, its population, its result, every refusal count, the identity proof,
     the measurement table, and a recommendation per opening: default on (paid, cheap), keep closed (paid nothing), or
     remove. Return: file paths, the test output, the tables verbatim, the full report text.`

const VERDICT = {
  type: 'object',
  properties: {
    defects: { type: 'array', items: { type: 'object', properties: {
      severity: { type: 'string', enum: ['blocking', 'major', 'minor'] },
      where: { type: 'string' }, what: { type: 'string' }, evidence: { type: 'string' } },
      required: ['severity', 'where', 'what', 'evidence'] } },
    exact_rows_confirmed: { type: 'integer' },
    summary: { type: 'string' },
  },
  required: ['defects', 'exact_rows_confirmed', 'summary'],
}

const REVIEW_CHECKS = `Refute it. Read the report and tools/xform/t69_prologue.py in full, then git diff the tool and its tests against HEAD
(read-only) so you review exactly what changed. Run the unit tests. For EVERY exact output in the lane's out/ (there will be
few), diff the C text by hand against src/: a parameter retyped where a surviving use is not a bare value, a cast dropped
whose type was not the local's own, a second local renamed where the two values could differ (either local or the parameter
written anywhere, a use of the second local before its copy on some path, an address taken), an ERASABLE pin erased that
named a DIFFERENT variable, a pin left that names a variable that no longer exists, a dropped or added qualifier, any edit in
an #ifdef arm (compare the NON-mips arms of source and output), a directive line touched - each is BLOCKING. Construct at
least two synthetic must-refuse cases per opening and show what the tool does with the switch on (a cast to a different type;
a qualifier inside the cast; a real read of the local before its copy next to the pin; a pin naming two variables; the
parameter written after the second copy; the two locals with different types; the second local used before its copy). Rerun
the menu-identity proof on 40 rows of YOUR choice. Rerun lane_eval yourself on each opening's row list with a new tag
(cast_r, usebefore_r, twice_r) and report the exact counts you read from the evidence (final.exact), independently of the
implementer's numbers. Check that all three switches default OFF and that with them off the whole-tree text scan
(work/native_lane/r32_family/scratch/t69_refusals.py, run into a scratch file of your own) reproduces
work/native_lane/r32_family/rows/t69_refusals.txt exactly. Check measurement D's classification on five rows by reading the
listings yourself. Do not fix anything. Return only defects you demonstrated with evidence, and the exact-row count you
confirmed.`

const ITEMS = [
  { key: 't69tail', file: 'tools/xform/t69_prologue.py (three openings) and tools/tests/test_t69_prologue.py', spec: SPEC },
]

const results = await pipeline(ITEMS,
  item => agent(`${RULES}\n\nYOUR TASK (implementer): ${item.spec}`,
    { label: `impl:${item.key}`, phase: 'Implement', model: 'opus', effort: 'high' }),
  (report, item) => agent(`${RULES}\n\nYOU ARE THE ADVERSARIAL REVIEWER of ${item.file}, just changed by another agent to this spec:\n${item.spec}\n\nThe implementer's report:\n${report}\n\n${REVIEW_CHECKS}`,
    { label: `review:${item.key}`, phase: 'Review', model: 'opus', effort: 'high', schema: VERDICT }).then(v => ({ report, verdict: v })),
  (r, item) => {
    const real = (r.verdict?.defects || []).filter(d => d.severity !== 'minor')
    if (!real.length) return { item: item.key, report: r.report, verdict: r.verdict, fixed: 'no blocking or major defects' }
    return agent(`${RULES}\n\nYou implemented ${item.file} (spec: ${item.spec}).\n\nAn adversarial reviewer demonstrated these defects:\n${JSON.stringify(real, null, 2)}\n\nFix each one (or show with evidence that the reviewer is wrong), rerun the unit tests, the menu-identity proof and each opening's lane_eval with a new tag (<opening>2), and return the updated tables and a per-defect note: fixed / disputed (with evidence). Append a "Review fixes" section to the lane's report_impl.txt and return the full updated report text.`,
      { label: `fix:${item.key}`, phase: 'Fix', model: 'opus', effort: 'high' }).then(fix => ({ item: item.key, report: r.report, verdict: r.verdict, fixed: fix }))
  })

return results.filter(Boolean)
