export const meta = {
  name: 'r30-samereg3-addr',
  description: 'Opus opens t66_sameregmerge\'s remaining refusals (the declaration-run scan stopper, the asm-operand cast, the initialiser placement, the shadowed inner local, and the interference class tried under vf) and reads the address-materialisation residue class (231 near sites) against t54/t59 to open or build the move it needs; each item implementer -> adversarial reviewer -> fix.',
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
contract: its Facts/Flow/pairs_of/candidates_for/build structure, its env openings T66_RENAME_HOST / T66_MACRO_ARGS and how
their refusal counts are journaled in info.skips); tools/xform/natural.py (the declaration scan _Fn/_functions t66 augments);
tools/xform/screen.py (compile_s/sdiff); tools/pin_search_engine.py (improves()); tools/pin_census.py (sites_of,
unscored_text, asm_blocker, arm_labels - which labels ONLY NON_MATCHING conditions, so every generator must keep its own map
of preprocessor regions, as t66 does); tools/pin_sites.py (erase_many); tools/lane_eval.py --help; tools/lanes/erase_census.py
(the lone-erasure census that produced this round's site lists).
HARD RULES: never write under src/, ledger/, config/, build_ovl/; never run sweep.py, gates, pin_search.py, apply_candidates.py,
land_lanes.sh, launch_lane.sh, codex or agy; never run state-changing git (read-only git show/log is fine). The IO discipline
in CLAUDE.md applies: no recursive search over work/ or the repo root; grep only tools/, include/, docs/, your lane directory
and toolchain/gcc-src/<one version>/ with --max-filesize 4M (src/ may be searched with rg --max-filesize 4M: it is small).
Write only under tools/xform/, tools/tests/ and your lane directory (given below); the OTHER item's implementer owns the
files named in its spec - never edit them. At most 8 compiles at a time (lane_eval --jobs 6). Other jobs share the machine
(two codex packs scoring in work/native_lane/probe5 and probe6, the other implementer of this workflow): do not kill, wait
on, or read their directories. No scaffolding may ever appear in a candidate: no new ASM_* macro, __asm__, volatile, fake
dependency, do{}while(0), while(0), for(;0;) or any one-trip block, no new #pragma or attribute, no edit inside ANY
preprocessor arm (#ifdef NON_MATCHING, #ifdef __mips__, #if 0 ...; the mips build compiles one arm and the gate cannot see
the other). A candidate must compile at the row's cell; it may never drop or add a qualifier (volatile/const), change a
width, a signedness, an offset or a symbol. Only vf accepts a candidate; everything else is ranking. Every generator is
reviewed by an adversarial agent who found a blocking defect in every round-27/28/29 tool (a silent volatile drop; edits in
a non-mips arm; an interference edge missing from a liveness test; a substring rename; a macro parameter that is a member
NAME renamed as a value; a per-line macro scan blind to continuation lines): write the refusals first and test them.`

const SPEC_SAMEREG3 = `YOUR LANE DIRECTORY: work/native_lane/r30_samereg3/ (exists: rows/, scratch/, tmp/). YOU OWN
tools/xform/t66_sameregmerge.py and tools/tests/test_t66_sameregmerge.py for this workflow (keep every existing form, opening
and test passing; bump the module docstring's RESULT section).
THE EVIDENCE (measured this evening with the current module over every row of the tree that still carries a same-register
ASM_REG family: 138 rows / 2,148 pins; rows/skips_by_row.json holds pairs_of's first-pass skips per row, rows/cand_skips_by_row.json
the candidates_for-stage skips per row, and rows/<class>_rows.txt lists the rows of each class as "row<TAB>refused pairs<TAB>pins",
most pairs first). Only ONE row still offers a candidate today; the refusal table, pairs / rows / pins in those rows:
  decl-unparsed                792 / 41 / 797   <- the largest, and a SCAN STOPPER, not a parser gap (below)
  interference                 224 / 43 / 899   <- tried under vf this round (opening 5)
  host-name-collision (cand.)  138 /  6 / 170   <- still raised AFTER T66_RENAME_HOST: read why
  init-before-declarations      92 / 10 / 172   <- opening 3
  type-mismatch-narrow          88 / 32 / 433   <- the width rule: NOT an opening, leave it
  address-taken                 77 /  6 / 137
  asm-operand-cast              44 / 14 / 356   <- opening 2
  pp-guarded-mention            33 /  9 / 124   <- policy, leave it
  shadowed-inner-local          32 /  5 / 148   <- opening 4
  loop-backedge                 20 /  4 /  70
  compound-assign-cast          17 /  9 / 220   <- read why; open only if it is a spelling
decl-unparsed, read on the family rows: _augment's looser walk (t66 ~line 905) breaks at the first line that does not end
in ';' or does not match MULTIDECL_RE, and every declaration below that line is then invisible (_decl_of returns None ->
the pin's declaration is dropped from the family and the pairs are charged). The stoppers, counted over the hidden
declarations: (a) an anonymous struct declaration - the line is \`struct {\`, \`volatile struct {\` or \`volatile struct\`
alone, the members follow, then \`} name;\` (80 hidden declarations in 19 rows; e.g. dungeon/func_800969CC,
dungeon/func_819BF9F4, dungeon/func_8180E534); (b) the ONE-LINE computed-goto label table \`static void *const state_labels[] =
{ &&jt_c0, &&jt_c1, ... };\` including the \`__attribute__((used))\` spelling (96 hidden in 11 rows; e.g.
dungeon/func_81008664 - 63 pins, 23 hidden declarations - dungeon/func_81912154, dungeon/func_818FF710, dungeon/func_81820800,
dungeon/func_819835AC, dungeon/func_81838800): ARRAY_OPEN_RE only recognises the multi-line \`= {\` form; (c) a multi-dimensional
array \`s16 vertices[10][6][3];\`, \`void *volatile perspective_out;\` and \`struct { u16 a, b, c; } camera_angles;\` (10 hidden in
6 rows; dungeon/func_80B471EC, dungeon/func_800BFE94, dungeon/func_800A2564).
BUILD five openings behind env switches, each journaled like the existing ones (a skip key per refusal it opens, and a
"<class>-reopened" count so a T66_X=0 run still reports the old table):
  1. T66_DECL_RUN (default 1): the walk steps over the three stopper shapes exactly as it steps over the multi-line label
     table - register the declared NAME(s) for scope resolution (an anonymous struct's variable, the table's name, the
     array's name), never parse them as mergeable declarations - and continues to the next line. Anonymous structs by brace
     depth to the line that closes them; a one-line table by its \`};\`. Nothing else about the run changes.
  2. T66_ASM_OPERAND (default 1): the CAST spelling refuses the whole pair when V is mentioned inside any ASM_* macro
     argument (_cast_edits, "asm-operand-cast"), because \`(u8 *)h\` is not an lvalue for the "=r" output operand. Inside an
     ASM_* argument the operand is the REGISTER and a word is a word on this port, so emit the bare surviving name there
     (\`ASM_KEEP(h)\`, no cast) and cast everywhere else exactly as now. Assert: the pin count is unchanged, every ASM_* call
     keeps its operand count, the ASM_REG binding of a declaration is never rewritten.
  3. T66_INIT_PLACE (default 1): _demote refuses when any later declaration of the run has an initialiser
     ("init-before-declarations"). Open: place the demoted assignment after the LAST declaration of the run unless a crossed
     initialiser mentions V or H, calls anything, or the demoted initialiser mentions the name of any crossed declaration
     (their initialisers run in order and the moved one would then read a value it did not read before). Refuse otherwise.
  4. T66_SHADOW (default 1): "shadowed-inner-local" - a mention of the name resolves to a different (inner-block) declaration.
     Open by renaming that inner local to a fresh name in its own block first (the T66_RENAME_HOST machinery renames a
     variable's uses within a scope already), then the merge as usual. Refuse when the inner local is itself pinned or
     mentioned in a macro argument the classifier calls a NAME slot.
  5. T66_TRY_INTERFERENCE (default 0; the evaluation runs it =1 and the sweep gets the default you recommend): for pairs
     interference() refuses ("interference", not "loop-backedge"), offer the ordinary rename/cast forms anyway and let the
     screen and vf decide. THE ARGUMENT, which the reviewer will judge: both variables are bound to ONE hard register in a
     row that is byte-exact today, so the compiled program never holds both values at once; a clash at the C level is either
     the liveness over-approximating (a kill it does not recognise, a dead arm, a back edge carrying a dead value, a use in
     an arm control never reaches together with the clash) or an m2c artifact (m2c names one temporary per use, e.g.
     event_x_1 ... event_x_8 all on $2 in dungeon/func_812A524C, and a later temporary's "read" takes the earlier one's value
     through the shared register), in which case the merged text is the more honest C. Acceptance is vf's byte verdict, as for
     every form. Journal per pair whether the clash is "nested" (one lifetime inside the other) or "overlap"; report the rate
     for each and recommend the default from it.
Also read WHY "host-name-collision" is still charged at the candidate stage after T66_RENAME_HOST on rows/hostcoll_rows.txt
(6 rows: is the fresh name \`<host>_m\` itself colliding, is the rename refused, or is it the hoist target?) and why
"compound-assign-cast" refuses (17 pairs; the cast spelling of \`v += e\` where v is read inside a larger expression?); open
either only if it is a spelling, under T66_HOST_FRESH / T66_COMPOUND (default 1), journaled the same way.
Unit tests for every opening and its refusals in tools/tests/test_t66_sameregmerge.py (a one-line label table followed by a
mergeable pair; an anonymous struct; a NAME-slot inner local; an ASM_KEEP of V under the cast spelling with the pin count
asserted; a crossed initialiser that mentions H; an interference pair that vf refuses - use a fake vf).
EVALUATE with tools/lane_eval.py --lane work/native_lane/r30_samereg3 --module tools/xform/t66_sameregmerge.py --jobs 6:
tag t66v3_decl on rows/hidden_rows.txt (41 rows); tag t66v3_forms on the union of rows/asmcast_rows.txt, rows/initdecl_rows.txt,
rows/shadow_rows.txt, rows/hostcoll_rows.txt, rows/compound_rows.txt; tag t66v3_interf on rows/interference_rows.txt (43 rows)
with T66_TRY_INTERFERENCE=1. Then a REGRESSION check: with every new opening OFF, rerun 20 rows of
work/native_lane/r29_samereg2/rows/ that the round-29 pack evaluated (tag t66v3_regress) and confirm the candidates offered
are byte-identical to the round-29 run's (its evidence/ json records candidates_n and steps).
Report in work/native_lane/r30_samereg3/REPORT.md: per opening, pairs newly offered / screened / exact / pins; the refusal
table before and after over the 138 family rows (the census script is three lines with pairs_of + candidates_for; put it in
scratch/); the interference rate nested vs overlap and the recommended default; every exact output (row, pins before/after,
form, pair). Return: file paths, the test output, the tables verbatim, every skip-reason count.`

const SPEC_ADDR = `YOUR LANE DIRECTORY: work/native_lane/r30_addr/ (exists: rows/, scratch/, tmp/). YOU OWN tools/xform/t54_pagebase.py,
tools/xform/t59_offsetsym.py, and a new tools/xform/t68_addrform.py if you build one (plus their tests under tools/tests/).
THE EVIDENCE: tools/lanes/erase_census.py erased every one of the tree's 6,480 live pin sites alone and screened the result
against the pinned cc1 listing (rows/near_residues.json: the 2,161 sites within 4 listing lines, each with its residue lines,
"-" the pinned = retail listing, "+" the erased one). 46% of those residues are one instruction MOVED (the scheduling class,
t51's), 21% the same instructions RECOLOURED (the allocator class, measured out at the C level in rounds 26-28), and 31%
change an operation. The largest specific pattern in the last group is the ADDRESS MATERIALISATION class, rows/addr_sites.tsv:
231 sites in 143 rows (row, line, macro, kept variable, d0, pattern, residue), 112 of them \`lui+addiu -> lui+ori\` (retail
materialises an address as %hi/%lo carry-adjusted halves - a SYMBOL - and the erased text as an integer constant), 73
\`addiu -> ori\` (a kept page plus an offset: erased, combine knows the page's low bits are zero and adds with IOR), 22
\`addiu -> move+ori\`, 15 \`addiu -> lui+ori\`. Example: dungeon/func_819A1654 line 195, ASM_KEEP(copy_page):
\`-addiu $6,$2,16468 | +move $6,$2 | +ori $6,$6,0x4054\`. This is the pinned-integer-page family (docs/PIN_MECHANISMS_20260912.md
rounds 5-7 and 18: a symbol is a relocatable object address, a different compiler value from the integer page) and the
generators that serve it - t54_pagebase (the page's own definition written as the symbol), t59_offsetsym (one use written as
the symbol at that address), t29_addrsym, t33_argconst - have all been swept over the tree: these 231 sites are their RESIDUE.
TASK, in two steps, the first is the deliverable even if the second is empty:
  1. MEASURE. (a) For each of the 231 sites, what t54 and t59 offer or refuse on the row today (run their eligible() and
     candidate machinery; if they do not journal refusal reasons, add a skips Counter to them - that edit is allowed - or
     build the table with a script in scratch/); (b) the C shape of the kept value, classified: a page literal
     \`(u8 *)0x80120000\`, a symbol plus an offset, a base loaded from memory or returned by a call, a parameter, an integer
     arithmetic result; (c) on 20 sites, which pass makes the fold (compile with -da at the row's cell via
     tools/xform/reg_state.py or screen.py's cc1 invocation and read the .cse / .combine / .final dumps): cse's fold_rtx,
     combine's plus->ior, or final's address splitting; (d) whether the address the retail listing names has a symbol in the
     tree (include/*.h, include/records/*.h, the row's own NON_MATCHING arm) or not. Table: class x (t54 verdict, t59 verdict,
     pass, symbol known) with site counts.
  2. OPEN or BUILD. If the largest class is a spelling refusal of t54 or t59, open it in that module behind an env switch
     (default 1, journaled). If the class needs a move neither has - e.g. the kept page's use rewritten as \`&SYMBOL\` where
     the symbol is declared, an offset folded into the symbol name the tree already declares, a page value taken from a
     variable that gcc cannot fold (a parameter or a load) rather than a literal, a use respelled so combine cannot prove the
     low bits - build tools/xform/t68_addrform.py in the t57 contract (name "t68_addrform", level 1, needs_verify True; expose
     addrform_candidates(text) -> [(label, text)] <= 48 for the engine menu) with the refusals written first. Every candidate:
     no new symbol the tree does not declare, no integer written where the row had a symbol, no cast that changes a width,
     nothing in a preprocessor arm. If the measurement shows the class is unservable in C (the address has no symbol anywhere
     and inventing one is a config change, or the fold happens in a pass no source spelling reaches), report that with the
     table and build nothing: a demonstrated negative closes the class.
Unit tests for whatever you open or build. EVALUATE with tools/lane_eval.py --lane work/native_lane/r30_addr --module <the
module> --jobs 6 on rows/addr_rows.txt (143 rows, most sites first; tag addr1; the reviewer will hold out 20 of your own
choice, so evaluate the first 100 and leave the rest). Report in work/native_lane/r30_addr/REPORT.md: the measurement table,
the opening/move built, rows exact / pins, and every refusal count. Return: file paths, the test output, the tables verbatim.`

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
nearest candidates from the lane's evidence/ if fewer), diff the C texts by hand: a rename that captured a struct member, a
macro argument in a NAME slot, a label or an inner-scope local, a declaration parsed out of an anonymous struct's members, a
demoted initialiser that now reads a value it did not read before, an ASM_* operand whose count or binding changed, a merged
pair whose values are BOTH read after the clash in one path (for the interference opening: find a path on which the erased
variable's old value was needed - if vf accepted it, explain why the bytes agree, and mark it blocking only if the bytes
cannot agree for the reason you give), a dropped or added qualifier, an integer written where the row had a symbol, or any
edit in an #ifdef arm (compare the NON-mips arms of source and output: the gate cannot see them) is BLOCKING. Construct one
synthetic case per opening that MUST be refused and show what the tool does. grep the out/ files for ASM_, volatile, __asm__,
while (0), and count ASM_* per file against the source. Check budget accounting, that eligible() refuses rows with
asm_blocker, that a win restarts on the new text with sites re-read, that skip reasons add up, and that with every new
opening switched OFF the candidates offered on 20 round-29 rows are byte-identical to the round-29 evidence. Re-run lane_eval
on 20 rows of your own choice the implementer did not evaluate (further down the same row lists, a new tag) and report its
exact count independently. Do not fix anything. Return only defects you demonstrated with evidence, and the exact-row count
you confirmed by reading vf results (final.exact) yourself.`

const ITEMS = [
  { key: 'samereg3', file: 'tools/xform/t66_sameregmerge.py (five openings)', spec: SPEC_SAMEREG3 },
  { key: 'addr', file: 'tools/xform/t54_pagebase.py / t59_offsetsym.py / t68_addrform.py (the address-materialisation class)', spec: SPEC_ADDR },
]

const results = await pipeline(ITEMS,
  item => agent(`${RULES}\n\nYOUR TASK (implementer): ${item.spec}`,
    { label: `impl:${item.key}`, phase: 'Implement', model: 'opus', effort: 'high' }),
  (report, item) => agent(`${RULES}\n\nYOU ARE THE ADVERSARIAL REVIEWER of ${item.file}, just built by another agent to this spec:\n${item.spec}\n\nThe implementer's report:\n${report}\n\n${REVIEW_CHECKS}`,
    { label: `review:${item.key}`, phase: 'Review', model: 'opus', effort: 'high', schema: VERDICT }).then(v => ({ report, verdict: v })),
  (r, item) => {
    const real = (r.verdict?.defects || []).filter(d => d.severity !== 'minor')
    if (!real.length) return { item: item.key, report: r.report, verdict: r.verdict, fixed: 'no blocking or major defects' }
    return agent(`${RULES}\n\nYou implemented ${item.file} (spec: ${item.spec}).\n\nAn adversarial reviewer demonstrated these defects:\n${JSON.stringify(real, null, 2)}\n\nFix each one (or show with evidence that the reviewer is wrong), rerun the unit tests and the main lane_eval evaluation with a new tag (${item.key}2), and return the updated tables and a per-defect note: fixed / disputed (with evidence). Then update the lane's REPORT.md with a "Review fixes" section.`,
      { label: `fix:${item.key}`, phase: 'Fix', model: 'opus', effort: 'high' }).then(fix => ({ item: item.key, report: r.report, verdict: r.verdict, fixed: fix }))
  })

return results.filter(Boolean)
