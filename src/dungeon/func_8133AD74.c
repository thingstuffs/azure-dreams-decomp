/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80171D74_0 {
    s32 unk_00;
} S_80171D74_0;   /* D_8008333C in func_80171D74 */

typedef struct S_80171D74_1 {
    u8 pad_00[0x92];
    union { s16 s; u16 u; } unk_92;   /* accessed as both */
    s16 unk_94;
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 pad_9B[0x3];
    s16 unk_9E;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A0;   /* overlapping accesses */
} S_80171D74_1;   /* arg0 in func_80171D74 */

typedef struct S_80171D74_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80171D74_2;   /* D_80175D50[0] in func_80171D74 */

typedef struct S_80171D74_3 {
    union { struct { s32 v; } at00; struct { volatile s32 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { volatile s32 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    union { s32 n; volatile s32 v; } unk_0C;   /* accessed as both */
    union { s32 n; volatile s32 v; } unk_10;   /* accessed as both */
    s32 unk_14;
} S_80171D74_3;   /* arg1 in func_80171D74 */

typedef struct S_80171D74_4 {
    u8 pad_00[0x2A];
    union { u16 n; volatile u16 v; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80171D74_4;   /* temp_s3 in func_80171D74 */

typedef struct S_80171D74_5 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x16];
    union { M2C_UNK * p; u8 * p2; } unk_2C;   /* accessed as both */
} S_80171D74_5;   /* arg2 in func_80171D74 */

typedef struct S_80171D74_6 {
    s16 unk_00;
} S_80171D74_6;   /* D_80083228 in func_80171D74 */

typedef struct S_80171D74_7 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_80171D74_7;   /* temp_s4 in func_80171D74 */

typedef struct S_80171D74_8 {
    u8 pad_00[0x27];
    u8 unk_27;
    u8 pad_28[0x2];
    u16 unk_2A;
} S_80171D74_8;   /* temp_a1_2 in func_80171D74 */

typedef struct S_80171D74_9 {
    volatile s32 unk_00;
    s32 unk_04;
} S_80171D74_9;   /* &D_80083780 in func_80171D74 */

typedef struct S_80171D74_10 {
    u8 pad_00[0x32];
    s16 unk_32;
} S_80171D74_10;   /* D_80175DB8[0] in func_80171D74 */

typedef struct S_80171D74_11 {
    s16 unk_00;
    u16 unk_02;
} S_80171D74_11;   /* sp2_base16 in func_80171D74 */

typedef struct S_80171D74_12 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_80171D74_12;   /* base833c in func_80171D74 */

typedef struct S_80171D74_13 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_13;   /* temp_v0_12 in func_80171D74 */

typedef struct S_80171D74_14 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_14;   /* temp_v0_13 in func_80171D74 */

typedef struct S_80171D74_15 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_15;   /* temp_v0_14 in func_80171D74 */

typedef struct S_80171D74_16 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_16;   /* temp_v0_15 in func_80171D74 */

typedef struct S_80171D74_17 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_17;   /* temp_v0_16 in func_80171D74 */

typedef struct S_80171D74_18 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_18;   /* temp_v0_17 in func_80171D74 */

typedef struct S_80171D74_19 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_19;   /* temp_v0_18 in func_80171D74 */

typedef struct S_80171D74_20 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_20;   /* temp_v0_19 in func_80171D74 */

typedef struct S_80171D74_21 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_21;   /* temp_v0_20 in func_80171D74 */


typedef struct { u32 v; } __attribute__((packed)) UA32;
typedef struct { UA32 word[8]; } __attribute__((packed)) Table32;

#define SP1_X(a) M2C_FIELD((u8 *)&sp18 + ((((u16)(a)) >> 7) & 0x1C), s16 *, 0)
#define SP1_Y(a) M2C_FIELD((u8 *)&sp18 + ((((u16)(a)) >> 7) & 0x1C), u16 *, 2)
#define SP2_X(a) M2C_FIELD((u8 *)&sp38 + ((((u16)(a)) >> 7) & 0x1C), s16 *, 0)
#define SP2_Y(a) M2C_FIELD((u8 *)&sp38 + ((((u16)(a)) >> 7) & 0x1C), u16 *, 2)
#define SP1_X_AT(base, a) M2C_FIELD((u8 *)(base) + ((((u16)(a)) >> 7) & 0x1C), s16 *, 0)
#define SP1_Y_AT(base, a) M2C_FIELD((u8 *)(base) + ((((u16)(a)) >> 7) & 0x1C), u16 *, 2)
#define SP2_X_AT(base, a) M2C_FIELD((u8 *)(base) + ((((u16)(a)) >> 7) & 0x1C), s16 *, 0)
#define SP2_Y_AT(base, a) M2C_FIELD((u8 *)(base) + ((((u16)(a)) >> 7) & 0x1C), u16 *, 2)

void func_80041094(); /* extern */
void func_80047738();              /* extern */
void func_80047784();         /* extern */
void func_800478B8();  /* extern */
s32 func_800644B8();                     /* extern */
void func_800945E8();                 /* extern */
void func_800948BC();                            /* extern */
void func_800A56E0();             /* extern */
s32 func_800F685C();                      /* extern */
void func_80166F3C();             /* extern */
void func_8016738C();                      /* extern */
void func_801676CC();                      /* extern */
void func_801677FC();                  /* extern */
void func_8016F5D8();      /* extern */
void func_8016F79C();      /* extern */
void func_801715D0();                            /* extern */
void func_80173008() __attribute__((noreturn));                            /* extern */
void func_80173018() __attribute__((noreturn));                  /* extern */
void func_8017301C() __attribute__((noreturn));              /* extern */
void func_80173074() __attribute__((noreturn));                 /* extern */
void func_80173080() __attribute__((noreturn));                  /* extern */
void func_80173084() __attribute__((noreturn));                            /* extern */
void func_80173110() __attribute__((noreturn));                            /* extern */
extern u8 D_8006CCF8[16];
extern u16 D_80082E76[8];
extern s16 D_80083228[8];
extern s32 D_8008333C[8192];
extern u16 D_80083460[8];
extern s32 D_80083780[8192];
extern s32 D_800E3D7C[3];
extern Table32 D_8016482C;
extern Table32 D_80164AC0;
extern void *D_80164AE0[];
extern u8 D_80173DA4[16];
extern u8 D_80173DAC[16];
extern u8 D_80173DB4[16];
extern void *D_80175D50[3];
extern void *D_80175D54[3];
extern void *D_80175DB8[16];

void func_80171D74(void *arg0_in, void *arg1_in, void *arg2_in) {
    Table32 sp18;
    Table32 sp38;
    static void *const jt_keep[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6,
        &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13,
        &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17, &&jt_c18, &&jt_c19, &&jt_c20,
        &&jt_c21, &&jt_c22, &&jt_c23, &&jt_c24, &&jt_c25, &&jt_c26, &&jt_c27,
        &&jt_c28, &&jt_c29, &&jt_c30, &&jt_c31, &&jt_c32, &&jt_c33, &&jt_c34,
        &&jt_c35, &&jt_c36, &&jt_c37, &&jt_c38, &&jt_c39, &&jt_c40, &&jt_c41,
        &&jt_c42, &&jt_c43, &&jt_c44, &&jt_c45, &&jt_c46, &&jt_c47, &&jt_c48
    };
    M2C_UNK *var_v0_2;
    s16 temp_a0_11;
    s16 temp_a0_13;
    s16 temp_a0_5;
    s16 temp_s2_2;
    s16 temp_v1_2;
    s16 temp_v1_6;
    s16 temp_v1_7;
    s16 var_v1_6;
    s16 var_v1_8;
    s32 temp_a1_4;
    s32 temp_a1_8;
    void *arg0;
    register void *arg1 ASM_REG("$16");   /* MATCH pin: load-bearing for the whole function shape */
    void *arg2;
    Table32 *copy_base;
    register s32 *base833c ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 temp_s2 ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
    u8 tail_phase;
    register void *tail_call_arg ASM_REG("$4");   /* MATCH pin: retail delay-slot contents depend on it */
    s32 temp_v1_3;
    u16 temp_a0_12;
    u16 temp_a0_14;
    u16 temp_a0_2;
    u16 temp_a0_4;
    u16 temp_a0_7;
    u16 temp_a0_8;
    u16 temp_v0;
    u16 temp_v0_10;
    u16 temp_v0_11;
    u16 temp_v0_21;
    u16 temp_v0_22;
    u16 temp_v0_23;
    u16 temp_v0_24;
    u16 temp_v0_25;
    u16 temp_v0_26;
    u16 temp_v0_27;
    u16 temp_v0_28;
    u16 temp_v0_29;
    u16 temp_v0_2;
    u16 temp_v0_30;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v0_8;
    u16 temp_v0_9;
    u16 temp_v1;
    u16 var_v1;
    u16 var_v1_3;
    u16 var_v1_4;
    u16 var_v1_5;
    u16 var_v1_7;
    u16 var_v1_9;
    s32 temp_a0;
    s32 temp_a0_10;
    s32 temp_a0_9;
    S_80171D74_8 *temp_a1_2;
    s32 temp_a1_3;
    s32 temp_a1_5;
    s32 temp_a1_6;
    s32 temp_a1_7;
    S_80171D74_4 *temp_s3;
    register void *temp_s4 ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    S_80171D74_13 *temp_v0_12;
    S_80171D74_14 *temp_v0_13;
    S_80171D74_15 *temp_v0_14;
    S_80171D74_16 *temp_v0_15;
    S_80171D74_17 *temp_v0_16;
    S_80171D74_18 *temp_v0_17;
    S_80171D74_19 *temp_v0_18;
    S_80171D74_20 *temp_v0_19;
    S_80171D74_21 *temp_v0_20;
    s32 temp_v1_4;
    s32 temp_v1_5;

    arg0 = arg0_in;
    arg1 = arg1_in;
    arg2 = arg2_in;
    ASM_KEEP_NV(arg0);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP_NV(arg1);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP_NV(arg2);   /* MATCH pin: load-bearing for the whole function shape */
    copy_base = &D_8016482C;
    sp18 = *copy_base;
    copy_base = &D_80164AC0;
    sp38 = *copy_base;
    base833c = D_8008333C;
    temp_s2 = ((S_80171D74_0 *)D_8008333C)->unk_00;
    temp_s3 = D_80175D54[0] + 0x20;
    func_800478B8(arg2);
    temp_a0 = ((S_80171D74_1 *)arg0)->unk_9A;
    temp_s4 = ((S_80171D74_2 *)(D_80175D50[0]))->unk_08;
    temp_a1_2 = D_80175D50[0] + 0x20;
    if ((u32)temp_a0 >= 49U) {
        goto block_152;
    }
    (void)jt_keep;
    goto *D_80164AE0[(u32)temp_a0];
jt_c0:
        temp_v0 = ((S_80171D74_1 *)arg0)->unk_96;
        ((S_80171D74_1 *)arg0)->unk_96 = (u16) (temp_v0 + 1);
        if ((s16) temp_v0 >= 0x1E) {
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
            ((S_80171D74_3 *)arg1)->unk_10.n = (s32) 0xFFF80000;
            func_80173018();
            return;
        }
        goto block_147;
jt_c1:
        ((S_80171D74_3 *)arg1)->unk_04.at00.v = ((S_80171D74_3 *)arg1)->unk_04.at00.v + ((S_80171D74_3 *)arg1)->unk_10.n;
        temp_v0_2 = ((S_80171D74_1 *)arg0)->unk_96 + 1;
        ((S_80171D74_1 *)arg0)->unk_96 = temp_v0_2;
        if ((s16) temp_v0_2 >= 0x38) {
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
            ((S_80171D74_3 *)arg1)->unk_0C.n = 0;
            func_8017301C();
            return;
        }
        goto block_147;
jt_c2:
        temp_v0_3 = ((S_80171D74_1 *)arg0)->unk_96;
        ((S_80171D74_1 *)arg0)->unk_96 = (u16) (temp_v0_3 + 1);
        if ((s16) temp_v0_3 >= 0x1E) {
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
            func_80173018();
            return;
        }
        goto block_147;
jt_c3:
        temp_v0_4 = ((S_80171D74_1 *)arg0)->unk_96 + 1;
        ((S_80171D74_1 *)arg0)->unk_96 = temp_v0_4;
        if ((s16) temp_v0_4 == 3) {
            temp_s3->unk_2A.n = (u16) (temp_s3->unk_2A.n + 0x200);
        }
        if ((s16) ((S_80171D74_1 *)arg0)->unk_96 == 4) {
            temp_s3->unk_2A.n = (u16) (temp_s3->unk_2A.n + 0x200);
        }
        if ((s16) ((S_80171D74_1 *)arg0)->unk_96 == 0x12) {
            temp_s3->unk_2A.n = (u16) (temp_s3->unk_2A.n - 0x200);
        }
        if ((s16) ((S_80171D74_1 *)arg0)->unk_96 == 0x14) {
            temp_s3->unk_2A.n = (u16) (temp_s3->unk_2A.n - 0x200);
        }
        if ((s16) ((S_80171D74_1 *)arg0)->unk_96 == 0x1E) {
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
            ((S_80171D74_3 *)arg1)->unk_0C.n = 0;
            ((S_80171D74_3 *)arg1)->unk_10.n = (s32) 0xFFF80000;
            func_8017301C();
            return;
        }
        goto block_147;
jt_c4:
        ((S_80171D74_3 *)arg1)->unk_04.at00.v = ((S_80171D74_3 *)arg1)->unk_04.at00.v + ((S_80171D74_3 *)arg1)->unk_10.n;
        temp_v0_5 = ((S_80171D74_1 *)arg0)->unk_96 + 1;
        ((S_80171D74_1 *)arg0)->unk_96 = temp_v0_5;
        if ((s16) temp_v0_5 >= 0x10) {
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
            ((S_80171D74_3 *)arg1)->unk_0C.n = 0;
            func_8017301C();
            return;
        }
        goto block_147;
jt_c6:
        ((S_80171D74_5 *)arg2)->unk_2C.p = &D_80173DAC;
        func_80047784(arg2, D_80173DAC[((s32) (((S_80171D74_6 *)D_80083228)->unk_00 + (s16) temp_s3->unk_2A.n + 0x100) >> 9) & 7], 3);
        ((S_80171D74_1 *)arg0)->unk_96 = 0U;
        ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
        ((S_80171D74_3 *)arg1)->unk_0C.n = (s32) 0x00020000;
        func_80173080();
        return;
jt_c7:
        ((S_80171D74_3 *)arg1)->unk_00.at00.v = (s32) (((S_80171D74_3 *)arg1)->unk_00.at00.v + ((S_80171D74_3 *)arg1)->unk_0C.n);
        temp_v0_6 = ((S_80171D74_1 *)arg0)->unk_96 + 1;
        ((S_80171D74_1 *)arg0)->unk_96 = temp_v0_6;
        if ((s16) temp_v0_6 >= 8) {
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
            ((S_80171D74_3 *)arg1)->unk_0C.n = 0;
            ((S_80171D74_5 *)arg2)->unk_14 = (u16) (((S_80171D74_5 *)arg2)->unk_14 | 0x80);
            ((S_80171D74_3 *)arg1)->unk_04.at02.v = 1;
            ((S_80171D74_3 *)arg1)->unk_00.at02.v = 1U;
        }
        if ((s16) ((S_80171D74_1 *)arg0)->unk_96 == 3) {
            u32 tail_page7;
            func_80166F3C(temp_s4, 0);
            func_80166F3C(temp_s4, 1);
            func_8016738C(temp_s4);
            func_801676CC(temp_s4);
            tail_page7 = 0x80170000;
            ASM_PAGEBASE_PIN(tail_page7);   /* MATCH pin: retail delay-slot contents depend on it */
            func_80173084();
            return;
        }
        goto block_152;
jt_c9:
        func_801677FC(temp_a0, temp_a1_2);
        tail_phase = ((S_80171D74_1 *)arg0)->unk_9A;
        ASM_KEEP(tail_phase);   /* MATCH pin: retail basic-block layout depends on it */
        ((S_80171D74_1 *)arg0)->unk_96 = 0;
        func_80173074();
        return;
jt_c10:
        temp_v0_7 = ((S_80171D74_1 *)arg0)->unk_96 + 1;
        ((S_80171D74_1 *)arg0)->unk_96 = temp_v0_7;
        if ((s16) temp_v0_7 >= 2) {
            u8 *sp1_base = (u8 *)&sp18;
            u8 *sp2_base;
            register s32 angle_input ASM_REG("$3");   /* MATCH pin: retail keeps a computation the compiler would drop */
            s32 angle_tmp;
            register s32 angle_result ASM_REG("$3");   /* MATCH pin: retail keeps a computation the compiler would drop */
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
            ((S_80171D74_5 *)arg2)->unk_14 = (u16) (((S_80171D74_5 *)arg2)->unk_14 & 0xFF7F);
            ((S_80171D74_3 *)arg1)->unk_00.at02.v = (u16) (((S_80171D74_7 *)temp_s4)->unk_00.at02.v + (SP1_X_AT(sp1_base, temp_a1_2->unk_2A) * 0x28));
            ((S_80171D74_3 *)arg1)->unk_04.at02.v = (s16) (((S_80171D74_7 *)temp_s4)->unk_04.at02.v + ((s16) SP1_Y_AT(sp1_base, temp_a1_2->unk_2A) * 0x28));
            ((S_80171D74_1 *)arg0)->unk_92.s = -0x18;
            ((S_80171D74_1 *)arg0)->unk_9E = 0;
            ((S_80171D74_1 *)arg0)->unk_A0.at00.v = 0;
            angle_input = temp_a1_2->unk_2A;
            angle_tmp = angle_input - 0x400;
            angle_result = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_result = angle_tmp + 0x1000;
            }
            temp_s3->unk_2A.n = angle_result;
            ((S_80171D74_1 *)arg0)->unk_94 = 1;
            ((S_80171D74_5 *)arg2)->unk_2C.p = &D_80173DB4;
            func_80047784(arg2, D_80173DB4[((s32) (((S_80171D74_6 *)D_80083228)->unk_00 + (s16) temp_s3->unk_2A.n + 0x100) >> 9) & 7], 0);
            sp2_base = (u8 *)&sp38;
            ((S_80171D74_3 *)arg1)->unk_0C.n = (s32) (0 - (SP2_X_AT(sp2_base, temp_s3->unk_2A.n) << 0x10));
            ((S_80171D74_3 *)arg1)->unk_10.n = (void *) (0 - (SP2_Y_AT(sp2_base, temp_s3->unk_2A.n) << 0x10));
            func_801715D0();
            tail_call_arg = arg0;
            ASM_TAILSLOT_PIN(tail_call_arg);   /* MATCH pin: retail delay-slot contents depend on it */
            func_8017301C();
            return;
        }
        goto block_152;
jt_c11:
        {
            s32 pos_x = ((S_80171D74_3 *)arg1)->unk_00.at00.v;
            s32 vel_x = ((S_80171D74_3 *)arg1)->unk_0C.n;
            s32 pos_y = ((S_80171D74_3 *)arg1)->unk_04.at00.v;
            s32 vel_y = ((S_80171D74_3 *)arg1)->unk_10.n;
            ((S_80171D74_3 *)arg1)->unk_00.at00.v = pos_x + vel_x;
            ((S_80171D74_3 *)arg1)->unk_04.at00.v = pos_y + vel_y;
        }
        temp_v0_8 = ((S_80171D74_1 *)arg0)->unk_96 + 1;
        ((S_80171D74_1 *)arg0)->unk_96 = temp_v0_8;
        if ((s16) temp_v0_8 >= 0x14) {
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
            func_8017301C();
            return;
        }
        goto block_147;
jt_c13:
        temp_v1 = temp_s3->unk_2A.n;
        temp_v0_9 = temp_v1 + 0x200;
        temp_s3->unk_2A.n = temp_v0_9;
        if ((s16) temp_v0_9 >= 0x1000) {
            temp_s3->unk_2A.n = (u16) (temp_v1 - 0xE00);
        }
        ((S_80171D74_1 *)arg0)->unk_96 = 0U;
        ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
        temp_a1_2->unk_27 = 3;
        func_80173018();
        return;
jt_c15:
        ((S_80171D74_1 *)arg0)->unk_96 = 0x1EU;
        ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
        /* fallthrough */
jt_c16:
        {
            s32 target_x = ((S_80171D74_9 *)(&D_80083780))->unk_00;
            temp_a1_4 = ((S_80171D74_3 *)arg1)->unk_00.at00u.v;
            ((S_80171D74_3 *)arg1)->unk_0C.n = (target_x - temp_a1_4) / (s16) ((S_80171D74_1 *)arg0)->unk_96;
        }
        {
            s32 next_y = (((S_80171D74_9 *)(&D_80083780))->unk_04 - ((S_80171D74_3 *)arg1)->unk_04.at00.v) / (s16) ((S_80171D74_1 *)arg0)->unk_96;
            s32 vel_x = ((S_80171D74_3 *)arg1)->unk_0C.v;
            s32 pos_y = ((S_80171D74_3 *)arg1)->unk_04.at00u.v;
            s32 next_x;
            ((S_80171D74_3 *)arg1)->unk_10.v = next_y;
            next_x = temp_a1_4;
            temp_a1_4 = ((S_80171D74_3 *)arg1)->unk_10.v;
            ((S_80171D74_3 *)arg1)->unk_00.at00.v = next_x + vel_x;
            ((S_80171D74_3 *)arg1)->unk_04.at00.v = pos_y + temp_a1_4;
        }
        temp_v0_10 = ((S_80171D74_1 *)arg0)->unk_96 - 1;
        ((S_80171D74_1 *)arg0)->unk_96 = temp_v0_10;
        if ((temp_v0_10 << 0x10) <= 0) {
            u8 *sp2_base16;
            register s32 angle_input16 ASM_REG("$3");   /* MATCH pin: retail keeps a computation the compiler would drop */
            s32 angle_tmp16;
            register s32 angle_result16 ASM_REG("$3");   /* MATCH pin: retail keeps a computation the compiler would drop */
            register u32 angle_index16 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
            ((S_80171D74_10 *)(D_80175DB8[0]))->unk_32 = 3;
            ((S_80171D74_5 *)arg2)->unk_2C.p = &D_80173DA4;
            func_80047784(arg2, D_80173DA4[((s32) (((S_80171D74_6 *)D_80083228)->unk_00 + (s16) temp_s3->unk_2A.n + 0x100) >> 9) & 7], 0);
            angle_input16 = temp_s3->unk_2A.n;
            angle_tmp16 = angle_input16 + 0x200;
            angle_result16 = angle_tmp16;
            if ((s16) angle_tmp16 >= 0x1000) {
                angle_result16 = angle_tmp16 - 0x1000;
            }
            angle_index16 = ((u16) angle_result16 >> 7) & 0x1C;
            sp2_base16 = (u8 *)&sp38;
            sp2_base16 += angle_index16;
            ((S_80171D74_3 *)arg1)->unk_0C.n = (s32) (((S_80171D74_11 *)sp2_base16)->unk_00 << 0x10);
            ((S_80171D74_3 *)arg1)->unk_10.n = (s32) (((S_80171D74_11 *)sp2_base16)->unk_02 << 0x10);
            func_80173018();
            return;
        }
        goto block_147;
jt_c17:
        {
            s32 pos_x = ((S_80171D74_3 *)arg1)->unk_00.at00.v;
            s32 vel_x = ((S_80171D74_3 *)arg1)->unk_0C.n;
            s32 pos_y = ((S_80171D74_3 *)arg1)->unk_04.at00.v;
            s32 vel_y = ((S_80171D74_3 *)arg1)->unk_10.n;
            ((S_80171D74_3 *)arg1)->unk_00.at00.v = pos_x + vel_x;
            ((S_80171D74_3 *)arg1)->unk_04.at00.v = pos_y + vel_y;
        }
        {
            u16 pitch17;
            u16 phase17;
            pitch17 = ((S_80171D74_1 *)arg0)->unk_92.u;
            phase17 = ((S_80171D74_1 *)arg0)->unk_96;
            pitch17 = pitch17 - 2;
            ASM_KEEP_NV(pitch17);   /* MATCH pin: retail schedule: same instructions, different order without it */
            phase17 = phase17 + 1;
            temp_v0_11 = phase17;
            ((S_80171D74_1 *)arg0)->unk_96 = temp_v0_11;
            ((S_80171D74_1 *)arg0)->unk_92.u = pitch17;
        }
        if ((s16) temp_v0_11 >= 0x28) {
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
            ((S_80171D74_3 *)arg1)->unk_10.n = NULL;
            ((S_80171D74_3 *)arg1)->unk_0C.n = 0;
        }
        temp_v1_2 = (s16) ((S_80171D74_1 *)arg0)->unk_96;
        if ((temp_v1_2 == 0xA) || (temp_v1_2 == 0x14) || (temp_v1_2 == 0x1E)) {
            register s32 angle_input ASM_REG("$3");   /* MATCH pin: retail keeps a computation the compiler would drop */
            s32 angle_tmp;
            register s32 angle_result ASM_REG("$3");   /* MATCH pin: retail keeps a computation the compiler would drop */
            angle_input = temp_s3->unk_2A.n;
            angle_tmp = angle_input - 0x200;
            angle_result = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_result = angle_tmp + 0x1000;
            }
            temp_s3->unk_2A.n = angle_result;
            if ((s16) ((S_80171D74_1 *)arg0)->unk_96 == 0x1E) {
                func_800A56E0(0x81A);
                tail_call_arg = arg0;
                ASM_TAILSLOT_PIN(tail_call_arg);   /* MATCH pin: retail delay-slot contents depend on it */
                func_8017301C();
                return;
            }
            goto block_147;
        }
        goto block_147;
jt_c19:
        ((S_80171D74_1 *)arg0)->unk_96 = 0x14U;
        ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
        temp_v0_12 = ((0x1F << ((S_80171D74_12 *)base833c)->unk_14) * 6) + temp_s2 + 0xBA;
        temp_v0_12->unk_04 = (u16) (temp_v0_12->unk_04 & 0x7FFF);
        temp_v0_13 = ((0x1F << ((S_80171D74_12 *)base833c)->unk_14) * 6) + temp_s2 + 0xC0;
        temp_v0_13->unk_04 = (u16) (temp_v0_13->unk_04 & 0x7FFF);
        temp_v0_14 = ((0x1F << ((S_80171D74_12 *)base833c)->unk_14) * 6) + temp_s2 + 0xC6;
        temp_v0_14->unk_04 = (u16) (temp_v0_14->unk_04 & 0x7FFF);
        temp_v0_15 = ((0x20 << ((S_80171D74_12 *)base833c)->unk_14) * 6) + temp_s2 + 0xBA;
        temp_v0_15->unk_04 = (u16) (temp_v0_15->unk_04 & 0x7FFF);
        temp_v0_16 = ((0x20 << ((S_80171D74_12 *)base833c)->unk_14) * 6) + temp_s2 + 0xC0;
        temp_v0_16->unk_04 = (u16) (temp_v0_16->unk_04 & 0x7FFF);
        temp_v0_17 = ((0x20 << ((S_80171D74_12 *)base833c)->unk_14) * 6) + temp_s2 + 0xC6;
        temp_v0_17->unk_04 = (u16) (temp_v0_17->unk_04 & 0x7FFF);
        temp_v0_18 = ((0x21 << ((S_80171D74_12 *)base833c)->unk_14) * 6) + temp_s2 + 0xBA;
        temp_v0_18->unk_04 = (u16) (temp_v0_18->unk_04 & 0x7FFF);
        temp_v0_19 = ((0x21 << ((S_80171D74_12 *)base833c)->unk_14) * 6) + temp_s2 + 0xC0;
        temp_v0_19->unk_04 = (u16) (temp_v0_19->unk_04 & 0x7FFF);
        temp_v0_20 = ((0x21 << ((S_80171D74_12 *)base833c)->unk_14) * 6) + temp_s2 + 0xC6;
        temp_v0_20->unk_04 = (u16) (temp_v0_20->unk_04 & 0x7FFF);
        ((S_80171D74_3 *)arg1)->unk_0C.n = (s32) ((S_80171D74_7 *)temp_s4)->unk_00.at00.v;
        ((S_80171D74_3 *)arg1)->unk_10.n = (void *) ((S_80171D74_7 *)temp_s4)->unk_04.at00.v;
        ((S_80171D74_3 *)arg1)->unk_14 = (void *) ((S_80171D74_7 *)temp_s4)->unk_08;
        /* fallthrough */
jt_c20:
        ((S_80171D74_3 *)arg1)->unk_00.at00.v += (((S_80171D74_3 *)arg1)->unk_0C.n - ((S_80171D74_3 *)arg1)->unk_00.at00.v) / (s16) ((S_80171D74_1 *)arg0)->unk_96;
        ((S_80171D74_3 *)arg1)->unk_04.at00.v += (((S_80171D74_3 *)arg1)->unk_10.n - ((S_80171D74_3 *)arg1)->unk_04.at00.v) / (s16) ((S_80171D74_1 *)arg0)->unk_96;
        ((S_80171D74_3 *)arg1)->unk_08.at00.v += (((S_80171D74_3 *)arg1)->unk_14 - ((S_80171D74_3 *)arg1)->unk_08.at00.v) / (s16) ((S_80171D74_1 *)arg0)->unk_96;
        temp_v0_21 = ((S_80171D74_1 *)arg0)->unk_96 - 1;
        ((S_80171D74_1 *)arg0)->unk_96 = temp_v0_21;
        if ((temp_v0_21 << 0x10) <= 0) {
            tail_phase = ((S_80171D74_1 *)arg0)->unk_9A;
            ASM_KEEP(tail_phase);   /* MATCH pin: retail basic-block layout depends on it */
            ((S_80171D74_1 *)arg0)->unk_96 = 0;
            func_80173074();
            return;
        }
        goto block_152;
jt_c21:
        if (((S_80171D74_5 *)arg2)->unk_04 == 0) {
            ((S_80171D74_5 *)arg2)->unk_14 = (u16) (((S_80171D74_5 *)arg2)->unk_14 | 0x800);
            func_80173080();
            return;
        }
        goto block_152;
jt_c22:
        {
            u16 phase22;
        if (((S_80171D74_5 *)arg2)->unk_04 == 0) {
            ((S_80171D74_5 *)arg2)->unk_14 = (u16) (((S_80171D74_5 *)arg2)->unk_14 | 0x800);
        }
        temp_v0_22 = ((S_80171D74_1 *)arg0)->unk_96;
        phase22 = temp_v0_22 + 1;
        ASM_KEEP_NV(phase22);   /* MATCH pin: retail register colouring depends on it */
        ((S_80171D74_1 *)arg0)->unk_96 = phase22;
        if ((u32) (temp_v0_22 - 0xA) < 8U) {
            ((S_80171D74_1 *)arg0)->unk_A0.at00.v = (s32) (func_800644B8(((s32) (phase22 << 0x10) >> 8) - 0xA00) << 8);
            ((S_80171D74_3 *)arg1)->unk_08.at02.v = (u16) (temp_s3->unk_88 - ((S_80171D74_1 *)arg0)->unk_A0.at02.v);
        }
        }
        temp_v1_6 = (s16) ((S_80171D74_1 *)arg0)->unk_96;
        if ((temp_v1_6 == 0x19) || (temp_v1_6 == 0x1E) || (temp_v1_6 == 0x23) || (temp_v1_6 == 0x28)) {
            register s32 angle_input ASM_REG("$3");   /* MATCH pin: retail keeps a computation the compiler would drop */
            s32 angle_tmp;
            register s32 angle_result ASM_REG("$3");   /* MATCH pin: retail keeps a computation the compiler would drop */
            angle_input = temp_s3->unk_2A.n;
            angle_tmp = angle_input - 0x200;
            angle_result = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_result = angle_tmp + 0x1000;
            }
            temp_s3->unk_2A.n = angle_result;
        }
        if ((s16) ((S_80171D74_1 *)arg0)->unk_96 >= 0x2D) {
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_92.s = -0x18;
            ((S_80171D74_1 *)arg0)->unk_9E = 0;
            ((S_80171D74_1 *)arg0)->unk_A0.at00.v = 0;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
            ((S_80171D74_3 *)arg1)->unk_08.at02.v = temp_s3->unk_88;
            func_80173080();
            return;
        }
        goto block_152;
jt_c24:
        temp_v0_23 = ((S_80171D74_1 *)arg0)->unk_96 + 1;
        ((S_80171D74_1 *)arg0)->unk_96 = temp_v0_23;
        if (((s16) temp_v0_23 == 5) || ((s16) temp_v0_23 == 0xA) || ((s16) temp_v0_23 == 0xF) || ((s16) temp_v0_23 == 0x14)) {
            register s32 angle_input ASM_REG("$3");   /* MATCH pin: retail keeps a computation the compiler would drop */
            s32 angle_tmp;
            register s32 angle_result ASM_REG("$3");   /* MATCH pin: retail keeps a computation the compiler would drop */
            angle_input = temp_s3->unk_2A.n;
            angle_tmp = angle_input - 0x200;
            angle_result = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_result = angle_tmp + 0x1000;
            }
            temp_s3->unk_2A.n = angle_result;
        }
        if ((s16) ((S_80171D74_1 *)arg0)->unk_96 >= 0x18) {
            u8 *sp2_base24;
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
            ((S_80171D74_5 *)arg2)->unk_2C.p = &D_80173DA4;
            ((S_80171D74_5 *)arg2)->unk_14 = (u16) (((S_80171D74_5 *)arg2)->unk_14 & 0xF7FF);
            func_80047784(arg2, D_80173DA4[((s32) (((S_80171D74_6 *)D_80083228)->unk_00 + (s16) temp_s3->unk_2A.n + 0x100) >> 9) & 7], 0);
            sp2_base24 = (u8 *)&sp38;
            ((S_80171D74_3 *)arg1)->unk_0C.n = (s32) (SP2_X_AT(sp2_base24, temp_s3->unk_2A.n) << 0x14);
            ((S_80171D74_3 *)arg1)->unk_10.n = (s32) (SP2_Y_AT(sp2_base24, temp_s3->unk_2A.n) << 0x14);
            ((S_80171D74_3 *)arg1)->unk_14 = (void *)0xFFF00000;
            func_80173080();
            return;
        }
        goto block_152;
