export const meta = {
  name: 'r28-varset-regroute',
  description: 'Opus builds two generators - t64_varset (lifetime split / per-definition inline / merge / retype, learned from the lane-won diffs) and t65_regroute (probe-directed sugg and order-swap register moves) - each refuted by an adversarial opus reviewer, then fixed',
  phases: [
    { title: 'Implement', detail: 'one opus implementer per generator, with unit tests, the reachability replay and lane_eval' },
    { title: 'Review', detail: 'adversarial opus reviewer reruns everything and returns demonstrated defects only' },
    { title: 'Fix', detail: 'implementer fixes blocking/major defects and re-measures' },
  ],
}

const RULES = `
Repository: <repo> (run everything from there; python3 from the repo root). Read first: docs/LANE_KIT.md;
tools/xform/t57_keepafterstore.py (the generator contract: class T with name/level/needs_verify, eligible(text,row,census),
apply_verified(text,row,census,vf)); tools/xform/t63_memdep.py (the newest generator in that contract: its screen/vf budget,
journal fields, restart-on-win); tools/xform/natural.py (menu generators *_candidates(text) -> [(label, text)]: splitcursor,
host, hostwide, unhost, declorder, dropcopy are the EXISTING variable-set moves); tools/xform/t51_sched_order.py
(declarations(), units(), mask(), candidates(): fuse / single-set / move / commute); tools/xform/t60_alloc_inputs.py
(reuse_candidates: two disjoint straight-line same-type lifetimes merged); tools/xform/t53_reg_state.py (extra_candidates:
width and decl-swap; a two-rewrite pass-stream beam); tools/xform/reg_state.py (observe/metrics: the pass-stream distance);
tools/xform/screen.py (compile_s/sdiff: the free cc1 screen); tools/pin_search_engine.py (improves()); tools/pin_census.py
(sites_of, unscored_text, asm_blocker); tools/pin_sites.py (erase_many); tools/lane_eval.py --help; tools/common.py (rows()).
HARD RULES: never write under src/, ledger/, config/, build_ovl/; never run sweep.py, gates, pin_search.py, apply_candidates.py,
land_lanes.sh, launch_lane.sh, codex or agy; never run state-changing git (read-only git show/log is fine). The IO discipline
in CLAUDE.md applies: no recursive search over work/ or the repo root; grep only tools/, include/, docs/, your lane directory
and toolchain/gcc-src/<one version>/ with --max-filesize 4M. Write only under tools/xform/, tools/tests/, tools/lanes/ and
your lane directory (given below; create scratch/ and tmp/ inside it, each with a .ignore file containing "*"). At most 8
compiles at a time (lane_eval --jobs 6). Other jobs share the machine (two codex lanes probe3/probe4, a finished pin_search
changed_r27_20260915, reach2.py replay processes): do not kill, wait on, or read their directories. No scaffolding may ever
appear in a candidate: no new ASM_* macro, __asm__, volatile, fake dependency, do{}while(0), while(0), for(;0;) or any
one-trip block, no new #pragma or attribute, no edit inside an #ifdef NON_MATCHING / port / dead arm (unscored_text(candidate)
must equal unscored_text(text)). A candidate must compile at the row's cell. A candidate may never drop or add a
qualifier (volatile/const), change a width, a signedness, an offset or a symbol: the screen cannot see a dropped volatile
(round 27's blocking defect). Only vf accepts a candidate; everything else is ranking.`

