export const meta = {
  name: 'r33b-widen',
  description: 'Round 33 step 1c: widen the perturbation catalogue where the text oracle and the coverage tables say the kinds are narrow (the goto-loop terminator, the redundant-copy and initialised-alias shapes, the address/page family, the statement shift, the common-tail hoist, the condition temporary, merge over initialised declarations), fix the cause table, split bucket a by the sweep journal; two opus implementers in parallel, each adversarially reviewed and fixed, then one opus runner re-catalogues the whole population, re-runs the oracle and re-reads the gate.',
  phases: [
    { title: 'Implement', detail: 'two opus implementers in parallel: C the text-level kinds + driver, D the structural kinds + varset switch' },
    { title: 'Review', detail: 'one adversarial opus reviewer per item' },
    { title: 'Fix', detail: 'the implementer fixes blocking/major defects' },
    { title: 'Run', detail: 'one opus runner: whole-population catalogue, match, oracle, control, report' },
  ],
}

const RULES = `
Repository: the git checkout that holds tools/common.py (your working directory; run everything from there with python3 -B).
READ FIRST, in this order: work/native_lane/r33_catalog/report_oracle.txt (sections 3, 4, 6: the text oracle over 152 rows a
generator landed - 47 exact, 105 not; the missing shapes NAMED with counts and the rows behind each; the build list),
rows/oracle_missing_shapes.txt (every shape with two examples: the m2c target's lines against the landed text's),
rows/oracle_table.txt (per generator; the reversing kind enumerates NOTHING on 48 of 152 rows - each refusal listed),
report_run.txt sections 4, 6 and 9 (coverage 11.6% at L1 / 16.0% whole population; beyond d=4 the key cannot cover the
catalogue's own other half; in the near band 1,364 of 2,062 sites uncovered, 34% address materialisation, 25% width/sign;
the recommendation), rows/near_uncovered.txt, rows/single_refusals.txt (each kind's refusal counters over 1,000 rows),
report_impl_A.txt and report_impl_B.txt (what each module does today and its authors' widening notes), and the code:
tools/lanes/residue.py, tools/lanes/perturb_basic.py, tools/lanes/perturb_struct.py, tools/lanes/perturb_catalog.py,
tools/tests/test_perturb_basic.py, test_perturb_struct.py, test_residue.py (310 lines of tests; the style), tools/xform/varset.py
(merge_local_candidates, usable_locals(allow_init)), tools/xform/t15_shapes.py (dup_after_if), tools/xform/t51_sched_order.py
(units, access, independent), tools/lanes/reach.py (skeleton, dist), work/native_lane/r33_catalog/scratch/oracle.py (the
text oracle: \`python3 -B work/native_lane/r33_catalog/scratch/oracle.py --help\` or read its main; it enumerates every kind
on the LANDED text of each generator row and reports exact hits against the pre-landing text minus its pins).
THE CONTRACT (unchanged): PERTURBATIONS = [(kind, fn)]; fn(text, detail=None) -> [(params, new_text)]; params carries
"site" and "label"; deterministic; never a directive line touched; never an ASM_* macro, __asm__, volatile, a fake
dependency, a one-trip block, #pragma or attribute added; a move means what it says (a swap of two statements is a swap of
two INDEPENDENT statements; a hoist never moves a memory read across a call or a store); __typeof__(expr) may spell a
temp's type. THE DIRECTION: every kind is a generator's move REVERSED, toward the m2c form; the '-' side of every listing
diff is retail. A kind that enumerates nothing on the rows its own generator landed is broken for that generator: the text
oracle is the acceptance test - run it on your kinds' generator rows before and after, and report exact hits before/after.
HARD RULES: never write under src/, ledger/, config/, build_ovl/, toolchain/; never run sweep.py, gates, pin_search.py,
apply_candidates.py, land_lanes.sh, launch_lane.sh, lane_eval.py, codex or agy; never run state-changing git (read-only git
show/log/diff is fine). IO discipline (CLAUDE.md): no recursive search over work/ or the repo root; grep only tools/,
include/, docs/, your lane directory and single files under src/<container>/, with --max-filesize 4M. At most 6 concurrent
compiles while other agents run. The harness may refuse .md writes: write your report as a .txt in the lane and return its
full text. Do not modify work/native_lane/r33_catalog/scratch/oracle.py: copy it to scratch/oracle_<C|D>.py if you need a
change, and say what you changed. An honest negative, measured, is a complete deliverable.
LANE: work/native_lane/r33_catalog/ (rows/, scratch/, tmp/, evidence/; .ignore hides scratch/, tmp/, *.jsonl);
bulk JSONL under scratch/ or work/perturb_catalog/.`