jt_c25:
        temp_a0_9 = ((S_80171D74_3 *)arg1)->unk_10.n;
        temp_a1_6 = ((S_80171D74_3 *)arg1)->unk_14;
        ((S_80171D74_3 *)arg1)->unk_00.at00.v = (s32) (((S_80171D74_3 *)arg1)->unk_00.at00.v + ((S_80171D74_3 *)arg1)->unk_0C.n);
        ((S_80171D74_3 *)arg1)->unk_04.at00.v = (void *) (((S_80171D74_3 *)arg1)->unk_04.at00.v + temp_a0_9);
        ((S_80171D74_3 *)arg1)->unk_08.at00.v = (void *) (((S_80171D74_3 *)arg1)->unk_08.at00.v + temp_a1_6);
        temp_v0_24 = ((S_80171D74_1 *)arg0)->unk_96 + 1;
        ((S_80171D74_1 *)arg0)->unk_96 = temp_v0_24;
        if ((s16) temp_v0_24 >= 0x28) {
            tail_phase = ((S_80171D74_1 *)arg0)->unk_9A;
            ASM_KEEP(tail_phase);   /* MATCH pin: retail basic-block layout depends on it */
            ((S_80171D74_1 *)arg0)->unk_96 = 0;
            func_80173074();
            return;
        }
        goto block_152;
