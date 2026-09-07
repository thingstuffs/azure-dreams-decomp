#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern void func_8004B248(void *arg0);
extern s32 D_800814A0;

void func_80050CDC(void *arg0, void *arg1, void *arg2)
{
    s32 count;
    u8 color;
    void *part;

    part = FIELD(arg2, void *, 8);
    FIELD(part, u16, 2) -= 0x40;
    part = FIELD(arg2, void *, 4);
    FIELD(part, u16, 0xC) += 0x20;
    part = FIELD(arg2, void *, 4);
    FIELD(part, u16, 8) -= 0x40;
    part = FIELD(arg2, void *, 4);
    color = FIELD(part, u8, 2) - 0x20;
    FIELD(part, u8, 2) = color;
    FIELD(part, u8, 1) = color;
    FIELD(part, u8, 0) = color;

    count = FIELD(arg0, s32, 8) - 1;
    FIELD(arg0, s32, 8) = count;
    if (count == -1) {
        func_8004B248((u8 *)arg0 + 0x6C);
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