const SPEC_C = `YOU ARE IMPLEMENTER C. YOU OWN tools/lanes/perturb_basic.py, tools/lanes/perturb_catalog.py, tools/lanes/residue.py,
tools/tests/test_perturb_basic.py, tools/tests/test_residue.py. Implementer D owns perturb_struct.py and varset.py at the
same time: do not edit or wait for those. Existing tests must keep passing. Report file: report_impl_C.txt.
 1. local_alias WIDENED to the redundant-copy shapes the oracle found on 48 rows (EXTRA_LOCAL_IN_M2C / EXTRA_LOCAL_IS_A_COPY /
    ALIAS_WRITTEN_IN_RUN / ALIAS_READ_ONCE / ALIAS_BLOCK_REFUSED / TYPED_ALIAS_INIT_DECL), each behind its own refusal->opening
    with a test: (a) a copy read ONCE (the run is one statement); (b) the source written inside the run - the alias covers the
    reads UP TO that write only (the alias is a snapshot of the value before the write; both texts compute the same values);
    (c) a declaration block the current parser calls not simple (say what the parser refused and open the honest cases);
    (d) the INITIALISED typed alias: \`T *alias = source;\` as a declaration with an initialiser at the top of the block, T the
    source's declared type or - when the source is a pointer - void * (m2c's untyped alias) and, for the void * form, every
    use of the alias that needs the type cast back ((T *)alias)->f; the casts are the retype_void spelling, so this variant
    is only allowed where every use is a bare value or a member access you can spell. Measure each opening with the text
    oracle on the t20_fencefree / t64_varset / t53_reg_state rows it names (rows/oracle_rows.txt gives the generator per
    row): exact hits before and after, per opening. On a landed row the alias's NAME does not matter (the oracle
    alpha-renames locals).
 2. stmt_shift, a new kind beside adjacent_swap: one simple statement moved k = 2..6 positions up or down within its block,
    every statement it crosses independent of it under t51's tests AND the alias test adjacent_swap now applies; refuse
    crossing a control line, a declaration, a label, a call. Params: k and the direction. Then read the 6 t51 rows the oracle
    tagged SWAP_REFUSED_CONTROL_OR_DECL (rows/oracle_missing_shapes.txt) and say per row which refusal stands and whether a
    meaning-preserving widening exists; build it only if it does.
 3. THE ADDRESS / PAGE FAMILY, built for the census number (469 uncovered near-band pins carry an address-materialisation
    shape: \`CHANGED|3-4|-addiu,lui +lui,ori\` 107 pins / 80 rows, \`CHANGED|1-2|-addiu +ori\` 70 / 50, and the rest in
    rows/near_uncovered.txt), not only for the 11 oracle rows:
    (a) addr_literal, a new kind (t29_addrsym's move reversed, and t54's producer spelling): a D_8XXXXXXX symbol reference
        written as its integer address - a value use \`D_X\` -> \`(*(__typeof__(D_X) *)0xADDR)\`, an address use \`&D_X\` or an
        array/function decay -> \`((__typeof__(&D_X))0xADDR)\` - one instance per symbol (all its uses), plus one instance per
        function with EVERY symbol of one page rewritten. Read three t29 and three t54 exemplar diffs first
        (work/native_lane/r28_dev/ex/KEEP/INDEX.md names them; the .diff files sit beside it) and make the kind produce
        exactly the pre-landing spelling of those rows; the oracle on the t54_pagebase rows is the acceptance test.
    (b) page_local's refusals opened: \`symbol-used-as-array-or-function\` (1,412 of 2,798 refusals) spelled explicitly -
        an array symbol through \`(*(__typeof__(D_X) *)(page + off))[i]\`, a function symbol refused; \`address-of-symbol\`
        (468) as \`(page + off)\`; the \`page\` name check per function; a SIGNED page base with subtraction where the m2c
        text has it (\`0x80100000 - 0x1AE0\`, \`page - 0x34C\`: the base is the NEXT 64 KiB boundary and offsets are negative)
        as a second instance per page.
    Report per kind the whole-population instances, the visible share, and the near-band d distribution; and, decisive:
    the share of the 469 address-shape census pins whose L1 key the new kinds now reach five or more times (compute it with
    perturb_catalog.py match on your own run against scratch/census_fp.jsonl).
 4. perturb_catalog.py: (a) KIND_GENERATOR corrected - merge/split name t51_sched_order beside t64 (t51's own split lever),
    tail_merge -> t15_shapes.dup_after_if / t61_naturalkeep, cond_temp -> varset.inline_def / t64, addr_literal ->
    t29_addrsym / t54, stmt_shift -> t51, and the new local_alias openings -> natural.dropcopy / t20 / t61; (b) BUCKET a
    SPLIT BY THE SWEEP JOURNAL: read one ledger/sweeps/*.jsonl file first (fields: id, transform, in_sha, outcome, ...; the
    outcomes that exist); index all journals once (1 s, 127 MB); for every bucket-a row and its top cause's generator(s),
    look up records for that row whose in_sha is sha256 of the row's CURRENT src text: a_missed = the generator ran on this
    very text and did not apply (report its outcome), a_unseen = no record on the current text (the generator never ran here,
    or ran on an older text), a_applied = an applied record on the current text (it changed the row and pins remain). Print
    rows and pins per sub-bucket, per generator. Confirm on the key \`MOVED|3-4|-move,sw +move,sw\` (109 pins) that most
    rows are a_missed for t69_prologue (the parent measured 87 of 109 sites in the DROP_REG-miss rows). (c) match prints,
    per KIND_GENERATOR generator, the share of pinned rows on which the kind enumerates at least one instance (the
    zero-instance rate the oracle asked for beside every coverage number).
 5. residue.py: one more key, L1f = cls|band|the SET of register families that appear in the recolour pairs (sorted, joined),
    for the far-band experiment; match reports coverage at L1f beside L1 per band, and the negative-control script the runner
    has (scratch/control.py) will judge it - do not claim anything about the far band yourself. Tests for the new key.
 6. Tests for every opening and kind (the move; two must-refuse cases each); the whole-population run of perturb_basic
    (perturb_catalog.py run rows/population_rows.txt work/perturb_catalog/basic_C.jsonl --procs 6 --per-kind 3 --per-row
    14 --kinds <your kinds>; ~2 min) with summary; the text oracle before/after on your kinds' generator rows; 6 instances per
    new kind or opening written to tmp/ and their C diffs read by you. report_impl_C.txt: every file, the tests, the tables,
    the oracle before/after, the address-class share, the bucket split. Return the full report text and the paths.`