jt_c30: {
        u8 *sp2_base30;
        u16 angle30;
        u16 y30;
        angle30 = temp_s3->unk_2A.v;
        sp2_base30 = (u8 *)&sp38;
        ((S_80171D74_3 *)arg1)->unk_0C.n = (s32) (SP2_X_AT(sp2_base30, angle30) << 0x13);
        y30 = SP2_Y_AT(sp2_base30, temp_s3->unk_2A.n);
        ((S_80171D74_3 *)arg1)->unk_14 = (void *)0xFFFB0000;
        ((S_80171D74_3 *)arg1)->unk_10.n = (void *) (y30 << 0x13);
        tail_phase = ((S_80171D74_1 *)arg0)->unk_9A;
        ASM_KEEP(tail_phase);   /* MATCH pin: retail basic-block layout depends on it */
        ((S_80171D74_1 *)arg0)->unk_96 = 0;
        func_80173074();
        return;
    }
jt_c31:
        temp_a0_10 = ((S_80171D74_3 *)arg1)->unk_10.n;
        temp_a1_7 = ((S_80171D74_3 *)arg1)->unk_14;
        ((S_80171D74_3 *)arg1)->unk_00.at00.v = (s32) (((S_80171D74_3 *)arg1)->unk_00.at00.v + ((S_80171D74_3 *)arg1)->unk_0C.n);
        ((S_80171D74_3 *)arg1)->unk_04.at00.v = (void *) (((S_80171D74_3 *)arg1)->unk_04.at00.v + temp_a0_10);
        ((S_80171D74_3 *)arg1)->unk_08.at00.v = (void *) (((S_80171D74_3 *)arg1)->unk_08.at00.v + temp_a1_7);
        temp_v0_25 = ((S_80171D74_1 *)arg0)->unk_96 + 1;
        ((S_80171D74_1 *)arg0)->unk_96 = temp_v0_25;
        if ((s16) temp_v0_25 >= 5) {
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
            ((S_80171D74_3 *)arg1)->unk_14 = NULL;
            ((S_80171D74_3 *)arg1)->unk_10.n = NULL;
            ((S_80171D74_3 *)arg1)->unk_0C.n = 0;
            func_80173080();
            return;
        }
        goto block_152;
