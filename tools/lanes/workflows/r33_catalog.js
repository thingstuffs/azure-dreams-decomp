export const meta = {
  name: 'r33-catalog',
  description: 'Round 33 step 1: the forward perturbation catalogue on pin-free byte-exact rows. Two opus implementers in parallel (A: fingerprint + driver + census extension + match + the text-level perturbations; B: the parsing-level perturbations), each adversarially reviewed and fixed; then one opus runner builds the 1,000-row catalogue, the two-move catalogue, the census fingerprints, the match, the calibration and the coverage report. The parent does the final check and reads the gate.',
  phases: [
    { title: 'Implement', detail: 'two opus implementers in parallel: A the framework, B the structural perturbations' },
    { title: 'Review', detail: 'one adversarial opus reviewer per item, reruns everything, demonstrated defects only' },
    { title: 'Fix', detail: 'the implementer fixes blocking/major defects' },
    { title: 'Run', detail: 'one opus runner: census --fp, the catalogues, the match, the calibration, the report' },
  ],
}

const RULES = `
Repository: the git checkout that holds tools/common.py (your working directory; run everything from there with python3 -B).
READ FIRST: work/native_lane/r33_catalog/evidence/PLAN_round33.txt (the owner-agreed plan; the round-32 block of
docs/HANDOVER.md lines 26-99 has the context); docs/LANE_KIT.md; docs/PIN_MECHANISMS_20260912.md sections "Round 32",
"Round 31", "Round 30"; tools/lanes/erase_census.py (the lone-erasure census: one record per live pin site, d0 = screen
distance of the site erased alone); tools/xform/screen.py (compile_s(row, text) -> normalised cc1 listing lines or None,
sdiff(a, b) -> changed-line count; ~25-60 ms a compile); work/native_lane/r32_t69tail/scratch/dropreg_residue.py (the
residue classes MOVED / RECOLOURED / CHANGED and the opcode shape) and scratch/rev_residue_check.py (the reviewer's stricter
reading: hard registers vs $L labels); tools/pin_census.py sites_of (the live pin sites of a text); tools/common.py rows(),
clean_path(), parse_cfg(); tools/tests/test_t69_prologue.py (the unittest style to follow).
THE POPULATION: the registered rows (tools/common.rows(), 6,767) whose clean text under src/ has NO pin site
(pin_census.sites_of(text) == []): 5,467 rows, every one byte-exact as it stands. Rows with a preprocessor conditional
inside a function body are excluded from the catalogue (count them). Pinned rows are never perturbed.
THE DIRECTION (the rule every perturbation obeys): the census diff is ref = the PINNED text's listing (= retail), cand =
the text with one site erased. The catalogue diff is ref = the pin-free row's listing (= retail), cand = the perturbed
text. So every perturbation is a generator's move REVERSED - toward the m2c form that the generator would undo - and the
'-' side of both diffs is retail, the '+' side is the m2c-like text. For t41 the population is the backward-goto loops
in pin-free rows (the honest C) rewritten as do { } while / while (m2c's form); for t54/t59 it is the named symbols
rewritten as a page-base local plus offsets; for t69 it is a parameter copied into an entry local; and so on.
THE CONTRACT between the two perturbation modules (fixed; neither module imports the other; both may import any
existing module under tools/ and tools/xform/):
    PERTURBATIONS = [(kind, fn), ...]          # module-level, kind a short snake_case string
    fn(text, detail=None) -> [(params, new_text), ...]
  params is a JSON-serialisable dict with at least {"site": <1-based line of the edited statement or declaration>,
  "label": <one human-readable line>} plus the kind's own parameters (the variable, the from/to type, the expression,
  the two statements, ...). detail is a collections.Counter (like t69_prologue.Detail) that the function fills with
  (refusal, what) records so the population ceiling of each kind can be read text-only. Enumeration is deterministic
  (same text -> same list, same order), instances ordered by site line. A perturbation never touches a preprocessor
  directive line, never adds an ASM_* macro, __asm__, volatile, a fake dependency, a one-trip block, a #pragma or an
  attribute; it must not change what the text means beyond what the move itself means (a width change means a width
  change; an adjacent swap means two independent statements). A temp's type may be spelled __typeof__(expr) where the
  explicit type is not known from the text (the instance never lands; gcc 2.x accepts __typeof__ and it is codegen-neutral).
HARD RULES: never write under src/, ledger/, config/, build_ovl/, toolchain/; never run sweep.py, gates, pin_search.py,
apply_candidates.py, land_lanes.sh, launch_lane.sh, lane_eval.py, codex or agy; never run state-changing git (read-only
git show/log/diff is fine). The IO discipline in CLAUDE.md applies: no recursive search over work/ or the repo root; grep
only tools/, include/, docs/, your lane directory and single files under src/<container>/, always with --max-filesize 4M.
At most 6 concurrent compiles (Pool(6)) while other agents run. The harness may refuse writes of .md files: write your
report as a .txt in the lane and ALSO return its full text. An honest negative (a kind that produces no instance, a
fingerprint no kind reaches) is a complete deliverable when it is measured.
LANE DIRECTORY: work/native_lane/r33_catalog/ (rows/, scratch/, tmp/, evidence/; .ignore hides scratch/, tmp/ and
*.jsonl). Bulk JSONL goes under scratch/ or under work/perturb_catalog/ (its .ignore hides *.jsonl and *.json). Tables
you want read go in rows/ as .txt.`

