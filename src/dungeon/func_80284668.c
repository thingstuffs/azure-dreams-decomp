#include "dungeon/level/generate.h"

void fill_generation_cell_marks(s16 start_x, s16 y, s16 width, s32 height, u16 fill_value) {
    s16 rows_left;
    s32 span_left;
    s32 width_shifted;
    s32 start_x_shifted;
    s32 x;
    s32 row_y;
    MapGrid *grid_settings;
    s32 cell_index;
    u16 *cell;

    rows_left = height;
    grid_settings = &g_game_work.map;
    if ((height << 16) > 0) {
        width_shifted = width << 16;
        start_x_shifted = start_x << 16;
        do {
            span_left = width_shifted >> 16;
            x = start_x_shifted >> 16;
            if (span_left > 0) {
                row_y = y;
                do {
                    span_left--;
                    cell_index = grid_settings->shiftX;
                    cell_index = row_y << cell_index;
                    cell_index += x;
                    x++;
                    cell = (u16 *)(((u8 *)D_800EA000) + cell_index * 6);
                    cell[2] = fill_value;
                } while (span_left > 0);
            }
            rows_left--;
            y++;
        } while (rows_left > 0);
    }
}

