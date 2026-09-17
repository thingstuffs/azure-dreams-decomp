# Round 45: reconstruct complete typed operations

The 144-byte position-table function removes **ten pins**, leaving **6,050 in
1,276 rows**: 53 removed since the reopened 6,103-pin baseline. Independent
linked verification is exact for all 210 words; both covering DUNGEON windows
and SLUS MATCH, and the row database passes. One pin remains in this function.
See [the durable receipt](evidence/pin_research_round45_20260917.json) and
[independent review](evidence/pin_research_position144_review_20260917.md).

## Position table and effect initialization

`dungeon/func_813315CC` snapshots `s16 values[8][3][3]`, selects three components
by direction and color, initializes an effect, and writes a typed output table.
Reconstructing those structures and array operations recovers the allocation
that isolated copy replacement did not. The actual three-argument
`func_8003DB94` contract also removes a false render-pointer argument.

The fully unpinned typed source initially swaps the saved source/color roles.
A normal held-source alias fixes those roles and the entire prologue. The
result has all 210 words, with only the `-1` materialization and its two vertex
stores differing. An isolated control was essential: an earlier probe changed
both the alias and pointer/sentinel reuse, so it could not establish which
change disturbed allocation. The alias-only result disproves that initial
explanation.

Retaining just the existing position/sentinel binding to `$3` makes the entire
function exact at stock CDK. Its existing volatile accesses and pointer/sentinel
conversion remain; none was added to replace a removed pin. This is a ten-pin
repair, not a claim that the final binding is necessary or that every inherited
source artifact has been eliminated. Ordinary integer-scalar and unbound
`register`-hint controls retain the same six-indel residue.

The source and recipe must be reviewed together: the original is exact at
2.8.1, and the reconstructed operation at CDK. The stricter automatic
cell-transition rule is unchanged. Split symbolic addresses and stores in call
delay slots support the compiler family; they do not prove a historical release.

Caller consistency also changes the final source. Narrowing the caller's
fifth-argument declaration to `u16` misses by 53 substitutions. The exact repair
instead accepts its existing `s32` argument and explicitly converts that value
to local `u16`. CDK folds this to the same retail unsigned-halfword stack load.
The caller stays unchanged and exact, while the old width mismatch is removed.

## Snapshot140: identify the rejected compiler decision

The 24-pin snapshot remains nonexact, but its missing saved address now has a
specific cause. CDK creates a fresh `HIGH(D_800E3E48)` inside the second loop,
recognizes it as invariant, then rejects hoisting it as unprofitable: one saved
instruction, lifetime one, in a 36-instruction call loop. Allocation never sees
the across-loop high-half value that retail keeps in s7.

Reusing the existing ordinary buffer-base local restores the 56-byte frame
without a pin, but retains the full address instead of its high half. A fixed
runtime-address control emits `ori` address pairs and remains nonexact; the
relocatable E-region symbols fit retail's split `addiu` forms better. Correcting
the actual index helper's return and parameter widths does not change the
original mismatch.

The inverse and an independent initializer establish a logical saved-record
layout rooted at `0x80012194`, with four corresponding arrays. The old
`Global1004C`/page views are biased compiler cursors, not actual object roots.
The original declaration and packing remain uncertain. Straight indexing over
separate arrays grows the frame to 72 bytes; the grouped save view reduces it to
64, still above retail's 56. This rejects those lowerings, not the recovered
save-format relationships.

Next, compare minimal real loop RTL with the staged lookup arguments removed,
measuring the invariant's lifetime, savings and loop instruction count before
more source experiments. Independent compiler-provenance evidence remains
another route. No page value, fake use or per-function compiler patch should be
invented to override the diagnosed profitability decision.

## Mechanical repetition

The existing aggregate generator, explicit-recipe probe, pin-erasure cascade
and strict comparator cover repetitive candidate production and scoring. This
round needed no new framework. The new positive combines complete typed source
roles and actual helper/caller contracts; it is not yet an independently
validated generic rewrite. Keep those semantic prerequisites explicit when
selecting siblings, then automate the bounded compile/score work. The previous
seven helper-arity/pin-overlap negatives already show that deleting surplus
arguments alone is not a general removal rule.