const SPEC_D = `YOU ARE IMPLEMENTER D. YOU OWN tools/lanes/perturb_struct.py, tools/tests/test_perturb_struct.py, and ONE parameter in
tools/xform/varset.py (item 3). Implementer C owns perturb_basic.py / perturb_catalog.py / residue.py at the same time: do not
edit or wait for those. Existing tests must keep passing (tools.tests.test_varset, test_t64_varset, test_t69_prologue: 146).
Report file: report_impl_D.txt.
 1. goto_to_loop ACCEPTS t41's OWN LANDED SPELLING (14 oracle rows, the only class the oracle proved is the WHOLE residue on
    11: report_oracle.txt section 4 item 1 and check V5): (a) a terminator that shares its line with the closing brace -
    \`} if (COND) goto L;\` - split and accepted; (b) \`body-declares\` relaxed when the label carries its own brace (\`L: {\`):
    the body is already a block, so \`do { ... } while (COND);\` changes no declaration's scope; (c) read the other 3
    LOOP_ONELINE rows and the 2 t44 \`goto-from-outside\` rows and say what stands. Acceptance: the oracle on the
    t41_gotoloop / t41c / t44 rows (rows/oracle_rows.txt) - exact hits before (0 of 15) and after (the oracle predicted 11).
 2. cond_temp, a new kind (CONDITION_TEMPORARY, 10 rows): an \`if\` condition, or one side-effect-free operand of an \`if\`
    condition, computed into a temporary first - \`__typeof__(EXPR) t; ... t = EXPR; if (t)\` - with hoist's refusals
    (no call, no ++/--/=, no memory read moved across a call or a store between the temp's assignment and the if: the
    assignment goes immediately before the if). Not for while/for conditions (they are re-evaluated; say so in the refusal).
 3. merge over an INITIALISED declaration: varset.merge_local_candidates / merge_param_candidates gain a keyword parameter
    (allow_init=False, the default UNCHANGED) that passes allow_init through to usable_locals; the wrapper in perturb_struct
    calls with allow_init=True. Prove the default unchanged: varset.candidates(text) and t64's menu byte-identical with and
    without your edit over 40 pinned rows (git show HEAD:tools/xform/varset.py as scratch/varset_head.py; compare the label
    and text lists), and the 146 existing tests. Then read merge's live-ranges-overlap / address-taken refusals on the nine
    EXTRA_LOCAL_IN_THE_LANDED_TEXT rows (report_oracle check V7) and say which are honest refusals.
 4. tail_merge, a new kind (DUP_TAIL_BOTH_ARMS_LANDED 8 rows + DUP_TAIL_BEFORE_GOTO_LANDED 2): the inverse of
    t15_shapes.dup_after_if - when both arms of an if/else end with the same statement(s) (token-identical after the arms'
    own indentation), those statements are hoisted out to follow the if once; refuse when either arm ends in a jump
    (return / goto / break / continue) before the common tail, when the tail reads a variable the arms assign differently
    only if that changes meaning (it does not: the tail runs after either arm in both texts - say so in a comment), and when
    the if has no else. And dup_after_if itself (t15_shapes' own function) wrapped as kind dup_tail for the target direction
    (2 rows) with its refusals carried. Acceptance: the oracle on the t61_naturalkeep rows (6) and the t53 rows the shape
    tagged.
 5. retype_void's OFFSET-LOAD spelling (your own widening 2, report_impl_B.txt section 9): \`*(s32 *)((u8 *)p + 0x10)\` for
    \`((S *)p)->unk_10\` where the member's offset and width are readable from the row's own typedef (the padding fields);
    one instance per pointer, all its member uses; refuse when any use's offset cannot be read. Say what share of
    retype_void's population it reaches and its visible share on the whole population (retype_void today: 0 visible in 632).
 6. Tests for every opening and kind (the move; two must-refuse cases each); the whole-population run of perturb_struct
    (perturb_catalog.py run rows/population_rows.txt work/perturb_catalog/struct_D.jsonl --procs 6 --per-kind 3 --per-row
    14 --kinds <your kinds>; ~2 min) with summary; the oracle before/after on your kinds' generator rows; 6 instances per new
    kind or opening written to tmp/ and their C diffs read by you. report_impl_D.txt: every file, the tests, the varset
    identity proof, the tables, the oracle before/after. Return the full report text and the paths.`

