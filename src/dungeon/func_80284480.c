#include "common.h"
#include "shared/game_work.h"

typedef struct {
    u16 field_0;
    u16 field_2;
    u16 field_4;
} DungeonCell;

extern DungeonCell D_800EA000[];

/* Applies a bitmask to field_4 of each dungeon cell in a rectangle. */
void func_80017480(s32 start_x, s32 start_y, s32 rect_width, s32 rect_height, u16 mask)
{
    s32 y;
    s32 height;
    s32 y_limit;
    s32 y_end;
    s32 x;
    s32 x_end;
    s32 width;
    MapGrid *config;
    DungeonCell *cells;

    y = (s16)start_y;
    config = &gameWork.map;
    cells = D_800EA000;
    height = (s16)rect_height;
    y_limit = y + height;
    if (y < y_limit) {
        start_x = (s32)((u32)start_x << 16);
        rect_width = (s32)((u32)rect_width << 16);
        width = rect_width >> 16;
        y_end = y_limit;
        do {
            x = start_x >> 16;
            ASM_KEEP_NV(rect_width);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            if (x < x + width) {
                x_end = x + (rect_width >> 16);
                do {
                    cells[x + (y << config->shiftX)].field_4 &= mask;
                    x++;
                } while (x < x_end);
            }
            y++;
        } while (y < y_end);
    }
}
