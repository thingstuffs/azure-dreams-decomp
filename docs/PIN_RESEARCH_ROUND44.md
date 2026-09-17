# Round 44: typed lookup and bounded mechanical transfers

**6,060 pins in 1,276 rows: one removed this wave, 43 since restarting.**
The independently reviewed lookup repair removes the last pin from
`dungeon/func_8008E714` through the normal hash-bound landing path. The full
393,216-byte DUNGEON engine window and SLUS MATCH; row database and research
ledger validate. [Durable proof](evidence/pin_research_round44_20260917.json).

## Ordinary indexing replaces address scaffolding

The existing pointer table and masked index already describe an array lookup.
Replacing the pinned shift/add/pointer-to-integer sequence with
`record_table[saved_index]` is exact at the recorded stock `2.7.2-cdk-G0`
recipe: 110/110 words. No recipe, API, memory qualification or aggregate-copy
change is needed. The now-unused integer address local is also removed.

Independent review checks the same-index registry access, unchanged callers,
full linked bytes and the absence of hidden or relocated pins. The erasure-only
control misses by five substitutions. Its integer staging emits the index shift
first and allocates the table base/result differently; the typed expression
naturally restores retail's base-first order and registers.
[Review](evidence/pin_research_registry_lookup_review_20260917.md).

## What can be mechanical

The productive unit is a proven source relationship followed by bounded
transfer. Existing copy generation, candidate verification and guarded landing
already automate the repetitive work. New source inventories narrow the next
tests before anyone spends time on compiler explanations.

The six-helper arity audit scans 893 currently pinned, registered DUNGEON
sources. It finds 35 over-arity calls; eight selected call sites in seven rows
pass pure locals also named by pins. Actual resident definitions establish the
consumed arguments. Removing extra arguments still requires checking their
evaluation effects, and exactness remains an independent test. The seven-row
pilot tests the corrected calls together with only those related pins, at the
recorded recipes, with baseline and argument-only controls.

All seven baselines match; none of the seven pin-removing candidates does.
Argument-only controls match in `800AC008` and `818B0C3C` but remove no pin.
The closest coupled result, `80C96F24`, has just two register substitutions:
the generated owner load uses a3 where retail uses a2. This is now a concrete
allocation question. These results do not support a broad argument-pruning
erasure sweep; actual helper contracts remain useful when reconstructing the
complete operation that created those false dependencies.

The typed-lookup inventory is deliberately narrower: existing typed tables,
matching element scale and ordinary local indexing. Literal pages, stack
address scaffolding and unknown record layouts do not establish this mechanism.
No general C parser or unconditional rewrite rule is justified by one positive.
The exact ordered search finds only the known reference, and ten inspected
near matches yield no additional eligible row. This bounds that lexical cohort,
not every semantic array lookup in the remaining sources.

## Bounded copy results

The remaining nine-row named copy cohort has no untested alignment-2 two-path
copy. That statement does not cover all DUNGEON sources. `80D137FC` reproduces
the 48-byte aggregate/helper repair exactly at 404 words while retaining its
unrelated action pin. Removing that pin rotates saved argument roles and misses
by 51. This confirms the copy transfer but removes no pin, so it was not landed.

In `8009DB44`, a 140-byte aggregate reproduces the entire copy loop and tail.
The zero-pin candidate misses outside the transfer because the outer slot scan
no longer hoists the mask and copy limit. A natural do/while scan restores those
invariants but also hoists two flag constants that retail keeps inside. Three
bounded probes remain nonexact. Recover the actual world-slot layout and scan
structure before another probe; the copy itself no longer needs a spelling
search. The diagnostic volatile-tail removal is not a production change.

None of these negatives establishes an unavoidable pin. The next phase should
return to complete operation and argument-role reconstruction in the higher-pin
144-byte and snapshot cases. Use the measured source contracts during those
rebuilds, then run bounded transfers and the existing erasure cascade on an exact
winner. The `80C96F24` owner-load register discrepancy is a smaller diagnostic
target. Expanding these particular mechanical patterns without a new source
fact is not supported by this wave's results.
