#include "common.h"
#include "m2c_compat.h"

typedef struct S_8016E998_0 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x15];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0x58];
    s16 unk_74;
    s16 unk_76;
    s16 unk_78;
    s16 unk_7A;
    s16 unk_7C;
    s16 unk_7E;
    s16 unk_80;
    s16 unk_82;
    s16 unk_84;
    s16 unk_86;
    s16 unk_88;
    s16 unk_8A;
} S_8016E998_0;   /* temp_s0 in func_8016E998 */

typedef struct S_8016E998_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s8 unk_20;
} S_8016E998_1;   /* temp_v0 in func_8016E998 */

typedef struct S_8016E998_2 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_8016E998_2;   /* temp_a1 in func_8016E998 */

typedef struct S_8016E998_3 {
    s32 unk_00;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_8016E998_3;   /* temp_v1 in func_8016E998 */

typedef struct S_8016E998_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8016E998_4;   /* arg0 in func_8016E998 */

typedef struct S_8016E998_5 {
    u8 pad_00[0xC];
    s8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_8016E998_5;   /* temp_a1_3 in func_8016E998 */


void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                        /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8016E4E8;
extern void *D_80175D78;

void func_8016E998(S_8016E998_4 *arg0) {
    s32 temp_a1_2;
    s32 temp_s1;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    register s32 temp_a0_4 ASM_REG("$4");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    void *temp_a0_5;
    register s32 temp_v1_2 ASM_REG("$3");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u16 temp_v1_3;
    s32 var_s3;
    s32 var_s4;
    u16 temp_v0_2;
    M2C_UNK *temp_s7;
    void **var_s5;
    register S_8016E998_2 *temp_a1 ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    S_8016E998_5 *temp_a1_3;
    S_8016E998_0 *temp_s0;
    void *temp_v0;
    S_8016E998_3 *temp_v1;

    var_s4 = 0;
    temp_s7 = &D_8016E4E8;
    var_s5 = &D_80175D78;
    var_s3 = 0x100;
    do {
        temp_v0 = func_8003FC64(0x12);
        if (temp_v0 != NULL) {
            temp_a0_5 = temp_v0;
            ASM_KEEP(temp_a0_5);   /* MATCH pin: retail schedule: same instructions, different order without it */
            temp_s0 = temp_v0 + 0x20;
            temp_v0_8 = 0x32;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            temp_s0->unk_18 = (s16) temp_v0_8;
            temp_s0->unk_1A = (s16) temp_v0_8;
            ((S_8016E998_1 *)temp_v0)->unk_10 = temp_s7;
            func_8004491C(temp_a0_5, &D_80045340);
            temp_a1 = ((S_8016E998_1 *)temp_v0)->unk_0C;
            temp_v0_2 = temp_a1->unk_14 | 0xC;
            temp_a1->unk_14 = temp_v0_2;
            ASM_KEEP(temp_v0_2);   /* MATCH pin: retail schedule: same instructions, different order without it */
            temp_v1_3 = temp_v0_2;
            ASM_KEEP(temp_v1_3);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            temp_a1->unk_10 = 0x20;
            temp_a1->unk_14 = (u16) (temp_v1_3 | 0x80);
            temp_v1 = ((S_8016E998_1 *)temp_v0)->unk_08;
            temp_v1->unk_00 = (s32) arg0->unk_00;
            temp_v1->unk_04.at00.v = (s32) arg0->unk_04;
            temp_a1_2 = arg0->unk_08;
            temp_v1->unk_04.at02.v = (u16) (temp_v1->unk_04.at02.v - 0x440);
            temp_v1->unk_08 = temp_a1_2;
            temp_s0->unk_7E = -0x40;
            temp_s0->unk_78 = -0x40;
            temp_s0->unk_8A = 0;
            temp_s0->unk_84 = 0;
            temp_s1 = var_s4 << 8;
            temp_v0_3 = (s32) (func_80064584(var_s3, temp_a1_2) << 5) >> 0xC;
            temp_s0->unk_80 = (s16) temp_v0_3;
            temp_s0->unk_74 = (s16) temp_v0_3;
            temp_v0_4 = (s32) (func_80064584(temp_s1) << 5) >> 0xC;
            temp_s0->unk_86 = (s16) temp_v0_4;
            temp_s0->unk_7A = (s16) temp_v0_4;
            temp_v0_5 = (s32) (func_800644B8(var_s3) << 5) >> 0xC;
            temp_s0->unk_82 = (s16) temp_v0_5;
            temp_s0->unk_76 = (s16) temp_v0_5;
            temp_v0_6 = (s32) (func_800644B8(temp_s1) << 5) >> 0xC;
            temp_v1_2 = 0x40;
            temp_s0->unk_88 = (s16) temp_v0_6;
            temp_s0->unk_7C = (s16) temp_v0_6;
            temp_a1_3 = ((S_8016E998_1 *)temp_v0)->unk_0C;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            temp_v0_7 = 0x1000;
            ASM_KEEP(temp_v0_7);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            temp_a1_3->unk_0C = (s8) temp_v1_2;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            temp_a0_4 = temp_v1_2;
            temp_a1_3->unk_1E = (s16) temp_v0_7;
            temp_a1_3->unk_1C = (s16) temp_v0_7;
            temp_a1_3->unk_0D = (u8) temp_v1_2;
            temp_a1_3->unk_0E = (u8) temp_v1_2;
            ((S_8016E998_1 *)temp_v0)->unk_20 = (s8) temp_a0_4;
            temp_s0->unk_01 = (u8) temp_a1_3->unk_0D;
            temp_s0->unk_02 = (u8) temp_a1_3->unk_0E;
            *var_s5 = temp_v0;
        }
        var_s5 = (void **)((s8 *)((void **)((s8 *)var_s5 + 4)));
        var_s4 += 1;
        var_s3 += 0x100;
    } while (var_s4 < 0x10);
}

/* MECHANISM: Held global bases and caller-saved constant pins restore the 0x38
   s0-s7 prologue; split RMW names and schedule seams preserve retail copies,
   delay-slot fills, and tail store order. */
