#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void *func_8003FC64();
extern void func_8004491C();
extern s32 D_800814A0;
extern u8 D_80166914[];
extern u8 D_80167C30[];
extern u8 D_80173B4C[];
extern u8 D_80175DD8[];

void func_80168C88(u8 *arg0, void *arg1, void *arg2_in)
{
    register void *arg2 ASM_REG("$23");
    s16 temp_v1;
    u16 temp_a0;
    s32 var_v0;
    s32 var_v0_2;
    register s32 var_t0 ASM_REG("$8");
    register s32 var_t4 ASM_REG("$12");
    register s32 var_t5 ASM_REG("$13");
    register s32 var_t2 ASM_REG("$10");
    register s32 var_t3 ASM_REG("$11");
    register s32 var_t1 ASM_REG("$9");
    register s32 var_a3 ASM_REG("$7");
    register s32 temp_a1 ASM_REG("$5");
    register u8 *temp_v1_2 ASM_REG("$3");
    register u8 *temp_v0 ASM_REG("$2");
    register s16 *temp_a2 ASM_REG("$6");
    register s32 temp_a0_2 ASM_REG("$4");
    u8 *table_base;
    register s32 var_s3 ASM_REG("$19");
    register s32 var_s4 ASM_REG("$20");
    void *temp_v0_2;
    u8 *temp_s0;
    register void *temp_a3 ASM_REG("$7");
    void *temp_v1_3;
    register s32 var_t0_2 ASM_REG("$8");
    register u8 *var_a0 ASM_REG("$4");
    register void *temp_a3_2 ASM_REG("$7");
    register s32 var_t2_2 ASM_REG("$10");
    register u8 *var_t0_3 ASM_REG("$8");
    u8 *temp_a0_3;
    void *temp_a0_4;
    register s32 var_a3_2 ASM_REG("$7");
    register s32 temp_t1 ASM_REG("$9");
    register u16 *var_a1 ASM_REG("$5");
    register u16 *var_a2 ASM_REG("$6");
    s32 temp_a0_5;
    register s32 temp_v1_4 ASM_REG("$3");
    register s32 temp_v0_4 ASM_REG("$2");
    register u8 *lookup ASM_REG("$2");
    register u8 *lookup_final ASM_REG("$4");
    s16 temp_v0_3;
    u8 *base_80175DD8;
    register s32 one ASM_REG("$22");

    temp_v1 = FIELD(arg0, s16, 0x12);
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
    if (FIELD(arg0, s16, 0x18) < 6) {
        FIELD(arg0, u16, 0x12) = temp_a0 + 1;
    }
    goto table_start;

status_one:
    var_v0 = FIELD(arg0, u8, 0) * FIELD(arg0, s16, 0x18);
    if (var_v0 < 0) {
        var_v0 += 3;
    }
    FIELD(arg2, u8, 0xC) = var_v0 >> 2;
    var_v0_2 = FIELD(arg0, u8, 1) * FIELD(arg0, s16, 0x18);
    if (var_v0_2 < 0) {
        var_v0_2 += 3;
    }
    FIELD(arg2, u8, 0xD) = var_v0_2 >> 2;

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
        temp_v1_2 = (u8 *)(FIELD(arg0, s16, 0x1C) * 0x60);
        ASM_KEEP_NV(temp_v1_2);
        temp_v1_2 += (s32)table_base;
        temp_v0 = (u8 *)((s32)var_t1 + (s32)temp_v1_2);
        temp_a2 = (s16 *)temp_a1;
        temp_a2 = (s16 *)((u8 *)temp_a2 + (s32)temp_v0);
        ASM_KEEP_DEP_NV(temp_a2, temp_v0);
        temp_v0 += temp_a1;
        ASM_KEEP_NV(temp_v0);
        temp_a0_2 = (FIELD(temp_v0, s16, 0x54) - *temp_a2) * var_t0;
        var_a3 += 1;
        temp_v1_2 = (u8 *)((s32)var_t5 + (s32)temp_v1_2);
        temp_v1_2 = (u8 *)((s32)var_t1 + (s32)temp_v1_2);
        temp_a1 += (s32)temp_v1_2;
        ASM_KEEP_NV(temp_a1);
        FIELD((void *)temp_a1, s16, 0) = *temp_a2 + temp_a0_2 / 7;
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
    FIELD(arg0, u16, 0x1E) = FIELD(arg0, u16, 0x1E) - 1;
    do {
        temp_v0_2 = func_8003FC64(0x12);
        if (temp_v0_2 != NULL) {
            register void *task_arg ASM_REG("$4");
            register void *init_fn ASM_REG("$2");
            register void *callback ASM_REG("$5");

            task_arg = temp_v0_2;
            temp_s0 = (u8 *)temp_v0_2 + 0x20;
            ASM_SCHED_BARRIER();
            init_fn = D_80167C30;
            ASM_KEEP_DEP_NV(init_fn, temp_s0);
            callback = D_80166914;
            ASM_KEEP_DEP_NV(callback, init_fn);
            FIELD(temp_s0, s16, 0x18) = one;
            FIELD(temp_s0, s16, 0x1A) = one;
            FIELD(temp_v0_2, void *, 0x10) = init_fn;
            func_8004491C(task_arg, callback);

            temp_a3 = FIELD(temp_v0_2, void *, 0xC);
            FIELD(temp_a3, s16, 0x10) = 0x20;
            FIELD(temp_a3, u16, 0x14) |= 0xC;

            temp_v1_3 = FIELD(temp_v0_2, void *, 8);
            FIELD(temp_v1_3, s32, 0) = FIELD(arg1, s32, 0);
            var_t0_2 = 0;
            FIELD(temp_v1_3, s32, 4) = FIELD(arg1, s32, 4);
            var_a0 = temp_s0;
            FIELD(temp_v1_3, s32, 8) = FIELD(arg1, s32, 8);

            temp_a3_2 = FIELD(temp_v0_2, void *, 0xC);
            FIELD(temp_a3_2, s16, 0x1E) = 0x1000;
            FIELD(temp_a3_2, s16, 0x1C) = 0x1000;
            FIELD(temp_a3_2, u8, 0xE) = 0x80;
            FIELD(temp_a3_2, u8, 0xD) = 0x80;
            FIELD(temp_a3_2, u8, 0xC) = 0x80;

            do {
                FIELD(var_a0, u8, 0) = FIELD(arg2, u8, 0xC);
                FIELD(var_a0, u8, 1) = FIELD(arg2, u8, 0xD);
                var_t0_2 += 1;
                FIELD(var_a0, u8, 2) = FIELD(arg2, u8, 0xE);
                var_a0 += 4;
            } while (var_t0_2 < 4);

            if (var_s3 == 0) {
                FIELD(temp_s0, s8, 6) = 0;
                FIELD(temp_s0, s8, 5) = 0;
                FIELD(temp_s0, s8, 4) = 0;
                FIELD(temp_s0, s8, 2) = 0;
                FIELD(temp_s0, s8, 1) = 0;
                FIELD(temp_s0, s8, 0) = 0;
            }
            if (var_s3 == 6) {
                FIELD(temp_s0, s8, 0xE) = 0;
                FIELD(temp_s0, s8, 0xD) = 0;
                FIELD(temp_s0, s8, 0xC) = 0;
                FIELD(temp_s0, s8, 0xA) = 0;
                FIELD(temp_s0, s8, 9) = 0;
                FIELD(temp_s0, s8, 8) = 0;
            }

            FIELD(temp_a3_2, s16, 6) = 0;
            __builtin_memcpy(temp_s0 + 0x28, D_80173B4C, 0xC);

            var_t2_2 = 0;
            var_t3 = var_s4;
            var_t0_3 = temp_s0;
            temp_a0_3 = var_t0_3 + 0x28;
            FIELD(temp_a3_2, void *, 8) = temp_a0_3;
            FIELD(temp_a0_3, u8, 8) += FIELD(arg0, s16, 0x1C) * 4;
            temp_a0_4 = FIELD(temp_a3_2, void *, 8);
            FIELD(temp_a0_4, u8, 9) += (FIELD(arg0, u16, 0x1E) & 3) * 8;

            do {
                var_a3_2 = 0;
                temp_v1_4 = one - var_t2_2;
                ASM_KEEP_NV(temp_v1_4);
                temp_v0_4 = temp_v1_4 * 2;
                temp_v0_4 += temp_v1_4;
                ASM_KEEP_NV(temp_v0_4);
                temp_t1 = temp_v0_4 * 2;
                var_a2 = (u16 *)(var_t0_3 + 0x80);
                var_a1 = (u16 *)(var_t0_3 + 0x74);
loop_28:
                temp_a0_5 = var_a3_2 * 2;
                lookup = (u8 *)(FIELD(arg0, s16, 0x1C) * 0x60);
                ASM_KEEP_NV(lookup);
                lookup += (s32)base_80175DD8;
                lookup = (u8 *)((s32)var_t3 + (s32)lookup);
                lookup = (u8 *)((s32)temp_t1 + (s32)lookup);
                lookup = (u8 *)((s32)temp_a0_5 + (s32)lookup);
                *var_a1 = FIELD(lookup, u16, 0);
                var_a3_2 += 1;
                var_a1 += 1;
                lookup = (u8 *)(FIELD(arg0, s16, 0x1C) * 0x60);
                ASM_KEEP_NV(lookup);
                lookup += (s32)base_80175DD8;
                lookup = (u8 *)((s32)var_t3 + (s32)lookup);
                lookup += 0xC;
                lookup = (u8 *)((s32)temp_t1 + (s32)lookup);
                lookup_final = (u8 *)((s32)temp_a0_5 + (s32)lookup);
                ASM_KEEP_NV(lookup_final);
                *var_a2 = FIELD(lookup_final, u16, 0);
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

    temp_v0_3 = FIELD(arg0, u16, 0x18) - 1;
    FIELD(arg0, s16, 0x18) = temp_v0_3;
    if ((temp_v0_3 << 0x10) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
