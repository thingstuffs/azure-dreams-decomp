#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_800478B8(void *arg0);
extern s32 func_800A45D8(u16 arg0, u16 arg1, s16 arg2);
extern s16 func_800BCB04(u16 arg0, u16 arg1, s16 arg2);
extern s32 D_800814A0[3];

void func_80D65534(void *arg0, void *arg1, void *arg2)
{
    s16 count;
    s32 old_z;
    s32 scale;
    s32 terrain;
    u16 value;
    u16 x_arg;
    u16 z_arg;

    FIELD(arg1, s32, 8) += FIELD(arg0, s32, 0x34);
    FIELD(arg0, s32, 0x34) += FIELD(arg0, s32, 0x40);

    x_arg = FIELD(arg1, u16, 2);
    z_arg = FIELD(arg1, u16, 0xA);
    old_z = FIELD(arg1, s16, 0xA);
    terrain = func_800BCB04(x_arg,
                            FIELD(arg1, u16, 6),
                            (s16)(z_arg - 4));
    if (terrain - 0x10 < old_z) {
        FIELD(arg0, s32, 0x34) = 0;
        FIELD(arg1, s16, 0xA) =
            func_800BCB04(FIELD(arg1, u16, 2),
                          FIELD(arg1, u16, 6),
                          (s16)(FIELD(arg1, u16, 0xA) - 4)) - 0x11;
        FIELD(arg1, s16, 8) = 0;
        if (FIELD(arg0, s16, 2) == 0) {
            FIELD(arg0, s16, 2) = 1;
        }
    }

    if (FIELD(arg0, s16, 2) == 1) {
        FIELD(arg1, s32, 0) += FIELD(arg0, s32, 0x2C);
        FIELD(arg0, s32, 0x2C) += FIELD(arg0, s32, 0x38);
        if (func_800BCB04(FIELD(arg1, u16, 2),
                          FIELD(arg1, u16, 6),
                          FIELD(arg1, s16, 0xA)) < 0x200 &&
            (s16)func_800A45D8(FIELD(arg1, u16, 2),
                                FIELD(arg1, u16, 6),
                                FIELD(arg1, s16, 0xA)) != 0) {
            FIELD(arg1, s32, 0) -= FIELD(arg0, s32, 0x2C);
            FIELD(arg0, s32, 0x2C) = 0;
            FIELD(arg0, s32, 0x38) = 0;
        }

        FIELD(arg1, s32, 4) += FIELD(arg0, s32, 0x30);
        FIELD(arg0, s32, 0x30) += FIELD(arg0, s32, 0x3C);
        if (func_800BCB04(FIELD(arg1, u16, 2),
                          FIELD(arg1, u16, 6),
                          FIELD(arg1, s16, 0xA)) < 0x200 &&
            (s16)func_800A45D8(FIELD(arg1, u16, 2),
                                FIELD(arg1, u16, 6),
                                FIELD(arg1, s16, 0xA)) != 0) {
            FIELD(arg1, s32, 4) -= FIELD(arg0, s32, 0x30);
            FIELD(arg0, s32, 0x30) = 0;
            FIELD(arg0, s32, 0x3C) = 0;
        }
    }

    scale = (FIELD(arg0, s16, 0xC) << 7) /
            FIELD(arg0, s16, 0xE);
    FIELD(arg2, s8, 0xE) = scale;
    FIELD(arg2, s8, 0xD) = scale;
    FIELD(arg2, s8, 0xC) = scale;

    value = FIELD(arg0, u16, 0x18) + 1;
    FIELD(arg0, u16, 0x18) = value;
    if ((s16)value == 3) {
        func_800478B8(arg2);
        FIELD(arg0, u16, 0x18) = 0;
    }

    value = FIELD(arg2, u16, 0x1C) + 0xC8;
    FIELD(arg2, u16, 0x1C) = value;
    if (value > 0x1000) {
        FIELD(arg2, u16, 0x1C) = 0x1000;
    }

    value = FIELD(arg2, u16, 0x1E) + 0xC8;
    FIELD(arg2, u16, 0x1E) = value;
    if (value > 0x1000) {
        FIELD(arg2, u16, 0x1E) = 0x1000;
    }

    count = FIELD(arg0, u16, 0xC) - 1;
    FIELD(arg0, u16, 0xC) = count;
    if ((count << 16) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