const SPEC_A = `YOU ARE IMPLEMENTER A. YOU OWN: tools/lanes/residue.py (new), tools/lanes/perturb_basic.py (new),
tools/lanes/perturb_catalog.py (new), tools/lanes/erase_census.py (one additive flag), tools/tests/test_perturb_basic.py and
tools/tests/test_residue.py (new). Another implementer is writing tools/lanes/perturb_struct.py to the same contract at the
same time: do not read, import or wait for it; your driver imports it by name inside a try/except and logs its absence.
DELIVERABLES, in this order:
 1. tools/lanes/residue.py: fingerprint(ref, cand) -> dict, ONE function used by the census side and the catalogue side.
    ref and cand are compile_s listings (cand None -> cls NOBUILD). Fields: d (sdiff), cls in {INVISIBLE (d == 0),
    MOVED (same lines, another order), RECOLOURED (register-anonymised lines equal AND in the same order - only registers
    differ; use a hard-register regex, not \\$\\w+, so a $L label renumber is not read as a recolour), BOTH (register-
    anonymised multisets equal, order differs), CHANGED (anything else), NOBUILD}, band (d in 1-2, 3-4, 5-8, 9-16, 17-32,
    33+), shape (the opcode multiset of the '-' lines then the '+' lines, dropreg_residue.py's format, computed exactly when
    the diff has at most 8 changed lines, else the top-4 opcodes per side by count with a 'far:' prefix), regs (the (from,
    to) register pairs of a recolour, at most 6), regfam (the same pairs mapped to register families: a, v, t, s, sp, ra,
    gp, fp, at, k, zero, other), and three nested keys L0 = cls|band, L1 = L0|shape, L2 = L1|regfam. Unit tests on
    synthetic listings for every class and both shape modes.
 2. tools/lanes/erase_census.py: a --fp flag that adds fp = residue.fingerprint(ref, c) to EVERY record (all sites, not
    only d0 <= DIFF_MAX). Without --fp the output must be byte-identical to today's: prove it by running
    \`git show HEAD:tools/lanes/erase_census.py\` saved as scratch/erase_census_head.py against yours on 50 rows (--only a
    row list; compare the two JSONL outputs sorted).
 3. tools/lanes/perturb_basic.py, the text-level kinds, each with a refusal Detail counter and tests (the move on synthetic
    text; two must-refuse cases each):
    param_copy    (t69_prologue reversed: m2c's entry copy) a parameter p becomes p_in (m2c's names: x_in / x_arg / x_data;
                  use _in) in the signature, a local \`T p;\` is declared at the top of the function's declaration block
                  and \`p = p_in;\` is inserted as the first statement; body uses stay p. Refuse array, function-pointer and
                  struct-by-value parameters, a parameter whose name collides, and a K&R signature. One instance per parameter.
    decl_reorder  (t53_reg_state decl-swap, symmetric) two adjacent declaration lines of one block exchanged. One instance
                  per adjacent pair; refuse declarations that span lines or carry initialisers with side effects.
    width_change  (t36_paramwidth / t37_localwidth, symmetric) an integer local or parameter of type u8/s8/u16/s16/u32/s32
                  (also char/short/int spellings) declared at another width or signedness; instances for each of: one
                  width up, one width down, the other signedness (params record from and to). Refuse arrays, pointers,
                  address-taken variables, bit-fields, and 64-bit types.
    adjacent_swap (t51_sched_order) two adjacent simple statements of one block exchanged when tools/xform/t51_sched_order's
                  own units()/access()/independent() say they are independent (the same tests tools/lanes/sched_map.py
                  applies); refuse control lines, declarations, multi-line statements, calls (a call is never swapped).
    local_alias   (natural.dropcopy reversed: m2c's \`x = y;\`) a local or parameter y read in a straight run of two or more
                  consecutive simple statements and not written in that run nor address-taken: a new local x of y's declared
                  type at the top of the block, \`x = y;\` before the run, the run's reads of y renamed x. One instance per
                  maximal run, longest runs first, at most 4 per function.
    page_local    (t54_pagebase / t59_offsetsym reversed) two or more uses of D_8XXXXXXX symbols whose upper 16 bits agree
                  (one 64 KiB page) in one function: \`u8 *page;\` declared, \`page = (u8 *)0xXXXX0000;\` inserted as the
                  first statement, each use D_XXXXYYYY rewritten \`(*(__typeof__(D_XXXXYYYY) *)(page + 0xYYYY))\`. Refuse
                  symbols used as arrays, functions or with &; refuse a function that already has a local named page. One
                  instance per page.
    Determinism, the directive rule and the population rule (a text with pin sites is refused outright) are tested.
 4. tools/lanes/perturb_catalog.py, the driver (docstring first, usage lines like erase_census.py):
    sample   --n 1000 --seed 20260916 --out work/native_lane/r33_catalog/rows/sample_rows.txt: the pin-free population
             (exclusions counted and printed), stratified by container x size tercile (line count), proportional
             allocation, a manifest (rows/sample_manifest.txt) with each stratum's population and draw.
    run      ROWS OUT.jsonl [--procs 6] [--per-kind 3] [--per-row 12] [--kinds k1,k2] [--two-move] [--phase]: per row
             ref = compile_s(row, text) once; the kinds of perturb_basic.PERTURBATIONS plus perturb_struct.PERTURBATIONS
             (try/except import; log which modules loaded); per kind up to --per-kind instances chosen deterministically
             from a seeded shuffle of the enumeration (the seed derived from the row id), at most --per-row per row; each
             instance compiled and fingerprinted; ONE JSON record per instance: id, kind, params, fp (and nobuild=true when
             compile_s returns None). Refusal counters aggregated into OUT.refusals.json. Resumable by row id. Records with
             fp.cls INVISIBLE are kept (a move cc1 cannot see is a finding, never a cause). --two-move: for each row every
             ordered pair of the row's chosen single instances (the second kind re-enumerated on the first's text, the
             instance whose site is nearest the original chosen), capped at 100 pairs a row, records carrying kinds=[k1,k2]
             and both params. --phase: on records with fp.d in 1..4 only, the first differing pass via
             tools/phase_census.compile_dumps (40x the cost of compile_s; optional, never a gate input).
    summary  OUT.jsonl: per kind: instances, nobuild, INVISIBLE share, class distribution, d distribution, the 10 most
             common L1 keys with counts; the same for two-move records by kind pair.
    match    --census CENSUS.jsonl --catalog CAT.jsonl [--catalog2 CAT2.jsonl] --out DIR [--min 5]: for every census
             site with fp: at each level the catalogue kinds (and kind pairs) producing its key with counts; the site's
             ranked causes = kinds by share of that key's catalogue mass, taken at the finest level where the key has
             >= --min catalogue instances. Tables (as .txt in DIR): coverage (share of sites with a covered key) at L0, L1,
             L2, overall and by band, by row pin-band (1 / 2-6 / 7-20 / 21+) and by macro family (REG / KEEP / FENCE /
             other); the concentration (top-10 keys' share of catalogue mass and of census mass per level); cause purity
             (for covered keys, the top kind's share of the key's mass; its distribution); the uncovered L1 keys ranked by
             pins behind them; per-row buckets: a = some site covered at L1 with a top cause whose kind has a generator
             (KIND_GENERATOR, a static table in the module: param_copy -> t69_prologue, hoist -> varset.inline_def / t64,
             decl_reorder -> t53 decl-swap, retype_void -> varset.retype_ptr / t64, split -> varset.split_def / t64,
             merge -> varset.merge_local + merge_param / t64, width_change -> t36 / t37, adjacent_swap -> t51,
             local_alias -> natural.dropcopy, page_local -> t54 / t59, goto_to_loop -> t41 / t41b), b = covered but the
             top cause's kind has no generator, weak = covered at L0 only, c = no site covered; rows and pins per bucket;
             and per-site JSONL (id, i, macro, fp keys, causes) in DIR. Every table also written as one summary .txt.
 5. A smoke run: sample, then run on the first 60 sample rows with --procs 6 and --per-kind 2, then summary; put the
    output tables in rows/smoke_*.txt. Report per kind: instances, nobuild rate, INVISIBLE share, class distribution.
    A kind that produces no instance on 60 rows, or only INVISIBLE or only NOBUILD, is a defect: fix it before reporting.
 6. Direction check: on three instances (one param_copy, one local_alias, one page_local) print both listings' diff and
    confirm by reading that the '-' lines are the exact text's and the '+' lines the perturbed text's.
 7. report_impl_A.txt in the lane: every file, the tests' output, the identity proof of erase_census, the smoke tables,
    the direction check, every refusal count, and what you would widen. Return: file paths, the test output, the tables
    verbatim, the full report text.`

