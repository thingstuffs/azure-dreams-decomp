# Claude / Codex restart: review, improve, then resume pin cleanup

Written 2026-09-27 for the next usage reset. Evidence baseline: `a0b30a59`.
This is a work order for the next orchestrator, not a claim that a new campaign has
already run. Dates and counters below are snapshots; refresh them at pickup.
The reset is a capacity checkpoint, not a deadline for spending the allowance.

## Goal statement

Continue Azure Dreams toward clean, readable, byte-accurate ordinary C, with zero
genuine pins, hidden assembly, artificial dependencies or assembler imitation
used to disguise unresolved source shape. First review the recent GP/toolchain
and lane-tooling work, identify the highest-value remaining blockers, and repair
the workflow where necessary. Then run bounded pin-removal campaigns that turn
individual discoveries into reusable C patterns and mechanical transforms.
Improve verified progress per unit of LLM usage while preserving every byte,
legitimacy, ownership and placement gate.

Claude owns campaign direction and integration decisions. Codex supplies bounded
implementation, C reconstruction, tooling and verification work. Expensive models
resolve consequential uncertainty; smaller models and deterministic tools carry
repeatable work. A partially successful row is eligible for a fresh, narrower
attempt after its result lands. Do not automatically escalate it away from a
cheap model that is still making progress.

The [pin charter](PIN_CAMPAIGN_CHARTER.md) and [level definitions](PLAN.md) remain
the acceptance contract. This plan updates scheduling and measurement preferences:
do not revive older instructions for new model bake-offs, overlap comparisons,
automatic escalation after one partial success, or large simultaneous waves.
Existing owner approvals remain valid. Do not request the GP approval again.

## Targets and definition of success

These operating targets are proposed here, not historical measurements or a
prediction that the remaining hard rows will yield at earlier rates.

| Horizon | Concrete target | Required evidence |
|---|---|---|
| Before the next production wave | One concise restart review; reconcile current counts, open changes, active workers, proof freshness and highest-value queue | Commit/input identities, receipts, selected tasks, explicit launch budgets |
| First wave | 10–20 distinct rows in one or two understood families; include reduced rows worth revisiting | Landed reductions and failures, complete task dispositions, usage provenance, required gates |
| First week after restart | Initial planning target: remove at least 100 net genuine pins from the refreshed baseline; review feasibility after the first wave | Unchanged census at both endpoints; separate any owner-approved reclassification from actual removals |
| Continual improvement | Seek 20% lower measured usage per landed pin in a comparable family/band after an adopted workflow improvement | Sequential production observations; same token meter, difficulty/context notes, sample sizes; no duplicate paid comparison |
| Every wave | Zero byte regressions, zero concealed scaffolding growth, zero unowned concurrent edits | Landing receipts and legitimacy review |
| Every completed task | 100% outcome accounting; measured usage or an explicit missing/estimated flag | Failed, capped, interrupted and zero-progress tasks included |

100 pins is about 3.2% of the last recorded 3,098. Reforecast from real yield and
capacity; do not relax gates or pad progress to hit it. If comparison samples are
too small, report the efficiency target as unmeasured. Module cleanup, dependency
retirement and evidence-backed research have separate deliverables, not invented
pin-equivalent scores. The terminal goal remains zero pins; this week is a step.

## What actually landed recently

Read the **completion** sections and receipts before historical introductions.
Some older document openings still describe private rehearsals or pending approval.

1. **GP ownership and assembler semantics are repaired in production.**
   Commit `819de459` installed the approved transition on September 25. Externally
   declared small globals now follow genuine ASPSX absolute-address behavior;
   appropriate TU-owned small data has real C ownership and GP-relative treatment.
   This required coherent declarations, data storage, grouped sources and explicit
   collector partitions, rather than a source/address whitelist in the assembler.
   The unused `_sink_call_separated_la` pass was removed.
2. **The transition has full linked proof.** All 524,288 SLUS bytes match retail;
   all 2,175 active overlay windows match. There are 33 ownership proofs, two
   refreshed placement certificates, 860 physical C objects and 884 logical SLUS
   rows. Recorded checks passed: 166 SLUS, eight configure, 418 assembler tests
   and 60 fidelity controls. These are archived results, not tests rerun for this plan.
3. **The fresh production census removed 22 dependencies, 189 → 167, adding none.**
   Of 6,767 registered rows, 6,600 match a common genuine ASPSX version. The external
   GP detector reports zero rows. This does not mean all remaining assembler or
   compiler-model debt is gone. `_split_funcaddr_la` still serves
   `dungeon/func_818D4E68`; accepted epilogue models and old-ASPSX dials remain.
