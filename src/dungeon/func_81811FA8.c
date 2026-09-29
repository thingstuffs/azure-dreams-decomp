#include "common.h"
s32 func_80026FA8(s32 match_byte_2, s32 match_byte_1, s32 start_index)
{
    s32 i;
    for (i = start_index; i < 0x40; i++) {
        u8 *e = (u8 *)0x80010000 + i * 19;
        if (e[0x57D2] == match_byte_2 && e[0x57D1] == match_byte_1) {
            return i;
        }
    }
    return -1;
}
