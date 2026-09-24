# CD shared-declaration inventory

Read-only inventory of the selected CD-state declarations and accesses. Source
line references below identify the exact seven whole-row files requested plus
the `func_8003F240` span in `code2.c`. The companion JSON records declarator
bounds and source hashes. Declarator overlaps are C views only; they do not
establish independent allocations, historical TU ownership, or a storage
contract. No declaration fix or compiler conclusion is inferred here.

The state snapshot in `docs/evidence/gp_cd_partition/state_inventory.{md,json}`
is baseline `f02cb899` (23 modules, 869 physical objects, 21 GP rows). It reports
zero initial bytes equal to retail for the listed symbols and gives observed
access extents, not historical allocation extents. Its mapped intervals and
recipes are included below as snapshot evidence. `D_800814D8` is declared in
source but is not one of the snapshot's mapped rows, so this inventory makes no
asset-offset or initial-byte claim for it.

## E758 state fields

| Address symbol | Snapshot interval / asset offset / bytes | Source declarations and observed accesses |
|---|---|---|
| `D_80080AD0` | `AD0–AD1`, `0x90`, `00` | E34C declares `s8` and stores zero (13, 28); E758 declares `u8` and tests against zero (46, 384). Same one-byte access width, signedness differs. |
| `D_80080AD2` | `AD2–AD4`, `0x92`, `0000` | E758 declares `u16`, increments and tests `(value & 3) == 3` (47, 388–389). |
| `D_80080AD4` | `AD4–AD6`, `0x94`, `0000` | E34C and `Control_CD` declare `s16` and store zero (E34C 14, 30; E4FC 12, 123); E758 and F5AC declare `u16`, E758 stores 1 and F5AC tests nonzero (E758 48, 470; F5AC 5, 12–16). Width agrees; signedness differs. |
| `D_80080AD8` | `AD8–ADC`, `0x98`, `00000000` | E758 declares `s32`, stores `CdReadSync` result, then tests positive / zero / negative values (49, 381–383, 407). |
| `D_800814CC` | `814CC–814D0`, `0xA8C`, `00000000` | E758 declares `u32`; stores a computed end address (40, 179), then casts the value to `u32 *` and dereferences it (385). |
| `D_800814D0` | `814D0–814D1`, `0xA90`, `00` | E34C declares `s8` and stores zero (16, 24); E758, F2A4, F368 and code2 declare `u8` (E758 36; F2A4 10; F368 23; code2 297), with ring-head indexing/increments, decrement-and-mask, and previous-entry lookup (E758 101–149, 230–267, 353–354, 438, 487–500; F2A4 37; F368 77, 81; code2 301–302). One-byte width; signedness differs. |
| `D_800814D4` | `814D4–814D5`, `0xA94`, `00` | E758 and F624 declare `u8` (E758 39; F624 6); E758 stores `0x80` (180), F624 stores `0x84` (17). |
| `D_80081450` | `81450–81454`, `0xA10`, `00000000` | E758 declares `u8` and reads it as status / bit flags (42, 435, 455–456); F368 declares a four-byte union `{u32 raw; struct {u8 mm, ss, sect, mode;} b;}` (5–13, 20), copies it, clears `.raw`, restores it, and reads `.b.mm` (37, 45–46, 86, 90, 95). Material one-byte versus four-byte declaration-width conflict. |

`D_800814D8` is `extern u8 D_800814D8[16]` in E758 (41); it is passed to
`CdReadSync(1, ...)` as its result buffer (381). Its C-declared span is
`814D8–814E8`; that span overlaps other array views below. This source set does
not establish the array's independently allocated size or its asset bytes.

The adjacent `D_80080ADC` is also relevant to interpreting the AD fields:
snapshot interval `ADC–AE0`, asset offset `0x9C`, bytes `00000000`; E34C
declares `s32` and resets it (15, 29), while E4FC declares `void *`, loads the
event source's `field4`, and stores `event_data` (13, 112, 131). This is a
same-address four-byte integer/pointer view disagreement, outside the
AD0/AD2/AD4/AD8 focus set.