const SPEC_B = `YOU ARE IMPLEMENTER B. YOU OWN: tools/lanes/perturb_struct.py (new) and tools/tests/test_perturb_struct.py (new).
Another implementer is writing the driver and tools/lanes/perturb_basic.py at the same time: do not read, import or wait
for them. Your module exposes PERTURBATIONS per the contract; you measure it with a scratch driver of your own
(work/native_lane/r33_catalog/scratch/struct_measure.py: compile_s / sdiff against the row's own text, the MOVED /
RECOLOURED / CHANGED / INVISIBLE / NOBUILD reading of dropreg_residue.py with the hard-register regex of
rev_residue_check.py, Pool(6)).
READ ALSO: tools/xform/varset.py in full (Fn, functions(), webs(), reaching(), liveness(), usable_locals(),
inline_def_candidates, split_def_candidates, merge_local_candidates, merge_param_candidates, retype_ptr_candidates - the
declaration-level moves the lanes made, with a skips Counter), tools/xform/t64_varset.py (how varset is driven),
tools/xform/natural.py (dropcopy, retype and the fence shapes; its _params/_decl helpers), tools/xform/t41_gotoloop.py and
t41b_gotoloop_while.py (loops(), rewrite(): the do-while -> goto and while -> goto moves you reverse), tools/xform/t69_prologue.py
(_pp_depth: the directive-depth map; how a function's declaration block is found).
THE KINDS (each with a refusal Detail counter and tests: the move on synthetic text, two must-refuse cases each):
    hoist        (varset inline_def reversed) a side-effect-free sub-expression of a simple statement or a return - a member
                 load a->b / a.b, an array element, a call argument, an arithmetic sub-expression - hoisted into a new local
                 declared \`__typeof__(EXPR) hoisted_N;\` at the top of the function's declaration block, \`hoisted_N = EXPR;\`
                 inserted before the statement, the occurrence replaced. Refuse expressions with ++ -- = or a call inside,
                 expressions inside loop conditions or short-circuit / conditional operands, bit-field members (typeof
                 fails; let the compile refuse those, count nobuild), and statements inside a nested block that declares a
                 variable the expression names. Params: the expression, its class (member / array / arg / arith). At most
                 6 instances per function, ordered by site.
    retype_void  (varset retype_ptr reversed: m2c's untyped pointer) a local or parameter \`T *p\` (T a struct / union /
                 typedef name, not void / char / u8 / s8 and not a function pointer) declared \`void *p\` with every use
                 that needs the type - p->f, p[i], *p, p + n / p - n, p++ / p-- - rewritten as ((T *)p)->f etc.; a bare p
                 passed or assigned stays bare (void * converts silently under -w). Refuse double pointers, address-taken p,
                 p declared with an initialiser you cannot rewrite, and a p that is a struct member access target only.
    split        (varset merge reversed; varset.split_def_candidates IS this move) wrap varset's split_def_candidates(text,
                 skips=detail) as instances, params = the label; keep varset's refusals in detail.
    merge        (varset split reversed) wrap merge_local_candidates and merge_param_candidates the same way (kind 'merge',
                 params carry which). Both wrappers: the population is pin-free text, so pass whatever varset needs for an
                 unpinned function (read usable_locals' allow_register_pin / allow_init).
    goto_to_loop (t41 / t41b reversed: m2c's loop form for a backward goto) a backward-goto loop - a label L, a body, and a
                 single \`if (COND) goto L;\` (t41's shape) or a \`goto L;\` under a top test (t41b's shape) - rewritten as
                 \`do { body } while (COND);\` or \`while (COND) { body }\` with the label removed. Refuse a label with two
                 or more gotos, a goto from outside the region, a body that declares variables, a label used by a
                 forward goto, and any region containing a directive line. Params: the label, the form.
    If a kind's population on 100 pin-free rows is empty, say so with its refusal table - that is a result, not a failure.
DELIVERABLES, in order:
 1. The module and its tests (all passing; python3 -B -m pytest tools/tests/test_perturb_struct.py -q, or unittest).
 2. The measurement on 100 pin-free rows (choose them deterministically: the first 100 registered rows in id order whose
    src text has no pin site and no preprocessor conditional inside a function body): per kind instances, nobuild,
    INVISIBLE share, class distribution, d distribution, the refusal table. A kind that is only INVISIBLE or only NOBUILD,
    or that never enumerates, is a defect to fix (unless its population is genuinely empty - show the refusals).
 3. The typeof check: on 5 hoist instances whose explicit type you CAN name from the text (a local of known type), compile
    the __typeof__ spelling and the explicit spelling and show the listings are identical.
 4. Direction check: on one goto_to_loop and one retype_void instance, print the listing diff and confirm by reading that
    the '-' lines are the exact text's and the '+' lines the perturbed text's.
 5. report_impl_B.txt in the lane: every file, the tests' output, the measurement tables, the refusal tables, the typeof
    check, the direction check, and what you would widen. Return: file paths, the test output, the tables verbatim, the full
    report text.`

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

