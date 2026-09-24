# CD state inventory at `f02cb899`

Read-only source and manifest inventory on the active 23-module, 869-physical-object,
21-GP-row baseline. The companion `state_inventory.json` records each observed
width, VMA interval, `54240` asset offset, initial bytes, declaration, consumer,
and row recipe. All listed bytes equal the retail image. No source, recipe,
manifest, or build was changed for this inventory.

## Ownership and storage

None of the twelve symbols below is covered by a `data` entry in
`config/slus_modules.json`. They remain references to the `54240` asset in the
current build. The nearby named owners do not cover them: `gp_shared_slots`
ends its listed group at `80080AB3`; `owned_80035484` and `owned_80038A10`
own `80081440` and `80081448`; `sort_rank_81540` owns `80081540`;
`command_slots_81554` starts at `80081554`. The table gives **observed access
extent**, not a proved historical allocation or a right to claim intervening
bytes. All requested intervals initialize to zero.

| Symbol | Observed VMA interval, end exclusive | Asset offset | Access/declaration evidence |
|---|---:|---:|---|
| `D_80080AD0` | `80080AD0–80080AD1` | `0x90` | one byte: `s8` reset in 3E34C, `u8` test in 3E758 |
| `D_80080AD2` | `80080AD2–80080AD4` | `0x92` | `u16` increment/test in 3E758 |
| `D_80080AD4` | `80080AD4–80080AD6` | `0x94` | `s16` reset in 3E34C/Control_CD; `u16` set/test in 3E758/3F5AC |
| `D_80080AD8` | `80080AD8–80080ADC` | `0x98` | `s32` CdReadSync result in 3E758 |
| `D_80080ADC` | `80080ADC–80080AE0` | `0x9C` | `s32` reset in 3E34C; `void *` event pointer in Control_CD |
| `D_80081450` | `80081450–80081454` | `0xA10` | `u8` status in 3E758; four-byte location union save/clear/restore in 3F368 |
| `D_800814B0` | `800814B0–800814B4` | `0xA70` | `s32` pair word written in 3F2A4 |
| `D_800814B4` | `800814B4–800814B8` | `0xA74` | `s32` pair word written in 3F2A4 |
| `D_800814CC` | `800814CC–800814D0` | `0xA8C` | `u32` end-address store and pointer dereference in 3E758 |
| `D_800814D0` | `800814D0–800814D1` | `0xA90` | one byte: `s8` reset in 3E34C; `u8` ring head in 3E758, 3F2A4, 3F368, code2's 3F240 |
| `D_800814D4` | `800814D4–800814D5` | `0xA94` | `u8` mode stores in 3E758 and 3F624 |
| `D_80081550` | `80081550–80081554` | `0xB10` | four-byte message-mode selector; see separate component below |

The AD0–ADF envelope has 13 named payload bytes but also unclaimed AD1 and
AD6–AD7. B0/B4 are an eight-byte pair, yet `D_800814AC[12]` is an overlapping
address-generation view in 3F2A4, not another twelve-byte owned object. The
CC/D0/D4 envelope contains active D1–D3 byte names between the listed fields.
3E34C writes D2/D3 by absolute address; 3E758, 3F368 and 3F624 use D1/D2/D3
extern or alias views. Likewise 3E758's `D_80081438[0x20]` reaches the
`D_80081450` status address, while 3F368 declares D81451/D81452 as 16-byte
code-generation views. Their declared array sizes do not prove independent
allocations. A contiguous owner for either area must resolve these aliases and
the intervening bytes before a carve can be asserted.

## Current consumers and recipes

The CD state listed above has **eight direct function consumers**: seven whole
rows and `func_8003F240`, which is still in the `code2` collector remainder.
`func_8003E34C` resets AD0/AD4/ADC and D0; `Control_CD` writes AD4/ADC;
`func_8003E758` drives AD0/AD2/AD4/AD8, CC/D0/D4 and reads the 81450 status;
`func_8003F5AC` reads AD4; `func_8003F2A4` writes B0/B4 and reads D0;
`func_8003F368` uses the 81450 four-byte view and D0; `func_8003F624`
writes D4; `func_8003F240` reads D0. No selected whole CD row is already a
member of a named ownership module.

| Current row/function | Registered compiler recipe |
|---|---|
| 3E34C, Control_CD/3E4FC, 3F5AC | `2.7.2-cdk`, default flags |
| 3E758 | `2.7.2-cdk -G32 -fno-expensive-optimizations` |
| 3F2A4 | `2.6.3 -fno-schedule-insns` |
| 3F368, 3F624 | `2.7.2`, default flags |
| code2 remainder, including 3F240 | `2.8.1`, default flags |

The signed/unsigned one-byte and halfword declarations at AD0, AD4 and D0
have equal access width but incompatible C types. ADC's `s32`/`void *` views
also disagree. `D_80081450` has a material width conflict (`u8` versus a
four-byte union), although both uses currently address the same starting byte.
These need a shared, evidence-based declaration or consciously separate views
before any joined source can compile and prove. The five current recipes also
preclude treating all eight functions as one ordinary owner TU without a
measured recipe change. The existing `code2` collector must retain its other
canonical functions if 3F240 is extracted.

`D_80081550` is a **separate message-mode component**, adjacent to the active
81554/58 owner but with different users. `func_8004DCE0` is still in the
`code` collector remainder and stores it; whole rows 4DCEC, 4DE88 and 4DF8C
index the `D_800714A4` handler table with it. `include/globals.h` and 4DCEC
declare `int`, while 4DE88/4DF8C declare `s32` (all four-byte MIPS32 views).
Their registered recipes are `code` 2.7.2, 4DCEC CDK with
`-fno-schedule-insns -fno-delayed-branch`, and 4DE88/4DF8C default CDK.
Its one named four-byte slot at B10–B13 is currently unowned; grouping it with
CD command state solely because both have GP references would be unsupported.

The next bounded CD experiment is to choose a declaration contract for the
five AD fields, the 81450 four-byte view, B0/B4, and CC/D0/D4, then compile
the eight consumers in their registered physical recipes with a single
collector part for 3F240. Establish exact bytes and emitted function sets
before considering owner modules or any recipe move. This inventory grants no
historical translation-unit or placement claim.

Evidence read: `src/slus` direct symbol uses, `include/globals.h`,
`config/slus_modules.json`, `config/slus_partitions.json`,
`ledger/splits/slus.jsonl`, `ledger/maspsx_dependence.jsonl`,
`docs/evidence/fidelity_gp_symbols.tsv`, `build_slus/assets/54240.bin`, and
`baserom/slus_006.14` at the selected offsets.