const EVIDENCE = `EVIDENCE ALREADY MEASURED (read these files, do not redo them):
- work/native_lane/r28_dev/ex/reg/ and .../ex/KEEP/: every landed diff of the last 60 commits that lowered the register
  (403 lane-won, list lane_won.txt) or keep (220) count with a body change (INDEX.md: commit, row, generators, diff file;
  a diff's pre text is \`git show <commit>~1:src/<row>.c\`, its post text \`git show <commit>:src/<row>.c\`).
- .../ex/reg/lane_won.txt.declmoves.json and .../ex/KEEP/lane_won.txt.declmoves.json (tool: .../tools/declmoves.py): the
  declaration-level move inventory. REG (403 diffs): RETYPE-int 50, SPLIT 43 (an added local takes one definition of an
  existing local), INLINE 31 + INLINE? 47 (a removed local whose defining expression now sits at its uses), MERGE-local 24,
  MERGE-param 8, RENAME 9, CTRL 76 (labels/gotos/loops changed), PARAM 13, no declaration change at all 113. KEEP (220):
  CTRL 64, RETYPE-int 39, INLINE 19 + 31, SPLIT 11, none 51.
- .../tools/reach2.py: the depth-2, rename-invariant menu reachability replay (skeleton = pins erased, comments gone,
  locals alpha-renamed by first appearance, declaration runs sorted; distance = token edit distance; depth 1 = the whole
  current menu on the pre text, depth 2 = the menu on the 12 nearest depth-1 texts). Its results on the same 120 register
  rows round 27 replayed at depth 1 (1 of 120 reached) are in .../reach2_reg.json with hit1/hit2 (the reaching family),
  best1/best2 (nearest distance, a lower bound: only the 40 nearest by token bag are measured) and d_base; the summary is
  at the end of .../reach2_reg.log: on 118 of the 120 rows at the time of writing, depth-1 exact 7 (t51 single-set 4, gotoloop 1, t51 move 1, t51 fuse 1),
  depth-2 exact 6 (dropcopy+armstore, hostwide+hostwide, dropcopy+dropcopy, basesym+basesym, fuse+fuse, fuse+width), closer
  60, no-closer 45; median distance reduction on the unreached 9%, 29 of 105 halfway; the reached rows are the SMALL diffs
  (d_base 8-27 tokens for 9 of 13, median unreached d_base 48); the nearest families on the unreached: t53 width 6,
  dropcopy 4, single-set 4, hostwide 3, narrow 3. The keep replay (100 rows, reach2_keep.json / reach2_keep.log) may
  still be running when you start: use it only once its log ends with the "median reduction" summary line, and never wait
  on or kill its processes. So with rename invariance and depth 2 the CURRENT menu reaches about one lane-won register
  text in nine under oracle ranking (the replay ranks by distance to the known answer, which the search cannot do); the
  search itself, ranking by assembly distance, reached none of these rows when it ran on them. Both levers are therefore
  in play: the ranking (item b below) for the reachable ninth, new moves for the rest.
- .../rows/: frozen row lists from the pool table (tools/lanes/pools.py --json): reg_near_1_8.txt (298 register-dominant
  rows, 1-8 pins, fresh search result within 4 asm lines), keep_near_1_8.txt (215), probe_sugg_1_8.txt (145 rows with a
  register site whose minimal sufficient allocator knob is a missing SUGGESTION), probe_order_1_8.txt (93 rows, ORDER-SWAP).
- work/alloc_probe/reg_all/<container>_<func>.json: the allocator counterfactual probe per row (tools/alloc_probe.py
  docstring): per ASM_REG site \`var\`, \`register\`, \`line\`, \`owner\` (local|global), \`minimal_knob\`, \`competitor\` /
  \`competitor_names\`, \`attempt_labels\`.
- Round 26/27 negatives you must not repeat: \`pref\` on a saved register is unreachable (a bare copy is coalesced before
  allocation, so no preference forms); the CPU search is menu-limited (deep beam 0/39); t53/t60/t51 single-set/splitcursor/
  reuse exist and were in the replayed menu, so a move that only duplicates them adds nothing - measure the DELTA.`