4. **The module pilot is real but its scope is limited.** `runtime_directory`
   remains L5/L4/L5; its middle row retains PASSTHRU residue. Ownership proofs do
   not confer placement certificates on every new owner. Partition ownership
   does not certify the whole collector. Changed shared inputs require fresh proof.
5. **Pin recovery continued alongside fidelity work.** The interrupted H28 work
   yielded eleven landed CDK candidates, 74 pins removed, nine newly pin-free
   rows and two partial reductions, with genuine-ASPSX and retail gates. The last
   committed status records **3,098 sites in 765 rows**. H28 and later snapshots
   overlap in time; do not add their reductions as independent totals.

Primary references: [production closeout](evidence/gp_partition_only/production_transition/README.md),
[completed goal](GOAL_TOOLCHAIN_AND_MODULES.md#completion-checkpoint-approved-production-transition),
[H28 recovery](evidence/r77_h28_recovery.md), [status](../STATUS.md),
[module workflow](SLUS_MODULES.md), [partition rules](SLUS_PARTITIONS.md).

Scope qualifications matter: the assembler census masks 872 relocation words in
302 overlay rows; the separate window gates prove retail bytes. SLUS has zero
census masks. A data-only row and two unlinked helper symbols have narrower direct
comparison coverage. Twenty-two movie rows remain owner-parked. Three unregistered
MAIN routines (`800217C8`, `800218A0`, `80021958`) still lack C coverage; their SDK
attribution/loading questions are documented, not solved. See the
[MAIN audit](evidence/main_kernel_coverage_audit.md). Do not claim whole-game C completion.

## Review before dispatch

Claude should produce a short decision record, then act on it without returning
to the owner for routine scheduling permission:

1. Read this plan, the production closeout, the H28 recovery and the current lane
   kit. Inspect changes since `a0b30a59`, existing workers/landers and the working
   tree. Preserve other work. At plan creation, edits to lane docs/prompts, kit
   installation and tests were already present, plus the untracked
   `tools/learnings/pin_removal_possibilities.md`. Review their actual diff and
   relevant tests before treating them as deployed policy.
2. Reconcile the pin census, dependent rows and certificate freshness. Reuse
   archived proofs only for identical relevant inputs. Run required checks for
   changed inputs; avoid an unchanged full rebuild merely to rediscover a receipt.
3. Audit launch enforcement: bounded work ownership, actual model/version, caps,
   usage capture, same-text retry guard and landing lock. Fix missing enforcement
   before scaling. Existing code is a starting point, not proof that a flag is on.
4. Choose the next two priorities by expected verified benefit and evidence.
   Recommended starting order: recover any still-valid staged work; apply known
   patterns to current residual families; resume H28 C-shape reconstruction;
   investigate a shared blocker only when it blocks a meaningful population.
   Keep MAIN gaps, module placement and the egcs proxy question visible in their
   own queues. They need not block independent pin work.
5. Launch one small production wave, review its yield and failures, then expand
   only the paying families. Never fill every available agent slot by default.

**FFT inspiration:** the owner reports influence from the FFT decompilation
project. Bounded searches of recent commit messages and selected project notes
did not locate a named FFT reference, so no specific technique is attributed to
it here. If the source/link survives in prior notes, attach it once and extract
testable ideas. Do not spend a new research campaign rediscovering the reference.
The local source-shape catalogue is useful on its own: typed aggregate copies,
real symbol/type relationships, address formation and whole-function live ranges
are hypotheses to compile and prove, not guaranteed local instruction recipes.

## Model routing and responsibilities

The owner's model observations below are the default operating policy. They are
not controlled model-quality findings. Record the actual model ID and reasoning
effort; aliases are insufficient. If the desired version is unavailable, record
the substitution instead of silently relabelling it.

| Resource | Assigned role | Limits and routing |
|---|---|---|
| Claude Opus 5.5 | Orchestration, difficult C reasoning, consequential review, synthesis into reusable methods | At most five active Claude agents total, counting the coordinator and any advisor; start below this ceiling |
| Fable 5.1 advisor | Bounded strategic advice at major decision points; a hard unresolved question after normal approaches fail | At most one at a time, inside the Claude ceiling; concise evidence packet, not bulk rows |
| Sonnet | No routine work in this restart | Reconsider after Sonnet 5.5 or material new evidence; do not launch a comparison now |
| Codex Astra | Novel cross-cutting diagnosis or particularly hard reconstruction | Sparing use, one active specialist initially; return a reusable finding and next action |
| Codex Sol | Bounded implementation, probes, tooling fixes, medium-complexity reconstruction and verification | If 6 fails instructions, stops prematurely or produces weaker work, try 5.6 on the actual unfinished task and record the outcome |
| Codex Luna | Small explicit tasks, family inventories, known-pattern application, fresh attempts on reduced rows | 5.6 at max is an owner-preferred option for tightly bounded work; observe 6/5.6 behavior without duplicate comparisons |
| Gemini 3.8 Flash | Independent bounded candidates, inventories and known-shape work | Use remaining allowance liberally; count CPU/IO, review and landing costs even when marginal subscription spend is low |

Initially cap Codex workers at three total, including any Astra specialist, and
Gemini at one. These are proposed operational defaults, not account limits.
The coordinator may lower concurrency for IO/compile pressure or adjust it after
measuring throughput. The Claude ceiling remains five; Fable remains one.

Claude owns priority, ownership assignments, review decisions and the wave report.
Codex owns the concrete assigned artifact and its proof: give each task exact
paths, source/recipe identity, hypothesis, allowed edits, output location, budget
and acceptance checks. Workers stage candidates; the designated integrator uses
the existing serialized landing transaction. Do not have two agents modify or
sweep the same family/module concurrently. Avoid delegating a task whose setup
and review would cost more than completing it directly.

For a suspected version regression, record: model/effort, task class, prompt and
source identity, the specific unmet instruction or failed artifact, measured
usage, and what the subsequent 5.6 attempt accomplished. Separate an early stop
from a byte mismatch or an impossible budget. A rescue starts with accumulated
evidence, so its success is useful routing evidence, not proof of causal superiority.

## Retry, escalation and mechanical reuse

- A 20-pin row reduced to 15 is successful partial progress. Land it, recensus,
  and offer the smaller problem to the same inexpensive tier in a fresh context.
  One removal out of twenty is not a reason never to revisit that row cheaply.
- A retry packet contains only current C, remaining pin clusters, recipe, retail
  target, successful/failed hypotheses and the next discriminator. Fresh context
  should remove stale reasoning while preserving durable discoveries.
- Do not blindly repeat identical failures. Use the tier/text/kit/scope guard in
  `served.py`. After two no-progress attempts at the same meaningful state, require
  a changed hypothesis, new evidence or kit improvement before another attempt.
  An exceptional same-text retry needs a written reason and bounded budget; do not
  disable the served guard across the pool. Reduced source is a new state.
- Escalate when the residual needs missing reasoning or evidence, not because a
  cheap worker failed to remove every pin in one pass. Stop an unproductive family
  and diagnose it; keep independent productive families moving.
- When multiple wins share one move, inspect existing generator refusal classes,
  then encode/reuse the move. Test it on representative and held-out rows, check
  protected arms and legitimacy, and apply through the real byte gates. Related
  Luna packs are appropriate when the pattern is known but unsafe to script.
- Credit research separately: require a demonstrated mechanism, affected population,
  reusable artifact and a next executable step. A long report or a lower diff
  score is not a landed pin removal.

## Toolchain posture: source shape first, documented exceptions retained

The broad historical compiler hunt is exhausted enough to stop routine compiler
shopping. The inventory tested 21 historical/rebuilt compilers plus 13 patched
research builds. There is still a documented missing historical window and an
accepted epilogue model; the remaining 167 dependencies cannot honestly be called
all C-shape debt. Reopen toolchain investigation only for new discriminating
evidence and a bounded experiment, not because a source search was difficult.

Use the established recipe and compiler source to explain the first divergent
pass. Follow expansion → CSE/combine → scheduling → local/global allocation and
reload → delay-slot filling. Inspect register roles, set counts, allocno order,
variable live ranges, signedness, real aggregate layout, alias relationships and
control-flow shape. A locally correct instruction sequence may still have the
wrong surrounding C. Score and explain the whole-function residual.

`docs/LANE_KIT.md` maps dumps to compiler files; sources live under
`toolchain/gcc-src/<version>/`. Public source for the proprietary 2.7.2-cdk variant
is unavailable: use 2.7.2 source as a guide and confirm CDK behavior experimentally.
Retail split-address fingerprints and the recovered CDK lineage are evidence for
recipe attribution; do not imitate another compiler with numeric page constants.
At a trial recipe, genuine-ASPSX equality with maspsx does **not** prove retail
equality: use `cell_retail_check.py` and the applicable linked gate. That mistaken
inference already caused a withdrawn module-census conclusion.

Preserve stock-compiler and recipe-trade rules. No patched compiler landings,
function-keyed assembler exceptions, new volatile/barriers/fake dependencies or
hidden whole-function assembly. Keep accepted model residue visible until its
actual dependency is removed. See [fidelity plan](TOOLCHAIN_FIDELITY_PLAN.md).

## Measure efficiency without conflating meters

Keep three accounts: **verified product progress**, **LLM consumption**, and
**wall/CPU/IO/review time**. Capture failed work and coordinator overhead too.
Do not rank a tiny-row batch against hard residual research as if work were equal.

For each lane, record input tokens, cached input, output, model/effort and meter
definition. For the existing Codex harness, `input - cached_input + output` is the
reported uncached-plus-output figure. Cached input is already included in input;
never add it twice. Retain raw fields even if a report uses a derived total.

Claude Agent-tool `subagent_tokens` has been observed to approximate final context
size, not cumulative API consumption. Some old lane self-estimates were mistaken
for measurements. Use actual tool results and, where available, deduplicated
transcript usage. The current transcript collector also documents undercounted
streaming output: mark that total as a lower bound. Multiplying incompatible
token figures by a weight does not make them comparable. See
[`record_usage.py`](../tools/lanes/record_usage.py).

`config/model_cost_weights.json` currently uses owner estimates (Luna 6 = 1,
Sol 6 = 10, Astra = 35, Opus = 10); 5.6 weights are unknown, and Gemini's zero
was a window-specific assumption. These are planning heuristics, not measured
subscription conversions. Do not use them to declare a cross-provider winner.

For additional context, the official Standard-speed Codex **credit** rates
retrieved on 2026-09-27 are below, in credits per million tokens. Refresh before
using them for a later financial estimate; they do not specify subscription drain.

| Model | Uncached input | Cached input | Output |
|---|---:|---:|---:|
| GPT-6 Astra | 250 | 25 | 1,250 |
| GPT-6 Sol | 50 | 5 | 250 |
| GPT-6 Luna | 2.5 | 0.25 | 12.5 |
| GPT-5.6 Sol | 100 | 10 | 500 |
| GPT-5.6 Luna | 5 | 0.5 | 30 |

Thus Astra/Sol/Luna 6 are 100/20/1 at an identical token mix on this credit meter;
the repository's 35/10/1 estimates concern a different assumption. Neither ratio
establishes which model solves a task most efficiently. Credit cost is
`(uncached_input × input_rate + cached_input × cache_rate + output × output_rate) / 1e6`.
Included-plan limits must be read from actual usage status, separately for each
provider. [Official OpenAI pricing and usage guidance](https://learn.chatgpt.com/docs/pricing).

At wave start/end, record each available five-hour/weekly meter, its reset time
and any unrelated concurrent use. Report percentage-point consumption only across
the same window. Do not sum across a reset or claim a per-lane quota measurement
from a shared account. Reserve capacity for review and landing; as an initial
budget, allocate 70% of remaining campaign capacity to production, 20% to reusable
improvements and 10% to verification/recovery. Adjust from observed demand.
No new paid credits or API purchases are authorized by this plan.

Report these metrics by provider/model, family, initial pin band and retry status:

- Net landed pins and newly pin-free rows; full gate pass rate and rejected claims.
- Usage per landed pin and per newly pin-free row, with zero-progress spend included.
  For zero pins, report consumption and zero yield rather than dropping the lane.
- Same-tier repeat yield after a partial landing; escalation yield on prior failures.
- First-pass acceptance, repair attempts, capped tasks and instruction failures.
- End-to-end time to landing; coordinator/reviewer usage and missing-meter coverage.
- Reusable-transform payoff: downstream gated removals, amortizing discovery and
  maintenance cost once. Attribute each actual removal once, even if several lanes
  proposed it. Show discovery benefit without double-counting campaign totals.

## Evidence supporting and limiting the owner's observations

| Local observation | What it supports | What it does not establish |
|---|---|---|
| September 8 readability pilot, 40 frozen rows ≤100 B: 88k → 12.9k input tokens/row; 45 → 8.3 seconds; acceptance 39–40/40, equivalent assessed readability | Prepared context and batches cut input about 85% and duration about 82% in that tiny-readability workflow | The same savings on hard pin reconstruction or a different model |
| Round-77 clone-port notes: about 150k input tokens / six minutes vs about 400k / 45 minutes from scratch; small successful cohort | Reusing a known source shape can be cheaper than rediscovering it | A controlled universal speedup |
| H28 recovery: eleven landings, 74 pins, nine newly pin-free rows, two partial reductions | Recover interrupted work and accept useful partial reductions | That every interrupted or partial lane is worth repeating |
| R73–75 routed pools: Opus 132/215 exact, Astra 70/97, Sol 20/106, Luna 10/70 | Strong-tier retries can pay; routing and task preparation matter | Intrinsic model ranking: pools were selected differently |
| Tier/text/kit/scope retry guard and historical kit-era retry successes | Re-serving after changed source/evidence is legitimate and useful | Unlimited identical retries or automatic escalation |
| Older Astra campaign: 363.6M input tokens, including 312.8M cached, across 4,509 attempts | Context and orchestration overhead deserve measurement | Subscription cost, landed pin cost, or a pin-only success rate |

Sources: [efficiency review](AGENT_EFFICIENCY_HANDOVER.md), the September 8 pilot
in [archived handover](handover_archive/HANDOVER_through_20260922.md), round-77
and R73–75 entries in [handover](HANDOVER.md), and [lane kit](LANE_KIT.md).
The old evidence does not establish 5.6 versus 6 quality. Capture natural production
rescues prospectively; do not rerun solved tasks for side-by-side comparisons.

## Enforcement and continual improvement

`lane_cap.py` and `pool.py` already support caps, but their defaults are **off**.
For the next wave, require explicit `--token-cap` / `--wall-cap` (or launcher
`LANE_TOKEN_CAP` / `LANE_WALL_CAP`), a task output contract and an ownership record.
Initial proposed limits: routine Codex pack 250,000 uncached-plus-output tokens /
45 minutes; hard specialist 750,000 / 90 minutes. Calibrate from actual task sizes;
these are runaway ceilings, not targets to spend. Give a smaller task a smaller
budget. A bounded extension requires a concrete residual hypothesis and recorded
reason, not an automatic relaunch of a capped lane.

Claude Agent-tool lanes are not covered by the Codex rollout watcher. The Claude
coordinator must enforce its own task/checkpoint limits and record actual usage
at completion. Do not describe a prompt request to conserve tokens as a hard cap.
Review low yield after four completed comparable lanes; pause dispatch to that
family if it has no landed progress and no demonstrated reusable finding. Keep
finished candidates from capped lanes available for independent verification.

After each wave, record one of: adopt a demonstrated improvement, run one bounded
test of a specific suspected waste, or make no workflow change because the evidence
does not justify it. Do not manufacture changes to satisfy a process metric.
Repeated avoidable failures should become a launcher check, fixture, context-packet
field or generator fix. Update the actual prompt/kit/controller and check its
behavior; a prose note alone is not enforcement. Track adoption and measured
effect on later production tasks. Retire stale instructions when policy changes.

Respect the shared disk: narrow reads only, `rg --max-filesize 4M`, no recursive
search at repo root, `work/`, the home directory, or archived bulk-work directories.
Restore the exact archived experiment when required instead of regenerating it.
Keep large traces in ignored storage and searchable summaries small. Use recorded
PIDs or the bracket trick when polling; never a self-matching `pgrep` loop.

## Required compact wave record

Extend existing lane journals/reporting rather than building a competing system.
Each wave should leave the following fields in a small durable report:

```text
Wave / UTC interval / start and end commit + relevant dirty-input identities:
Objective, family, initial pin bands, row owners, model IDs and effort:
Budget and enabled caps; provider meters/reset times where available:
Rows served / retries / escalations / failed / capped / interrupted:
Pins before -> after; removals vs census changes; newly pin-free rows:
Candidate receipts -> unique landings -> covering/full gate receipts:
Measured input / cached / output; token-meter definition and missing coverage:
Coordinator + review consumption; quota deltas and attribution limitations:
Usage per landed pin; wall/CPU time; reusable findings and downstream payoff:
Instruction failures or 6 -> 5.6 rescues, with concrete evidence:
One adopted improvement or reason for no change; next bounded tasks:
```

Pickup instruction for Claude: **Read this file, verify the current state against
the cited completion receipts, review the pending lane-kit changes, write the
short restart decision record, then orchestrate the next bounded production wave.
Keep the owner informed of measured progress and material uncertainty; continue
routine authorized work without repeated permission requests.**
