export const meta = {
  name: 'r31-prologue',
  description: 'Opus reads the PROLOGUE scheduling class (89 pin sites in 65 rows where a body statement\'s instructions exchange order with the $sp adjust or a callee-saved store at sched2 or dbr) in the pass dumps, names the C shape that decides gcc 2.x\'s priority there, and opens t40 or builds t69_prologue for it; implementer -> adversarial reviewer -> fix.',
  phases: [
    { title: 'Implement', detail: 'one opus implementer: mechanism on 20 sites, then the lever, unit tests and lane_eval' },
    { title: 'Review', detail: 'adversarial opus reviewer reruns everything and returns demonstrated defects only' },
    { title: 'Fix', detail: 'implementer fixes blocking/major defects and re-measures' },
  ],
}

const RULES = `
Repository: <repo> (the repository root that holds tools/common.py; run everything from there; python3 from the repo root).
Read first: docs/LANE_KIT.md; docs/PIN_MECHANISMS_20260912.md "Round 31" and "Round 16" (the sched_astra mechanism: gcc 2.x
schedules backward with dynamic priorities, a single-set live producer is promoted, dependence class, then LUID);
tools/xform/t57_keepafterstore.py (the generator contract: class T with name/level/needs_verify, eligible(text,row,census),
apply_verified(text,row,census,vf)); tools/xform/t66_sameregmerge.py (the newest generator in that contract: journaled
refusals in info.skips, env openings, the preprocessor-region map); tools/xform/t40_prologue_param.py and
tools/xform/t36_paramwidth.py (the existing prologue-reorder generator: a parameter's declared width decides where its entry
copy is scheduled; 8 rows paid in round 6 - its width lever is measured out, do not re-sweep it); tools/xform/t51_sched_order.py
and tools/xform/sched_trace.py (compile_text with dumps, instructions(), decisions() = the dynamic ready ranks of the
scheduler trace, diagnose()); tools/phase_census.py (compile_dumps: -da at the row's cell); tools/lanes/sched_map.py (how the
round-31 site lists were made: -g keeps line notes in every dump, so insns map to C lines); tools/xform/screen.py
(compile_s/sdiff); tools/pin_search_engine.py (improves()); tools/pin_census.py (sites_of, unscored_text, asm_blocker,
arm_labels - which labels ONLY NON_MATCHING conditions, so keep your own map of preprocessor regions as t66 does);
tools/pin_sites.py (erase_many); tools/lane_eval.py --help; toolchain/gcc-src/2.7.2/sched.c (priority(), sched_analyze,
schedule_block - the second scheduler runs the same code after reload) and reorg.c (fill_simple_delay_slots,
fill_slots_from_thread).
HARD RULES: never write under src/, ledger/, config/, build_ovl/; never run sweep.py, gates, pin_search.py, apply_candidates.py,
land_lanes.sh, launch_lane.sh, codex or agy; never run state-changing git (read-only git show/log is fine). The IO discipline
in CLAUDE.md applies: no recursive search over work/ or the repo root; grep only tools/, include/, docs/, your lane directory
and toolchain/gcc-src/<one version>/ with --max-filesize 4M (src/ may be searched with rg --max-filesize 4M: it is small).
Write only under tools/xform/, tools/tests/ and your lane directory (given below). At most 8 compiles at a time (lane_eval
--jobs 6). No scaffolding may ever appear in a candidate: no new ASM_* macro, __asm__, volatile, fake dependency,
do{}while(0), while(0), for(;0;) or any one-trip block, no new #pragma or attribute, no edit inside ANY preprocessor arm
(#ifdef NON_MATCHING, #ifdef __mips__, #if 0 ...; the mips build compiles one arm and the gate cannot see the other). A
candidate must compile at the row's cell; it may never drop or add a qualifier (volatile/const), change a width, a
signedness, an offset or a symbol - EXCEPT that a parameter or local width change is this class's known lever (t36/t40) and
is allowed when the candidate keeps every use's value (the reviewer will check each one). Only vf accepts a candidate;
everything else is ranking. Every generator is reviewed by an adversarial agent who found three major defects in every
round-28/29/30 tool: write the refusals first and test them. A demonstrated negative (the class needs a shape C cannot
spell honestly, with the table that shows it) is a complete deliverable; a tool that lands 0 rows is not a failure if its
report says why.`