jt_c32:
        temp_v0_26 = ((S_80171D74_1 *)arg0)->unk_96 + 1;
        ((S_80171D74_1 *)arg0)->unk_96 = temp_v0_26;
        if (((s16) temp_v0_26 == 2) || ((s16) temp_v0_26 == 8) || ((s16) temp_v0_26 == 0xA) || ((s16) temp_v0_26 == 0x10) || ((s16) temp_v0_26 == 0x12)) {
            var_v1_6 = temp_s3->unk_2A.n;
            temp_a0_11 = var_v1_6 + 0x200;
            var_v1_6 = temp_a0_11;
            if (temp_a0_11 >= 0x1000) {
                var_v1_6 = temp_a0_11 - 0x1000;
            }
            temp_s3->unk_2A.n = (u16) var_v1_6;
        }
        var_v1_6 = (s16) ((S_80171D74_1 *)arg0)->unk_96;
        if ((var_v1_6 == 4) || (var_v1_6 == 6) || (var_v1_6 == 0xC) || (var_v1_6 == 0xE) || (var_v1_6 == 0x14)) {
            var_v1_6 = temp_s3->unk_2A.n;
            temp_a0_12 = var_v1_6 - 0x200;
            var_v1_6 = temp_a0_12;
            if ((s16) temp_a0_12 < 0) {
                var_v1_6 = temp_a0_12 + 0x1000;
            }
            temp_s3->unk_2A.n = var_v1_6;
        }
        var_v1_6 = (s16) ((S_80171D74_1 *)arg0)->unk_96;
        if (var_v1_6 == 0x1A) {
            ((S_80171D74_5 *)arg2)->unk_2C.p = &D_80173DA4;
            ((S_80171D74_5 *)arg2)->unk_14 = (u16) (((S_80171D74_5 *)arg2)->unk_14 & 0xF7FF);
            func_80047784(arg2, D_80173DA4[((s32) (((S_80171D74_6 *)D_80083228)->unk_00 + (s16) temp_s3->unk_2A.n + 0x100) >> 9) & 7], 0);
        }
        if ((s16) ((S_80171D74_1 *)arg0)->unk_96 >= 0x1E) {
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
            ((S_80171D74_3 *)arg1)->unk_14 = (void *)0xFFF80000;
            func_80173080();
            return;
        }
        goto block_152;