const SPEC_A = `YOUR LANE DIRECTORY: work/native_lane/r28_dev/ (exists; write under it only, plus tools/xform, tools/tests, tools/lanes).
BUILD (1) tools/xform/varset.py, a pure text move library, every function \`<move>_candidates(text, focus=None) -> [(label,
text)]\` (focus = a variable name; None = every local), deterministic, bounded (<= 48 candidates per move per call, the ones
nearest the focus first), using t51.units()/declarations()/mask() and natural's helpers where they fit:
  inline_def: for a local V with N >= 1 definitions \`V = E;\` (E without calls, ++/--, volatile, or V itself), for ONE definition
    at a time: substitute E at every use that only that definition reaches, delete the definition, and delete the declaration
    when no definition remains; E's operands must not be assigned between the definition and each use; uses reached by
    another definition, or through a loop back-edge, refuse the candidate. (t51 fuse only takes the NEXT statement's sole use;
    natural dropcopy only \`x = y\` copies. The lanes inlined multi-definition temps whose uses sit several statements later,
    across labels: see ex/reg dungeon_func_80CEB850.2c41d45a.diff.)
  split_def: for a local V with >= 2 definitions, give ONE definition and the uses only it reaches a fresh name (V + "_2",
    the same type, declared right after V's declaration), refusing when a use is reached by two definitions or the region
    crosses a loop back-edge that carries V. (t51 single-set covers only a straight-line run of <= 10 statements; the lanes
    split at labels and across arms: ex/reg town_func_800BC8AC.27e12c0f.diff turned one \`page\` into six.)
  merge_local: two locals of the identical declared type whose live ranges are disjoint on the CONTROL-FLOW graph (not
    straight-line only: t60 reuse already does that), the later renamed to the earlier, both naming directions.
  merge_param: a local whose every definition is reached before any later use of parameter P of the same type, and P is
    dead after the local's first definition: the local becomes P (and the reverse: a parameter copied once into a local of
    the same type where the copy is the only definition - keep both alive by using the local everywhere after the copy).
  retype_ptr: a local declared \`M2C_UNK *\`, \`void *\`, \`u8 *\` whose every dereference casts it to one struct pointer type
    \`(S *)v->f\` -> declare it \`S *\` and drop those casts (address arithmetic on it must stay byte-identical: refuse when it is
    indexed or offset by a non-constant).
  Build the reachability on a statement-level control-flow graph you derive from t51.units() (labels, goto, if/else, loops,
  switch/case, return; conservative: an unknown construct makes every later statement reachable). Struct members
  (\`->name\`, \`.name\`), macro arguments, labels, string contents and identifiers inside #ifdef arms are never renamed.
BUILD (2) tools/xform/t64_varset.py in the t57 contract (name "t64_varset", level 1, needs_verify True) exposing also
\`varset_candidates(text)\` for the engine menu: for each live ASM_REG / ASM_KEEP / ASM_KEEP_NV site (nearest-first, the pin's
variable as focus), depth 1 = the varset moves on that variable and its neighbours, plus the existing menu (natural
GENERATORS, t51.candidates at the site, t53 extra_candidates, t60 reuse_candidates); each candidate is tried with the site's
pin erased (erase_many, clean_notes=True; re-read sites_of on the new text) and screened by compile_s/sdiff against the
current pinned listing; vf ONLY on distance-0 candidates that pass pin_search_engine.improves (t53's finding: every win was
accepted on its first, assembly-identical vf call; scoring non-identical candidates never won). Depth 2 = the same menu on the
8 nearest depth-1 texts, ranked by (screen distance, then reg_state.metrics pass-stream distance on the row's deciding pass,
combine and greg as t53 does). Budgets T64_SCREENS (600) and T64_VERIFY (6) per row, journaled like t63 (pins_in, pins_out,
screened, tried, candidates_n, nearest distances, step labels, per-move counts and skip reasons); restart on the new text
after a win. Unit tests tools/tests/test_varset.py and test_t64_varset.py: every move on synthetic texts, AND the refusals: a
split whose use is reached from another definition through a label, a loop back-edge carrying the variable, an
address-taken local (&v), a struct member with the local's name, a same-named inner-scope local, a local referenced inside
an #ifdef arm, a \`register ... ASM_REG\` declaration (never retyped or merged), volatile/const qualifiers preserved.
EVALUATE, in this order, and put every table in work/native_lane/r28_dev/REPORT_A.md:
  (a) Reachability delta: add varset's moves to reach2's menu (copy .../tools/reach2.py to reach2_varset.py; do not edit
      the original) and rerun on the SAME 120 register rows (seed 1) and 100 keep rows: hit1/hit2 before vs after, and for
      the rows newly reached, which move. Also re-classify the still-unreached rows with .../tools/declmoves.py output:
      which inventory classes remain out of reach.
  (b) Ranking audit on every row reached at depth 2 (before or after): compile the pre text (pinned, exact), the correct
      depth-1 intermediate with the pin erased, and the bare erasure; report the intermediate's screen distance and
      pass-stream distance against the bare erasure's, and its rank among all depth-1 candidates under each ranking. The
      question the search needs answered: is the correct first step within the top 4 by screen distance, by pass-stream
      distance, or by neither (a valley)?
  (c) lane_eval: python3 tools/lane_eval.py --lane work/native_lane/r28_dev --module tools/xform/t64_varset.py --jobs 6 on
      the first 100 rows of rows/reg_near_1_8.txt (tag t64_reg) and the first 60 of rows/keep_near_1_8.txt (tag t64_keep):
      rows eligible, candidates per row (median), screened, exact outputs (row id, pins before/after, the move labels),
      and for 10 misses the nearest distance and residue. If exact is zero, take three near-misses through
      tools/xform/sched_trace.py (compile_text with dumps) and say what the intermediate changed in the dumps - a bounded
      negative with a reason is a valid result.
Do not touch tools/sweep.py, pin_search_engine.py, natural.py, t51/t53/t60 or land_lanes.sh. Return: file paths, the test
output, the three evaluation tables verbatim, every skip-reason count, and the ranking-audit verdict in one sentence.`

