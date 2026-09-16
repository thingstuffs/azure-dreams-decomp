export const meta = {
  name: 'r34-packs',
  description: 'Round 34 step 3c tooling: the catalogue-admission pack builder for the model lanes - rows the catalogue cannot explain (unexplained at L1 in the near band, or far band), ranked by pins, served and closed-group checks per bucket, each brief carrying the row\'s fingerprint, its top causes labelled as compatible mechanisms, and the round-33/34 negatives. One opus implementer, one adversarial opus reviewer, a fix if needed; the parent decides the launch.',
  phases: [
    { title: 'Implement', detail: 'one opus implementer: build_catalog_lanes.py, catalog_lane_brief.md, two dry-run packs' },
    { title: 'Review', detail: 'adversarial opus reviewer: the admission rule, the served/closed guards, the briefs' },
    { title: 'Fix', detail: 'the implementer fixes blocking/major defects' },
  ],
}

const RULES = `
Repository: the git checkout that holds tools/common.py (your working directory; run everything from there with python3 -B).
READ FIRST: docs/LANE_KIT.md in full (the pack builders, served.py, ledger.py --closed, the brief rules in "Before launch"
item 8 - the cd rule as line 1 of PROMPT.txt, write only inside the lane directory, never src/ git gates sweeps, the IO
discipline, at most 8 compiles, the scaffolding list VERBATIM, freedom of approach, hypotheses to TEST not assume, an
unreachable class is a finding, the deliverables); tools/lanes/build_keep_lanes.py and build_alloc_lanes.py in full (the
pack layout every builder writes: base/<container>/<name>.c, out/, rows.md, BRIEF.md from a template with @TOKENS@,
PROMPT.txt; the served.assert_unserved guard; --dry-run; --per); tools/lanes/keep_lane_brief.md and alloc_lane_brief.md
(the templates: what a lane is told about outputs - exact files under out/<container>/<name>.c - and about .base_sha);
tools/lanes/served.py; tools/lanes/ledger.py (--closed 0.2: the (family, stratum) groups no pack may be built on);
tools/lanes/pools.py (a row's family and stratum); tools/lanes/launch_lane.sh (how a pack is launched: BRIEF.md +
PROMPT.txt; sol = gpt-5.6-sol); docs/HANDOVER.md lines 26-75 (round 34) and the round-33 block below it (the catalogue,
the buckets, the round-35 plan item 1 - which is exactly what you build); docs/PIN_MECHANISMS_20260912.md "Round 34" and
"Round 33" (the measured negatives every brief must carry so no lane re-derives them).
THE EVIDENCE: work/native_lane/r33_catalog/rows/match3/per_site.jsonl (one record per pinned site: id, i, macro, d0, cls,
band, L0/L1/L2 keys, level, mass, causes = [{cause, n, share, generator}] ranked), rows/match3/row_buckets.txt and
bucket_{a,weak,c}_rows.txt, rows/match3/bucket_a_split.jsonl (per bucket-a row: generator, journal outcomes),
scratch/census_fp2.jsonl (the census with fingerprints; the tree has since lost 33 pins in 9 rows - re-read sites_of on
src/ and drop or re-count those rows), rows/near_uncovered.txt (the shape families of the uncovered near band).
HARD RULES: never write under src/, ledger/, config/, build_ovl/, toolchain/; never run sweep.py, gates, pin_search.py,
apply_candidates.py, land_lanes.sh, launch_lane.sh, codex or agy; never run state-changing git. IO discipline (CLAUDE.md):
no recursive search over work/ or the repo root; grep only tools/, docs/, the named lane directories and single files under
src/<container>/ with --max-filesize 4M. Write only tools/lanes/build_catalog_lanes.py, tools/lanes/catalog_lane_brief.md,
tools/tests/test_build_catalog_lanes.py, and under work/native_lane/ the pack directories you build (names catalog_near1,
catalog_far1) plus your report work/native_lane/r34_wave/report_packs.txt (the harness may refuse .md writes; return the
full report text too). Building a pack must NOT launch it.`

