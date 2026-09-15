export const meta = {
  name: 'r28-samereg-merge',
  description: 'Opus builds t66_sameregmerge (two register pins on the SAME hard register with disjoint lifetimes merged into one variable, the move that won 5 of 7 rows in the probe4 sol pack); an opus reviewer refutes; implementer fixes',
  phases: [
    { title: 'Implement', detail: 'generator + unit tests + lane_eval on the family rows' },
    { title: 'Review', detail: 'adversarial reviewer reruns everything' },
    { title: 'Fix', detail: 'confirmed defects fixed' },
  ],
}

const RULES = `
Repository: <repo> (run everything from there; python3 from the repo root). Read first: docs/LANE_KIT.md;
tools/xform/t57_keepafterstore.py (the generator contract: class T with name/level/needs_verify, eligible(text,row,census),
apply_verified(text,row,census,vf)); tools/xform/t63_memdep.py (the newest generator in that contract: screen/vf budget,
journal fields, restart-on-win); tools/xform/t62_regfamily.py (hard_register(), the same-register FAMILY erasure: 0 of 186
rows applied - erasing a family is not the move); tools/xform/natural.py host_candidates (a pinned variable renamed onto an
unpinned host: the OPPOSITE direction); tools/xform/t51_sched_order.py (declarations(), units(), mask()); tools/xform/screen.py
(compile_s/sdiff); tools/pin_search_engine.py (improves()); tools/pin_census.py (sites_of, unscored_text, asm_blocker);
tools/pin_sites.py (erase_many); tools/lane_eval.py --help.
HARD RULES: never write under src/, ledger/, config/, build_ovl/; never run sweep.py, gates, pin_search.py, apply_candidates.py,
land_lanes.sh, launch_lane.sh, codex or agy; never run state-changing git. The IO discipline in CLAUDE.md applies: no
recursive search over work/ or the repo root; grep only tools/, include/, docs/, your lane directory and
toolchain/gcc-src/<one version>/ with --max-filesize 4M. Write only under tools/xform/, tools/tests/ and your lane directory
work/native_lane/r28_samereg/ (exists, with rows/, scratch/, tmp/). At most 8 compiles at a time (lane_eval --jobs 6). Another
opus workflow is building tools/xform/varset.py, t64_varset.py and t65_regroute.py right now: never read, import or edit
those three files; do not touch work/native_lane/r28_dev/ or r28_probe/; do not kill or wait on any process you did not
start. No scaffolding may ever appear in a candidate: no new ASM_* macro, __asm__, volatile, fake dependency, do{}while(0),
while(0), for(;0;) or any one-trip block, no new #pragma or attribute, no edit inside an #ifdef NON_MATCHING / port / dead arm
(unscored_text(candidate) must equal unscored_text(text)). A candidate must compile at the row's cell. Never drop or add a
qualifier (volatile/const) - the screen cannot see it. Only vf accepts a candidate; everything else is ranking.`

const MECHANISM = `THE MOVE (measured today by the sol pack work/native_lane/probe4/: 7 of 9 rows exact, 10 pins; read its REPORT.md and
diff base/ against out/ for dungeon/func_81084D04, 819602D8, 8008F228, 809F90DC, 8187A9A8, 80C96F24):
A row often carries two or more \`register T v ASM_REG("$N")\` declarations on the SAME hard register $N in one function,
with disjoint lifetimes (m2c gave each value its own name). Retail's author reused ONE variable: the later value is
carried in the earlier variable, so it inherits the register through the surviving pin and its own pin goes. The pack's
winning shapes: (1) the plain rename - \`register s32 next_x ASM_REG("$3")\` removed, every \`next_x\` written as
\`initial_direction\` (the earlier $3 variable of the same type, dead by then); (2) the same across a type mismatch with
casts - \`register s32 width_unit ASM_REG("$7") = 1;\` removed, the earlier \`register s16 *width_info ASM_REG("$7")\` reused as
\`width_info = (s16 *)1; width_check = (s32)width_info << width_check;\`; (3) the host's declaration hoisted out of its inner
block to the block that encloses both uses, keeping its initialiser when that is a constant or address expression; (4) two
arm-local declarations on the same register in mutually exclusive arms replaced by one declaration in the enclosing block
with arm-local assignments. The allocator reading (tools/alloc_probe.py, tools/alloc_trace.py): the erased pseudo's
suggestion/preference is gone, but a value written into an already-pinned variable needs no allocator decision at all.
Population today (tools/xform/t62_regfamily.hard_register over sites_of): 235 rows hold a same-register family (1,179 pins in
those families, 1,798 pairs): 20 rows with 1-3 pins, 57 with 4-8, 106 with 9-20, 52 with 21+. t62 erased whole families and
landed nothing; natural's host_candidates goes the other way (the pinned variable onto an unpinned host).`

