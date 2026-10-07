#include "common.h"

typedef s32 M2C_UNK;

extern s32 func_8001839C(s32);
extern s32 D_8001B3F2[3];
extern s32 D_8001B71A[3];

/* Returns special data for IDs 11 and 28 when their value is below -47. */
M2C_UNK *func_80016D98(s32 id) {
    s32 *special_data;

    special_data = 0;
    if (func_8001839C(id) < -0x2F) {
        if (id == 0xB) {
            special_data = &D_8001B3F2[0];
        } else if (id == 0x1C) {
            special_data = &D_8001B71A[0];
        }
    }
    return special_data;
}
