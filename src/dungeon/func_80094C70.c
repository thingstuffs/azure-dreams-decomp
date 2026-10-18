#include "common.h"
#include "shared/game_work.h"

typedef struct {
    u8 pad[4];
    u16 flags;
} DungeonCell;

s32 count_floor_items_at_tile(s16 first_key, s16 second_key);

/* Clears selected cell flags or decrements their encoded value, clamping at zero. */
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags)
{
    DungeonCell *cells;
    MapGrid *map;

    cells = (DungeonCell *)g_game_work.map.cells;
    map = &g_game_work.map;
    if (flags & 0x8832) {
        if (flags & 0x800) {
            s16 cell_x = x;
            s16 cell_y = y;

            if ((s16)count_floor_items_at_tile(cell_x, cell_y) >= 2) {
                return;
            }
            cells[cell_x + (cell_y << map->shiftX)].flags &= ~flags;
        } else {
            cells[(s16)x + ((s16)y << map->shiftX)].flags &= ~flags;
        }
    } else {
        s32 cell_x = (s16)x;
        s32 cell_y = (s16)y;
        s32 i;
        u16 old_flags;
        s16 remainder;

        i = cell_x + (cell_y << map->shiftX);
        old_flags = cells[i].flags;
        remainder = (old_flags & flags) - (flags & 0x1100);
        cells[i].flags = old_flags & ~flags;
        if (remainder < 0) {
            remainder = 0;
        }
        cells[cell_x + (cell_y << map->shiftX)].flags |= remainder;
    }
}
