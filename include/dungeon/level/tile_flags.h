#ifndef DUNGEON_LEVEL_TILE_FLAGS_H
#define DUNGEON_LEVEL_TILE_FLAGS_H

/* Occupancy bits in the flag halfword at +4 of a six-byte map cell; map loading supplies the cells.
 * cycle_map_cell_flags sets these bits; update_map_cell_flags_with_item_limit clears them, retaining item occupancy
 * while count_floor_items_at_tile reports two or more entries. The other cell fields include encoded counters. */
enum TileFlags {
    TILE_HAS_OBJECT = 0x20, /* floor object/fixed-marker occupancy; neighboring-tile blockage checks include this bit */
    TILE_HAS_ITEM = 0x800, /* ground item occupancy; clearing is deferred while at least two items still occupy the tile */
};

#endif
