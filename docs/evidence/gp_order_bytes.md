# 49F68: real order bytes, C register roles and an assembler pass

Status: **source repair privately genuine/retail-exact; not integrated**.
The resumed az-c-rebuild investigation resolved the four register substitutions
through RTL-guided source ordering. The remaining assembler issue is
`_fold_selfinc_la`, tracked in `tools/maspsx_leads.md`. Production source and its
six existing pins remain unchanged. The original near-miss below is retained as
measurement history; the solved candidate and continuation follow it.

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
outside this candidate. This original source was a near miss; see the solved successor below.

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

## RTL-guided source repair

The [solved candidate](gp_order_bytes/solved_candidate.c) reads the first byte
into `elem_index` **before** assigning `end_marker = 4`, then compares those
locals. This is the only body change from the real-table candidate. Both reads
remain after the initialization loop, and the new assignment crosses no call or
memory write. The table stays exactly four bytes and all six existing pins remain.

The [RTL receipt](gp_order_bytes/rtl_receipt.json) compares the original source,
the near-miss table source, and this successor at the same CDK recipe. The original
scalar guard expands directly to `mem:QI(symbol)`. The array guard first creates
address pseudo 112; CSE folds the load back to the symbol but reuses that pseudo
for the cursor beyond the branch. It therefore remains live during scheduling.
In the near miss, scheduled instruction 118 sets sentinel pseudo 92 before
instruction 122 loads byte pseudo 113; local allocation gives them v1 and v0.
The address pseudo is then eliminated, leaving those reversed roles in the code.

Moving the explicit byte read before the marker assignment changes this order:
instruction 125 loads byte pseudo 113 before instruction 123 sets sentinel
pseudo 92. Local allocation now gives the byte v1 and the marker v0, matching
retail. The frame, complete 31-word initialization prefix, pointer loop and
return are unchanged. A separate four-byte packed-word representation did not
fix the near miss; its [control receipt](gp_order_bytes/packed_word_receipt.json)
records the same four substitutions. No padding, volatile qualification or new
pin was needed.

The [independent verification](gp_order_bytes/solved_verification.json) compares
all 50 words against the actual 200-byte retail extent, with zero relocation
masks. Genuine ASPSX 2.67, 2.77, **2.79** and 2.81 reproduce retail exactly.
With the generic small-data correction and only `_fold_selfinc_la` disabled in
the private harness, maspsx also matches all 50 words and emits the exact
`.sdata` bytes `01 03 02 04`, with the global symbol at section offset zero.
ASPSX 2.86 is a measured version boundary: its GP-relative address load shortens
the function to 49 words. It is not claimed exact or selected for production.

Reproduce the compiler evidence with
`python3 work/native_lane/gp_order_bytes/rtl_probe.py` and the genuine/retail
comparison with `python3 work/native_lane/gp_order_bytes/guard_verify.py`.
The [private full-link receipt](gp_order_bytes/link_receipt.json) also passes:
the full image equals retail, SHA-1
`e6bfbb95ff6676899e077481221d73ddd4d3bf52`, and the linked function is exactly
200 bytes at `0x80049F68`. Object, genuine and retail comparisons cover all
50 words. The real global is at `.sdata+0`, linked at `0x80080B30`, replacing
asset 54240 bytes `0xF0..0xF3`. The adjacent four color bytes at B2C remain in the
raw chunk. All 17 production modules, every logical recipe and the other 873 C
objects are unchanged. Reproduce with
`python3 work/native_lane/gp_order_bytes_link/probe.py`.

Only the private owner input uses the generic correction plus the one-pass
ablation. This routing is a measurement aid, not a source-specific production
exception. The receipt's `stock_retail` field refers to that privately assembled
linked object; it does **not** claim the untouched production assembler passes.

## Concrete continuation

Keep the solved source queued with its real storage and private full-image proof.
Refresh `_fold_selfinc_la` consumers, repair their C/recipes, and prepare the
assembler transition together with the other remaining GP changes. No production
pass is disabled and no dependency record is removed by this evidence. Preserve
the required genuine, cell-retail and full-link gates before integration.
