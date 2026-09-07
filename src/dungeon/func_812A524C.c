#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_812A524C_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
} S_812A524C_0;   /* &D_800FBE22 in func_812A524C */

typedef struct S_812A524C_1 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
} S_812A524C_1;   /* &D_800FBE20 in func_812A524C */


typedef struct S_812A524C_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x60];
    M2C_UNK (*unk_8C)(void *, void *, void *, void *);
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_90;   /* overlapping accesses */
    s16 unk_94;
    u8 pad_96[0x2];
    u16 unk_98;
    u8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x1];
    union { s8 s; u8 u; } unk_9D;   /* accessed as both */
    u16 unk_9E;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A0;   /* overlapping accesses */
    u8 pad_A4[0xC];
    s32 unk_B0;
    u8 pad_B4[0x4];
    u8 unk_B8;
    u8 unk_B9;
} S_812A524C_3;   /* arg0 in func_812A524C */

typedef struct S_812A524C_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    u16 unk_88;
} S_812A524C_4;   /* arg3 in func_812A524C */

typedef struct S_812A524C_5 {
    void * unk_00;
} S_812A524C_5;   /* &D_800FBE54 in func_812A524C */

typedef struct S_812A524C_6 {
    u16 unk_00;
} S_812A524C_6;   /* &D_80013714 in func_812A524C */

typedef struct S_812A524C_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_812A524C_7;   /* ev0 in func_812A524C */

typedef struct S_812A524C_8 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_8;   /* pos0 in func_812A524C */

typedef struct S_812A524C_9 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x6E];
    u8 unk_9A;
} S_812A524C_9;   /* temp_actor in func_812A524C */

