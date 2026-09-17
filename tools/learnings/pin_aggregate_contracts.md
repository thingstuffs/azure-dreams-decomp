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
