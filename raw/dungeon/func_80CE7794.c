#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_800478B8(void *arg0);
extern s32 func_800A45D8(u16 arg0, u16 arg1, s16 arg2);
extern s16 func_800BCB04(u16 arg0, u16 arg1, s16 arg2);
extern s32 D_800814A0;

void func_80170F94(void *arg0, void *arg1, void *arg2)
{
    s32 height;
    u16 value;

    FIELD(arg1, s32, 0x0) += FIELD(arg0, s32, 0x40);
    FIELD(arg0, s32, 0x40) += FIELD(arg0, s32, 0x4C);
    if (func_800A45D8(FIELD(arg1, u16, 0x2),
                      FIELD(arg1, u16, 0x6),
                      FIELD(arg1, s16, 0xA)) << 16) {
        FIELD(arg1, s32, 0x0) -= FIELD(arg0, s32, 0x40);
        FIELD(arg0, s32, 0x40) = 0;
        FIELD(arg0, s32, 0x4C) = 0;
    }

    FIELD(arg1, s32, 0x4) += FIELD(arg0, s32, 0x44);
    FIELD(arg0, s32, 0x44) += FIELD(arg0, s32, 0x50);
    if (func_800A45D8(FIELD(arg1, u16, 0x2),
                      FIELD(arg1, u16, 0x6),
                      FIELD(arg1, s16, 0xA)) << 16) {
        FIELD(arg1, s32, 0x4) -= FIELD(arg0, s32, 0x44);
        FIELD(arg0, s32, 0x44) = 0;
        FIELD(arg0, s32, 0x50) = 0;
    }

    FIELD(arg1, s32, 0x8) += FIELD(arg0, s32, 0x48);
    FIELD(arg0, s32, 0x48) += FIELD(arg0, s32, 0x54);
    height = FIELD(arg1, s16, 0xA);
    if (func_800BCB04(FIELD(arg1, u16, 0x2),
                      FIELD(arg1, u16, 0x6),
                      (s16)(FIELD(arg1, u16, 0xA) - 4)) - 0x10 < height) {
        FIELD(arg0, s32, 0x48) = 0;
        FIELD(arg1, s16, 0xA) = func_800BCB04(
            FIELD(arg1, u16, 0x2), FIELD(arg1, u16, 0x6),
            (s16)(FIELD(arg1, u16, 0xA) - 4)) - 0x11;
        FIELD(arg1, s16, 0x8) = 0;
        if (FIELD(arg0, s16, 0xE) == 0) {
            FIELD(arg0, s16, 0xE) = 1;
            FIELD(arg0, s16, 0x18) = 0;
        }
    }

    value = FIELD(arg0, u16, 0x1A) + 1;
    FIELD(arg0, u16, 0x1A) = value;
    if ((value & 3) == 0) {
        func_800478B8(arg2);
    }

    value = FIELD(arg2, u16, 0x1C) + 100;
    FIELD(arg2, u16, 0x1C) = value;
    if (value > 0x1000) {
        FIELD(arg2, u16, 0x1C) = 0x1000;
    }

    value = FIELD(arg2, u16, 0x1E) + 100;
    FIELD(arg2, u16, 0x1E) = value;
    if (value > 0x1000) {
        FIELD(arg2, u16, 0x1E) = 0x1000;
    }

    value = FIELD(arg0, u16, 0x18) - 1;
    FIELD(arg0, u16, 0x18) = value;
    if ((s16)value <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
