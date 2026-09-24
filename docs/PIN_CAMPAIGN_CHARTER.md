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
   4b. **Coherence repairs** (added 2026-09-18, round 56): a switch *toward* the row's module
   census recipe, with a new text that is byte-exact there, is admissible even though the
   current text is not exact at the new recipe (rule 2's purpose, no byte evidence lost, holds
   because the new text reproduces retail; the old text and recipe stay in git and in the trade
   ledger). It lands through `tools/lanes/land_coherence.sh`, which verifies before it switches
   and restores the recipe if the candidate does not land, and it is reported separately from
   pin removals. The owner may veto the clause; until then it applies.
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

## Working method (added 2026-09-22, after the 1,293-pin day)

The owner's standing direction (2026-09-21): the session architects and decides from the data; Opus and Sonnet do the
bounded work; every pack row carries a rubber-duck brief; astra or sol on whole functions or on mechanisms, either is
good; Fable takes a mechanism only after both models failed, and sceptically; a documented pin-for-uglier-C trade is
acceptable; no busy work while jobs run; and **the process itself is changeable - "don't be confined by the current
shape or process"**.

The loop that paid: (1) census the pins, rank rows by pin count; (2) build duck-briefed KIT packs
(`tools/lanes/build_class_pack.py --rows --duck` + `tools/lanes/kit_pack.py`), astra on 13+-pin rows, sol on 12-8;
(3) run them through `tools/lanes/pool.py`, land continuously with `tools/lanes/land_finished2.sh` (isolated);
(4) harvest every wave's REPORT.md moves into generators (move tables in `docs/evidence/`), sweep with
`gen_drive.py --fresh`, land, `refresh_exemplars.py`, `clone_transfer.py`; (5) when yield flattens, run the
retrospective: mine the session logs, fix the tooling or the brief, A/B on the next wave. Measured on 2026-09-21: the
kit took astra from ~2 rows per 5-row pack to 38 of 40. See docs/PIN_RESEARCH_ROUND62.md (rounds 68-72) and
docs/LANE_KIT.md.

## Rulings 2026-09-24 (later) — owner sign-off: recipe from retail evidence; hidden scaffolding on the ladder

1. **Coherence toward the retail-proven recipe (amends clause 4b).** Owner: "Ok, it sounds like that needs to be
   done." A coherence repair may move a row toward the recipe its RETAIL BYTES prove (the split-address fingerprint,
   `tools/fidelity/split_fingerprint.py`, docs/evidence/fidelity_step2_split_fingerprint.md), not only toward its
   module census recipe, provided the new text is byte-exact at the new recipe. Where the evidence cannot separate
   two cells (slus: 2.7.2-cdk vs 2.8.1 both split), choose the cell at which the natural C is exact; if both, the
   cell of the TU's neighbours; record the evidence in `ledger/recipe_trades.jsonl`.
2. **Hidden scaffolding belongs on the L0-L5 ladder.** Owner: "a whole function as .word data is a missing function
   right? We need to expose these and fix them through the L0-L5 pass, somewhere." Implemented: a function whose
   body is emitted by top-level asm (`.ent` in an `__asm__` string) is a blocking fidelity site, so the row is L0
   (`tools/levels.py` WHOLE_ASM_FN_RE; slus/w_8005A1D0 L3 -> L0, the only such row). Planned after fidelity step 1:
   L4 residue kinds `cell_imitation` (unpinned page literals the fingerprint shows are split symbols) and
   `maspsx_dependent` (rows exact only through a maspsx pass genuine ASPSX lacks).
   IMPLEMENTED 2026-09-24 after fidelity step 1 (tools/levels.py, fidelity_index): `cell_imitation` = retail strict
   fingerprint (ledger/split_fingerprint_rows.jsonl) at a registered non-splitting cell, blocks L4, clears when the row
   moves; `maspsx_pass` = exact only through a source-driven maspsx rewrite genuine ASPSX lacks (cdk-imitating `la`
   passes, jal->j and marked-slot rewrites), blocks L4; `maspsx_dependent` = exact only through the toolchain MODEL
   (the pre-July-1997 cc1 epilogue rules, the small-extern $gp model, the pre-2.56 ASPSX dials) - not the C's fault -
   blocks L5 only (ledger/maspsx_dependence.jsonl from docs/evidence/fidelity_step1_maspsx_dependent.tsv).

