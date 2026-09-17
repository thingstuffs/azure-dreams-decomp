# Pin-removal research: zero pins

## Active objective (2026-09-17)

The owner has superseded the 500-pin/plateau stopping rule below. The objective
is **zero genuine C pins**, or a demonstrated unavoidable minimum with a clear
explanation. Failed searches, current compiler coverage and unexplained C shapes
remain unresolved research questions; they do not establish impossibility.

Starting point: **6,103 pins in 1,284 rows**, commit `bd28d6cf`.
Four changes are being implemented together: whole-function reconstruction from
retail register roles and control flow; causal compiler-decision explanations;
compiler/assembler provenance audits; and independently controlled family
transfer. The historical rubber-duck method is part of reconstruction: explain
the compiler decision in ordinary language, ask what real source would produce
it, predict an intermediate effect, then compile a small discriminating probe.
Existing allocator traces and counterfactual tools are reused, not replaced.

Recipe reconsideration is allowed when supported by mechanism and provenance
evidence. A matching compiler cell is not, by itself, proof of historical
lineage. Exact retail bytes, source semantics, caller consistency and full
affected gates remain required; function-specific toolchain substitutions and
replacement pin scaffolding do not count as removals.

See [PIN_RESEARCH_WORKFLOW.md](PIN_RESEARCH_WORKFLOW.md) for the research and
transfer contract. The campaign history below records the previous objective.

Round 39 first gated result: **6,102 pins in 1,283 rows (-1)**. Ordinary returning
C for `dungeon/func_81811388` becomes exact when the inherited volatile table
pointer is removed together with its input binding, using stock CDK split-address
generation. The old pinned source is exact at CDK too. Same-image callers and
helper definition substantiate the return repair. Affected window and SLUS MATCH;
row database OK. See [PIN_RESEARCH_ROUND39.md](PIN_RESEARCH_ROUND39.md). The first
small transfer cohort has no independent positive yet, so this is a verified
individual repair, not a demonstrated population-wide rule.

Round 40 gated result: **6,098 pins in 1,282 rows (-4; -5 cumulative)**.
The rubber-duck reconstruction recovers `80878974` as a 52-byte record copy and
three diagnostic calls. GCC's aggregate block-move RTL naturally preserves the
copy-tail schedule; the old-ASPSX constant convention removes the unsigned
zero-register carrier. Semantic review, exact row, full TOWN window, SLUS, and
row database pass. Independent `800A23CC` transfer removes two more pins with
an 84-byte record assignment; its full scene window matches. Three other copy
rows remain nonexact, and the 88-byte lineage probe is two words away at stock
2.7.2 with unresolved recipe-transition evidence. See
[PIN_RESEARCH_ROUND40.md](PIN_RESEARCH_ROUND40.md).

Round 41 gated result: **6,071 pins in 1,279 rows (-27; -32 cumulative)**.
Two complete initializer reconstructions remove 19 and six pins with real
88-byte/24-byte aggregate assignments and reviewed stock recipe transitions.
Recovering the actual entry return removes the last two pins in `800A23CC`;
its wrapper and direct caller contracts are aligned. All five changed rows
are exact, all four affected windows and SLUS MATCH, row database OK.
The ordinary source and stock recipe must be considered together for whole
reconstructions; the generic automatic cell-switch rule stays unchanged.
The Pair24 control remains nonexact with a specific page/source lifetime
question. See [PIN_RESEARCH_ROUND41.md](PIN_RESEARCH_ROUND41.md).

Round 42 gated result: **6,070 pins in 1,278 rows (-1; -33 cumulative)**.
The previously nonexact Record68 source is exact at stock CDK; the old pinned
source is exact there too, so the standard controlled cell transition applies.
Independent caller review, strict row bytes, full town scene window, SLUS and
row database pass. Local allocation timing explains the copy register change.
A bounded mechanical copy generator/probe workflow reproduces the 68-byte and
84-byte repairs plus a pin-free control; it refuses two complex historical
initializers. The TOWN cohort audit finds no new trivial member. Field, group and snapshot
initializers have specific unresolved compiler decisions rather than an
impossibility verdict. See [PIN_RESEARCH_ROUND42.md](PIN_RESEARCH_ROUND42.md).

Round 43 gated result: **6,061 pins in 1,277 rows (-9; -42 cumulative)**.
An alignment-2 aggregate snapshot removes eight pins at its recorded CDK recipe;
correcting a real two-argument helper contract together with a 48-byte copy
removes one at a controlled CDK transition. Three affected windows and SLUS
MATCH; row database OK. The changed-row erasure cascade finds no more.
Two related copies now have isolated scheduling residues, and the field case
has a concrete combine explanation. No new parser or compiler patch was needed.
See [PIN_RESEARCH_ROUND43.md](PIN_RESEARCH_ROUND43.md).

