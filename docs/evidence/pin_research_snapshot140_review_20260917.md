Working paths refer to `work/native_lane/r42_snapshot140/`.

# Snapshot140 read-only semantic review

## Scope and status

This review covers `dungeon/func_8008EE88` (runtime `func_800945E8`) and the
two 140-byte transfers in `base.c` / `aggregate_copy4.c`. It is a source and
data-flow review only: no compiler or verifier was run and no production file
was changed. The zero-pin aggregate reconstruction remains nonexact at total
distance 40 (180/181 words), so it is not a landing candidate.

## Facts established by the source

Both transfers have an exact extent of `0x8c` bytes: eight 16-byte groups and
a 12-byte tail, or 35 words. The first destination is
`D_800E3E48 + record_index * 0x8c`. The second loop walks all 20 slots backward
from `D_800E3E48 + 19 * 0x8c` and writes the corresponding 20 slots backward
from `0x80012260 + 19 * 0x8c`. `func_802833F4` clears `D_800E3E48` as one
`0xaf0`-byte region, which equals `20 * 0x8c`.

The 140-byte value is a record prefix, not a complete record. Before the first
copy, the code may read source byte `0xa8` and store it at byte `0x13`.
`0xa8` lies beyond the copied range `0..0x8b`. Accordingly, `Blob140` describes
the persisted prefix only. A rigorous typed reconstruction should eventually
represent that prefix as a real member of the larger record (or retain an
explicit byte-copy contract); a naked cast of an unrelated complete-record
type to `Blob140 *` is not by itself proof of the original C type.

`func_80042900(record, 0xA)` searches the record's four effect entries for
effect type 10. It returns the signed effect value, `0x100` for a matching
zero-valued effect, and zero when no such ordinary effect exists. Thus the
call's nonzero test controls the byte `0xa8` to byte `0x13` refresh before the
prefix is captured; it does not change the copy extent.

The strongest independent source witness is `func_8008E714.c`. It derives the
same low-five-bit record index, reads `D_800E3DF0[index]`, performs the same
effect-10 byte refresh, chooses `D_800E3E48 + index * 0x8c`, redirects that
same table slot to the chosen storage, and copies an ordinary `Copy140`
aggregate. `func_800B1364.c` and `func_8009DB44.c` also treat the buffer as 20
ordinary 0x8c-byte records; the former assigns `D_800E3DF0[index]` to the
same-index buffer slot before filling it, and the latter scans byte `0x13` in
those records. These uses identify normal mutable RAM snapshot storage, not
MMIO.

## Aliasing and overlap

The second 140-byte transfer is disjoint. Its complete source interval is the
snapshot buffer at `D_800E3E48 .. D_800E3E48 + 0xaf0`; its complete destination
interval is `0x80012260 .. 0x80012260 + 0xaf0`. These are separate RAM regions.

For the first transfer, recognized table writers support two intended cases:

- a table slot points to a live record outside `D_800E3E48`, so source and
  destination are disjoint; or
- a previously redirected slot `i` points to
  `D_800E3E48 + i * 0x8c`, so the operation is exact self-copy.

The target itself redirects slot `i` to slot `i`, and the sibling save paths
do the same. Exact aggregate self-assignment is compatible with C's overlap
rule because source and destination are the same object with the same type.
It may be optimized away, but it preserves the value. No recognized writer in
the narrow dungeon source audit constructs a pointer to a different or
partially overlapping buffer slot. This supports the disjoint-or-exact-self
invariant; it does not prove that arbitrary corruption, an unseen indirect
writer, or original-TU code outside the recovered views can never violate it.
Aggregate assignment must not be treated as `memmove` if such partial overlap
is later found.

## Volatile conclusion

The inherited `volatile u32 *copy_dst_cursor` qualifications are not supported
by the recovered object semantics. Both destinations are ordinary state RAM;
their declarations are nonvolatile, the buffer is cleared and inspected as a
normal array, and a sibling path already expresses the same 140-byte snapshot
as a nonvolatile aggregate assignment. Retail's straight `sw` sequence also
contains no synchronization or device-access signal. Removing `volatile` from
these copy stores therefore preserves the recovered single-threaded snapshot
contract, including the exact-self case.

This conclusion is limited to the qualification of the stores. It does not
establish that `aggregate_copy4.c` has recovered the correct enclosing types,
address lifetimes, or compiler ownership, and it does not make its distance-40
output promotable. The source audit also cannot independently exclude an
unrecovered asynchronous observer; no declaration, caller, or sibling path
found here provides evidence for one.

## Remaining evidence and next discrimination

The next semantic evidence should be a complete writer inventory for
`D_800E3DF0` tied to a recovered common table/record type. That would promote
the disjoint-or-exact-self rule from a supported invariant to an explicit
object contract and would supply a typed 140-byte prefix member without relying
on casts. The next code-generation discrimination remains the one in
`REPORT.md`: explain the second loop's retained `0x800e0000` page lifetime and
the surrounding global-record views. The diagnostic restoration of
`buffer_page` recovers the frame but worsens the score to 41, so another body
rewrite or artificial keep is not evidence for that owner.
