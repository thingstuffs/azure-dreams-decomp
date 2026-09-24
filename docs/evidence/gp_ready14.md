# Combined 14-row private rehearsal

The initial checkpoint below is retained. The current rebased and extended
proof is the [18-function rehearsal](gp_ready18.md); production counts in the
initial report are historical.

All 14 prepared rows now coexist in one full retail-exact private image, with
**735 words** independently matching genuine ASPSX 2.79 and zero masked
references. This is a partial repair rehearsal, not production integration or a
global assembler-transition gate. The [receipt](gp_ready14/receipt.json) records
source provenance/hashes, exact recipe differences, fresh-object comparisons,
owned-data placement, and the remaining live GP cohort.

The run combines the earlier [11-row proof](gp_ready_ownership.md), the
all-passes-enabled [49F68 local-data guard](selfinc_local_guard.md), and the
[AF3 pair declaration repair](gp_af3_declarations.md). It preserves all 19 active
production modules and adds six private ownership units: 25 private modules,
870 physical inputs and the same 884 logical rows. The only seven recipe changes
are the already-proved CDK moves for 3D92C, 3FAD4, 41588, 41AB0, 43CD0, 4450C and
4AB7C. No flags or pins are added.

Exactly 11 physical inputs use the private guarded generic assembler; the
remaining inputs use stock assembly. This isolated selection is a diagnostic
mechanism, not an acceptable production whitelist. The guarded package is
`28e45bbcf00fc90dc0645250f233b73f96ad11d06a2f8230ce533fc2fafbbfbe`, with all
passes enabled. Fresh generic objects match the actual linked input objects,
genuine objects, and retail independently. Nine owned symbols have exact object
section bytes/offsets, asset slices, linked non-absolute VMAs, and filtered
absolute assignments. The complete image matches retail SHA-256
`ae19d8d4bdd2db9a933b1e44d70dd61be670781e441d7cb37da85250a7aed31f`.
All 11 selected physical objects also equal their earlier proved object bytes.
All 898 compared pre-existing outside object files are unchanged; that includes
inactive cached files and is not an active-TU count.

Nine of the live 29 GP-dependent rows are prepared here: 3D92C, 4437C, 4450C,
47D44, 47DF0, 47E30, 47E78, 49F68 and 53CFC. The five other prepared rows address
separate toolchain residue. The remaining **20 unprepared GP rows** are precisely
the historical component described in [its inventory](gp_component20.md).
That graph's collector-file bridges require function-level analysis before
choosing module boundaries. Production still has 197 dependency records and
29 GP rows; none are removed by this experiment.

Reproduce with `python3 work/native_lane/gp_ready14_combined/probe.py`.
[The script hash](gp_ready14/reproducer.json) identifies this measured run.
The next global correction gate must apply the correction to **all** inputs,
include the remaining coordinated source/ownership repairs, and refresh the
whole dependency census. This selective proof alone does not authorize a default
switch or pass deletion.

## Rebase after production function partitions

The [fresh 14-row receipt](gp_ready14_rebased/receipt.json) preserves all 22
production owners and the active function-partition plan. It has 28 private
owners, 869 physical inputs and 884 logical rows, with exactly the same seven
recipe changes and 735 genuine-matched words. All 52 owned data declarations
have exact object/asset/link evidence. This run compares 858 active unchanged
outputs by object key, excluding inactive cached files from the denominator.
All are byte-identical. The [primary coverage check](gp_ready14_rebased/coverage_review.json)
requires exactly 14 functions across all 11 fresh, genuine and linked streams.

This prepares nine of the current 25 GP rows. The subsequent 18-function combined
rehearsal adds the 81550 source/data repair and is the current integration fixture.
Neither private run changes production dependencies or authorizes a global switch.
