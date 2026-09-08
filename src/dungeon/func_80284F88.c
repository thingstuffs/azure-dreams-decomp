#include "common.h"

typedef struct {
    u16 x;
    u16 y;
    s16 width;
    s16 height;
    u8 pad[12];
} DungeonRect;

typedef struct {
    u16 x;
    u16 y;
    u16 flags;
} DungeonCell;

typedef struct {
    DungeonCell *cells;
    u8 pad[16];
    s16 shift;
} DungeonState;

extern DungeonState D_8008333C;
extern DungeonRect D_800E2970[];
extern s16 func_800BCB04(s32, s32, s32);

/* Finds the eligible tile with the highest sampled value below 0x200 in a rectangle. */
s32 func_80017F88(s16 rect_index, s16 *out_x, s16 *out_y, s16 check_flags)
{
    s16 best_value;
    s16 rows_left;
    s16 cols_left;
    s16 tile_y;
    s16 tile_x;
    s16 tile_value;
    s32 row_index;
    u16 flags;
    s32 tile_center_y;
    DungeonCell *cells;
    DungeonState *state;

    best_value = -0x200;
    rows_left = D_800E2970[rect_index].height;
    tile_y = D_800E2970[rect_index].y;
    state = &D_8008333C;
    cells = state->cells;
    if (rows_left > 0) {
        do {
            cols_left = D_800E2970[rect_index].width;
            tile_x = D_800E2970[rect_index].x;
            if (cols_left > 0) {
                row_index = (s16)tile_y;
                tile_center_y = (row_index << 6) + 0x20;
                do {
                    flags = cells[(s16)tile_x
                        + (row_index << state->shift)].flags;
                    if (!(flags & 0x8400)
                        && ((check_flags == 0)
                        || ((flags & 0x300) == 0x200))) {
                        tile_value = func_800BCB04(
                            (((s16)tile_x << 6) + 0x20) & 0xFFE0,
                            tile_center_y & 0xFFFF,
                            -0x400);
                        if (tile_value < 0x200) {
                            if (best_value < tile_value) {
                                *out_x = tile_x;
                                best_value = tile_value;
                                *out_y = tile_y;
                            }
                        }
                    }
                    cols_left--;
                    tile_x++;
                } while ((cols_left << 16) > 0);
            }
            rows_left--;
            tile_y++;
        } while ((rows_left << 16) > 0);
    }
    if (best_value == -0x200) {
        best_value = 0x200;
    }
    return best_value;
}

