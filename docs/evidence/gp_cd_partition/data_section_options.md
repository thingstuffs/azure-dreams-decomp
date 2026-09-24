# Current SLUS data placement options

## What the current module carver can place

`config/slus_modules.json` records each owned symbol's asset, byte offset, size, VMA, exact initializer bytes, and input section. The loader accepts only `.sdata` and `.sbss`; `.sbss` entries must be all zero (`tools/build/slus_modules.py:128-154`). `data_sections()` groups records by section, then requires each section's records to use one asset and form one ordered, gap-free range in both asset offsets and VMAs (`:220-236`). Consequently, one module can currently describe at most one contiguous `.sdata` range and one contiguous `.sbss` range. Custom names such as `.sdata.foo` are rejected.

For each accepted range, `plan_asset_carves()` emits one `module_data` slot naming the module object and the exact section. Bytes before, between, and after ownership spans remain raw asset chunks, copied from the asset and converted to binary objects (`:254-299`, `:302-320`). `rewrite_ordered_linker_script()` replaces the asset's `.data` selector with those chunk and module-section selectors in asset-offset order (`:323-355`). Thus gaps are retained from the original asset; no C padding object is needed. The linker input selector is the whole input section, for example `module.o(.sdata)`, not a named symbol range.

The carver handles a misaligned new boundary by relaxing `SUBALIGN` to 1 only on the containing output section when required; it leaves other output sections and word-aligned cases alone (`slus_modules.py:336-354`). This prevents linker-added padding from shifting later chunks. It does not create another ownership extent within the same module `.sdata` section.

## Same-section islands are not represented today

Several nonadjacent symbols assigned to the same module `.sdata` section cannot currently be placed at separate asset offsets with raw chunks between them. The manifest groups all `.sdata` records into one span and rejects a same-section gap. Repeating `module.o(.sdata)` would still select the same whole input section; there is no manifest field for distinct subsection names or section fragments. The same rule applies separately to `.sbss`. A module may own different `.sdata` and `.sbss` spans, but `.sbss` is specifically zero-filled NOBITS storage, not a general second `.sdata` island.

`tools/build/slus_partitions.py` does not extend data placement: its plan maps original functions to destination module names, and its renderer moves function bodies while checking emitted function coverage (`slus_partitions.py:46-87, 192-218`). Data records and linker section slots remain the responsibility of `slus_modules.py`.

## Existing examples and test evidence

- `gp_split_storage` is the current example of one module object with two separated section spans: the manifest puts contiguous `D_80080B10/12/14` at asset offsets 208–213 in `.sdata`, and `D_80081530` at offset 2800 in `.sbss` (`config/slus_modules.json:784-822`). The source view `src/slus/gp_split_storage.c` includes `w_80048660.c`; that body defines the three initialized `u16` values and an uninitialized static `u16 D_80081530` (`src/slus/w_80048660.c:14-17`). This demonstrates separated `.sdata`/`.sbss` ownership, not multiple `.sdata` islands.
- `gp_shared_slots` defines six adjacent variables in one C aggregator (`src/slus/gp_shared_slots.c:1-8`); its current manifest entries are a single contiguous `.sdata` run. `command_slots_81554` similarly defines adjacent `D_80081554` and `D_80081558` in its owner source (`src/slus/w_8004DCA8_owned.c:1-10`). These examples do not show one module placing two disjoint `.sdata` ranges.
- `tools/tests/test_slus_modules.py:test_multiple_contiguous_data_in_one_module_only` accepts adjacent same-module `.sdata` records and rejects a gap (`:188-199`).
- `tools/tests/test_slus_split_storage.py:test_sections_carve_separate_spans_and_filter_both_symbols` confirms one object can be selected once as `.sdata` and once as `.sbss` at separate asset offsets (`:47-65`). `test_same_section_gap_and_cross_section_overlap_rejected` explicitly rejects a same-section gap and overlapping section ranges (`:80-93`); `test_unsupported_storage_section_rejected` rejects `.bss` (`:109-113`). Its optional MIPS-binutils integration assembles `.sdata` PROGBITS plus `.sbss` NOBITS, links them between raw chunks, and asserts the output binary equals the original asset (`:115-145`). It was inspected, not run for this inventory.
- `tools/tests/test_slus_module_alignment.py` covers halfword carves under `SUBALIGN(4)` and, in its optional link test, verifies the repaired output bytes equal the original asset while the unrepaired script inserts two bytes (`:55-63, 69-112`). It also checks the owner section contributes only the two real bytes, with no filler symbol or padding definition (`:78-90`).

## Constraint for the proposed symbol groups

The named `D_80080AD0/AD2/AD4/AD8/ADC` and `D_800814CC/D0/D4` sets may use the chunk-preserving mechanism only where the planner can identify separate real input-section spans. Under today's schema, one module cannot place separated spans from the same `.sdata` input section around untouched asset chunks. The existing supported example is one `.sdata` span plus one `.sbss` span, not an arbitrary number of subsections. No current test or manifest example demonstrates multiple `.sdata.*` subsections or repeated `.sdata` placement for one object.

The practical next decision is therefore an ownership/section-model question: keep the represented data ranges truthful and the intervening bytes in raw chunks; do not bridge gaps by inventing C storage. The current function-partition machinery alone does not supply the missing same-section placement capability.
