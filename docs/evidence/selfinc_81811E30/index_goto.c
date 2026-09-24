#include "common.h"

/* First value byte of entries spaced 19 bytes apart. */
extern u8 D_800157D2[];

s32 func_80026E30(s32 target_value)
{
    s32 count = 0;
    s32 index = count;
    u8 value;
loop:
    value = D_800157D2[index * 19];
    if (value != 0) {
        if (value == target_value)
            count++;
        index++;
        if (index < 64)
            goto loop;
    }
    return count;
}
