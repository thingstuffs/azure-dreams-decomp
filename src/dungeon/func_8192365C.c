#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800247B8();      /* extern */
M2C_UNK func_80024AEC();      /* extern */
M2C_UNK func_80024D34();      /* extern */
void func_80025190() __attribute__((noreturn)); /* extern */
void func_800251F4() __attribute__((noreturn)); /* extern */
void func_800252C4() __attribute__((noreturn)); /* extern */
void func_800255B0() __attribute__((noreturn)); /* extern */
M2C_UNK func_80047784();         /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 func_800A4778();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800D4AB0();      /* extern */
extern u8 D_80025B38[9];
extern s16 D_80025B60;
extern s32 D_800814A0;
extern u8 D_800DDC40[];


typedef struct S_80024E5C_0_pre {
    u16 unk_00;
} S_80024E5C_0_pre;   /* the 0x2 bytes before arg0 in func_80024E5C, addressed as arg0[-1] */

typedef struct S_80024E5C_0 {
    u8 pad_00[0x56];
    u16 unk_56;
    union { u16 u; s16 s; } unk_58;   /* accessed as both */
    union { u16 u; s16 s; } unk_5A;   /* accessed as both */
    u16 unk_5C;
    u8 pad_5E[0x2];
    s16 unk_60;
    s16 unk_62;
    u8 pad_64[0xE];
    u16 unk_72;
    u8 pad_74[0x14];
    void * unk_88;
    void * unk_8C;
    u8 pad_90[0x8];
    s32 unk_98;
    s32 unk_9C;
    s32 unk_A0;
} S_80024E5C_0;   /* arg0 in func_80024E5C */

typedef struct S_80024E5C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    union { s8 s; u8 u; } unk_0C;   /* accessed as both */
    union { s8 s; u8 u; } unk_0D;   /* accessed as both */
    union { s8 s; u8 u; } unk_0E;   /* accessed as both */
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_80024E5C_1;   /* arg2 in func_80024E5C */

typedef struct S_80024E5C_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80024E5C_2;   /* arg1 in func_80024E5C */

typedef struct S_80024E5C_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_80024E5C_3;   /* temp_a1 in func_80024E5C */

typedef struct S_80024E5C_4_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_80024E5C_4_pre;   /* the 0x18 bytes before ((S_80024E5C_0 *)arg0)->unk_88 in func_80024E5C, addressed as ((S_80024E5C_0 *)arg0)->unk_88[-1] */

typedef struct S_80024E5C_4 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_80024E5C_4;   /* ((S_80024E5C_0 *)arg0)->unk_88 in func_80024E5C */

typedef struct S_80024E5C_5 {
    u8 pad_00[0x86];
    s16 unk_86;
} S_80024E5C_5;   /* ((S_80024E5C_0 *)arg0)->unk_8C in func_80024E5C */

