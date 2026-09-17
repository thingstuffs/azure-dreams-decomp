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
