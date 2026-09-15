export const meta = {
  name: 'r27-lane-ledger-pools',
  description: 'Opus builds the lane ledger and the pool table tools; an opus reviewer refutes each, implementer fixes',
  phases: [
    { title: 'Implement', detail: 'one opus agent per tool' },
    { title: 'Review', detail: 'adversarial opus reviewer runs the tool and checks the data path' },
    { title: 'Fix', detail: 'implementer addresses confirmed defects' },
  ],
}

const RULES = `
Repository: <repo> (run everything from there). Read docs/LANE_KIT.md and tools/lanes/served.py first.
HARD RULES: never write under src/, ledger/sweeps/, config/, build_ovl/; never run gates, sweeps, pin_search.py, apply_candidates.py, land_lanes.sh, launch_lane.sh or any codex/agy command; never run git commands that change state (read-only git log/show is fine). Obey the IO discipline in CLAUDE.md: never search work/ or the repo root recursively; the ONLY work/ paths you may glob are work/native_lane/*/{base,out,candidates}/*/*.c, work/native_lane/*/{BRIEF.md,rows.md,REPORT.md,codex.log,agy.log,PROMPT.txt}, work/alloc_retrace/summary*.json and work/alloc_probe/*/ *.json, and work/pin_search/<tag>/{manifest.json,results/*/*.json} for named tags. A running pin_search (tag deep_pilot_r27_20260915) and a background python process must not be disturbed. Tools go in tools/lanes/, Python 3, no new dependencies, a module docstring in the style of tools/lanes/served.py (what it is for, the commands, what it reads, what it writes). Keep the tool under ~400 lines. Every claim in your final report must come from running the tool on the real repository.`

const SCHEMA = `ledger/lanes.jsonl: one JSON object per lane directory, fields:
  lane (str, dir name), model (str, e.g. gpt-5.6-sol; from the codex.log header line "model: ..." or agy.log, else "unknown"),
  tier (luna|sol|astra|opus|agy|unknown, derived from model or, for opus packs, from BRIEF.md/PROMPT.txt mentioning opus/workflow),
  family (REG|KEEP|FENCE|LAC|SWITCH|PROBE|MIXED|OTHER: from the lane name prefix alloc*/keep*/fence*/lac*/switch*/probe* and BRIEF.md),
  stratum (str: for alloc lanes the "stratum **allocN**" marker in rows.md, majority over rows, else the lane family name),
  rows_served (int: base/*/*.c count), rows_exact (int: out/*/*.c count), rows_landed (int: records with "outcome":"applied" in ledger/sweeps/lane_<lane>.jsonl, else 0),
  pins_before / pins_after (ints: pin sites via tools/pin_census.py sites_of over base texts, and for each landed/exact row the out text; rows without an out text count their base pins on both sides),
  pins_removed (int), rate (rows_exact/rows_served, float, null when 0 served), started (ISO date from codex.log "session id" neighbourhood or the directory mtime), rows (list of row ids served).`