jt_c33:
        ((S_80171D74_3 *)arg1)->unk_08.at00.v = (void *) (((S_80171D74_3 *)arg1)->unk_08.at00.v + ((S_80171D74_3 *)arg1)->unk_14);
        temp_v0_27 = ((S_80171D74_1 *)arg0)->unk_96 + 1;
        ((S_80171D74_1 *)arg0)->unk_96 = temp_v0_27;
        if ((s16) temp_v0_27 >= 0xA) {
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
            temp_v0_27 = ((S_80171D74_3 *)arg1)->unk_08.at02.v;
            ((S_80171D74_3 *)arg1)->unk_14 = NULL;
            ((S_80171D74_3 *)arg1)->unk_10.n = NULL;
            ((S_80171D74_3 *)arg1)->unk_0C.n = 0;
            temp_v1_7 = temp_s3->unk_88;
            ((S_80171D74_1 *)arg0)->unk_9E = 0;
            ((S_80171D74_1 *)arg0)->unk_A0.at00.v = 0;
            ((S_80171D74_1 *)arg0)->unk_92.u = (u16) (temp_v0_27 - temp_v1_7);
            var_v1_8 = temp_s3->unk_2A.n;
            temp_a0_13 = var_v1_8 + 0x400;
            var_v1_8 = temp_a0_13;
            if (temp_a0_13 >= 0x1000) {
                var_v1_8 = temp_a0_13 - 0x1000;
            }
            temp_s3->unk_2A.n = (u16) var_v1_8;
            func_80047784(arg2, *(((S_80171D74_5 *)arg2)->unk_2C.p2 + (((s32) (((S_80171D74_6 *)D_80083228)->unk_00 + var_v1_8 + 0x100) >> 9) & 7)), 0);
        }
        goto block_152;
