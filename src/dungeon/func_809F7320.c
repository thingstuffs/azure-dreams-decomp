#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80174B20_13 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80174B20_13;   /* temp_v0_2 in func_80174B20 */

typedef struct S_80174B20_14 {
    u8 pad_00[0x60];
    void * unk_60;
} S_80174B20_14;   /* arg3 in func_80174B20 */

typedef struct S_80174B20_15 {
    s32 unk_00;
    s32 unk_04;
} S_80174B20_15;   /* ((S_80174B20_13 *)temp_v0_2)->unk_08 in func_80174B20 */

typedef struct S_80174B20_16 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80174B20_16;   /* ((S_80174B20_14 *)arg3)->unk_60 in func_80174B20 */


typedef struct S_80174B20_0_pre {
    u16 unk_00;
} S_80174B20_0_pre;   /* the 0x2 bytes before arg0 in func_80174B20, addressed as arg0[-1] */

typedef struct S_80174B20_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x10];
    void * unk_AC;
    s16 unk_B0;
} S_80174B20_0;   /* arg0 in func_80174B20 */

typedef struct S_80174B20_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x9];
    s8 unk_6D;
    u8 pad_6E[0x1C];
    u16 unk_8A;
} S_80174B20_1;   /* arg3 in func_80174B20 */

typedef struct S_80174B20_2 {
    u8 unk_00;
} S_80174B20_2;   /* &D_8017521D in func_80174B20 */

typedef struct S_80174B20_3 {
    u8 pad_00[0xA8];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} S_80174B20_3;   /* temp_s0_base in func_80174B20 */

typedef struct S_80174B20_4 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_80174B20_4;   /* temp_a1 in func_80174B20 */

typedef struct S_80174B20_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80174B20_5;   /* temp_v0_2 in func_80174B20 */


typedef struct S_80174B20_7 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
    u8 pad_14A4[0x3D74];
    s16 unk_5218;
} S_80174B20_7;   /* temp_a1_base in func_80174B20 */

typedef struct S_80174B20_8 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80174B20_8;   /* temp_a2 in func_80174B20 */

typedef struct S_80174B20_9 {
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
} S_80174B20_9;   /* temp_s0 in func_80174B20 */


typedef struct S_80174B20_11_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80174B20_11_pre;   /* the 0x14 bytes before temp_v1_3 in func_80174B20, addressed as temp_v1_3[-1] */

typedef struct S_80174B20_11 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80174B20_11;   /* temp_v1_3 in func_80174B20 */

typedef struct S_80174B20_12 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80174B20_12;   /* temp_a0_2 in func_80174B20 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_801708B8[];
void func_8003DB94();     /* extern */
s32 func_8003E4FC(); /* extern */
void func_8003F540(); /* extern */
void *func_8003FC64();                       /* extern */
void func_80041588(); /* extern */
int func_800445E0();                           /* extern */
s32 func_8004491C();           /* extern */
void func_80047738();              /* extern */
s32 func_800498A0();  /* extern */
s32 func_80069EF8();                          /* extern */
void func_8009A028();                      /* extern */
void func_8009A3D0();             /* extern */
void func_800A18E8();                 /* extern */
s32 func_800A504C();                /* extern */
s32 func_800A56E0();                     /* extern */
s32 func_800ADC4C();     /* extern */
s32 func_800C77D0(); /* extern */
void func_80174800(); /* extern */
extern M2C_UNK D_8003E140;
extern s32 D_8006CD58;
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083160;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern void *D_800DCEEC[];
extern M2C_UNK D_800DCF5C;
extern u8 D_8014A000[];
extern M2C_UNK D_80174574;
extern M2C_UNK D_801749F4;
extern M2C_UNK D_801751F8;
extern s32 D_80175200[];
extern s16 D_80175218;
extern M2C_UNK D_8017521C;
extern M2C_UNK D_8017521D;
extern s32 D_80175220;