const SPEC = `BUILD tools/xform/t66_sameregmerge.py in the t57 contract (name "t66_sameregmerge", level 1, needs_verify True), also
exposing sameregmerge_candidates(text) -> [(label, text)] for the engine menu (bounded to 48, nearest pairs first).
Candidates: for every ordered pair (H, V) of live ASM_REG declarations on the same hard register in the same function, with
the lifetimes disjoint on a statement-level control-flow graph you derive from t51.units() (labels, goto, if/else, loops,
switch/case, return; conservative: unknown constructs make everything later reachable; refuse when either variable is live
around a loop back-edge that contains the other's lifetime), nearest pairs first: (a) plain rename when the declared types
are identical: V's declaration and pin deleted, every use of V (not struct members, not macro arguments, not labels, not
inner-scope same-named locals, not #ifdef arms) rewritten to H; (b) the cast form when both are word-sized (a pointer and a
32-bit integer, or two 32-bit integers of different signedness): V's definitions become \`H = (TH)(expr);\` and V's reads
\`(TV)H\` (narrow types s8/u8/s16/u16 are refused - the width would change the code); (c) hoisting: when H is declared in an
inner block that does not enclose V, move H's declaration (with its initialiser if that is a literal, a symbol address or a
cast of one; otherwise the initialiser becomes an assignment where the declaration stood) to the nearest block enclosing
both; (d) the two-arm form: two declarations on the same register in the two arms of one if/else (or two case arms) become
one declaration in the enclosing block. Both directions (host the later on the earlier, and the earlier on the later with
the declaration moved) are tried. Each candidate is screened with compile_s/sdiff against the current pinned listing (both
compile at the row's cell; the candidate already has one pin fewer, so nothing is erased separately); vf ONLY on distance-0
candidates that pass pin_search_engine.improves; budgets T66_SCREENS (200) and T66_VERIFY (6) per row, journaled like t63
(pins_in, pins_out, families, pairs, candidates by form, screened, tried, nearest distances, skip reasons); restart on the
new text after a win (the family shrinks, more pairs may fall). Unit tests tools/tests/test_t66_sameregmerge.py: each form on
synthetic texts, the refusals (overlapping lifetimes, a loop back-edge, an address-taken variable, a narrow type in the cast
form, a struct member or macro argument with V's name, a same-named inner-scope local, uses inside #ifdef arms, a
different hard register), and that the output has exactly one pin fewer with unscored_text unchanged.
EVALUATE with tools/lane_eval.py --lane work/native_lane/r28_samereg --module tools/xform/t66_sameregmerge.py --jobs 6 on
rows/samereg_1-8.txt (tag t66_small, all rows) and then the first 60 rows of rows/samereg_9-20.txt (tag t66_mid). Report in
work/native_lane/r28_samereg/REPORT.md: rows eligible, families and pairs per row (median), candidates by form, screened,
exact outputs (row, pins before/after, the form and the pair), and for 10 misses the nearest distance and residue; if a form
never lands, take three of its near-misses through tools/xform/sched_trace.py and say what changed. Do not touch sweep.py,
pin_search_engine.py, natural.py, t62, land_lanes.sh. Return: file paths, the test output, both evaluation tables verbatim,
every skip-reason count.`

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

const impl = await agent(`${RULES}\n\n${MECHANISM}\n\nYOUR TASK (implementer): ${SPEC}`,
  { label: 'impl:t66', phase: 'Implement', model: 'opus', effort: 'high' })

const review = await agent(`${RULES}\n\n${MECHANISM}\n\nYOU ARE THE ADVERSARIAL REVIEWER of tools/xform/t66_sameregmerge.py, just built by another agent to this spec:\n${SPEC}\n\nThe implementer's report:\n${impl}\n\nRefute it. Read the generator in full. Run its unit tests. For five of its exact outputs on real rows (or its five nearest candidates from evidence/ if fewer), diff the C texts by hand: a dropped or added qualifier, a changed width or signedness outside the documented cast form, a rename that captured a struct member, a macro argument, a label, a same-named inner-scope local, or a use inside an #ifdef arm, a merge of two OVERLAPPING lifetimes (construct one synthetic overlapping case per form and show what the tool does), or a hoisted initialiser with a side effect, is BLOCKING. grep the out/ files for ASM_, volatile, __asm__, while (0). Check budget accounting (screened/tried never exceed the limits), that eligible() refuses rows with asm_blocker, that a win restarts on the new text with sites re-read, and that the journal's skip reasons add up. Re-run lane_eval on 20 rows of your own choice from rows/samereg_9-20.txt beyond the first 60 (a new tag) and report its exact count independently. Do not fix anything. Return only defects you demonstrated with evidence, and the exact-row count you confirmed by reading vf results yourself.`,
  { label: 'review:t66', phase: 'Review', model: 'opus', effort: 'high', schema: VERDICT })

const real = (review?.defects || []).filter(d => d.severity !== 'minor')
let fix = 'no blocking or major defects'
if (real.length) {
  fix = await agent(`${RULES}\n\n${MECHANISM}\n\nYou implemented tools/xform/t66_sameregmerge.py (spec: ${SPEC}).\n\nAn adversarial reviewer demonstrated these defects:\n${JSON.stringify(real, null, 2)}\n\nFix each one (or show with evidence that the reviewer is wrong), rerun the unit tests and the t66_small evaluation (tag t66_small2), and return the updated tables and a per-defect note: fixed / disputed (with evidence).`,
    { label: 'fix:t66', phase: 'Fix', model: 'opus', effort: 'high' })
}
return { impl, review, fix }
