Publication update: the accepted candidate has landed and passed all affected
windows and SLUS; see [the round-43 receipt](pin_research_round43_20260917.json).
The review below records its pre-publication state.

Working paths in this review snapshot refer to `work/native_lane/r43_dungeon_copy`.

# Round 43 bounded DUNGEON aggregate-copy investigation

The investigation selected two fixed 48-byte copies and stopped after three
source models per row.  It added no parser or production scaffolding.

## Exact result

`dungeon/func_8132B300` has a reviewed zero-pin aggregate candidate at
`out/dungeon/func_8132B300.c`.  It is exact only at `2.7.2-cdk-G0`; the unchanged
source is exact at both the recorded and control cells.  `verify.json`,
`REVIEW.md`, the base-SHA sidecar, and `cells.jsonl` make the result reviewable
through the normal application path.  It has not been exported.

## Bounded negative

`dungeon/func_81339700` is also a complete 48-byte copy from the current
object's render data into a freshly allocated object's render storage.  The
grounded two-argument helper candidate is
`raw/81339700/aggregate_real_call.c`, SHA
`4b446d7400a84147aacb8de10338a0bec5d1b5de8534e62123d0cb3d86d0c281`.
At recorded `2.7.2-cdk-G0` it produces 78/78 words with zero substitutions and
two indels: the same instruction multiset with one `move` relocated.  A checked
prototype for the following `func_80047784` call leaves the same two-indel
result.  Probing stopped at that bounded allocator-order residue.

`dungeon/func_8009DB44` was not selected because its 128-byte chunk loop ends
with three reads through a `volatile s32 *`.  An ordinary 140-byte aggregate
would erase or broaden volatile access semantics, so it requires a separate
human source decision.