jt_c34: {
        temp_v0_28 = ((S_80171D74_1 *)arg0)->unk_96 + 1;
        ((S_80171D74_1 *)arg0)->unk_96 = temp_v0_28;
        if ((temp_v0_28 & 3) == 3) {
            register s32 angle_input ASM_REG("$3");   /* MATCH pin: retail keeps a computation the compiler would drop */
            s32 angle_tmp;
            register s32 angle_result ASM_REG("$3");   /* MATCH pin: retail keeps a computation the compiler would drop */
            angle_input = temp_s3->unk_2A.n;
            angle_tmp = angle_input - 0x200;
            angle_result = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_result = angle_tmp + 0x1000;
            }
            temp_s3->unk_2A.n = angle_result;
        }
        temp_a1_8 = ((0x61 - (s16) ((S_80171D74_1 *)arg0)->unk_96) * 0x60000) / 97;
        {
            u8 *base34 = (u8 *)&sp38;
            s32 comp_x = SP2_X_AT(base34, temp_s3->unk_2A.n);
            ((S_80171D74_3 *)arg1)->unk_0C.n = temp_a1_8 * comp_x;
            base34 = (u8 *)&sp38;
            {
                s16 comp_y = (s16) SP2_Y_AT(base34, temp_s3->unk_2A.n);
                ((S_80171D74_3 *)arg1)->unk_10.n = temp_a1_8 * comp_y;
            }
            ((S_80171D74_3 *)arg1)->unk_00.at00.v += ((S_80171D74_3 *)arg1)->unk_0C.n;
            ((S_80171D74_3 *)arg1)->unk_04.at00.v += ((S_80171D74_3 *)arg1)->unk_10.n;
        }
        if ((s16) ((S_80171D74_1 *)arg0)->unk_96 >= 0x58) {
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
            {
                u16 *reset_base = (u16 *)D_80083780;
                ((S_80171D74_3 *)arg1)->unk_00.at02.v = reset_base[1];
                ((S_80171D74_3 *)arg1)->unk_04.at02u.v = reset_base[3];
            }
            func_8017301C(arg0);
            return;
        }
        goto block_147;
    }
