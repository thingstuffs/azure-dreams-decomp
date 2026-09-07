#include "common.h"
#include "m2c_compat.h"

typedef struct S_80C97514_12 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80C97514_12;   /* temp_v0_2 in func_80C97514 */

typedef struct S_80C97514_13 {
    u8 pad_00[0x60];
    void * unk_60;
} S_80C97514_13;   /* arg3 in func_80C97514 */

typedef struct S_80C97514_14 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80C97514_14;   /* ((S_80C97514_12 *)temp_v0_2)->unk_08 in func_80C97514 */

typedef struct S_80C97514_15 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80C97514_15;   /* ((S_80C97514_13 *)arg3)->unk_60 in func_80C97514 */


typedef struct S_80C97514_0_pre {
    u16 unk_00;
} S_80C97514_0_pre;   /* the 0x2 bytes before arg0 in func_80C97514, addressed as arg0[-1] */

typedef struct S_80C97514_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s16 unk_A4;
    u8 pad_A6[0x6];
    void * unk_AC;
} S_80C97514_0;   /* arg0 in func_80C97514 */

typedef struct S_80C97514_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x16];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x9];
    s8 unk_6D;
    u8 pad_6E[0x1C];
    u16 unk_8A;
} S_80C97514_1;   /* arg3 in func_80C97514 */

typedef struct S_80C97514_2 {
    u8 unk_00;
} S_80C97514_2;   /* &D_801753A9 in func_80C97514 */

typedef struct S_80C97514_3 {
    u8 pad_00[0xA8];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} S_80C97514_3;   /* temp_base in func_80C97514 */

typedef struct S_80C97514_4 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_80C97514_4;   /* temp_a1 in func_80C97514 */

typedef struct S_80C97514_5 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80C97514_5;   /* temp_v0_2 in func_80C97514 */

typedef struct S_80C97514_6 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80C97514_6;   /* arg1 in func_80C97514 */

typedef struct S_80C97514_7 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    union { s32 s; void * u; } unk_0C;   /* accessed as both */
    s32 unk_10;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_80C97514_7;   /* temp_s0 in func_80C97514 */

typedef struct S_80C97514_8 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80C97514_8;   /* arg2 in func_80C97514 */

typedef struct S_80C97514_9_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80C97514_9_pre;   /* the 0x14 bytes before temp_v1_3 in func_80C97514, addressed as temp_v1_3[-1] */

typedef struct S_80C97514_9 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80C97514_9;   /* temp_v1_3 in func_80C97514 */

typedef struct S_80C97514_10 {
    s32 unk_00;
} S_80C97514_10;   /* &D_800814A0 in func_80C97514 */

typedef struct S_80C97514_11 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80C97514_11;   /* temp_base2 in func_80C97514 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80170858[];
void func_8003DB94();     /* extern */
s32 func_8003E4FC(); /* extern */
void func_8003F540(); /* extern */
void *func_8003FC64();                       /* extern */
void func_80041588(); /* extern */
int func_800445E0();                           /* extern */
s32 func_8004491C();           /* extern */
void func_80047738();              /* extern */
s32 func_800498A0();                /* extern */
s32 func_80069EF8();                          /* extern */
void func_8009A028();                      /* extern */
void func_8009A3D0();             /* extern */
void func_800A18E8();                 /* extern */
s32 func_800A504C();                /* extern */
s32 func_800A56E0();                     /* extern */
s32 func_800ADC4C();     /* extern */
s32 func_800C77D0(); /* extern */
M2C_UNK func_80174724();      /* extern */
extern M2C_UNK D_8003E140;
extern M2C_UNK D_80045340;
extern s32 D_8006CD58;
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083160;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_800DCEEC;
extern M2C_UNK D_800DCF5C;
extern M2C_UNK D_8014A000;
extern M2C_UNK D_80174BE8;
extern M2C_UNK D_8017530C;
extern s16 D_80175314;
extern M2C_UNK D_80175318;
extern M2C_UNK D_801753A8;
extern M2C_UNK D_801753A9;
extern s32 D_801753AC;

void func_80C97514(void *arg0, S_80C97514_6 *arg1, S_80C97514_8 *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8 };
    s32 temp_a0;
    s32 temp_v0_3;
    u16 temp_v0;
    u16 temp_v0_5;
    u16 temp_v1_2;
    u8 temp_v1;
    u8 var_v0;
    S_80C97514_4 *temp_a1;
    S_80C97514_3 *temp_base = &D_80083160;
    S_80C97514_11 *temp_base2;
    S_80C97514_7 *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    S_80C97514_5 *temp_v0_2;
    void *temp_v0_4;
    void *temp_v1_3;

    temp_v1 = ((S_80C97514_0 *)arg0)->unk_9B;
    if (temp_v1 >= 9U) {
        goto block_27;
    }
    (void)jt_keep; goto *D_80170858[(u32)(temp_v1)];