const REVIEW_A = `Refute it. Read the report and every owned file in full, then git diff tools/lanes/erase_census.py against HEAD
(read-only) so you review exactly what changed there. Run the unit tests. Then, independently of the implementer's numbers:
(1) rerun the erase_census identity proof yourself on 50 rows of YOUR choice (HEAD's script vs the new one without --fp,
outputs sorted and compared byte-for-byte) - any difference is BLOCKING; (2) run the driver on 50 fresh pin-free rows
(--procs 6 --per-kind 2) twice and confirm the two outputs are identical (determinism) - a difference is MAJOR; (3) for EVERY
kind, write 5 instances' original and perturbed texts to tmp/ and read the C diffs (git diff --no-index): the move must be
exactly the m2c form the spec names and nothing else - a directive line touched, a second variable renamed, a use missed
(a p left where p_in was meant, a read of y in the run not renamed), a width change that also changed a pointer, a swap of
two statements that share a memory access or a variable, a page rewrite of a symbol used as an array - each is BLOCKING;
(4) the direction on three instances read from both listings by you; (5) the fingerprint: construct listings by hand that
are MOVED, RECOLOURED, BOTH and CHANGED and one where only $L labels differ, and show what fingerprint() returns for each -
a label renumber classed as RECOLOURED is MAJOR; (6) the match: build a tiny census and catalogue by hand (10 records) and
check the coverage, purity and bucket tables against your own count - a wrong share is MAJOR; (7) the sample: check the
manifest's strata against your own count of the population - a wrong population rule (a pinned row admitted, the
directive exclusion not applied) is BLOCKING. Do not fix anything. Return only defects you demonstrated with evidence, the
list of kinds you confirmed produce the named move, and a summary.`