jt_c40:
        if ((func_800F685C(temp_a0, temp_a1_2) << 0x10) != 0) {
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
            D_80083460[5] = (u16) (D_80083460[5] + 1);
        }
        goto block_152;
jt_c41:
        temp_v0_29 = ((S_80171D74_1 *)arg0)->unk_96 + 1;
        ((S_80171D74_1 *)arg0)->unk_96 = temp_v0_29;
        if ((s16) temp_v0_29 >= 0x3C) {
            tail_phase = ((S_80171D74_1 *)arg0)->unk_9A;
            ASM_KEEP(tail_phase);   /* MATCH pin: retail basic-block layout depends on it */
            ((S_80171D74_1 *)arg0)->unk_96 = 0;
            func_80173074();
            return;
        }
        goto block_152;
jt_c45:
        if ((func_800F685C(temp_a0, temp_a1_2) << 0x10) != 0) {
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
            D_80083460[5] = (u16) (D_80083460[5] + 1);
        }
        goto block_146;
jt_c46:
        temp_v0_30 = ((S_80171D74_1 *)arg0)->unk_96 + 1;
        ((S_80171D74_1 *)arg0)->unk_96 = temp_v0_30;
        if ((s16) temp_v0_30 >= 0x3C) {
            ((S_80171D74_1 *)arg0)->unk_96 = 0U;
            ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
        }
        goto block_146;
