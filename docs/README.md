# Documentation index

Start with the [top-level README](../README.md) and [STATUS.md](../STATUS.md). The files below are
the current reference material; everything under `history/` and most of `evidence/` is a record of
how the project got here and is not needed to use or contribute to it.

## Current reference

| doc | what it is |
|---|---|
| [PLAN.md](PLAN.md) | strategy, the cleanliness levels L0-L5 and what each requires |
| [SYMBOLS.md](SYMBOLS.md) | the names the game itself gives us (assertion strings, tables, identifiers) and how the repo uses them |
| [EVIDENCE.md](EVIDENCE.md) | index of the naming and module evidence carried per row and how each level uses it |
| [STRUCT_CENSUS.md](STRUCT_CENSUS.md) | cross-function struct census (groundwork for shared types) |
| [TYPE_CONSOLIDATION.md](TYPE_CONSOLIDATION.md) | how per-function struct views are merged into shared game types |
| [FIDELITY.md](FIDELITY.md) | what "fidelity debt" means: C shapes that match only because of compiler quirks, how they are measured |
| [SLUS_MODULES.md](SLUS_MODULES.md) | how the main executable is grouped into source modules |
| [SLUS_PARTITIONS.md](SLUS_PARTITIONS.md) | function partitions of the executable and their ownership certificates |
| [SWAPOVER.md](SWAPOVER.md) | how this tree came to own all of its sources (the pin and the swap-over) |
| [TOOLCHAIN_FIDELITY_PLAN.md](TOOLCHAIN_FIDELITY_PLAN.md) | plan for making the toolchain reproduce the original build faithfully |
| [GOAL_TOOLCHAIN_AND_MODULES.md](GOAL_TOOLCHAIN_AND_MODULES.md) | goal statement: toolchain repairs and module cleanup |
| [OPEN_ITEMS.md](OPEN_ITEMS.md) | open questions and unfinished work |
| [../CONTRIBUTING.md](../CONTRIBUTING.md) | how to make and prove a change |
| [../NOTICE](../NOTICE) | legal notice, credits, what is and is not in this repository |

Tool-level notes live next to the tools: [tools/maspsx/README.md](../tools/maspsx/README.md),
[tools/learnings/](../tools/learnings/) (short write-ups of compiler behaviour found while matching).

## Evidence

`evidence/` holds the individual research notes, measurements and receipts behind names, module
boundaries and decisions. Files are named by topic, function address or date. Modules and the
naming levels cite them by path, so they are kept as they are; browse by searching for an address.

## History

`history/` is the project's working journal: handover notes, round-by-round research on the
"pin" cleanup campaign (`PIN_*`), the agent/lane workflow documents, the early reports. It is
accurate for its date and was not rewritten for outside readers; numbers in it are old.

| doc | what it is |
|---|---|
| [history/HANDOVER.md](history/HANDOVER.md) | long running handover log (latest state, rulings, landing procedures) |
| [history/handover_archive/](history/handover_archive/) | earlier parts of the handover log |
| [history/PIN_CAMPAIGN_CHARTER.md](history/PIN_CAMPAIGN_CHARTER.md) | the charter and rulings of the pin-removal campaign |
| [history/PIN_GOAL_PROGRESS.md](history/PIN_GOAL_PROGRESS.md) | pin-removal research progress summary |
| [history/PIN_MECHANISMS_20260912.md](history/PIN_MECHANISMS_20260912.md), [PIN_PATTERNS.md](history/PIN_PATTERNS.md), [PIN_ATLAS_20260912.md](history/PIN_ATLAS_20260912.md), [PIN_FAMILIES.md](history/PIN_FAMILIES.md), [PIN_CENSUS.md](history/PIN_CENSUS.md) | what the scaffolding was, why the compiler needed it, censuses |
| [history/PIN_RESEARCH_ROUND39.md](history/PIN_RESEARCH_ROUND39.md) .. ROUND62 | per-round research notes of the campaign |
| [history/PIN_SEARCH.md](history/PIN_SEARCH.md), PIN_SEARCH_*, PIN_WAVE_*, PIN_RECOVERY_*, PIN_CLEANUP_REVIEW_* | search tooling and wave reports |
| [history/L0_BLOCKED_PLAN_20260922.md](history/L0_BLOCKED_PLAN_20260922.md) | classification of the last blocked rows |
| [history/LANE_KIT.md](history/LANE_KIT.md), [AGENT_EFFICIENCY_HANDOVER.md](history/AGENT_EFFICIENCY_HANDOVER.md), [CLAUDE_CODEX_RESTART_PLAN_20260927.md](history/CLAUDE_CODEX_RESTART_PLAN_20260927.md), [BAKEOFF.md](history/BAKEOFF.md) | how AI-assisted work lanes were set up and measured |
| [history/REPORT_20260907.md](history/REPORT_20260907.md) | day-one report |

Paths such as `docs/PIN_*.md` quoted in tool docstrings and comments predate the move into
`history/`.
