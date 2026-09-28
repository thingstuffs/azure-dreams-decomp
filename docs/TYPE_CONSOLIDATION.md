# Type consolidation (started 2026-09-28)

Owner rulings, 2026-09-28 (binding until revisited - "nothing is set in stone"):

1. **Consolidate.** The decompiler's per-function view structs (`S_800B0870_0 /* arg0 in func_800B0870 */`,
   `unk_XX` fields) and globals spelled as several `D_<addr>` symbols become shared, named game types.
2. **Naming.** Name a type or field when confidence is relatively high; a wrong name can be revisited. An unknown
   may stay `unk_XX` or get a descriptive name that makes the code easier to follow, never a name that asserts
   something it is not.
3. **Scope.** A type or global used by several binaries (SLUS, main, town and dungeon overlays) has one shared
   definition across all of them; the binaries are separate only for PS1 RAM/architecture reasons.
4. **Unions.** "Accessed as both" unions are resolved to the true field type where evidence allows.
5. **Pilot first**, then scale from measured cost and fallout.

Constraint: every touched row stays byte-exact through the normal gates. Types change codegen (signedness, alignment
and aggregate copies, alias/MEM_IN_STRUCT dependence, and shared `%hi` bases for fields of one object versus
separate symbols), so each row is verified individually; retail's own address-formation pattern is evidence of
how the original declared an object.

Baseline (2026-09-28): 276 local address-named typedefs in 223 files (259 distinct layouts), 102 shared
`include/records/Rec_*` headers, 3,140 rows referencing an address-named type; three opaque shared types in
include/game.h. Most-referenced globals: D_800814A0 (723 rows, all binaries), D_80083228 (578), D_80083460 block
(538 + 196 + 171 via separate symbols), D_80083160 (403, all binaries), direction step tables D_8006CCD8 /
D_8006CCE8 (231).

Pilot: `work/native_lane/r78_types_pilot/` (Opus) - the direction step tables (data-symbol naming mechanism) and
the 0x80083460 global block (struct consolidation). Results and the scaling recommendation go here when it lands.
