#include "common.h"

void func_80039F4C(void *arg0) {
    u32 src = *(u32 *)((u8 *)arg0 + 0x1C);
    u32 dst = *(u32 *)((u8 *)arg0 + 0x80);
    u32 value = *(u8 *)src;
    s32 count;

    src++;
    dst += 0x3C;
    *(u32 *)((u8 *)arg0 + 0x1C) = src;

    count = 15;
    do {
        *(u32 *)(dst + 0x48) = value;
        count--;
        dst -= 4;
    } while (count >= 0);
}
