#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80168C88_0 {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[0x10];
    union { s16 s; u16 u; } unk_12;   /* accessed as both */
    u8 pad_14[0x4];
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
    u8 pad_1A[0x2];
    s16 unk_1C;
    u16 unk_1E;
} S_80168C88_0;   /* arg0 in func_80168C88 */

typedef struct S_80168C88_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80168C88_1;   /* arg2 in func_80168C88 */

typedef struct S_80168C88_2 {
    u8 pad_00[0x54];
    s16 unk_54;
} S_80168C88_2;   /* temp_v0 in func_80168C88 */

typedef struct S_80168C88_3 {
    s16 unk_00;
} S_80168C88_3;   /* (void *)temp_a1 in func_80168C88 */

typedef struct S_80168C88_4 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x1];
    s8 unk_04;
    s8 unk_05;
    s8 unk_06;
    u8 pad_07[0x1];
    s8 unk_08;
    s8 unk_09;
    s8 unk_0A;
    u8 pad_0B[0x1];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x9];
    s16 unk_18;
    s16 unk_1A;
} S_80168C88_4;   /* temp_s0 in func_80168C88 */

typedef struct S_80168C88_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80168C88_5;   /* temp_v0_2 in func_80168C88 */

typedef struct S_80168C88_6 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_80168C88_6;   /* temp_a3 in func_80168C88 */

typedef struct S_80168C88_7 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80168C88_7;   /* temp_v1_3 in func_80168C88 */

typedef struct S_80168C88_8 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80168C88_8;   /* arg1 in func_80168C88 */

typedef struct S_80168C88_9 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_80168C88_9;   /* temp_a3_2 in func_80168C88 */

typedef struct S_80168C88_10 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_80168C88_10;   /* var_a0 in func_80168C88 */

typedef struct S_80168C88_11 {
    u8 pad_00[0x8];
    u8 unk_08;
} S_80168C88_11;   /* temp_a0_3 in func_80168C88 */

typedef struct S_80168C88_12 {
    u8 pad_00[0x9];
    u8 unk_09;
} S_80168C88_12;   /* temp_a0_4 in func_80168C88 */

typedef struct S_80168C88_13 {
    u16 unk_00;
} S_80168C88_13;   /* lookup in func_80168C88 */

typedef struct S_80168C88_14 {
    u16 unk_00;
} S_80168C88_14;   /* lookup_final in func_80168C88 */



extern void *func_8003FC64();
extern void func_8004491C();
extern s32 D_800814A0;
extern u8 D_80166914[];
extern u8 D_80167C30[];
extern u8 D_80173B4C[];
extern u8 D_80175DD8[];

