#include "common.h"
#include "m2c_compat.h"

typedef struct S_80173CEC_11 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80173CEC_11;   /* temp_v0_2 in func_80173CEC */

typedef struct S_80173CEC_12 {
    s32 unk_00;
    s32 unk_04;
} S_80173CEC_12;   /* ((S_80173CEC_11 *)temp_v0_2)->unk_08 in func_80173CEC */


typedef struct S_80173CEC_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xA];
    s16 unk_A6;
    u8 pad_A8[0x4];
    void * unk_AC;
} S_80173CEC_0;   /* arg0 in func_80173CEC */

typedef struct S_80173CEC_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x34];
    s32 unk_60;
    u8 pad_64[0x26];
    u16 unk_8A;
} S_80173CEC_1;   /* arg3 in func_80173CEC */

typedef struct S_80173CEC_2 {
    u8 unk_00;
} S_80173CEC_2;   /* &D_801742E5 in func_80173CEC */

typedef struct S_80173CEC_3 {
    u8 pad_00[0xA8];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} S_80173CEC_3;   /* temp_s0_3 in func_80173CEC */

typedef struct S_80173CEC_4 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_80173CEC_4;   /* temp_a1 in func_80173CEC */

typedef struct S_80173CEC_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80173CEC_5;   /* temp_v0_2 in func_80173CEC */

typedef struct S_80173CEC_6 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80173CEC_6;   /* arg1 in func_80173CEC */

typedef struct S_80173CEC_7 {
    u8 pad_00[0x42E0];
    s16 unk_42E0;
} S_80173CEC_7;   /* temp_a1_2 in func_80173CEC */

typedef struct S_80173CEC_8 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80173CEC_8;   /* temp_a2 in func_80173CEC */