## Rulings 2026-09-24 — owner sign-off for rule 5 (NON_MATCHING arm retirement)

Owner, verbatim, asked "When a pin-free rewrite leaves a NON_MATCHING arm with nothing to do, may the arm be deleted?":
"yes, it may".

**Rule (`tools/pin_census.landing_refusal`, `_arm_retirement`):** a candidate may delete WHOLE `NON_MATCHING` blocks.
Every port block it keeps must be verbatim one of the current text's (none edited, none added), at least one must be
gone, `#if 0` text must be unchanged, and the -DNON_MATCHING port front end must still accept the candidate (a
deleted block the code still uses is refused there). Editing a kept arm still needs the textual or port-codegen
identity as before. First use: town/func_80953900 (lane r77_opus_m3, 3 -> 0 pins; the port arm assigned a page
variable the pin-free text no longer has), 3,210 -> 3,207.

## Rulings 2026-09-23 — owner sign-off for rule 5 (pin inside a local macro)

Owner, verbatim: "3706 seems like the more accurate count so we should probably do that".

**Rule (`tools/pin_census.sites_of`):** a pin inside a function-like macro counts once per call of that macro in
compiled code, not once per definition. This covers file-local macros defined in compiled (non-port, non-`#if 0`)
text whose body carries `ASM_*` pins. A body pin written without its `;`, an object-like macro, and a macro nested
inside another macro are covered too, so rewriting a macro body cannot hide a pin. A macro with no compiled call
contributes nothing. When a landing removes a call, or makes the body pin-free, it removes those sites. Each
additional expansion is an `expand` site tuple that erases nothing: to remove it, edit the call or the body.
Measured on the same tree: **3,701 -> 3,706 sites, still 902 rows**. The change affects 2 rows:
dungeon/func_807B0B3C (24 -> 27: `FINISH_GLOBAL_TABLE`, 4 calls) and dungeon/func_818B7F38 (13 -> 15:
`LOAD_TABLE_X_BASE`/`LOAD_TABLE_Y_BASE`, 2 calls each). `hidden_asm`'s wrapper-call count drops 9 -> 0, because those
calls are now counted pins. Evidence: `docs/evidence/r76_pin_count_discrepancy.md`.

## Rulings 2026-09-22 (evening) — owner sign-off for rule 5 (census/level changes)

Owner decisions, verbatim gist: (1) official ASPSX never rewrites `jal`→`j`, so a retail `j` to a "function" symbol
means the row may have been split wrong; "that deserves a check before it goes to L3 or at least a level should
check". (2) the sibcall/noreturn-tail-jump scaffolding "needs to be covered by a level, somewhere". (3) site-for-pin
trades are OK "as long as they're tracked; L4 is where we start to draw the line on pins". (4) tier B of
`config/void_callees.txt` (call-site evidence only, no callee image on disc) stays, marked.

