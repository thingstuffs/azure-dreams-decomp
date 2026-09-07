#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 D_800814A0;

void func_8002744C(void *arg0, void *arg1, void *arg2) {
    s16 timer;
    u8 intensity;

    FIELD(arg1, s32, 0x00) += FIELD(arg0, s32, 0x0C);
    FIELD(arg1, s32, 0x04) += FIELD(arg0, s32, 0x10);
    FIELD(arg1, s32, 0x08) += FIELD(arg0, s32, 0x14);

    FIELD(arg1, s32, 0x0C) += FIELD(arg0, s32, 0x0C) >> 1;
    FIELD(arg1, s32, 0x10) += FIELD(arg0, s32, 0x10) >> 1;
    FIELD(arg1, s32, 0x14) += FIELD(arg0, s32, 0x14) >> 1;

    intensity = FIELD(arg2, u8, 0x0C);
    intensity -= intensity / FIELD(arg0, s16, 0x66);
    FIELD(arg2, u8, 0x0C) = intensity;
    FIELD(arg2, u8, 0x0D) = intensity;
    FIELD(arg2, u8, 0x0E) = intensity;

    timer = (u16)FIELD(arg0, s16, 0x66) - 1;
    FIELD(arg0, s16, 0x66) = timer;
    if ((timer << 16) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
