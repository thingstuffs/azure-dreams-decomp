export const meta = {
  name: 'r33-oracle',
  description: 'Round 33 step 1b, the text oracle before the widening: for every row a generator landed, does some catalogue instance on the landed text reproduce the pre-landing text with its pins erased (rename-invariant, reach.py skeletons)? Where none does, the nearest instance names the missing shape. One opus measurer, one adversarial opus reviewer, a fix if needed.',
  phases: [
    { title: 'Measure', detail: 'one opus agent: the oracle over every landed-generator row, the missing shapes named' },
    { title: 'Review', detail: 'adversarial opus reviewer reruns it and reads the diffs' },
    { title: 'Fix', detail: 'the measurer fixes blocking/major defects' },
  ],
}

const RULES = `
Repository: the git checkout that holds tools/common.py (your working directory; run everything from there with python3 -B).
READ FIRST: work/native_lane/r33_catalog/report_run.txt sections 5 and 9 (the calibration: 23 of 81 single-pin rows agree
at L1; on 20 the reversing kind enumerates nothing; t41's landed shape is refused), work/native_lane/r33_catalog/scratch/
calibrate.py (how the rows, the pre text and the generator chain were selected; its GEN_KINDS table maps generator ->
reversing kinds) and scratch/calibration.jsonl (its 202 candidates with skip reasons), tools/lanes/reach.py (skeleton(),
dist(): rename-invariant token distance - pins erased, comments gone, locals alpha-renamed by first appearance,
declaration lines sorted per block), tools/lanes/perturb_catalog.py (load_modules, kinds_of: every kind's fn(text,
detail) -> [(params, new_text)]), tools/lanes/perturb_basic.py and perturb_struct.py docstrings (the eleven kinds),
tools/pin_sites.py erase_many (clean_notes=True drops emptied #ifndef NON_MATCHING blocks), tools/pin_census.py sites_of.
THE IDEA (the advisor's): the census fingerprint of a landed row is listing(pre) vs listing(pre with its pins erased); the
catalogue fingerprint is listing(landed) vs listing(perturbed). Both refs are the same retail bytes. So if an instance of
a kind on the LANDED text equals the pre-erased text rename-invariantly, the fingerprints agree by construction, and
where no instance does, the diff between the nearest instance and the target names the missing perturbation shape
exactly - text only, no compile, seconds a row.
HARD RULES: never write under src/, ledger/, config/, build_ovl/, toolchain/, tools/; never run sweep.py, gates,
pin_search.py, apply_candidates.py, land_lanes.sh, launch_lane.sh, lane_eval.py, codex or agy; never run state-changing git
(read-only git show/log is fine and needed). The IO discipline in CLAUDE.md applies: no recursive search over work/ or the
repo root; grep only tools/, docs/, your lane directory and single files under src/<container>/ with --max-filesize 4M.
No compiles are needed; if you compile anything, at most 6 at a time. Write only under work/native_lane/r33_catalog/
(scratch/ for scripts and JSONL, rows/ for tables, report_oracle.txt for the report; the harness may refuse .md writes -
return the full report text as well).`

