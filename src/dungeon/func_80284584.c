#include "common.h"

typedef struct {
    u16 field_0;
    u16 field_2;
    u16 field_4;
} DungeonCell;

extern s16 D_8008333C[12];
extern DungeonCell D_800EA000[];

s32 func_80017584(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s16 *config;
    s32 raw0;
    s32 raw2;
    s32 row;
    s32 height;

    row = arg1;
    if (row <= 0) {
        return -1;
    }
    raw0 = arg0 << 16;
    if ((raw0 >> 16) <= 0) {
        goto ret_err;
    }
    config = D_8008333C;
    if (row + arg3 >= (1 << config[11])) {
        return -1;
    }
    raw2 = arg2 << 16;
    if ((raw0 >> 16) + (raw2 >> 16) >= (1 << config[10])) {
    ret_err:
        return -1;
    }
    height = arg3;
    while (height > 0) {
        s32 remaining;
        s32 x;

        remaining = raw2 >> 16;
        x = raw0 >> 16;
        while (remaining > 0) {
            DungeonCell *cell;

            cell = &D_800EA000[(row << config[10]) + x];
            if (cell->field_4 != 0) {
                return (s16)cell->field_4;
            }
            remaining -= 1;
            x += 1;
        }
        height -= 1;
        row += 1;
    }
    return 0;
}
