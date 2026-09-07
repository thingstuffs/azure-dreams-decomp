#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_8003FC64(s32);
void func_8004491C(void *, void *);
s32 func_800644B8(s32);
s32 func_80064584(s32);
void func_80174DC0(void) __attribute__((noreturn));
void func_80175094(void *) __attribute__((noreturn));
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80174954;
extern M2C_UNK D_801749A8;

void func_801749EC(void *arg0, void *arg1, void *arg2) {
    s16 sp10[10];
    s16 sp28[10][6][3];
    s16 *volatile sp190;
    s16 *volatile sp194;
    register void *object_origin;
    M2C_UNK *var_v0;
    register s16 *temp_s6 ASM_REG("$22");
    register s16 *temp_s6_2 ASM_REG("$22");
    s16 temp_v0;
    register s16 temp_v0_11 ASM_REG("$2");
    register s16 temp_v0_17 ASM_REG("$2");
    s16 temp_v0_18;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_7;
    s16 temp_v0_8;
    s16 temp_v0_9;
    s16 temp_dec;
    s16 temp_v1;
    register s16 var_s2 ASM_REG("$18");
    register s16 var_s2_2 ASM_REG("$18");
    register s16 var_s3 ASM_REG("$19");
    register s16 var_s3_3 ASM_REG("$19");
    register s16 var_s3_4 ASM_REG("$19");
    register s16 var_s4 ASM_REG("$20");
    s16 var_v0_4;
    s16 var_v0_5;
    s32 temp_a0_3;
    register s32 temp_a1 ASM_REG("$5");
    s32 temp_s0;
    s32 temp_s0_2;
    register s32 temp_s1 ASM_REG("$17");
    register s32 temp_s1_2 ASM_REG("$17");
    register s32 temp_s5 ASM_REG("$21");
    register s32 temp_s7 ASM_REG("$23");
    s32 temp_trig;
    register s32 temp_outer;
    s32 temp_v0_6;
    u16 temp_v0_10;
    u16 temp_v0_5;
    u16 temp_tail;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a0_4;
    void *temp_a0_5;
    register void *temp_a0_6 ASM_REG("$4");
    register void *temp_s1_3 ASM_REG("$17");
    register void *temp_s1_4 ASM_REG("$17");
    void *temp_s2;
    void *temp_s2_2;
    register void *temp_s4 ASM_REG("$20");
    register void *color ASM_REG("$7");
    register void *temp_v0_12 ASM_REG("$16");
    void *temp_v0_13;
    register void *temp_v0_14 ASM_REG("$16");
    register void *temp_v0_15 ASM_REG("$2");
    register void *temp_v0_16 ASM_REG("$2");
    void *temp_v1_2;
    void *temp_v1_3;
    void *temp_v1_4;
    void *temp_v1_5;
    register M2C_UNK *second_global;

    (void)&arg0;
    object_origin = arg1;
    temp_v1 = M2C_FIELD(arg0, s16 *, 6);
    if (temp_v1 != 1) {
        var_s2 = 0;
        if (temp_v1 < 2) {
            if (temp_v1 == 0) {
                register s32 scale ASM_REG("$4");
                register s16 *prep_base ASM_REG("$5");
                register s32 prep_clamp ASM_REG("$6");
                register s32 state ASM_REG("$7");
                scale = 0x1E;
                var_s4 = 1;
                state = (s32) *(void *volatile *)&arg0;
                prep_base = sp10;
                prep_clamp = 0x400;
                sp10[0] = (0 - M2C_FIELD(state, u16 *, 0xC)) + 0x400;
                do {
                    temp_v1_2 = (void *)(((var_s4 << 0x10) >> 0xF) + (s32)prep_base);
                    temp_v0_2 = M2C_FIELD(temp_v1_2, u16 *, -2) + 0xCC;
                    M2C_FIELD(temp_v1_2, s16 *, 0) = temp_v0_2;
                    if (temp_v0_2 >= 0x401) {
                        M2C_FIELD(temp_v1_2, s16 *, 0) = prep_clamp;
                    }
                    temp_v0 = var_s4 + 1;
                    var_s4 = temp_v0;
                } while (temp_v0 < 0xA);
                var_s4 = 0;
                state = (s32) sp10;
                sp190 = (void *) state;
                temp_s7 = scale;
                do {
                    var_s3 = 0;
                    temp_v0_6 = var_s4 << 0x10;
                    temp_outer = temp_v0_6 >> 0x10;
                    state = (s32) sp190;
                    {
                        register s32 scaled_outer ASM_REG("$2");
                        scaled_outer = temp_outer << 1;
                        temp_s6 = (s16 *) (scaled_outer + state);
                    }
loop_9:
                    temp_s1 = var_s3 << 0x10;
                    state = temp_s7 * func_800644B8(*temp_s6);
                    temp_s1 >>= 0x10;
                    temp_trig = (temp_s1 * 6) + (temp_outer * 0x24);
                    temp_s2 = (s8 *)sp28 + temp_trig;
                    {
                        register s32 trig_v0 ASM_REG("$2");
                        trig_v0 = state >> 0xC;
                        M2C_FIELD(temp_s2, s16 *, 4) = (s16) trig_v0;
                    }
                    temp_s0 = temp_s1 << 2;
                    state = temp_s7 * func_80064584(*temp_s6);
                    temp_s0 += temp_s1;
                    temp_s0 += temp_s0 << 4;
                    temp_s0 <<= 2;
                    temp_s0 += temp_s1;
                    temp_s0 <<= 1;
                    temp_s1 = state >> 0xC;
                    state = (s16) temp_s1 * func_80064584(temp_s0);
                    {
                        register s32 trig_v0 ASM_REG("$2");
                        trig_v0 = state >> 0xC;
                        M2C_FIELD(temp_s2, s16 *, 0) = (s16) trig_v0;
                    }
                    temp_v0_4 = var_s3 + 1;
                    var_s3 = temp_v0_4;
                    state = (s16) temp_s1 * func_800644B8(temp_s0);
                    {
                        register s32 trig_v1 ASM_REG("$3");
                        trig_v1 = state >> 0xC;
                        M2C_FIELD(temp_s2, s16 *, 2) = (s16) trig_v1;
                    }
                    if (temp_v0_4 < 6) {
                        goto loop_9;
                    }
                    temp_v0_3 = var_s4 + 1;
                    var_s4 = temp_v0_3;
                } while (temp_v0_3 < 0xA);
                state = (s32) *(void *volatile *)&arg0;
                temp_v0_5 = M2C_FIELD(state, u16 *, 0xC) + 0x64;
                M2C_FIELD(state, u16 *, 0xC) = temp_v0_5;
                if ((s16) temp_v0_5 >= 0x800) {
                    M2C_FIELD(state, u16 *, 0xC) = 0x800U;
                }
                var_s2 = 0;
                state = (s32) *(void *volatile *)&arg0;
                if (M2C_FIELD(state, s16 *, 8) < 0x16) {
                    temp_tail = M2C_FIELD(state, u16 *, 6);
                    M2C_FIELD(state, u16 *, 0xC) = 0U;
                    M2C_FIELD(state, u16 *, 6) = temp_tail + 1;
                    func_80174DC0();
                    return;
                }
                goto block_26;
            }
            var_v0 = &D_801749A8;
            goto block_27;
        }
        goto block_26;
    }
    {
    register s32 scale ASM_REG("$4");
    register s16 *prep_base ASM_REG("$5");
    register s32 prep_clamp ASM_REG("$6");
    register s32 state ASM_REG("$7");
    scale = 0x1E;
    var_s4 = 8;
    state = (s32) *(void *volatile *)&arg0;
    prep_base = sp10;
    prep_clamp = -0x400;
    sp10[9] = (0 - M2C_FIELD(state, u16 *, 0xC)) + 0x400;
    do {
        temp_v1_3 = (void *)(((var_s4 << 0x10) >> 0xF) + (s32)prep_base);
        temp_v0_7 = M2C_FIELD(temp_v1_3, u16 *, 2) - 0xCC;
        M2C_FIELD(temp_v1_3, s16 *, 0) = temp_v0_7;
        if (temp_v0_7 < -0x400) {
            M2C_FIELD(temp_v1_3, s16 *, 0) = prep_clamp;
        }
        temp_dec = var_s4 - 1;
        var_s4 = temp_dec;
    } while ((temp_dec << 0x10) != 0);
    var_s4 = 0;
    state = (s32) sp10;
    sp194 = (void *) state;
    temp_s7 = scale;
    do {
        var_s3 = 0;
        temp_v0_6 = var_s4 << 0x10;
        temp_outer = temp_v0_6 >> 0x10;
        state = (s32) sp194;
        {
            register s32 scaled_outer ASM_REG("$2");
            scaled_outer = temp_outer << 1;
            temp_s6_2 = (s16 *) (scaled_outer + state);
        }
loop_22:
        temp_s1_2 = var_s3 << 0x10;
        state = temp_s7 * func_800644B8(*temp_s6_2);
        temp_s1_2 >>= 0x10;
        temp_trig = (temp_s1_2 * 6) + (temp_outer * 0x24);
        temp_s2_2 = (s8 *)sp28 + temp_trig;
        {
            register s32 trig_v0 ASM_REG("$2");
            trig_v0 = state >> 0xC;
            M2C_FIELD(temp_s2_2, s16 *, 4) = (s16) trig_v0;
        }
        temp_s0_2 = temp_s1_2 << 2;
        state = temp_s7 * func_80064584(*temp_s6_2);
        temp_s0_2 += temp_s1_2;
        temp_s0_2 += temp_s0_2 << 4;
        temp_s0_2 <<= 2;
        temp_s0_2 += temp_s1_2;
        temp_s0_2 <<= 1;
        temp_s1_2 = state >> 0xC;
        state = (s16) temp_s1_2 * func_80064584(temp_s0_2);
        {
            register s32 trig_v0 ASM_REG("$2");
            trig_v0 = state >> 0xC;
            M2C_FIELD(temp_s2_2, s16 *, 0) = (s16) trig_v0;
        }
        temp_v0_9 = var_s3 + 1;
        var_s3 = temp_v0_9;
        state = (s16) temp_s1_2 * func_800644B8(temp_s0_2);
        {
            register s32 trig_v1 ASM_REG("$3");
            trig_v1 = state >> 0xC;
            M2C_FIELD(temp_s2_2, s16 *, 2) = (s16) trig_v1;
        }
        if (temp_v0_9 < 6) {
            goto loop_22;
        }
        temp_v0_8 = var_s4 + 1;
        var_s4 = temp_v0_8;
    } while (temp_v0_8 < 0xA);
    state = (s32) *(void *volatile *)&arg0;
    temp_v0_10 = M2C_FIELD(state, u16 *, 0xC) + 0x64;
    M2C_FIELD(state, u16 *, 0xC) = temp_v0_10;
    if ((s16) temp_v0_10 >= 0x800) {
        M2C_FIELD(state, u16 *, 0xC) = 0x800U;
    }
    var_s2 = 0;
    }
block_26:
    var_v0 = &D_801749A8;
block_27:
    temp_s5 = (s32)sp28;
    ASM_USE_NV(temp_s5);
    var_s3_3 = 0;
    do {
        {
            register s32 temp_shift ASM_REG("$2");
            temp_shift = var_s2 << 0x10;
            temp_s4 = (void *) (temp_shift >> 0x10);
        }
loop_29:
        temp_v0_12 = func_8003FC64(0x212);
        if (temp_v0_12 == NULL) {
            goto next_29;
        }
        ASM_SCHED_BARRIER();
        temp_s1_3 = temp_v0_12 + 0x20;
        M2C_FIELD(temp_s1_3, s16 *, 0x1A) = 1;
        M2C_FIELD(temp_s1_3, s16 *, 0x1C) = 1;
        M2C_FIELD(temp_v0_12, M2C_UNK **, 0x10) = var_v0;
        func_8004491C(temp_v0_12, &D_80174954);
        temp_a0 = M2C_FIELD(temp_v0_12, void **, 0xC);
        M2C_FIELD(temp_a0, s16 *, 0x10) = 0x20;
        M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC);
        temp_v1_4 = M2C_FIELD(temp_v0_12, void **, 8);
        M2C_FIELD(temp_v1_4, s32 *, 0) = (s32) M2C_FIELD(object_origin, s32 *, 0);
        M2C_FIELD(temp_v1_4, s32 *, 4) = (s32) M2C_FIELD(object_origin, s32 *, 4);
        M2C_FIELD(temp_v1_4, s32 *, 8) = (s32) M2C_FIELD(object_origin, s32 *, 8);
        temp_a0 = M2C_FIELD(temp_v0_12, void **, 0xC);
        M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x1000;
        color = *(void *volatile *)&arg2;
        M2C_FIELD(temp_a0, u8 *, 0xC) = (u8) M2C_FIELD(color, u8 *, 0xC);
        M2C_FIELD(temp_a0, u8 *, 0xD) = (u8) M2C_FIELD(color, u8 *, 0xD);
        M2C_FIELD(temp_a0, u8 *, 0xE) = (u8) M2C_FIELD(color, u8 *, 0xE);
        temp_a1 = var_s3_3 << 0x10;
        temp_a1 >>= 0x10;
        temp_a0_3 = (s32) temp_s4 * 6;
        temp_v0_13 = (s8 *)sp28 + (temp_a0_3 + ((temp_a1 + 1) * 0x24));
        M2C_FIELD(temp_s1_3, u16 *, 0x64) = (u16) M2C_FIELD(temp_v0_13, u16 *, 0);
        M2C_FIELD(temp_s1_3, u16 *, 0x66) = (u16) M2C_FIELD(temp_v0_13, u16 *, 2);
        M2C_FIELD(temp_s1_3, u16 *, 0x68) = (u16) M2C_FIELD(temp_v0_13, u16 *, 4);
        temp_a0_4 = (s8 *)sp28 + (temp_a0_3 + (temp_a1 * 0x24));
        M2C_FIELD(temp_s1_3, u16 *, 0x6A) = (u16) M2C_FIELD(temp_a0_4, u16 *, 0);
        M2C_FIELD(temp_s1_3, u16 *, 0x6C) = (u16) M2C_FIELD(temp_a0_4, u16 *, 2);
        M2C_FIELD(temp_s1_3, u16 *, 0x6E) = (u16) M2C_FIELD(temp_a0_4, u16 *, 4);
next_29:
        var_v0_4 = var_s3_3 + 1;
        var_s3_3 = var_v0_4;
        if (var_v0_4 < 9) {
            goto loop_29;
        }
        var_s3_3 = 0;
        temp_v0_11 = var_s2 + 1;
        var_s2 = temp_v0_11;
    } while (temp_v0_11 < 6);
    var_s3_4 = 1;
    second_global = &D_801749A8;
    temp_s6 = (s16 *)sp28;
