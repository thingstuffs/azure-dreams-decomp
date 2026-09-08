# Astra and Claude efficiency: advice for the next maintainer

Written 2026-09-08 after reviewing the campaign harness, journals, documentation, and a live
Astra lane. This is a proposed improvement programme, not an implemented change or a measured
speedup. The review did not interrupt the campaign or modify its sources, prompts, or gates.

The main opportunity is to reduce repeated context discovery and orchestration per function.
Keep the existing strategy: machines apply reusable transforms; agents supply naming judgement
and solve the residue; independent compilation and the applicable retail gates prove changes.
Start with a small comparison before changing model routing or scaling a new workflow.

## Evidence from the review

Snapshot of `ledger/agents/gpt-6-astra-high-campaign.jsonl` at approximately 12:52 UTC:

| Population | Attempts | Summed agent time | Input tokens | Cached input tokens |
|---|---:|---:|---:|---:|
| Whole campaign | 4,509 | 53.57 hours | 363,572,794 | 312,817,152 |
| Functions with retail size <=100 B | 919 | 10.77 hours | 70,546,280 | 61,752,576 |

These are cumulative model-input counts across turns, not unique prompt sizes or billing
amounts. Cached tokens are included in input tokens. Time is the sum of each `codex exec`
duration, including its tool waits, not elapsed campaign time; it excludes the harness's
subsequent verification and promotion. The campaign was still running, so later counts differ.
The full snapshot contained 4,496 accepted, 11 rejected, and 2 unchanged attempts. Accepted
does not necessarily mean landed; use the promotion journal for product progress.

Concrete observations:

- A live lane for `town/func_804712B4` received a nine-line wrapper, reread it, and added one
  summary comment. It received a fresh general Codex session, including skill and plugin
  guidance, for that task.
- A recent lane for `town/func_800CF9CC` spent 176,174 input tokens, 156,544 cached, and 62.6
  seconds. It searched a nonexistent `overlays/` directory, listed configuration files, read
  the verifier implementation, and found a related source before editing a seven-line file.
  The useful callee investigation should be made easier, rather than forbidden.
- Among accepted records with pin telemetry, 319 had pins on input: 3,387 input pin sites,
  95 net removals, 39 rows with a reduction. This does not isolate the cost of pin work from
  naming work. No recorded input fidelity sites occurred in that telemetry population, so
  zero site removals is not evidence of a failed site-removal campaign.
- The [bake-off](BAKEOFF.md) tested 12 rows per model with a narrower prompt preserving pins.
  The current prompt also requires scaffolding removal attempts. Its workload has changed;
  the bake-off does not establish the best model or effort for every current task class.
- Claude's epilogue pilot became a reusable transform: 453 rows changed and 979 sites removed.
  This is a strong example of model work paying off across the corpus. See [FIDELITY.md](FIDELITY.md).

## First implementation: a controlled readability pilot

1. Freeze a sample of 50–100 small functions and their relevant inputs. Include wrappers,
   local renames, evidence-rich rows, ambiguous callees, and a few awkward cases. Keep the
   comparison separate from live campaign ownership so both arms start from identical C.
2. Run the existing single-row workflow as the baseline. Compare it with batches of initially
   10–20 small, related functions, bounded by total source/context size as well as row count.
   Use the same Astra model and effort initially to isolate workflow effects.
3. Give the batch a prepared context packet and request naming/comment changes only. Let the
   harness apply or collect each result, verify it independently, and return compact diagnostics
   for a bounded repair attempt. One failed row must not discard the other successful rows.
4. Record tokens, uncached input tokens, output tokens, model duration, compile attempts,
   verification/promotion time, first-pass exactness, and independently verified improvements.
   Sample the names and summaries for accuracy and specificity without revealing the arm.
   Byte equality cannot establish whether a semantic name is truthful.
5. Compare tokens and end-to-end time per verified improvement, not merely per accepted file.
   Changing a comment can count as accepted without making the code more understandable.
   Report failures and quality tradeoffs alongside savings. If quality holds and usage falls,
   extend to another size band before adopting it across the campaign.

The pilot is proposed work. No paid comparison or additional agent campaign was launched by
this review. Lower effort or another model can be a later comparison once batching is measured.

## Changes worth making, in order

### 1. Prepare context once and batch related small rows

Extend `tools/agent_task.py::one` and `tools/evidence.py::prompt_block` with a compact packet:

- Row ID, actual definition symbol, true address where known, and exact source/output paths.
- Relevant callee summaries or small callee excerpts, shared record declarations, and evidence
  provenance. Include an explicit unknown when evidence is absent.
- Known failed transformations relevant to the current source/compiler/evidence state.
- The supported verification interface and where to look for additional local context.