const SPEC = `YOUR LANE DIRECTORY: work/native_lane/r31_prologue/ (exists: rows/, scratch/, tmp/). YOU OWN tools/xform/t40_prologue_param.py
(if you open it) and a new tools/xform/t69_prologue.py (if you build one), plus their tests under tools/tests/.
THE EVIDENCE (measured this morning; every number is reproducible from rows/):
  rows/prologue_sites.tsv - 89 pin sites in 65 rows (893 pins in those rows): row, site index, macro, deciding pass, pins in
  the row, the pin's line, the kept variable, d0 (listing lines the lone erasure changes), the RTL of the prologue insn that
  exchanged order with the body, the C lines of the insns it crossed, the function's first body line, and the residue lines
  (- pinned = retail, + erased). rows/prologue_rows.txt - the 65 rows, most sites first. rows/body_moves.json - the other
  499 moved sites (the body class) with the same fields, for contrast only: there a single statement move reaches
  distance 0 on 0 of 60 sites and 312 of 402 sites move three or more insns - do NOT work on the body class.
WHAT THE CLASS LOOKS LIKE (read these five in the listing before anything else; compile with tools/xform/screen.py
compile_s and diff pinned vs erased with difflib context 3):
  dungeon/func_80094DE0 site 3 (ASM_KEEP(saved_height) at line 32, sched2): retail has \`andi $4,$4,0x0001\` (the first
    statement's narrowing of parameter $4) AFTER \`sw $22,48($sp); move $22,$7\`; erased, the scheduler lifts the andi above
    that save pair. The pin is 21 lines below the first body line.
  dungeon/func_800AEA34 sites at lines 63 and 65 (ASM_KEEP_NV(entityp) / (contextp), sched2): retail saves $17 and copies
    parameter $5 into it BEFORE the \`sll/sra\` sign extension of parameter $4; erased, the save pair sinks below the sll/sra
    (one site) or the sll/sra rise above the $19 pair (the other). Two keeps, two different interleavings, one function.
  dungeon/func_8009EE78 site 1 (ASM_KEEP(query_kind) line 25, sched2): retail places \`move $6,$0\` (an argument of the first
    call) ABOVE the save pairs \`sw $16; move $16,$2; sw $17; move $17,$5; sw $31\`; erased it sinks to just above the jal.
  dungeon/func_8009F8EC site (ASM_REG copy_call_entity "$4", dbr): retail fills the jal's delay slot with \`sw $10,88($16)\` and
    leaves \`move $4,$16\` above; erased, \`move $4,$16\` moves into the slot / below.
  In every case the pin is NOT at the top of the function (87 of 89 sit nine or more lines below the first body line): it
  holds an ordinary statement, and its asm - a full dependency on the kept variable - lengthens that statement's chain, so
  the second scheduler's priority (the longest path to the end of the block, sched.c priority()) ranks the body
  instruction differently against the prologue's saves and entry copies, which have no dependencies at all except the
  stack adjust. Retail's source produced retail's priorities honestly: something in the retail text made that first
  statement's chain longer or shorter than ours, or made the save/entry-copy pair belong to a different register
  (allocation order decides WHICH callee-saved register a parameter's copy takes, and the saves are emitted in register
  order). t36/t40 found one such lever in round 6 - a parameter's declared WIDTH decides where its entry copy is
  scheduled - and paid 8 rows; the width lever alone is measured out on this population.
TASK, two steps; the first is the deliverable even if the second is empty:
  1. MECHANISM on 20 sites (stratified over sched2/dbr and KEEP/KEEP_NV/SCHED_BARRIER/REG; include the five above). For each:
     the sched2 (or dbr) trace with priorities - sched_trace.compile_text(row, text, dumps=True) and decisions(), or -da
     plus -dS / the scheduler's verbose dump if the cell offers one - for the pinned and the erased text; the dependency the
     pin's asm adds; the priority of the exchanged body insn and of the prologue insn in both; and the C statement the body
     insn belongs to (rows/prologue_sites.tsv names it). Then the question that decides the lever: WHAT IN C, without the pin,
     gives that body insn retail's priority or gives the prologue insn a dependency? Candidates to test on those sites, each
     as a real candidate text screened with compile_s/sdiff against the pinned listing: (a) the parameter's width or
     signedness (t36/t40 - probably already tried; confirm from ledger/sweeps/t40_prologue_param.jsonl and t36); (b) the
     first statement's spelling - a parameter copied into a local before its first use vs used directly (the entry copy's
     register and its save move with it), a local declared with an initialiser vs assigned; (c) the ORDER of the first
     statements / declarations (which parameter is touched first decides which callee-saved register it takes and where its
     save lands - t53_reg_state's decl-swap lever, already in the cascade: confirm what it offers here); (d) the kept
     variable's LIFETIME - a use of the kept value later in the same block (the chain the pin lengthens may be the chain retail
     had because the value was used again), a merge with another variable (t66's move), or its declaration hoisted /
     sunk; (e) for the dbr sites, the statement before the call - what fills the slot is the last independent insn before
     the jal, so the statement order just before the call decides it. Report a table: site x (pass, pin macro, prologue insn
     kind, body statement kind, priority pinned/erased, lever that reaches distance 0 if any, else nearest distance and its
     lever).
  2. If one lever reaches distance 0 on several sites, OPEN it in t40_prologue_param.py behind an env switch (if it is a
     width/parameter lever) or BUILD tools/xform/t69_prologue.py in the t57 contract (name "t69_prologue", level 1,
     needs_verify True; expose prologue_candidates(text) -> [(label, text)] <= 48 for the engine menu) with the refusals
     written first and journaled in info.skips, unit tests for every move and refusal, then EVALUATE with
     tools/lane_eval.py --lane work/native_lane/r31_prologue --module <the module> --jobs 6 on rows/prologue_rows.txt
     (tag prologue1; evaluate the first 45 rows and leave the last 20 for the reviewer). If no lever reaches distance 0 on
     the 20 sites, say so with the table, name what the retail shape must have been if you can, and build nothing.
Report in work/native_lane/r31_prologue/REPORT.md: the mechanism table, the lever, rows exact / pins, every refusal count.
Return: file paths, the test output, the tables verbatim.`

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

