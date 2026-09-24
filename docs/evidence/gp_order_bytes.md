# 49F68: real order bytes, C register roles and an assembler pass

Status: **not integrated**. Route: **az-c-rebuild** for the four register-role
substitutions, plus the `_fold_selfinc_la` fidelity lead in
`tools/maspsx_leads.md`. This is a concrete near-miss handoff, not a compiler-wall
or NON_MATCHING verdict. The production row and its six existing pins are unchanged.

## Storage evidence

The old C declares a scalar `D_80080B30` and an overlapping 16-byte array
`D_80080B2C`. It tests the scalar, then traverses the array starting at offset 4.
Retail bytes at B2C are `bc bc 9c 00 01 03 02 04 3c 0b 08 80 c0 e4 02 80`.
`w_800499E8` copies only the first four bytes for a color. 49F68 starts at B30,
visits element indices 1, 3 and 2, and stops at the sentinel 4. No other canonical
SLUS C source references B30; these were narrow source searches, not a claim
about arbitrary pointer accesses at runtime.

The [candidate](gp_order_bytes/candidate.c) owns the actual four-byte order table
as `u8 D_80080B30[4] = {1, 3, 2, 4}`. Its initial test reads element zero and its
cursor starts at the table. It removes this function's oversized overlapping
color-array declaration. No padding data, additional pins, volatile qualifier or
new assembler statement is introduced. The neighboring color storage remains
outside this candidate. A full linked proof has **not** passed for this source.

## Retail site map and lineage

The entire function is [50 retail words](gp_order_bytes/retail.s), with no stack
frame or calls. The retained recipe is `2.7.2-cdk -fno-strength-reduce`.
The fingerprint CLI currently resolves overlays only, so the SLUS retail slice
was fed directly to its `scan` and `classify` functions. The
[scanner receipt](gp_order_bytes/lineage.json) has no conflicting family verdict:
the store classifier has insufficient evidence, while the two-register split
address is an explicit CDK/4.1-lineage signature. This is not a config-sweep
attribution. The available reference interpreter supplied the scanner's Capstone
dependency; the current checkout's interpreters lack it. The skill's referenced
RUNBOOK was not present in this checkout's root, docs or tools directories.

| Words | Register roles, access forms and emission order |
|---|---|
| 0–13 | `a0` is the object; `a3` is the initialization index; `a2` is element offset; `t2` points to object+0xA0. `t1` holds the defaults page, `t0` its full address via a two-register split. `v0` addresses the second defaults record and `v1` transfers fields. |
| 14–30 | Four-iteration initialization loop: `a1` walks the object, `t0` reads defaults at +4/+8/+12, and `t1` supplies the folded first-field address. `v0` transfers values, `v1` holds the element pointer. Pointer advancement fills the back-edge delay slot. |
| 31–35 | GP-relative first order byte into **v1**, sentinel 4 into **v0**, equality branch, `a2 = object+0x30` in its delay slot. Copy v0 to a3 to hold the sentinel through the link loop. |
| 36–37 | Materialize the absolute order-table address in a1 as `lui` / `addiu`; its loads remain base+displacement accesses. |
| 38–47 | Read current index into v0, advance a1, scale index by 32, add object+0x30, link it through a2+0xC. Read the next byte into v1, retain its load-delay nop, compare with a3, and update a2 in the back-edge slot. |
| 48–49 | Return with the final link's next pointer cleared in the delay slot. |

The new candidate's genuine ASPSX output preserves the frame, the whole initial
loop and the pointer loop. Its only retail differences are four substitutions:
words 31–33 and 35 exchange v0/v1 for the first byte and sentinel. Both streams
are 50 words, with zero unresolved relocations. The
[aligned variant receipts](gp_order_bytes/variant_receipts.json) record the exact
regions. Commuting the comparison and making the byte read explicit did not
change allocation. A first-byte/trailing-three-byte struct representation also
left the same four substitutions; its [receipt](gp_order_bytes/first_and_tail_receipt.json)
is retained. Stop these source-shape trials here; no recipe sweep was used.

## Separately owned assembler difference

With the existing generic small-data correction, maspsx emits 49 words while
genuine ASPSX emits 50 from the identical compiler stream. The
[trace](gp_order_bytes/trace.json) identifies `_fold_selfinc_la` as the only fired
post-pass. It folds the table address into the cursor loads, unlike genuine
ASPSX's preserved full base. Disabling **only** that pass in the private trace
harness restores exact 50-word equality with genuine ASPSX, as the
[ablation receipt](gp_order_bytes/ablation_receipt.json) proves. The four C-owned
register substitutions against retail remain. No production pass is disabled.

## Concrete continuation

Use this site map, the real four-byte candidate, aligned register-role regions
and lineage receipt as the az-c-rebuild handoff. Next compare same-recipe compiler
RTL/live ranges for the original scalar/overlapping-address source and the real
table source, focusing on why the guard's byte and sentinel receive opposite
temporary roles. Preserve the already-correct 31-word initialization prefix and
the natural pointer loop. Do not add a pin or fabricate a larger data owner to
force the coloring. If attribution changes, update the owner table before a new
source trial.

The separate assembler lead requires a refreshed consumer census and full gates
before removal or semantic changes. Neither an exact genuine/maspsx comparison
nor a four-word near miss constitutes a completed row repair.
