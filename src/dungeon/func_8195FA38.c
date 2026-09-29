#include "common.h"

extern s32 func_80024C3C();

/* Sets tile bounds and dispatches tiles for a seven-by-seven grid. */
s32 func_80025238(void *tile_data, s32 draw_arg_1, s32 draw_arg_2) {
    s32 column;
    s32 row;
    s32 tile_y;
    s32 row_arg;
    s32 tile_size;
    s32 edge_size;
    s32 last_tile;

    row = 0;
    last_tile = 6;
    edge_size = 0xF;
    tile_size = 0x10;
    tile_y = -0x80;
    do {
        column = 0;
        row_arg = (s16)row;
        do {
            *(s8 *)((s8 *)tile_data + 8) = column * 0x10;
            *(s8 *)((s8 *)tile_data + 9) = tile_y;
            if (column == last_tile) {
                *(s8 *)((s8 *)tile_data + 0xA) = edge_size;
            } else {
                *(s8 *)((s8 *)tile_data + 0xA) = tile_size;
            }
            if (row == last_tile) {
                *(s8 *)((s8 *)tile_data + 0xB) = edge_size;
            } else {
                *(s8 *)((s8 *)tile_data + 0xB) = tile_size;
            }
            func_80024C3C(tile_data, draw_arg_1, draw_arg_2, (s16)column, row_arg);
            column += 1;
        } while (column < 7);
        row += 1;
        tile_y += 0x10;
    } while (row < 7);
    return 0;
}