**New rules (`tools/levels.py`):** L3 additionally requires every tail-jump dependency of the row — a noreturn
pseudo-call in the text, or a call to a symbol in the row's container `config/sibcall_syms*.txt`/
`config/noreturn_syms*.txt` — to carry a `ledger/split_audit.jsonl` record (schema `azure-clean.split-audit.v1`)
whose `kind` is neither `intra` (mis-split) nor `unresolved`; a row with none is unaffected. L4 = the module
criterion (`l4_modules` sweep) AND pins == 0 (strict, not the `t2_pins` sweep loophole; a site-for-pin trade counts
as a pin here, per decision (3)) AND zero tail-jump dependency of any kind, audited or not. L5 = the old L5 minus
what moved to L4 (fidelity site of any audit class, computed-goto, inline asm, `NON_MATCHING`). `ledger/levels.jsonl`
carries `tail_jumps`/`split_audit` per row and a new `l4_residue` (`pins`/`tail_jump`/`not_in_module`) alongside
`l5_residue`. Measured with `ledger/split_audit.jsonl` at 347 records (concurrent Opus work): 48 rows / 22,724 B
sit at L2 instead of L3, unaudited-or-intra — see `docs/HANDOVER.md`'s 2026-09-22 evening paragraph for the
per-container count and the population still needing a split-audit record.

## Rulings 2026-09-22 (afternoon, goal round)

Owner decisions, verbatim gist: (a) a LABEL_AS_CALL / intra-tail-call site whose target has a
`ledger/split_audit.jsonl` record of a DECIDED non-intra kind (`cross-segment` or `cross-image`) is a real
inter-module jump, not scaffolding for this row, so it no longer makes the row `blocking` (L0) — "im ok with a
level change as long as it's picked up at some level." (b) site-for-pin trades may add TWO tracked pins when
one is not enough (previously one) — "accept 2 pins." (c) partial landings of a multi-site row (fewer sites,
bytes exact, no level change) are allowed — "land site-b." (d) a `NON_MATCHING` arm may be edited in lockstep
with the row's compiled arm to make a site pin-free — never deleted, both arms move together — so a site whose
only occurrence sits inside a `NON_MATCHING` block is not permanently rule-blocked. `dungeon/func_818B6AFC`
landed under this ruling (site_for_pin trade: ASM_USE_NV(`render_owner`); pins 16 → 17, `pins_after_live` 14;
`ledger/recipe_trades.jsonl` round `l0_goal_20260922`).

**New rule (`tools/levels.py`):** a LABEL_AS_CALL site whose target carries a DECIDED `cross-segment`/
`cross-image` split_audit record for THIS row — and the same exemption for an `intra_tail_calls` hit whose
target carries one — no longer counts toward `blocking`, so such a row can reach L3 (the L3 audit gate already
accepted those kinds). L4 is unchanged: it still requires zero tail-jump dependency of any kind, so the site is
picked up there — `tools/split_audit.py` only ever audits `tail_jump_targets` members, so an exempted target is
by construction already counted in `tail_jumps`. PASSTHRU_NO_ARGS is unaffected. Measured effect:
`town/func_8047E0D8` (the callback dispatcher; target `func_80016120`, kind `cross-segment`) moves L0 → L3 with `l4_residue` still
carrying `tail_jump`; the same run also cleared three devkit-blob rows (`town/func_808B8184`, `func_808B85F0`,
`func_808BB138`) whose LABEL_AS_CALL targets picked up new `cross-image` (`image: "kernel"`) records from
concurrent `split_audit.py` work in the same window.

## Ruling 2026-09-23 — dead zero initializer at a declaration is ordinary C

Owner, verbatim: "looks like a legitimate attempt a dev might do for variable initialisation, maybe as a coding
standard or habit. so agree."

**Rule:** a `= 0` / `NULL` initializer at a local variable's **declaration** is ordinary C even when the value is
never read. It emits no code, but it makes the variable set more than once (REG_N_SETS > 1), which is what an
`ASM_KEEP` pin fakes. gcc 2.x's `-Wall` "might be used uninitialized" warning is a period reason such
initializers exist. It does **not** cover dead assignments added between statements; those stay under rule 3's
dead-store ban. Each landing that relies on it is recorded as a spelling trade, for later review. The first case
is `dungeon/func_809CAE20` (lane r76_opus_b12_2): `void *effect = 0;` replaces `ASM_KEEP(allocated_effect)`.
