#include "common.h"

extern u32 func_8001E670(s16 value);
extern u8 D_80017BD0[];
extern u8 D_8001791C[];

s32 func_8001A5D0(void) {
    s32 count;
    u8 *entries;
    u8 *records;

    count = 0;
    if (D_80017BD0[0] == 0) {
        return count;
    }
    do { records = D_8001791C; } while (0);
    entries = D_80017BD0;
    do {
        if (func_8001E670(*(s16 *)(records + (*entries * 0xC) + 4)) != 0) {
            count += 1;
        }
        entries += 1;
    } while (*entries != 0);
    return count;
}
