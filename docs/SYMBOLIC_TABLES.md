# Symbolic callback tables in complete translation units

Use `separated-symbolic-allocations-v1` for an existing native module whose
natural text stream and initialized function-pointer array occupy separate
retail spans. Define the array in the existing owning C translation unit and
put its callback typedef/declaration in that feature's existing header. A const
array can use `.rodata`; a writable array uses `.data`.

Each `function_pointers` slot records its symbol, type, declaration header,
source, exact size/offset, code owner row and ordered canonical target symbols.
Register one evidenced `function_table` data row per slot. Its `owner` is a
code member of the same module and its source path is that owner's complete
TU. The existing text cohort's membership evidence remains unchanged; the
new data's eligibility comes from explicit registry ownership and its complete
symbolic allocation proof, not fabricated historical level/baseline records.

The gate rejects literal address initializers, expressions, missing or extra
relocations, different targets/addends, unregistered targets, data targets,
wrong canonical bindings, equal addresses in a different load map, hidden storage and incomplete rows. Every word has
an exact 32-bit function relocation. The two assembler outputs are compared
as complete objects and resolved with no masks before retail comparison.
Only canonical zero GNU section-end padding may be removed. Certification
replays the source/relocation/storage checks from retained object artifacts.

The window module is the first use: 36 functions / 7,292 text bytes and
`town_object_callbacks[172]` / 688 data bytes at TOWN +0x561F0. Its whole-table
bounds follow the callback consumer and the independently referenced next
object at +0x564A0. A union of a callback pointer and a word preserves the
existing consumer's stored address without adding a cast.

An isolated pointer word in an unknown descriptor does not establish table
bounds or its C record type. Mixed descriptors, compiler switch tables, BSS,
cross-region callback tables, new raw rows and copying symbolic modules into other banks are outside this
model. Reconstruct and prove those owners before extending the schema.