const REVIEW_B = `Refute it. Read the report and tools/lanes/perturb_struct.py and its tests in full. Run the unit tests. Then,
independently of the implementer's numbers: (1) rerun the 100-row measurement with the implementer's scratch driver on 100
DIFFERENT pin-free rows (rows 101-200 by the same rule) and report the per-kind tables you read; (2) for EVERY kind, write 5
instances' original and perturbed texts to tmp/ and read the C diffs (git diff --no-index): the move must be exactly the
m2c form the spec names and nothing else - a hoisted expression with a side effect or one that changes evaluation order
across a call, a cast added at a use that did not need it or missed at one that did, a retype of a double pointer, a
varset wrapper that admits a pinned function, a goto loop rewritten where the label has a second goto or a forward goto, a
loop body that declared a variable, a directive line touched - each is BLOCKING; (3) the typeof check on 5 instances of
YOUR choice (explicit vs __typeof__ spelling: identical listings) - a difference is MAJOR; (4) the direction check read by
you on one instance per kind; (5) determinism: enumerate each kind twice on 20 rows and compare - a difference is MAJOR;
(6) run each fn on a text that carries an ASM_KEEP and on one with an #ifdef inside the body and show it refuses. Do not
fix anything. Return only defects you demonstrated with evidence, the list of kinds you confirmed produce the named move,
and a summary.`

