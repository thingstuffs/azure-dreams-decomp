#include "common.h"

#define FIELD(base, type, off) (*(type *)((u8 *)(base) + (off)))

extern s32 func_800478B8();
extern s32 func_800A45D8();
extern s16 func_800BCB04();
extern s16 D_800269B4;
extern s32 D_800814A0;

void func_8196B074(void *arg0, void *arg1, s32 arg2) {
    s32 temp_s0;
    u16 value;

    value = FIELD(arg0, u16, 0x2C);
    D_800269B4 = 1;
    FIELD(arg0, u16, 0x2C) = value - 1;
    func_800478B8(arg2);
    FIELD(arg1, s32, 0) += FIELD(arg0, s32, 0x8C);
    FIELD(arg0, s32, 0x8C) += FIELD(arg0, s32, 0x98);
    if ((func_800A45D8(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6), FIELD(arg1, s16, 0xA)) << 16) != 0) {
        FIELD(arg1, s32, 0) -= FIELD(arg0, s32, 0x8C);
        FIELD(arg0, s32, 0x8C) = 0;
        FIELD(arg0, s32, 0x98) = 0;
    }
    FIELD(arg1, s32, 4) += FIELD(arg0, s32, 0x90);
    FIELD(arg0, s32, 0x90) += FIELD(arg0, s32, 0x9C);
    if ((func_800A45D8(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6), FIELD(arg1, s16, 0xA)) << 16) != 0) {
        FIELD(arg1, s32, 4) -= FIELD(arg0, s32, 0x90);
        FIELD(arg0, s32, 0x90) = 0;
        FIELD(arg0, s32, 0x9C) = 0;
    }
    FIELD(arg1, s32, 8) += FIELD(arg0, s32, 0x94);
    FIELD(arg0, s32, 0x94) += FIELD(arg0, s32, 0xA0);
    temp_s0 = FIELD(arg1, s16, 0xA);
    if ((func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                       (s16)((u16)FIELD(arg1, volatile s16, 0xA) - 4)) - 0x10) < temp_s0) {
        FIELD(arg0, s32, 0x94) = 0;
        FIELD(arg0, s32, 0x90) = 0;
        FIELD(arg0, s32, 0x8C) = 0;
        FIELD(arg1, s16, 0xA) = func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                                               (s16)((u16)FIELD(arg1, s16, 0xA) - 4)) - 0x11;
        FIELD(arg1, s16, 8) = 0;
        FIELD(arg0, u16, 0x2C) = 0;
    }
    if ((s16)FIELD(arg0, u16, 0x2C) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
