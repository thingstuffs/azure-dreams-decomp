#include "common.h"

extern u8 D_800E0000;

s32 func_800B5128(void) {
    u8 *entry;
    s32 entry_index;

    entry_index = 0;
    entry = &D_800E0000 + 0x3648;
    do {
        if (entry[1] != 0) {
            entry_index++;
            entry += 4;
            continue;
        }
        return (s16)entry_index;
    } while (entry_index < 0x20);
    return -1;
}
