#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef long long s64_local;

extern s32 func_800242DC() __attribute__((noreturn));
extern s32 func_8003DB94();
extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 rand();

extern u8 D_800240B8[];
extern u8 D_80045340[];
extern u8 D_800DEC70[];

s32 func_818B6954(s32 arg0, void *arg1, s32 arg2) {
    s16 temp_s0;
    register s32 temp_a0 ASM_REG("$4");
    s32 temp_a1;
    s64_local temp_copy01;
    s32 temp_copy4;
    s32 temp_copy5;
    register s32 ret ASM_REG("$2");
    register s32 scale ASM_REG("$3");
    s32 temp_v0_3;
    s32 temp_v1;
    s32 var_s0;
    s32 var_v0;
    void *temp_s0_2;
    void *temp_s2;
    register void *temp_v0 ASM_REG("$17");
    void *temp_v0_2;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        FIELD(temp_v0, void *, 0x10) = D_800240B8;
        temp_v0_2 = (u8 *)temp_v0 + 0x20;
        FIELD(temp_v0, s32, 0x20) = arg0;
        FIELD(temp_v0_2, s16, 4) = 0;
        FIELD(temp_v0_2, s16, 6) = 0;
        temp_s0_2 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_s0_2, s32, 0xC) = arg2;
        FIELD(temp_s0_2, s16, 0x12) = 0x7DCF;
        FIELD(temp_s0_2, u16, 0x14) |= 0xC;
        FIELD(temp_s0_2, u16, 0x10) |= 0x20;
        FIELD(temp_s0_2, u16, 0x14) |= 0x100;
        func_8003DB94(temp_s0_2, D_800DEC70, 0);
        var_v0 = rand();
        temp_v1 = var_v0;
        if (temp_v1 < 0) {
            var_v0 = temp_v1 + 0xFFF;
        }
        ASM_KEEP(temp_v1);
        FIELD(temp_s0_2, s16, 0x1A) = temp_v1 - ((var_v0 >> 0xC) << 0xC);
        FIELD(temp_s0_2, s16, 0x1E) = 0xC00;
        FIELD(temp_s0_2, s16, 0x1C) = 0xC00;
        func_8004491C(temp_v0, D_80045340);
        temp_s2 = FIELD(temp_v0, void *, 8);
        temp_copy01 = FIELD(arg1, s64_local, 0);
        temp_a0 = FIELD(arg1, s32, 8);
        temp_a1 = FIELD(arg1, s32, 0xC);
        FIELD(temp_s2, s64_local, 0) = temp_copy01;
        FIELD(temp_s2, s32, 8) = temp_a0;
        FIELD(temp_s2, s32, 0xC) = temp_a1;
        temp_copy4 = FIELD(arg1, s32, 0x10);
        temp_copy5 = FIELD(arg1, s32, 0x14);
        FIELD(temp_s2, s32, 0x10) = temp_copy4;
        FIELD(temp_s2, s32, 0x14) = temp_copy5;
        temp_v0_3 = rand(temp_a0, temp_a1);
        var_s0 = temp_v0_3;
        if (temp_v0_3 < 0) {
            var_s0 = temp_v0_3 + 0xFFF;
        }
        temp_s0 = temp_v0_3 - ((var_s0 >> 0xC) << 0xC);
        FIELD(temp_s2, s32, 0) += (func_80064584(temp_s0) >> 4) * 0x1200;
        temp_a0 = func_800644B8(temp_s0) >> 4;
        ret = (s32)temp_v0;
        ASM_KEEP(ret);
        scale = temp_a0 * 0x1200;
        temp_a0 = FIELD(temp_s2, s32, 4) + scale;
        FIELD(temp_s2, s32, 4) = temp_a0;
        func_800242DC(temp_a0);
    }
    return 0;
}
