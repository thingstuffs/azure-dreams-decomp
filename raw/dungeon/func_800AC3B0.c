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

extern u8 D_80083498[];
void *func_8003FD64();
M2C_UNK func_8004491C();
s32 func_8004DA74();
s32 func_80069E98();
s32 func_800990FC();
s8 *func_80099368();
void *func_800B12F4();
M2C_UNK func_800B1320();
M2C_UNK func_800B135C();
M2C_UNK func_800B1400();
void *func_800B1434();
extern M2C_UNK D_800B14FC;
extern M2C_UNK D_800B06F0;

void func_800B1B10(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 arg5) {
    u16 subroutine_arg4;
    register void *arg0_s5 ASM_REG("$21") = arg0;
    register s32 arg1_s0 ASM_REG("$16") = arg1;
    register s32 arg2_s1 ASM_REG("$17") = arg2;
    register s32 arg3_s4 ASM_REG("$20") = arg3;
    register s32 raw_arg4 ASM_REG("$23") = arg4;
    register u16 arg5_t0 ASM_REG("$8") = arg5;
    register s32 temp_s8;
    M2C_UNK var_a1;
    register M2C_UNK temp_s2 ASM_REG("$18");
    register s32 arg3_v0 ASM_REG("$2");
    register s32 geom_v1 ASM_REG("$3");
    register s32 call3_a0 ASM_REG("$4");
    register s32 call69_a0 ASM_REG("$4");
    register u8 *call_a1 ASM_REG("$5");
    register s32 copy_v0 ASM_REG("$2");
    register s32 copy_v1 ASM_REG("$3");
    register u32 byte_v0 ASM_REG("$2");
    s32 temp_v0_4;
    s32 temp_v0_5;
    register s32 tail_v0 ASM_REG("$2");
    register void *temp_s3 ASM_REG("$19");
    s32 *temp_s6;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v1;

    call3_a0 = 0x12;
#ifdef NON_MATCHING
    call_a1 = D_80083498;
#else
    call_a1 = (u8 *) 0x80080000;
#endif
    ASM_KEEP_DEP_NV(call_a1, call3_a0);
    ASM_KEEP_DEP_NV(arg5_t0, raw_arg4);
    subroutine_arg4 = arg5_t0;
#ifndef NON_MATCHING
    call_a1 += 0x3498;
#endif
    ASM_KEEP_DEP_NV(call_a1, arg5_t0);
    temp_s2 = (M2C_UNK) func_8003FD64(call3_a0, call_a1);
    ASM_KEEP_NV(arg0_s5);
    temp_s8 = raw_arg4;
    if (temp_s2 != NULL) {
        ASM_KEEP(temp_s8);
        temp_v1 = M2C_FIELD(temp_s2, void **, 0xC);
        temp_v0_2 = M2C_FIELD(temp_s2, void **, 8);
        temp_s3 = temp_s2 + 0x20;
        M2C_FIELD(temp_v0_2, s16 *, 2) = arg1_s0;
        M2C_FIELD(temp_v0_2, s16 *, 6) = arg2_s1;
        M2C_FIELD(temp_s3, s16 *, 8) = 1;
        M2C_FIELD(temp_v1, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_v1, s32 *, 0xC) = 0;
        M2C_FIELD(temp_s2, M2C_UNK **, 0x10) = &D_800B14FC;
        func_8004491C(temp_s2, &D_800B06F0);
        call3_a0 = 3;
        ASM_KEEP_NV(call3_a0);
        arg3_v0 = (s32) (arg3_s4 << 0x10) >> 0x18;
        ASM_KEEP_NV(arg3_v0);
        M2C_FIELD(temp_s3, s16 *, 0x24) = (s16) arg3_v0;
        M2C_FIELD(temp_s3, s16 *, 0xA) = arg1_s0;
        M2C_FIELD(temp_s3, s16 *, 0xC) = arg2_s1;
        M2C_FIELD(temp_s2, void **, 0x20) = (void *) (temp_s2 + 0x70);
        M2C_FIELD(temp_s3, void **, 4) = (void *) (temp_s2 + 0x58);
        if (func_8003FA44(call3_a0) != 0) {
            temp_s6 = (s32 *) (temp_s2 + 0x5C);
            arg1_s0 = (s32) func_800B12F4();
            arg2_s1 = arg1_s0;
            ASM_KEEP_NV(arg2_s1);
            M2C_FIELD(temp_s3, s32 *, 0x28) = arg1_s0;
            M2C_FIELD(temp_s2, s32 *, 0x70) = arg2_s1;
            temp_v0_3 = func_8004A658(M2C_FIELD(arg0_s5, u8 *, 1), M2C_FIELD(arg0_s5, u8 *, 0));
            arg3_s4 = 2;
            arg2_s1 = (s32) func_800B1434((void *) arg2_s1, temp_v0_3);
            ASM_KEEP_NV(arg3_s4);
            func_800B13CC((void *) arg1_s0, 0x20);
            func_800B1400((void *) arg1_s0, arg3_s4);
            {
                register s32 color_v0 ASM_REG("$2");
                color_v0 = 0x808080;
                ASM_KEEP_NV(color_v0);
                M2C_FIELD(temp_s2, s32 *, 0x58) = color_v0;
            }
            temp_v0_4 = func_800990FC();
            *func_80099368(arg0_s5, temp_v0_4) = 0;
            temp_v0_5 = func_8004DA74((void *) arg2_s1, temp_v0_4, 0);
            {
                register s32 mask_v1 ASM_REG("$3");
                mask_v1 = 0x7FFFFFFF;
                ASM_KEEP_NV(mask_v1);
                call69_a0 = temp_v0_4;
                ASM_KEEP_NV(call69_a0);
                arg0_s5 = (void *) temp_v0_5;
                M2C_FIELD(temp_s2, s32 *, 0x74) = (s32) arg0_s5 & mask_v1;
            }
            temp_s2 = func_80069E98(call69_a0) * 4;
            if ((raw_arg4 << 0x10) != 0) {
                tail_v0 = 0x89 - temp_s2;
                ASM_KEEP_NV(tail_v0);
                var_a1 = (s16) tail_v0;
                goto block_shared;
            }
            ASM_KEEP(raw_arg4);
            var_a1 = 0x8A;
block_shared:
            func_800B1320((void *) arg2_s1, var_a1, (s16) ((0 - (s8) M2C_FIELD((void *) arg2_s1, u8 *, 3)) - 0xE));
            var_a1 = 8;
            if ((temp_s8 << 0x10) != 0) {
                var_a1 = 4;
            }
            func_800B135C((void *) arg2_s1, var_a1);
            func_800B13CC((void *) arg2_s1, 0x20);
            func_800B1400((void *) arg2_s1, 2);
            {
                register s32 color_v0 ASM_REG("$2");
                color_v0 = 0x808080;
                ASM_KEEP_NV(color_v0);
                *temp_s6 = color_v0;
            }
            temp_s6++;
            func_80069E98(temp_v0_4);
            arg2_s1 = (s32) func_800B12F4();
            M2C_FIELD(temp_s3, s32 *, 0x2C) = arg2_s1;
            {
                register s32 mask_v0 ASM_REG("$2");
                mask_v0 = 0x7FFFFFFF;
                ASM_KEEP_NV(mask_v0);
                M2C_FIELD(((arg3_s4++ * 4) + temp_s3), s32 *, 0x50) = arg2_s1 & mask_v0;
            }
            func_800B1434((void *) arg2_s1, arg0_s5);
            func_800B1320(arg0_s5, 1, 1);
            arg2_s1 = (s32) func_800B12F4();
            M2C_FIELD(temp_s3, s32 *, 0x30) = arg2_s1;
            *temp_s6 = 0x80808;
            geom_v1 = 0x80000;
            ASM_KEEP_NV(geom_v1);
            M2C_FIELD(((arg3_s4 * 4) + temp_s3), s32 *, 0x50) = arg2_s1;
            M2C_FIELD((void *) arg2_s1, u8 *, 1) = 0x38U;
            M2C_FIELD((void *) arg2_s1, s8 *, 2) = -0xA;
            M2C_FIELD((void *) arg2_s1, s8 *, 3) = -0x10;
            M2C_FIELD((void *) arg2_s1, s8 *, 0xA) = (s8) (temp_s2 + 0x18);
            ASM_USE_NV(temp_s2);
            M2C_FIELD((void *) arg2_s1, s8 *, 9) = 0;
            M2C_FIELD((void *) arg2_s1, s8 *, 8) = 0;
            M2C_FIELD((void *) arg2_s1, s8 *, 0xB) = 0x14;
            M2C_FIELD((void *) arg2_s1, u8 *, 0) = 0xC0;
            M2C_FIELD(temp_s3, s32 *, 0x10) = 0;
            M2C_FIELD(temp_s3, s32 *, 0x14) = 0;
            geom_v1 |= 0x4008;
            M2C_FIELD(temp_s3, s32 *, 0x18) = geom_v1;
            M2C_FIELD(temp_s3, s32 *, 0x1C) = geom_v1;
            M2C_FIELD((void *) arg2_s1, s32 *, 4) = (s32) M2C_FIELD(temp_s3, s32 *, 0x10);
            M2C_FIELD((void *) arg2_s1, s32 *, 0xC) = (s32) M2C_FIELD(temp_s3, s32 *, 0x14);
            copy_v0 = M2C_FIELD(temp_s3, volatile s32 *, 0x18);
            ASM_KEEP_NV(copy_v0);
            ASM_KEEP_DEP_NV(arg3_s4, copy_v0);
            arg3_s4++;
            M2C_FIELD((void *) arg2_s1, volatile s32 *, 0x10) = copy_v0;
            byte_v0 = M2C_FIELD((void *) arg2_s1, volatile u8 *, 1);
            ASM_KEEP_NV(byte_v0);
            copy_v1 = M2C_FIELD(temp_s3, volatile s32 *, 0x1C);
            ASM_KEEP_NV(copy_v1);
            byte_v0 |= 2;
            M2C_FIELD((void *) arg2_s1, volatile u8 *, 1) = byte_v0;
            M2C_FIELD((void *) arg2_s1, volatile s32 *, 0x14) = copy_v1;
            arg2_s1 += 0x18;
            M2C_FIELD(((arg3_s4 * 4) + temp_s3), s32 *, 0x50) = arg2_s1;
            ASM_USE_NV(arg3_s4);
            M2C_FIELD((void *) arg2_s1, u8 *, 1) = 0x81;
            M2C_FIELD((void *) arg2_s1, s16 *, 4) = 0x20;
            M2C_FIELD((void *) arg2_s1, s16 *, 6) = 0;
            M2C_FIELD((void *) arg2_s1, u8 *, 0) = 0xC0;
            goto block_8;
        }
block_8:
        M2C_FIELD(temp_s3, s16 *, 0x22) = 4;
        arg5_t0 = subroutine_arg4;
        ASM_KEEP_NV(arg5_t0);
        M2C_FIELD(temp_s3, u16 *, 0x26) = arg5_t0;
    }
}
