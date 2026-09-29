#include "common.h"
#include "shared/game_work.h"

typedef struct {
    u16 field_0;
    u16 field_2;
    u16 field_4;
} DungeonCell;

extern DungeonCell D_800EA000[];

/* Applies a bitmask to field_4 of each dungeon cell in a rectangle. */
void func_80017480(s16 start_x, s16 start_y, s16 rect_width, s16 rect_height, u16 mask)
{
    s32 x;
    s32 y;
    MapGrid *config;
    DungeonCell *cells;

    config = &gameWork.map;
    cells = D_800EA000;
    for (y = start_y; y < start_y + rect_height; y++) {
        for (x = start_x; x < start_x + rect_width; x++) {
            cells[x + (y << config->shiftX)].field_4 &= mask;
        }
    }
}