const RUN_SPEC = `YOU ARE THE RUNNER. Both perturbation modules are written, reviewed and fixed (their reports are below). You
own nothing under tools/; you write only under work/native_lane/r33_catalog/ and work/perturb_catalog/. You may use
Pool(8) / --procs 8 (you run alone). Do everything in this order and record the wall time of each step:
 1. The census with fingerprints on the CURRENT tree: python3 -B tools/lanes/erase_census.py
    work/native_lane/r33_catalog/scratch/census_fp.jsonl --procs 8 --fp; then erase_census.py summary on it (rows/
    census_summary.txt). Expect ~6,180 sites in ~1,300 rows.
 2. The sample (perturb_catalog.py sample, n 1000, seed 20260916) and the single-move catalogue on it:
    perturb_catalog.py run rows/sample_rows.txt work/perturb_catalog/single_1000.jsonl --procs 8 --per-kind 3 --per-row 14;
    then summary -> rows/single_summary.txt. Report per kind: instances, nobuild, INVISIBLE share, class and d distributions.
 3. The two-move catalogue on 200 rows of the sample (every fifth row of sample_rows.txt): run ... --two-move ->
    work/perturb_catalog/pairs_200.jsonl; summary -> rows/pairs_summary.txt.
 4. The match: perturb_catalog.py match --census scratch/census_fp.jsonl --catalog work/perturb_catalog/single_1000.jsonl
    --catalog2 work/perturb_catalog/pairs_200.jsonl --out rows/match/ --min 5. Read every table.
 5. THE CALIBRATION (the gate is unfalsifiable without it). From ledger/sweeps/*.jsonl (records with "outcome":"applied";
    read one file first for the field names) and read-only git, select up to 40 rows that are pin-free NOW, whose last
    landing commit (git log --format=%H -n 1 -- src/<id>.c; git show <commit>^:src/<id>.c is the pre text) had EXACTLY ONE
    pin site, and whose landing was one of the generators the kinds reverse (t69_prologue, natural dropcopy / t20 / t61,
    t53 decl-swap, t36, t37, t51, t64 / varset inline_def / split / merge / retype_ptr, t54, t59, t41 / t41b) - the sweep
    journal or the commit subject names it. For each: F_census = residue.fingerprint(compile_s(pre), compile_s(erase_many
    (pre, [site]))) and, on the CURRENT text, EVERY instance of the reversing kind (no cap), each fingerprinted; report per
    generator: rows, agree at L2, at L1, at L0, none, and the nearest instance's d. Agreement at L1 on most rows is what
    the method claims; write plainly if it fails.
 6. A negative control for the fingerprint's resolution: split the single-move catalogue in halves by row and compute the
    coverage of half B's records by half A at each level (how much the catalogue covers ITSELF), beside the census coverage.
    If the census coverage at L1 is not clearly above what a catalogue of the same size covers of random OTHER perturbations,
    say so: the keys are too coarse.
 7. --phase on the near band of the single-move catalogue only if steps 1-6 finished within 3 hours; otherwise skip and say so.
 8. report_run.txt in the lane: the population and exclusions, the sample manifest, every per-kind table, the coverage
    tables (level x band, level x pin-band, level x family), concentration and purity, the top 30 uncovered L1 keys with the
    pins behind them and the macro families, the calibration table, the control, the bucket table (rows and pins per
    bucket), and your reading of the gate: coverage at L1 by band and by pin-band; is the shortfall in the far band and the
    7+ rows (the finding the plan predicted) or in the near band (the perturbation set is too narrow); which kinds explain
    the most census mass; which uncovered keys recur. Recommend: widen perturbations (which, from what evidence) or widen rows.
    Return the full report text and the paths of every table.`