typedef struct S_812A524C_10 {
    u8 pad_00[0x24];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_812A524C_10;   /* ev1 in func_812A524C */

typedef struct S_812A524C_11 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_11;   /* pos1 in func_812A524C */

typedef struct S_812A524C_12 {
    u8 pad_00[0x24];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_812A524C_12;   /* ev2 in func_812A524C */

typedef struct S_812A524C_13 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_13;   /* pos2 in func_812A524C */

typedef struct S_812A524C_14 {
    u8 pad_00[0x24];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_812A524C_14;   /* ev3 in func_812A524C */

typedef struct S_812A524C_15 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_15;   /* pos3 in func_812A524C */

typedef struct S_812A524C_16 {
    u8 pad_00[0x24];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_812A524C_16;   /* ev4 in func_812A524C */

typedef struct S_812A524C_17 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_17;   /* pos4 in func_812A524C */

typedef struct S_812A524C_18 {
    u8 pad_00[0x24];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_812A524C_18;   /* ev5 in func_812A524C */

typedef struct S_812A524C_19 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_19;   /* pos5 in func_812A524C */

typedef struct S_812A524C_20 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_812A524C_20;   /* flag_base in func_812A524C */

typedef struct S_812A524C_21 {
    u8 pad_00[0x24];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_812A524C_21;   /* ev6 in func_812A524C */

typedef struct S_812A524C_22 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_22;   /* pos6 in func_812A524C */

typedef struct S_812A524C_23 {
    u8 pad_00[0x24];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_812A524C_23;   /* ev7 in func_812A524C */

typedef struct S_812A524C_24 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_24;   /* pos7 in func_812A524C */

typedef struct S_812A524C_25 {
    u8 pad_00[0x24];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_812A524C_25;   /* ev8 in func_812A524C */

typedef struct S_812A524C_26 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_26;   /* pos8 in func_812A524C */

typedef struct S_812A524C_27 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_812A524C_27;   /* ev9 in func_812A524C */

typedef struct S_812A524C_28 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_28;   /* pos9 in func_812A524C */

typedef struct S_812A524C_29 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_812A524C_29;   /* ev10 in func_812A524C */

typedef struct S_812A524C_30 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_30;   /* pos10 in func_812A524C */

typedef struct S_812A524C_31 {
    u8 pad_00[0x24];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_812A524C_31;   /* ev11 in func_812A524C */

typedef struct S_812A524C_32 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_32;   /* pos11 in func_812A524C */

typedef struct S_812A524C_33 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_812A524C_33;   /* var_v0_7 in func_812A524C */

typedef struct S_812A524C_34 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_812A524C_34;   /* temp_v1_3 in func_812A524C */

typedef struct S_812A524C_35 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_812A524C_35;   /* pos12 in func_812A524C */

typedef struct S_812A524C_36 {
    union { s32 n; volatile s32 v; } unk_00;   /* accessed as both */
} S_812A524C_36;   /* &D_800E296C in func_812A524C */

typedef struct S_812A524C_37 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_812A524C_37;   /* arg1 in func_812A524C */

typedef struct S_812A524C_38 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    union { u16 n; volatile u16 v; } unk_14;   /* accessed as both */
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    union { u8 * p; s32 i; } unk_2C;   /* accessed as both */
} S_812A524C_38;   /* arg2 in func_812A524C */

typedef struct S_812A524C_39 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x6E];
    u8 unk_9A;
} S_812A524C_39;   /* ((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v in func_812A524C */

typedef struct S_812A524C_40 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_812A524C_40;   /* ((S_812A524C_5 *)(&D_800FBE54))->unk_00 in func_812A524C */


M2C_UNK func_800353F4(); /* extern */
M2C_UNK func_80042B68();                /* extern */
M2C_UNK func_80047738();              /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
M2C_UNK func_800A020C();                 /* extern */
s32 func_800A2C34();                          /* extern */
M2C_UNK func_800A48F0();       /* extern */
M2C_UNK func_800A9A0C();                      /* extern */
s32 func_800A9E70();  /* extern */
M2C_UNK func_800AA36C(); /* extern */
s32 func_800BCB04();                   /* extern */
s32 func_800F6D28();    /* extern */
void *func_800F6DFC();                /* extern */
void func_80170CE8() __attribute__((noreturn));     /* extern */
void func_801713EC() __attribute__((noreturn));     /* extern */
void func_80171468() __attribute__((noreturn));     /* extern */
void func_801714E4() __attribute__((noreturn));     /* extern */
void func_80171968() __attribute__((noreturn));     /* extern */
void func_80171AD8() __attribute__((noreturn));     /* extern */
void func_80171B6C() __attribute__((noreturn));     /* extern */
void func_80171BEC() __attribute__((noreturn));     /* extern */
void func_80171CD4() __attribute__((noreturn));     /* extern */
void func_80171E8C() __attribute__((noreturn));     /* extern */
void func_80171ECC() __attribute__((noreturn));     /* extern */
void func_80171ED0() __attribute__((noreturn));     /* extern */
void func_80171F74() __attribute__((noreturn));     /* extern */
extern u8 D_80010248[];
extern u16 D_80013714[8];
extern u8 D_8006CCF8[16];
extern u8 D_8006EE9C[16];
extern u8 D_8006F47A[16];
extern u8 D_8006F50D[16];
extern u8 D_8006F6B9[16];
extern u8 D_8006F9D0[16];
extern u8 D_8006FD01[16];
extern u8 D_8006FFB7[16];
extern u8 D_800703D9[16];
extern u8 D_80070684[16];
extern u8 D_80070AF8[16];
extern u8 D_80070C11[16];
extern u8 D_80070E63[16];
extern u8 D_80082E80[64];
extern u16 D_80082EA4[8];
extern u8 D_80083160[16];
extern s16 D_80083228[8];
extern u16 D_80083462[8];
extern u8 D_80083780[16];
extern u8 D_800E296C[16];
extern u8 D_800E3D7C[16];
extern u8 D_800FB3C8[16];
extern u8 D_800FB8DF[16];
extern u8 D_800FBAD7[16];
extern u8 D_800FBD96[16];
extern u8 D_800FBE20[16];
extern u8 D_800FBE22[16];
extern u8 D_800FBE54[16];
typedef struct {
    u8 bytes[16];
} __attribute__((packed)) Packed16;
extern Packed16 D_80170804;
extern u8 D_80171FA4[16];
extern u8 D_80175C30[16];
extern void (*D_80175CC8[])(void *, void *, void *, void *);

#define event_base ((u8 *)&D_80082E80)
#define position_base ((u8 *)&D_80083780)

void func_812A524C(void *in0, void *in1, void *in2) {
    Packed16 stack_copy;
    Packed16 *copy_src;
    void *arg0 = in0;
    void *arg1 = in1;
    void *arg2 = in2;
    void *arg3;
    register u16 *copy_base ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 tail_value;
    s32 tail_acc;
    register u32 early_page ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
    u8 *flag_base;
    u8 *ev0;
    u8 *pos0;
    u8 *ev1;
    u8 *pos1;
    u8 *ev2;
    u8 *pos2;
    u8 *ev3;
    u8 *pos3;
    u8 *ev4;
    u8 *pos4;
    u8 *ev5;
    u8 *pos5;
    u8 *ev6;
    u8 *pos6;
    u8 *ev7;
    u8 *pos7;
    u8 *ev8;
    u8 *pos8;
    u8 *ev9;
    u8 *pos9;
    u8 *ev10;
    u8 *pos10;
    u8 *ev11;
    u8 *pos11;
    u8 *pos12;
    M2C_UNK (*temp_v0_4)(void *, void *, void *, void *);
    M2C_UNK (*temp_v1_4)(void *, void *, void *, void *);
    M2C_UNK *var_v0_10;
    M2C_UNK *var_v0_6;
    M2C_UNK *var_v0_7;
    u8 *var_v1;
    u8 *var_v1_2;
    u8 *var_v1_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s16 temp_a0_6;
    s16 temp_s2;
    s16 temp_v0_6;
    s32 temp_a0;
    s32 temp_a0_3;
    s32 temp_a1_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_5;
    s32 temp_v1_12;
    s32 temp_v1_6;
    s32 temp_v1_9;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 loop_hi;
    s32 loop_lo;
    s32 clear_flags;
    s32 motion_x;
    register s32 motion_y ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 var_v0_11;
    s32 var_v0_8;
    s32 var_v0_9;
    s32 scaled_x;
    register s32 event_x1 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    register s32 event_x2 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    register s32 event_x3 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    register s32 event_x4 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    register s32 event_x5 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    register s32 event_x6 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    register s32 event_x7 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    register s32 event_x8 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    register s32 event_x11 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    s32 final_tail_value;
    s32 fixed_flags;
    s16 temp_s0_3;
    s16 temp_s0_4;
    u16 *var_v0;
    u16 temp_v1_10;
    u16 temp_v1_11;
    register s32 temp_v1_5 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    u16 first_flags;
    u16 temp_v1_7;
    u16 temp_v1_8;
    u16 var_v0_12;
    u8 temp_a0_2;
    u8 temp_a1;
    u8 temp_s0;
    register u8 temp_s0_2 ASM_REG("$16");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 temp_v1;
    u8 temp_v1_2;
    void **var_v0_2;
    void **var_v0_3;
    void **var_v0_4;
    void **var_v0_5;
    void *temp_v0_3;
    S_812A524C_34 *temp_v1_3;
    S_812A524C_9 *temp_actor;

    copy_src = &D_80170804;
    ASM_KEEP(arg0);   /* MATCH pin: retail schedule: same instructions, different order without it */
    stack_copy = *copy_src;
    arg3 = arg0;
    flag_base = D_80083160;
    copy_base = (u16 *)&stack_copy;
    if (((S_812A524C_0 *)(&D_800FBE22))->unk_00.s != ((S_812A524C_1 *)(&D_800FBE20))->unk_00.s) {
        ((S_812A524C_0 *)(&D_800FBE22))->unk_00.u = (u16) ((S_812A524C_1 *)(&D_800FBE20))->unk_00.u;
    }
    if (((S_812A524C_1 *)(&D_800FBE20))->unk_00.s != ((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A) {
        ((S_812A524C_1 *)(&D_800FBE20))->unk_00.u = (u16) ((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A;
    }
    temp_s0 = ((S_812A524C_3 *)arg0)->unk_B8;
    if (temp_s0 == 2) {
        temp_v0 = func_800F6D28(arg1);
        ((S_812A524C_3 *)arg0)->unk_2A = (s16) (temp_v0 << 9);
        if ((((S_812A524C_3 *)arg0)->unk_B8 == temp_s0) && (((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A == 0xE)) {
            ((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_2A = (s16) (copy_base[temp_v0 & 7] << 9);
        }
    }
    if (((S_812A524C_3 *)arg0)->unk_B8 == 3) {
        ((S_812A524C_3 *)arg0)->unk_B8 = 0U;
        func_800AA36C(arg0, arg1, arg2, arg3);
    }
    if (((S_812A524C_3 *)arg0)->unk_B8 != 0) {
        func_800A9A0C(arg3);
        if (D_80083462[0] & 0x2000) {
            ((S_812A524C_4 *)arg3)->unk_71 = (u8) (((S_812A524C_4 *)arg3)->unk_71 & 0x7F);
        }
    }
    if ((u32) (D_80082EA4[0] - 0x2536) < 2U) {
        ((S_812A524C_3 *)arg0)->unk_B0 = (s32) (((S_812A524C_3 *)arg0)->unk_B0 | 0x20000);
    }
    if (!(((S_812A524C_3 *)arg0)->unk_B0 & 0x20000)) {
        if (((S_812A524C_5 *)(&D_800FBE54))->unk_00 == NULL) goto block_27;
        func_800A48F0(((S_812A524C_5 *)(&D_800FBE54))->unk_00 + 0x20, 1, 0xA);
        early_page = 0x80010000;
        ASM_PAGEBASE_PIN(early_page);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80170CE8();
    }
    goto block_26;
action_10:
    func_800353F4(&D_8006F6B9);
    ((S_812A524C_4 *)arg3)->unk_6D = 0U;
    ((S_812A524C_3 *)arg0)->unk_9B = 0;
    ((S_812A524C_3 *)arg0)->unk_B8 = 1U;
    ((S_812A524C_3 *)arg0)->unk_B0 |= 0x10;
    func_801713EC();
action_80:
    func_800353F4(&D_8006FFB7);
    ((S_812A524C_4 *)arg3)->unk_6D = 0U;
    ((S_812A524C_3 *)arg0)->unk_9B = 0;
    ((S_812A524C_3 *)arg0)->unk_B8 = 1U;
    ((S_812A524C_3 *)arg0)->unk_B0 |= 0x80;
    func_80171468();
action_100:
    func_800353F4(&D_800703D9);
    ((S_812A524C_4 *)arg3)->unk_6D = 0U;
    ((S_812A524C_3 *)arg0)->unk_9B = 0;
    ((S_812A524C_3 *)arg0)->unk_B8 = temp_s0_2;
    ((S_812A524C_3 *)arg0)->unk_B0 |= 0x100;
    func_801714E4();
block_26:
    temp_a0 = (s32) ((S_812A524C_5 *)(&D_800FBE54))->unk_00;
    if (temp_a0 != 0) {
        func_80042B68(temp_a0 + 0x20, 1);
        ((S_812A524C_5 *)(&D_800FBE54))->unk_00 = NULL;
    }
block_27:
    ASM_CLOBBER("$18");   /* MATCH pin: keeps a constant in a register as retail does */
    if (!(((S_812A524C_6 *)(&D_80013714))->unk_00 & 1)) {
        if (((S_812A524C_3 *)arg0)->unk_B8 == 0) {
            if (!(D_80083462[0] & 0x2000) && ((func_800A2C34(arg3) << 0x10) == 0) && (ev0 = (u8 *)&D_80082E80, pos0 = (u8 *)&D_80083780, (((((S_812A524C_7 *)ev0)->unk_24 << 6) + 0x20) == ((S_812A524C_8 *)pos0)->unk_02)) && (((((S_812A524C_7 *)ev0)->unk_25 << 6) + 0x20) == ((S_812A524C_8 *)pos0)->unk_06)) {
                temp_v1 = ((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A;
                if ((temp_v1 != 0x19) && (temp_v1 != 0x1B) && !(((S_812A524C_4 *)arg3)->unk_1C & 0x80000)) {
                    if ((((S_812A524C_3 *)arg0)->unk_B9 == 0) && !(D_80013714[0] & 1)) {
                        ((S_812A524C_3 *)arg0)->unk_B9 = 1U;
                        func_800353F4(&D_8006EE9C);
                        ((S_812A524C_4 *)arg3)->unk_6D = 0U;
                        ((S_812A524C_3 *)arg0)->unk_9B = 0;
                        ((S_812A524C_3 *)arg0)->unk_B8 = 2U;
                        temp_v0_2 = func_800F6D28(arg1);
                        temp_actor = ((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v;
                        ((S_812A524C_4 *)arg3)->unk_2A = (s16) (temp_v0_2 << 9);
                        if (temp_actor->unk_9A == 0xE) {
                            temp_actor->unk_2A = (s16) (((u16 *)&stack_copy)[temp_v0_2 & 7] << 9);
                        }
                        ((S_812A524C_5 *)(&D_800FBE54))->unk_00 = func_800F6DFC(arg3);
                    }
                    if (((S_812A524C_3 *)arg0)->unk_B8 == 0) {
                        if (!(((S_812A524C_3 *)arg0)->unk_B0 & 0x20)) {
                            ev1 = (u8 *)&D_80082E80;
                            if ((((S_812A524C_10 *)ev1)->unk_24.at00.v == 0x519) || (((S_812A524C_10 *)ev1)->unk_24.at00.v == 0x619)) {
                                pos1 = (u8 *)&D_80083780;
                                event_x1 = ((S_812A524C_10 *)ev1)->unk_24.at00u.v;
                                if (((event_x1 << 6) + 0x20) == ((S_812A524C_11 *)pos1)->unk_02) {
                                    if (((((S_812A524C_10 *)ev1)->unk_24.at01.v << 6) + 0x20) == ((S_812A524C_11 *)pos1)->unk_06) {
                                        func_800353F4(&D_8006F9D0);
                                        ((S_812A524C_4 *)arg3)->unk_6D = 0U;
                                        ((S_812A524C_3 *)arg0)->unk_9B = 0;
                                        ((S_812A524C_3 *)arg0)->unk_B8 = 1U;
                                        ((S_812A524C_3 *)arg0)->unk_B0 = (s32) (((S_812A524C_3 *)arg0)->unk_B0 | 0x20);
                                    }
                                }
                            }
                            temp_v1_2 = ((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A;
                            if ((temp_v1_2 != 0x19) && (temp_v1_2 != 0x1B) && ((((S_812A524C_0 *)(&D_800FBE22))->unk_00.s == 0x1B) || (((S_812A524C_0 *)(&D_800FBE22))->unk_00.s == 0x1F) || (((S_812A524C_0 *)(&D_800FBE22))->unk_00.s == 0x20) || (((S_812A524C_1 *)(&D_800FBE20))->unk_00.s == 0x1B) || (((S_812A524C_1 *)(&D_800FBE20))->unk_00.s == 0x1F) || (((S_812A524C_1 *)(&D_800FBE20))->unk_00.s == 0x20))) {
                                func_800353F4(&D_8006F9D0);
                                ((S_812A524C_4 *)arg3)->unk_6D = 0U;
                                ((S_812A524C_3 *)arg0)->unk_9B = 0;
                                ((S_812A524C_3 *)arg0)->unk_B8 = 1U;
                                ((S_812A524C_3 *)arg0)->unk_B0 = (s32) (((S_812A524C_3 *)arg0)->unk_B0 | 0x20);
                            }
                        }
                        if (((S_812A524C_3 *)arg0)->unk_B8 == 0) {
                            if (!(((S_812A524C_3 *)arg0)->unk_B0 & 0x4000)) {
                                ev2 = (u8 *)&D_80082E80;
                                if ((((S_812A524C_12 *)ev2)->unk_24.at00.v == 0x2B2D) || (((S_812A524C_12 *)ev2)->unk_24.at00.v == 0x2C2D)) {
                                    pos2 = (u8 *)&D_80083780;
                                    event_x2 = ((S_812A524C_12 *)ev2)->unk_24.at00u.v;
                                    if (((event_x2 << 6) + 0x20) == ((S_812A524C_13 *)pos2)->unk_02) {
                                        if (((((S_812A524C_12 *)ev2)->unk_24.at01.v << 6) + 0x20) == ((S_812A524C_13 *)pos2)->unk_06) {
                                            func_800353F4(&D_800FB8DF);
                                            ((S_812A524C_4 *)arg3)->unk_6D = 0U;
                                            ((S_812A524C_3 *)arg0)->unk_9B = 0;
                                            ((S_812A524C_3 *)arg0)->unk_B8 = 1U;
                                            ((S_812A524C_3 *)arg0)->unk_B0 = (s32) (((S_812A524C_3 *)arg0)->unk_B0 | 0x4000);
                                        }
                                    }
                                }
                                if (((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A == 0x1C) {
                                    func_800353F4(&D_800FB8DF);
                                    ((S_812A524C_4 *)arg3)->unk_6D = 0U;
                                    ((S_812A524C_3 *)arg0)->unk_9B = 0;
                                    ((S_812A524C_3 *)arg0)->unk_B8 = 1U;
                                    ((S_812A524C_3 *)arg0)->unk_B0 = (s32) (((S_812A524C_3 *)arg0)->unk_B0 | 0x4000);
                                }
                            }
                            if (((S_812A524C_3 *)arg0)->unk_B8 == 0) {
                                if (!(((S_812A524C_3 *)arg0)->unk_B0 & 0x200) && (ev3 = (u8 *)&D_80082E80, ((u32) (((S_812A524C_14 *)ev3)->unk_24.at00.v - 0xB36) < 2U)) && (pos3 = (u8 *)&D_80083780, event_x3 = ((S_812A524C_14 *)ev3)->unk_24.at00u.v, (((event_x3 << 6) + 0x20) == ((S_812A524C_15 *)pos3)->unk_02)) && (((((S_812A524C_14 *)ev3)->unk_24.at01.v << 6) + 0x20) == ((S_812A524C_15 *)pos3)->unk_06)) {
                                    func_800353F4(&D_80070684);
                                    ((S_812A524C_4 *)arg3)->unk_6D = 0U;
                                    ((S_812A524C_3 *)arg0)->unk_9B = 0;
                                    ((S_812A524C_3 *)arg0)->unk_B8 = 1U;
                                    ((S_812A524C_3 *)arg0)->unk_B0 = (s32) (((S_812A524C_3 *)arg0)->unk_B0 | 0x200);
                                }
                                if (((S_812A524C_3 *)arg0)->unk_B8 == 0) {
                                    if (!(((S_812A524C_3 *)arg0)->unk_B0 & 0x8000) && (ev4 = (u8 *)&D_80082E80, ((u32) (((S_812A524C_16 *)ev4)->unk_24.at00.v - 0x1236) < 2U)) && (pos4 = (u8 *)&D_80083780, event_x4 = ((S_812A524C_16 *)ev4)->unk_24.at00u.v, (((event_x4 << 6) + 0x20) == ((S_812A524C_17 *)pos4)->unk_02)) && (((((S_812A524C_16 *)ev4)->unk_24.at01.v << 6) + 0x20) == ((S_812A524C_17 *)pos4)->unk_06)) {
                                        func_800353F4(&D_800FBAD7);
                                        ((S_812A524C_4 *)arg3)->unk_6D = 0U;
                                        ((S_812A524C_3 *)arg0)->unk_9B = 0;
                                        ((S_812A524C_3 *)arg0)->unk_B8 = 1U;
                                        ((S_812A524C_3 *)arg0)->unk_B0 = (s32) (((S_812A524C_3 *)arg0)->unk_B0 | 0x8000);
                                    }
                                    if (((S_812A524C_3 *)arg0)->unk_B8 == 0) {
                                        if (!(((S_812A524C_3 *)arg0)->unk_B0 & 2)) {
                                            ev5 = (u8 *)&D_80082E80;
                                            if ((u32) (((S_812A524C_18 *)ev5)->unk_24.at00.v - 0x1D07) < 2U) {
                                                pos5 = (u8 *)&D_80083780;
                                                event_x5 = ((S_812A524C_18 *)ev5)->unk_24.at00u.v;
                                                if (((event_x5 << 6) + 0x20) == ((S_812A524C_19 *)pos5)->unk_02) {
                                                    if (((((S_812A524C_18 *)ev5)->unk_24.at01.v << 6) + 0x20) == ((S_812A524C_19 *)pos5)->unk_06) {
                                                        func_800353F4(&D_8006F47A);
                                                        ((S_812A524C_4 *)arg3)->unk_6D = 0U;
                                                        ((S_812A524C_3 *)arg0)->unk_9B = 0;
                                                        ((S_812A524C_3 *)arg0)->unk_B8 = 1U;
                                                        ((S_812A524C_3 *)arg0)->unk_B0 = (s32) (((S_812A524C_3 *)arg0)->unk_B0 | 2);
                                                    }
                                                }
                                            }
                                            if ((((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A != 0x19) && (((S_812A524C_20 *)flag_base)->unk_10 & 0x20)) {
                                                func_800353F4(&D_8006F47A);
                                                ((S_812A524C_4 *)arg3)->unk_6D = 0U;
                                                ((S_812A524C_3 *)arg0)->unk_9B = 0;
                                                ((S_812A524C_3 *)arg0)->unk_B8 = 1U;
                                                ((S_812A524C_3 *)arg0)->unk_B0 = (s32) (((S_812A524C_3 *)arg0)->unk_B0 | 2);
                                            }
                                        }
                                        if (((S_812A524C_3 *)arg0)->unk_B8 == 0) {
                                            if (!(((S_812A524C_3 *)arg0)->unk_B0 & 4)) {
                                                ev6 = (u8 *)&D_80082E80;
                                                if ((u32) (((S_812A524C_21 *)ev6)->unk_24.at00.v - 0x291E) < 3U) {
                                                    pos6 = (u8 *)&D_80083780;
                                                    event_x6 = ((S_812A524C_21 *)ev6)->unk_24.at00u.v;
                                                    if (((event_x6 << 6) + 0x20) == ((S_812A524C_22 *)pos6)->unk_02) {
                                                        if (((((S_812A524C_21 *)ev6)->unk_24.at01.v << 6) + 0x20) == ((S_812A524C_22 *)pos6)->unk_06) {
                                                            func_800353F4(&D_8006F50D);
                                                            ((S_812A524C_4 *)arg3)->unk_6D = 0U;
                                                            ((S_812A524C_3 *)arg0)->unk_9B = 0;
                                                            ((S_812A524C_3 *)arg0)->unk_B8 = 1U;
                                                            ((S_812A524C_3 *)arg0)->unk_B0 = (s32) (((S_812A524C_3 *)arg0)->unk_B0 | 4);
                                                        }
                                                    }
                                                }
                                                if ((((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A != 0x19) && (((S_812A524C_20 *)flag_base)->unk_08 & 0x10)) {
                                                    func_800353F4(&D_8006F50D);
                                                    ((S_812A524C_4 *)arg3)->unk_6D = 0U;
                                                    ((S_812A524C_3 *)arg0)->unk_9B = 0;
                                                    ((S_812A524C_3 *)arg0)->unk_B8 = 1U;
                                                    ((S_812A524C_3 *)arg0)->unk_B0 = (s32) (((S_812A524C_3 *)arg0)->unk_B0 | 4);
                                                }
                                            }
                                            if (((S_812A524C_3 *)arg0)->unk_B8 == 0) {
                                                if (!(((S_812A524C_3 *)arg0)->unk_B0 & 0x10) && (((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A != 0x23)) {
                                                    var_a0 = 0;
                                                    loop_hi = 0xF;
                                                    loop_lo = 2;
                                                    var_v1 = (u8 *)0x80010000;
loop_102:
                                                    if ((var_v1[0x249] != loop_hi) || (var_v1[0x248] != loop_lo)) {
                                                        var_a0 += 1;
                                                        var_v1 += 4;
                                                        if (var_a0 >= 0x14) {
                                                            goto block_105;
                                                        }
                                                        goto loop_102;
                                                    }
                                                    goto action_10;
                                                }
block_105:
                                                if (((S_812A524C_3 *)arg0)->unk_B8 == 0) {
                                                    if (!(((S_812A524C_3 *)arg0)->unk_B0 & 0x80) && (((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A != 0x23)) {
                                                        var_a0_2 = 0;
                                                        loop_hi = 0x12;
                                                        loop_lo = 0x15;
                                                        var_v1_2 = (u8 *)0x80010000;
loop_109:
                                                        if ((var_v1_2[0x249] != loop_hi) || (var_v1_2[0x248] != loop_lo)) {
                                                            var_a0_2 += 1;
                                                            var_v1_2 += 4;
                                                            if (var_a0_2 >= 0x14) {
                                                                goto block_112;
                                                            }
                                                            goto loop_109;
                                                        }
                                                        goto action_80;
                                                    }
block_112:
                                                    if (((S_812A524C_3 *)arg0)->unk_B8 == 0) {
                                                        if (!(((S_812A524C_3 *)arg0)->unk_B0 & 0x100) && (((S_812A524C_39 *)(((Rec_D_800E3D7C *)D_800E3D7C)->unk_00.at00_pv.v))->unk_9A != 0x23)) {
                                                            var_a0_3 = 0;
                                                            loop_hi = 4;
                                                            loop_lo = 1;
                                                            var_v1_3 = (u8 *)0x80010000;
loop_116:
                                                            if ((var_v1_3[0x249] != loop_hi) || (temp_s0_2 = var_v1_3[0x248], (temp_s0_2 != loop_lo))) {
                                                                var_a0_3 += 1;
                                                                var_v1_3 += 4;
                                                                if (var_a0_3 >= 0x14) {
                                                                    goto block_119;
                                                                }
                                                                goto loop_116;
                                                            }
                                                            goto action_100;
                                                        }
block_119:
                                                        if (((S_812A524C_3 *)arg0)->unk_B8 == 0) {
                                                            if (!(((S_812A524C_3 *)arg0)->unk_B0 & 0x40) && (ev7 = (u8 *)&D_80082E80, ((u32) (((S_812A524C_23 *)ev7)->unk_24.at00.v - 0x161C) < 7U)) && (pos7 = (u8 *)&D_80083780, event_x7 = ((S_812A524C_23 *)ev7)->unk_24.at00u.v, (((event_x7 << 6) + 0x20) == ((S_812A524C_24 *)pos7)->unk_02)) && (((((S_812A524C_23 *)ev7)->unk_24.at01.v << 6) + 0x20) == ((S_812A524C_24 *)pos7)->unk_06)) {
                                                                func_800353F4(&D_8006FD01);
                                                                ((S_812A524C_4 *)arg3)->unk_6D = 0U;
                                                                ((S_812A524C_3 *)arg0)->unk_9B = 0;
                                                                ((S_812A524C_3 *)arg0)->unk_B8 = 1U;
                                                                ((S_812A524C_3 *)arg0)->unk_B0 = (s32) (((S_812A524C_3 *)arg0)->unk_B0 | 0x40);
                                                            }
                                                            if (((S_812A524C_3 *)arg0)->unk_B8 == 0) {
                                                                if (!(((S_812A524C_3 *)arg0)->unk_B0 & 0x400) && (ev8 = (u8 *)&D_80082E80, ((u32) (((S_812A524C_25 *)ev8)->unk_24.at00.v - 0x2036) < 2U)) && (pos8 = (u8 *)&D_80083780, event_x8 = ((S_812A524C_25 *)ev8)->unk_24.at00u.v, (((event_x8 << 6) + 0x20) == ((S_812A524C_26 *)pos8)->unk_02)) && (((((S_812A524C_25 *)ev8)->unk_24.at01.v << 6) + 0x20) == ((S_812A524C_26 *)pos8)->unk_06)) {
                                                                    func_800353F4(&D_80070AF8);
                                                                    ((S_812A524C_4 *)arg3)->unk_6D = 0U;
                                                                    ((S_812A524C_3 *)arg0)->unk_9B = 0;
                                                                    ((S_812A524C_3 *)arg0)->unk_B8 = 1U;
                                                                    ((S_812A524C_3 *)arg0)->unk_B0 = (s32) (((S_812A524C_3 *)arg0)->unk_B0 | 0x400);
                                                                }
                                                                if (((S_812A524C_3 *)arg0)->unk_B8 == 0) {
                                                                    if (!(((S_812A524C_3 *)arg0)->unk_B0 & 0x800) && ((D_80082EA4[0] == 0x31E) || (D_80082EA4[0] == 0x41E) || (D_80082EA4[0] == 0x51E) || (D_80082EA4[0] == 0x61E) || (D_80082EA4[0] == 0x71E) || (D_80082EA4[0] == 0x81E)) && (ev9 = (u8 *)&D_80082E80, pos9 = (u8 *)&D_80083780, (((((S_812A524C_27 *)ev9)->unk_24 << 6) + 0x20) == ((S_812A524C_28 *)pos9)->unk_02)) && (((((S_812A524C_27 *)ev9)->unk_25 << 6) + 0x20) == ((S_812A524C_28 *)pos9)->unk_06)) {
                                                                        func_800353F4(&D_80070C11);
                                                                        ((S_812A524C_4 *)arg3)->unk_6D = 0U;
                                                                        ((S_812A524C_3 *)arg0)->unk_9B = 0;
                                                                        ((S_812A524C_3 *)arg0)->unk_B8 = 1U;
                                                                        ((S_812A524C_3 *)arg0)->unk_B0 = (s32) (((S_812A524C_3 *)arg0)->unk_B0 | 0x800);
                                                                    }
                                                                    if (((S_812A524C_3 *)arg0)->unk_B8 == 0) {
                                                                        if (!(((S_812A524C_3 *)arg0)->unk_B0 & 0x1000)) {
                                                                            if (((u32) (D_80082EA4[0] - 0x2C1E) < 3U) || (D_80082EA4[0] == 0x2D1E) || (D_80082EA4[0] == 0x2D1F) || (D_80082EA4[0] == 0x2D20)) {
                                                                                ev10 = (u8 *)&D_80082E80;
                                                                                pos10 = (u8 *)&D_80083780;
                                                                                if ((((((S_812A524C_29 *)ev10)->unk_24 << 6) + 0x20) == ((S_812A524C_30 *)pos10)->unk_02) && (((((S_812A524C_29 *)ev10)->unk_25 << 6) + 0x20) == ((S_812A524C_30 *)pos10)->unk_06)) {
                                                                                    func_800353F4(&D_80070E63);
                                                                                    ((S_812A524C_4 *)arg3)->unk_6D = 0U;
                                                                                    ((S_812A524C_3 *)arg0)->unk_9B = 0;
                                                                                    ((S_812A524C_3 *)arg0)->unk_B8 = 1U;
                                                                                    ((S_812A524C_3 *)arg0)->unk_B0 = (s32) (((S_812A524C_3 *)arg0)->unk_B0 | 0x1000);
                                                                                }
                                                                            }
                                                                        }
                                                                        if (((S_812A524C_3 *)arg0)->unk_B8 == 0) {
                                                                            if (!(((S_812A524C_3 *)arg0)->unk_B0 & 0x2000) && (ev11 = (u8 *)&D_80082E80, ((u32) (((S_812A524C_31 *)ev11)->unk_24.at00.v - 0x121C) < 7U)) && (pos11 = (u8 *)&D_80083780, event_x11 = ((S_812A524C_31 *)ev11)->unk_24.at00u.v, (((event_x11 << 6) + 0x20) == ((S_812A524C_32 *)pos11)->unk_02)) && (((((S_812A524C_31 *)ev11)->unk_24.at01.v << 6) + 0x20) == ((S_812A524C_32 *)pos11)->unk_06)) {
                                                                                func_800353F4(&D_800FB3C8);
                                                                                ((S_812A524C_4 *)arg3)->unk_6D = 0U;
                                                                                ((S_812A524C_3 *)arg0)->unk_9B = 0;
                                                                                ((S_812A524C_3 *)arg0)->unk_B8 = 1U;
                                                                                ((S_812A524C_3 *)arg0)->unk_B0 = (s32) (((S_812A524C_3 *)arg0)->unk_B0 | 0x2000);
                                                                            }
                                                                            if (((S_812A524C_3 *)arg0)->unk_B8 == 0) {
                                                                                if (!(((S_812A524C_3 *)arg0)->unk_B0 & 0x10000)) {
                                                                                    if (((S_812A524C_5 *)(&D_800FBE54))->unk_00 == NULL) {
                                                                                        temp_v0_3 = func_800F6DFC(arg3);
                                                                                        ((S_812A524C_5 *)(&D_800FBE54))->unk_00 = temp_v0_3;
                                                                                        if (temp_v0_3 != NULL) {
                                                                                            goto block_163;
                                                                                        }
                                                                                    } else {
block_163:
                                                                                        temp_v1_3 = ((S_812A524C_40 *)(((S_812A524C_5 *)(&D_800FBE54))->unk_00))->unk_0C;
                                                                                        var_v0_7 = &D_80082E80;
                                                                                        temp_a0 = ((S_812A524C_33 *)var_v0_7)->unk_24;
                                                                                        var_v0_8 = temp_a0 - temp_v1_3->unk_24;
                                                                                        if (var_v0_8 < 0) {
                                                                                            var_v0_8 = 0 - var_v0_8;
                                                                                        }
                                                                                        if (var_v0_8 < 4) {
                                                                                            temp_a1_2 = ((S_812A524C_33 *)var_v0_7)->unk_25;
                                                                                            var_v0_9 = temp_a1_2 - temp_v1_3->unk_25;
                                                                                            if (var_v0_9 < 0) {
                                                                                                var_v0_9 = 0 - var_v0_9;
                                                                                            }
                                                                                            if (var_v0_9 < 4) {
                                                                                                scaled_x = temp_a0 << 6;
                                                                                                pos12 = (u8 *)&D_80083780;
                                                                                                if (((scaled_x + 0x20) == ((S_812A524C_35 *)pos12)->unk_02) && (((temp_a1_2 << 6) + 0x20) == ((S_812A524C_35 *)pos12)->unk_06)) {
                                                                                                    func_800353F4(&D_800FBD96);
                                                                                                    ((S_812A524C_4 *)arg3)->unk_6D = 0U;
                                                                                                    ((S_812A524C_3 *)arg0)->unk_9B = 0;
                                                                                                    ((S_812A524C_3 *)arg0)->unk_B8 = 1U;
                                                                                                    ((S_812A524C_3 *)arg0)->unk_B0 |= 0x10000;
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                goto block_172;
                                                                            }
                                                                            goto active_return;
                                                                        }
                                                                        goto active_return;
                                                                    }
                                                                    goto active_return;
                                                                }
                                                                goto active_return;
                                                            }
                                                            goto active_return;
                                                        }
                                                        goto active_return;
                                                    }
                                                    goto active_return;
                                                }
                                                goto active_return;
                                            }
                                            goto active_return;
                                        }
                                        goto active_return;
                                    }
                                    goto active_return;
                                }
                                goto active_return;
                            }
                            goto active_return;
                        }
                        goto active_return;
                    }
                    goto active_return;
                }
            }
            goto block_172;
        }
        goto active_return;
    }
block_172:
    if (((S_812A524C_3 *)arg0)->unk_B8 == 0) {
        goto inactive;
    }
active_return:
    ((S_812A524C_36 *)(&D_800E296C))->unk_00.n |= 0x200000;
    func_80171968();
inactive:
    clear_flags = ((S_812A524C_36 *)(&D_800E296C))->unk_00.v;
    clear_flags &= 0xFFDFFFFF;
    ((S_812A524C_36 *)(&D_800E296C))->unk_00.v = clear_flags;
    ASM_KEEP(clear_flags);   /* MATCH pin: keeps a constant in a register as retail does */
    if (D_80083462[0] & 0x2000) {
        temp_v1_4 = ((S_812A524C_3 *)arg0)->unk_8C;
        if (temp_v1_4 == &D_80171FA4) {
            temp_v1_4(arg0, arg1, arg2, arg3);
            func_80171F74();
            return;
        }
        ((S_812A524C_4 *)arg3)->unk_71 &= 0x7F;
        func_80171F74(arg0);
        return;
    }
    temp_s0_3 = (s8) ((S_812A524C_4 *)arg3)->unk_6D;
    if (func_800A9E70(arg0, arg1, arg2, arg3) == 0) {
        temp_v0_4 = ((S_812A524C_3 *)arg0)->unk_8C;
        if (temp_v0_4 != NULL) {
            temp_v0_4(arg0, arg1, arg2, arg3);
        }
        D_80175CC8[((S_812A524C_3 *)arg0)->unk_9A](arg0, arg1, arg2, arg3);
        if ((s16) temp_s0_3 != (s8) ((S_812A524C_4 *)arg3)->unk_6D) {
            func_800AA36C(arg0, arg1, arg2, arg3);
        }
        motion_x = ((S_812A524C_37 *)arg1)->unk_00.at00.v;
        temp_a0_3 = ((S_812A524C_37 *)arg1)->unk_0C;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        motion_y = ((S_812A524C_37 *)arg1)->unk_04.at00.v;
        temp_a1_2 = ((S_812A524C_37 *)arg1)->unk_10;
        ((S_812A524C_37 *)arg1)->unk_00.at00.v = motion_x + temp_a0_3;
        ((S_812A524C_37 *)arg1)->unk_04.at00.v = motion_y + temp_a1_2;
        if (!(((S_812A524C_4 *)arg3)->unk_1C & 0x40000) && !(((S_812A524C_3 *)arg0)->unk_98 & 8)) {
            ((S_812A524C_37 *)arg1)->unk_14 = (s32) (((S_812A524C_37 *)arg1)->unk_14 + (((S_812A524C_3 *)arg0)->unk_9D.s * 0x14000));
            ((S_812A524C_3 *)arg0)->unk_9D.u += 1;
            func_80171AD8(temp_a0_3, temp_a1_2);
            return;
        }
        ((S_812A524C_3 *)arg0)->unk_9D.s = 0;
        ASM_MEM_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        ((S_812A524C_3 *)arg0)->unk_90.at00.v = (s32) (((S_812A524C_3 *)arg0)->unk_90.at00.v + ((S_812A524C_37 *)arg1)->unk_14);
        temp_s2 = ((s32) (D_80083228[0] + ((S_812A524C_4 *)arg3)->unk_2A + 0x100) >> 9) & 7;
        temp_s0_4 = temp_s2;
        if (((S_812A524C_3 *)arg0)->unk_94 != temp_s0_4) {
            func_80047738(arg2, ((S_812A524C_38 *)arg2)->unk_2C.p[temp_s0_4], ((S_812A524C_38 *)arg2)->unk_04.s8);
            ((S_812A524C_3 *)arg0)->unk_94 = temp_s2;
        }
        if (D_8006CCF8[temp_s0_4] != 0) {
            tail_value = ((S_812A524C_38 *)arg2)->unk_14.n;
            tail_value |= 1;
            ASM_TAILSLOT_PIN_TIED(tail_value);   /* MATCH pin: retail delay-slot fill depends on it */
            func_80171B6C();
            return;
        }
        first_flags = ((S_812A524C_38 *)arg2)->unk_14.v;
        ((S_812A524C_38 *)arg2)->unk_14.v = first_flags & 0xFFFE;
        temp_v1_5 = ((S_812A524C_38 *)arg2)->unk_14.v;
        fixed_flags = temp_v1_5 & 0x8000;
        if (fixed_flags == 0) {
            func_800A020C(((S_812A524C_4 *)arg3)->unk_1C, arg2 + 0xC);
            if (!(((S_812A524C_4 *)arg3)->unk_1C & 0x20)) {
                if (!(((S_812A524C_38 *)arg2)->unk_14.n & 0x40)) {
                    func_800478B8(arg2);
                    tail_value = 0xF7FF0000;
                    ASM_TAILSLOT_PIN(tail_value);   /* MATCH pin: retail delay-slot contents depend on it */
                    func_80171BEC();
                    return;
                }
                goto block_201;
            }
            ((S_812A524C_38 *)arg2)->unk_14.n = (u16) (((S_812A524C_38 *)arg2)->unk_14.n | 0x7000);
            ((S_812A524C_4 *)arg3)->unk_1C = (s32) (((S_812A524C_4 *)arg3)->unk_1C & 0xFFFBFFFF);
block_201:
            temp_v1_6 = ((S_812A524C_4 *)arg3)->unk_1C & 0xF7FFFFFF;
            ((S_812A524C_4 *)arg3)->unk_1C = temp_v1_6;
            if (temp_v1_6 & 0x40000) {
                if (!(((S_812A524C_38 *)arg2)->unk_14.n & 0x40) && (((S_812A524C_38 *)arg2)->unk_2C.i == &D_80175C30)) {
                    if (((S_812A524C_38 *)arg2)->unk_04.u16 == 0x100) {
                        ((S_812A524C_3 *)arg0)->unk_9E = 0U;
                        ((S_812A524C_3 *)arg0)->unk_A0.at00.v = 0;
                    }
                    if ((u32) ((u8) ((S_812A524C_38 *)arg2)->unk_04.s8 - 1) < 4U) {
                        temp_v1_7 = ((S_812A524C_3 *)arg0)->unk_9E;
                        ((S_812A524C_3 *)arg0)->unk_9E = (u16) (temp_v1_7 + 1);
                        tail_value = func_800644B8((s16) temp_v1_7 * 0xAA);
                        tail_acc = ((S_812A524C_3 *)arg0)->unk_A0.at00.v;
                        tail_value <<= 5;
                        ASM_KEEP(tail_acc);   /* MATCH pin: retail basic-block layout depends on it */
                        ASM_TAILSLOT_PIN_TIED(tail_value);   /* MATCH pin: retail delay-slot fill depends on it */
                        func_80171CD4();
                        return;
                    }
                    temp_v1_8 = ((S_812A524C_3 *)arg0)->unk_9E;
                    ((S_812A524C_3 *)arg0)->unk_9E = (u16) (temp_v1_8 + 1);
                    ((S_812A524C_3 *)arg0)->unk_A0.at00.v = (s32) (((S_812A524C_3 *)arg0)->unk_A0.at00.v + (func_800644B8((s16) temp_v1_8 * 0xAA) << 6));
                    goto block_210;
                }
block_210:
                if (!(((S_812A524C_3 *)arg0)->unk_98 & 8)) {
                    temp_a0_4 = ((S_812A524C_3 *)arg0)->unk_90.at02.v;
                    tail_acc = ((S_812A524C_3 *)arg0)->unk_90.at02u.v;
                    if (temp_a0_4 >= -0x1F) {
                        tail_value = temp_a0_4 < -0x28;
                        ASM_KEEP(tail_value);   /* MATCH pin: retail delay-slot fill depends on it */
                        tail_value = tail_acc - 8;
                        ASM_TAILSLOT_PIN_TIED(tail_value);   /* MATCH pin: retail delay-slot fill depends on it */
                        func_80171ECC(temp_a0_4);
                        return;
                    }
                    goto block_233;
                }
                goto block_235;
            }
            goto block_217;
        }
        fixed_flags = temp_v1_5 & 0x800;
        if (fixed_flags != 0) {
            fixed_flags = temp_v1_5 & 0x8FFF;
            goto flags_ready;
        }
        fixed_flags = temp_v1_5 | 0x7000;
flags_ready:
        ((S_812A524C_38 *)arg2)->unk_14.n = (u16) fixed_flags;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_v1_9 = ((S_812A524C_4 *)arg3)->unk_1C & 0xF7FFFFFF;
        ((S_812A524C_4 *)arg3)->unk_1C = temp_v1_9;
        if (!(temp_v1_9 & 0x40000)) {
block_217:
            temp_v0_5 = ((S_812A524C_3 *)arg0)->unk_A0.at00.v;
            ((S_812A524C_3 *)arg0)->unk_9E = 0U;
            ((S_812A524C_3 *)arg0)->unk_A0.at00.v = 0;
            ((S_812A524C_3 *)arg0)->unk_90.at00.v = (s32) (((S_812A524C_3 *)arg0)->unk_90.at00.v - temp_v0_5);
            if (!(((S_812A524C_3 *)arg0)->unk_98 & 8)) {
                temp_a0_5 = func_800BCB04(((S_812A524C_37 *)arg1)->unk_00.at02.v, ((S_812A524C_37 *)arg1)->unk_04.at02.v, (s16) (((S_812A524C_4 *)arg3)->unk_88 - 0x20)) - ((S_812A524C_4 *)arg3)->unk_88;
                if ((s16) temp_a0_5 < ((S_812A524C_3 *)arg0)->unk_90.at02.v) {
                    ((S_812A524C_3 *)arg0)->unk_90.at02.v = (s16) temp_a0_5;
                    ((S_812A524C_3 *)arg0)->unk_9D.s = 0;
                    ((S_812A524C_37 *)arg1)->unk_14 = 0;
                    ((S_812A524C_4 *)arg3)->unk_1C |= 0x08000000;
                    func_80171ED0(temp_a0_5);
                    return;
                }
            }
            goto block_235;
        }
        if (!(((S_812A524C_38 *)arg2)->unk_14.n & 0x40) && (((S_812A524C_38 *)arg2)->unk_2C.i == &D_80175C30)) {
            if (((S_812A524C_38 *)arg2)->unk_04.u16 == 0x100) {
                ((S_812A524C_3 *)arg0)->unk_9E = 0U;
                ((S_812A524C_3 *)arg0)->unk_A0.at00.v = 0;
            }
            if ((u32) ((u8) ((S_812A524C_38 *)arg2)->unk_04.s8 - 1) < 4U) {
                temp_v1_10 = ((S_812A524C_3 *)arg0)->unk_9E;
                ((S_812A524C_3 *)arg0)->unk_9E = (u16) (temp_v1_10 + 1);
                tail_value = func_800644B8((s16) temp_v1_10 * 0xAA);
                tail_acc = ((S_812A524C_3 *)arg0)->unk_A0.at00.v;
                tail_value <<= 5;
                ASM_KEEP(tail_acc);   /* MATCH pin: retail basic-block layout depends on it */
                ASM_TAILSLOT_PIN_TIED(tail_value);   /* MATCH pin: retail delay-slot fill depends on it */
                func_80171E8C();
                return;
            }
            temp_v1_11 = ((S_812A524C_3 *)arg0)->unk_9E;
            ((S_812A524C_3 *)arg0)->unk_9E = (u16) (temp_v1_11 + 1);
            ((S_812A524C_3 *)arg0)->unk_A0.at00.v = (s32) (((S_812A524C_3 *)arg0)->unk_A0.at00.v + (func_800644B8((s16) temp_v1_11 * 0xAA) << 6));
            goto block_229;
        }
block_229:
        if (!(((S_812A524C_3 *)arg0)->unk_98 & 8)) {
            temp_a0_4 = ((S_812A524C_3 *)arg0)->unk_90.at02.v;
            tail_acc = ((S_812A524C_3 *)arg0)->unk_90.at02u.v;
            if (temp_a0_4 >= -0x1F) {
                tail_value = tail_acc - 8;
                ASM_TAILSLOT_PIN_TIED(tail_value);   /* MATCH pin: retail delay-slot fill depends on it */
                func_80171ECC(temp_a0_4);
                return;
            }
block_233:
            if (temp_a0_4 < -0x28) {
                final_tail_value = tail_acc + 8;
                ((S_812A524C_3 *)arg0)->unk_90.at02.v = (s16) final_tail_value;
            }
            goto block_235;
        }
block_235:
        temp_v1_12 = ((S_812A524C_4 *)arg3)->unk_1C;
        if (temp_v1_12 & 0x40000000) {
            ((S_812A524C_4 *)arg3)->unk_1C = (s32) (temp_v1_12 & 0xBFFFFFFF);
            temp_v0_6 = func_800BCB04((((S_812A524C_38 *)arg2)->unk_24 << 6) | 0x20, (((S_812A524C_38 *)arg2)->unk_25 << 6) | 0x20, (s16) (((S_812A524C_4 *)arg3)->unk_88 - 0x20));
            if (temp_v0_6 < 0x200) {
                ((S_812A524C_3 *)arg0)->unk_90.at02.v = (s16) ((u16) ((S_812A524C_3 *)arg0)->unk_90.at02.v + (((S_812A524C_4 *)arg3)->unk_88 - temp_v0_6));
                ((S_812A524C_4 *)arg3)->unk_88 = (u16) temp_v0_6;
            }
        }
        ((S_812A524C_37 *)arg1)->unk_0A = (s16) ((((S_812A524C_4 *)arg3)->unk_88 + (u16) ((S_812A524C_3 *)arg0)->unk_90.at02.v) - ((S_812A524C_3 *)arg0)->unk_A0.at02.v);
        ((S_812A524C_38 *)arg2)->unk_14.n = (u16) (((S_812A524C_38 *)arg2)->unk_14.n | 0x40);
    }
    return;
}
