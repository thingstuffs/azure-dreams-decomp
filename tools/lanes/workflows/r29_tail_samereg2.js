export const meta = {
  name: 'r29-tailform-samereg2',
  description: 'Opus builds t67_tailform (a shared tail duplicated into its predecessors / duplicated tails merged - the control-flow class the lane diffs use most) and opens t66_sameregmerge\'s two largest refusal classes; an adversarial opus reviewer refutes each; implementers fix',
  phases: [
    { title: 'Implement', detail: 'one opus implementer per item, with unit tests and lane_eval' },
    { title: 'Review', detail: 'adversarial opus reviewer reruns everything and returns demonstrated defects only' },
    { title: 'Fix', detail: 'implementer fixes blocking/major defects and re-measures' },
  ],
}

const RULES = `
Repository: <repo> (the repository root that holds tools/common.py; run everything from there; python3 from the repo root).
Read first: docs/LANE_KIT.md; tools/xform/t57_keepafterstore.py (the generator contract: class T with name/level/needs_verify,
eligible(text,row,census), apply_verified(text,row,census,vf)); tools/xform/t66_sameregmerge.py (the newest generator in that
contract and its control-flow graph over t51.units(): the pattern to reuse); tools/xform/t64_varset.py and tools/xform/varset.py
(the erase-first depth-2 search, the definition webs); tools/xform/natural.py (menu generators; gotoloop, ret2break,
hoist_from_goto_arm, dup_after_if in t15_shapes.py are the EXISTING control-flow moves); tools/xform/t48_gotoreturn.py,
t41_gotoloop.py, t44_doloop_greedy.py; tools/xform/screen.py (compile_s/sdiff); tools/pin_search_engine.py (improves());
tools/pin_census.py (sites_of, unscored_text, asm_blocker, arm_labels - which labels ONLY NON_MATCHING conditions, so every
generator must keep its own map of preprocessor regions, as t66 does); tools/pin_sites.py (erase_many); tools/lane_eval.py --help.
HARD RULES: never write under src/, ledger/, config/, build_ovl/; never run sweep.py, gates, pin_search.py, apply_candidates.py,
land_lanes.sh, launch_lane.sh, codex or agy; never run state-changing git (read-only git show/log is fine). The IO discipline
in CLAUDE.md applies: no recursive search over work/ or the repo root; grep only tools/, include/, docs/, your lane directory
and toolchain/gcc-src/<one version>/ with --max-filesize 4M (src/ may be searched with rg --max-filesize 4M: it is small).
Write only under tools/xform/, tools/tests/ and your lane directory (given below). At most 8 compiles at a time (lane_eval
--jobs 6). Other jobs share the machine (a sweep, a lane_eval pilot, the other implementer of this workflow): do not kill,
wait on, or read their directories; never edit a file the other item owns. No scaffolding may ever appear in a candidate:
no new ASM_* macro, __asm__, volatile, fake dependency, do{}while(0), while(0), for(;0;) or any one-trip block, no new #pragma
or attribute, no edit inside ANY preprocessor arm (#ifdef NON_MATCHING, #ifdef __mips__, #if 0 ...; the mips build compiles
one arm and the gate cannot see the other). A candidate must compile at the row's cell; it may never drop or add a qualifier
(volatile/const), change a width, a signedness, an offset or a symbol. Only vf accepts a candidate; everything else is ranking.
Every generator is reviewed by an adversarial agent who found a blocking defect in every round-27/28 tool (a silent volatile
drop; edits in a non-mips arm; an interference edge missing from a liveness test; a substring rename): write the refusals
first and test them.`

