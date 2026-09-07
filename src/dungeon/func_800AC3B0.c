#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B1B10_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x34];
    s32 unk_58;
    u8 pad_5C[0x14];
    s32 unk_70;
    s32 unk_74;
} S_800B1B10_0;   /* temp_s2 in func_800B1B10 */

typedef struct S_800B1B10_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800B1B10_1;   /* temp_v0_2 in func_800B1B10 */

typedef struct S_800B1B10_2 {
    u8 pad_00[0x4];
    void * unk_04;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x2];
    s32 unk_10;
    s32 unk_14;
    union { s32 n; volatile s32 v; } unk_18;   /* accessed as both */
    union { s32 n; volatile s32 v; } unk_1C;   /* accessed as both */
    u8 pad_20[0x2];
    s16 unk_22;
    s16 unk_24;
    u16 unk_26;
    s32 unk_28;
    s32 unk_2C;
    s32 unk_30;
} S_800B1B10_2;   /* temp_s3 in func_800B1B10 */

typedef struct S_800B1B10_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
} S_800B1B10_3;   /* temp_v1 in func_800B1B10 */

typedef struct S_800B1B10_4 {
    u8 unk_00;
    u8 unk_01;
} S_800B1B10_4;   /* arg0_s5 in func_800B1B10 */

typedef struct S_800B1B10_5 {
    u8 unk_00;
    union { u8 n; volatile u8 v; } unk_01;   /* accessed as both */
    s8 unk_02;
    union { u8 u; s8 s; } unk_03;   /* accessed as both */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    s8 unk_08;
    s8 unk_09;
    s8 unk_0A;
    s8 unk_0B;
    s32 unk_0C;
    volatile s32 unk_10;
    volatile s32 unk_14;
} S_800B1B10_5;   /* (void *) arg2_s1 in func_800B1B10 */

typedef struct S_800B1B10_6 {
    u8 pad_00[0x50];
    s32 unk_50;
} S_800B1B10_6;   /* ((arg3_s4++ * 4) + temp_s3) in func_800B1B10 */

typedef struct S_800B1B10_7 {
    u8 pad_00[0x50];
    s32 unk_50;
} S_800B1B10_7;   /* ((arg3_s4 * 4) + temp_s3) in func_800B1B10 */


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
    S_800B1B10_4 *arg0_s5 = arg0;
    register s32 arg1_s0 ASM_REG("$16") = arg1;   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 arg2_s1 = arg2;
    register s32 arg3_s4 ASM_REG("$20") = arg3;   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 raw_arg4 ASM_REG("$23") = arg4;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u16 arg5_t0 ASM_REG("$8") = arg5;   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 temp_s8;
    M2C_UNK var_a1;
    M2C_UNK temp_s2;
    register s32 arg3_v0 ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 geom_v1;
    register s32 call3_a0 ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 call69_a0 ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register u8 *call_a1 ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 copy_v0;
    s32 copy_v1;
    u32 byte_v0;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 tail_v0;
    register void *temp_s3 ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
    s32 *temp_s6;
    S_800B1B10_1 *temp_v0_2;
    void *temp_v0_3;
    S_800B1B10_3 *temp_v1;

    call3_a0 = 0x12;
#ifdef NON_MATCHING
    call_a1 = D_80083498;
#else
    call_a1 = (u8 *) 0x80080000;
#endif
    ASM_KEEP_DEP_NV(call_a1, call3_a0);   /* MATCH pin: retail immediate-load split depends on it */
    ASM_KEEP_DEP_NV(arg5_t0, raw_arg4);   /* MATCH pin: retail schedule: same instructions, different order without it */
    subroutine_arg4 = arg5_t0;
#ifndef NON_MATCHING
    call_a1 += 0x3498;
