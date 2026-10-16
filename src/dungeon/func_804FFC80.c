/* Relink of matched dungeon/func_80284480; every changed retail word is a paired relocation. */
#include "modules/dungeon_floor_generate.h"

void func_80017480(s16 start_x, s16 start_y, s16 rect_width, s16 rect_height, u16 mask)
{
    s32 x;
    s32 y;
    MapGrid *config;
    floor_generate_isolated_80284480_DungeonCell *cells;

    config = &gameWork.map;
    cells = ((floor_generate_isolated_80284480_DungeonCell *)D_800EA000);
    for (y = start_y; y < start_y + rect_height; y++) {
        for (x = start_x; x < start_x + rect_width; x++) {
            cells[x + (y << config->shiftX)].field_4 &= mask;
        }
    }
}
