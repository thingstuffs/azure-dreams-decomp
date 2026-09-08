#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_801749EC_0 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_801749EC_0;   /* arg0 in func_801749EC */

typedef struct S_801749EC_1_pre {
    u16 unk_00;
} S_801749EC_1_pre;   /* the 0x2 bytes before state in func_801749EC, addressed as state[-1] */

typedef struct S_801749EC_1 {
    u8 pad_00[0x6];
    u16 unk_06;
    s16 unk_08;
    u8 pad_0A[0x2];
    u16 unk_0C;
} S_801749EC_1;   /* state in func_801749EC */

typedef struct S_801749EC_2_pre {
    u16 unk_00;
} S_801749EC_2_pre;   /* the 0x2 bytes before temp_v1_2 in func_801749EC, addressed as temp_v1_2[-1] */

typedef struct S_801749EC_2 {
    s16 unk_00;
} S_801749EC_2;   /* temp_v1_2 in func_801749EC */

typedef struct S_801749EC_3 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} S_801749EC_3;   /* temp_s2 in func_801749EC */

typedef struct S_801749EC_4 {
    s16 unk_00;
    u16 unk_02;
} S_801749EC_4;   /* temp_v1_3 in func_801749EC */

typedef struct S_801749EC_5 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} S_801749EC_5;   /* temp_s2_2 in func_801749EC */

typedef struct S_801749EC_6 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x46];
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u16 unk_6A;
    u16 unk_6C;
    u16 unk_6E;
} S_801749EC_6;   /* temp_s1_3 in func_801749EC */

typedef struct S_801749EC_7 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_801749EC_7;   /* temp_v0_12 in func_801749EC */

typedef struct S_801749EC_8 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_801749EC_8;   /* temp_a0 in func_801749EC */

typedef struct S_801749EC_9 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801749EC_9;   /* temp_v1_4 in func_801749EC */

typedef struct S_801749EC_10 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801749EC_10;   /* object_origin in func_801749EC */

typedef struct S_801749EC_11 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_801749EC_11;   /* color in func_801749EC */

typedef struct S_801749EC_12 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_801749EC_12;   /* temp_v0_13 in func_801749EC */

typedef struct S_801749EC_13 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_801749EC_13;   /* temp_a0_4 in func_801749EC */

typedef struct S_801749EC_14 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x46];
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u16 unk_6A;
    u16 unk_6C;
    u16 unk_6E;
} S_801749EC_14;   /* temp_s1_4 in func_801749EC */

typedef struct S_801749EC_15 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_801749EC_15;   /* temp_v0_14 in func_801749EC */

typedef struct S_801749EC_16 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_801749EC_16;   /* temp_a0_5 in func_801749EC */

typedef struct S_801749EC_17 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801749EC_17;   /* temp_v1_5 in func_801749EC */

typedef struct S_801749EC_18 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_801749EC_18;   /* temp_a0_6 in func_801749EC */

typedef struct S_801749EC_19 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_801749EC_19;   /* temp_v0_15 in func_801749EC */

typedef struct S_801749EC_20 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_801749EC_20;   /* temp_s4 in func_801749EC */

