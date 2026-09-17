# Round 52: measured metadata transfer and exact compiler attribution

**6,028 pins remain in 1,271 functions; no pin removals this round.**
Eight independently reviewed, incorrect dungeon `noreturn` entries are removed.
All 15 affected rows, all 18 covering windows, SLUS and the row database pass.
No production C, recipe or compiler/assembler implementation changes.
The [durable receipt](evidence/pin_research_round52_20260917.json) preserves
the scripts, sources, controls, reviews and compiler observations.

## The mechanical census result

The alias-aware lexical index reads current dungeon C once (11.9 MB), strips
comments and strings, canonicalizes `names.tsv` aliases, and separates top-level
declarations/definitions from body call tokens. Of the 934 stale names after
round 51, **29 are called in 31 source files; 14 have visible definitions**.
This is a candidate index, not a complete C parser or a bank-identity proof.
The wider round-51 figure of 114 included definitions, declarations and comments.

Eight candidates have reviewed returning definitions and callers in proven
matching banks: `800240EC`, `8002443C`, `800243B8`, `801744DC`, `800249E4`,
`80174BC8`, `80172050`, and `80025B78`. The last has weaker caller evidence
because its caller immediately returns; its definition explicitly returns an
object or null. Each receives a separate review, not a blanket stale-name rule.

Same-source/current-versus-one-entry-filtered controls are exact and unchanged
for all eight cases, covering seven caller rows. A second diagnostic erases all
83 pins across those seven callers. None becomes exact, and none changes bytes
when its reviewed census entry is removed. That is **zero demonstrated pin
unlocks in this batch**. The corrected metadata prevents false non-returning
claims in future reconstructions; it is not reported as a source improvement.

The canonical census now has 1,036 entries. The frozen stale inventory has 926
remaining names. Preserve candidate-owned local declarations; do not regenerate
or prune the remainder from absence alone. The [review](evidence/pin_research_census_round52_review_20260917.md)
records same-bank proofs, surplus-argument/prototype debts and index limitations.

## Switch: memory classification changes scheduling

For `819C0C18`, the first scheduling pass moves the scalar `D_8002992E` store
past the child-pointer load. The preceding combine input retains source order.
The existing barrier supplies the otherwise absent dependence. A targeted check
with first scheduling disabled fails both endpoints: 343/334 words and 93 edits
with the barrier, 342/334 and 96 edits without. There is no basis to change the
recorded `2.7.2-cdk-G0` recipe.

Five same-bank siblings declare this global as `s16[5]`, while two declare it as
a scalar. A single unsized-array diagnostic changes the global RTL memory
classification from scalar to aggregate and restores scheduler dependencies.
The zero-pin switch improves from **332/334 words, 23 edits** to **333/334 words,
six substitutions and three indels**. Its child-pointer load still moves above
the final effect-field stores, eliminating a stall retail retains. It is not exact.

The [independent layout review](evidence/pin_research_global_array_review_20260917.md)
finds strong evidence only for a halfword at offset zero. Every use accesses
element zero. The five-element extent dates to initial import and likely serves
the old `-G8` size threshold; it is not recovered array-layout evidence. The
unsized view is a diagnostic, not a verified source repair. Do not spread this
declaration change mechanically merely because it improves one score.

## Transition: the precise zero-copy owner

Luna's bounded follow-up compares the exact six-pin baseline, the five-pin
one-substitution candidate and the existing row-entry reset. Literal zero
survives through `lreg`; the copy from `s3` first appears in `greg`. This corrects
the earlier attribution to ordinary pre-allocation CSE. No new source hypotheses
were needed for this boundary measurement.

Root then traced the actual CDK executable without modifying compiler RTL or data.
At `reload_cse_simplify_set`, instruction 362 enters as `s1 <- const_int 0`.
The equivalence search rejects registers 0 through 16 and 18, skips destination
17, and accepts register 19 (`s3`). The instruction leaves with `s3` as its
source. The normalized traced assembly equals an ordinary compile of the same
candidate. **Post-allocation reload CSE is the measured owner.**

The row-entry reset had avoided the copy but swapped `s1/s2` at 22 sites. Its
counter references/lifetime change from 33/148 to 30/145, changing global
allocation order. That is a separate, measured consequence. Repeating either
initialization form will not resolve the coupled allocation and cached-value
questions. The candidate remains 224/224 words with one substitution.

A narrow inventory finds **24 live explicit zero-register bindings in 22
files**, including this case. Macro definitions are excluded by the site parser.
These are potential independent controls for the zero-value investigation,
not 24 proven instances of the same compiler decision or promised removals.

## Next bounded work

- Follow the exact compiler's zero-value recording and invalidation across the
  second traversal's real control-flow joins. Select at most two genuine source
  lifetimes that avoid the cached copy while preserving register roles.
- For the switch, establish the actual global/object memory relationships before
  another C hypothesis. Keep the improved diagnostic and its missing load stall
  as the measurement target; do not invent aliases or dependent uses.
- The metadata batch has measured zero pin yield. Give subsequent metadata
  cases priority when a raw-compiler/processed-assembly discrepancy implicates
  them, instead of treating all 926 stale names as equally promising pin work.

The zero-pin objective remains active. These results narrow the next experiments;
they establish no impossibility or unavoidable minimum.