void func_80174B20(void *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8 };
    register s32 temp_a3 ASM_REG("$7");   /* MATCH pin: retail schedule: same instructions, different order without it */
    S_80174B20_7 *temp_a1_base;
    S_80174B20_12 *temp_a0_2;
    s32 temp_v0_flags;
    u16 temp_v1_count;
    s16 temp_v0_4;
    s16 var_s0;
    s32 temp_a0;
    s32 temp_flag;
    s32 temp_index;
    s32 temp_random;
    s32 temp_v0_3;
    register s32 var_v1 ASM_REG("$3");   /* MATCH pin: retail keeps a computation the compiler would drop */
    s32 temp_v1_copy;
    register void *temp_a0_arg ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    u16 temp_v0;
    u16 temp_v0_6;
    u16 temp_v1_2;
    u8 temp_v1;
    S_80174B20_4 *temp_a1;
    S_80174B20_8 *temp_a2;
    S_80174B20_3 *temp_s0_base;
    S_80174B20_9 *temp_s0;
    S_80174B20_5 *temp_v0_2;
    void *temp_v0_5;
    void *temp_v1_3;

    temp_s0_base = &D_80083160;
    temp_v1 = ((S_80174B20_0 *)arg0)->unk_9B;
    if (temp_v1 >= 9U) {
        goto block_28;
    }
    (void)jt_keep; goto *D_801708B8[(u32)(temp_v1)];
jt_c0:
    ((S_80174B20_0 *)arg0)->unk_9B = (u8) (((S_80174B20_0 *)arg0)->unk_9B + 1);
    return;
jt_c1:
    func_80041588(&D_801751F8, &D_8017521C, 0);
    ((S_80174B20_0 *)arg0)->unk_B0 = 0;
    ((S_80174B20_0 *)arg0)->unk_9B = (u8) (((S_80174B20_0 *)arg0)->unk_9B + 1);
    ((S_80174B20_1 *)arg3)->unk_8A = (u16) ((S_80174B20_1 *)arg3)->unk_2A;
    ((S_80174B20_1 *)arg3)->unk_1C = (s32) (((S_80174B20_1 *)arg3)->unk_1C & 0xFFFBFFFF);
jt_c2:
    temp_a0 = ((s32) (D_80083228 + (s16) ((S_80174B20_1 *)arg3)->unk_2A + 0x100) >> 9) & 7;
    if ((*(u8 *)&D_8017521C) == 0) {
        goto block_6;
    }
    if (temp_a0 == 2) {
        goto block_8;
    }
block_6:
    if (temp_a0 == 2) {
        goto block_28;
    }
    ((S_80174B20_1 *)arg3)->unk_2A = (u16) (((S_80174B20_1 *)arg3)->unk_2A + 0x200);
    return;
block_8:
    func_80041588(&D_801751F8, &D_8017521C, 1);
    func_8003F540(0, D_8006CD58, 0x04000AD4, 0x05000CC4);
    func_8003E4FC(0x15, func_800445E0(), NULL);
    (*(s8 *)&D_8017521D) = 0;
    func_8003E4FC(0xFF, &D_8003E140, &D_8017521D);
    func_800C77D0(arg3 - 0x20, arg1, 8, 0x300);
    ((S_80174B20_0 *)arg0)->unk_96 = 0x10U;
    ((S_80174B20_0 *)arg0)->unk_9B = (u8) (((S_80174B20_0 *)arg0)->unk_9B + 1);
jt_c3:
    temp_v1_2 = ((S_80174B20_0 *)arg0)->unk_96;
    temp_v0 = temp_v1_2 - 1;
    ((S_80174B20_0 *)arg0)->unk_96 = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto block_12;
    }
    temp_flag = ((S_80174B20_2 *)(&D_8017521D))->unk_00;
    ((S_80174B20_0 *)arg0)->unk_96 = temp_v1_2;
    if (temp_flag == 0) {
        goto block_28;
    }
    ((S_80174B20_0 *)arg0)->unk_9B = (u8) (((S_80174B20_0 *)arg0)->unk_9B + 1);
    func_800A56E0(0x300);
    return;