const ITEMS = [
  { key: 'A', file: 'tools/lanes/residue.py, perturb_basic.py, perturb_catalog.py, erase_census.py --fp', spec: SPEC_A, review: REVIEW_A },
  { key: 'B', file: 'tools/lanes/perturb_struct.py', spec: SPEC_B, review: REVIEW_B },
]

const results = await pipeline(ITEMS,
  item => agent(`${RULES}\n\nYOUR TASK: ${item.spec}`,
    { label: `impl:${item.key}`, phase: 'Implement', model: 'opus', effort: 'high' }),
  (report, item) => agent(`${RULES}\n\nYOU ARE THE ADVERSARIAL REVIEWER of ${item.file}, just written by another agent to this spec:\n${item.spec}\n\nThe implementer's report:\n${report}\n\n${item.review}`,
    { label: `review:${item.key}`, phase: 'Review', model: 'opus', effort: 'high', schema: VERDICT }).then(v => ({ report, verdict: v })),
  (r, item) => {
    const real = (r.verdict?.defects || []).filter(d => d.severity !== 'minor')
    if (!real.length) return { item: item.key, report: r.report, verdict: r.verdict, fixed: 'no blocking or major defects' }
    return agent(`${RULES}\n\nYou implemented ${item.file} (spec: ${item.spec}).\n\nYour report:\n${r.report}\n\nAn adversarial reviewer demonstrated these defects:\n${JSON.stringify(real, null, 2)}\n\nFix each one (or show with evidence that the reviewer is wrong), rerun the unit tests and your measurement / smoke run, and return a per-defect note: fixed / disputed (with evidence). Append a "Review fixes" section to your report file and return the full updated report text.`,
      { label: `fix:${item.key}`, phase: 'Fix', model: 'opus', effort: 'high' }).then(fix => ({ item: item.key, report: r.report, verdict: r.verdict, fixed: fix }))
  })

const done = results.filter(Boolean)
log(`implement/review/fix done for ${done.map(d => d.item).join(', ')}; starting the runner`)
const reports = done.map(d => `=== ITEM ${d.item} implementer report ===\n${d.report}\n=== reviewer verdict ===\n${JSON.stringify(d.verdict, null, 2)}\n=== fix ===\n${typeof d.fixed === 'string' ? d.fixed : JSON.stringify(d.fixed)}`).join('\n\n')
const run = await agent(`${RULES}\n\n${RUN_SPEC}\n\nTHE TWO ITEMS' REPORTS:\n${reports}`,
  { label: 'run:catalog', phase: 'Run', model: 'opus', effort: 'high' })

return { items: done, run }