const VERDICT = {
  type: 'object',
  properties: {
    defects: { type: 'array', items: { type: 'object', properties: {
      severity: { type: 'string', enum: ['blocking', 'major', 'minor'] },
      where: { type: 'string' }, what: { type: 'string' }, evidence: { type: 'string' } },
      required: ['severity', 'where', 'what', 'evidence'] } },
    kinds_confirmed: { type: 'array', items: { type: 'string' } },
    summary: { type: 'string' },
  },
  required: ['defects', 'kinds_confirmed', 'summary'],
}

const REVIEW_C = `Refute it. Read the report and git diff every owned file against HEAD (read-only). Run the unit tests (all of
tools.tests.test_residue test_perturb_basic test_perturb_struct, and test_varset test_t64_varset test_t69_prologue). Then,
independently: (1) for EVERY new kind and opening, write 5 instances' original and perturbed texts to tmp/ and read the C
diffs: an alias covering a read AFTER the source's write, an alias whose declared type is not the source's (other than the
allowed void * form), a cast missing at a use of a void * alias, a shift that crosses a dependent statement / a call / a
control line / a declaration, an addr_literal whose literal is not the symbol's address or that rewrites a symbol inside its
own extern declaration, a page rewrite with the wrong offset sign, a directive line touched - each BLOCKING; (2) the oracle
before/after numbers: rerun scratch/oracle.py (unchanged) on the rows the report names and compare - a claimed exact hit
that is not, MAJOR; (3) the bucket split: recompute a_missed / a_unseen / a_applied for 10 rows by hand from the journals
and the current file's sha256 - a wrong sub-bucket is MAJOR; (4) the address-class share: recompute it from the run's
JSONL and scratch/census_fp.jsonl - a wrong share is MAJOR; (5) determinism on 20 rows for every new kind; (6) the L1f key
nests under L0 and is tested. Do not fix anything. Return only defects you demonstrated with evidence, the kinds you
confirmed produce the named move, and a summary.`

