# Consolidating shared types

Use one shared definition when evidence identifies the same object across
functions or binaries. Partial views are useful while layout remains unknown;
they should not become competing declarations once the common type is known.
Shared game types live under `include/shared/`; unresolved generated layouts
remain under `include/records/`. See the [struct census](STRUCT_CENSUS.md).

## Evidence before replacement

Establish the storage base and extent, field offsets, widths, alignment,
signedness, pointer roles and all known users. Retail address formation is
useful evidence: one aggregate base and several independent symbols can compile
differently even when their addresses coincide. A frequent view is not by
itself proof of the original type.

Examples of shared definitions include `GameWork` in
`include/shared/game_work.h` and the object types documented by the current
headers. Read their comments for supported offsets and unresolved fields.
Use snake_case for new global/function names and PascalCase for types; preserve
proven developer spellings. Do not copy old camelCase examples as a new naming
rule. See [SYMBOLS.md](SYMBOLS.md).

Resolve overlapping views to a field type when evidence permits. Keep an honest
union, padding or `unk_XX` when it does not. Distinguish the object's real extent
from linker padding and from a larger address range through which a caller
forms a temporary view.

## Verification scope

Type changes can affect loads, stores, aggregate copies, alias assumptions,
register allocation and address formation. Verify every affected row, including
unchanged users of an edited header, then run the corresponding retail windows
or executable image. A shared TU must retain all its siblings; a shared home
can have multiple placements. Renew certificates binding changed declarations.

Do not force a cast-free spelling when it changes the required bytes. Explain
the remaining view and the measured difference. Do not infer a larger object or
a false prototype solely to make a compiler emit a desired instruction.

## Historical experiments

The [pilot design](evidence/type_consolidation_pilot_design.md) and
[pilot report](evidence/type_consolidation_pilot_report.md) preserve the original
method and measured outcomes. Later rulings appear in the
[decision record](evidence/r97_decisions.md). These documents include older
names, round identifiers and counts; use the current headers, alias table and
generated status for today's state.

Contributors can propose a bounded type improvement without replaying the old
automation campaigns. Include the evidence, dependent users, verified scope,
remaining conflicts and before/after hashes with the change.