const SPEC = `YOUR TASK (the measurer). Build scratch/oracle.py and run it.
 1. THE ROWS. Every registered row that is pin-free now. For each, walk \`git log --format=%H -- src/<id>.c\` from the newest
    commit and take the FIRST (newest) commit whose parent version of the file has one or more pin sites and whose own
    version has none: that is the landing commit; pre = the parent's text, landed = that commit's text (NOT the current
    file, which later tidy commits may have changed - report how many rows differ). Read the generator chain from
    ledger/sweeps/*.jsonl the way calibrate.py does (sha256(pre) -> ... -> sha256(landed), outcome applied; index the
    journals once). Keep every row whose chain holds at least one transform in calibrate.py's GEN_KINDS (a reversing kind
    exists); record chain_len and whether the chain holds exactly one GEN_KINDS transform (the clean rows) or more. Do not
    require exactly one pin: multi-pin rows are in (all sites erased in the target). Report the counts at each filter.
 2. THE TARGET: target = erase_many(pre, all its sites, clean_notes=True). The START: landed. Sanity: skeleton(landed) !=
    skeleton(target) (else the landing was pins-only: count and drop those - the generator changed nothing else).
 3. DEPTH 1: every kind of both modules enumerated on landed (no cap; if a kind returns more than 400 instances take the
    400 nearest by dist to the target and say so); for each instance dist(skeleton(instance), skeleton(target)). Record per
    row: the reversing kind(s), the best distance by the reversing kind, the best by any kind (which kind), exact hits
    (dist 0) by kind. DEPTH 2 on rows with no exact hit: take the 8 nearest depth-1 instances (any kind), re-enumerate every
    kind on each, record the best distance and any exact hit with its kind pair.
 4. THE MISSING SHAPES. For every row without an exact hit at depth 1 or 2, the nearest instance's text against the target
    as a unified diff (git diff --no-index on tmp files is fine; skeleton-level diff too). Read at least 40 of them across
    all generators and NAME the missing shapes as a short list with counts (for example: the t41 loop label with the
    brace and the test on one line; a symbol written as an integer literal; a fence's statement moved across k
    statements; an initialised declaration split; a member spelled as an offset load). Each named shape: the count of rows,
    the generator(s), one row id and the two texts' differing lines. Rows whose diff is noise (a comment, a NON_MATCHING
    arm, whitespace) are counted separately as oracle noise, not shapes.
 5. TABLES in rows/: oracle_table.txt (per generator: rows, clean rows, exact by the reversing kind at depth 1, exact by
    another kind at depth 1 (which), exact at depth 2, none; the median best distance of the reversing kind and of any
    kind), oracle_missing_shapes.txt (the named shapes, counts, examples), oracle_rows.jsonl in scratch/ (one record a row
    with everything above), and a per-row text list rows/oracle_rows.txt (id, generator, verdict, best kind, best dist).
 6. report_oracle.txt: what was measured, every count, the two tables, the shapes ranked by rows behind them, and which
    shapes you would build first for the widening with the numbers. Return the full report text and the file paths.
Time: the whole thing is pure Python; 300 rows x 11 kinds should take minutes at Pool(8). Say the wall time.`

const VERDICT = {
  type: 'object',
  properties: {
    defects: { type: 'array', items: { type: 'object', properties: {
      severity: { type: 'string', enum: ['blocking', 'major', 'minor'] },
      where: { type: 'string' }, what: { type: 'string' }, evidence: { type: 'string' } },
      required: ['severity', 'where', 'what', 'evidence'] } },
    shapes_confirmed: { type: 'array', items: { type: 'string' } },
    summary: { type: 'string' },
  },
  required: ['defects', 'shapes_confirmed', 'summary'],
}

const REVIEW = `Refute it. Read the report and scratch/oracle.py in full. Rerun it (or its per-row function) yourself on 30 rows of
YOUR choice drawn across the generators and check: (1) the landing commit is the right one (the parent has pins, the
child none, and the chain's transform is the one the commit subject names) - a wrong commit or a chain mis-read is
BLOCKING; (2) the target really is the pre text minus its pins and nothing else (diff pre against target: only pin
statements, ASM_REG declarators and emptied blocks may differ) - anything else is BLOCKING; (3) an 'exact' verdict is
real: for 10 exact rows diff the instance's text against the target by eye - a rename-invariance that hides a real
difference (a different variable merged, a different statement moved) is MAJOR; (4) the named missing shapes: read 15
'none' diffs yourself and say whether the shape names are right and whether a shape is missing from the list - a shape
the measurer named that the diffs do not show is MAJOR; (5) the counts in oracle_table.txt reproduce from
oracle_rows.jsonl. Do not fix anything. Return only defects you demonstrated with evidence, the shapes you confirmed, and
a summary.`

const r = await agent(`${RULES}\n\n${SPEC}`, { label: 'measure:oracle', phase: 'Measure', model: 'opus', effort: 'high' })
const v = await agent(`${RULES}\n\nYOU ARE THE ADVERSARIAL REVIEWER of the oracle another agent built to this spec:\n${SPEC}\n\nThe measurer's report:\n${r}\n\n${REVIEW}`,
  { label: 'review:oracle', phase: 'Review', model: 'opus', effort: 'high', schema: VERDICT })
const real = (v?.defects || []).filter(d => d.severity !== 'minor')
let fix = 'no blocking or major defects'
if (real.length) {
  fix = await agent(`${RULES}\n\nYou built scratch/oracle.py (spec: ${SPEC}).\n\nYour report:\n${r}\n\nAn adversarial reviewer demonstrated these defects:\n${JSON.stringify(real, null, 2)}\n\nFix each one (or show with evidence that the reviewer is wrong), rerun the oracle, regenerate the tables, append a "Review fixes" section to report_oracle.txt and return the full updated report text.`,
    { label: 'fix:oracle', phase: 'Fix', model: 'opus', effort: 'high' })
}
return { report: r, verdict: v, fix }