const REVIEW_D = `Refute it. Read the report and git diff every owned file against HEAD (read-only) - varset.py's diff must be ONE
keyword parameter threaded through, nothing else. Run the unit tests (all of tools.tests.test_residue test_perturb_basic
test_perturb_struct test_varset test_t64_varset test_t69_prologue). Then, independently: (1) rerun the varset identity proof
on 40 pinned rows of YOUR choice (HEAD's varset vs the new one, default arguments): any difference in varset.candidates or
t64's menu is BLOCKING; (2) for EVERY new kind and opening, write 5 instances' original and perturbed texts to tmp/ and read
the C diffs: a goto loop rewritten where the label has a second goto or a forward goto, or where a declaration's scope
changes; a condition temporary that moves a memory read across a call or a store, or is hoisted out of a while/for; a tail
merged out of arms whose tails differ by a token, or where an arm jumps before the tail, or where the if has no else; a
merge under allow_init that merges an initialised local whose initialiser has a side effect or that changes evaluation
order; an offset load with the wrong offset or width; a directive line touched - each BLOCKING; (3) the oracle before/after
numbers: rerun scratch/oracle.py (unchanged) on the t41/t41c/t44/t61 rows and compare - a claimed exact hit that is not,
MAJOR; (4) determinism on 20 rows for every new kind; (5) run each new fn on a text with an ASM_KEEP and on one with an
#ifdef inside the body: both must refuse. Do not fix anything. Return only defects you demonstrated with evidence, the
kinds you confirmed produce the named move, and a summary.`

const RUN_SPEC = `YOU ARE THE RUNNER. Both items are written, reviewed and fixed (reports below). You own nothing under tools/; you
write only under work/native_lane/r33_catalog/ and work/perturb_catalog/; Pool(8) / --procs 8 (you run alone). In order,
with wall times (rows/timings2.txt):
 1. python3 -B -m unittest over all six test modules - must pass. \`git status --short\` - list what changed under tools/.
 2. The census: scratch/census_fp.jsonl was made on this tree at HEAD; the tree under src/ has not changed (check: git
    status shows nothing under src/). Re-run erase_census.py --fp into scratch/census_fp2.jsonl anyway (25 s) and confirm the
    sorted files are identical; use census_fp2.
 3. The whole-population single catalogue with ALL kinds: perturb_catalog.py run rows/population_rows.txt
    work/perturb_catalog/single_all2.jsonl --procs 8 --per-kind 3 --per-row 16; summary -> rows/single_all2_summary.txt (per
    kind: instances, nobuild, INVISIBLE share, class and d distributions; compare with rows/single_summary.txt's kinds).
 4. The two-move catalogue on the 1,000 sample rows: run ... --two-move -> work/perturb_catalog/pairs_1000_2.jsonl;
    summary -> rows/pairs_1000_2_summary.txt.
 5. The match: perturb_catalog.py match --census scratch/census_fp2.jsonl --catalog single_all2.jsonl --catalog2
    pairs_1000_2.jsonl --out rows/match2/ --min 5. Read every table. Report coverage at L0 / L1 / L1f / L2 overall, by band,
    by pin band, by family; the top causes at L1; the top 30 uncovered L1 keys with pins and families; the near-band uncovered
    by shape family (as rows/near_uncovered.txt did) and specifically the address-materialisation share now; the bucket table
    WITH the a_missed / a_unseen / a_applied split per generator; the zero-instance rate per generator.
 6. THE TEXT ORACLE, re-run: copy scratch/oracle.py to scratch/oracle2.py and make its skeleton alpha-rename PARAMETERS as
    well as locals (report_oracle.txt section 4, "three changes to the method", first item; keep everything else); run it
    over the same 152 rows; rows/oracle2_table.txt beside rows/oracle_table.txt: exact hits before (47) and after, per
    generator, and the zero-instance rows before (48) and after; the remaining missing shapes with counts.
 7. The negative control, scratch/control.py adapted to single_all2 and to L1f: self-coverage vs census coverage per band at
    L1 and at L1f; apply the pass rule per band: L1f is USABLE in a band only where self-coverage >= 50% and census coverage
    is clearly below it; where it passes nowhere beyond d=8 say so and stop - the far band is bucket c by definition.
 8. --phase on the near band of single_all2 if steps 1-7 took under 2 hours.
 9. report_run2.txt: every table; the gate re-read at L1 by band and pin band, against report_run.txt's numbers; which
    kinds explain the most census mass now; what the oracle says about the kinds' reach now; the bucket table with its
    split, and a recommendation for STEP 2 (the match into three buckets and the targeted wave): which a_missed classes are
    composition targets (name the generator and the residue), which a_unseen classes are refusal tables to open, how many
    rows and pins are bucket c / weak at L1 after this widening, and whether a further widening round is worth it (with the
    number). Return the full report text and every table path.`