## Overlapping views and direct accesses

- **81438 / 81450 status and location:** E758 declares `u8 D_80081438[0x20]`
  and documents `&D_80081438[0x18] == &D_80081450`; `CDBUF` is that address
  (E758 43, 82), passed to CD operations (148, 374, 411, 434). Its declared
  range is `81438–81458`, overlapping the four-byte F368 location union at
  `81450–81454`. E758 separately reads the first status byte at `81450`.
- **814D1:** E758 declares `u8 D_800814D1[16]` (`814D1–814E1`) and reads byte
  zero as the queue tail (37, 101).
- **814D2 / 814D3 / 814D4 / 814D8:** E758 declares `u8 D_800814D2[16]`
  (`814D2–814E2`), `u8 D_800814D3[16]` (`814D3–814E3`) and multiple
  `D_800814D3_*[16]` names with `__asm__("D_800814D3")` (65–80), as well as
  `D_800814D8[16]` (`814D8–814E8`). These declared spans overlap each other
  and the scalar `D_800814D4`. E758 reads/writes `[0]` state bytes and takes
  `&D_800814D3[1]` for `CdControl` (101–181, 234–254, 364–402, 428–475);
  F368 declares `D_800814D3[16]`, uses it as `recovery_state`, writes byte 0,
  and reads `recovery_state[-3]` (F368 24, 67–79); F624 instead declares
  `D_800814D3[8]` and passes `&D_800814D3[1]` to `CdControlB` (7, 17–19).
  E34C writes D2 and D3 through absolute `u8 *` casts (21–22, 25).
- **814D2 named views:** Besides `D_800814D2[16]`, E758 declares
  `D_800814D2_P[16]` and `D_800814D2_R[16]`, both explicitly aliased to symbol
  `D_800814D2` (78–80). It writes/reads index zero through these views (119,
  131, 144, 214, 402, 458–464). F368 declares `S_80081451 D_80081451` and
  `D_80081452`, where that struct is `u8 val; u8 pad[15]` (F368 15–22): each
  object has a 16-byte C extent starting one/two bytes after 81450. It uses
  `.val`, passes `(u8 *)&D_80081451 - 1` to CD APIs, and reads through byte
  casts at offsets `-1` and `+1` (F368 56, 68, 90–93, 101–103). These are
  overlapping address views, not proof of 16-byte owned objects.
- **814B0 / 814B4 pair:** F2A4 declares two adjacent `s32` globals (15–16),
  writes each from the pointed-to pair fields (41–42), and repoints the entry
  to `(S_8003F2A4_pair *)&D_800814AC[4]` (43). `D_800814AC` is declared
  `u8[12]` (`814AC–814B8`, 21), so its address-generation view covers both
  scalar addresses. The two scalar intervals and the larger array declarator
  overlap by address; the array is not evidence for a 12-byte payload owner.

## Snapshot recipes and limits

The companion state inventory records E34C and E4FC/`Control_CD` as
`2.7.2-cdk` default, E758 as `2.7.2-cdk -G32 -fno-expensive-optimizations`,
F5AC as `2.7.2-cdk` default, F2A4 as `2.6.3 -fno-schedule-insns`, F368 and
F624 as `2.7.2` default, and `func_8003F240` in the `code2` collector remainder
as `2.8.1` default. These are the snapshot's row recipes, not a measured
recommendation to combine the functions. Declarator overlap, shared symbols,
and address adjacency alone do not decide a storage contract or ownership
group. In particular, this report does not assert that the source array extents
match retail object allocation extents.

## Provenance hashes

SHA-256 hashes of the exact inputs inspected are recorded in `cd_contract.json`
so later review can detect source or evidence drift.
