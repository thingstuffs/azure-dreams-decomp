#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 D_800814A0[];

void func_818BDCE0(void *arg0, void *arg1, void *arg2)
{
    void *v1;

    v1 = FIELD(arg0, void *, 0);
    FIELD(v1, u16, 0x14)++;
    FIELD(arg0, u16, 0x10)++;
    FIELD(arg2, u16, 0x1A) += 0x300;

    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);

    if (FIELD(arg0, s16, 0x10) > FIELD(arg0, s16, 0x14)) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
