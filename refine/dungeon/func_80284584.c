#include "common.h"

typedef struct {
    u16 field_0;
    u16 field_2;
    u16 field_4;
} DungeonCell;

extern s16 D_8008333C[12];
extern DungeonCell D_800EA000[];

/* Returns the first nonzero field_4 in a rectangle, zero if none, or -1 for invalid bounds. */
s32 func_80017584(s16 start_x, s16 start_y, s16 width, s16 height) {
    s16 *config;
    s32 shifted_x;
    s32 shifted_width;
    s32 row;
    s32 rows_left;

    row = start_y;
    if (row <= 0) {
        return -1;
    }
    shifted_x = start_x << 16;
    if ((shifted_x >> 16) <= 0) {
        goto ret_err;
    }
    config = D_8008333C;
    if (row + height >= (1 << config[11])) {
        return -1;
    }
    shifted_width = width << 16;
    if ((shifted_x >> 16) + (shifted_width >> 16) >= (1 << config[10])) {
    ret_err:
        return -1;
    }
    rows_left = height;
    while (rows_left > 0) {
        s32 cols_left;
        s32 x;

        cols_left = shifted_width >> 16;
        x = shifted_x >> 16;
        while (cols_left > 0) {
            DungeonCell *cell;

            cell = &D_800EA000[(row << config[10]) + x];
            if (cell->field_4 != 0) {
                return (s16)cell->field_4;
            }
            cols_left -= 1;
            x += 1;
        }
        rows_left -= 1;
        row += 1;
    }
    return 0;
}
