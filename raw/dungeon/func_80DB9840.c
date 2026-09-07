#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_800478B8(void *arg0);
extern s32 func_800A45D8(u16 arg0, u16 arg1, s16 arg2);
extern s16 func_800BCB04(u16 arg0, u16 arg1, s16 arg2);
extern s32 D_800814A0;

void func_80171040(void *arg0, void *arg1, void *arg2)
{
    s32 height;
    u16 count;

    FIELD(arg1, s32, 0) += FIELD(arg0, s32, 0xA4);
    FIELD(arg0, s32, 0xA4) = (FIELD(arg0, s32, 0xA4) * 2) / 3;
    if ((s16)func_800A45D8(FIELD(arg1, u16, 2),
                           FIELD(arg1, u16, 6),
                           FIELD(arg1, s16, 0xA)) != 0) {
        FIELD(arg1, s32, 0) -= FIELD(arg0, s32, 0xA4);
        FIELD(arg0, s32, 0xA4) = 0;
    }

    FIELD(arg1, s32, 4) += FIELD(arg0, s32, 0xA8);
    FIELD(arg0, s32, 0xA8) = (FIELD(arg0, s32, 0xA8) * 2) / 3;
    if ((s16)func_800A45D8(FIELD(arg1, u16, 2),
                           FIELD(arg1, u16, 6),
                           FIELD(arg1, s16, 0xA)) != 0) {
        FIELD(arg1, s32, 4) -= FIELD(arg0, s32, 0xA8);
        FIELD(arg0, s32, 0xA8) = 0;
    }

    FIELD(arg1, s32, 8) += FIELD(arg0, s32, 0xAC);
    FIELD(arg0, s32, 0xAC) += FIELD(arg0, s32, 0xB0);

    height = FIELD(arg1, s16, 0xA);
    if (func_800BCB04(FIELD(arg1, u16, 2),
                      FIELD(arg1, u16, 6),
                      (s16)(FIELD(arg1, volatile u16, 0xA) - 4)) - 0x10 < height) {
        FIELD(arg0, s32, 0xAC) = 0;
        FIELD(arg1, s16, 0xA) = func_800BCB04(
            FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
            (s16)(FIELD(arg1, u16, 0xA) - 4)) - 0x11;
        FIELD(arg1, s16, 8) = 0;
        if (FIELD(arg0, u16, 0x98) == 0) {
            FIELD(arg0, u16, 0x98) = 1;
            FIELD(arg0, u16, 0x96) = 0;
        }
    }

    FIELD(arg0, u16, 0x9E)++;
    func_800478B8(arg2);
    count = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = count;
    if ((s16)count <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
