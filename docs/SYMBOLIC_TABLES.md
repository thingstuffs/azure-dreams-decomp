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
bounds or its C record type. Unsupported descriptor layouts, compiler switch tables, BSS,
cross-region callback tables, new raw rows and copying symbolic modules into other banks are outside this
model. Reconstruct and prove those owners before extending the schema.

Mixed descriptor records use `typed_records` slots in the same allocation
model. The owning folder header declares the C struct and real callback/data
pointer typedefs. The manifest describes each field's offset/type, every
symbolic initializer and scalar, complete stride/count and independently
reviewed bounds/consumers. Initialized pointers must emit exact zero-addend
32-bit relocations; scalar fields must emit their declared bytes. No pointer
literal, cast or arithmetic initializer is accepted. A descriptor must have
a symbolic callback field; scalar-only blobs are excluded. Function targets start
registered code rows in the actual load map; data imports retain their proven
resident-asset bounds. Complete native TU proof remains mandatory.

The four square-scene arrays contain 31 complete choices (496 bytes), including
terminal fallback records. Their parents reference array bases at +0x10;
consumers index 16-byte records, read the flag at +12, call the predicate at +0
and select text through +4. The SLUS loader descriptor at +0x54AF8 establishes
the full 0x9800-byte loaded image; its former 0x8000 view truncated referenced
data. The next independently referenced object bounds each array's end.

An existing native entry/switch prefix can also be separated from a combined
first code row. `prefix_provenance` records that original member, and the
original code identity survives at its complete body start. Separate logical
data rows exactly partition the existing `owned_data` records; pointer and
switch rows inherit their real native member owners, and minimal switch
alignment belongs to the following switch. These logical data names need not
invent exported C labels for compiler switch tables. The unchanged whole TU,
original membership evidence, original assembly ownership, all relocations and
both assembler outputs still prove the complete prefix and all functions.
No new historical baseline or level records are manufactured. This changes
accounting, not owned byte coverage; a subsequent full-body placement can add
coverage elsewhere. Block's 124-byte prefix is the first such separation.