const SPEC = `YOUR TASK (the implementer). Build tools/lanes/build_catalog_lanes.py to the other builders' shape:
    python3 tools/lanes/build_catalog_lanes.py [--bucket near|far|both] [--per 12] [--band 4-8] [--repack]
        [--ignore-closed] [--dry-run] [--match DIR] [--census FILE] LANE...
 1. THE ADMISSION RULE (round 35 plan item 1): a pinned row (sites_of on src/ NOW) is UNEXPLAINED-NEAR when it has at least
    one site with d0 <= 4 and NONE of its d0 <= 4 sites is covered at L1 or finer with a cause (per_site.jsonl: level in
    (L1, L2) and causes non-empty); it is FAR when it has no site with d0 <= 4 at all (every site in a band where the
    round-33 control says the key means nothing). Rows with a near site covered at L1 are bucket a and NOT admitted (they
    are the generators' work). Rank by pins descending (the plan's rule) unless --band restricts the pin band. Guards, both
    on by default: served rows are refused (served.served_rows(); --repack lifts it and marks the pack a retry), and rows in
    a CLOSED (family, stratum) group are refused (ledger.py's --closed 0.2 groups; read how ledger/pools compute family
    and stratum and reuse their functions; --ignore-closed lifts it). --dry-run prints, per bucket: candidates, refused as
    served, refused as closed (with the group), admitted, and the pin-band histogram of the admitted rows.
 2. THE PACK: base/<container>/<name>.c (the current text), out/ (empty), rows.md - one section per row with: the pin count
    and each site's line, macro, d0, class, band, shape and register pairs (from per_site.jsonl / the census), the site's
    top three causes with shares and the generator each names, EACH LABELLED "a compatible mechanism, not the move" (the
    oracle agreed on 45% of landed rows), the journal outcome of that generator on this text where bucket_a_split has it,
    and the measured negative that applies (a lookup table in the builder keyed by cause / L1 key family: the t69 missed
    class - which copies are parameters, every register and ordering lever negative in round 34; the address class - t29
    SYMDEF pays 1 pin, NONRAM 0, the copy-drop composition 0, t54's budget 0, the residue is allocation/schedule after the
    respelling; the t51 noop class - a region reschedule, a single statement move reaches 0 on 0 of 60; RECOLOURED
    residues - an allocation choice no single text move produces; INVISIBLE - assembler-side). For FAR rows say plainly
    that the catalogue names no cause and give the per-site classes only. BRIEF.md from tools/lanes/catalog_lane_brief.md
    (write it: keep_lane_brief.md's structure and every rule it carries, the scaffolding list VERBATIM, the outputs and
    .base_sha exactly as the existing briefs specify, the family section rewritten for this pack: what a fingerprint is,
    what a cause is and is not, the measured negatives, and the instruction to TEST the named hypotheses first and then
    the whole-function rewrite the plan calls "the rewrites only a model makes"); PROMPT.txt with the cd rule as line 1.
    served.assert_unserved before writing unless --repack.
 3. BUILD TWO DRY-RUN PACKS AND THEN THE PACKS: --bucket near --per 12 catalog_near1 and --bucket far --per 12
    catalog_far1 (sol is the tier the plan names; the parent launches, not you). Report the dry-run tables and, for each
    built pack, the row list with pins and the bucket, and paste one row's rows.md section in the report.
 4. TESTS (tools/tests/test_build_catalog_lanes.py): the admission rule on synthetic per_site records (near-explained ->
    refused, near-unexplained -> admitted, far -> far, a served row refused, a closed-group row refused, --repack and
    --ignore-closed lifting each), the ranking, and that the brief carries the scaffolding sentence verbatim.
 5. report_packs.txt: the rule, the dry-run tables, the two packs' rows, the negatives table, the tests' output; return
    the full text and the paths.`

const VERDICT = {
  type: 'object',
  properties: {
    defects: { type: 'array', items: { type: 'object', properties: {
      severity: { type: 'string', enum: ['blocking', 'major', 'minor'] },
      where: { type: 'string' }, what: { type: 'string' }, evidence: { type: 'string' } },
      required: ['severity', 'where', 'what', 'evidence'] } },
    packs_ok: { type: 'boolean' },
    summary: { type: 'string' },
  },
  required: ['defects', 'packs_ok', 'summary'],
}

const REVIEW = `Refute it. Read the report, the builder, the template and the tests in full; run the tests. Then, independently:
(1) recompute the admission verdict for 12 rows of YOUR choice from per_site.jsonl and src/ (near-explained / near-
unexplained / far / served / closed) and compare with the dry-run tables - a wrong verdict is BLOCKING; (2) check every row
of both packs against served.served_rows() and against ledger.py --closed 0.2 - a served or closed row in a pack is
BLOCKING; (3) read three rows.md sections against per_site.jsonl and the census: a wrong site fact, a cause not labelled
as a compatible mechanism, a missing applicable negative - MAJOR; (4) diff the brief's rule paragraphs against
keep_lane_brief.md: a rule dropped (the cd rule as PROMPT.txt line 1, write-only-in-lane, the scaffolding list verbatim,
the .base_sha output rule, the IO discipline, the compile cap) is BLOCKING; (5) confirm the builder cannot launch (no call
to launch_lane.sh or codex) and that base/ holds the CURRENT src text. Do not fix anything. Return only defects you
demonstrated with evidence, whether the two packs are launchable as built, and a summary.`

const r = await agent(`${RULES}\n\n${SPEC}`, { label: 'impl:packs', phase: 'Implement', model: 'opus', effort: 'high' })
const v = await agent(`${RULES}\n\nYOU ARE THE ADVERSARIAL REVIEWER of tools/lanes/build_catalog_lanes.py and its packs, built to this spec:\n${SPEC}\n\nThe implementer's report:\n${r}\n\n${REVIEW}`,
  { label: 'review:packs', phase: 'Review', model: 'opus', effort: 'high', schema: VERDICT })
const real = (v?.defects || []).filter(d => d.severity !== 'minor')
let fix = 'no blocking or major defects'
if (real.length) {
  fix = await agent(`${RULES}\n\nYou built tools/lanes/build_catalog_lanes.py (spec: ${SPEC}).\n\nYour report:\n${r}\n\nAn adversarial reviewer demonstrated these defects:\n${JSON.stringify(real, null, 2)}\n\nFix each one (or show with evidence that the reviewer is wrong), rerun the tests and the two dry-runs, REBUILD both packs (delete and recreate their directories), append a "Review fixes" section to report_packs.txt and return the full updated report text.`,
    { label: 'fix:packs', phase: 'Fix', model: 'opus', effort: 'high' })
}
return { report: r, verdict: v, fix }
