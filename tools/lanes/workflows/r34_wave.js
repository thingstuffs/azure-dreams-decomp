export const meta = {
  name: 'r34-wave',
  description: 'Round 34, the targeted wave\'s CPU items from the catalogue\'s bucket a read against the sweep journals: (A) t69_prologue\'s 72 rows where its candidate was produced and missed, composed with a register or ordering lever; (B) the address family - t29_addrsym\'s 31 missed candidates composed with a copy drop, its 16 textual refusals opened with a Detail counter, t54\'s 121 unrecognised rows read for their shape. Two opus implementers in parallel, each adversarially reviewed and fixed; the parent lands and gates.',
  phases: [
    { title: 'Implement', detail: 'two opus implementers: A the t69 composition, B the address family' },
    { title: 'Review', detail: 'one adversarial opus reviewer per item, reruns lane_eval, reads every exact diff' },
    { title: 'Fix', detail: 'the implementer fixes blocking/major defects' },
  ],
}

const RULES = `
Repository: the git checkout that holds tools/common.py (your working directory; run everything from there with python3 -B).
READ FIRST: docs/HANDOVER.md lines 26-120 (the round-33 block: the catalogue, the buckets, and the round-34 plan whose items
2 and 3 are yours); docs/PIN_MECHANISMS_20260912.md "Round 33", "Round 32" (t69's refusal table, T69_DROP_REG, the T69_TWICE
d=2 class one register word from retail, measurement D: the DROP_REG misses are 65 ordering-only - 50 of them
\`-move,sw +move,sw\` at d=4 - 20 colouring-only, 86 both, 55 changed) and "Round 31" (the prologue mechanism: sched1's
adjust_priority / birthing_insn_p; the parameter copies dropped TOGETHER); docs/LANE_KIT.md; tools/lanes/residue.py
(fingerprint(ref, cand): the residue class and shape both sides of round 33 use); tools/xform/screen.py (compile_s / sdiff:
the free cc1 screen against the PINNED listing - ranking only, vf decides); tools/pin_census.py (sites_of, unscored_text,
arm_labels); tools/pin_sites.py (erase_many); tools/lane_eval.py (--lane --module --rows --tag --jobs: the evaluator; its
out/<container>/<file>.c with .base_sha is what the parent lands); tools/tests/test_t69_prologue.py (the test style);
work/native_lane/r32_t69tail/scratch/dropreg_residue.py and rev_residue_check.py (how a candidate's residue was classified
in round 32); tools/lanes/sched_map.py (a residue's moved insns mapped to C statements through -g line notes);
tools/alloc_trace.py (per ASM_REG site, the stock allocator's real reason for the pinned register: ~1 s a site).
THE EVIDENCE: work/native_lane/r33_catalog/rows/match3/per_site.jsonl (every pinned site: fingerprint keys, ranked causes),
rows/match3/bucket_a_split.jsonl (per bucket-a row: the generator and its journal outcomes on the current text), and the
frozen lists in work/native_lane/r34_wave/rows/ (your lane): t69_missed_rows.txt (72 rows: t69_prologue produced candidates
and vf refused every one, "no candidate exact at the recorded cell"), t69_textual_rows.txt (22: "no redundant parameter
copy" 15, "no buildable candidate" 7), wave_addr_rows.txt (152 rows / 1,388 pins whose top cause is addr_literal, i.e.
t29_addrsym / t54: columns id, pins, t29 outcome + reason, t54 outcome + reason at the text as of this morning - the parent
swept t29 / t59 / t54 over all 152 just before this run, so re-read \`sites_of\` on src/ and drop the rows that are now
pin-free; say how many). A catalogue cause is evidence of a compatible MECHANISM, not of the move (the oracle agreed on 45%
of landed rows): treat it as a hypothesis to screen, never as a fact.
HARD RULES: never write under src/, ledger/, config/, build_ovl/, toolchain/; never run sweep.py, gates, pin_search.py,
apply_candidates.py, land_lanes.sh, launch_lane.sh, codex or agy; never run state-changing git (read-only git show/log/diff
is fine). The IO discipline in CLAUDE.md applies: no recursive search over work/ or the repo root; grep only tools/,
include/, docs/, your lane directory and single files under src/<container>/ with --max-filesize 4M. At most 6 concurrent
compiles (lane_eval --jobs 6). No scaffolding may ever appear in a candidate: no new ASM_* macro, __asm__, volatile, fake
dependency, do{}while(0), while(0), for(;0;) or any one-trip block, no new #pragma or attribute, no edit inside ANY
preprocessor arm (#ifdef NON_MATCHING, #ifdef __mips__, #if 0: the mips build compiles one arm and the gate cannot see the
other - compare the non-mips arms of source and output). A candidate must compile at the row's cell; it may never drop or
add a qualifier (volatile/const), change a width, a signedness, an offset or a symbol's identity (naming the symbol at
the same address IS allowed - that is t29's move); a pointer retype only where the generator's existing guard allows it. A
\`register\` keyword may move or go only as an explicit, journalled lever. Only vf accepts a candidate; everything else is
ranking. Every opening is behind an env switch (default OFF unless it paid, then say so), with a journalled note, its
refusals written first and tested; every opening must leave the menu of every row it does not apply to byte-identical
(prove it over 40 pinned rows without the shape). Any generator you add follows the tNN contract (class T: name, eligible,
apply_verified(text, row, census, vf)) so lane_eval and sweep.py can run it. The harness may refuse .md writes: write your
report as <lane>/report_<A|B>.txt and ALSO return its full text. An honest negative with the screen table is a complete
deliverable. LANE: work/native_lane/r34_wave/ (rows/, scratch/, tmp/, evidence/; .ignore hides scratch/, tmp/, *.jsonl).`

