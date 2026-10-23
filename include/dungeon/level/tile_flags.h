#ifndef DUNGEON_LEVEL_TILE_FLAGS_H
#define DUNGEON_LEVEL_TILE_FLAGS_H

/* Map-cell flags (+4 in each six-byte cell), passed to cycle_map_cell_flags
 * and update_map_cell_flags_with_item_limit. Floor object slots and fixed
 * markers use 0x20; ground item slots use 0x800. Item pickup clears 0x800
 * only when fewer than two ground items remain at the tile. */
enum TileFlags {
    TILE_HAS_OBJECT = 0x20,
    TILE_HAS_ITEM = 0x800,
};

#endif
