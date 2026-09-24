# Additional privately verified ownership groups

Measured after the split-storage landing `f69cd042`: production has 16 ownership
units, 201 dependency records and 34 remaining GP rows. None of the groups below
is integrated by this report. All three private images are exactly the 524,288
retail bytes, SHA-1 `e6bfbb95ff6676899e077481221d73ddd4d3bf52`.

| Group | Genuine ASPSX 2.79 proof | Pipeline and remaining integration |
|---|---|---|
| 47D44 / 47DF0 / 47E30 | All three functions, 63 words combined, zero masks | Existing 2.7.2 recipe; generic correction only for the new owner object. Production global correction remains pending. |
| 3D92C | 136 words, zero masks | Prepared pin-free C, trial CDK recipe and generic correction only for the new object. Production source/recipe/assembler transition remains pending. |
| 45340 / 453E0 | 40 + 533 words, zero masks | Stock assembler. Byte-neutral standalone CDK recipe trial for 45340 passes; recipe landing and ownership integration remain. |

## Shared pointer at 8152C

The [three-function owner](gp_ready_ownership/gp_shared_8152c.c) defines one
ordinary `void *D_8008152C = 0` after the unchanged source fragments. Its four
initialized bytes and non-absolute linked address match retail. The outside
consumer `code7.o` stays byte-identical and keeps external HI16/LO16 references.
The existing 16 modules are preserved.

Stock assembly shortens 47D44's address load. The group is then 62 words versus
genuine ASPSX's 63, and the full image fails. The private generic correction
restores the 63-word group and exact linked layout. The
[receipt](gp_ready_ownership/gp_shared_8152c_receipt.json) retains stock standalone
comparison failures as controls; its `generic_vs_genuine` and
`generic_vs_linked` fields describe the successful corrected object. The genuine
retail comparison checks all three functions with zero masks. Reproduce with
`work/native_lane/gp_shared_8152c/probe.py`.

## Prepared pin-free 3D92C with actual storage

The retained candidate is
`work/fidelity/step4/cands/slus/w_8003D92C.gp.hand_d92c_cdk.c.c`.
Its [owner](gp_ready_ownership/gp_d92c_owned.c) provides actual `short` definitions
for `D_80080ABC` and `D_80080ABE`, both zero, at `.sdata` offsets 0 and 2.
The successful link places them at their retail VMAs. No pinned GP whitelist is
used. The [receipt](gp_ready_ownership/gp_d92c_owned_receipt.json) explicitly
records the sole logical recipe change, from registered 2.7.2 to trial
2.7.2-cdk; row identities remain stable. The stock control is 127 words and fails,
while the generic-corrected and genuine objects match at 136 words. Reproduce
with `work/native_lane/gp_d92c_owned/probe.py`.

## Shared state at 81510

The adjacent 45340 and 453E0 functions share one `s32 D_80081510 = 0` in a
stock-assembled owner. The shared header declares the callee's actual signature
and forward `Entry` type. The caller casts its integer context and node pointer
to that signature at the call. Its node view and the callee's distinct entry
layout are retained, not asserted to be one interchangeable struct. The callee
drops only the duplicate forward typedef; pins and other body operations remain.

The [receipt](gp_ready_ownership/gp_shared_81510_receipt.json) proves an unchanged
standalone 45340 source is byte-neutral at CDK. In the private grouped build,
only that row's recipe changes from 2.8.1 to CDK. Both functions, the four-byte
data section, linked addresses and the full image are exact. The private build
has 874 physical inputs and 884 logical rows. Source, shared header and aggregator
are retained with the receipt. Reproduce with
`work/native_lane/gp_shared_81510/probe.py`; integrate the recipe through
`tools/fidelity/land_recipe_move.py` before activating the grouped source.

These are present ownership reconstructions with explicit recipe and assembler
treatments. They do not prove historical translation-unit boundaries or L4
placement. The prepared source files alone are insufficient: retain the linked,
genuine and symbol-placement gates when integrating them.

## Combined generic-correction rehearsal

The [combined receipt](gp_ready_ownership/combined_receipt.json) puts the two
address-taking owners, the three 8152C consumers, owned 3D92C and the five earlier
natural CDK candidates into one private executable. All **11 logical rows**
match genuine ASPSX and retail across **532 words**, with zero masks. Standalone
corrected objects equal their actual linked build inputs. Exactly nine physical
C inputs use the generic correction; the remaining inputs keep stock assembly.
The complete image remains retail-exact, with all 16 production ownership units
preserved and all six new data symbols at their exact offsets and VMAs.

Only 3D92C and the five earlier prepared rows change recipes (2.7.2 to CDK).
All 884 logical IDs remain. Stored preparation hashes were checked before using
the five earlier candidates; [source hashes](gp_ready_ownership/combined_source_hashes.json)
identify the staged inputs. Reproduce with
`work/native_lane/gp_ready_combined/probe.py`. The earlier private recipe-injection
attempt was overridden by existing configure mappings; the successful reproducer
applies its private trial recipe overrides after that mapping is constructed.

This is a combined **partial** repair proof: six of these rows belong to the
remaining GP cohort, while five address other toolchain residue. It does not
activate a global correction, repair the other GP rows, or remove production
dependency records. The stock-only 45340/453E0 group above is a separate next
landing and is not included in this rehearsal.
