# Reading the struct census

The census groups compatible memory views to help find shared types. It is
evidence for layout work, not a vote that proves the most common type is right.
Use it with [type consolidation](TYPE_CONSOLIDATION.md) and the actual accesses.

`tools/struct_census.py` records local struct views and their provenance in
`ledger/struct_census.json` and `ledger/struct_census_structs.json`. Provenance
may be a known global, a parameter traced through callers, or a local expression
whose wider identity remains unknown. `ledger/records.json` records generated
shared-record mappings; declarations live under `include/records/`.

## Interpreting agreement and conflict

* Matching offsets and widths support a shared layout when provenance also
  connects the views. Similar layouts alone do not prove one object.
* Width or pointer/integer conflicts need examination of overlap, unions and
  actual storage. Signedness/qualifier differences can still affect codegen.
* Unknown-width types, address-taken members, function pointers and `sizeof`
  require particular care. Preserve an explicit unknown when the evidence
  cannot determine the declaration.

Generated `Rec_*` names and `unk_XX` members describe unresolved layouts. They
can be replaced with shared semantic types once all relevant users support the
change. Existing domain types in `include/shared/` take priority over creating
another duplicate view. A source path must be resolved from its row ID; census
IDs and old address-named type names do not imply current filenames.

## Reviewing a proposed type

Establish object identity, extent, field offsets, access widths, alignment and
pointer roles. Check conflicts across all users, including separate overlays
that access the same resident storage. Verify every affected row and its retail
window/image; renew certificates whose source/header inputs changed.

The [initial consolidation design](evidence/type_consolidation_pilot_design.md)
and [measured report](evidence/type_consolidation_pilot_report.md) preserve the
early experiments. Their counts describe those snapshots. Current generated
status and the present headers describe the current tree; old transform scripts
and removed journal history are not prerequisites for proposing a type.
