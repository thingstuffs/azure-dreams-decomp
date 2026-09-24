#include "common.h"
extern u8 D_800157D2[];
s32 func_80026E30(s32 target_value)
{
    s32 count = 0;
    s32 index = count;
    u8 value;
    do {
        value = D_800157D2[index * 19];
        if (value == 0)
            break;
        if (value == target_value)
            count++;
        index++;
    } while (index < 64);
    return count;
}
