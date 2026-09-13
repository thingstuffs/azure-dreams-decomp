#include "common.h"

extern u8 D_800157D2[];

/* GCC 2.7.2 does not accept the read/write constraint in ASM_KEEP. */

/* Count entries matching both bytes, stopping at a zero value or 64 entries. */
s32 func_80026E70(s32 target_value, s32 prefix_value) {
    s32 count;
    s32 index;
    u8 *entry;
    u8 value;

    count = 0;
    index = count; ASM_KEEP(index);
    entry = D_800157D2;
loop:
    value = entry[0];
    if (value != 0) {
        if ((value == target_value) && (entry[-1] == prefix_value)) {
            count++;
        }
        do {
            index++;
            entry += 0x13;
        } while (0);
        if (index < 0x40) {
            goto loop;
        }
    }
    return count;
}
