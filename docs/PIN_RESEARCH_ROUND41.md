# Round 41: reconstruct whole operations and actual return values

The starting census is **6,098 pins in 1,282 rows**, commit `9e573bb0`.
This round follows the strongest round-40 evidence: aggregate copying produced
the retail operations, while changing source shape and compiler family together
recovered the copy-register partition. It also investigates the two remaining
pins around the independent 84-byte record's entry-store join.

## A complete object initializer, rather than individual copy pins

`town/func_8080E838` has 19 pins in 87 retail words. Reconstructing both its
88-byte payload and 24-byte initial record as aggregate assignments, using typed
object/render fields and a symbolic scalar resource table, removes every pin.
The first ordinary form at stock 2.7.2-G0 differs only by one moved instruction:
the object-result copy appears before the table address. Keeping the allocation
result in an ordinary temporary until table setup reproduces the retail order.
RTL shows that GCC eliminates the temporary, then places the table setup before
the single object-result copy. No asm, volatile access, fake arithmetic, extra
runtime operation, or artificial live argument is needed.

The final source independently matches all 87 unmasked linked words. Semantic
review confirms both copy extents against the caller's 128-byte spawn buffer,
the three-entry scalar resource table, field offsets and typed callback. It
also catches a tempting wrong pointer-table declaration before landing. The
canonical handler declaration now agrees with its State/Motion/Actor definition.
The allocation-result temporary and the aggregate operations account for the
compiler decisions that the previous source expressed with 19 separate pins.

The source and compiler recipe are reviewed together. The old source is exact
at its recorded 2.95.2 recipe; the new source is exact at stock 2.7.2-G0.
Neither cross-combination matches. This does not establish the unique historical
release. The [recipe review](evidence/pin_research_recipe_transition_20260917.md)
records a whole-reconstruction transition while preserving the stricter existing
automatic pin-erasure cell-switch rule. Publication still requires live-row and
full-window verification. See the [semantic review](evidence/pin_research_copy88_review_20260917.md).

The automated lineage scanner's pointer-based call-slot store is not a useful
CDK-only signature here: stock 2.7.2 directly reproduces that instruction. The
scanner conflict was manually checked against the actual operation rather than
used as a reason to stop investigating. Likewise, use full verifier summaries
for cross-cell length: the old diff-only control truncated a longer build.
The fresh summary gives 92/87 words and total 25 for the old pinned source at
2.7.2-G0; the earlier truncated diff's 87/87 and total 30 are not full-size
endpoint measurements. Both remain nonmatching controls.

## Independent initializer transfer: six more pins

`town/func_8081DD70` is an 88-word initializer with the same two copy extents.
The independent reconstruction removes all six pins at stock 2.7.2-cdk-G0.
Its table address is prepared before allocation; its retail split-address
sequence differs from the first initializer. The callback contract is also
independently checked: this handler takes three `void *` parameters, unlike
the first handler's named structure types. Copying those types blindly would
have introduced an unproved cross-TU promise.

Same-image callers supply separate 88-byte and 24-byte records and bound the
resource index to 0..2. The resource table contains scalar words. Review rejects
an alternative with pointer-to-s32 casts and a private allocator return type;
the selected source retains the established pointer helper contracts. Existing
guest-pointer layout and global helper prototype debt remain explicit. Both
initializers have zero pins and no hidden asm. See the
[independent review](evidence/pin_research_copy88_twin_review_20260917.md).

These two independently reviewed positives support the aggregate-initializer
family mechanism. They do not justify assigning one compiler cell or callback
type to every similar row.

## A real return explains the remaining entry-store pins

After round 40's Record84 repair, `town/func_800A23CC` still had a forced return
register and a keep around a redundant entry-value join. A trusted allocator
trace shows why erasure fails: the artificial join value conflicts with v0,
lands in a0, and adds two predecessor copies. Retail instead leaves the entry
pointer in v0 through the slot store and return.

Its caller consumes and returns that entry value; the void definition was wrong.
Returning the actual entry, storing it directly, and removing the synthetic join
removes both pins. The selected contract is pointer-or-null, including
`set_item_w0` and its direct caller `mam_bita_give`; there is no new pointer-to-s32
narrowing. All three rows independently match: 113, 30 and 11 words. The generic
VM's reconstructed function-pointer types remain existing debt; target return
word transport does not prove ISO-C compatibility of that whole dispatcher.
Read the [return review](evidence/pin_research_entry_return_20260917.md).

## Bounded negative: the local 24-byte Pair

`town/func_800AB37C` received six reasoned probes. The actual helper
`func_800374F4` takes one argument, so the old extra copy-temporary arguments are
reconstruction artifacts. Ordinary aggregate C reproduces the entire suffix;
the unresolved prefix gives different page/source address pseudos. The best
staged two-Vec3 form scores 8. Its next question concerns symbolic object
identity and split-address lifetime, not more aggregate spelling. Receipts:
[bounded report](evidence/pin_research_pair24_20260917.md) and its retained RTL prefix maps.

## What changes in the next phase

Prioritize real operations spanning several pins: complete object initialization,
record assignment, return contracts, and address ownership. For each, explain
retail register roles in ordinary language, predict the relevant RTL lifetime
or lowering, then test a small discriminating source reconstruction. Review
source and stock compiler recipe together when a whole reconstruction warrants
it; retain the stricter automatic cell-switch rule for ordinary erasures.

The next family pass should find initializer siblings through real copy extents
and helper/callback relationships, then independently establish their layouts
and recipes. The two positives justify a bounded cohort, not an unrestricted
compiler or declaration-order sweep. For the Pair24 negative, recover the real
global object's identity and explain why retail keeps page and derived source
addresses separate. The larger dungeon rebuild still needs its competing global
allocation lifetimes explained, and the SLUS address case still needs the real
frame-sync object's source provenance. None is classified as impossible.

## Gated outcome

**27 pins removed; 6,071 remain in 1,279 rows.** Three functions become pin-free,
and two caller rows receive exact return-contract corrections. All five changed
rows are independently exact. All four affected overlay windows MATCH: town_scene
335,872 bytes, town_deep_t8b_022590 120 bytes, town_deep_t8b_78e59c 10,512 bytes,
and town_deep_t8b_79cdc8 11,364 bytes. SLUS SHA-1 MATCH; row database OK.
The [durable receipt](evidence/pin_research_round41_20260917.json) records source
hashes, old/new recipes, exact endpoint checks and publication gates. The total
since restarting zero-pin research is 32 removals from 6,103. Zero remains the
objective; this is a gated research checkpoint, not a minimum claim.