const SPEC_B = `YOUR LANE DIRECTORY: work/native_lane/r28_probe/ (create it; write under it only, plus tools/xform, tools/tests, tools/lanes).
THE MECHANISM, to confirm from toolchain/gcc-src/2.7.2 before designing (do not take it from this text): local-alloc.c
1792-1834 (block_alloc's copy handling) sets qty_phys_sugg[qty] |= R when an insn copies the pseudo to or from hard register
R (qty_phys_copy_sugg when the other side is a pseudo already tied to R); find_free_reg tries suggested registers before
priority order (local-alloc.c ~1469-1477, just_try_suggested). Before reload, hard registers appear in this port's RTL only
as: $4-$7 copied INTO pseudos at function entry (the parameters), pseudos copied OUT to $4-$7 as call-argument setup, $2
copied out of a call result (\`V = f(...)\`) and into the function's return (\`return V;\`), and whatever mips.md ties to $3
(find out: the probe names $3 on 34 of 175 sugg sites; check what expands to a (reg 3) before reload in 2.7.2 mips.md/mips.c,
e.g. the second word of a DImode value, a division or a compare helper). global.c allocno_compare: priority =
floor_log2(n_refs) * n_refs / live_length * size, ties by allocno number; the probe's order-swap knob exchanged the target
with a NAMED competitor in that order, so the C moves are: one fewer or one more REAL reference on the target or the
competitor (inline a single-use definition; hoist a repeated expression into the variable), a shorter or longer lifetime
(split at a redefinition; sink a definition to its first use; merge a neighbour into it), never a fake use.
The probe records (work/alloc_probe/reg_all/<container>_<func>.json, format in tools/alloc_probe.py's docstring): per
ASM_REG site \`var\`, \`register\` (the hard register retail used), \`line\`, \`owner\` (sugg sites are all local; order-swap
sites all global), \`minimal_knob\`, \`competitor\` (found, source) and \`competitor_names\` (pseudo -> C name where known).
BUILD tools/xform/t65_regroute.py in the t57 contract (name "t65_regroute", level 1, needs_verify True): eligible only when
the row has a probe report whose sha equals the current text and at least one site with minimal_knob in (sugg, order-swap)
(else return the reason). For each such site, targeted candidates, tried with that site's pin erased and screened by
compile_s/sdiff against the pinned listing, vf only at distance 0 and improves():
  sugg $2/$3: (i) \`return E;\` -> \`V = E; return V;\` when V's type matches and V is dead there; (ii) \`W = f(...); V = W op K\`
    -> V receives the call directly where the algebra allows; (iii) \`return V op K\` -> the operation done before through V;
    (iv) V assigned from the call whose result the text stores elsewhere first. sugg $4-$7 (argument k = R-4): (i) a call
    whose argument k is an expression E with V's value -> \`f(.., V, ..)\`; (ii) \`f(.., V op K, ..)\` -> \`V = V op K; f(.., V, ..)\`
    when V is dead after (a real redefinition, not a copy); (iii) V is a copy of parameter k or parameter k is dead after
    V's definition -> merge V into the parameter (both directions: rename the parameter's later uses to V, or V's uses to
    the parameter); (iv) the parameter copied into V at the top (\`V = param;\`) with the parameter used nowhere after.
  order-swap (target T, competitor C when named): inline T's single-use definitions; split C at its redefinitions; split T;
    sink T's definition to its first use; merge T with a same-type neighbour whose lifetime is disjoint; the same on C. You
    may reuse t51.candidates (single-set, fuse, move), natural.splitcursor/host/unhost and t60.reuse_candidates by import;
    do not import tools/xform/varset.py (another agent is writing it now; a race).
Budgets T65_SCREENS (400) and T65_VERIFY (6) per row, journaled like t63 (per site: knob, register, var, candidates by move,
nearest distance, skip reasons). Unit tests tools/tests/test_t65_regroute.py: each move on synthetic texts, the refusals
(V live after, parameter used after the merge point, a call argument that is not V's value, volatile/const kept, no edit in
#ifdef arms), and the probe-report gating (stale sha -> ineligible).
EVALUATE with tools/lane_eval.py --lane work/native_lane/r28_probe --module tools/xform/t65_regroute.py --jobs 6 on the
first 80 rows of work/native_lane/r28_dev/rows/probe_sugg_1_8.txt (tag t65_sugg) and the first 60 of
.../rows/probe_order_1_8.txt (tag t65_order). Report in work/native_lane/r28_probe/REPORT.md: rows eligible, sites by knob
and register, candidates per site (median), screened, exact outputs (row, site, knob, register, move label, pins
before/after), and for 10 misses the nearest distance and what the residue holds. If exact is zero on a class, take three
misses through tools/alloc_trace.py <row> --source <candidate> (the allocator observer: does the candidate CREATE the
suggestion / change the order as intended, and if so why is the assembly still different?) - the answer bounds the class.
Do not touch tools/sweep.py, pin_search_engine.py, natural.py, t51/t53/t60 or land_lanes.sh. Return: file paths, the test
output, both evaluation tables verbatim, every skip-reason count, and the $3 finding.`

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

