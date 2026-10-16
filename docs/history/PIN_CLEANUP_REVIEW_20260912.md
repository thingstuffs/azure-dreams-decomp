# Mechanical asm-pin cleanup review — 2026-09-12

Keep the mechanical strategy. Improve work selection, screening and resumability before
increasing search depth or launching another corpus-wide LLM campaign. Use models to explain
representative failures and implement reusable transforms; compilation and gates remain mechanical.

This review inspected the active `azure-clean` checkout at `c35efafb` plus its in-flight T27
changes. The other cleanup checkout is the earlier admission project; only its
dashboard was running. No worker, source, search tool or gate was changed by this review.

## Evidence and current yield

- `STATUS.md` at 07:32 UTC reports 10,641 live pin sites, down from 25,759 at the baseline
  (about 58.7% removed), in 1,648 rows. These are pin-site counts, not a proof that all replacement
  C is free of scaffolding: scheduling fences are a separate debt category.
- T26's completed corpus pass (`work/t26_chain.log`, commit `2d6b680e`) changed 98 of 1,652
  processed rows. Its journal records 176,296 screen compilations, 219 internal verifier calls,
  and 134 pins removed. T2 follow-up brought the reported combined result to 103 rows, 160 pins
  removed and seven rows pin-free. The chain records 81 changed windows MATCH and SLUS MATCH.
- T27 at **08:19:13 UTC**, using a bounded read of `ledger/sweeps/t27_beam.jsonl`: 339 records,
  317 noop, one refusal, 21 applied; 38 pins removed, 418,951 screen compilations and 127
  internal verifier calls. Those changes await completion of the current chain's final gates.
  Records continue arriving; these are a snapshot, not final campaign totals.
- That is approximately 1,316 screen compilations per pin for T26's core pass versus 11,025
  for T27's partial pass. The populations and completion bias differ, so this does not measure
  a controlled speed regression. It does justify measuring marginal yield before expanding T27.
  Internal verifier-call counts exclude the sweep's independent final verification.
- `docs/PIN_PATTERNS.md` already finds 24 macro-family × residue classes covering 80% of
  measured sites, but 2,860 detailed residue signatures. There are few broad mechanisms, not
  evidence for only 24 universal fixes. Its subset study also supports joint removal: 40% of
  measured pairs overlap in affected instructions and 1% cancel some of each other's damage.
- `bash tools/setup.sh --check` passed during review, including 417 assembler tests and
  16 subtests. This checks provisioning; it does not replace final gates for T27's new source.

## Findings that affect the next run

### 1. Resume identity is incomplete

`tools/sweep.py:118` keys completed work on `(row id, input hash)` and also skips successful
output hashes. It does not bind compiler configuration, headers, transform/screen versions or
environment budgets. Exhaustion, screen compilation failure and a completed unsuccessful search
can all become `noop`; refusals are also treated as done.

This matters now: the original T27 launch preceded the 07:37 screen-normalization commit.
Before the 08:09 sharded restart, 122 records existed: 114 noop, one refused, seven applied.
The restart increased the screen budget to 12,000 and scorer budget to 60, but its normal resume
logic still skips unchanged journalled rows. Source hashes alone cannot establish that these
rows received the new search. Applied output hashes also do not mean that the new source was
searched to exhaustion: a successful pass may have stopped at its budget.

Record a run fingerprint covering source/recipe, relevant tool and header hashes, generator
settings and search limits. Record explicit stop reasons and a resumable cursor/frontier for
exhausted searches. Reconsider affected old-screen/budget-limited rows selectively after T27;
do not indiscriminately `--force` every historical failure.

### 2. The cc1 screen is useful but is not a sound rejection proof

`tools/xform/screen.py` says different cc1 assembly cannot produce identical final bytes because
later stages are deterministic. Determinism does not imply a one-to-one mapping: assembly
expansion, scheduling and discarded directives can make different inputs converge.

The project's own replay confirms this: `docs/HANDOVER.md` reports eight misses in 177 known
exact pairs before normalization, then one in 280 afterward (a moved `sw $31`). T26 and T27
invoke the exact verifier only for screen distance zero. The remaining false negative therefore
excludes a real category of winners. T27's distance band can also exclude groups before search.

Keep the cheap screen for ranking. Give each promising group a small fallback allowance for
full verification of its best distinct nonzero candidates, especially scheduling/assembler
residue. Maintain an exact-pair replay suite split by compiler and transform family; sample
screen-rejected candidates to measure recall. Broaden normalization only with evidence, retaining
the exact verifier and physical gates as the authority. Avoid silently turning this screen into
a hard filter in older search passes without checking their historical winners.

### 3. Target the menu and preserve useful alternatives