void func_80024E5C(void *arg0, void *arg1, void *arg2) {
    register s32 temp_v0_3 ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
    s16 temp_v0_8;
    u8 *var_v0;
    register s32 var_v0_2 ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
    s16 temp_a0;
    s16 temp_v0_10;
    s16 temp_v0_11;
    s16 temp_v0_12;
    s16 temp_v0_13;
    s16 temp_v0_5;
    s16 temp_v1_3;
    s16 var_s0_2;
    s16 var_s0_3;
    s16 var_s0_4;
    s16 var_s0_5;
    s16 var_s0_6;
    s32 temp_a0_2;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_a2;
    s32 current_x;
    s32 temp_v0_14;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_s0;
    s32 var_v0_3;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_4;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v0_9;
    u16 temp_v1;
    u16 initial_state;
    u16 var_v1;
    u8 effect_id;
    void *temp_a1;

    initial_state = ((S_80024E5C_0 *)arg0)->unk_58.u;
    D_80025B60 = 1;
    if (initial_state < 3U) {
        ((S_80024E5C_1 *)arg2)->unk_0E.s = 0x3C;
        ((S_80024E5C_1 *)arg2)->unk_0D.s = 0x3C;
        ((S_80024E5C_1 *)arg2)->unk_0C.s = 0x3C;
        temp_v1 = ((S_80024E5C_0 *)arg0)->unk_72;
        temp_v0 = temp_v1 + 1;
        ((S_80024E5C_0 *)arg0)->unk_72 = temp_v0;
        if (!(temp_v0 & 7)) {
            ((S_80024E5C_0 *)arg0)->unk_72 = (u16) (temp_v1 + 2);
        }
        if (((S_80024E5C_0 *)arg0)->unk_72 & 1) {
            ((S_80024E5C_1 *)arg2)->unk_0C.u = 0x80;
        }
        if (((S_80024E5C_0 *)arg0)->unk_72 & 2) {
            ((S_80024E5C_1 *)arg2)->unk_0D.u = 0x80;
        }
        if (((S_80024E5C_0 *)arg0)->unk_72 & 4) {
            ((S_80024E5C_1 *)arg2)->unk_0E.u = 0x80;
        }
    }
    if (((S_80024E5C_0 *)arg0)->unk_58.s == 0) {
        temp_v0_2 = ((S_80024E5C_0 *)arg0)->unk_5A.u;
        ((S_80024E5C_0 *)arg0)->unk_5A.u = (u16) (temp_v0_2 + 1);
        if ((s16) temp_v0_2 >= 6) {
            effect_id = D_80025B38[0];
            ((S_80024E5C_1 *)arg2)->unk_2C = D_80025B38;
            func_80047784(arg2, effect_id, 0);
            ((S_80024E5C_0 *)arg0)->unk_5A.u = 0U;
            ((S_80024E5C_0 *)arg0)->unk_58.u = (u16) (((S_80024E5C_0 *)arg0)->unk_58.u + 1);
            ((S_80024E5C_2 *)arg1)->unk_08.at02.v = (u16) (((S_80024E5C_2 *)arg1)->unk_08.at02.v - 0x5A);
        }
    }
    var_s0 = ((S_80024E5C_0 *)arg0)->unk_58.s;
    if (var_s0 == 1) {
        if ((func_800A4778(((S_80024E5C_2 *)arg1)->unk_00.at02.v, ((S_80024E5C_2 *)arg1)->unk_04.at02.v, (s16) ((S_80024E5C_2 *)arg1)->unk_08.at02.v, ((S_80024E5C_0 *)arg0)->unk_88) << 0x10) == 0) {
            if (((S_80024E5C_0 *)arg0)->unk_60 != 0) {
                temp_a1 = ((S_80024E5C_4_pre *)(((S_80024E5C_0 *)arg0)->unk_88))[-1].unk_00;
                ((S_80024E5C_1 *)arg2)->unk_06 = 8;
                if (((S_80024E5C_0 *)arg0)->unk_5A.s == 0) {
                    temp_v0_3 = ((S_80024E5C_3 *)temp_a1)->unk_00.at02.v;
                    temp_v0_3 -= ((S_80024E5C_2 *)arg1)->unk_00.at02u.v;
                    var_a0 = temp_v0_3;
                    if (temp_v0_3 < 0) {
                        var_a0 = 0 - var_a0;
                    }
                    if (var_a0 < 0) {
                        var_a0 += 0x3F;
                    }
                    temp_v0_3 = ((S_80024E5C_3 *)temp_a1)->unk_04.at02.v;
                    temp_v0_3 -= ((S_80024E5C_2 *)arg1)->unk_04.at02u.v;
                    var_v0_2 = temp_v0_3;
                    if (temp_v0_3 < 0) {
                        var_v0_2 = 0 - var_v0_2;
                    }
                    ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
                    if (var_v0_2 < 0) {
                        var_v0_2 += 0x3F;
                    }
                    var_v0_2 = (var_a0 >> 6) + (var_v0_2 >> 6);
                    ((S_80024E5C_0 *)arg0)->unk_5A.u = (u16) (((s32) (var_v0_2 << 0x10) >> 0xF) + 0xB);
                }
                var_v0 = D_800DDC40;
                temp_a0 = (s16) ((S_80024E5C_0 *)arg0)->unk_5A.u;
                temp_a2 = ((S_80024E5C_3 *)temp_a1)->unk_08 - (((u8) *(((S_80024E5C_4 *)(((S_80024E5C_0 *)arg0)->unk_88))->unk_13 + var_v0) >> 1) << 0x10);
                var_v0_3 = temp_a0 < 0xE;
                ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
                temp_v1_2 = ((S_80024E5C_3 *)temp_a1)->unk_00.at00.v;
                temp_a1_2 = ((S_80024E5C_3 *)temp_a1)->unk_04.at00.v;
                if (var_v0_3 == 0) {
                    current_x = ((S_80024E5C_2 *)arg1)->unk_00.at00.v;
                    ((S_80024E5C_2 *)arg1)->unk_0C = (s32) ((temp_v1_2 - current_x) / (s32) (temp_a0 - 0xB));
                    ((S_80024E5C_2 *)arg1)->unk_10 = (s32) ((s32) (temp_a1_2 - ((S_80024E5C_2 *)arg1)->unk_04.at00.v) / (s32) ((s16) ((S_80024E5C_0 *)arg0)->unk_5A.u - 0xB));
                    ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
                    temp_v1_2 = ((S_80024E5C_2 *)arg1)->unk_08.at00.v;
                    temp_v0_3 = ((S_80024E5C_0 *)arg0)->unk_5A.s;
                    temp_v1_2 = temp_a2 - temp_v1_2;
                    temp_v0_3 -= 0xB;
                    ASM_USE(temp_v1_2);   /* MATCH pin: retail basic-block layout depends on it */
                    ASM_TAILSLOT_PIN(temp_v0_3);   /* MATCH pin: load-bearing for the whole function shape */
                    func_80025190(temp_a0, temp_a1_2, temp_a2);
                    return;
                }
                ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
                if (temp_a0 >= 0xB) {
                    current_x = ((S_80024E5C_2 *)arg1)->unk_00.at00.v;
                    ((S_80024E5C_2 *)arg1)->unk_0C = (s32) ((temp_v1_2 - current_x) / (s32) (temp_a0 - 9));
                    ((S_80024E5C_2 *)arg1)->unk_10 = (s32) ((s32) (temp_a1_2 - ((S_80024E5C_2 *)arg1)->unk_04.at00.v) / (s32) ((s16) ((S_80024E5C_0 *)arg0)->unk_5A.u - 9));
                    ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
                    temp_v1_2 = ((S_80024E5C_2 *)arg1)->unk_08.at00.v;
                    temp_v0_3 = ((S_80024E5C_0 *)arg0)->unk_5A.s;
                    temp_v1_2 = temp_a2 - temp_v1_2;
                    temp_v0_3 -= 9;
                    ASM_USE(temp_v1_2);   /* MATCH pin: retail basic-block layout depends on it */
                    ASM_TAILSLOT_PIN(temp_v0_3);   /* MATCH pin: load-bearing for the whole function shape */
                    func_80025190(temp_a0, temp_a1_2, temp_a2);
                    return;
                }
                ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
                if (temp_a0 >= 5) {
                    current_x = ((S_80024E5C_2 *)arg1)->unk_00.at00.v;
                    ((S_80024E5C_2 *)arg1)->unk_0C = (s32) ((temp_v1_2 - current_x) / (s32) (temp_a0 - 4));
                    ((S_80024E5C_2 *)arg1)->unk_10 = (s32) ((s32) (temp_a1_2 - ((S_80024E5C_2 *)arg1)->unk_04.at00.v) / (s32) ((s16) ((S_80024E5C_0 *)arg0)->unk_5A.u - 4));
                    ((S_80024E5C_2 *)arg1)->unk_14 = (s32) ((s32) (temp_a2 - ((S_80024E5C_2 *)arg1)->unk_08.at00.v) / (s32) ((s16) ((S_80024E5C_0 *)arg0)->unk_5A.u - 4));
                    func_800251F4(temp_a0, temp_a1_2, temp_a2);
                    return;
                }
                ((S_80024E5C_2 *)arg1)->unk_0C = (s32) ((s32) (temp_v1_2 - ((S_80024E5C_2 *)arg1)->unk_00.at00.v) / temp_a0);
                ((S_80024E5C_2 *)arg1)->unk_10 = (s32) ((s32) (temp_a1_2 - ((S_80024E5C_2 *)arg1)->unk_04.at00.v) / (s16) ((S_80024E5C_0 *)arg0)->unk_5A.u);
                ((S_80024E5C_2 *)arg1)->unk_14 = (s32) ((s32) (temp_a2 - ((S_80024E5C_2 *)arg1)->unk_08.at00.v) / (s16) ((S_80024E5C_0 *)arg0)->unk_5A.u);
                ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                temp_a0_2 = ((S_80024E5C_2 *)arg1)->unk_10;
                temp_a1_3 = ((S_80024E5C_2 *)arg1)->unk_14;
                ((S_80024E5C_2 *)arg1)->unk_00.at00.v = (s32) (((S_80024E5C_2 *)arg1)->unk_00.at00.v + ((S_80024E5C_2 *)arg1)->unk_0C);
                ((S_80024E5C_2 *)arg1)->unk_04.at00.v = (s32) (((S_80024E5C_2 *)arg1)->unk_04.at00.v + temp_a0_2);
                ((S_80024E5C_2 *)arg1)->unk_08.at00.v = (s32) (((S_80024E5C_2 *)arg1)->unk_08.at00.v + temp_a1_3);
                temp_v0_4 = ((S_80024E5C_0 *)arg0)->unk_5A.u - 1;
                ((S_80024E5C_0 *)arg0)->unk_5A.u = temp_v0_4;
                if ((temp_v0_4 << 0x10) == 0) {
                    ((S_80024E5C_0 *)arg0)->unk_58.u = 2U;
                    ((S_80024E5C_0 *)arg0)->unk_62 = 6;
                    ((S_80024E5C_0 *)arg0)->unk_5A.u = 0U;
                    ((S_80024E5C_2 *)arg1)->unk_14 = 0;
                    ((S_80024E5C_2 *)arg1)->unk_10 = 0;
                    ((S_80024E5C_2 *)arg1)->unk_0C = 0;
                    ((S_80024E5C_0 *)arg0)->unk_56 = 0x1E;
                    func_800252C4(temp_a0_2, temp_a1_3, temp_a2);
                    return;
                }
                goto block_38;
            }
            ((S_80024E5C_0 *)arg0)->unk_5A.u = 0xAU;
            ((S_80024E5C_0 *)arg0)->unk_5C = (u16) (((S_80024E5C_0 *)arg0)->unk_5C - 1);
            ((S_80024E5C_2 *)arg1)->unk_00.at00.v = (s32) (((S_80024E5C_2 *)arg1)->unk_00.at00.v + ((S_80024E5C_0 *)arg0)->unk_98);
            ((S_80024E5C_2 *)arg1)->unk_04.at00.v = (s32) (((S_80024E5C_2 *)arg1)->unk_04.at00.v + ((S_80024E5C_0 *)arg0)->unk_9C);
            ((S_80024E5C_2 *)arg1)->unk_08.at00.v = (s32) (((S_80024E5C_2 *)arg1)->unk_08.at00.v + ((S_80024E5C_0 *)arg0)->unk_A0);
            if ((s16) ((S_80024E5C_0 *)arg0)->unk_5C > 0) {
block_38:
                if ((s16) ((S_80024E5C_0 *)arg0)->unk_5A.u >= 5) {
                    var_s0_2 = 0;
                    do {
                        func_80024D34(arg0, arg1, arg2);
                        temp_v0_5 = var_s0_2 + 1;
                        var_s0_2 = temp_v0_5;
                    } while (temp_v0_5 < 4);
                }
                goto block_41;
            }
            goto destroy;
        }
        goto destroy;
    }
block_41:
    temp_v1_3 = (s16) ((S_80024E5C_0 *)arg0)->unk_58.u;
    if (temp_v1_3 == 2) {
        temp_v0_6 = ((S_80024E5C_0 *)arg0)->unk_5A.u + 1;
        ((S_80024E5C_0 *)arg0)->unk_5A.u = temp_v0_6;
        if ((s16) temp_v0_6 == temp_v1_3) {
            func_80024AEC(arg0, arg1, arg2);
            func_800A56E0(0x300);
        }
        if ((s16) ((S_80024E5C_0 *)arg0)->unk_5A.u >= 0xA) {
            temp_v0_7 = ((S_80024E5C_1 *)arg2)->unk_1C;
            if (temp_v0_7 != 0) {
                temp_v0_8 = temp_v0_7 - 0xC8;
                var_v1 = temp_v0_8;
                if (temp_v0_8 < 0) {
                    var_v1 = 0;
                }
                ((S_80024E5C_1 *)arg2)->unk_1C = var_v1;
                ((S_80024E5C_1 *)arg2)->unk_1E = var_v1;
            }
        }
        if ((s16) ((S_80024E5C_0 *)arg0)->unk_5A.u >= 0x1E) {
            ((S_80024E5C_0 *)arg0)->unk_56 = (u16) (((S_80024E5C_0 *)arg0)->unk_56 + 3);
            func_800247B8(arg0, arg1, arg2);
            if ((s16) ((S_80024E5C_0 *)arg0)->unk_5A.u >= 0x28) {
                func_800247B8(arg0, arg1, arg2);
            }
            if ((s16) ((S_80024E5C_0 *)arg0)->unk_5A.u >= 0x2D) {
                func_800247B8(arg0, arg1, arg2);
            }
        }
        if ((s16) ((S_80024E5C_0 *)arg0)->unk_5A.u >= 0x32) {
            ((S_80024E5C_0 *)arg0)->unk_58.u = 3U;
            ((S_80024E5C_0 *)arg0)->unk_5A.u = 0U;
            ((S_80024E5C_1 *)arg2)->unk_14 = (u16) (((S_80024E5C_1 *)arg2)->unk_14 | 0x80);
        }
    }
    if ((s16) ((S_80024E5C_0 *)arg0)->unk_58.u == 3) {
        temp_v0_9 = ((S_80024E5C_0 *)arg0)->unk_5A.u + 1;
        ((S_80024E5C_0 *)arg0)->unk_5A.u = temp_v0_9;
        if ((s16) temp_v0_9 < 0x12) {
            var_s0_3 = 0;
            ((S_80024E5C_0 *)arg0)->unk_56 = (u16) (((S_80024E5C_0 *)arg0)->unk_56 - 3);
            do {
                func_800247B8(arg0, arg1, arg2);
                temp_v0_10 = var_s0_3 + 1;
                var_s0_3 = temp_v0_10;
            } while (temp_v0_10 < 5);
        }
        if ((s16) ((S_80024E5C_0 *)arg0)->unk_5A.u == 0x10) {
            var_s0_4 = 0;
            do {
                func_800247B8(arg0, arg1, arg2);
                temp_v0_11 = var_s0_4 + 1;
                var_s0_4 = temp_v0_11;
            } while (temp_v0_11 < 2);
        }
        var_s0_5 = 0;
        if ((s16) ((S_80024E5C_0 *)arg0)->unk_5A.u == 0x11) {
            do {
                func_800247B8(arg0, arg1, arg2);
                temp_v0_12 = var_s0_5 + 1;
                var_s0_5 = temp_v0_12;
            } while (temp_v0_12 < 3);
        }
        var_s0_6 = 0;
        if ((s16) ((S_80024E5C_0 *)arg0)->unk_5A.u == 0x12) {
            do {
                func_800247B8(arg0, arg1, arg2);
                temp_v0_13 = var_s0_6 + 1;
                var_s0_6 = temp_v0_13;
            } while (temp_v0_13 < 4);
        }
        temp_v0_14 = (s16) ((S_80024E5C_0 *)arg0)->unk_5A.u;
        var_s0 = 1;
        if (temp_v0_14 == 1) {
            func_800D4AB0(arg0, arg1, arg2);
            temp_v0_14 = ((S_80024E5C_0 *)arg0)->unk_5A.s;
        }
        if (temp_v0_14 >= 0x1B) {
            goto destroy;
        }
    }
    goto normal_return;
destroy:
    ((S_80024E5C_5 *)(((S_80024E5C_0 *)arg0)->unk_8C))->unk_86 = var_s0;
    (*(u16 *)((u8 *)arg0 + (-2))) = (u16) (((S_80024E5C_0_pre *)arg0)[-1].unk_00 | 0x8000);
    D_800814A0 |= 0x8000;
    func_800255B0();
normal_return:
    func_800478B8(arg2);
}