const SPEC_TAIL = `YOUR LANE DIRECTORY: work/native_lane/r29_tail/ (exists: rows/, ex/, ctrlmoves.py, scratch/, tmp/).
THE EVIDENCE (measured, read it): the lane-won exemplar diffs of the last 60 commits (ex/reg 403 register, ex/KEEP 220, ex/FENCE
177; a diff's pre text is \`git show <commit>~1:src/<row>.c\`, post \`git show <commit>:src/<row>.c\`) carry a control-flow change in
76 / 64 / ~62 of them, and ctrlmoves.py (its output in ex/*/lane_won.txt.ctrlmoves.json) classifies those: TAILMERGE 35/30/36
(a statement run that stood twice now stands once: the lane merged duplicated tails under one label or hoisted a common tail
out of both arms), TAILDUP 19/15/27 (the reverse: a shared tail after a label reached by several gotos, or after an if/else,
copied into each predecessor), LOOPFORM 35/19/10 (already served by t41/t44/natural gotoloop), RETSPLIT 17/17/6, GOTO2RET 9/4/8
(served by t48), ARMSWAP 9/4/5, EARLYRET 6/9/4, OTHER 35/39/30. Two real examples to read first: ex/reg/dungeon_func_800D2A74.dd967a78.diff
(four \`goto advance_phase\` sites; the lane copied the two-statement tail into each and dropped both labels) and
ex/reg/dungeon_func_81257000.17a95a06.diff then ex/FENCE/dungeon_func_81257000.d7a6d7dd.diff (the SAME function: one lane merged
the two arms' brightness tails into a shared tail, a later lane duplicated them back into the arms - both directions are real
moves and only the byte verdict decides). Pins whose notes name the mechanism: 138 pins in 102 rows say "basic-block layout",
351 in 188 rows "delay-slot", 300-odd more "moves a statement across a call/branch" (rows/ctrl_noted_1_20.txt: 430 such rows
with 1-20 pins, 2,544 pins, fewest pins first). GCC 2.x cross-jumps identical tails
(jump.c, cross_jump) and fills delay slots from the tail (reorg.c): the SOURCE shape decides which basic-block layout and
which delay-slot fill the retail bytes show, and no generator today changes that shape except through loops and returns.
BUILD tools/xform/t67_tailform.py in the t57 contract (name "t67_tailform", level 1, needs_verify True) exposing
tailform_candidates(text) -> [(label, text)] for the engine menu (<= 48, nearest a pin site first). Moves, each on a
statement-level control-flow graph built from t51.units() as t66 builds its own (labels, goto, if/else, loops, switch/case,
return; unknown constructs refuse), never across a preprocessor arm, never moving or copying a pin statement (an ASM_* line
inside a tail makes that tail ineligible; the candidate is then tried with the nearest pin erased instead, as t64 does):
  dup_label   a label L with k >= 2 incoming \`goto L;\` whose tail T (from L to the next terminator - return / goto / break /
              continue - at most 8 statements, no label, no declaration, no pin) is copied over each \`goto L;\`; the label and
              its tail stay when control also falls through into L, otherwise they go. Also with k == 1 when the goto is the
              only entry (a tail moved to its one predecessor).
  sink_tail   \`if (c) { A } else { B } T\` (T = the statements after the if/else up to the next terminator or label, <= 8, no
              declaration, no pin) -> \`if (c) { A; T } else { B; T }\`; the same for an if without else when A ends in a
              terminator (T is copied into the arm as well as left in place only when A does not terminate - refuse that).
  hoist_tail  the reverse: \`if (c) { A; T } else { B; T }\` with identical T (token-equal after comment stripping) ->
              \`if (c) { A } else { B } T\`.
  merge_runs  two identical statement runs (>= 2 statements, or 1 statement that is a terminator with an argument) in
              different places, each ending in the same terminator (return E; / goto M; / break;): the second becomes
              \`goto L;\` with a fresh label L placed before the first when the first is the last statement of its block
              (control must not fall through into L from elsewhere unless it already did) - the m2c/cross-jump shape.
  split_ret   \`v = E1; goto R;\` ... \`v = E2; goto R;\` ... \`R: return v;\` -> \`return E1;\` / \`return E2;\` (RETSPLIT), when v has
              no other use; and the reverse where two \`return E;\` with the same E are merged under one label.
Each move both directions where it has one; candidates nearest a live pin site first (the pin's line), each tried as is and
with the nearest pin erased (erase_many, clean_notes=True; re-read sites_of), screened by compile_s/sdiff against the current
pinned listing, vf only at distance 0 and improves(). Depth 2: the 8 nearest depth-1 texts get one more move (T67_BEAM, default
8). Budgets T67_SCREENS (400) and T67_VERIFY (6) per row, journaled like t66 (pins_in/out, moves offered per kind, screened,
tried, nearest distances, skip reasons, first-pass counts). Unit tests tools/tests/test_t67_tailform.py: every move on
synthetic texts in both directions, and the refusals: a tail with a declaration, a pin, a label, or a preprocessor line; a
label with a fallthrough entry (kept); a goto into a loop body; a run that is not token-identical; a terminator with a
side-effecting argument duplicated (refuse \`return f();\` duplication? no - copying a call is fine, it runs once per path;
refuse only when the tail reads a variable assigned differently on the paths - it cannot, the tail is copied verbatim, but
a \`goto L\` from inside a loop whose tail contains \`break\` changes meaning: refuse break/continue inside a copied tail when the
copy lands in a different loop depth); unscored_text unchanged; exactly the expected pin count.
EVALUATE with tools/lane_eval.py --lane work/native_lane/r29_tail --module tools/xform/t67_tailform.py --jobs 6 on
the first 250 rows of rows/ctrl_noted_1_20.txt (tag t67_ctrl) and the first 80 of rows/keep_near_1_8.txt (tag t67_keep). Report in
work/native_lane/r29_tail/REPORT.md: rows eligible, candidates per row by move (median), screened, exact outputs (row, pins
before/after, move, direction), and for 10 misses the nearest distance and residue. Also the text-level check on the exemplars:
for the TAILDUP and TAILMERGE diffs in ex/*/lane_won.txt.ctrlmoves.json, does tailform_candidates(pre) contain the landed
skeleton at depth 1 or 2 (reuse the skeleton and distance functions of work/native_lane/r28_dev/tools/reach2.py by import;
do not edit that file) - report the count per move and family. If a move never lands, take three of its near-misses through
tools/xform/sched_trace.py and say what the jump/reorg dumps show. Do not touch sweep.py, pin_search_engine.py, natural.py,
t41/t44/t48/t66/t64, land_lanes.sh. Return: file paths, the test output, both evaluation tables verbatim, the exemplar
reachability counts, every skip-reason count.`