const ITEMS = [
  { key: 'C', file: 'tools/lanes/perturb_basic.py, perturb_catalog.py, residue.py', spec: SPEC_C, review: REVIEW_C },
  { key: 'D', file: 'tools/lanes/perturb_struct.py, one parameter in tools/xform/varset.py', spec: SPEC_D, review: REVIEW_D },
]

const results = await pipeline(ITEMS,
  item => agent(`${RULES}\n\nYOUR TASK: ${item.spec}`,
    { label: `impl:${item.key}`, phase: 'Implement', model: 'opus', effort: 'high' }),
  (report, item) => agent(`${RULES}\n\nYOU ARE THE ADVERSARIAL REVIEWER of ${item.file}, just changed by another agent to this spec:\n${item.spec}\n\nThe implementer's report:\n${report}\n\n${item.review}`,
    { label: `review:${item.key}`, phase: 'Review', model: 'opus', effort: 'high', schema: VERDICT }).then(v => ({ report, verdict: v })),
  (r, item) => {
    const real = (r.verdict?.defects || []).filter(d => d.severity !== 'minor')
    if (!real.length) return { item: item.key, report: r.report, verdict: r.verdict, fixed: 'no blocking or major defects' }
    return agent(`${RULES}\n\nYou implemented ${item.file} (spec: ${item.spec}).\n\nYour report:\n${r.report}\n\nAn adversarial reviewer demonstrated these defects:\n${JSON.stringify(real, null, 2)}\n\nFix each one (or show with evidence that the reviewer is wrong), rerun the unit tests, your whole-population run and the oracle before/after, and return a per-defect note: fixed / disputed (with evidence). Append a "Review fixes" section to your report file and return the full updated report text.`,
      { label: `fix:${item.key}`, phase: 'Fix', model: 'opus', effort: 'high' }).then(fix => ({ item: item.key, report: r.report, verdict: r.verdict, fixed: fix }))
  })

const done = results.filter(Boolean)
log(`implement/review/fix done for ${done.map(d => d.item).join(', ')}; starting the runner`)
const reports = done.map(d => `=== ITEM ${d.item} implementer report ===\n${d.report}\n=== reviewer verdict ===\n${JSON.stringify(d.verdict, null, 2)}\n=== fix ===\n${typeof d.fixed === 'string' ? d.fixed : JSON.stringify(d.fixed)}`).join('\n\n')
const run = await agent(`${RULES}\n\n${RUN_SPEC}\n\nTHE TWO ITEMS' REPORTS:\n${reports}`,
  { label: 'run:catalog2', phase: 'Run', model: 'opus', effort: 'high' })

return { items: done, run }