Round 44 gated result: **6,060 pins in 1,276 rows (-1; -43 cumulative)**.
A typed pointer-table subscript replaces a pinned integer address calculation
at its recorded CDK recipe. Independent strict bytes and semantic/caller review,
full DUNGEON engine, SLUS, row database and research-ledger validation pass.
Mechanical follow-ups are bounded negatives: ten typed-lookup near matches yield
no direct member, and seven real-helper-arity/pin-overlap candidates yield no
exact removal. The copy repair transfers exactly elsewhere but leaves an
unrelated argument pin. Return to complete operation/argument-role reconstruction
with these measured contracts, then transfer the next demonstrated mechanism.
See [PIN_RESEARCH_ROUND44.md](PIN_RESEARCH_ROUND44.md).

Round 45 gated result: **6,050 pins in 1,276 rows (-10; -53 cumulative)**.
Complete typed Position144 reconstruction, a real helper contract and ordinary
held-source alias recover the copy, argument roles and prologue. One existing
position/sentinel binding remains unresolved. The caller's s32 contract stays
unchanged; an explicit local u16 conversion keeps exact bytes. Independent
linked210/210, both covering windows, SLUS and row database pass. Snapshot140
now has a specific invariant-hoisting profitability diagnosis and corroborated
save layout; no new pin removal there. Mechanical tools are reused for bounded
repetition, with no unproven generic rewrite. See
[PIN_RESEARCH_ROUND45.md](PIN_RESEARCH_ROUND45.md).

## Previous objective: 500 new removals or a measured plateau

Objective completed at the measured plateau: continue small, hypothesis-driven waves; prove a source fix,
transfer it cheaply, adapt to results; stop after 500 new pins are removed or
measured removals plateau with no productive approach remaining. The initial
round-35 ten-pin demonstration is outside this goal's counter.

Baseline: commit `500808e2`, **6,138 pins in 1,292 rows**. Goal target if reached:
5,638 pins or fewer, without inventory redefinition or replacement scaffolding.
Fixed row recipes, independent exact verification, source-hash checking, and the
applicable overlay/SLUS gates remain required. A stopped budget is a bounded
negative, not a proof of impossibility.

## Round 36 (gated)

- Proper pairs inside larger pinned integer families: 234 rows, 28,499 screens,
  11 rows reaching a 400-screen cap. One verified result: `dungeon/func_81084D04`,
  two register bindings removed while `step_x` becomes `s32`. Its values are
  explicitly truncated to `u16` before use, so the signed local preserves values.
  `tile_x` stays `s32`. The matching `u32` pair alternative was not selected.
- Five same-callee transfer rows: 1,227 additional screens, no hits, two capped.
  This was a bounded family transfer; it does not establish width-space exhaustion.
- Return repairs: one Sol agent audited all seven strict pinned/non-void/bare-return
  rows and reviewed a 36-body syntactic fall-through inventory. Three verified
  one-pin repairs (`dungeon/func_80086E64`, `town/func_80097340`,
  `town/func_800C49C4`); four bare-return negatives, no additional straightforward
  fall-through case. 34 distinct candidate screens, 40 full verifiers including
  controls and independent rechecks. Return expressions make actual results live
  instead of preserving them with keeps.
- Caller return declarations corrected to the unique same-container callee return
  type: 249 rows, 3,313 screens, 8 screen-hit rows, **zero fully verified hits**
  (11 full verifiers). No prototype edits landed. Screen equality is not byte proof.
- `town/func_8080E838` aggregate-copy hypothesis: 10 source forms (whole 88-byte
  copy, paired 88/24-byte copies, and 16-byte chunk copies, as aggregates or
  builtins with pin-erasure variants), no exact result. Whole aggregate copy
  reproduced the loop structure but chose different register roles. The old arc
  loop wall `809A38E4` was read and baseline-erased once; the prior multi-agent
  investigation already covers the obvious loop/angle directions, so no new
  mutation campaign was launched there.

Four functions / **6 pins removed**, including one extra from the changed-row
`t53_reg_state` cascade (`80086E64`, the remaining binding). Current count:
**6,132 pins in 1,290 rows; 6/500 toward the goal**. Two newly pin-free rows.
All five changed overlay windows MATCH (244 seconds), SLUS SHA-1 MATCH, row
database OK. This is progress, not a plateau; the goal remains active.

Artifacts: `work/native_lane/r36_width/`, `r36_returns/`, `r36_proto/`,
`r36_struct/`. The return lane's report gives every tested negative and result.

## Round 37 (gated)

- The boolean-return-width probe on `80094A20` failed: ten candidates all total9.
  Sol reconstructed the tail-failure/shared-return join in `800A21EC`; nine
  reasoned candidates and two full verifiers split the required features:
  shared joins preserve layout but miss allocation (11), direct returns recover
  allocation but invert the branch layout (5). No return repair landed here.