jt_c0:
    var_v0 = ((S_80C97514_0 *)arg0)->unk_9B + 1;
    goto block_17;
jt_c1:
    func_80041588(&D_8017530C, &D_801753A8, 0);
    ((S_80C97514_0 *)arg0)->unk_A4 = 0;
    ((S_80C97514_0 *)arg0)->unk_9B = (u8) (((S_80C97514_0 *)arg0)->unk_9B + 1);
    ((S_80C97514_1 *)arg3)->unk_8A = (u16) ((S_80C97514_1 *)arg3)->unk_2A;
jt_c2:
    temp_a0 = ((s32) (D_80083228 + (s16) ((S_80C97514_1 *)arg3)->unk_2A + 0x100) >> 9) & 7;
    if ((*(u8 *)&D_801753A8) == 0) {
        goto block_6;
    }
    if (temp_a0 == 2) {
        goto block_8;
    }
block_6:
    if (temp_a0 == 2) {
        goto block_27;
    }
    ((S_80C97514_1 *)arg3)->unk_2A = (u16) (((S_80C97514_1 *)arg3)->unk_2A + 0x200);
    return;
block_8:
    func_80041588(&D_8017530C, &D_801753A8, 1);
    func_8003F540(0, D_8006CD58, 0x04000AD4, 0x05000CC4);
    func_8003E4FC(0x15, func_800445E0(), NULL);
    (*(s8 *)&D_801753A9) = 0;
    func_8003E4FC(0xFF, &D_8003E140, &D_801753A9);
    func_800C77D0(arg3 - 0x20, arg1, 8, 0x300);
    ((S_80C97514_0 *)arg0)->unk_96 = 0x10U;
    ((S_80C97514_0 *)arg0)->unk_9B = (u8) (((S_80C97514_0 *)arg0)->unk_9B + 1);
    func_80174724(arg0, arg1, arg2);
jt_c3:
    temp_v1_2 = ((S_80C97514_0 *)arg0)->unk_96;
    temp_v0 = temp_v1_2 - 1;
    ((S_80C97514_0 *)arg0)->unk_96 = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto block_12;
    }
    temp_v1 = ((S_80C97514_2 *)(&D_801753A9))->unk_00;
    ((S_80C97514_0 *)arg0)->unk_96 = temp_v1_2;
    if (temp_v1 == 0) {
        goto block_27;
    }
    ((S_80C97514_0 *)arg0)->unk_9B = (u8) (((S_80C97514_0 *)arg0)->unk_9B + 1);
    func_800A56E0(0x300);
    return;
block_12:
    temp_a1 = ((void **)&D_800DCEEC)[func_800498A0(arg3)];
    temp_base->unk_A8 = (u8) (temp_base->unk_A8 + ((s32) (temp_a1->unk_00 - temp_base->unk_A8) / (s16) ((S_80C97514_0 *)arg0)->unk_96));
    temp_base->unk_A9 = (u8) (temp_base->unk_A9 + ((s32) (temp_a1->unk_01 - temp_base->unk_A9) / (s16) ((S_80C97514_0 *)arg0)->unk_96));
    temp_base->unk_AA = (u8) (temp_base->unk_AA + ((s32) (temp_a1->unk_02 - temp_base->unk_AA) / (s16) ((S_80C97514_0 *)arg0)->unk_96));
    return;
