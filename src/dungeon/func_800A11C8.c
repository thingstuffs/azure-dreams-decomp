#include "common.h"

s16 func_800A6928(s32 arg0, s32 arg1) {
    u8 *ptr;
    u32 page;
    s32 count;
    s32 i;
    s32 value;

    value = (arg0 << 8) | (arg1 & 0xFF);
    count = 0;
    i = 0x13;
    value &= 0xFFFF;
    page = 0x80010000;
    ptr = (u8 *)(page | 0x4C);
    do {
        if (*(u16 *)*(u32 *)(ptr + 0x29C) == value) {
            count++;
        }
        i--;
        ptr -= 4;
    } while (i >= 0);
    return count;
}