typedef struct S_80173CEC_9 {
    u8 pad_00[0xC];
    union { s32 s; void * u; } unk_0C;   /* accessed as both */
    s32 unk_10;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80173CEC_9;   /* temp_s0 in func_80173CEC */

typedef struct S_80173CEC_10 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80173CEC_10;   /* arg2 in func_80173CEC */


/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80170858[];
void func_8003DB94();
s32 func_8003E4FC();
void func_8003F540();
void *func_8003FC64();
void func_80041588();
int func_800445E0();
s32 func_8004491C();
s32 func_800498A0();
s32 func_80069EF8();
void func_8009A028();
void func_8009A3D0();
void func_800A18E8();
s32 func_800A504C();
s32 func_800A56E0();
s32 func_800ADC4C();
s32 func_800C77D0();
void func_80173904();
extern M2C_UNK D_8003E140;
extern s32 D_8006CD58;
extern M2C_UNK D_80083160;
extern s16 D_80083228;
extern M2C_UNK D_800DCEEC;
extern M2C_UNK D_800DCF5C;
extern M2C_UNK D_8014A000;
extern M2C_UNK D_801736AC;
extern M2C_UNK D_80173B94;
extern M2C_UNK D_801742CC;
extern s32 D_801742D4[];
extern s16 D_801742E0;
extern M2C_UNK D_801742E4;
extern M2C_UNK D_801742E5;
extern s32 D_801742E8;

void func_80173CEC(S_80173CEC_0 *arg0, S_80173CEC_6 *arg1, S_80173CEC_10 *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    s16 temp_v0_4;
    s16 temp_v0_6;
    s16 var_s0;
    s16 var_s0_2;
    s32 temp_a0;
    s32 temp_a3;
    s32 temp_v0_3;
    register s32 var_v1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    u16 temp_v0;
    u16 temp_v0_5;
    u16 temp_v1_2;
    s32 temp_v0_7;
    u8 temp_v1;
    void *temp_a0_2;
    S_80173CEC_4 *temp_a1;
    register S_80173CEC_7 *temp_a1_2 ASM_REG("$5");   /* MATCH pin: retail delay-slot fill depends on it */
    register S_80173CEC_8 *temp_a2 ASM_REG("$6");   /* MATCH pin: retail schedule: same instructions, different order without it */
    S_80173CEC_9 *temp_s0;
    S_80173CEC_3 *temp_s0_3;
    S_80173CEC_5 *temp_v0_2;

    temp_s0_3 = &D_80083160;
    temp_v1 = arg0->unk_9B;
    if (temp_v1 >= 8U) {
        goto block_28;
    }
    (void)jt_keep; goto *D_80170858[(u32)(temp_v1)];
jt_c0:
    arg0->unk_9B = (u8) (arg0->unk_9B + 1);
    return;
jt_c1:
    func_80041588(&D_801742CC, &D_801742E4, 0);
    arg0->unk_A6 = 0;
    arg0->unk_9B = (u8) (arg0->unk_9B + 1);
    ((S_80173CEC_1 *)arg3)->unk_8A = (u16) ((S_80173CEC_1 *)arg3)->unk_2A;
    ((S_80173CEC_1 *)arg3)->unk_1C = (s32) (((S_80173CEC_1 *)arg3)->unk_1C & 0xFFFBFFFF);
jt_c2:
    temp_a0 = ((s32) (D_80083228 + (s16) ((S_80173CEC_1 *)arg3)->unk_2A + 0x100) >> 9) & 7;
    if ((*(u8 *)&D_801742E4) == 0) {
        goto block_6;
    }
    if (temp_a0 == 2) {
        goto block_8;
    }
block_6:
    if (temp_a0 == 2) {
        goto block_28;
    }
    ((S_80173CEC_1 *)arg3)->unk_2A = (u16) (((S_80173CEC_1 *)arg3)->unk_2A + 0x200);
    return;
block_8:
    func_80041588(&D_801742CC, &D_801742E4, 1);
    func_8003F540(0, D_8006CD58, 0x04000AD4, 0x05000CC4);
    func_8003E4FC(0x15, func_800445E0(), NULL);
    (*(s8 *)&D_801742E5) = 0;
    func_8003E4FC(0xFF, &D_8003E140, &D_801742E5);
    func_800C77D0(arg3 - 0x20, arg1, 8, 0x300);
    arg0->unk_96 = 0x10U;
    arg0->unk_9B = (u8) (arg0->unk_9B + 1);
jt_c3:
    temp_v1_2 = arg0->unk_96;
    temp_v0 = temp_v1_2 - 1;
    arg0->unk_96 = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto block_12;
    }
    temp_v0_7 = ((S_80173CEC_2 *)(&D_801742E5))->unk_00;
    arg0->unk_96 = temp_v1_2;
    if (temp_v0_7 == 0) {
        goto block_28;
    }
    arg0->unk_9B = (u8) (arg0->unk_9B + 1);
    func_800A56E0(0x300);
    return;
block_12:
    temp_a1 = (*(void **)((u8 *)(&D_800DCEEC) + func_800498A0(arg3) * 4));
    temp_s0_3->unk_A8 = (u8) (temp_s0_3->unk_A8 + ((s32) (temp_a1->unk_00 - temp_s0_3->unk_A8) / (s16) arg0->unk_96));
    temp_s0_3->unk_A9 = (u8) (temp_s0_3->unk_A9 + ((s32) (temp_a1->unk_01 - temp_s0_3->unk_A9) / (s16) arg0->unk_96));
    temp_s0_3->unk_AA = (u8) (temp_s0_3->unk_AA + ((s32) (temp_a1->unk_02 - temp_s0_3->unk_AA) / (s16) arg0->unk_96));
    return;
jt_c4:
    temp_v0_2 = func_8003FC64(0x12);
    if (temp_v0_2 == NULL) {
        goto block_28;
    }
    temp_v0_2->unk_10 = &D_80173B94;
    func_8004491C(temp_v0_2, &D_801736AC);
    temp_a3 = 0x808080;
    ASM_KEEP(temp_a3);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    arg0->unk_AC = temp_v0_2;
    temp_a0_2 = arg3;
    ((S_80173CEC_12 *)(((S_80173CEC_11 *)temp_v0_2)->unk_08))->unk_00 = (s32) arg1->unk_00;
    ASM_KEEP(temp_a0_2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ((S_80173CEC_12 *)(((S_80173CEC_11 *)temp_v0_2)->unk_08))->unk_04 = (s32) arg1->unk_04;
    temp_a2 = temp_v0_2->unk_08;
    var_v1 = arg1->unk_08;
    temp_a1_2 = (void *) 0x80170000;
    temp_a1_2->unk_42E0 = -8;
    temp_a2->unk_08 = var_v1;
    temp_s0 = temp_v0_2->unk_0C;
    temp_s0->unk_1E = 0x1000;
    temp_s0->unk_1C = 0x1000;
    temp_s0->unk_0C.s = temp_a3;
    temp_v0_3 = func_800498A0(temp_a0_2, temp_a1_2, temp_a2, temp_a3) - 1;
    var_v1 = temp_v0_3;
    ASM_KEEP(temp_v0_3);   /* MATCH pin: retail delay-slot fill depends on it */
    if ((temp_v0_3 << 0x10) >= 0) {
        goto block_16;
    }
    var_v1 = func_80069EF8() % 3;
block_16:
    func_8003DB94(temp_s0, D_801742D4[(s16) var_v1] + (s8 *) &D_8014A000, 0);
    arg2->unk_14 = (u16) (arg2->unk_14 | 0x80);
    var_s0 = 0;
    arg0->unk_96 = 0U;
    arg0->unk_9B = (u8) (arg0->unk_9B + 1);
loop_17:
    func_80173904(arg0, arg1, arg2, arg3, func_80069EF8() & 0xFFF, 0);
    temp_v0_4 = var_s0 + 1;
    var_s0 = temp_v0_4;
    if (temp_v0_4 >= 8) {
        goto block_28;
    }
    goto loop_17;
jt_c5:
    temp_v0_5 = arg0->unk_96;
    arg0->unk_96 = (u16) (temp_v0_5 + 1);
    if ((s16) temp_v0_5 >= 0x1E) {
        goto block_22;
    }
    var_s0_2 = 0;
loop_21:
    func_80173904(arg0, arg1, arg2, arg3, func_80069EF8() & 0xFFF, 0);
    temp_v0_6 = var_s0_2 + 1;
    var_s0_2 = temp_v0_6;
    if (temp_v0_6 < 8) {
        goto loop_21;
    }
block_22:
    temp_s0 = arg0->unk_AC;
    temp_s0 = temp_s0->unk_0C.u;
    if (!(temp_s0->unk_14 & 0xE000)) {
        goto block_24;
    }
    arg0->unk_9B = (u8) (arg0->unk_9B + 1);
jt_c6:
block_24:
    if (arg0->unk_9B != 6) {
        goto block_28;
    }
    if (func_800ADC4C(arg1, D_801742E8, D_801742E0, &D_800DCF5C) == 0) {
        goto block_28;
    }
    arg0->unk_96 = 0x10U;
    arg0->unk_9B = (u8) (arg0->unk_9B + 1);
    func_800A18E8(((S_80173CEC_1 *)arg3)->unk_13, 3);
    func_8009A3D0(arg2->unk_24, arg2->unk_25, 0x300);
    func_8009A028(arg3);
    temp_s0 = arg3 - 0x20;
    temp_s0->unk_10 = (s32) (temp_s0->unk_10 | 0x80000000);
    return;
jt_c7:
    ((S_80173CEC_1 *)arg3)->unk_60 = func_800A504C(arg2, arg3);
block_28:
    return;
}
