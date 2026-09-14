#include "common.h"

extern s32 func_8004A658(s32, s32);

s32 func_800A7A38(u8 *item)
{
    s32 result;

    if (item[1] == 0x12) {
        u32 value = 0x80070000;

        ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        value -= 0x1DC0;
        result = value;
    } else {
        result = func_8004A658(item[1], item[0]);
    }
    return result;
}
