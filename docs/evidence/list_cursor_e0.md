# E0 list cursor ownership and placement

`list_cursor_e0` is an inferred present C ownership unit for three adjacent list
operations. Shared state, direct accesses and retail order support this grouping;
it is not a recovered filename or proof of a historical translation-unit boundary.

| Function | Operation | Original logical row | Effective owner recipe |
|---|---|---|---|
| `func_800410FC` | Set the cursor to the list base and clear its first word | `slus/code2` | 2.8.1, unchanged |
| `func_80041110` | Write a value, advance the cursor and write a zero terminator | `slus/code` | 2.8.1; original collector recipe remains 2.7.2 |
| `func_80041134` | Remove the first equal word, shift the following entries and back up the cursor | `slus/w_80041134` | 2.8.1, unchanged |

The explicit partition plan retains both complete canonical collector files and
their registered IDs. Generated function views supply only 410FC and 41110 to the
owner. The collector remainders contain 23 and 155 functions respectively and
retain their original recipes. The unchanged one-function membership of 41134
is distinct from these two incoming parts. Every original function is emitted
exactly once; the registry still contains 884 logical SLUS rows.

## Interface and data

`include/slus/list_cursor_e0.h` declares the three existing signatures, the cursor
and an incomplete external word-array view. The aggregator and 41134 include this
header. Collector remainders retain their separate declarations; the generated
parts receive the owner's header. No shared header is forced onto unrelated
collector functions or other external users.

The only owned object is `s32 *D_800814E0 = 0`, exactly four bytes of `.sdata` at
`0x800814E0`. It replaces the four retail zero bytes at offset `0xAA0` in
`assets/54240.bin`. Normal generation carves that storage from the raw asset and
removes its former absolute-symbol assignment. No adjacent data is claimed.

`D_80083C68` remains external. These functions use a word-list view; 411AC also
uses a function-pointer view of that address. Neither the complete extent nor a
universal type for the storage is established. The new incomplete array declaration
removes this owner's old eight-word extent assumption. Pointer loads/stores and
four-byte cursor increments support the declared cursor interface. The existing
function bodies and symbols are preserved, with no new pins, padding, volatile
accesses or assembler exceptions.

## Proof and limits

The private certificate probe in
`work/native_lane/slus_partition_certificate/probe.py` builds the proposed header,
source, partition and data definition through normal Ninja. All 44 owner words
match genuine ASPSX 2.79 and retail with zero masks, and the complete 524288-byte
image matches retail. The proof validates the actual four-byte object storage,
its non-absolute linked symbol and exact address. Missing incoming functions,
partial full-object comparisons, masked relocations and whole-collector placement
claims are rejected.

The authoritative ownership receipt is
[the E0 ownership proof](slus_partitions/e0_ownership.json). It establishes data
ownership and a direct genuine comparison of the entire physical owner. The
separate placement certificate in `ledger/modules/list_cursor_e0.json` binds this
review, shared inputs, recipe, tool fingerprints and whole-image proof. It can
supply placement only for the declared whole member `slus/w_80041134`; it cannot
grant either collector row from the successful moved subset. Existing L4/L5 pin,
tail-jump and toolchain-residue requirements still apply.

The [fresh collector measurements](slus_partitions/e0_live_rows.json) retain all
unrelated GP dependencies. Their remaining genuine discrepancies must be repaired
separately. The generic assembler correction and compatibility-pass retirement
are also separate, unfinished work. This module does not change production
assembler semantics or remove any pass.
