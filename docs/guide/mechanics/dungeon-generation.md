# Dungeon generation and population

[Mechanics index](README.md) · [Dungeon source map](../dungeon.md) · [Item rarity](items.md#floor-rarity) · [Monster decisions](monsters.md)

## Seed, fixed layouts and generated layouts

Verified by reading `setup_run_and_load_track`, `setup_dungeon_floor_encounters`
and `load_dungeon_layout` in
[`generate.c`](../../../src/dungeon/level/generate.c).
Setup chooses a saved/revised seed or combines two `rand()` results with a
game-work value. It seeds both RNG interfaces, clears floor item/object
records, and selects floor encounters. A nonzero encounter code chooses a
track configuration, optional fixed layout and callback list. Otherwise it
loads a terrain resource and repeatedly clears/regenerates the layout until
generation succeeds and the floor state is ready. Final steps apply tile
masks, place elevators unless a fixed layout already supplied them, and write
border cells.

A fixed layout reads dimension shifts, room rectangles, region entries,
floor markers, item entries and object entries, then decompresses the tile
grid. Item/object marker 99 selects loaded-content flags. Fixed content and
procedural generation therefore have different data paths; the procedural
rules below are not claims about every tutorial/event map.

## Room layout and terrain

Verified by reading `generate_floor_layout`, `fill_region_with_random_patches`
and `update_region_until_complete` in
[`generate.c`](../../../src/dungeon/level/generate.c).
The procedural algorithm partitions a 64-tile coordinate space into 2, 3 or
4 columns and independently 2, 3 or 4 rows. Each dimension's roll chooses 2
when `(r & 127)==0`, otherwise 3 when `(r & 31)==0`, otherwise 4.
These are slot counts, not a promise of that many finished rooms.

Most layout attempts mark each slot usable with `(random & 3)!=0`. In each
marked slot, random origin/size choices are tested against an expanded
reservation rectangle. Accepted rectangles become rooms and receive a
`random & 0x60` value. Rejected or unmarked slots retain waypoint-like
coordinates for connection work. A separate rare branch bypasses ordinary
room placement. If fewer than two rooms result, the code creates one large
room at (2,2), with width/height equal to the map dimensions minus four.

Room terrain is first filled, then patched with raised/lowered rectangles
and surrounded by a border. The number of patch attempts is approximately
`(width + height) / 4`; before floor 5 it uses `/16`. Random patch dimensions
can be nonpositive, so an attempt need not alter tiles. A room feature is
chosen, traversal is checked, and failed room layouts retry.

Room feature rolls use `random & 255`. Cases 1, 2 and 4 attempt a special
object, item room and trap room respectively, sharing a single-feature latch;
case 0 changes the room type without that latch, and cases 5..12 alter tile
heights on a selected coordinate parity. These branch counts are not final
floor probabilities because retries and the latch change which rolls survive.
Special item/trap records can remain from failed terrain attempts:
[B019](../../BUGS.md#items-and-traps-on-regenerated-floors).

## Connecting rooms

Verified by reading `connect_rooms_with_corridor`,
`choose_next_step_toward_destination`, `carve_corridor_toward_destination`
and the link loop in `generate_floor_layout`, all in
[`generate.c`](../../../src/dungeon/level/generate.c).
The generator chooses a starting slot and cardinal direction, searches outward
for eligible slots, and records successful links. A source/destination pair
chooses points on room edges and can pass through intermediate slots. The
carver uses cardinal segments with randomized bend offsets; it advances an
interpolated height value and rejects an existing non-sentinel cell when its
height differs by at least 33. The connection routine also rewrites doorway
and adjacent edge tile kinds.

The slot walk has a 1024-initialized retry counter; after exhaustion it clears
active unlinked rooms. Generation then compacts region records, clears
temporary masks and updates area tiles. The outer setup can regenerate a
failed floor. This is an iterative room/link construction, not a proven
minimum spanning tree or a guarantee that every initially proposed room
appears in the final map.

## Monster tables and spawning

Verified by reading `load_floor_spawn_tables`, `setup_dungeon_floor_encounters`
and [`spawn_floor_monster_from_table`](../../../src/dungeon/item/spawn_floor_monster_from_table.c).
The floor resource at index `floor + 0x3f5e` supplies 32 bytes copied into
`monster_spawn_table`, 32 bytes copied into `floor_species_pool`, and a terrain
variant byte at resource +0x40. The ordinary spawn table is consumed as 16
two-byte species/level pairs. The species pool is also used for eggs.
The loader proves the format and floor-indexed resource selection, not a
decoded species list for every floor.

The spawn routine returns when the suppress-spawn floor flag is set or the
live monster count reaches 32. It makes at most 16 tile attempts, requiring
an active room. Mode zero also requires Manhattan distance at least 33 from
the player. Modes below two choose table index `random & 15`; later modes
address a specific pair and take a separate cleanup path. A species-zero
entry returns without spawning. Successful ordinary spawns initialize stats,
seed EXP from the requested level and repeatedly raise the actor against the
following threshold, then choose a held/drop item when no item is already set.

The second-tower setup has special table construction. Some groups cap
`floor + (random & 1)` at 99, but the last two groups do not. On floor 99 they
can request level 100 and leave the capped leveling loop running:
[B016S](../../BUGS.md#spawning-monsters-past-level-99).

[`select_dungeon_spawn_tile`](../../../src/dungeon/actor/entity_spawn_load.c)
tries 256 random room tiles, filtering tile mask `0xf720`, then scans the
interior coordinates 1..62. If neither path succeeds it can retain valid
input coordinates or fall back to (1,1). This fallback is another reason not
to infer that every caller receives a newly proven free tile.

## Item counts and trap population

Verified by reading `populate_floor_item_records` and
`restore_spawns_and_place_floor_traps` in
[`spawn.c`](../../../src/dungeon/level/spawn.c).
The item array holds 64 entries. For one room, ordinary population uses a
slot limit of `8 + (random & 7)`; otherwise it uses
`floor(room_count / 2) + (random & 3)`. Existing records, special placements,
overrides and category-14 drops make this different from a guaranteed final
number of visible items. Item kinds/rarity are detailed in [Items](items.md).

Trap setup first restores saved kind-19 monster records, then populates
kind-21 trap records. For one room the ordinary trap slot limit is
`4 + (random & 3)`; otherwise `room_count / 2 + (random & 3)`, capped at 32.
Its initial budget is `floor_number / 2 + (random & 63)`, with another
`random & 15` added per ordinary candidate. A candidate trap ID comes from
1..19, excludes rarity field 3, and costs `4 + 4*rarity_field`. IDs 15 and
16 also require a tested floor flag. Accepted entries select a spawn tile,
set the object occupancy flag and prepare height/display state. Loaded trap
records take their own branch and need not obey the new-candidate budget.

Verified by reading `place_room_trap_records` in
[`generate.c`](../../../src/dungeon/level/generate.c).
A trap room instead starts at index
`min(28, floor(room_area/8) + (random & 7))` and scans **through zero**.
Thus its maximum is 29 attempted slots, not 28 guaranteed traps. Each attempt
can fail its tile or rarity checks. A room-wide zero roll on `random & 255`
forces trap ID 7; other rolls choose IDs 1..19 and reject rarity field 3.
These writes do not preserve preexisting slots, including the reserved
floor-31 encounter: [B020](../../BUGS.md#special-encounter-and-item-records-overwritten).
The [item-room special suppression](../../BUGS.md#special-encounter-and-item-records-overwritten)
is another ordering effect, separate from the rarity selector.
