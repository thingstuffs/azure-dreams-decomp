#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_800478B8(void *arg0);
extern s32 func_800A45D8(u16 arg0, u16 arg1, s16 arg2);
extern s16 func_800BCB04(u16 arg0, u16 arg1, s16 arg2);
extern s32 D_800814A0;

void func_80170D58(void *arg0, void *arg1, void *arg2)
{
    s32 old_z;
    u16 value;

    FIELD(arg1, s32, 0) += FIELD(arg0, s32, 0x54);
    FIELD(arg0, s32, 0x54) += FIELD(arg0, s32, 0x60);
    if ((func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                       FIELD(arg1, s16, 0xA)) < 0x200) &&
        ((s16)func_800A45D8(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                            FIELD(arg1, s16, 0xA)) != 0)) {
        FIELD(arg1, s32, 0) -= FIELD(arg0, s32, 0x54);
        FIELD(arg0, s32, 0x54) = 0;
        FIELD(arg0, s32, 0x60) = 0;
    }

    FIELD(arg1, s32, 4) += FIELD(arg0, s32, 0x58);
    FIELD(arg0, s32, 0x58) += FIELD(arg0, s32, 0x64);
    if ((func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                       FIELD(arg1, s16, 0xA)) < 0x200) &&
        ((s16)func_800A45D8(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                            FIELD(arg1, s16, 0xA)) != 0)) {
        FIELD(arg1, s32, 4) -= FIELD(arg0, s32, 0x58);
        FIELD(arg0, s32, 0x58) = 0;
        FIELD(arg0, s32, 0x64) = 0;
    }

    FIELD(arg1, s32, 8) += FIELD(arg0, s32, 0x5C);
    FIELD(arg0, s32, 0x5C) += FIELD(arg0, s32, 0x68);
    old_z = FIELD(arg1, s16, 0xA);
    if (func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                      (s16)(FIELD(arg1, u16, 0xA) - 4)) - 0x10 < old_z) {
        FIELD(arg0, s32, 0x5C) = 0;
        FIELD(arg1, s16, 0xA) =
            func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                          (s16)(FIELD(arg1, u16, 0xA) - 4)) - 0x11;
        FIELD(arg1, s16, 8) = 0;
        if (FIELD(arg0, s16, 0x1A) == 0) {
            FIELD(arg0, s16, 0x1A) = 1;
            FIELD(arg0, s16, 0x26) = 0;
        }
    }

    value = FIELD(arg0, u16, 0x28) + 1;
    FIELD(arg0, u16, 0x28) = value;
    if ((value & 3) == 0) {
        func_800478B8(arg2);
    }

    value = FIELD(arg2, u16, 0x1C) + 0x64;
    FIELD(arg2, u16, 0x1C) = value;
    if (value > 0x1000) {
        FIELD(arg2, u16, 0x1C) = 0x1000;
    }

    value = FIELD(arg2, u16, 0x1E) + 0x64;
    FIELD(arg2, u16, 0x1E) = value;
    if (value > 0x1000) {
        FIELD(arg2, u16, 0x1E) = 0x1000;
    }

    value = FIELD(arg0, u16, 0x26) - 1;
    FIELD(arg0, u16, 0x26) = value;
    if ((s16)value <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