typedef struct S_801749EC_21 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_801749EC_21;   /* temp_v0_16 in func_801749EC */


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
    s16 *temp_s6;
    s16 *temp_s6_2;
    s16 temp_v0;
    s16 temp_v0_11;
    s16 temp_v0_17;
    s16 temp_v0_18;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_7;
    s16 temp_v0_8;
    s16 temp_v0_9;
    s16 temp_dec;
    s16 temp_v1;
    s16 var_s2;
    s16 var_s2_2;
    register s16 var_s3 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s16 var_s3_3 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 var_s3_4;
    s16 var_s4;
    s16 var_v0_4;
    s16 var_v0_5;
    s32 temp_a0_3;
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s5;
    s32 temp_s7;
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
    register void *temp_a0_6 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *temp_s1_3 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    register void *temp_s1_4 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s4;
    register void *color ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *temp_v0_12;
    void *temp_v0_13;
    void *temp_v0_14;
    void *temp_v0_15;
    void *temp_v0_16;
    void *temp_v1_2;
    void *temp_v1_3;
    void *temp_v1_4;
    void *temp_v1_5;
    register M2C_UNK *second_global;

    (void)&arg0;
    object_origin = arg1;
    temp_v1 = ((S_801749EC_0 *)arg0)->unk_06;
    if (temp_v1 != 1) {
        var_s2 = 0;
        if (temp_v1 < 2) {
            if (temp_v1 == 0) {
                register s32 scale ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                s16 *prep_base;
                s32 prep_clamp;
                register s32 state ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                scale = 0x1E;
                var_s4 = 1;
                state = (s32) *(void *volatile *)&arg0;
                prep_base = sp10;
                prep_clamp = 0x400;
                sp10[0] = (0 - ((S_801749EC_1 *)state)->unk_0C) + 0x400;
                do {
                    temp_v1_2 = (void *)(((var_s4 << 0x10) >> 0xF) + (s32)prep_base);
                    temp_v0_2 = ((S_801749EC_2_pre *)temp_v1_2)[-1].unk_00 + 0xCC;
                    ((S_801749EC_2 *)temp_v1_2)->unk_00 = temp_v0_2;
                    if (temp_v0_2 >= 0x401) {
                        ((S_801749EC_2 *)temp_v1_2)->unk_00 = prep_clamp;
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
                        s32 scaled_outer;
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
                        register s32 trig_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        trig_v0 = state >> 0xC;
                        ((S_801749EC_3 *)temp_s2)->unk_04 = (s16) trig_v0;
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
                        register s32 trig_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        trig_v0 = state >> 0xC;
                        ((S_801749EC_3 *)temp_s2)->unk_00 = (s16) trig_v0;
                    }
                    temp_v0_4 = var_s3 + 1;
                    var_s3 = temp_v0_4;
                    state = (s16) temp_s1 * func_800644B8(temp_s0);
                    {
                        register s32 trig_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        trig_v1 = state >> 0xC;
                        ((S_801749EC_3 *)temp_s2)->unk_02 = (s16) trig_v1;
                    }
                    if (temp_v0_4 < 6) {
                        goto loop_9;
                    }
                    temp_v0_3 = var_s4 + 1;
                    var_s4 = temp_v0_3;
                } while (temp_v0_3 < 0xA);
                state = (s32) *(void *volatile *)&arg0;
                temp_v0_5 = ((S_801749EC_1 *)state)->unk_0C + 0x64;
                ((S_801749EC_1 *)state)->unk_0C = temp_v0_5;
                if ((s16) temp_v0_5 >= 0x800) {
                    ((S_801749EC_1 *)state)->unk_0C = 0x800U;
                }
                var_s2 = 0;
                state = (s32) *(void *volatile *)&arg0;
                if (((S_801749EC_1 *)state)->unk_08 < 0x16) {
                    temp_tail = ((S_801749EC_1 *)state)->unk_06;
                    ((S_801749EC_1 *)state)->unk_0C = 0U;
                    ((S_801749EC_1 *)state)->unk_06 = temp_tail + 1;
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
    register s32 scale ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 *prep_base;
    s32 prep_clamp;
    register s32 state ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    scale = 0x1E;
    var_s4 = 8;
    state = (s32) *(void *volatile *)&arg0;
    prep_base = sp10;
    prep_clamp = -0x400;
    sp10[9] = (0 - ((S_801749EC_1 *)state)->unk_0C) + 0x400;
    do {
        temp_v1_3 = (void *)(((var_s4 << 0x10) >> 0xF) + (s32)prep_base);
        temp_v0_7 = ((S_801749EC_4 *)temp_v1_3)->unk_02 - 0xCC;
        ((S_801749EC_4 *)temp_v1_3)->unk_00 = temp_v0_7;
        if (temp_v0_7 < -0x400) {
            ((S_801749EC_4 *)temp_v1_3)->unk_00 = prep_clamp;
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
            s32 scaled_outer;
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
            register s32 trig_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            trig_v0 = state >> 0xC;
            ((S_801749EC_5 *)temp_s2_2)->unk_04 = (s16) trig_v0;
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
            register s32 trig_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            trig_v0 = state >> 0xC;
            ((S_801749EC_5 *)temp_s2_2)->unk_00 = (s16) trig_v0;
        }
        temp_v0_9 = var_s3 + 1;
        var_s3 = temp_v0_9;
        state = (s16) temp_s1_2 * func_800644B8(temp_s0_2);
        {
            register s32 trig_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            trig_v1 = state >> 0xC;
            ((S_801749EC_5 *)temp_s2_2)->unk_02 = (s16) trig_v1;
        }
        if (temp_v0_9 < 6) {
            goto loop_22;
        }
        temp_v0_8 = var_s4 + 1;
        var_s4 = temp_v0_8;
    } while (temp_v0_8 < 0xA);
    state = (s32) *(void *volatile *)&arg0;
    temp_v0_10 = ((S_801749EC_1 *)state)->unk_0C + 0x64;
    ((S_801749EC_1 *)state)->unk_0C = temp_v0_10;
    if ((s16) temp_v0_10 >= 0x800) {
        ((S_801749EC_1 *)state)->unk_0C = 0x800U;
    }
    var_s2 = 0;
    }
block_26:
    var_v0 = &D_801749A8;
block_27:
    temp_s5 = (s32)sp28;
    ASM_USE_NV(temp_s5);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    var_s3_3 = 0;
    do {
        {
            s32 temp_shift;
            temp_shift = var_s2 << 0x10;
            temp_s4 = (void *) (temp_shift >> 0x10);
        }
loop_29:
        temp_v0_12 = func_8003FC64(0x212);
        if (temp_v0_12 == NULL) {
            goto next_29;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        temp_s1_3 = temp_v0_12 + 0x20;
        ((S_801749EC_6 *)temp_s1_3)->unk_1A = 1;
        ((S_801749EC_6 *)temp_s1_3)->unk_1C = 1;
        ((S_801749EC_7 *)temp_v0_12)->unk_10 = var_v0;
        func_8004491C(temp_v0_12, &D_80174954);
        temp_a0 = ((S_801749EC_7 *)temp_v0_12)->unk_0C;
        ((S_801749EC_8 *)temp_a0)->unk_10 = 0x20;
        ((S_801749EC_8 *)temp_a0)->unk_14 = (u16) (((S_801749EC_8 *)temp_a0)->unk_14 | 0xC);
        temp_v1_4 = ((S_801749EC_7 *)temp_v0_12)->unk_08;
        ((S_801749EC_9 *)temp_v1_4)->unk_00 = (s32) ((S_801749EC_10 *)object_origin)->unk_00;
        ((S_801749EC_9 *)temp_v1_4)->unk_04 = (s32) ((S_801749EC_10 *)object_origin)->unk_04;
        ((S_801749EC_9 *)temp_v1_4)->unk_08 = (s32) ((S_801749EC_10 *)object_origin)->unk_08;
        temp_a0 = ((S_801749EC_7 *)temp_v0_12)->unk_0C;
        (*(s16 *)((u8 *)temp_a0 + 0x1E)) = 0x1000;
        (*(s16 *)((u8 *)temp_a0 + 0x1C)) = 0x1000;
        color = *(void *volatile *)&arg2;
        ((S_801749EC_8 *)temp_a0)->unk_0C = (u8) ((S_801749EC_11 *)color)->unk_0C;
        ((S_801749EC_8 *)temp_a0)->unk_0D = (u8) ((S_801749EC_11 *)color)->unk_0D;
        ((S_801749EC_8 *)temp_a0)->unk_0E = (u8) ((S_801749EC_11 *)color)->unk_0E;
        temp_a1 = var_s3_3 << 0x10;
        temp_a1 >>= 0x10;
        temp_a0_3 = (s32) temp_s4 * 6;
        temp_v0_13 = (s8 *)sp28 + (temp_a0_3 + ((temp_a1 + 1) * 0x24));
        ((S_801749EC_6 *)temp_s1_3)->unk_64 = (u16) ((S_801749EC_12 *)temp_v0_13)->unk_00;
        ((S_801749EC_6 *)temp_s1_3)->unk_66 = (u16) ((S_801749EC_12 *)temp_v0_13)->unk_02;
        ((S_801749EC_6 *)temp_s1_3)->unk_68 = (u16) ((S_801749EC_12 *)temp_v0_13)->unk_04;
        temp_a0_4 = (s8 *)sp28 + (temp_a0_3 + (temp_a1 * 0x24));
        ((S_801749EC_6 *)temp_s1_3)->unk_6A = (u16) ((S_801749EC_13 *)temp_a0_4)->unk_00;
        ((S_801749EC_6 *)temp_s1_3)->unk_6C = (u16) ((S_801749EC_13 *)temp_a0_4)->unk_02;
        ((S_801749EC_6 *)temp_s1_3)->unk_6E = (u16) ((S_801749EC_13 *)temp_a0_4)->unk_04;
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
        s32 signed_outer;
        s32 scaled_outer;
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
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    temp_s1_4 = temp_v0_14 + 0x20;
    ((S_801749EC_14 *)temp_s1_4)->unk_1A = 1;
    ((S_801749EC_14 *)temp_s1_4)->unk_1C = 1;
    ((S_801749EC_15 *)temp_v0_14)->unk_10 = second_global;
    func_8004491C(temp_v0_14, &D_80174954);
    temp_a0_5 = ((S_801749EC_15 *)temp_v0_14)->unk_0C;
    {
        u16 object_flags;
        register s32 object_width ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        object_flags = ((S_801749EC_16 *)temp_a0_5)->unk_14;
        object_width = 0x20;
        ((S_801749EC_16 *)temp_a0_5)->unk_10 = object_width;
        object_flags |= 0xC;
        ((S_801749EC_16 *)temp_a0_5)->unk_14 = object_flags;
    }
    temp_v1_5 = ((S_801749EC_15 *)temp_v0_14)->unk_08;
    ((S_801749EC_17 *)temp_v1_5)->unk_00 = (s32) ((S_801749EC_10 *)object_origin)->unk_00;
    ((S_801749EC_17 *)temp_v1_5)->unk_04 = (s32) ((S_801749EC_10 *)object_origin)->unk_04;
    ((S_801749EC_17 *)temp_v1_5)->unk_08 = (s32) ((S_801749EC_10 *)object_origin)->unk_08;
    temp_a0_6 = ((S_801749EC_15 *)temp_v0_14)->unk_0C;
    (*(s16 *)((u8 *)temp_a0_6 + 0x1E)) = 0x1000;
    (*(s16 *)((u8 *)temp_a0_6 + 0x1C)) = 0x1000;
    color = *(void *volatile *)&arg2;
    ((S_801749EC_18 *)temp_a0_6)->unk_0C = (u8) ((S_801749EC_11 *)color)->unk_0C;
    ((S_801749EC_18 *)temp_a0_6)->unk_0D = (u8) ((S_801749EC_11 *)color)->unk_0D;
    ((S_801749EC_18 *)temp_a0_6)->unk_0E = (u8) ((S_801749EC_11 *)color)->unk_0E;
    if (var_s2_2 != 5) {
        temp_v0_15 = (s8 *)temp_s6 + (((var_s2_2 + 1) * 6) + temp_s5);
        ((S_801749EC_14 *)temp_s1_4)->unk_64 = (u16) ((S_801749EC_19 *)temp_v0_15)->unk_00;
        ((S_801749EC_14 *)temp_s1_4)->unk_66 = (u16) ((S_801749EC_19 *)temp_v0_15)->unk_02;
        ((S_801749EC_14 *)temp_s1_4)->unk_68 = (u16) ((S_801749EC_19 *)temp_v0_15)->unk_04;
        goto block_second_triple;
    }
    ((S_801749EC_14 *)temp_s1_4)->unk_64 = (u16) ((S_801749EC_20 *)temp_s4)->unk_00;
    ((S_801749EC_14 *)temp_s1_4)->unk_66 = (u16) ((S_801749EC_20 *)temp_s4)->unk_02;
    ((S_801749EC_14 *)temp_s1_4)->unk_68 = (u16) ((S_801749EC_20 *)temp_s4)->unk_04;
block_second_triple:
    temp_v0_16 = (s8 *)temp_s6 + ((var_s2_2 * 6) + temp_s5);
    ((S_801749EC_14 *)temp_s1_4)->unk_6A = (u16) ((S_801749EC_21 *)temp_v0_16)->unk_00;
    ((S_801749EC_14 *)temp_s1_4)->unk_6C = (u16) ((S_801749EC_21 *)temp_v0_16)->unk_02;
    ((S_801749EC_14 *)temp_s1_4)->unk_6E = (u16) ((S_801749EC_21 *)temp_v0_16)->unk_04;
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
        register void *state ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        state = *(void *volatile *)&arg0;
        temp_v0_18 = (u16) ((S_801749EC_1 *)state)->unk_08 - 1;
        ((S_801749EC_1 *)state)->unk_08 = temp_v0_18;
        if ((temp_v0_18 << 0x10) <= 0) {
            (*(u16 *)((u8 *)state + -2)) = (u16) (((S_801749EC_1_pre *)state)[-1].unk_00 | 0x8000);
            D_800814A0 = D_800814A0 | 0x8000;
        }
        return;
    }
}
