#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s8 D_80083160[];
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
s32 func_80044724();
M2C_UNK func_800D112C();
M2C_UNK func_800D1338();
M2C_UNK func_800D1618();

void func_800D13B8(void) {
    s8 *temp_s0_1;
    register s8 *temp_s1 ASM_REG("$17");
    s16 temp_s2;
    s16 temp_s3;
    s32 temp_s0;
    s32 temp_s4;
    register s32 temp_s5 ASM_REG("$21");
    s32 temp_s6;
    s32 temp_a0;
    s32 temp_a1;
    register s32 temp_a0_2 ASM_REG("$4");
    register s32 temp_a1_2 ASM_REG("$5");
    register s32 temp_a2_2 ASM_REG("$6");
    s32 temp_wide1;
    s32 temp_wide2;
    s32 temp_v1;
    u16 *temp_s0_2;
    u16 *temp_s1_2;

    temp_s0_1 = D_80083160;
    temp_s1 = temp_s0_1 + 0x18;
    if (func_80044724() != 0) {
        temp_s0 = 2 - ((s32) (M2C_FIELD(temp_s0_1, s16 *, 0xC8) + 0x100) >> 9);
        func_800D1338();
        temp_s2 = (u16) M2C_FIELD(temp_s1, u16 *, 0xA4) >> 6;
        temp_s3 = (u16) M2C_FIELD(temp_s1, u16 *, 0xA6) >> 6;
        temp_s4 = temp_s0 & 7;
        if (temp_s0 & 1) {
            temp_s6 = temp_s2;
            temp_s2 = temp_s3;
            func_800D112C((temp_s4 + 1) & 7, temp_s6, temp_s2);
            func_800D112C((temp_s4 - 1) & 7, temp_s6, temp_s2);
            temp_a0 = temp_s4 + 3;
            temp_a0 &= 7;
            temp_s1_2 = D_8006CCD8;
            temp_s1_2 = &temp_s1_2[temp_s4];
            func_800D112C(temp_a0, (u32) (s16) (temp_s6 + ((s16) *temp_s1_2 * 0xA)), (u32) (s16) (temp_s2 + ((s16) D_8006CCE8[temp_s4] * 0xA)));
            func_800D1618((temp_s4 - 3) & 7,
                          (s16) (temp_s6 + ((s16) *temp_s1_2 * 0xA)),
                          (s16) (temp_s2 + ((s16) D_8006CCE8[temp_s4] * 0xA)));
            return;
        }
        temp_s1 = (s8 *) (s32) temp_s4;
        func_800D112C((s32) temp_s1, temp_s2, temp_s3);
        temp_s4 = (s32) temp_s1 + 2;
        temp_s4 &= 7;
        func_800D112C(temp_s4, temp_s2, temp_s3);
        temp_s5 = ((s32) temp_s1 - 2) & 7;
        func_800D112C(temp_s5, temp_s2, temp_s3);
        temp_a0 = (s32) temp_s1 + 4;
        temp_a0 &= 7;
        temp_s0_2 = D_8006CCD8;
        temp_s1 = (s8 *) ((s32) temp_s1 * 2);
        temp_s0_2 = (u16 *) ((s8 *) temp_s0_2 + (s32) temp_s1);
        temp_a1 = (s32) ((u32) (temp_s2 + ((s16) *temp_s0_2 * 0xA)) << 16);
        temp_s1 = (s8 *) D_8006CCE8 + (s32) temp_s1;
        func_800D112C(temp_a0, temp_a1 >> 16, (u32) (s16) (temp_s3 + ((s16) *(u16 *) temp_s1 * 0xA)));
        func_800D112C(temp_s4, (u32) (s16) (temp_s2 + ((s16) *temp_s0_2 * 0xA)), (u32) (s16) (temp_s3 + ((s16) *(u16 *) temp_s1 * 0xA)));
        temp_v1 = (s16) *temp_s0_2;
        ASM_SET(temp_a0_2);
        temp_a0_2 = temp_s5;
        temp_wide1 = (s32) ((u32) (temp_s2 + (temp_v1 * 0xA)) << 16);
        temp_v1 = (s16) *(u16 *) temp_s1;
        ASM_KEEP_DEP_NV(temp_wide1, temp_v1);
        temp_a1_2 = temp_wide1 >> 16;
        temp_wide2 = (s32) ((u32) (temp_s3 + (temp_v1 * 0xA)) << 16);
        temp_a2_2 = temp_wide2 >> 16;
        ASM_KEEP(temp_a2_2);
        func_800D112C(temp_a0_2, temp_a1_2, temp_a2_2);
    }
}