const ITEMS = [
  {
    key: 'ledger',
    file: 'tools/lanes/ledger.py',
    spec: `Build tools/lanes/ledger.py: THE LANE LEDGER WITH RATES. Every model lane so far lives in work/native_lane/<lane>/ (186 dirs; base/ holds the rows served, out/ the exact outputs with .base_sha, candidates/ non-exact tries; codex.log's header has "model: gpt-5.6-sol" etc; rows.md carries per-row "stratum **allocN**" for register packs; ledger/sweeps/lane_<lane>.jsonl records what landed with "outcome":"applied"). Until now the rate tables in docs/HANDOVER.md were built by hand. The tool:
  python3 tools/lanes/ledger.py build            # (re)writes ledger/lanes.jsonl, incremental: a lane whose base/out/candidates listing and journal size are unchanged is reused from the existing file
  python3 tools/lanes/ledger.py                  # prints a markdown table, one line per lane, newest first: lane, tier, model, family, stratum, served, exact, landed, pins -, rate
  python3 tools/lanes/ledger.py --by stratum|tier|family|tier,stratum   # aggregate table with served/exact/landed/pins/rate, sorted by rate
  python3 tools/lanes/ledger.py --closed 0.2     # strata whose aggregate rate over >= 20 served rows is below 0.2 (these are CLOSED for new packs: print them as a list of "family stratum rate n")
Record schema: ${'${SCHEMA}'}. Read tools/lanes/served.py for how served rows are found and reuse its served_rows(); reuse tools/pin_census.sites_of for pin counts. Unit-test the parsing functions (model line, stratum marker, journal outcomes) with a small pytest file under tools/tests/ using synthetic fixtures in a tempdir - do not depend on real lanes in the test. Run "build" then the three report commands on the real repository and include the --by tier,stratum table and the --closed 0.2 list verbatim in your final report, plus the total lanes/served/exact/landed/pins_removed numbers.`
  },
  {
    key: 'pools',
    file: 'tools/lanes/pools.py',
    spec: `Build tools/lanes/pools.py: THE POOL TABLE. Before any model pack is launched the owner wants one table that lists every remaining pinned row by family and stratum, served versus unserved, with the last measured lane rate on that stratum (round 26 built this by hand three times). Inputs: the current tree's pinned rows (tools/common.py rows() and clean_path(), tools/pin_census.py sites_of() -> per-row counts of ASM_REG*, ASM_KEEP*, fences ASM_SCHED_BARRIER/ASM_MEM_BARRIER, other), served lanes per row (tools/lanes/served.py served_rows()), the register stratum per row (reuse tools/lanes/build_alloc_lanes.py: its collect()/site_reasons()/STRATA over the traces under work/alloc_retrace/raw and the summary files - read that module's docstring and functions; import it rather than re-deriving; if importing it triggers argparse or heavy work at import, refactor minimally and safely so the functions are importable, keeping its CLI behaviour identical), the probe knob class per row when a report exists under work/alloc_probe/missed_small/<container>_<row>.json (one-knob | force-only | no-knob-plan | none; read tools/alloc_probe.py's report format), the near band from the newest pin_search results: for --search-tag <tag> (default: the newest dir under work/pin_search/ that has results/baseline/) read results/baseline/*.json and record min d0 over groups and whether any group's best < d0, ONLY when the result's source_sha equals the current text's sha (else "stale"), and the lane rates from ledger/lanes.jsonl (schema: ${'${SCHEMA}'}; if the file is absent print rates as "-" and say so; do not build it yourself).
  python3 tools/lanes/pools.py                    # the table: rows grouped by (family = dominant pin family, stratum, pin band 1 / 2-3 / 4-8 / 9-20 / 21+) with columns unserved rows, unserved pins, served rows, served pins, near-band rows (min d0 <= 4), last rate on this stratum (from lanes.jsonl aggregated by stratum), and a final TOTAL line that must equal the tree's live pin count (print both and assert equality)
  python3 tools/lanes/pools.py --rows REG alloc5 --band 1-3 --unserved      # row ids (one per line, with pins and min d0) for a pack builder
  python3 tools/lanes/pools.py --json out.json    # the per-row records
It must finish in under 3 minutes on the real tree (cache the per-row site counts keyed by file sha in work/lanes_cache/pools_sites.json; create that dir with a .ignore file containing "*"). Unit-test the band/family/stratum classification with synthetic records under tools/tests/. Run it on the real repository and include the full table and the TOTAL check line verbatim in your final report.`
  },
]

const VERDICT = {
  type: 'object',
  properties: {
    defects: { type: 'array', items: { type: 'object', properties: {
      severity: { type: 'string', enum: ['blocking', 'major', 'minor'] },
      where: { type: 'string' }, what: { type: 'string' }, evidence: { type: 'string' } },
      required: ['severity', 'where', 'what', 'evidence'] } },
    ran_ok: { type: 'boolean' },
    summary: { type: 'string' },
  },
  required: ['defects', 'ran_ok', 'summary'],
}

const results = await pipeline(ITEMS,
  item => agent(`${RULES}\n\nYOUR TASK (implementer): ${item.spec}\n\nWhen done, return: the exact file paths you wrote, how you tested, the verbatim output tables requested, and any data-path caveat you found (e.g. lanes with no model line, journals missing).`,
    { label: `impl:${item.key}`, phase: 'Implement', model: 'opus', effort: 'high' }),
  (report, item) => agent(`${RULES}\n\nYOU ARE THE ADVERSARIAL REVIEWER of ${item.file}, just written by another agent. Its spec:\n${item.spec}\n\nThe implementer's report:\n${report}\n\nRefute it. Read the file in full. Run every documented command on the real repository yourself and compare against independent checks you compute with a few lines of python (e.g. count base/*/*.c and out/*/*.c for three lanes by hand, read one codex.log header, recount pins with sites_of for one lane, recompute the tree's total live pin count independently). Round 26's reviewers found a real defect every time (a wrong direction in a comparison, a fallback applied too late): look for wrong joins (row id vs file name), lanes whose out/ text is exact but never landed, counting a lane's base pins for rows that never had an out, stale caches keyed wrongly, an aggregate rate that divides by the wrong denominator, quiet exceptions that hide rows, and anything that reads outside the allowed paths or violates the IO rules. Do not fix anything. Return only defects you demonstrated with evidence.`,
    { label: `review:${item.key}`, phase: 'Review', model: 'opus', effort: 'high', schema: VERDICT }).then(v => ({ report, verdict: v })),
  (r, item) => {
    const real = (r.verdict?.defects || []).filter(d => d.severity !== 'minor')
    if (!real.length) return { item: item.key, report: r.report, verdict: r.verdict, fixed: 'no blocking or major defects' }
    return agent(`${RULES}\n\nYou implemented ${item.file} (spec: ${item.spec}).\n\nAn adversarial reviewer demonstrated these defects:\n${JSON.stringify(real, null, 2)}\n\nFix each one (or show with evidence that the reviewer is wrong), rerun the unit tests and the real-repository commands, and return the updated verbatim output tables and a per-defect note: fixed / disputed (with evidence).`,
      { label: `fix:${item.key}`, phase: 'Fix', model: 'opus', effort: 'high' }).then(fix => ({ item: item.key, report: r.report, verdict: r.verdict, fixed: fix }))
  })

return results.filter(Boolean)