const SPEC_A = `YOU ARE IMPLEMENTER A: t69_prologue's 72 MISSED rows composed with a register or ordering lever. YOU OWN
tools/xform/t69_prologue.py, tools/tests/test_t69_prologue.py, and a new module if you build one (tools/xform/t70_*.py +
its test). Implementer B owns t29_addrsym.py / t54 / t59 at the same time: do not edit those.
 1. THE POPULATION, re-measured: for each of the 72 rows (rows/t69_missed_rows.txt) build t69's menu with T69_DROP_REG=1
    (default on) and ALSO with T69_TWICE=1 where its shape exists; screen every candidate with compile_s/sdiff against the
    PINNED listing; take the best (t69's own ranking); classify its residue with residue.fingerprint (cls, band, shape,
    regs). Table: cls x count, the ten commonest L1 keys with a row each. Expect round 32's four classes.
 2. THE LEVERS, cheapest first, each screened on the rows of its class, at most 24 compiles a row, then lane_eval ONLY on
    rows where a composition screens at 0 (or, if none does, the 10 nearest, to test whether the screen's rank and vf
    disagree as they did once in round 32):
    (a) the cheap T69_TWICE variant round 32 asked for: lift \`param-copied-twice\`, enumerate each record ALONE (no subset
        fold) - which rows change class or distance;
    (b) the ORDERING class (\`MOVED\`, the \`-move,sw +move,sw\` d=4 family): map the candidate's residue to C with
        sched_map.py's method (compile both with -g -da, the moved insns' C statements; write your own scratch adapter
        that takes two TEXTS rather than a pin site); then compose the t69 candidate with tools/xform/t51_sched_order's
        candidates(text, focus_line) at that statement (fuse / commute / move), screened;
    (c) the COLOURING class (\`RECOLOURED\` / \`BOTH\`): alloc_trace.py --source <candidate.c> on 10 rows: which allocator
        input differs from retail for the recoloured pseudo (a preference, a conflict, an order); then the text levers that
        touch that input, on the candidate text: t53_reg_state's menu(text, line, var, cls) at the residue's variable,
        t37's width change of the variable, a declaration reorder, the \`register\` keyword moved onto the parameter
        (t69 today never moves it: an explicit lever, journalled) - each screened;
    (d) anything the residues themselves suggest that is not in (a)-(c); say what and why.
 3. THE GENERATOR: whichever lever reaches 0 on two or more rows becomes a composition mode - in t69_prologue behind an
    env switch (T69_COMPOSE=<lever>) or a new tNN module that calls t69's menu then the lever's menu and hands vf the pair
    - with refusals first, tests (the move; two must-refuse cases per lever), and the menu-identity proof (40 pinned rows
    without the shape, switch on vs off). Then lane_eval --lane work/native_lane/r34_wave --module <module> --rows
    rows/t69_missed_rows.txt --tag t69comp1 --jobs 6 with the switch set; report rows / hits / pins, every hit's C diff read
    by you (no width, signedness, qualifier, offset or symbol-identity change; no preprocessor-arm edit; the non-mips arms
    identical).
 4. The 22 textual rows (rows/t69_textual_rows.txt): read what t69 refuses on each (Detail counter) in one table; open
    nothing unless a class of 5+ pins is one rule away - then behind a switch, screened first.
 5. report_A.txt: the population table, every lever's screen table (rows / at 0 / nearest), the lane_eval evidence, the
    diffs, refusal counts, and a recommendation per switch: default on (paid, cheap) / keep closed / remove. Return the
    full report text and the paths.`