jt_c4:
{
    void *case_a0;
    s32 case_v0;
    register s32 case_v1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

    temp_v0_2 = func_8003FC64(0x12);
    if (temp_v0_2 == NULL) {
        goto block_27;
    }
    temp_v0_2->unk_10 = &D_80174BE8;
    func_8004491C(temp_v0_2, &D_80045340);
    ((S_80C97514_0 *)arg0)->unk_AC = temp_v0_2;
    ((S_80C97514_14 *)(((S_80C97514_12 *)temp_v0_2)->unk_08))->unk_00 = (s32) arg1->unk_00;
    ((S_80C97514_14 *)(((S_80C97514_12 *)temp_v0_2)->unk_08))->unk_04 = (s32) arg1->unk_04;
    ((S_80C97514_14 *)(((S_80C97514_12 *)temp_v0_2)->unk_08))->unk_08 = (s32) arg1->unk_08;
    temp_s0 = temp_v0_2->unk_0C;
    temp_s0->unk_1E = 0x1000;
    temp_s0->unk_1C = 0x1000;
    temp_s0->unk_0C.s = 0x808080;
    case_v0 = func_800498A0(arg3) - 1;
    case_v1 = case_v0;
    ASM_KEEP(case_v0);   /* MATCH pin: retail delay-slot fill depends on it */
    case_a0 = temp_s0;
    if ((case_v0 << 0x10) >= 0) {
        goto block_16;
    }
    case_v1 = func_80069EF8() % 3;
block_16:
    temp_a1 = (void *)(*((s32 *)&D_80175318 + (s16) case_v1) + (s32)&D_8014A000);
    func_8003DB94(temp_s0, temp_a1, 0);
    arg2->unk_14 = (u16) (arg2->unk_14 | 0x80);
    ((S_80C97514_0 *)arg0)->unk_96 = 0U;
    var_v0 = ((S_80C97514_0 *)arg0)->unk_9B + 1;
block_17:
    ((S_80C97514_0 *)arg0)->unk_9B = var_v0;
    return;
}
jt_c5:
    temp_s0 = ((S_80C97514_0 *)arg0)->unk_AC;
    temp_s0 = temp_s0->unk_0C.u;
    if (!(temp_s0->unk_14 & 0xE000)) {
        goto block_20;
    }
    ((S_80C97514_0 *)arg0)->unk_9B = (u8) (((S_80C97514_0 *)arg0)->unk_9B + 1);
jt_c6:
block_20:
    if (((S_80C97514_0 *)arg0)->unk_9B != 6) {
        goto block_27;
    }
    if (func_800ADC4C(arg1, D_801753AC, D_80175314, &D_800DCF5C) == 0) {
        goto block_27;
    }
    ((S_80C97514_0 *)arg0)->unk_96 = 0x10U;
    ((S_80C97514_0 *)arg0)->unk_9B = (u8) (((S_80C97514_0 *)arg0)->unk_9B + 1);
    func_800A18E8(((S_80C97514_1 *)arg3)->unk_13, 3);
    func_8009A3D0(arg2->unk_24, arg2->unk_25, 0x300);
    func_8009A028(arg3);
    temp_s0 = arg3 - 0x20;
    temp_s0->unk_10 = (s32) (temp_s0->unk_10 | 0x80000000);
    return;
jt_c7:
    temp_v0_4 = func_800A504C(arg2, arg3);
    ((S_80C97514_1 *)arg3)->unk_60 = temp_v0_4;
    if (temp_v0_4 == NULL) {
        goto block_27;
    }
    ((S_80C97514_0 *)arg0)->unk_96 = 0x10U;
    ((S_80C97514_0 *)arg0)->unk_9B = (u8) (((S_80C97514_0 *)arg0)->unk_9B + 1);
    ((S_80C97514_15 *)(((S_80C97514_13 *)arg3)->unk_60))->unk_2A = (u16) ((S_80C97514_1 *)arg3)->unk_2A;
    temp_v1_3 = ((S_80C97514_1 *)arg3)->unk_60;
    temp_s0 = ((S_80C97514_9_pre *)temp_v1_3)[-1].unk_00;
    func_80047738(temp_s0, temp_s0->unk_2C[((s32) (D_80083228 + (s16) ((S_80C97514_9 *)temp_v1_3)->unk_2A + 0x100) >> 9) & 7], temp_s0->unk_04);
    temp_s0->unk_14 = (u16) (temp_s0->unk_14 & 0xFFFE);
jt_c8:
    temp_v0_5 = ((S_80C97514_0 *)arg0)->unk_96 - 1;
    ((S_80C97514_0 *)arg0)->unk_96 = temp_v0_5;
    if ((temp_v0_5 << 0x10) > 0) {
        goto block_27;
    }
    ((S_80C97514_15 *)(((S_80C97514_13 *)arg3)->unk_60))->unk_2A = (u16) ((S_80C97514_1 *)arg3)->unk_8A;
    ((S_80C97514_0_pre *)arg0)[-1].unk_00 = (u16) (((S_80C97514_0_pre *)arg0)[-1].unk_00 | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (((S_80C97514_10 *)(&D_800814A0))->unk_00 | 0x8000);
    temp_base2 = &D_80083460;
    temp_base2->unk_0A = (u16) (temp_base2->unk_0A - 1);
    ((S_80C97514_1 *)arg3)->unk_6D = 0;
block_27:
    return;
}