block_12:
    temp_index = func_800498A0(arg3);
    temp_a1 = D_800DCEEC[temp_index];
    temp_s0_base->unk_A8 = (u8) (temp_s0_base->unk_A8 + ((s32) (temp_a1->unk_00 - temp_s0_base->unk_A8) / (s16) ((S_80174B20_0 *)arg0)->unk_96));
    temp_s0_base->unk_A9 = (u8) (temp_s0_base->unk_A9 + ((s32) (temp_a1->unk_01 - temp_s0_base->unk_A9) / (s16) ((S_80174B20_0 *)arg0)->unk_96));
    temp_s0_base->unk_AA = (u8) (temp_s0_base->unk_AA + ((s32) (temp_a1->unk_02 - temp_s0_base->unk_AA) / (s16) ((S_80174B20_0 *)arg0)->unk_96));
    return;
jt_c4:
    temp_v0_2 = func_8003FC64(0x12);
    if (temp_v0_2 == NULL) {
        goto block_28;
    }
    temp_v0_2->unk_10 = &D_801749F4;
    func_8004491C(temp_v0_2, &D_80174574);
    temp_a3 = 0x808080;
    temp_a0_arg = arg3;
    ((S_80174B20_0 *)arg0)->unk_AC = temp_v0_2;
    ((S_80174B20_15 *)(((S_80174B20_13 *)temp_v0_2)->unk_08))->unk_00 = (s32) arg1->unk_00.at00_s32.v;
    ((S_80174B20_15 *)(((S_80174B20_13 *)temp_v0_2)->unk_08))->unk_04 = (s32) arg1->unk_04.at00_s32.v;
    temp_a2 = temp_v0_2->unk_08;
    temp_a1_base = (void *)0x80170000;
    ASM_KEEP(temp_a3);   /* MATCH pin: retail immediate-load split depends on it */
    temp_v1_copy = arg1->unk_08.at00_s32.v;
    temp_a1_base->unk_5218 = -4;
    temp_a2->unk_08 = temp_v1_copy;
    temp_s0 = temp_v0_2->unk_0C;
    temp_s0->unk_1E = 0x1000;
    temp_s0->unk_1C = 0x1000;
    ASM_KEEP(temp_a3);   /* MATCH pin: retail immediate-load split depends on it */
    temp_s0->unk_0C.s = temp_a3;
    temp_v0_3 = func_800498A0(temp_a0_arg, temp_a1_base, temp_a2, temp_a3) - 1;
    var_v1 = temp_v0_3;
    ASM_KEEP_NV(temp_v0_3);   /* MATCH pin: retail delay-slot fill depends on it */
    temp_a0_arg = temp_s0;
    if ((temp_v0_3 << 0x10) >= 0) {
        goto block_16;
    }
    temp_random = func_80069EF8(temp_a0_arg);
    var_v1 = temp_random % 3;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    temp_a0_arg = temp_s0;
block_16:
    func_8003DB94(temp_a0_arg, &D_8014A000[(*(s32 *)((u8 *)D_80175200 + (s16) var_v1 * 4))], 0);
    arg2->unk_14.at00_u16.v = (u16) (arg2->unk_14.at00_u16.v | 0x80);
    var_s0 = 1;
    ((S_80174B20_0 *)arg0)->unk_96 = 0U;
    ((S_80174B20_0 *)arg0)->unk_9B = (u8) (((S_80174B20_0 *)arg0)->unk_9B + 1);
loop_17:
    func_80174800(arg0, arg1, arg2, (s16) (var_s0 << 0xA));
    temp_v0_4 = var_s0 + 1;
    var_s0 = temp_v0_4;
    if (temp_v0_4 < 8) {
        goto loop_17;
    }
    return;
