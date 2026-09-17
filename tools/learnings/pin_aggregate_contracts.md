# Aggregate-copy pin repairs: measured source contracts

## Alignment-sensitive records (2026-09-17)

At stock CDK, a halfword aggregate can naturally generate a runtime alignment
test, an unaligned word-pair loop, an aligned word loop, and a shared tail.
Do not infer two source algorithms from those retail branches. Preserve the
record's true alignment; casting the whole operation to a word-aligned record
would change the compiler's justified assumptions.

Positive: `dungeon/func_819C0000`, `LocalPoint { u16 x,y; }[3][3]`, 36 bytes,
alignment two, ordinary global to distinct stack object. At recorded
`2.7.2-cdk-G0 -fno-expensive-optimizations`, one aggregate assignment removes
eight copy pins and is exact at 314 words. Three unrelated pins remain; T2
tries them with no additional removal. All affected image gates pass.

Bounded negative: `dungeon/func_813315CC`, existing s16[8][3][3], 144 bytes,
alignment two. CDK reproduces all 210 instructions and roles but emits the
retained input binding's prologue pair early. Scalar-vs-aggregate expansion
and scheduler ordering explain this residual. This is not a universal exact
rewrite rule. Whole ordinary argument-role reconstruction remains open.

## Callee contracts before post-copy cursor preservation

Some m2c callers pass copy-end cursors as extra register arguments even though
the actual helper consumes only two arguments. Preserving those artificial
uses while replacing a manual loop makes unnecessary lifetimes real in C.
Establish the actual resident helper first; only discard pure unused values.

Positive: verified resident `func_8004491C` consumes entry and registration ID.
`dungeon/func_8132B300` becomes zero-pin exact at CDK after ordinary Copy48 and
two actual arguments replace the loop and four-argument call. Its old source is
exact at both recorded 2.8.1 and CDK, satisfying normal transition controls.
Bounds, fresh allocated destination, source caller and gates are reviewed.
No pointer narrowing or interface change is introduced.

Negative: `dungeon/func_81339700` with the same helper correction reaches
78 words and identical instructions but retains a two-indel schedule mismatch
at the next helper's argument move. That actual helper prototype also misses.
The narrow source scan finds six direct copy-cursor calls; this is not a
population-wide count of all helper uses.

Receipts and next experiments: `docs/PIN_RESEARCH_ROUND43.md` and the linked
source-hash-bound reviews. The round-42 mechanical generator remains advisory
and deliberately refuses runtime alignment arms; no recognizer expansion was
necessary to prove these new source relationships.

## Round 44 transfer bounds and typed registry access

`80D137FC` independently reproduces the 48-byte aggregate plus real two-argument
helper at 404 words, but its unrelated action pin remains. Erasing that pin
rotates saved arguments throughout the function. An exact copy transfer is not
automatically a pin-removal transfer.

The six-helper audit finds 35 over-arity sites in 893 currently pinned DUNGEON
files. Seven direct argument/pin-overlap rows all miss when real arity is paired
with related pin erasure. Two argument-only controls are exact without reducing
pins. Do not expand argument pruning into a blind erasure sweep on this evidence.
The known positive required correcting the whole copy operation as well.

Around an already ordinary Copy140, `8008E714` still kept a `void **` table alive
while spelling its subscript as integer shift/add/dereference. Replacing that
sequence with `record_table[saved_index]` removes the last pin and is exact at
recorded CDK, 110 words. Bare erasure misses by five substitutions: typed indexing
changes address expansion order and the base/result register roles. The existing
masked index and actual pointer registry establish the source relationship.
No aggregate, interface, qualifier or recipe change is involved.

A bounded inventory of ten lexical near matches finds no additional direct
member; it does not audit all semantic table accesses. Preserve the type and
element scale, and reject page-address or unknown-layout cases before transfer.
Full evidence and next questions: `docs/PIN_RESEARCH_ROUND44.md`.

## Round 45 complete typed roles and caller conversion

Position144 (`813315CC`) becomes exact at stock CDK with ten of eleven pins
removed when the aggregate is embedded in a complete typed reconstruction:
real position/output dimensions, object fields, actual three-argument render
helper and ordinary held-source alias. Copy replacement alone left the prologue
wrong. The alias-only control recovers argument roles and prologue; an earlier
probe changed alias and pointer/sentinel reuse together and wrongly blamed the
alias. Isolate one proposed cause before encoding it as a rule.

