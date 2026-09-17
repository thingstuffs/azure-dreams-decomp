# Evidence-led pin research workflow

The target is zero pins. The 6,103-pin / 1,284-row census is a baseline, not a
plateau verdict. A finite search that finds no exact result is a bounded negative:
it rules out only the recorded source forms, recipes, and measurements. An
impossibility claim is admissible only when an architecture or instruction-set
limit is demonstrated and independently reproduced.

The case ledger is
[`docs/evidence/pin_research_cases_20260917.json`](evidence/pin_research_cases_20260917.json).
It records the current individual repairs and unresolved investigations, with
live source hashes and publication receipts for each completed repair.
[`tools/pin_research.py`](../tools/pin_research.py) validates the ledger against
the live source tree and enforces the evidence gates below. It does not compile,
edit source, or promote candidates.

## Working loop

1. Freeze the case identity. Record the live source path and SHA-256, the retail
   row/function identity, and the fixed compiler/assembler recipe. Give both
   identity and recipe a confidence with a concrete basis. Source and recipe are
   separate variables; an exact result at another stock cell does not by itself
   prove either a source repair or a recipe correction.
2. Rubber-duck the compiler decision before compiling. State the causal question,
   the relevant compiler inputs (source roles, live ranges, pass state, instruction
   constraint), and a prediction that a dump or exact-byte result can falsify.
   Ask what ordinary original source would make the retail result fall out
   naturally.
3. Run one bounded experiment. Record the exact menu, cells, controls, score,
   first divergent pass, and retained artifacts. A failure must say both what was
   tested and what remains untested. Do not turn “the menu failed” into “C cannot
   express this.”
4. Treat an exact output as a `positive_candidate`. Keep the case
   `experiment_ready` until the candidate is reproduced at a justified fixed
   recipe and its semantics and callers are reviewed. Exact bytes can expose a
   useful coincidence while leaving source/recipe attribution unresolved.
5. Move to `repair_verified` only after exact bytes, semantic review, and caller
   review pass. Bind the candidate file and hash to the current source hash and
   recipe, and cite existing repository artifacts for each passing review. Caller
   review may be `not_applicable` only when the change cannot affect an interface
   or a consumed result.
6. Before a family transfer, write the rule in terms of source facts and compiler
   behavior. Select a distinct independent positive control that should reproduce
   the repair and a distinct independent negative control that should reject it.
   Bind both controls to live source paths, source hashes, and expected outcomes.
   This is the entry gate for `transfer_testing`.
7. A transferred repair reaches `resolved` only when both controls start from
   exact baselines and produce their expected independent outcomes: the positive
   repair is exact, while the negative repair is rejected or mismatches as
   predicted. Every accepted target also needs semantic/caller review and the
   affected overlay window or SLUS image gate. A non-transfer repair has the same
   exact-byte, review, and publication requirements. Only `resolved` cases
   satisfying these checks are reported as landable.

The old hard-gap method remains the useful research posture: read the compiler
pass and dumps, enumerate ordinary late-1990s C idioms, and probe one mechanism at
a time. Compiler walls remain owner-level conclusions. This ledger adds durable
identity and state gates so that later family work can reuse a causal result
without inheriting an untested story.

## Compiler fingerprint scope

Use the repository-local `tools/lineage_fingerprint.py` with an explicit
`--overlay`. Run it with an available Capstone-enabled Python environment;
the reference checkout's virtualenv provides one. For a data-prefixed row,
provide its measured `--body-offset` and `--body-size`. Never treat bank data
as compiler instructions.

A store in a call/jump delay slot is scheduling evidence, not by itself compiler
family evidence: ordinary object-local stores can occupy such slots under plain
2.7.2. Round 50 preserves a pin-free compiler probe proving this. Check the
actual access form and address provenance before inferring macro versus split
symbol emission. The tool's remaining signatures are heuristics requiring
instruction-level review; no score or family hint proves an exact historical
release. Do not ignore contradictory evidence merely because pinned C matches.

