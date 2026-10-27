# Species 22 segmented line renderer: draw_segmented_motion_lines

The 1,152-byte renderer shared by the resource-22 (troll family) slot images is
now complete C in `src/dungeon/monster/troll/draw_segmented_motion_lines.c`,
one source for all seven placements:

| placement row | DUNGEON offset | VMA | link image |
|---|---|---|---|
| dungeon/func_80CE706C (home) | 0xD0706C | 0x8017086C | dungeon/bank_d07000 |
| dungeon/func_80CED06C | 0xD0D06C | 0x8016A86C | dungeon/bank_d0d000 |
| dungeon/func_80CF306C | 0xD1306C | 0x8016486C | dungeon/bank_d13000 |
| dungeon/func_80CF906C | 0xD1906C | 0x8015E86C | dungeon/bank_d19000 |
| dungeon/func_80CFF06C | 0xD1F06C | 0x8015886C | dungeon/region_d1f06c_d1f4ec |
| dungeon/func_80D0506C | 0xD2506C | 0x8015286C | dungeon/bank_d25000 |
| dungeon/func_80D0B06C | 0xD2B06C | 0x8014C86C | dungeon/bank_d2b000 |

The seven bodies differ only in one internal absolute `j` (to entry +0x31C);
each resolves exactly at its own address. Every bank's copy of
`process_linked_states_mode_zero` (dispatch.c) already binds its
draw_sprite_parts_as_quad_grid call to the renderer at that bank's address.

## Recipe

GCC 2.7.2-cdk -O2 -G0. **Genuine ASPSX 2.79 needs `-q -G0 -0`**: the unit
contains signed `div` (each interpolated coordinate divides by the segment
count). With `-0` the genuine and maspsx complete units are identical; without
it ASPSX expands the checked division (342 words versus 288) and the unit
differs. Plain overlay rows have no per-row genuine-assembler field (the
`genuine_aspsx` flag exists only on native modules in
`config/overlays/modules.json`, and `row_asflags` refuses `-0`), so the flag is
recorded here and in the lane receipt. A later native-module conversion of this
TU must carry `genuine_aspsx: {"flags": ["-0"]}`.

## Shape

The segment count is the longer of |x| and |y| of the effect's motion vector
(body +0x58/+0x5C/+0x60, integer halves), divided by 16, at least one. The
length is computed in its own statement, `length = abs(x) <= abs(y) ? abs(y) :
abs(x); segments = length / 16;` with builtin `abs`: folding the division into
the same expression swaps the scratch and packet registers (s1/s2) against
retail. Each segment interpolates the three coordinates, duplicates the endpoint
pair for RotAverage4, subtracts the signed depth bias and six, and links a
16-byte LINE_F2 packet; a draw-mode packet follows. Sprite flags 8/4 choose the
semi-transparency bit.

The packet cursor is read through a draw-context view whose +0x8D0 cursor is a
union of the two packet types, and the scratchpad base comes from a header
macro, so the function body has no pointer casts and no local declarations.

## Data-row trims

In each slot image the unclassified data-segment row before the function
(func_80CE6AC0, func_80CEC5C4, func_80CF25C4, func_80CF85C4, func_80CFE5C4,
func_80D045C4, func_80D0A5C4) extended eight bytes into it. Each keeps its
identity and start and loses only those eight bytes.

## Related typing

`draw_ribbon_center_lines` (dungeon/func_8132F968, 940 bytes) takes its render
argument as SpriteFrameState (run-13 carve typing; nine casts and three
generated layouts removed); its prototype is in `include/dungeon/effect/particle.h`.
Its complete object is unchanged.