#endif
    ASM_KEEP_DEP_NV(call_a1, arg5_t0);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_s2 = (M2C_UNK) func_8003FD64(call3_a0, call_a1);
    temp_s8 = raw_arg4;
    if (temp_s2 != NULL) {
        temp_v1 = ((S_800B1B10_0 *)temp_s2)->unk_0C;
        temp_v0_2 = ((S_800B1B10_0 *)temp_s2)->unk_08;
        temp_s3 = temp_s2 + 0x20;
        temp_v0_2->unk_02 = arg1_s0;
        temp_v0_2->unk_06 = arg2_s1;
        ((S_800B1B10_2 *)temp_s3)->unk_08 = 1;
        temp_v1->unk_1C = 0x1000;
        temp_v1->unk_0C = 0;
        ((S_800B1B10_0 *)temp_s2)->unk_10 = &D_800B14FC;
        func_8004491C(temp_s2, &D_800B06F0);
        call3_a0 = 3;
        ASM_KEEP_NV(call3_a0);   /* MATCH pin: retail schedule: same instructions, different order without it */
        arg3_v0 = (s32) (arg3_s4 << 0x10) >> 0x18;
        ((S_800B1B10_2 *)temp_s3)->unk_24 = (s16) arg3_v0;
        ((S_800B1B10_2 *)temp_s3)->unk_0A = arg1_s0;
        ((S_800B1B10_2 *)temp_s3)->unk_0C = arg2_s1;
        ((S_800B1B10_0 *)temp_s2)->unk_20 = (void *) (temp_s2 + 0x70);
        ((S_800B1B10_2 *)temp_s3)->unk_04 = (void *) (temp_s2 + 0x58);
        if (func_8003FA44(call3_a0) != 0) {
            temp_s6 = (s32 *) (temp_s2 + 0x5C);
            arg1_s0 = (s32) func_800B12F4();
            arg2_s1 = arg1_s0;
            ASM_KEEP_NV(arg2_s1);   /* MATCH pin: retail delay-slot fill depends on it */
            ((S_800B1B10_2 *)temp_s3)->unk_28 = arg1_s0;
            ((S_800B1B10_0 *)temp_s2)->unk_70 = arg2_s1;
            temp_v0_3 = func_8004A658(arg0_s5->unk_01, arg0_s5->unk_00);
            arg3_s4 = 2;
            arg2_s1 = (s32) func_800B1434((void *) arg2_s1, temp_v0_3);
            ASM_KEEP_NV(arg3_s4);   /* MATCH pin: load-bearing for the whole function shape */
            func_800B13CC((void *) arg1_s0, 0x20);
            func_800B1400((void *) arg1_s0, arg3_s4);
            {
                s32 color_v0;
                color_v0 = 0x808080;
                ((S_800B1B10_0 *)temp_s2)->unk_58 = color_v0;
            }
            temp_v0_4 = func_800990FC();
            *func_80099368(arg0_s5, temp_v0_4) = 0;
            temp_v0_5 = func_8004DA74((void *) arg2_s1, temp_v0_4, 0);
            {
                s32 mask_v1;
                mask_v1 = 0x7FFFFFFF;
                call69_a0 = temp_v0_4;
                arg0_s5 = (void *) temp_v0_5;
                ((S_800B1B10_0 *)temp_s2)->unk_74 = (s32) arg0_s5 & mask_v1;
            }
            temp_s2 = func_80069E98(call69_a0) * 4;
            if ((raw_arg4 << 0x10) != 0) {
                tail_v0 = 0x89 - temp_s2;
                var_a1 = (s16) tail_v0;
                goto block_shared;
            }
            ASM_KEEP(raw_arg4);   /* MATCH pin: keeps a statement from moving across a call/branch */
            var_a1 = 0x8A;
block_shared:
            func_800B1320((void *) arg2_s1, var_a1, (s16) ((0 - (s8) ((S_800B1B10_5 *)((void *) arg2_s1))->unk_03.u) - 0xE));
            var_a1 = 8;
            if ((temp_s8 << 0x10) != 0) {
                var_a1 = 4;
            }
            func_800B135C((void *) arg2_s1, var_a1);
            func_800B13CC((void *) arg2_s1, 0x20);
            func_800B1400((void *) arg2_s1, 2);
            {
                s32 color_v0;
                color_v0 = 0x808080;
                *temp_s6 = color_v0;
            }
            temp_s6++;
            func_80069E98(temp_v0_4);
            arg2_s1 = (s32) func_800B12F4();
            ((S_800B1B10_2 *)temp_s3)->unk_2C = arg2_s1;
            {
                s32 mask_v0;
                mask_v0 = 0x7FFFFFFF;
                ((S_800B1B10_6 *)(((arg3_s4++ * 4) + temp_s3)))->unk_50 = arg2_s1 & mask_v0;
            }
            func_800B1434((void *) arg2_s1, arg0_s5);
            func_800B1320(arg0_s5, 1, 1);
            arg2_s1 = (s32) func_800B12F4();
            ((S_800B1B10_2 *)temp_s3)->unk_30 = arg2_s1;
            *temp_s6 = 0x80808;
            geom_v1 = 0x80000;
            ((S_800B1B10_7 *)(((arg3_s4 * 4) + temp_s3)))->unk_50 = arg2_s1;
            ((S_800B1B10_5 *)((void *) arg2_s1))->unk_01.n = 0x38U;
            ((S_800B1B10_5 *)((void *) arg2_s1))->unk_02 = -0xA;
            ((S_800B1B10_5 *)((void *) arg2_s1))->unk_03.s = -0x10;
            ((S_800B1B10_5 *)((void *) arg2_s1))->unk_0A = (s8) (temp_s2 + 0x18);
            ((S_800B1B10_5 *)((void *) arg2_s1))->unk_09 = 0;
            ((S_800B1B10_5 *)((void *) arg2_s1))->unk_08 = 0;
            ((S_800B1B10_5 *)((void *) arg2_s1))->unk_0B = 0x14;
            ((S_800B1B10_5 *)((void *) arg2_s1))->unk_00 = 0xC0;
            ((S_800B1B10_2 *)temp_s3)->unk_10 = 0;
            ((S_800B1B10_2 *)temp_s3)->unk_14 = 0;
            geom_v1 |= 0x4008;
            ((S_800B1B10_2 *)temp_s3)->unk_18.n = geom_v1;
            ((S_800B1B10_2 *)temp_s3)->unk_1C.n = geom_v1;
            ((S_800B1B10_5 *)((void *) arg2_s1))->unk_04.at00.v = (s32) ((S_800B1B10_2 *)temp_s3)->unk_10;
            ((S_800B1B10_5 *)((void *) arg2_s1))->unk_0C = (s32) ((S_800B1B10_2 *)temp_s3)->unk_14;
            copy_v0 = ((S_800B1B10_2 *)temp_s3)->unk_18.v;
            arg3_s4++;
            ((S_800B1B10_5 *)((void *) arg2_s1))->unk_10 = copy_v0;
            byte_v0 = ((S_800B1B10_5 *)((void *) arg2_s1))->unk_01.v;
            copy_v1 = ((S_800B1B10_2 *)temp_s3)->unk_1C.v;
            byte_v0 |= 2;
            ((S_800B1B10_5 *)((void *) arg2_s1))->unk_01.v = byte_v0;
            ((S_800B1B10_5 *)((void *) arg2_s1))->unk_14 = copy_v1;
            arg2_s1 += 0x18;
            ((S_800B1B10_7 *)(((arg3_s4 * 4) + temp_s3)))->unk_50 = arg2_s1;
            ASM_USE_NV(arg3_s4);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            ((S_800B1B10_5 *)((void *) arg2_s1))->unk_01.n = 0x81;
            ((S_800B1B10_5 *)((void *) arg2_s1))->unk_04.at00u.v = 0x20;
            ((S_800B1B10_5 *)((void *) arg2_s1))->unk_04.at02.v = 0;
            ((S_800B1B10_5 *)((void *) arg2_s1))->unk_00 = 0xC0;
            goto block_8;
        }
block_8:
        ((S_800B1B10_2 *)temp_s3)->unk_22 = 4;
        arg5_t0 = subroutine_arg4;
        ASM_KEEP_NV(arg5_t0);   /* MATCH pin: retail register colouring depends on it */
        ((S_800B1B10_2 *)temp_s3)->unk_26 = arg5_t0;
    }
}
