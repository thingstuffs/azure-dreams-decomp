# Evidence-led pin research workflow

The target is zero pins. The 6,103-pin / 1,284-row census is a baseline, not a
plateau verdict. A finite search that finds no exact result is a bounded negative:
it rules out only the recorded source forms, recipes, and measurements. An
impossibility claim is admissible only when an architecture or instruction-set
limit is demonstrated and independently reproduced.

The case ledger is
[`docs/evidence/pin_research_cases_20260917.json`](evidence/pin_research_cases_20260917.json).
It starts with the three active investigations and records no landed win; an
exact, reviewed allocator repair remains below the publication gate.
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