One existing position/sentinel binding is retained; ordinary integer sentinel
and unbound-register controls remain six indels away. Its pointer-derived -1
and inherited volatile accesses are unresolved legacy artifacts, not required
source facts. No new pin, volatile, fake use or extra argument replaces removals.

The actual caller passes s32 mode. Narrowing its declaration to u16 changes
allocation and misses53. Keeping the callee formal s32 with an explicit local
u16 conversion is exact and restores width agreement. Review real caller and
callee contracts together; matching one isolated body is insufficient.

The old source/2.8.1 and reconstructed source/CDK are exact endpoints of a
reviewed whole-C transition. Cross-controls are nonexact. Do not feed this into
the stricter automatic cell-switch path or claim unique historical attribution.
The existing generator/probe and comparator automate repetition; this combined
semantic repair still needs an independent positive before generic transfer.
See `docs/PIN_RESEARCH_ROUND45.md` and its source-hash-bound evidence.

## Round46 shared symbolic address from actual indexed use

Snapshot140's mutable source cursor hid repeated symbolic access. Replacing
only its second-copy source with the actual D_800E3E48[slot_index]140-byte
aggregate gives HIGH lifetime 8/savings 3. CDK naturally hoists it and reuses the
partial address for the lookup. Frame56 returns without page scaffolding.
The exact Sony executable's call-loop threshold is30; staged-call simplification
36->34->33->32 could not pass with life 1/savings 1. More real reuse matters more
than fewer operations. This is measured compiler behavior, not proof of the
original source or release.

The closer182/181 source retained dead old cursor initialization. Removing it
yields181/181 but swaps input/HIGH allocation. Do not keep dead setup as a
constraint. Cursor rebasing is separately visible in loop's induction-variable
combination. A partial first-loop transfer has 17 pins and13 register differences;
retaining its original record binding damages aggregate copy source roles.
The next source question is a real larger record containing the 140-byte prefix.

Independent cheap transfer: 8132E5EC's port arm already used the true helper
table. Direct table argument removes its only keep at stock CDK, with old source
exact at old/new recipes and portassembly identity. Caller parameter/return
declaration correction is independently exact. The measured effect cluster
contains 15 members, ten previously unpinned; the 144-byte shape has no sibling.
See `docs/PIN_RESEARCH_ROUND46.md`.

## Round47 global allocation effects across regions

Snapshot140's zero-offset typed prefix folds back into the same record pointer;
a typed registry only commutes two address additions. Neither solves the
13-substitution partial candidate. Do not repeat these names as new shapes.
Retained hard-register bindings in later regions enter the already-used set
that global allocation prefers, and can change earlier region roles. Removing
them is a valid counterfactual but did not produce an exact repair here.

The fully ordinary input/HIGH swap is explained by
`floor_log2(refs) * refs / live_length * 10000 * size`. Eliminating dead setup
raises HIGH references3->4, changing the logarithmic multiplier1->2. The
minimally live input's typed two-element ref array still becomes a separate
strength-reduced cursor: seven input references, priority1157 versus HIGH1176.
It improves real schedule, not allocation order. Seek an actual source/lifetime
relationship; never add fake uses or retain dead setup merely for priority.

The initial table-only follow-ups missed all three selected candidates among
96 additional allocator/helper rows. This was not exhaustion of the family:
two candidates had false noreturn calls to their own epilogues. At the already
solved bases, ordinary positive allocation arms ending in return-object and
falling through to return-zero match exactly at 2.8.1-G0. Direct callback/table
addresses then need neither global v0 binding nor keep/use fences: four and
six pins removed, independently exact 55/55 and 58/58. The callback keep had
been a real scheduler barrier, but diagnosing that barrier alone missed the
larger CFG error. Resolve branch destinations before tuning delay-slot source.

Two contiguous callback/function chains, nearby proven functions and the bank
header corroborate the local bases. Promote only the proven row extents.
The ordinary early-null-return spelling has distance 5 from branch layout;
the positive allocation arm is exact. This is measured at 2.8.1-G0, not a claim
of a unique original release. Seven single erasures in the corrected caller
still miss. See the round 47 receipt for all bounds and endpoint hashes.
