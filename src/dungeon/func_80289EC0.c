#include "dungeon/level/generate.h"

void adjust_random_parity_tile_heights(floor_generate_isolated_80289EC0_Rect *rect, s32 rng_input_1)
{
    MapGrid *dungeon = &g_game_work.map;
    s32 parity;
    s32 x_end;
    s32 y_end;
    s32 x;
    s32 y;
    s32 initial_y;
    s32 initial_x;
    s32 initial_width;
    s32 initial_height;
    s32 y_parity;
    floor_generate_isolated_80289EC0_Tile *tile;

    parity = generate_random_value() & 1;
    initial_y = rect->y;
    initial_x = rect->x;
    initial_width = rect->width;
    initial_height = rect->height;
    x_end = initial_x + initial_width;
    y_end = initial_y + initial_height;
    y = initial_y;

    if (y < y_end) {
        do {
            x = rect->x;
            if (x < x_end) {
                y_parity = y & 1;
                do {
                    if (((x & 1) == parity) && (y_parity == parity)) {
                        tile = (floor_generate_isolated_80289EC0_Tile *) (((u8 *)D_800EA000) +
                            (((y << dungeon->shiftX) + x) * 6));
                        tile->height = (tile->flags >> 1) + 0x63;
                        tile->y -= 0x60;
                        tile->flags |= 0x8000;
                    }
                    x++;
                } while (x < x_end);
            }
            y++;
        } while (y < y_end);
    }
}