const SPEC_B = `YOU ARE IMPLEMENTER B: the address family. YOU OWN tools/xform/t29_addrsym.py, tools/xform/t54_pagebase.py,
tools/xform/t59_offsetsym.py, their tests (create tools/tests/test_t29_addrsym.py if none exists; follow
test_t59_offsetsym.py's style), and a new composition module if you build one. Implementer A owns t69_prologue.py at the
same time: do not edit it (you may CALL natural.dropcopy_candidates, varset's merges, t69's menu read-only).
 0. Re-read the population: for every row in rows/wave_addr_rows.txt, sites_of(src text) now - the parent's t29/t59/t54
    sweep may have landed some (their journals are in ledger/sweeps/, read-only). Report: rows still pinned, pins.
 1. t29's REFUSAL TABLE WITH THE PINS BEHIND IT (round 32's method): add a Detail counter (refusal, variable) to t29's
    refusal chain (\`no pinned address-literal variable\`, \`no rewritable variable: <v> not-operand / port-arm /
    operand-context / no-decl\`, ...), run it over EVERY pinned row of the tree (1,298 rows, text only, seconds), and count
    the ERASABLE pins naming each refused variable. Read the CODE behind the two largest counts before opening anything
    (round 30: the largest class of t66 was a scan stopper, not a parser gap). Open the largest honest classes behind
    switches (T29_<NAME>=1), refusals first, tests, menu identity over 40 rows; screen text-only with compile_s/sdiff
    against the pinned listing (a scratch screen script like r32_family/scratch/dropreg_screen.py); lane_eval on the rows
    at 0.
 2. THE 31 MISSED ROWS (t29 outcome \`refused: no candidate exact ...\`; wave_addr_rows.txt column 3-4): t29's best
    candidate's residue classified with residue.fingerprint; the re-matched census keys on these rows say the residue is an
    address materialisation beside a REGISTER COPY (\`CHANGED|3-4|-move,ori +ori\`, \`-addiu +move,ori\`,
    \`RECOLOURED|3-4|-addiu,lui +addiu,lui\`). Compose t29's candidate with a copy drop - natural.dropcopy_candidates on
    the candidate text, varset merge_local / merge_param, and t69's menu where the copy is a parameter's - each screened; a
    composition that reaches 0 on two or more rows becomes a mode (T29_COMPOSE=<lever>, or a new tNN module with the
    contract), lane_eval with the switch set.
 3. t54's 121 NOOP rows (column 5 = noop): t54 does not recognise the site. Read 15 rows across the pin bands and NAME the
    shape the kept variable has (an integer page literal t54's regex misses; a symbol-address local \`p = (u8 *)&D_X\`; a
    struct view; a page in a parameter; ...) with counts over all 121 (a text-only classifier in scratch/). If one shape
    holds 20+ rows and a t54 / t59 / t29 opening reaches it, build that opening behind a switch and screen it; else the
    table is the deliverable.
 4. report_B.txt: the population after the sweep, t29's refusal table with pins behind each refusal, each opening's screen
    and lane_eval tables, the composition table, t54's shape table, every hit's C diff read by you (no width, signedness,
    qualifier, offset or symbol-identity change; no preprocessor-arm edit; non-mips arms identical), and a recommendation
    per switch. Return the full report text and the paths.`

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

