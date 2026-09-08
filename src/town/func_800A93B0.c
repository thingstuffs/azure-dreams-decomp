#include "common.h"

extern s32 D_800814A0[3];

__asm__(".set func_800A6B68, 0x800A6B68");

void func_800A6B10(void *arg0, s32 arg1, void *arg2) {
    s32 value;
    u16 size;

    value = *(u8 *)((u8 *)arg2 + 0xE);
    value -= 0x10;
    if (value < 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    *(u8 *)((u8 *)arg2 + 0xE) = value;
    *(u8 *)((u8 *)arg2 + 0xD) = value;
    *(u8 *)((u8 *)arg2 + 0xC) = value;
    size = *(u16 *)((u8 *)arg2 + 0x20) + 0x100;
    *(u16 *)((u8 *)arg2 + 0x20) = size;
    *(u16 *)((u8 *)arg2 + 0x1E) = size;
    *(u16 *)((u8 *)arg2 + 0x1C) = size;
}