void func_80168C88(u8 *arg0, void *arg1, void *arg2_in)
{
    register void *arg2 ASM_REG("$23");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s16 temp_v1;
    u16 temp_a0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_t0;
    s32 var_t4;
    s32 var_t5;
    s32 var_t2;
    s32 var_t3;
    register s32 var_t1 ASM_REG("$9");   /* MATCH pin: retail register colouring depends on it */
    s32 var_a3;
    s32 temp_a1;
    register u8 *temp_v1_2 ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    register u8 *temp_v0 ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s16 *temp_a2;
    register s32 temp_a0_2 ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 *table_base;
    s32 var_s3;
    s32 var_s4;
    void *temp_v0_2;
    u8 *temp_s0;
    register void *temp_a3 ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
    void *temp_v1_3;
    register s32 var_t0_2 ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
    register u8 *var_a0 ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
    void *temp_a3_2;
    s32 var_t2_2;
    u8 *var_t0_3;
    u8 *temp_a0_3;
    void *temp_a0_4;
    s32 var_a3_2;
    s32 temp_t1;
    u16 *var_a1;
    register u16 *var_a2 ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    s32 temp_a0_5;
    s32 temp_v1_4;
    s32 temp_v0_4;
    register u8 *lookup ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 *lookup_final;
    s16 temp_v0_3;
    u8 *base_80175DD8;
    register s32 one ASM_REG("$22");   /* MATCH pin: keeps a constant in a register as retail does */

    temp_v1 = ((S_80168C88_0 *)arg0)->unk_12.s;
    temp_a0 = *(volatile u16 *)(arg0 + 0x12);
    arg2 = arg2_in;
    if (temp_v1 == 0) {
        goto status_zero;
    }
    if (temp_v1 == 1) {
        goto status_one;
    }
    var_t0 = 1;
    goto table_setup;

status_zero:
    if (((S_80168C88_0 *)arg0)->unk_18.s < 6) {
        ((S_80168C88_0 *)arg0)->unk_12.u = temp_a0 + 1;
    }
    goto table_start;

status_one:
    var_v0 = ((S_80168C88_0 *)arg0)->unk_00 * ((S_80168C88_0 *)arg0)->unk_18.s;
    if (var_v0 < 0) {
        var_v0 += 3;
    }
    ((S_80168C88_1 *)arg2)->unk_0C = var_v0 >> 2;
    var_v0_2 = ((S_80168C88_0 *)arg0)->unk_01 * ((S_80168C88_0 *)arg0)->unk_18.s;
    if (var_v0_2 < 0) {
        var_v0_2 += 3;
    }
    ((S_80168C88_1 *)arg2)->unk_0D = var_v0_2 >> 2;

table_start:
    var_t0 = 1;
table_setup:
    table_base = D_80175DD8;
    var_t4 = 0xC;
    do {
        var_t2 = 0;
        var_t5 = var_t4;
        var_t3 = var_t2;
loop_14:
        var_a3 = 0;
        var_t1 = var_t3;
loop_15:
        temp_a1 = var_a3 * 2;
        temp_v1_2 = (u8 *)(((S_80168C88_0 *)arg0)->unk_1C * 0x60);
        ASM_KEEP_NV(temp_v1_2);   /* MATCH pin: keeps a constant in a register as retail does */
        temp_v1_2 += (s32)table_base;
        temp_v0 = (u8 *)((s32)var_t1 + (s32)temp_v1_2);
        temp_a2 = (s16 *)temp_a1;
        temp_a2 = (s16 *)((u8 *)temp_a2 + (s32)temp_v0);
        ASM_KEEP_DEP_NV(temp_a2, temp_v0);   /* MATCH pin: keeps a constant in a register as retail does */
        temp_v0 += temp_a1;
        ASM_KEEP_NV(temp_v0);   /* MATCH pin: keeps a constant in a register as retail does */
        temp_a0_2 = (((S_80168C88_2 *)temp_v0)->unk_54 - *temp_a2) * var_t0;
        var_a3 += 1;
        temp_v1_2 = (u8 *)((s32)var_t5 + (s32)temp_v1_2);
        temp_v1_2 = (u8 *)((s32)var_t1 + (s32)temp_v1_2);
        temp_a1 += (s32)temp_v1_2;
        ASM_KEEP_NV(temp_a1);   /* MATCH pin: keeps a constant in a register as retail does */
        ((S_80168C88_3 *)((void *)temp_a1))->unk_00 = *temp_a2 + temp_a0_2 / 7;
        if (var_a3 < 3) {
            goto loop_15;
        }
        var_t2 += 1;
        var_t3 += 6;
        if (var_t2 < 2) {
            goto loop_14;
        }
        var_t0 += 1;
        var_t4 += 0xC;
    } while (var_t0 < 7);

    var_s3 = 0;
    base_80175DD8 = D_80175DD8;
    one = 1;
    var_s4 = var_s3;
    ((S_80168C88_0 *)arg0)->unk_1E = ((S_80168C88_0 *)arg0)->unk_1E - 1;
    do {
        temp_v0_2 = func_8003FC64(0x12);
        if (temp_v0_2 != NULL) {
            register void *task_arg ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
            void *init_fn;
            void *callback;

            task_arg = temp_v0_2;
            temp_s0 = (u8 *)temp_v0_2 + 0x20;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            init_fn = D_80167C30;
            ASM_KEEP_DEP_NV(init_fn, temp_s0);   /* MATCH pin: retail immediate-load split depends on it */
            callback = D_80166914;
            ((S_80168C88_4 *)temp_s0)->unk_18 = one;
            ((S_80168C88_4 *)temp_s0)->unk_1A = one;
            ((S_80168C88_5 *)temp_v0_2)->unk_10 = init_fn;
            func_8004491C(task_arg, callback);

            temp_a3 = ((S_80168C88_5 *)temp_v0_2)->unk_0C;
            ((S_80168C88_6 *)temp_a3)->unk_10 = 0x20;
            ((S_80168C88_6 *)temp_a3)->unk_14 |= 0xC;

            temp_v1_3 = ((S_80168C88_5 *)temp_v0_2)->unk_08;
            ((S_80168C88_7 *)temp_v1_3)->unk_00 = ((S_80168C88_8 *)arg1)->unk_00;
            var_t0_2 = 0;
            ((S_80168C88_7 *)temp_v1_3)->unk_04 = ((S_80168C88_8 *)arg1)->unk_04;
            var_a0 = temp_s0;
            ((S_80168C88_7 *)temp_v1_3)->unk_08 = ((S_80168C88_8 *)arg1)->unk_08;

            temp_a3_2 = ((S_80168C88_5 *)temp_v0_2)->unk_0C;
            ((S_80168C88_9 *)temp_a3_2)->unk_1E = 0x1000;
            ((S_80168C88_9 *)temp_a3_2)->unk_1C = 0x1000;
            ((S_80168C88_9 *)temp_a3_2)->unk_0E = 0x80;
            ((S_80168C88_9 *)temp_a3_2)->unk_0D = 0x80;
            ((S_80168C88_9 *)temp_a3_2)->unk_0C = 0x80;

            do {
                ((S_80168C88_10 *)var_a0)->unk_00 = ((S_80168C88_1 *)arg2)->unk_0C;
                ((S_80168C88_10 *)var_a0)->unk_01 = ((S_80168C88_1 *)arg2)->unk_0D;
                var_t0_2 += 1;
                ((S_80168C88_10 *)var_a0)->unk_02 = ((S_80168C88_1 *)arg2)->unk_0E;
                var_a0 += 4;
            } while (var_t0_2 < 4);

            if (var_s3 == 0) {
                ((S_80168C88_4 *)temp_s0)->unk_06 = 0;
                ((S_80168C88_4 *)temp_s0)->unk_05 = 0;
                ((S_80168C88_4 *)temp_s0)->unk_04 = 0;
                ((S_80168C88_4 *)temp_s0)->unk_02 = 0;
                ((S_80168C88_4 *)temp_s0)->unk_01 = 0;
                ((S_80168C88_4 *)temp_s0)->unk_00 = 0;
            }
            if (var_s3 == 6) {
                ((S_80168C88_4 *)temp_s0)->unk_0E = 0;
                ((S_80168C88_4 *)temp_s0)->unk_0D = 0;
                ((S_80168C88_4 *)temp_s0)->unk_0C = 0;
                ((S_80168C88_4 *)temp_s0)->unk_0A = 0;
                ((S_80168C88_4 *)temp_s0)->unk_09 = 0;
                ((S_80168C88_4 *)temp_s0)->unk_08 = 0;
            }

            ((S_80168C88_9 *)temp_a3_2)->unk_06 = 0;
            __builtin_memcpy(temp_s0 + 0x28, D_80173B4C, 0xC);

            var_t2_2 = 0;
            var_t3 = var_s4;
            var_t0_3 = temp_s0;
            temp_a0_3 = var_t0_3 + 0x28;
            ((S_80168C88_9 *)temp_a3_2)->unk_08 = temp_a0_3;
            ((S_80168C88_11 *)temp_a0_3)->unk_08 += ((S_80168C88_0 *)arg0)->unk_1C * 4;
            temp_a0_4 = ((S_80168C88_9 *)temp_a3_2)->unk_08;
            ((S_80168C88_12 *)temp_a0_4)->unk_09 += (((S_80168C88_0 *)arg0)->unk_1E & 3) * 8;

            do {
                var_a3_2 = 0;
                temp_v1_4 = one - var_t2_2;
                ASM_KEEP_NV(temp_v1_4);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                temp_v0_4 = temp_v1_4 * 2;
                temp_v0_4 += temp_v1_4;
                ASM_KEEP_NV(temp_v0_4);   /* MATCH pin: keeps a constant in a register as retail does */
                temp_t1 = temp_v0_4 * 2;
                var_a2 = (u16 *)(var_t0_3 + 0x80);
                var_a1 = (u16 *)(var_t0_3 + 0x74);
loop_28:
                temp_a0_5 = var_a3_2 * 2;
                lookup = (u8 *)(((S_80168C88_0 *)arg0)->unk_1C * 0x60);
                lookup += (s32)base_80175DD8;
                lookup = (u8 *)((s32)var_t3 + (s32)lookup);
                lookup = (u8 *)((s32)temp_t1 + (s32)lookup);
                lookup = (u8 *)((s32)temp_a0_5 + (s32)lookup);
                *var_a1 = ((S_80168C88_13 *)lookup)->unk_00;
                var_a3_2 += 1;
                var_a1 += 1;
                lookup = (u8 *)(((S_80168C88_0 *)arg0)->unk_1C * 0x60);
                lookup += (s32)base_80175DD8;
                lookup = (u8 *)((s32)var_t3 + (s32)lookup);
                lookup += 0xC;
                lookup = (u8 *)((s32)temp_t1 + (s32)lookup);
                lookup_final = (u8 *)((s32)temp_a0_5 + (s32)lookup);
                ASM_KEEP_NV(lookup_final);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                *var_a2 = ((S_80168C88_14 *)lookup_final)->unk_00;
                var_a2 += 1;
                if (var_a3_2 < 3) {
                    goto loop_28;
                }
                var_t2_2 += 1;
                var_t0_3 += 6;
            } while (var_t2_2 < 2);
        }
        var_s3 += 1;
        var_s4 += 0xC;
    } while (var_s3 < 7);

    temp_v0_3 = ((S_80168C88_0 *)arg0)->unk_18.u - 1;
    ((S_80168C88_0 *)arg0)->unk_18.s = temp_v0_3;
    if ((temp_v0_3 << 0x10) <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
