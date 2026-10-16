/* Relink of matched dungeon/func_80284EBC; every changed retail word is a paired relocation. */
#include "modules/dungeon_floor_generate.h"

s16 func_80017EBC(s16 entry_index) {
    s16 count = 0;
    u8 *entry_base = (u8 *)D_800E2970;
    floor_generate_isolated_80284EBC_DungeonEntry *region = (floor_generate_isolated_80284EBC_DungeonEntry *)(entry_base + (entry_index * 20));
    MapGrid *state = &gameWork.map;
    s16 height = region->height;
    u16 y = region->y;
    s16 rows_left = height;

    if (height > 0) {
        floor_generate_isolated_80284EBC_DungeonEntry *entry = region;

        while (rows_left > 0) {
            floor_generate_isolated_80284EBC_DungeonCell *cell = (floor_generate_isolated_80284EBC_DungeonCell *)((u8 *)((floor_generate_isolated_80284EBC_DungeonCell *)state->cells) + (((s16)y << state->shiftX) * 6)
                + (entry->x * 6));
            s16 cols_left = entry->width;

            while (cols_left > 0) {
                if (!(cell->flags & 0x8500)) {
                    count++;
                }
                cell++;
                cols_left--;
            }
            y++;
            rows_left--;
        }
    }
    return count;
}