`t27_beam.py` uses fresh census groups when available, then singles and nearby pairs. It calls
the entire `T15._menu` on each beam member, with group-local source deduplication and fixed
candidate ordering. Earlier groups and generators can consume budgets before later candidates.
The four retained candidates can also be very similar allocation variants.

Use the existing mechanism evidence to rank generator families: allocation changes for register
renames, address/symbol forms for materialization, control-flow shapes for scheduling, and joint
erasures where affected instruction sets overlap. Keep a small exploration allowance for other
families; a classifier is a priority hint, not grounds to declare a function impossible.

Share compile-result caches across groups and restarts, binding candidate input and complete
recipe. Cache generator results as well where profiling supports it. Preserve beam diversity by
transform family or control/dataflow effect. Do not merge all search states just because their
current assembly matches: different C states can enable different later transforms.

First try a bounded set of relevant single transforms; escalate promising unresolved groups to
the beam. Prefer affected-instruction overlap over source-line proximity for group selection.
Refresh stale census evidence only where its expected scheduling benefit justifies the cost.

### 4. Make completion and publication reliable

`sweep.py` still consumes `ThreadPoolExecutor.map` in input order. A slow earlier row delays
journalling later completed rows, even though `one()` may already have written their sources.
`screen.compile_s` has no subprocess timeout. The sharded launcher uses twelve processes with
two threads each, all appending to one journal; it uses bare `wait`, does not collect each child's
exit status, and has no fail-fast shell policy for the whole gate/status chain. Its final `exit $?`
message can describe the last command rather than the success of every worker and gate.

Use completion-order durable records, explicit worker results, compiler timeouts, per-phase
timings and a single writer or per-shard journals. Distinguish interrupted and exhausted work
from no applicable transform. Keep stable bounded process workers for Python-heavy generation
if measurements favor them; adding more threads cannot fix Python generation throughput.

The sweep writes scorer-exact source before the final window gates, whereas `promote.py`
already supports gate-and-rollback for applicable legacy overlay rows. Existing documentation
records scorer-exact/window-mismatch failures. Reuse that transaction model, or stage a batch
and publish only after its required gates succeed. Do not report all current T27 `applied`
records as fully gated results. These are process weaknesses, not evidence that a current
candidate has failed its gate.

### 5. Optimize total cleanup, not just disappearance of ASM macros

T27's fewer-pins/no-more-fences acceptance and the decision to revert fake dependencies are
good. Extend the mechanical debt check to all tracked scaffolding categories. Keep native
syntax checks and exact target checks, but do not equate native syntax acceptance with native
behavioral equivalence or readable variable roles. HOST transformations can reuse a variable
with an unrelated semantic name.

Review each new generator's preconditions and negative cases once, including aliasing, types,
evaluation order and scope/liveness. Flag questionable role reuse for family-level review.
Continue cheap dead-pin and dead-fence passes on changed rows; count net debt and fully pin-free
functions, with gates complete, as the product outcome.

## Recommended sequence

1. Let the current bounded T27 pass finish. Collect every shard's outcome, then require the
   overlay and SLUS gates explicitly. Run T2 and T20 on affected rows, re-gate subsequent changes,
   and publish final net-debt counts. Preserve the source/recipe snapshot and run configuration.
2. Fix resume fingerprints, stop reasons, completion journalling and gate failure propagation.
   Add the screen's bounded nonzero fallback and historical exact-pair regression coverage.
3. Freeze a **60–100 row pilot** spanning compiler cells, mechanism classes, group sizes and
   both near and wider residues. Include budget-exhausted rows and known screen misses.
   Compare current T27 with family-ranked search plus caches on identical inputs and equal
   CPU/scorer budgets. Use separate outputs; no live-tree competition.
4. Measure gated net debt removed, pin-free rows, compile/generation/gate time, cache reuse,
   candidates per win, screen recall and failure reasons. The row `secs` field currently records
   final verification time, not the full search cost. Expand only after measured benefit.
5. Send models only residual families with meaningful population and no existing explanation.
   Prepare one packet containing representative C, erasure diffs, compiler/recipe, pin linkage,
   failed transforms and best candidates. The deliverable is a mechanism, applicability rule,
   reusable generator and negative examples. Validate on held-out family members, then sweep
   mechanically with exact checks for every physical row. No LLM call is needed per candidate,
   per routine failure, or for routine job supervision.

The best first implementation is therefore the small controller/cache/screen correction,
followed by family-ranked search. Replacing the entire source transformer with an AST system
or starting another per-function model campaign has no demonstrated advantage here yet.

## Earlier checkout note

The earlier checkout's `tools/status.py --check` failed: generated status/backlog are stale and admission
receipts report a changed `/usr/bin/python3.12` verification input. Its old 146-admission count
must not be treated as freshly verified. This is separate from `azure-clean`'s active sweep and
does not establish a failure of that sweep. No old receipts were refreshed or weakened.