const REVIEW = `Refute it. Read the report and git diff every owned file against HEAD (read-only) so you review exactly what
changed. Run the unit tests (the owned test modules plus tools.tests.test_t69_prologue, test_t59_offsetsym, test_varset,
test_t64_varset). For EVERY exact output in the lane's out/ (evidence/<tag>/), diff the C text by hand against src/: a
width, signedness, qualifier, offset or symbol-identity change; a \`register\` keyword moved without the journal note; an
ERASABLE pin erased that named a different variable; a pin left naming a variable that no longer exists; a copy dropped
whose source is written while the copy is still read; any edit inside an #ifdef arm (compare the NON-mips arms); a
directive line touched - each is BLOCKING. Construct two synthetic must-refuse cases per opening or lever and show what the
tool does with its switch on. Rerun the menu-identity proof on 40 rows of YOUR choice. Rerun lane_eval yourself on each
row list with a new tag (<tag>_r), WITH the switch set, and report the exact counts you read from evidence/<tag>_r/
summary.json independently of the implementer's numbers. Check every screen table's arithmetic on 5 rows by recomputing
compile_s/sdiff. Do not fix anything. Return only defects you demonstrated with evidence, the exact-row count you
confirmed, and a summary.`

const ITEMS = [
  { key: 'A', file: 'tools/xform/t69_prologue.py (+ a composition module) and its tests', spec: SPEC_A },
  { key: 'B', file: 'tools/xform/t29_addrsym.py, t54_pagebase.py, t59_offsetsym.py (+ a composition module) and their tests', spec: SPEC_B },
]

const results = await pipeline(ITEMS,
  item => agent(`${RULES}\n\nYOUR TASK: ${item.spec}`,
    { label: `impl:${item.key}`, phase: 'Implement', model: 'opus', effort: 'high' }),
  (report, item) => agent(`${RULES}\n\nYOU ARE THE ADVERSARIAL REVIEWER of ${item.file}, just changed by another agent to this spec:\n${item.spec}\n\nThe implementer's report:\n${report}\n\n${REVIEW}`,
    { label: `review:${item.key}`, phase: 'Review', model: 'opus', effort: 'high', schema: VERDICT }).then(v => ({ report, verdict: v })),
  (r, item) => {
    const real = (r.verdict?.defects || []).filter(d => d.severity !== 'minor')
    if (!real.length) return { item: item.key, report: r.report, verdict: r.verdict, fixed: 'no blocking or major defects' }
    return agent(`${RULES}\n\nYou implemented ${item.file} (spec: ${item.spec}).\n\nYour report:\n${r.report}\n\nAn adversarial reviewer demonstrated these defects:\n${JSON.stringify(real, null, 2)}\n\nFix each one (or show with evidence that the reviewer is wrong), rerun the unit tests, the menu-identity proof and each lane_eval with a new tag (<tag>2), and return the updated tables and a per-defect note: fixed / disputed (with evidence). Append a "Review fixes" section to your report file and return the full updated report text.`,
      { label: `fix:${item.key}`, phase: 'Fix', model: 'opus', effort: 'high' }).then(fix => ({ item: item.key, report: r.report, verdict: r.verdict, fixed: fix }))
  })

return results.filter(Boolean)
