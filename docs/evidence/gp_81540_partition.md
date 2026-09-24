# Discovery-rank pointer ownership

`sort_rank_81540` is a present C owner for the rank-table pointer used while
sorting entries within a category. It groups `func_8004AE98` from the `code`
collector with the whole `slus/w_8004B08C` row, in retail order. This is not a
recovered historical translation unit. The owner uses default 2.7.2-cdk, the
whole member's existing recipe; the comparator previously used plain 2.7.2.
Both original row identities and the canonical collector source are preserved.

## Storage and declarations

The global is one four-byte `u8 *D_80081540 = 0`, replacing only the zeroed
slot at offset `0xB00` of `assets/54240.bin`, retail file offset `0x54D40`.
The 0x80-byte array in 4B08C is local storage, not the global object's extent.
4B08C stores its address in the global; the comparator loads that pointer and
subtracts two indexed bytes. The existing lifetime behavior is preserved.
Adjacent bytes and labels do not imply ownership beyond the four-byte pointer.
The bounded source audit found named uses only in these two functions; it does
not rule out indirect aliases.

`include/slus/sort_rank_81540.h` shares the pointer declaration and comparator
prototype. Its `u8 **` parameters match the canonical comparator's
`unsigned char **`, replacing the whole member's conflicting `void *`
prototype. The duplicate common include is removed. Function bodies are
unchanged, including the comparator's original local names and comment.
The surrounding helper functions and two-byte entry view remain outside this
ownership claim. No new pins, padded objects, compiler flags or assembler
rules are introduced. This review establishes data ownership only; it does
not grant module placement or L4/L5 status.

## Verification

The [direct comparison](gp_81540_partition/direct_receipt.json) covers 11 comparator
words and 70 sorting-routine words. All 81 words match stock, genuine ASPSX 2.79,
and the private guarded generic assembler, with zero retail differences and
zero masks. The private generic trial is not a global assembler transition gate.

The [private full-link receipt](gp_81540_partition/private_link_receipt.json)
proves actual four-byte `.sdata`, non-absolute linkage at 80081540, and the
retail-exact full image. All 870 surrounding objects are byte-identical. The
872 physical inputs project to the unchanged 884 logical rows. Across both
collectors and the E0, B98 and new owners, all 184 functions occur exactly once.
The [complete-owner proof](gp_81540_partition/private_genuine_receipt.json)
checks all three owners and preserves the collectors' remaining discrepancies.

Four [negative gate checks](gp_81540_partition/gate_receipt.json) change the new
81540 part, the B98 part, the E0 part and a collector remainder. Every changed
image is rejected; all canonical inputs and retail images are restored.
The [production ownership receipt](gp_81540_partition/ownership_receipt.json)
refreshes all three connected owners. The full image matches retail SHA-1
`e6bfbb95ff6676899e077481221d73ddd4d3bf52`.

The [live row evidence](gp_81540_partition/live_rows.json) clears only 4B08C's
dependency entry; four GP symbols remain in code and three in code2. E0 and
runtime-directory placement certificates are refreshed. No collector or new
whole member receives placement from this data proof. See the
[activation review](gp_81540_partition/activation_review.json) for hashes,
checks, counts and ladder results. Private reproducible inputs and the source
audit are in `work/native_lane/gp_81540_partition/`: `direct_probe.py`,
`build_probe.py`, `prove.py` and `gate_probe.py`.
