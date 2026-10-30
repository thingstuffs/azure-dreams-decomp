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

## Family consolidation tools

Generated layouts (`S_<addr>...`, counted by `tools/lint/debt_check.py` as `generated_layouts`) are
consolidated one family at a time: the views a census identifies as one real object are respelled through
the shared type, their typedefs are deleted, and the casts the new types make redundant are folded.

1. **Census.** `tools/typing/field_census.py` (flow identity of every access site),
   `tools/typing/field_cast_census.py` (casts applied to untyped members of shared structs) and
   `tools/typing/layout_census.py` (`inventory`, `assign`, `report`) produce `layouts_census.tsv`: one row
   per family (`type:`, `field:`, `derived:`, `new:`, `singletons:`), with views, generated sites, casts,
   the swap planner's readiness and identity evidence, ranked by removed debt per file touched.
2. **Plan.** `tools/typing/layout_swap.py plan --family F.json` checks every use of every listed view
   against the shared type (same offset, same access, sizes where a stride is used) and records identity
   evidence: `anchored` (a typed value flows into the view), `conflict`/`mixed` (another record does), or
   `shape` (layout fit only).  `"require_anchor": true` accepts anchored views only.
3. **Apply.** `layout_swap.py apply` retypes listed struct members first (`"retype_fields"`), then swaps the
   accepted views, folds redundant casts and retypes single-type locals.  It snapshots every touched file,
   measures Clang pointer-conversion warnings per physical TU before and after (any rise restores the
   whole batch) and restores any C file whose per-function debt rises.  `"hold"` prefixes are never
   edited (other lanes' areas).
4. **Prove.** `layout_swap.py prove` refreshes `ledger/layout_inline.jsonl`, runs
   `tools/build/affected.py prove` over every edited file (rows, modules and placement copies), reverts
   the files whose own recipes are not PASS, and repeats.  Commit, then `make -j8`.

Batch many views into one family file before proving; tidy refusals afterwards.  A view used for two
objects (a reused variable) is refused rather than renamed.  Raw-offset folds (`--raw-fold`) can change
gcc 2.x alias decisions and are left to `cast_wave.py`, which proves them site by site.

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
