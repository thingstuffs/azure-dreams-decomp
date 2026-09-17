# Round 43: preserve real copy and helper contracts

**6,061 pins in 1,277 rows: nine removed this wave, 42 since restarting.**
Baseline was `1f808e00` with 6,070 pins. Two source repairs landed through the
normal hash-bound application path. All three affected DUNGEON windows and
SLUS MATCH; row database OK. [Durable proof](evidence/pin_research_round43_20260917.json).

## Eight pins from one ordinary assignment

`dungeon/func_819C0000` snapshots a 36-byte `LocalPoints` global into a stack
object. Its nine pairs of halfwords have two-byte alignment. The manual source
had separate aligned/unaligned loops, a tail, three register bindings, two keeps
and three barriers. A single assignment using the existing type naturally
reproduces that whole operation, including the runtime alignment test.

The result is exact at the recorded stock CDK recipe: 314/314 words. Eight copy
pins disappear; three unrelated pins remain. The existing erasure cascade tried
those three once and found no additional removal. The candidate preserves the
original unscored source text and applies the aggregate operation to both build
paths; it does not move the old loop or pins into an inactive arm. Global and
stack objects are distinct, the extent and alignment are unchanged, and the
function interface is unchanged. [Review](evidence/pin_research_points36_review_20260917.md).

## One pin from correcting a false helper dependency

`dungeon/func_8132B300` copies a 48-byte render record into newly allocated
storage. Merely replacing the loop while preserving its advanced cursors misses.
The missing fact is the actual resident helper contract: verified
`func_8004491C` takes two arguments. The third/fourth arguments in these
reconstructed callers are incidental copy cursor values, with no side effects.
Removing those arguments together with the aggregate copy gives zero-pin C,
exact at CDK (114/114 words). The old source is exact at both the recorded
2.8.1 and CDK recipes, so the standard cell-transition controls pass.

Independent review establishes the sole caller's source extent and allocator's
fresh, aligned 48-byte destination. No caller interface or pointer width changes.
The existing registration-key representation debt is unchanged.
[Review](evidence/pin_research_copy48_review_20260917.md),
[helper evidence](evidence/pin_research_registration_helper_20260917.md).

## What the negative controls changed

- `81339700`: the same real helper/copy repair reaches 78 words with identical
  instructions, but the next call's `move a0,s0` is scheduled three positions
  late. Its actual helper prototype does not fix this. Investigate that
  argument's scheduler dependency before more copy spellings.
- `813315CC`: a 144-byte halfword aggregate naturally emits both alignment
  paths. CDK recovers all 210 instructions and register roles, but saves/moves
  s3 too early. RTL explains why: the retained input binding occurs before
  aggregate address/alignment expansion; moving it after the copy coalesces it
  into the entry move. Real pointer staging does not change the result. The
  next route is ordinary argument-role reconstruction or evidence for a real
  operation boundary, not an invented dependency.
- `800BEA7C`: three bounded source probes confirm why combine deletes its
  one-use payload pointer. Owner recovery preserves the add but already emits
  the wrong load base in initial RTL. More logging of the same predicate would
  not supply a new source fact. Seek an independent exact sibling or compiler
  provenance before another spelling menu.
- `8009DB44`: its volatile tail remains a semantic-review case; it was excluded
  from this conservative transfer, not declared impossible.

The successful alignment-sensitive copy extends the known family beyond the
round-42 recognizer. No parser expansion was necessary to prove it. Preserve
actual aggregate alignment when transferring: replacing a halfword record with
a word-aligned record would remove the very branch retail contains. Recognized
helper contracts can remove false lifetime requirements before mechanical
copy generation; they must be established from the actual callee.

Bounded reports: [48-byte cohort](evidence/pin_research_copy48_round43_20260917.md),
[144-byte scheduler cause](evidence/pin_research_position144_causal_20260917.md),
[field combine cause](evidence/pin_research_field_round43_20260917.md).
No compiler/toolchain patch, replacement pin, or impossibility verdict was used.