## Status meanings

| Status | Required evidence |
|---|---|
| `unresolved` | Current identity, causal question/prediction, and a concrete bounded next experiment. |
| `experiment_ready` | At least one evidence receipt plus the same concrete next experiment fields. An exact but unattributed candidate stays here. |
| `repair_verified` | Exact bytes pass; semantic review passes; caller review passes or is inapplicable. Publication may still be pending. |
| `transfer_testing` | A verified origin repair, a stated family rule, and distinct independent positive and negative controls bound to source hashes. |
| `resolved` | All repair gates, both enabled transfer-control outcomes from exact baselines, and the overlay-window or SLUS-image publication gate pass. `next_experiment` is null. |

The case `claim.level` is separate from its workflow status. `unresolved` leaves
the causal question open, `bounded_negative` summarizes a finite negative result,
and `verified_repair` names a resolved individual repair without implying family
transfer. `impossibility` requires an `architecture_limit` evidence item
containing the specific architecture or instruction constraint, its demonstration
and reproduction, and independent confirmation. The validator rejects an
impossibility claim supported only by failed searches.

## Ledger fields that carry the proof

Each case records:

- `source.path` and `source.sha256`: the current compiler input identity. A stale
  hash blocks every CLI view, so old evidence cannot silently attach to new text.
- `retail.identity` and `retail.recipe`: the target and how it is built, each with
  confidence and basis.
- `causal.question` and `causal.prediction`: the mechanism under test and an
  observable prediction.
- `evidence`: observations, bounded negatives, positive candidates, or the much
  stronger architecture-limit receipt. Evidence IDs are unique per case and each
  item names an existing repository artifact path (plus an optional `#anchor`).
- `candidate`: required from `repair_verified` onward; its live file, output
  SHA-256, base-source SHA-256, and recipe prevent a proof for one
  candidate/source pair from being attached to another. The case's current source
  must still be the recorded base or the landed candidate.
- `next_experiment`: action, measurement, success and failure criteria, and a
  finite bound. Every open case must have all five.
- `verification`: exact bytes, semantic review, caller review, publication gate,
  and per-gate references to the relevant evidence IDs. A pass without a durable
  referenced artifact is rejected.
- `transfer`: disabled until a verified repair has a causal family rule and two
  independent controls. Neither control may be the exemplar. Each records an
  exact baseline, the observed result, and evidence references backed by existing
  artifacts; the negative mutation is expected to reject or mismatch and is not
  required to become exact.

When source changes, do not merely refresh its hash. First decide which evidence
still describes the new text, move superseded observations into a bounded receipt
or a new case, then record the new SHA. This prevents a successful experiment on
one source version from becoming proof for another.

## Commands

Run these from the repository root:

```sh
python3 tools/pin_research.py validate
python3 tools/pin_research.py list
python3 tools/pin_research.py next
python3 tools/pin_research.py show dungeon/func_81811388
```

`validate` exits nonzero for stale source hashes, missing next actions, unbounded
negative evidence, insufficient repair reviews, incomplete transfer controls, or
an unresolved publication gate on a resolved case. `list` shows status, claim,
recipe, and derived landability. `next` prints the bounded action and measurement
for every open case. `show` emits one validated case as JSON.

The focused tests run with:

```sh
.venv/bin/python -m pytest -q tools/tests/test_pin_research.py
```

Before marking a real case resolved, also run the repository's normal independent
row verifier, affected overlay-window or SLUS gate, row database check, and any
caller-specific windows required by the change. Put those durable receipts in the
case rather than replacing them with the CLI's validation result.

## Whole-function reconstruction with a different stock recipe

The automatic `apply_candidates --cells` / `pin_cells_land` path remains for
simple cell corrections: both the original pinned source and the candidate
must be exact at the proposed cell. Do not weaken that check or call a matching
recipe proof of the original compiler release.

