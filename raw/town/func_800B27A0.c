#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern s32 D_8002E5D8[4];
extern s32 D_8002E5E8[3];

void func_800AFF00(void *arg0, void *arg1, void *arg2) {
    s32 *src1 = D_8002E5D8;
    s32 *src2 = D_8002E5E8;
    s32 temp;
    s32 neg = -60;
    register void *dst ASM_REG("$2");

    FIELD(arg1, s32, 0) = D_8002E5D8[0];
    FIELD(arg1, s32, 4) = FIELD(src1, s32, 4);
    FIELD(arg1, s32, 8) = FIELD(src1, s32, 8);
    temp = D_8002E5E8[0];
    FIELD(arg1, s32, 0xC) = FIELD(src1, s32, 0xC);
    FIELD(arg2, s32, 0) = temp;
    FIELD(arg2, s32, 4) = FIELD(src2, s32, 4);
    FIELD(arg2, s32, 8) = FIELD(src2, s32, 8);
    ASM_USE(neg);
    FIELD(arg0, void *, 4) = arg1;
    ASM_UNDEF(dst);
    dst = arg1;
    ASM_KEEP(dst);
    FIELD(arg0, void *, 8) = arg2;
    FIELD(arg0, s32, 0) = 0;
    FIELD(dst, s16, 8) = neg;
    FIELD(FIELD(arg0, void *, 4), s16, 0xA) = neg;
    FIELD(FIELD(arg0, void *, 4), s16, 0xC) = 0x200;
    FIELD(FIELD(arg0, void *, 4), s16, 6) = 0;
    FIELD(FIELD(arg0, void *, 8), s16, 8) = 0x30;
    FIELD(FIELD(arg0, void *, 4), u8, 0xF) = 4;
}