const SPEC_SAMEREG2 = `YOUR LANE DIRECTORY: work/native_lane/r29_samereg2/ (exists: scratch/, tmp/; create rows/).
THE EVIDENCE: tools/xform/t66_sameregmerge.py (built and reviewed yesterday, 34 tests) swept 238 pins from 127 rows in two
minutes; its journals (work/native_lane/r28_samereg/evidence/t66_small2/*.json and t66_mid/*.json, field info.skips, first
pass) and REPORT.md name its two largest refusals, both spelling problems rather than program problems:
  host-name-collision (141 pairs in 15 rows): the host's name means something else (an inner local or a global) in the block
    the merged declaration would cover, so the rename would capture it (t66 line ~776, in the hoist target loop).
  in-macro-arg (183 pairs in 45 rows): a mention of V inside the argument list of ANY uppercase macro call (MACROARG_RE,
    line 116: \`[A-Z][A-Z0-9_]{2,}\\s*(\`), refused wholesale (line ~301) - that includes ASM_KEEP(V), ASM_KEEP_NV(V), ASM_USE(V),
    M2C_FIELD(...) and the SDK's own macros, none of which stringify their argument.
Read t66 in full first (its Facts/Flow/pairs_of/build structure), its tests, and the two example rows the journals name
for each refusal (pick two rows per class from the evidence files; diff what the refusal blocked).
BUILD, in tools/xform/t66_sameregmerge.py itself (you own that file for this workflow; keep every existing form and test
passing; bump the module docstring's RESULT section), two openings behind env switches that default ON:
  1. T66_RENAME_HOST (default 1): when the host name collides in the target block, try the merge with the SURVIVING variable
     renamed to V's name (if V's name is free in that block) or else to a fresh name \`<host>_m\` (never one already in the
     function): every use of H in H's scope rewritten (a local's name is byte-neutral on this port), then the merge as before.
     The declaration keeps its type, register binding and initialiser.
  2. T66_MACRO_ARGS (default 1): a mention of V inside a macro argument no longer refuses the pair; it is renamed like any other
     use, EXCEPT inside the ASM_REG binding of a declaration (that is the pin being deleted or kept), and except when the
     macro is one that takes a member or symbol NAME rather than a value (there are none in include/ today - verify by
     listing every function-like macro in include/*.h and include/records/*.h that uses # or ## on its parameter, and refuse
     those by name). A renamed ASM_KEEP(V) becomes ASM_KEEP(H): the pin count is unchanged (assert it) and the keep still
     keeps the same value at the same point.
Unit tests added to tools/tests/test_t66_sameregmerge.py for both openings and their refusals (a colliding host that is
itself pinned in the inner block; a macro that stringifies; the ASM_REG binding never renamed; pin count exactly one fewer).
EVALUATE with tools/lane_eval.py --lane work/native_lane/r29_samereg2 --module tools/xform/t66_sameregmerge.py --jobs 6 on the
rows whose t66 journal carries either refusal (write rows/refused_rows.txt from the evidence files: 45 + 15 rows, ordered by
pairs refused), tag t66v2_refused, and on the first 60 rows of work/native_lane/r28_samereg/rows/samereg_21plus.txt (tag
t66v2_big; the 21+ band was swept but never examined). Report in work/native_lane/r29_samereg2/REPORT.md: per opening, pairs
newly offered, screened, exact, pins; the refusal table before/after; exact outputs (row, pins before/after, form, pair).
Do not touch any other generator, sweep.py, natural.py or land_lanes.sh. Return: file paths, the test output, both tables
verbatim, every skip-reason count.`

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