const REVIEW_CHECKS = `Refute it. Read the generator (and its library) in full. Run its unit tests. Take five of its exact
outputs (or, with fewer, its five nearest candidates from the lane's evidence/) on real rows, compile the original and the
candidate through tools/xform/screen.py and diff the C texts by hand: any dropped or added qualifier (volatile/const), a
changed width, signedness, offset, symbol, or an edit inside an #ifdef NON_MATCHING / port / dead arm is BLOCKING; so is a
rename that captured a struct member, a macro argument, a label, a same-named inner-scope local, or a use reached from another
definition (a split or inline that changes the value: construct one synthetic case per move and show what the tool does).
grep the out/ files for ASM_, volatile, __asm__, while (0). Check budget accounting (screened/tried never exceed the limits),
that eligible() refuses rows with asm_blocker, that a win restarts on the new text with sites re-read, and that the journal's
skip reasons add up to the eligible count. Re-run lane_eval on 20 rows of your own choice (rows the implementer did NOT
evaluate: take them from further down the same row lists) with a new tag and report its exact count independently; re-run
the implementer's reachability or ranking table on 30 rows and compare. Do not fix anything. Return only defects you
demonstrated with evidence, and the exact-row count you confirmed by reading vf results yourself.`

const ITEMS = [
  { key: 'varset', file: 'tools/xform/varset.py + tools/xform/t64_varset.py', spec: SPEC_A },
  { key: 'regroute', file: 'tools/xform/t65_regroute.py', spec: SPEC_B },
]

const results = await pipeline(ITEMS,
  item => agent(`${RULES}\n\n${EVIDENCE}\n\nYOUR TASK (implementer): ${item.spec}`,
    { label: `impl:${item.key}`, phase: 'Implement', model: 'opus', effort: 'high' }),
  (report, item) => agent(`${RULES}\n\n${EVIDENCE}\n\nYOU ARE THE ADVERSARIAL REVIEWER of ${item.file}, just built by another agent to this spec:\n${item.spec}\n\nThe implementer's report:\n${report}\n\n${REVIEW_CHECKS}`,
    { label: `review:${item.key}`, phase: 'Review', model: 'opus', effort: 'high', schema: VERDICT }).then(v => ({ report, verdict: v })),
  (r, item) => {
    const real = (r.verdict?.defects || []).filter(d => d.severity !== 'minor')
    if (!real.length) return { item: item.key, report: r.report, verdict: r.verdict, fixed: 'no blocking or major defects' }
    return agent(`${RULES}\n\n${EVIDENCE}\n\nYou implemented ${item.file} (spec: ${item.spec}).\n\nAn adversarial reviewer demonstrated these defects:\n${JSON.stringify(real, null, 2)}\n\nFix each one (or show with evidence that the reviewer is wrong), rerun the unit tests and the main lane_eval evaluation with a new tag (${item.key}2), and return the updated tables and a per-defect note: fixed / disputed (with evidence).`,
      { label: `fix:${item.key}`, phase: 'Fix', model: 'opus', effort: 'high' }).then(fix => ({ item: item.key, report: r.report, verdict: r.verdict, fixed: fix }))
  })

return results.filter(Boolean)