- A fresh width-pair fix in `81084D04` narrows `tile_y` and `next_y` to `u16`,
  removing the latter's binding. `tile_y` is unpinned, so the earlier pinned-only
  pairs excluded it. Either narrowing alone fails (41/2), both exact. Direct
  local-copy transfer:182 rows / 2,436 screens, only this exemplar exact.
- Parameter/local copies are more productive: change both ends together.
  Separate-assignment pilot118 rows / 1,150 screens found 10 exact rows. The
  bound-initializer spelling adds52 rows / 462 screens (164 unique total),
  finding5 more. Composing on these15 winners adds10 pins in 79 screens,
  including one plain binding erasure unlocked by the width repair. Final
  parameter lane:27 pins in 15 rows. All candidate outputs fully byte-verified.
- Source-range review: narrowed values feed 16-bit stores/casts/masks/shifts.
  One Sol agent independently reviewed all 15 rows and the composed coordinates.
  Same-file prototypes follow parameter changes; definite cross-TU declarations
  are being checked separately, with overlay identity established before edits.
- Standard landing accepted all 16 functions / 28 pins; changed-row cascade added
  two more (`80BAF094` binding and `800BEE14` angle-copy width). All20 changed
  overlay windows MATCH in 249 seconds; SLUS MATCH; row database OK. That first gate covered 30 removals. Caller review then required withdrawing
  `80287768` (one pin): its caller's compatible prototype could not stay exact,
  even after eight bounded caller/callee repairs. Nine other caller declarations
  were corrected exactly; all nine correction windows and SLUS MATCH (247 seconds); row database OK. Retained wave:
  **29 pins removed in 15 functions, six newly pin-free. Current: 6,103
  pins in 1,284 rows; cumulative goal progress 35/500.**
- `tools/xform/t70_copywidth.py` encodes the parameter/local repair. Five focused
  tests pass; it reproduces all 15 independently verified initial candidates.
  The automatic sweep refuses unreviewed signature changes; `candidates()`
  supports a batch whose callers are checked. No recipes, compiler flags,
  assembly, or replacement scaffolding changed.

Artifacts: `work/native_lane/r37_bool/`, `r37_param/`, `r37_returns/`.

## Round 38 follow-ups (no removals)

- Beyond the pilot size limit: all six eligible functions / 60 screens, no hits.
- Coherent groups of direct parameter/local copies: 71 rows / 426 screens, no hits.
- Explicit short-cast parameter copies: 6 rows / 7 screens, no hits.
- Caller/callee return-type repair together with a pinned result local's width:
  3 eligible rows / 3 screens, no hits. This tested the reverse edge of the
  paired argument repair, with actual callee definitions as evidence.
- Sol audited void definitions that definite same-image callers use for a
  scalar value: two strong definitions / four definite caller relations. Eight
  reasoned candidates, eight full verifiers, zero exact. `81811388` keeps an
  input argument in v0 (best distance 5); `800A23CC` needs a particular branch
  join (best distance 3). A third name relation was excluded because the return
  is discarded in a comma expression. No source changes or gates in round 38.

## Final result and evaluation

**Stopped at the plateau condition: 35 additional pins removed, 6,103 remaining
in 1,284 rows. The 500-pin target was not reached.** The initial ten-pin
round 35 demonstration is outside this goal, so total removal across the initial
request and continuation is 45. Gated implementation checkpoints: `85f57ff1`
(round 36, six pins) and `a6cb5c82` (round 37, 29 pins net). The final source tree has
passed every affected overlay window and SLUS; row database OK; five generator
boundary tests pass. One exact candidate was withdrawn to preserve caller type
agreement. No recipe or toolchain changes and no replacement scaffolding.

The broad proper-pair extension paid one exact row in 234 rows / 28,499 screens.
The evidence-led parameter/local repair paid 14 retained rows in 164 unique rows
/1,612 initial screens, then benefited from composition and the cleanup cascade.
That is the useful improvement over spending model time on many independent
near misses: find a missing source fact, test a finite related family cheaply,
and verify complete bytes plus caller consistency before landing. A normalized
compiler-listing match remains only a screen; the return-prototype experiment
had eight screen-hit rows and zero byte-exact results.

The final plateau measurement covers all six larger eligible functions, 71
coherent copy groups, six explicit-cast cases, three paired return/local cases,
and both strong void/scalar return contradictions: 88 row-visits / 504 candidate
screens, no exact removal. These are bounded negative results, not a proof that
all 6,103 pins are irreducible. The current productive mechanisms have no further
unmeasured concrete transfer in this audit. The remaining catalogue is dominated
by allocation, scheduling, and assembler-side residues already investigated in
prior campaigns. Another campaign needs new source/typing or toolchain evidence
to justify reopening those cases; simply enlarging the same menus is unlikely
to repeat the gains above.

Round 38 artifacts: `work/native_lane/r38_large/`, `r38_cast/`,
`r38_returnlocal/`, and `r38_void_returns/`. The four extra signature-repair
negatives are in `r38_sig/` and belong to the round 37 withdrawal decision.