const REVIEW_CHECKS = `Refute it. Read the generator in full. Run its unit tests. For five of its exact outputs on real rows (or its five
nearest candidates from the lane's evidence/ if fewer), diff the C texts by hand: a copied or moved statement that crosses a
preprocessor line, a loop boundary (a break/continue whose loop changed), a label with a fallthrough entry that was deleted, a
tail copied with a declaration or a pin inside, a merge of two runs that are not token-identical, a rename that captured a
struct member, a macro argument that stringifies, a label or an inner-scope local, a dropped or added qualifier, or any edit in
an #ifdef arm (compare the NON-mips arms of source and output: the gate cannot see them) is BLOCKING. Construct one synthetic
case per move/opening that MUST be refused and show what the tool does. grep the out/ files for ASM_, volatile, __asm__,
while (0), and count ASM_* per file against the source. Check budget accounting, that eligible() refuses rows with
asm_blocker, that a win restarts on the new text with sites re-read, that skip reasons add up. Re-run lane_eval on 20 rows of
your own choice the implementer did not evaluate (further down the same row lists, a new tag) and report its exact count
independently. Do not fix anything. Return only defects you demonstrated with evidence, and the exact-row count you confirmed
by reading vf results (final.exact) yourself.`

const ITEMS = [
  { key: 'tailform', file: 'tools/xform/t67_tailform.py', spec: SPEC_TAIL },
  { key: 'samereg2', file: 'tools/xform/t66_sameregmerge.py (the two openings)', spec: SPEC_SAMEREG2 },
]

const results = await pipeline(ITEMS,
  item => agent(`${RULES}\n\nYOUR TASK (implementer): ${item.spec}`,
    { label: `impl:${item.key}`, phase: 'Implement', model: 'opus', effort: 'high' }),
  (report, item) => agent(`${RULES}\n\nYOU ARE THE ADVERSARIAL REVIEWER of ${item.file}, just built by another agent to this spec:\n${item.spec}\n\nThe implementer's report:\n${report}\n\n${REVIEW_CHECKS}`,
    { label: `review:${item.key}`, phase: 'Review', model: 'opus', effort: 'high', schema: VERDICT }).then(v => ({ report, verdict: v })),
  (r, item) => {
    const real = (r.verdict?.defects || []).filter(d => d.severity !== 'minor')
    if (!real.length) return { item: item.key, report: r.report, verdict: r.verdict, fixed: 'no blocking or major defects' }
    return agent(`${RULES}\n\nYou implemented ${item.file} (spec: ${item.spec}).\n\nAn adversarial reviewer demonstrated these defects:\n${JSON.stringify(real, null, 2)}\n\nFix each one (or show with evidence that the reviewer is wrong), rerun the unit tests and the main lane_eval evaluation with a new tag (${item.key}2), and return the updated tables and a per-defect note: fixed / disputed (with evidence).`,
      { label: `fix:${item.key}`, phase: 'Fix', model: 'opus', effort: 'high' }).then(fix => ({ item: item.key, report: r.report, verdict: r.verdict, fixed: fix }))
  })

return results.filter(Boolean)
