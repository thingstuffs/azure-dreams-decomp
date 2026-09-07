#include "common.h"

extern void func_800478B8(void *arg0);
extern s32 D_800814A0[3];

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

void func_80170D44(void *arg0, void *arg1, void *arg2)
{
    s16 count;
    s32 shade;
    u16 pos;
    void *src;

    src = FIELD(arg0, void *, 0xAC);
    FIELD(arg1, u16, 2) = FIELD(src, u16, 2);
    FIELD(arg1, u16, 6) = FIELD(src, u16, 6);
    FIELD(arg1, u16, 0xA) = FIELD(src, u16, 0xA);

    pos = FIELD(arg2, u16, 0x1E) + 0x320;
    FIELD(arg2, u16, 0x1E) = pos;
    FIELD(arg2, u16, 0x1C) = pos;

    count = FIELD(arg0, u16, 0x96) - 1;
    shade = (s32)(count * 0x50) / (s16)FIELD(arg0, s16, 0xA8);
    FIELD(arg0, u16, 0x96) = (u16)count;
    FIELD(arg2, s8, 0xE) = (s8)shade;
    FIELD(arg2, s8, 0xD) = (s8)shade;
    FIELD(arg2, s8, 0xC) = (s8)shade;
    func_800478B8(arg2);

    if (FIELD(arg0, s16, 0x96) <= 0) {
        FIELD(arg0, u16, -2) = (u16)(FIELD(arg0, u16, -2) | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
    }
}
