# Initialized E758 data layout inventory

The actual private input is `initialized/w_8003E758.c` (SHA-256
`1d29f07f03c2648192dfaa7ed8ab49f1c060f7d92860aa2677fbc3cc80cc7c4f`).
It defines **eight** objects totaling **23 initializer bytes**. `D_80080ADC`
is absent; `D_80081450[8]` is present. The saved `initialized/a.o` and
`generic.o` both contain these eight symbols in a 28-byte `.sdata` section;
`initialized/a.s` shows five compiler alignment bytes between definitions.
Those object bytes and their order cannot simply replace the eight disjoint
retail locations. This is a layout inventory, not a successful owner layout.

The selected bytes below are all zero in `build_slus/assets/54240.bin` and the
corresponding retail image interval. The asset is 0x2BDC0 bytes, SHA-256
`c4e7faf5c7f42838e9fb2e9238af76ed6972cdc8ef055fa2b02a18d9360f76da`,
and maps EXE file offsets `0x54240..0x80000` to VMAs
`0x80080A40..0x800AC800`. Endpoints below are exclusive.

| Candidate definition | Type | Asset interval | VMA interval | Size |
|---|---|---|---|---:|
| `D_80080AD0` | `u8` | `0x90..0x91` | `80080AD0..80080AD1` | 1 |
| `D_80080AD2` | `u16` | `0x92..0x94` | `80080AD2..80080AD4` | 2 |
| `D_80080AD4` | `u16` | `0x94..0x96` | `80080AD4..80080AD6` | 2 |
| `D_80080AD8` | `s32` | `0x98..0x9C` | `80080AD8..80080ADC` | 4 |
| `D_80081450` | `u8[8]` | `0xA10..0xA18` | `80081450..80081458` | 8 |
| `D_800814CC` | `u32` | `0xA8C..0xA90` | `800814CC..800814D0` | 4 |
| `D_800814D0` | `u8` | `0xA90..0xA91` | `800814D0..800814D1` | 1 |
| `D_800814D4` | `u8` | `0xA94..0xA95` | `800814D4..800814D5` | 1 |

The final link uses `build_slus/build/slus_006.14_ordered.ld` and
`build_slus/build/slus_006.14.undefined_syms.modules.txt`; the base linker
selects `build/assets/54240.o(.data)` once. The eight definitions occupy
**three** existing ordered-linker raw selectors:

| Current selector | Selected definitions inside it | Raw remainder intervals if selected bytes are carved |
|---|---|---|
| `54240_000074_0000BE.o(.data)` (line 738) | AD0, AD2, AD4, AD8 | `74..90` (28), `91..92` (1), `96..98` (2), `9C..BE` (34) |
| `54240_000A0C_000A20.o(.data)` (line 755) | 81450 | `A0C..A10` (4), `A18..A20` (8) |
| `54240_000A24_000AA0.o(.data)` (line 757) | 814CC, D0, D4 | `A24..A8C` (104), `A91..A94` (3), `A95..AA0` (11) |

Each current raw `.bin` equals its exact asset slice. The projected **nine**
remainder selectors, intervals, and SHA-256 hashes are in
`layout_inventory.json`. The selected extents form **six** islands because
AD2/AD4 and CC/D0 touch. The existing output section has `SUBALIGN(1)`.
`tools/build/slus_modules.py:data_sections` requires each module input
`.sdata` or `.sbss` section to describe one contiguous, ordered span. An
eventual prototype therefore needs a concrete section/object split preserving
all intervening raw bytes; the saved 28-byte E758 `.sdata` section does not
fit these six islands by itself. The five alignment bytes in that object are
compiler layout, not permission to absorb retail gaps.

`filter_owned_symbols` removes only a registered data name with its exact
VMA. The generated absolute map currently assigns all eight selected names;
if owned, filter those eight and retain `D_80080ADC` at `80080ADC`. Also retain
unowned names such as `D_80081451` and `D_80081452`, which are absolute aliases
*inside* the proposed eight-byte 81450 span, and `D_800814D1/D2/D3` in the
three-byte gap after D0. Other adjacent assignments remain intact. AD0, AD4,
81450, D0 and D4 have named consumers outside E758 and need globally resolvable
definitions while those rows stay outside the owner; AD2, AD8 and CC have only
the E758 consumer in the present source inventory. In particular,
`w_8003F368.c` declares 81450 as a four-byte union view while this input
defines an eight-byte array. A shared declaration must reconcile those views;
the eight-byte extent follows the saved E758 input and the separate SDK buffer
audit, not the four-byte union alone.

A private link proof must check that the selected initializer bytes and VMAs
match these intervals, each of the nine raw remainders matches its original
asset slice, and all **179,625** other asset bytes remain equal at their
original offsets. Their offset-ordered concatenation currently hashes to
`a969af86b62590b8d251feced3a174f2bc9cd4fdfcb818198554c3d03c15b941`.
It must also verify exact absolute-symbol filtering, outside object hashes,
ordered linker slots, and the full 524,288-byte retail image. No build,
fixture, or production file was changed for this correction.
