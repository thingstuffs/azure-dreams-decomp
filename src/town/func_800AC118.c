#include "common.h"

extern s16 D_800D1054[];

/* Returns the matching index in the sentinel-terminated table, or -1. */
s32 func_800A9878(s32 target_value) {
    s32 i = 0;

    while (D_800D1054[i] != -1) {
        if (D_800D1054[i] == target_value) {
            return i;
        }
        i++;
    }
    return -1;
}