jt_c35:
block_146:
        func_8016F79C(arg0, arg1, arg2);
        goto block_147;
jt_c5:
jt_c12:
jt_c14:
jt_c18:
block_147:
    func_8016F5D8(arg0, arg1, arg2);
    {
        u32 tail_page147;
        tail_page147 = 0x80170000;
        ASM_PAGEBASE_PIN(tail_page147);   /* MATCH pin: retail delay-slot contents depend on it */
    }
    func_80173084();

jt_c42:
jt_c47:
        func_800945E8(D_800E3D7C[0], temp_a1_2);
        {
            s32 fwd_a0;
            s32 fwd_a1;
            s32 fwd_a2;
            s32 fwd_a3;
            ASM_SET(fwd_a0);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            ASM_SET(fwd_a1);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            ASM_SET(fwd_a2);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            ASM_SET(fwd_a3);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            func_800948BC(fwd_a0, fwd_a1, fwd_a2, fwd_a3);
        }
        D_80082E76[0] = 0x8000;
        func_80041094(6, 0, 0, 0, 0x8000);
        ((S_80171D74_1 *)arg0)->unk_9A = (u8) (((S_80171D74_1 *)arg0)->unk_9A + 1);
        goto block_152;
jt_c8:
jt_c23:
jt_c26:
jt_c27:
jt_c28:
jt_c29:
jt_c36:
jt_c37:
jt_c38:
jt_c39:
jt_c43:
jt_c44:
jt_c48:
block_152:
    if (D_80175D54[0] != 0) {
        temp_s2_2 = ((s32) (((S_80171D74_6 *)D_80083228)->unk_00 + (s16) temp_s3->unk_2A.n + 0x100) >> 9) & 7;
        if (((S_80171D74_1 *)arg0)->unk_94 != temp_s2_2) {
            func_80047738(arg2, *(((S_80171D74_5 *)arg2)->unk_2C.p2 + temp_s2_2), ((S_80171D74_5 *)arg2)->unk_04);
            ((S_80171D74_1 *)arg0)->unk_94 = temp_s2_2;
        }
        if ((*(u8 *)((u8 *)D_8006CCF8 + temp_s2_2)) != 0) {
            u16 tail_flag;
            tail_flag = ((S_80171D74_5 *)arg2)->unk_14 | 1;
            ASM_TAILSLOT_PIN(tail_flag);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_80173110();
            return;
        }
        ((S_80171D74_5 *)arg2)->unk_14 = (u16) (((S_80171D74_5 *)arg2)->unk_14 & 0xFFFE);
    }
    return;

}