const REVIEW_CHECKS = `Refute it. Read the report and any generator in full. Rerun the mechanism measurement on five sites of your own choice from
rows/prologue_sites.tsv that the implementer did not use, and say whether the priority reading holds. If a generator was
built or opened: run its unit tests; for five of its exact outputs on real rows (or its five nearest candidates from the
lane's evidence/ if fewer), diff the C texts by hand - a width or signedness change that alters a use's value (a narrowed
parameter compared or shifted as the wider type, a sign extension lost), a moved statement that crosses a call, a store,
a preprocessor line or a block boundary, a dropped or added qualifier, an initialiser moved past a side effect, or any edit
in an #ifdef arm (compare the NON-mips arms of source and output: the gate cannot see them) is BLOCKING. Construct one
synthetic case per move that MUST be refused and show what the tool does. grep the out/ files for ASM_, volatile, __asm__,
while (0), and count ASM_* per file against the source. Check budget accounting, that eligible() refuses rows with
asm_blocker, that a win restarts on the new text with sites re-read, that skip reasons add up. Re-run lane_eval on the 20
held-out rows (the last 20 of rows/prologue_rows.txt, a new tag) and report its exact count independently. If no generator
was built, verify the negative: take three sites and try to reach distance 0 yourself with any honest C spelling for one
hour; report what you reached. Do not fix anything. Return only defects you demonstrated with evidence, and the exact-row
count you confirmed by reading vf results (final.exact) yourself.`

const ITEMS = [
  { key: 'prologue', file: 'tools/xform/t40_prologue_param.py (opened) or tools/xform/t69_prologue.py (built)', spec: SPEC },
]

const results = await pipeline(ITEMS,
  item => agent(`${RULES}\n\nYOUR TASK (implementer): ${item.spec}`,
    { label: `impl:${item.key}`, phase: 'Implement', model: 'opus', effort: 'high' }),
  (report, item) => agent(`${RULES}\n\nYOU ARE THE ADVERSARIAL REVIEWER of ${item.file}, just produced by another agent to this spec:\n${item.spec}\n\nThe implementer's report:\n${report}\n\n${REVIEW_CHECKS}`,
    { label: `review:${item.key}`, phase: 'Review', model: 'opus', effort: 'high', schema: VERDICT }).then(v => ({ report, verdict: v })),
  (r, item) => {
    const real = (r.verdict?.defects || []).filter(d => d.severity !== 'minor')
    if (!real.length) return { item: item.key, report: r.report, verdict: r.verdict, fixed: 'no blocking or major defects' }
    return agent(`${RULES}\n\nYou implemented ${item.file} (spec: ${item.spec}).\n\nAn adversarial reviewer demonstrated these defects:\n${JSON.stringify(real, null, 2)}\n\nFix each one (or show with evidence that the reviewer is wrong), rerun the unit tests and the main lane_eval evaluation with a new tag (${item.key}2), and return the updated tables and a per-defect note: fixed / disputed (with evidence). Then update the lane's REPORT.md with a "Review fixes" section.`,
      { label: `fix:${item.key}`, phase: 'Fix', model: 'opus', effort: 'high' }).then(fix => ({ item: item.key, report: r.report, verdict: r.verdict, fixed: fix }))
  })

return results.filter(Boolean)