jt_c5:
    temp_s0 = ((S_80174B20_0 *)arg0)->unk_AC;
    temp_s0 = temp_s0->unk_0C.u;
    if (!(temp_s0->unk_14 & 0xE000)) {
        goto block_21;
    }
    ((S_80174B20_0 *)arg0)->unk_96 = 0x10U;
    ((S_80174B20_0 *)arg0)->unk_9B = (u8) (((S_80174B20_0 *)arg0)->unk_9B + 1);
    func_800A18E8(((S_80174B20_1 *)arg3)->unk_13, 3);
    func_8009A3D0(arg2->unk_24, arg2->unk_25, 0x300);
    func_8009A028(arg3);
    temp_s0 = arg3 - 0x20;
    temp_s0->unk_10 = (s32) (temp_s0->unk_10 | 0x80000000);
jt_c6:
block_21:
    if (((S_80174B20_0 *)arg0)->unk_9B != 6) {
        goto block_28;
    }
    if (func_800ADC4C(arg1, D_80175220, D_80175218, &D_800DCF5C) == 0) {
        goto block_28;
    }
    ((S_80174B20_0 *)arg0)->unk_96 = 0x10U;
    ((S_80174B20_0 *)arg0)->unk_9B = (u8) (((S_80174B20_0 *)arg0)->unk_9B + 1);
    func_800A18E8(((S_80174B20_1 *)arg3)->unk_13, 3);
    func_8009A3D0(arg2->unk_24, arg2->unk_25, 0x300);
    func_8009A028(arg3);
    temp_s0 = arg3 - 0x20;
    temp_s0->unk_10 = (s32) (temp_s0->unk_10 | 0x80000000);
    return;
jt_c7:
    temp_v0_5 = func_800A504C(arg2, arg3);
    ((S_80174B20_1 *)arg3)->unk_60 = temp_v0_5;
    if (temp_v0_5 == NULL) {
        goto block_28;
    }
    ((S_80174B20_0 *)arg0)->unk_96 = 0x10U;
    ((S_80174B20_0 *)arg0)->unk_9B = (u8) (((S_80174B20_0 *)arg0)->unk_9B + 1);
    ((S_80174B20_16 *)(((S_80174B20_14 *)arg3)->unk_60))->unk_2A = (u16) ((S_80174B20_1 *)arg3)->unk_2A;
    temp_v1_3 = ((S_80174B20_1 *)arg3)->unk_60;
    temp_s0 = ((S_80174B20_11_pre *)temp_v1_3)[-1].unk_00;
    func_80047738(temp_s0, temp_s0->unk_2C[((s32) (D_80083228 + (s16) ((S_80174B20_11 *)temp_v1_3)->unk_2A + 0x100) >> 9) & 7], temp_s0->unk_04);
    temp_s0->unk_14 = (u16) (temp_s0->unk_14 & 0xFFFE);
jt_c8:
    temp_v0_6 = ((S_80174B20_0 *)arg0)->unk_96 - 1;
    ((S_80174B20_0 *)arg0)->unk_96 = temp_v0_6;
    if ((temp_v0_6 << 0x10) > 0) {
        goto block_28;
    }
    temp_a1_base = (void *)0x80080000;
    temp_a0_2 = &D_80083460;
    ((S_80174B20_16 *)(((S_80174B20_14 *)arg3)->unk_60))->unk_2A = (u16) ((S_80174B20_1 *)arg3)->unk_8A;
    ((S_80174B20_0_pre *)arg0)[-1].unk_00 = (u16) (((S_80174B20_0_pre *)arg0)[-1].unk_00 | 0x8000);
    temp_v0_flags = temp_a1_base->unk_14A0;
    temp_v1_count = temp_a0_2->unk_0A;
    temp_a1_base->unk_14A0 = temp_v0_flags | 0x8000;
    temp_a0_2->unk_0A = temp_v1_count - 1;
    ((S_80174B20_1 *)arg3)->unk_6D = 0;
block_28:
    return;
}
