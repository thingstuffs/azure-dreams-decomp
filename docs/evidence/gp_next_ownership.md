# Next GP ownership repairs: private proofs

These experiments follow the production count/slot landing at `cbe72882`.
Production still has 35 GP-dependent rows and 202 total dependency records.
The candidates below are private; their passing measurements do not remove
production dependencies or approve a global assembler semantic change.

## Address-taking owners: 47E78 and 53CFC

Both ordinary C ownership aggregators, using the existing generic small-data
assembler correction for only their two physical inputs, produce a complete
retail-exact SLUS image. All 15 production modules remain present. Three zero
words occupy the exact retail addresses: `D_80081528`, `D_80081568` and
`D_8008156C`. The build keeps 875 physical inputs and 884 logical rows.

47E78 is genuine ASPSX 2.79 exact at 29 words. Stock GNU small-data address
optimization shortens its absolute address load; the generic correction's
downstream `-G0` preserves genuine ASPSX's two-word expansion.

53CFC initially failed the genuine condition despite an exact corrected image.
Its 12-byte asm alias caused GCC to emit `.extern D_80081568, 12` even though
the owner defined the real four-byte volatile word. Genuine ASPSX then expanded
three accesses absolutely, producing 29 words instead of retail's 26. Removing
only that assembler directive was an attribution experiment, not a source fix.
The [original receipt](gp_next_ownership/address_pair_original_receipt.json)
preserves both the failure and the diagnostic.

The [declaration repair](gp_next_ownership/w_80053CFC_declaration.diff) removes
the unused padded alias type and asm alias, changes the address local to
`void *`, and takes the actual scalar's address. All other operations, existing
pins, volatile access and the memory asm are retained. This removes the
conflicting directive at its C source. Genuine ASPSX now emits all 26 retail
words exactly, with zero masks; 47E78 remains exact at 29. The
[repaired receipt](gp_next_ownership/address_pair_repaired_receipt.json)
proves full image, function layout, real storage and genuine comparisons, with
production input hashes unchanged. Both genuine comparisons use unchanged
retail-exact production ELF anchors. This supersedes the earlier 53CFC diagnosis
based on a shifted candidate ELF.

Reproduce the original failing treatment with
`work/native_lane/gp_address_owned/probe.py` (expected nonzero exit), or the
repaired treatment with `work/native_lane/gp_address_owned/decl_repair/probe.py`.
The scripts preserve the active module set dynamically. The candidate C and
ownership aggregators are retained beside the durable receipts. Integration
still requires preparing the complete assembler correction and its affected
consumers, required full gates, and the existing final owner sign-off.

## Separated initialized and uninitialized storage: 48660

The current one-contiguous-`.sdata` manifest limitation is avoidable without
padding variables or section attributes. Three ordinary initialized halfwords
at `D_80080B10/12/14` occupy six `.sdata` bytes. A real uninitialized halfword
at `D_80081530` occupies two `.sbss` bytes. A private copy of the build helper
places these two actual input sections into separate raw-asset carves. The
complete image equals retail, and all 53 function words match genuine ASPSX
2.79 and retail with zero masks. The stock assembler is used throughout.

The first candidate's tentative global emits `.comm`; current maspsx lowers
that small common to a local `.sbss` label. This visibility discrepancy should
not be hidden. No other canonical SLUS source references `D_80081530`. An
explicit `static u16` definition instead emits `.lcomm` and expresses the
current sole ownership directly. That candidate also passes the whole image
and genuine gates; both candidates' resulting input objects are byte-identical.
The C-owned local resolves at `0x80081530`, and its two accesses relocate
against the real `.sbss` section. This does not claim original source visibility.

The [tentative-global receipt](gp_next_ownership/split_storage_global_receipt.json)
and [static receipt](gp_next_ownership/split_storage_static_receipt.json)
record section lengths, symbol binding/offsets/VMAs, full image and unchanged
logical edges. `.sbss` has no object-file payload; its two bytes of zero storage
are checked in the final retail image. The
[static candidate](gp_next_ownership/w_80048660_static_candidate.c) is preferred
for integration. No production source or helper has been changed by this probe.

Next, extend manifest validation and carve planning to distinct real data
sections, require each section's records to remain contiguous and ordered,
and require `.sbss` spans to be zero. Extend ownership proof to check section
identity as well as bytes, extent and symbol offsets. Add a real linker test
for separated `.sdata`/`.sbss` carves and rejection checks for overlap,
nonzero uninitialized spans and missing/wrong object sections. Then activate
this source through the normal complete-image/genuine gates and recertify the
existing runtime pilot against the changed verification inputs.

Both private image proofs above produce SHA-1
`e6bfbb95ff6676899e077481221d73ddd4d3bf52` (524,288 bytes). They establish
the specific tested candidates; neither supplies new L4 placement evidence.
