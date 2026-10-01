#include "common.h"

/* Count entries matching both bytes, stopping at a zero value or 64 entries. */
s32 func_80026E70(s32 target_value, s32 prefix_value) {
    s32 index;
    s32 count;
    u8 value;
    u8 *page = (u8 *)0x80010000;

    count = 0;
    for (index = 0; index < 0x40; index++) {
        value = page[0x57D2 + index * 0x13];
        if (value == 0) {
            break;
        }
        if ((value == target_value) && (page[0x57D1 + index * 0x13] == prefix_value)) {
            count++;
        }
    }
    return count;
}
