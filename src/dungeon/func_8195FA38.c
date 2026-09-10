#include "common.h"

extern s32 func_80024C3C();
extern void func_800252AC() __attribute__((noreturn));
extern void func_800252C0() __attribute__((noreturn));

/* Sets tile bounds and dispatches tiles for a seven-by-seven grid. */
s32 func_8195FA38(void *tile_data, s32 draw_arg_1, s32 draw_arg_2) {
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
next_row:
    column = 0;
    do {
        row_arg = (s16)row;
    } while (0);
next_column:
    *(s8 *)((s8 *)tile_data + 8) = column * 0x10;
    *(s8 *)((s8 *)tile_data + 9) = tile_y;
    if (column == last_tile) {
        do {
            *(s8 *)((s8 *)tile_data + 0xA) = edge_size;
        } while (0);
        func_800252AC();
    }
    *(volatile s8 *)((s8 *)tile_data + 0xA) = tile_size;
    if (row == last_tile) {
        *(s8 *)((s8 *)tile_data + 0xB) = edge_size;
        func_800252C0();
    }
    do {
        *(volatile s8 *)((s8 *)tile_data + 0xB) = tile_size;
    } while (0);
    func_80024C3C(tile_data, draw_arg_1, draw_arg_2, (s16)column, row_arg);
    column += 1;
    if (column >= 7) {
        row += 1;
        tile_y += 0x10;
        if (row >= 7) {
            return 0;
        }
        goto next_row;
    }
    goto next_column;
}
