#include "common.h"

extern s16 D_800269B4;
extern s32 D_800814A0;

void func_8196AB74(void *arg0)
{
    u8 *ptr = arg0;
    u16 value;

    value = *(u16 *)(ptr + 50);
    D_800269B4 = 1;
    value -= 8;
    *(u16 *)(ptr + 50) = value;
    if ((value << 16) <= 0) {
        *(u16 *)(ptr - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
