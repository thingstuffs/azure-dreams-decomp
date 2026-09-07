#include "common.h"

extern u32 D_800814A0[3];
extern void func_800478B8(void *arg0);

void func_8186898C(void *arg0, void *arg1, void *arg2)
{
    u8 *inner = *(u8 **)arg0;
    u16 value;
    u8 count;

    *(u16 *)(inner + 0x14) = *(u16 *)(inner + 0x14) + 1;
    value = *(u16 *)((u8 *)arg2 + 0x1E);
    count = *(u8 *)((u8 *)arg2 + 0xE);
    do { } while (0);
    value += 0x400;
    count -= 4;
    *(u8 *)((u8 *)arg2 + 0xE) = count;
    *(u8 *)((u8 *)arg2 + 0xD) = count;
    *(u8 *)((u8 *)arg2 + 0xC) = count;
    *(u16 *)((u8 *)arg2 + 0x1E) = value;
    *(u16 *)((u8 *)arg2 + 0x1C) = value;
    if (count == 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
    *(u16 *)((u8 *)arg1 + 0xA) -= 8;
    func_800478B8(arg2);
    if (*(u16 *)((u8 *)arg2 + 0x14) & 0x6000) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