A full reconstruction is a different reviewed change. Artificial source and
recipe choices can have evolved together, so neither cross-combination needs
to be exact. Acceptance requires both valid endpoints: current source at its
recorded recipe and reconstructed ordinary C at the proposed stock recipe.
Record the cross-combinations as diagnostic controls, not as publication gates.
Use full verifier summaries for length and score; a truncated diff listing is
not a complete endpoint check.

For a reviewed reconstruction, bind old/new source hashes, old/new recipes,
retail identity/hash, compiler mechanism evidence, and semantic/caller reviews.
The new source must remove the claimed pins without substitute asm, volatile
accesses, fake dependencies, literal platform bindings or ABI shortcuts. Report
historical lineage uncertainty separately from the reproducible build recipe.

After independent verification and review, apply the hash-bound source and
recipe together through `common.set_row_cfgs`, journal the explicit
`whole_c_reconstruction` transition, and immediately verify the live row using
the exported recipe. Coordinate shared exports with other compiler lanes.
Complete every affected overlay/SLUS and caller gate plus the row database
check. If live verification or a required gate fails, restore both the source
and its prior recipe and verify the restored endpoint. A low-level setter is
not an approval substitute: retain the review and exact endpoint receipts in
the journal and research case. This path does not enable unreviewed flag search.

## Mechanical fixed-copy probes

Use `tools/aggregate_copy.py` to recognize and generate a small set of ordinary
aggregate assignments from canonical fixed 16-byte copy loops and contiguous
word tails. This is an advisory candidate generator, not a C semantics proof.
Its measured population and refusal controls are in the round-42 report.
Object extent, non-overlap, effective type, actual callers and the meaning of
removed barriers still require review. Unknown or refused shapes are research
handoffs, not impossible cases.

`tools/aggregate_copy_probe.py` takes a JSON manifest selecting each row,
source and stock recipe explicitly. It accepts at most five rows and four
recipes per row, including the recorded recipe. It generates at most four
candidates per row, records source hashes and complete byte-comparison
summaries, and tests the unchanged source at every selected recipe. Historical
source snapshots remain visibly distinct from live source. An exact candidate
stays unreviewed; this command never promotes it or edits production source,
recipes or ledgers.

```sh
python3 tools/aggregate_copy_probe.py path/to/manifest.json --output work/native_lane/new_copy_probe
.venv/bin/python -m pytest -q tools/tests/test_aggregate_copy.py tools/tests/test_aggregate_copy_probe.py
```

Use a fresh output lane. Generated candidate files go beneath its ignored
`raw/` directory. Promote only after the normal independent source/caller review,
hash checks, exact verification and affected publication gates. Mechanize the
recognized repetition; spend reconstruction effort on refused or nonexact
cases only when a concrete new source or compiler fact motivates the next probe.

## Bounded whole-function workers

Gemini is available through the local `agy` CLI; the existing launcher and
harvester live in `~/agy_lane/`. Use a fresh, frozen function pack rather than
reusing an old live-source batch. The round-48 and round-49 receipts record
actual Gemini results and timeout behavior. A zero CLI exit after a print timeout
is not proof that the worker completed its experiment.

Give Luna or Gemini one complete function, its full retail map, baseline source
hash, proven runtime identity, recorded recipe, actual helper signatures and
object relationships. Ask for an explanation of the operation and at most six
source hypotheses. Save every candidate and full score immediately, then return
the best candidate and a concrete unresolved compiler question. Workers must not
edit production source, recipes, shared exports or gates. Enforce the time bound
in the launcher and preserve partial artifacts if it fires.

Root review checks callee contracts and residual ownership before adding probes.
Round 50 illustrates the division: Luna reached a zero-pin source with two
reorder indels; the real one-argument helper signature closed the remaining
schedule difference in one source change. Root then performed independent
review and publication gates. This is evidence that bounded delegation can
contribute useful C reconstruction, not a measured success rate for all pins.
