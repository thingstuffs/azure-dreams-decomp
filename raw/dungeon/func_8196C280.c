#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

typedef struct PositionRef {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} PositionRef;

extern s32 func_80024AF8();
extern s32 func_800A45D8();
extern s16 func_800BCB04();
extern s16 D_800269B4;
extern s32 D_800814A0;
extern PositionRef D_80083780;

void func_8196C280(void *arg0, void *arg1, void *arg2) {
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    register u16 raw_x ASM_REG("$3");
    u16 raw_y;
    register u16 var_a0 ASM_REG("$4");
    register u16 var_v1 ASM_REG("$3");

    FIELD(arg1, s32, 0) += FIELD(arg0, s32, 0x8C);
    FIELD(arg0, s32, 0x8C) += FIELD(arg0, s32, 0x98);
    {
        u16 call_x;
        u16 call_y;
        s32 call_z;

        call_x = FIELD(arg1, u16, 2);
        call_y = FIELD(arg1, u16, 6);
        call_z = FIELD(arg1, s16, 0xA);
        D_800269B4 = 1;
        if ((func_800A45D8(call_x, call_y, call_z) << 0x10) != 0) {
            FIELD(arg1, s32, 0) -= FIELD(arg0, s32, 0x8C);
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg0, s32, 0x98) = 0;
        }
    }
    FIELD(arg1, s32, 4) += FIELD(arg0, s32, 0x90);
    FIELD(arg0, s32, 0x90) += FIELD(arg0, s32, 0x9C);
    if ((func_800A45D8(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6), FIELD(arg1, s16, 0xA)) << 0x10) != 0) {
        FIELD(arg1, s32, 4) -= FIELD(arg0, s32, 0x90);
        FIELD(arg0, s32, 0x90) = 0;
        FIELD(arg0, s32, 0x9C) = 0;
    }
    FIELD(arg1, s32, 8) += FIELD(arg0, s32, 0x94);
    FIELD(arg0, s32, 0x94) += FIELD(arg0, s32, 0xA0);
    {
        s32 temp_s0;

        temp_s0 = FIELD(arg1, s16, 0xA);
        if ((func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6), (s16)(FIELD(arg1, u16, 0xA) - 4)) - 0x10) < temp_s0) {
            FIELD(arg0, s32, 0x94) = 0;
            FIELD(arg0, s32, 0x90) = 0;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg1, s16, 0xA) = func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6), (s16)(FIELD(arg1, u16, 0xA) - 4)) - 0x11;
            FIELD(arg1, u16, 8) = 0;
            FIELD(arg0, u16, 0x2C) = 0;
        }
    }
    temp_v0 = FIELD(arg0, u16, 0x50);
    FIELD(arg0, u16, 0x50) = temp_v0 + 1;
    if ((s16)temp_v0 >= 3) {
        raw_x = FIELD(arg2, u16, 0x1C);
        raw_y = FIELD(arg2, u16, 0x1E);
        temp_v0_2 = raw_x - 0x100;
        ASM_KEEP(raw_x);
        var_v1 = temp_v0_2;
        if ((s16)temp_v0_2 < 0) {
            var_v1 = 0;
        }
        temp_v0_3 = raw_y - 0x100;
        var_a0 = temp_v0_3;
        if ((s16)temp_v0_3 < 0) {
            var_a0 = 0;
        }
        if (((var_a0 << 0x10) == 0) || ((var_v1 << 0x10) == 0)) {
            FIELD(arg0, u16, 0x2C) = 0;
        }
        FIELD(arg2, u16, 0x1C) = var_v1;
        FIELD(arg2, u16, 0x1E) = var_a0;
        ASM_KEEP(var_v1);
        ASM_KEEP(var_a0);
    }
    func_80024AF8(arg0, arg1, arg2,
        (s16)(FIELD(arg1, u16, 2) - D_80083780.x),
        (s16)(FIELD(arg1, u16, 6) - D_80083780.y),
        (s16)(FIELD(arg1, u16, 0xA) - D_80083780.z));
    temp_v0_4 = FIELD(arg0, u16, 0x2C) - 1;
    FIELD(arg0, u16, 0x2C) = temp_v0_4;
    if ((temp_v0_4 << 0x10) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
