#include "common.h"

extern u8 D_800133E6;
extern u8 D_80089260[];

/* Returns the target byte's index in the copied list, or the terminator's index. */
s32 func_800B28A0(void) {
    u8 entries[6];
    u8 *cursor;
    s32 index;
    s32 first_entry;
    s32 target;

    memcpy(entries, D_80089260, sizeof(entries));
    first_entry = entries[0];

    target = (s32)0x80010000;

    target = *(u8 *)(target + 0x33E6);
    index = 0;
    if (first_entry != 0) {
        cursor = entries;
        do {
            if (*cursor == target) {
                return index;
            }
            cursor++;
            index++;
        } while (*cursor != 0);
    }
    return index;
}
