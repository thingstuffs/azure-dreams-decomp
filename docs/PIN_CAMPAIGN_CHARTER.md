# Pin campaign charter (owner, 2026-09-18)

## Goal

Drive the count of genuine C pins in `src/` toward **zero**, measured only by the unchanged
census (`tools/status.py` -> "Pin sites now", `tools/pin_census.sites_of` over every row except
owner-parked `ovmovie`), on a tree whose covering windows, the SLUS SHA-1 gate and the row
database all pass. Any method is allowed that lands under the legitimacy rules below. The
operator decides what to do next on written rationale, does it, documents it, and asks
forgiveness later; the owner is consulted only for decisions the charter reserves.

## What counts as a genuine removal

A pin is removed only when all of these hold:

1. **Genuine compiler.** The row builds through the fixed stock toolchain set (gcc 2.6.3, 2.7.2,
   2.7.2-cdk, 2.8.0, 2.8.1 with the recorded -G and flag dialects; 2.91.66/2.95.2 are recorded,
   never landed) and the real assembler pipeline (`maspsx` as the ASPSX stand-in under its
   existing byte-neutral rules). No compiler patches, no per-function toolchain substitutions,
   no edits to the pipeline that change what "exact" means.
2. **Byte-exact where it matters.** Strict row bytes, every covering window, SLUS, row database.
   Refused results keep the pin and record what matched (`ledger/pin_evidence.jsonl`).
3. **Ordinary C, net of scaffolding.** No scaffolding kind may grow on a landed row (`ASM_*`,
   `while (0)` barriers, `__asm__`, `volatile`, fake dependencies, computed-goto tricks: the
   land script's grow check), hidden asm is exposed not hidden (`tools/expose_asm.py`), port
   and dead preprocessor arms are never edited, retail bytes and row identities are never
   changed to fit. A pin moved elsewhere is not a removal: the count is tree-wide.
4. **Recipes are loans, not knobs.** A cell or flag change lands only under `pin_cells_land`
   rules 1-2 (the pinned text is exact at both recipes), with no flag cap, and every trade is
   appended first to `ledger/recipe_trades.jsonl` (site, macro, fingerprint, recipe from and to,
   module-neighbour numbers). The module recipe census (`ledger/module_recipe_census.jsonl`)
   is the instrument for paying the loans back later on cleaner source.
5. **The counter is sacred.** Changing the census, the scorer, the gate or the parked set to
   move the number needs the owner's explicit sign-off in the round document.

## Freedom and resources

- Choose the approach per round from evidence: measured yield per resource, not tradition.
  Rounds 28-34 (a discovered move swept over the tree by CPU) beat rounds 35-54 (per-row model
  reconstruction) by an order of magnitude per token; the round-55 census shows recipes were
  fitted per row. Both facts may be overturned by new measurement.
- **CPU first.** 24 cores are free; long jobs are fine. Every long job gets one completion event,
  never polling. Journals are hash-keyed: never rerun a menu on unchanged text.
- **Models by ladder, checked for capacity each round.** Probe before relying: a trivial
  `codex exec` (luna -> sol -> astra per `docs/LANE_KIT.md`) and `agy --print` (Gemini) at
  round start; journal the outcome in `ledger/lanes.jsonl` with the date. Claude opus/sonnet
  through `Workflow` or `claude -p` for designing moves and reviews, with a shared cached prefix.
  Spend models on discovering a family (mechanism -> generator -> CPU sweep), on whole-function
  reconstruction only for rows no generator can reach, and never on rows a lane already served
  at the same text (`tools/lanes/served.py`).
- Adapt mid-round when the numbers say so; write the rationale in the round document; do not
  stop to ask unless the charter reserves the decision.

## Reserved for the owner

Changes to the counter or the gates; abandoning a container or parking rows; any impossibility
claim (needs the `architecture_limit` evidence of `PIN_RESEARCH_WORKFLOW.md`, independently
reproduced); spending that exceeds the round budget below.

## Round shape and budget

Measure (fresh census, ledgers current) -> pick the highest expected pins per resource ->
run -> gate once -> land -> round document + receipt + HANDOVER/PIN_GOAL_PROGRESS top block +
memory -> commit. Budget per round: 8 hours wall or 3M subagent tokens without a gated landing
closes the round with a bounded-negative document. A round that lands nothing must still add a
measured negative that changes the next round's plan, or it is a repeat and is not run.

## Exit clause

The campaign stops, and hands back to the owner with a written state, when any of these holds:

1. The census reads zero genuine pins.
2. Three consecutive rounds each land fewer than five pins **and** the residue census, the
   module census and the model-capacity probes offer no untried lever with a stated expected
   yield. The closing document lists the remaining pins by mechanism class with what was
   tried on each, as bounded negatives, never as impossibility.
3. A legitimacy rule would have to bend to continue.
4. The owner says stop.

Nothing loops without a terminal condition: every background job has a completion event, every
round has a budget, and a repeated experiment on unchanged text is not an experiment.