Supply explicit paths to avoid layout rediscovery. Explore a dedicated worker configuration
with only relevant tools and guidance, preserving the project's IO discipline. Measure what
the installed client actually includes; do not assume configuration changes remove all base
context. Prefer short batches over an indefinitely growing session.

### 2. Separate readability from shape investigation

The current `PROMPT` asks for naming, control-flow simplification, removal attempts for every
pin/marker/pseudo-call, unlimited verifies, and a final `--gate`. Split task types explicitly:

| Task | Proposed handling |
|---|---|
| Names and one-line summaries | Prepared context, small batches, bounded repair |
| Known mechanical shape | Scripted candidate generation and verification |
| Unresolved source shape | One row or closely related family, a hypothesis and attempt budget |
| Shared names, layouts, module evidence | Claude/Astra investigation whose findings feed many rows |

This requires an explicit update to the current policy in `PLAN.md` and `HANDOVER.md`: every L3
lane currently must try scaffolding removal. Preserve that obligation in a separately tracked
queue; do not silently drop it or claim those attempts happened. Cache failed hypotheses with
source and toolchain identity, and revisit them when relevant inputs or evidence change.
Count all candidate-compilation entry points against a search budget: the existing mid-row
report allows `aligned_score.py --diff` iterations outside the verify budget, so that budget
alone does not bound actual work.

### 3. Consolidate repeated verification without weakening proof

For a typical successful changed row, the current path can invoke the scorer four times:

1. The lane's initial `verify.py` call.
2. Its final `verify.py --gate`, which scores again before checking the gate.
3. `agent_task.py::one` independently calling `verify`.
4. `promote.py::promote_text` calling `verify` again after normalising the candidate.

Rows requiring window gates can also repeat those between the lane and promotion. The current
code already skips the extra window check for true-name rows; preserve that existing distinction.

Make the harness own verification and landing, with agent iterations driven by failure
diagnostics. Reuse a result only when the exact candidate and all relevant inputs match:
headers, compiler, flags, assembler/preprocessing tools, target/address mapping, and for a
window proof every input to that window. Normalisation before promotion can change the text,
so a pre-normalisation result is not automatically reusable. Preserve locks and rollback.
The historical scorer-exact/window-mismatch failures in [HANDOVER.md](HANDOVER.md) remain
applicable. Do not remove the independent proof or substitute a model's reported success.

### 4. Spend Claude time on reusable discoveries and disputed claims

Continue the successful pattern: investigate a small representative family, identify the
mechanism, encode it as a transform, and apply it with machine verification. Feed discoveries
into the context packets so Astra does not repeatedly infer them from raw code.

The [script-call-table research](evidence/script_call_table_20260908.md) used 16 agents and
independent verification. It corrected a table error affecting 14 landed names, so that
verification had concrete value. For future research, begin with bounded questions and
evidence-bearing findings; add independent readers for consequential or disputed claims.
Avoid routinely re-deriving every settled claim. This recommendation is based on repo reports,
not a complete accounting of Claude tokens or a measured alternative research workflow.

Move routine tier transitions, relaunch conditions, and progress summaries into a controller.
Keep Claude available for decisions rather than repeated process supervision. Any rate-limit
controller must respect resets and stop conditions rather than repeatedly launching work.

### 5. Make accounting and scheduling reliable

`run_codex` currently searches up to 40 recent session files and reads them to recover usage.
Capture `codex exec --json` events instead: the documented `turn.completed` event includes
usage. Record the thread ID directly, plus task/prompt version and per-phase timings. Keep
small summaries searchable; put bulky traces in an ignored location under the IO rules.
See [official non-interactive documentation](https://learn.chatgpt.com/docs/non-interactive-mode#make-output-machine-readable).
Validate the installed client's event schema before replacing the current accounting.

The controller currently consumes `ThreadPoolExecutor.map` results in input order. A slow row
can delay journalling completed rows and observing quota failures while workers continue.
Use a bounded set of outstanding jobs and journal completions as they arrive, with explicit
quota/backoff handling. Introduce attempt limits and state-aware retry decisions; a rejected
row should not repeatedly receive identical instructions without new information.

## Where to pick up

Read `tools/agent_task.py` for prompt construction, invocation, journal fields, and scheduling;
`tools/verify.py` and `tools/promote.py` for proof and landing; `tools/evidence.py` for context.
Keep `ledger/agents/*.jsonl` and `ledger/promotions.jsonl` distinct when measuring outcomes.

Implement the readability pilot first. Keep experimental output separate from the active
campaign until verified and deliberately promoted. Do not rebuild `build_ovl/` under running
workers. Follow the global narrow-search and `rg --max-filesize 4M` rules throughout. When a
workflow is adopted, update the standing handover and policy together so future lanes receive
one consistent task definition.
