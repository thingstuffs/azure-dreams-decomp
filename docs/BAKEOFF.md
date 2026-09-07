# Layer-2 agent bake-off (readability pass under a byte-exact gate)

Task per row: rename m2c locals, add a one-line summary, simplify control flow only where the
bytes stay identical; keep pins, externs, structs and (from stage 2) struct member names.
The harness (`tools/agent_task.py`) gives the model the verify command, verifies the result
independently, and reads token usage from the Codex rollout. Same rows for every model.

## Stage 1 — six rows, 150–500 B, few gotos (2026-09-07)

| model | accepted | wall | output tokens | reasoning tokens | notes |
|---|---:|---:|---:|---:|---|
| gpt-6-astra high | 6/6 | 214 s | 3,281 | ~360 | fastest; conservative (kept `unk_XX`, left 3 m2c names on one row) |
| gpt-5.6-sol high | 6/6 | 263 s | 7,225 | ~1,700 | names close to Astra's; renamed struct members (now forbidden) |
| gpt-5.6-luna xhigh | 6/6 | 259 s | 8,863 | ~3,200 | generic names (`timing_field_0C`, `updated_state_value`) |

Input tokens were 45–95 k per row for every model, 85–95 % cached (the prompt is the file plus
the Codex system context). Nobody simplified control flow on these rows (gotos unchanged),
which is the instructed behaviour when exactness is uncertain.

Reading: Astra produces the same quality as sol at ~45 % of sol's output tokens and ~80 % of
its wall time; luna is cheaper per token than sol but its names carry less meaning. For this
task class the routing is Astra first.

## Stage 2 — six rows, 500–1,500 B, with gotos (member renames forbidden)

| model | accepted | wall | input tokens | output tokens | gotos |
|---|---:|---:|---:|---:|---:|
| gpt-6-astra high | 6/6 | 253 s | 492 k | **3,644** | 51 → 51 |
| gpt-5.6-sol high | 6/6 | 710 s | 579 k | 21,942 | 51 → 51 |
| gpt-5.6-luna xhigh | 6/6 | 669 s | 713 k | 29,852 | 51 → 51 |

Quality on the 18-local MAIN row (`func_7FDD26A8`): all three chose specific, correct-looking
names for the table-copy loops (Astra `sprite_table_source` / `color_mask_table_source`, sol
`template_src`, luna `initial_table`); Astra's are the most descriptive. Nobody restructured
gotos, as instructed when exactness is uncertain: goto removal is a different task class and
needs a search harness, not a single-shot rewrite.

## Verdict (2026-09-07)

For the Layer-2 pass (locals, summaries, no member renames) **Astra at high effort is the
routing**: same or better names than sol at one sixth of sol's output tokens and one third of
its wall time, 12/12 accepted byte-exact. Luna is the fallback only if Astra quota runs out.
Estimated cost of the pass over ~5,000 rows at Astra's measured rate: ~50 h serial wall time,
~4 M output tokens; input is dominated by cached context.
