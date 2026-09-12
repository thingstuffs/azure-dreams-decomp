# Pin-search pilot and restart decision — 2026-09-12

Keep the historical T27 search as the production default inside the new durable controller.
Targeted search found complementary fixes, but did not improve measured throughput. Both
modes are mechanical and make no model calls.

Both comparisons used the same 60 frozen functions: 12 historical recovery controls and
48 rows sampled across compiler/pin-count strata. Per arm and row: 1,200 screen requests,
12 full-verifier calls and 40 CPU seconds, with separate cold caches. CPU totals include
the process and its children; these are not wall-clock or model-usage measurements.

| Trial | Search | Pins removed | Candidate rows | Compiler invocations | CPU seconds |
| --- | --- | ---: | ---: | ---: | ---: |
| v1 | T27 baseline | 23 | 11 | 40,515 | 692 |
| v1 | Full menu with family ranking and near fallback | 23 | 11 | 39,726 | 903 |
| v2 | T27 baseline | 23 | 11 | 40,538 | 673 |
| v2 | Selective generators and fairer group budgets | 23 | 12 | 29,922 | 713 |

V1 spent 191 nonzero-distance fallback verifies without a fallback win. V2 reduced this
to 40 and generated fewer unrelated candidates. It used 26% fewer compiler invocations
but about 6% more CPU for the same pin reduction. This small sample does not establish
a universal algorithm ranking; it does not support replacing the production default.

All affected overlay windows passed in both arms of both trials. V2 targeted also found
a SLUS candidate; that passed an isolated executable build using the exact pinned Ninja
recipe and an explicit image SHA-1 check. The initial controller correctly refused to
call that arm fully gated until full-image validation was added and completed.
Compact tracked evidence: [pin_search_pilot_20260912.json](evidence/pin_search_pilot_20260912.json).
Frozen inputs, implementations, full results and logs remain under `work/pin_search/`.

The production improvements are durable staging/checkpoints, exact run and per-row
identities, reuse of completed work, compressed compilation caches, explicit budgets and
failures, worker cleanup on controller death, and checked publication. A changed source,
recipe, tool or budget invalidates reuse; unchanged rows need not repeat work merely
because other rows changed. Interrupted rows replay frozen input using their caches and
reverified success checkpoints, rather than restoring a serialized beam frontier.

The cc1 screen remains a heuristic. Historical replay confirms one missed exact pair
in 280, with both sources independently verified. Targeted mode has bounded nonzero
fallback verification. Baseline retains its original zero-distance screen: its negative
result is bounded search evidence, never proof that a pin cannot be removed.

## Source harvested from the experiments

Beyond the interrupted run's 49-pin recovery, three functions yielded four more removals:

- `dungeon/func_8125456C`: one pin, using a byte cast and eliminating a pointer copy.
- `slus/w_80046E38`: one pin, storing the selected mask directly in each branch.
- `dungeon/func_8187BB80`: two adjacent KEEP sites erased together from current source.
  The first historical candidate reintroduced an earlier pin, so the paired erasure was
  transplanted to current C and reverified instead, preserving the previous cleanup.

All three passed independent exact verification, source checks, T2/T20 follow-up and
current overlay/full-SLUS gates. Combined with recovery: **53 pins removed across 30
functions**, with no additional fences or detected fake dependencies.

## Bounded model work next

`packets --mode targeted` writes representative inputs, compiler/extent identity,
attempted shapes, stopping reasons and candidate diffs for unresolved families. These
labels are hints rather than diagnoses. Two representatives were read with full retail
diffs during this work:

- `town/func_8080E994`: the nominal addressing lead is actually a missing
  `addiu $a1,$zero,10` in a tail-call delay slot. Investigate the argument/interface
  and control-flow family before trying more unrelated HOST rewrites.
- `dungeon/func_80283F70`: `move $a1,$zero` versus retail's `move $a1,$a2` remains.
  Inspect shared values and live ranges; declaration order alone did not resolve it.

The next model session should explain one family and produce a conservatively guarded
generator with negative cases, then return application and verification to the tools.
No per-function model campaign was launched.
