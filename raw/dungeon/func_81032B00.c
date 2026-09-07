#include "common.h"

#define FIELD(base, type, off) (*(type *)((u8 *)(base) + (off)))

extern s32 func_800478B8();
extern s32 func_800A45D8();
extern s16 func_800BCB04();
extern s32 D_800814A0;

void func_80174300(void *arg0, void *arg1, s32 arg2) {
    s32 temp_s0;

    FIELD(arg0, u16, 0x1E) = FIELD(arg0, u16, 0x1E) - 1;
    func_800478B8(arg2);
    FIELD(arg1, s32, 0) += FIELD(arg0, s32, 0x50);
    FIELD(arg0, s32, 0x50) += FIELD(arg0, s32, 0x5C);
    if ((func_800A45D8(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6), FIELD(arg1, s16, 0xA)) << 16) != 0) {
        FIELD(arg1, s32, 0) -= FIELD(arg0, s32, 0x50);
        FIELD(arg0, s32, 0x50) = 0;
        FIELD(arg0, s32, 0x5C) = 0;
    }
    FIELD(arg1, s32, 4) += FIELD(arg0, s32, 0x54);
    FIELD(arg0, s32, 0x54) += FIELD(arg0, s32, 0x60);
    if ((func_800A45D8(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6), FIELD(arg1, s16, 0xA)) << 16) != 0) {
        FIELD(arg1, s32, 4) -= FIELD(arg0, s32, 0x54);
        FIELD(arg0, s32, 0x54) = 0;
        FIELD(arg0, s32, 0x60) = 0;
    }
    FIELD(arg1, s32, 8) += FIELD(arg0, s32, 0x58);
    FIELD(arg0, s32, 0x58) += FIELD(arg0, s32, 0x64);
    temp_s0 = FIELD(arg1, s16, 0xA);
    if ((func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                       (s16)((u16)FIELD(arg1, volatile s16, 0xA) - 4)) - 0x10) < temp_s0) {
        FIELD(arg0, s32, 0x58) = 0;
        FIELD(arg0, s32, 0x54) = 0;
        FIELD(arg0, s32, 0x50) = 0;
        FIELD(arg1, s16, 0xA) = func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                                               (s16)((u16)FIELD(arg1, s16, 0xA) - 4)) - 0x11;
        FIELD(arg1, s16, 8) = 0;
        FIELD(arg0, u16, 0x1E) = 0;
    }
    if ((s16)FIELD(arg0, u16, 0x1E) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
