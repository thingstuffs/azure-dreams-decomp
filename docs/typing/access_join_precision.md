# Access-join precision probe

The paired probe compares the ACCURACY 131 access census with the extended
proof on 12 large `src/dungeon/effect` translation units and
`src/town/scene/object/create_town_hud.c`. The effect set has 10,252 source
rows and moves from 6,431 to 6,456 exact joins, with no lost joins. The HUD
function has 54 source rows and moves from 16 to 30 exact joins, again with
no lost joins.

All 39 newly mapped rows were reviewed against the source line, base and
member expression, constant offset, access width and direction, and retail
opcode. All 39 agree with the source access; the 14 HUD accesses are stores
through a pointer member of a four-byte local union.

A dedicated instruction-provenance sample checks 30 newly joined rows from
the 12-TU effect set and 18 further effect TUs. All 30 agree on source line,
offset, width, direction and opcode.

The independent width check compares mapped, direct named-record fields with
unambiguous top-level `record_member` sizes. It checks 807 mapped rows in the
12-TU effect probe and finds zero mismatches. Five candidate checks were
excluded because their layout sizes are unknown (`NULL`), rather than treating
an unknown size as a mismatch. This check is separate from the join's own
width equality requirement.

The stack-object proof adds another 106 joins on the same 12 TUs (6,456 to
6,562) with no lost joins. Thirty-four of these new rows were checked by hand
across five files, including byte, halfword and word reads and stores; all 34
match the source line, offset, width and direction. The fixed-frame guard excludes 24 joins that a
less conservative stack tracker would have made in this probe.

For the four-byte local aggregate extension, 38 TUs containing pointer unions
have 4,892 joins before its register-location proof and 4,931 after it. All 39
new rows, with zero lost joins, were checked by hand against the same source
and opcode criteria. This includes signed and unsigned loads, stores, and a
negative-offset header access.

The direct-global HI16/LO16 relocation proof was checked on 40 TUs with
33,968 source rows. It increased joins from 21,716 to 22,989, adding 1,273
with none lost. Thirty new joins across 30 files were reviewed against their
source line, byte offset, width, direction and opcode. The independent layout-width check covered
7,224 eligible mapped rows in the new probe and found zero mismatches.
The completed 5,987-TU comparison adds 4,769 exact mapped sites, with zero
lost or retargeted prior joins. Its independent width check covers 33,294
eligible rows with zero mismatches. One former same-line join initially became
ambiguous because a cross-line global fallback claimed the same opcode; the
same-line precedence guard restored it, and all 112 ambiguity TUs were
remeasured before the final comparison.
