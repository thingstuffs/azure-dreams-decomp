#include "common.h"

/* Return the first of three entries matching the target's group, or -1. */
s32 func_800A57B4(void *entry, s16 target) {
    s32 index;

    index = 0;
    do {
        u8 value = *((u8 *)entry + 8);

        if (value != 0 && (target - 1) / 3 == (value - 1) / 3) {
            return (s16)index;
        }
        index++;
        entry = (u8 *)entry + 3;
    } while (index < 3);
    return -1;
}