loop_34:
    var_s2_2 = 0;
    {
        register s32 signed_outer ASM_REG("$3");
        register s32 scaled_outer ASM_REG("$2");
        signed_outer = var_s3_4;
        scaled_outer = (signed_outer << 3) + signed_outer;
        temp_s5 = scaled_outer << 2;
    }
    temp_s4 = (s8 *)temp_s6 + temp_s5;
loop_35:
    temp_v0_14 = func_8003FC64(0x212);
    if (temp_v0_14 == NULL) {
        goto next_35;
    }
    ASM_SCHED_BARRIER();
    temp_s1_4 = temp_v0_14 + 0x20;
    M2C_FIELD(temp_s1_4, s16 *, 0x1A) = 1;
    M2C_FIELD(temp_s1_4, s16 *, 0x1C) = 1;
    M2C_FIELD(temp_v0_14, M2C_UNK **, 0x10) = second_global;
    func_8004491C(temp_v0_14, &D_80174954);
    temp_a0_5 = M2C_FIELD(temp_v0_14, void **, 0xC);
    {
        register u16 object_flags ASM_REG("$3");
        register s32 object_width ASM_REG("$2");
        object_flags = M2C_FIELD(temp_a0_5, u16 *, 0x14);
        object_width = 0x20;
        M2C_FIELD(temp_a0_5, s16 *, 0x10) = object_width;
        object_flags |= 0xC;
        M2C_FIELD(temp_a0_5, u16 *, 0x14) = object_flags;
    }
    temp_v1_5 = M2C_FIELD(temp_v0_14, void **, 8);
    M2C_FIELD(temp_v1_5, s32 *, 0) = (s32) M2C_FIELD(object_origin, s32 *, 0);
    M2C_FIELD(temp_v1_5, s32 *, 4) = (s32) M2C_FIELD(object_origin, s32 *, 4);
    M2C_FIELD(temp_v1_5, s32 *, 8) = (s32) M2C_FIELD(object_origin, s32 *, 8);
    temp_a0_6 = M2C_FIELD(temp_v0_14, void **, 0xC);
    M2C_FIELD(temp_a0_6, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(temp_a0_6, s16 *, 0x1C) = 0x1000;
    color = *(void *volatile *)&arg2;
    M2C_FIELD(temp_a0_6, u8 *, 0xC) = (u8) M2C_FIELD(color, u8 *, 0xC);
    M2C_FIELD(temp_a0_6, u8 *, 0xD) = (u8) M2C_FIELD(color, u8 *, 0xD);
    M2C_FIELD(temp_a0_6, u8 *, 0xE) = (u8) M2C_FIELD(color, u8 *, 0xE);
    if (var_s2_2 != 5) {
        temp_v0_15 = (s8 *)temp_s6 + (((var_s2_2 + 1) * 6) + temp_s5);
        M2C_FIELD(temp_s1_4, u16 *, 0x64) = (u16) M2C_FIELD(temp_v0_15, u16 *, 0);
        M2C_FIELD(temp_s1_4, u16 *, 0x66) = (u16) M2C_FIELD(temp_v0_15, u16 *, 2);
        M2C_FIELD(temp_s1_4, u16 *, 0x68) = (u16) M2C_FIELD(temp_v0_15, u16 *, 4);
        goto block_second_triple;
    }
    M2C_FIELD(temp_s1_4, u16 *, 0x64) = (u16) M2C_FIELD(temp_s4, u16 *, 0);
    M2C_FIELD(temp_s1_4, u16 *, 0x66) = (u16) M2C_FIELD(temp_s4, u16 *, 2);
    M2C_FIELD(temp_s1_4, u16 *, 0x68) = (u16) M2C_FIELD(temp_s4, u16 *, 4);
block_second_triple:
    temp_v0_16 = (s8 *)temp_s6 + ((var_s2_2 * 6) + temp_s5);
    M2C_FIELD(temp_s1_4, u16 *, 0x6A) = (u16) M2C_FIELD(temp_v0_16, u16 *, 0);
    M2C_FIELD(temp_s1_4, u16 *, 0x6C) = (u16) M2C_FIELD(temp_v0_16, u16 *, 2);
    M2C_FIELD(temp_s1_4, u16 *, 0x6E) = (u16) M2C_FIELD(temp_v0_16, u16 *, 4);
next_35:
    var_v0_5 = var_s2_2 + 1;
    var_s2_2 = var_v0_5;
    if (var_v0_5 < 6) {
        goto loop_35;
    }
    temp_v0_17 = var_s3_4 + 1;
    var_s3_4 = temp_v0_17;
    if (temp_v0_17 < 9) {
        goto loop_34;
    }
    {
        register void *state ASM_REG("$7");
        state = *(void *volatile *)&arg0;
        temp_v0_18 = (u16) M2C_FIELD(state, s16 *, 8) - 1;
        M2C_FIELD(state, s16 *, 8) = temp_v0_18;
        if ((temp_v0_18 << 0x10) <= 0) {
            M2C_FIELD(state, u16 *, -2) = (u16) (M2C_FIELD(state, u16 *, -2) | 0x8000);
            D_800814A0 = D_800814A0 | 0x8000;
        }
        return;
    }
}
