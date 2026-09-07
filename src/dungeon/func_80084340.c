#include "common.h"
#include "m2c_compat.h"

typedef M2C_UNK (*Callback4)(void *, void *, void *, void *);
extern u8 D_80096384[];
extern u8 D_80080001[];
M2C_UNK func_8003DB6C();   /* extern */
M2C_UNK func_8003DB94();             /* extern */
M2C_UNK func_80040AA0();                     /* extern */
s16 func_80042900();                 /* extern */
M2C_UNK func_800478B8();                      /* extern */
M2C_UNK func_800489F4();     /* extern */
M2C_UNK func_80048AC8();             /* extern */
M2C_UNK func_8004D294(); /* extern */
M2C_UNK func_8004D7A8();                     /* extern */
M2C_UNK func_80053DA8();                     /* extern */
s32 func_80053EF0();                         /* extern */
s32 func_800644B8();                             /* extern */
M2C_UNK func_80096100(); /* extern */
M2C_UNK func_8009A180();                 /* extern */
void *func_8009B25C();           /* extern */
M2C_UNK func_8009D3B0();                            /* extern */
s32 func_8009F5CC();                             /* extern */
s32 func_8009FB34();                           /* extern */
M2C_UNK func_800A020C();                 /* extern */
M2C_UNK func_800A0DD8();                            /* extern */
s32 func_800A1C58();                      /* extern */
s32 func_800A2B28();                                /* extern */
s16 func_800A2C34();                         /* extern */
s32 func_800A4474();                          /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800A56E0();                     /* extern */
s32 func_800A5C70();                                /* extern */
s32 func_800A6D30();                                /* extern */
M2C_UNK func_800A9AFC();                 /* extern */
M2C_UNK func_800B66C8();                      /* extern */
s32 func_800BCB04();                   /* extern */
M2C_UNK func_800C6AB0();                            /* extern */
s32 func_800C77D0();    /* extern */
extern u16 D_80013714;
extern u8 D_8006CCF8[];
extern s8 D_80080A88;
extern M2C_UNK D_80080AA0;
extern s16 D_80081468[3];
extern void *D_800814A8;
extern s8 D_80083160[];
extern s16 D_80083228;
extern s32 D_800832B4[3];
extern M2C_UNK D_80083460;
extern u16 D_80083462;
extern u8 D_80083468[];
extern M2C_UNK D_8008ACDC;
extern s16 D_800DCE60[];
extern s8 D_800DCF4F;
extern u32 D_800DD160;
extern Callback4 D_800DD168[];
extern u16 D_800DD258;
extern u16 D_800DD25A;
extern M2C_UNK D_800E296C;
extern s8 D_800E2970[];
extern u8 D_800E3CD0;
extern s8 D_800E3D20;
extern s32 D_800E3D70;
extern s32 D_800E3D74;
extern void *D_800E3D7C;
extern void *D_800E3DE8;
extern s32 D_800E4948;


typedef struct S_80089AA0_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80089AA0_0;   /* base_83160 in func_80089AA0 */

typedef struct S_80089AA0_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
    u8 pad_20[0x98];
    s32 unk_B8;
    u8 pad_BC[0x9E4];
    union { u8 u; s8 s; } unk_AA0;   /* accessed as both */
} S_80089AA0_1;   /* var_s0 in func_80089AA0 */

typedef struct S_80089AA0_2 {
    u8 pad_00[0xB0];
    u16 unk_B0;
} S_80089AA0_2;   /* held_83178 in func_80089AA0 */

typedef struct S_80089AA0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s16 unk_14;
} S_80089AA0_3;   /* status_base in func_80089AA0 */

typedef struct S_80089AA0_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s16 unk_0C;
} S_80089AA0_4;   /* temp_a1 in func_80089AA0 */

typedef struct S_80089AA0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s16 unk_14;
} S_80089AA0_5;   /* var_v1_2 in func_80089AA0 */

typedef struct S_80089AA0_6 {
    s32 unk_00;
} S_80089AA0_6;   /* &D_800E296C in func_80089AA0 */

typedef struct S_80089AA0_7_pre {
    s16 unk_00;
    u8 pad_02[0x6];
} S_80089AA0_7_pre;   /* the 0x8 bytes before copy_dst in func_80089AA0, addressed as copy_dst[-1] */

typedef struct S_80089AA0_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x1A];
    u16 unk_1E;
} S_80089AA0_8;   /* status_or_base in func_80089AA0 */

typedef struct S_80089AA0_9 {
    s32 unk_00;
} S_80089AA0_9;   /* &D_800E3D70 in func_80089AA0 */

typedef struct S_80089AA0_10 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80089AA0_10;   /* var_a3 in func_80089AA0 */

typedef struct S_80089AA0_11 {
    u8 pad_00[0x25];
    u8 unk_25;
    u8 pad_26[0x2];
    u8 unk_28;
    u8 unk_29;
} S_80089AA0_11;   /* temp_a1_2 in func_80089AA0 */

typedef struct S_80089AA0_12 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80089AA0_12;   /* callback_status in func_80089AA0 */

typedef struct S_80089AA0_13 {
    u32 unk_00;
} S_80089AA0_13;   /* &D_800DD160 in func_80089AA0 */

typedef struct S_80089AA0_14 {
    u8 pad_00[0x5C];
    s32 unk_5C;
    u8 pad_60[0xC];
    s16 unk_6C;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_80089AA0_14;   /* var_a0 in func_80089AA0 */

typedef struct S_80089AA0_15 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s16 unk_14;
} S_80089AA0_15;   /* reset_base in func_80089AA0 */

typedef struct S_80089AA0_16 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
    u8 pad_30[0x2C];
    void * unk_5C;
} S_80089AA0_16;   /* arg2 in func_80089AA0 */

typedef struct S_80089AA0_17 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_80089AA0_17;   /* table_entry in func_80089AA0 */

typedef struct S_80089AA0_18 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80089AA0_18;   /* arg1 in func_80089AA0 */

typedef struct S_80089AA0_19_pre {
    union { void * p; s32 i; } unk_00;   /* accessed as both */
    u8 pad_04[0x10];
} S_80089AA0_19_pre;   /* the 0x14 bytes before var_s1 in func_80089AA0, addressed as var_s1[-1] */

typedef struct S_80089AA0_19 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x30];
    union { s32 i; void * p; } unk_5C;   /* accessed as both */
    u8 pad_60[0xA];
    u16 unk_6A;
    u8 pad_6C[0x1];
    s8 unk_6D;
    u8 pad_6E[0x3];
    s8 unk_71;
    u8 pad_72[0x16];
    u16 unk_88;
    u16 unk_8A;
} S_80089AA0_19;   /* var_s1 in func_80089AA0 */

typedef struct S_80089AA0_20 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80089AA0_20;   /* temp_v0_13 in func_80089AA0 */

typedef struct S_80089AA0_21 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
} S_80089AA0_21;   /* early_status in func_80089AA0 */

typedef struct S_80089AA0_22 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80089AA0_22;   /* var_v0_3 in func_80089AA0 */

typedef struct S_80089AA0_23 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0xC];
    s32 unk_10;
} S_80089AA0_23;   /* tail_status in func_80089AA0 */

typedef struct S_80089AA0_24 {
    u8 pad_00[0x2];
    u16 unk_02;
    s16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    s16 unk_0A;
    void * unk_0C;
    s32 unk_10;
    s16 unk_14;
} S_80089AA0_24;   /* var_v0_4 in func_80089AA0 */

typedef struct S_80089AA0_25 {
    u8 pad_00[0x296C];
    s32 unk_296C;
} S_80089AA0_25;   /* (void *)stack_flag in func_80089AA0 */

typedef struct S_80089AA0_26 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_80089AA0_26;   /* next_page in func_80089AA0 */

typedef struct S_80089AA0_27 {
    u8 pad_00[0x3DE8];
    void * unk_3DE8;
} S_80089AA0_27;   /* root_page in func_80089AA0 */

void func_80089AA0(void *in_arg0, void *in_arg1, void *in_arg2) {
    register void *arg0 ASM_REG("$17");   /* MATCH pin: keeps a constant in a register as retail does */
    register void *arg2 ASM_REG("$18");   /* MATCH pin: load-bearing for the whole function shape */
    void *arg1;
    void *base_83160;
    volatile s32 sp10;
    M2C_UNK (*temp_v0_8)(void *, void *, void *, void *);
    M2C_UNK (*temp_v1_3)(void *, void *, void *, void *);
    M2C_UNK *var_s0;
    M2C_UNK *early_status;
    M2C_UNK *var_v0_3;
    M2C_UNK *var_v0_4;
    M2C_UNK *var_v1_2;
    M2C_UNK *var_v1_5;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_v0;
    s16 temp_v0_10;
    s32 *temp_a1;
    s32 temp_a0_4;
    register s32 temp_a2_role ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
    s32 temp_v1_10;
    register s32 temp_v1_sign ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 temp_v1_9;
    s32 var_s5;
    register s32 var_s6 ASM_REG("$22");   /* MATCH pin: retail register colouring depends on it */
    register s32 var_s6_2 ASM_REG("$22");   /* MATCH pin: retail register colouring depends on it */
    s32 temp_v0_9;
    u16 temp_a0;
    u16 temp_v0_14;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v1_12;
    u16 temp_v1_13;
    u16 temp_v1_14;
    u16 temp_v1_2;
    u16 temp_v1_5;
    u16 temp_v1_6;
    u16 temp_v1_7;
    u16 temp_v1_8;
    u16 var_v0_5;
    u16 shared_a2_flags;
    u32 *var_a2;
    u32 temp_v0_2;
    u32 temp_v0_3;
    u32 temp_v0_4;
    u32 temp_v0_5;
    u8 temp_a0_2;
    u8 temp_a0_3;
    s32 temp_a1_3;
    u8 temp_v1;
    u8 temp_v1_11;
    s32 var_v1_3;
    s32 var_v1_4;
    S_80089AA0_11 *temp_a1_2;
    void *temp_s2;
    register void *temp_v0_12 ASM_REG("$2");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    S_80089AA0_20 *temp_v0_13;
    void *temp_v1_4;
    S_80089AA0_14 *var_a0;
    void *var_a3;
    void *var_s0_2;
    void *var_s0_3;
    void *var_s0_4;
    void *var_s1;
    register s32 stack_flag ASM_REG("$9");   /* MATCH pin: retail register colouring depends on it */
    void *var_s1_3;
    void *var_s1_4;
    void *var_s1_5;
    void *var_s4;
    void *var_s4_2;
    register void *arg0_copy ASM_REG("$20");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    S_80089AA0_2 *held_83178;
    void *page_8008;
    S_80089AA0_3 *status_base;
    register void *status_or_base ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    register void *callback_status ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    S_80089AA0_23 *tail_status;
    void *copy_dst;
    void *next_record;
    register u8 *root_page ASM_REG("$23");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u8 *next_page;
    u16 initial_flags;

    arg0 = in_arg0;
    base_83160 = D_80083160;
    initial_flags = D_80013714;
    arg1 = in_arg1;
    arg2 = in_arg2;
    arg0_copy = arg0;
    held_83178 = (u8 *)base_83160 + 0x18;
    if (initial_flags & 4) {
        var_s0 = (M2C_UNK *)0x80080000;
        if ((D_800E3CD0 == 0) && (((S_80089AA0_0 *)base_83160)->unk_10 != 0)) {
            D_800E3CD0 = 1;
            func_80040AA0(3);
            goto function_end;
        }
        goto block_6;
    }
    var_s0 = (M2C_UNK *)0x80080000;
block_6:
    if ((((S_80089AA0_1 *)var_s0)->unk_AA0.u != 0) && (D_800E3CD0 == 0) && (func_80053EF0(1) == 0)) {
        func_80053DA8(0x200);
        ((S_80089AA0_1 *)var_s0)->unk_AA0.s = 0;
        D_80080A88 = 1;
    }
    ASM_CLOBBER("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    if (D_80013714 & 4) {
        register s16 *dce_base ASM_REG("$2");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        s32 *dce_step_page;
        s32 dce_value;
        s32 reverse_step;
        dce_base = (s16 *)0x800E0000;
        ASM_KEEP_NV(dce_base);   /* MATCH pin: retail branch polarity depends on it */
        dce_step_page = (s32 *)0x80080000;
        ASM_KEEP_NV(dce_step_page);   /* MATCH pin: retail schedule: same instructions, different order without it */
        dce_base = (s16 *)((u8 *)dce_base - 0x31A0);
        reverse_step = *(s32 *)((u8 *)dce_step_page + 0x1468);
        dce_value = dce_base[2];
        if (reverse_step & 1) {
            reverse_step = dce_value + 8;
        } else {
            reverse_step = dce_value - 8;
        }
        dce_base[2] = (s16) reverse_step;
        D_800832B4[0] = 0;
        func_8004D7A8(1);
        func_8004D294(0, (s16 *)((u8 *)&D_800DCF4F - 0xEF), 2);
    }
    (*(s16 *)((u8 *)arg0 + 0x9E)) = (s16) (((u16) held_83178->unk_B0 >> 9) & 7);
    status_base = &D_80083460;
    status_base->unk_02 = (u16) (status_base->unk_02 & 0xFFCF);
    temp_a1 = &D_800E4948;
    if (status_base->unk_08 == D_800E4948) {
        if (status_base->unk_0C == ((S_80089AA0_4 *)temp_a1)->unk_04) {
            if (status_base->unk_10 == ((S_80089AA0_4 *)temp_a1)->unk_08) {
                if (status_base->unk_14 == ((S_80089AA0_4 *)temp_a1)->unk_0C) {
                    if (!(D_80013714 & 8)) {
                        temp_v1 = (*(u8 *)((u8 *)arg0 + 0x9A));
                        if ((temp_v1 != 0x17) && (temp_v1 != 0x27) && (temp_v1 != 0x29) && (D_800DCF4F == 0)) {
                            if (status_base->unk_0C == 0) {
                                if ((status_base->unk_10 == 0) && (status_base->unk_14 == 0)) {
                                    if (status_base->unk_08 != 0) {
                                        goto block_27;
                                    }
                                    goto block_31;
                                }
                                D_800DD160 += 1;
                                goto local_89ce0;
                            }
block_27:
                            D_800DD160 += 1;
                            goto local_89ce0;
                        }
                        goto block_30;
                    }
                }
            }
        }
        goto block_31;
    }
block_30:
block_31:
    D_800DD160 = 0;
local_89ce0:
    copy_dst = D_80083468;
    func_8003DB6C(&D_800E4948, copy_dst, 4);
    var_v1_2 = (u8 *)copy_dst - 8;
    if (((S_80089AA0_5 *)var_v1_2)->unk_0C == 0) {
        if (((S_80089AA0_5 *)var_v1_2)->unk_10 == 0) {
            temp_a0 = ((S_80089AA0_5 *)var_v1_2)->unk_02;
            if (!(temp_a0 & 8) && (((S_80089AA0_5 *)var_v1_2)->unk_08 == 0)) {
                if (((S_80089AA0_5 *)var_v1_2)->unk_14 == 0) {
                    if (!(((S_80089AA0_6 *)(&D_800E296C))->unk_00 & 0x100000) && (((S_80089AA0_5 *)var_v1_2)->unk_0A == 0)) {
                        if (!(temp_a0 & 0x2E01)) {
                            if ((func_8009F5CC(temp_a0) << 0x10) != 0) {
                                func_800C6AB0();
                            }
                            temp_v1_2 = ((S_80089AA0_5 *)var_v1_2)->unk_02;
                            if (temp_v1_2 & 2) {
                                ((S_80089AA0_5 *)var_v1_2)->unk_02 = (u16) ((temp_v1_2 & 0xFFFD) | 0x20);
                                func_800A0DD8();
                                temp_v0 = func_80042900(arg0_copy, 7);
                                temp_v1_sign = temp_v0;
                                temp_v0 = 0x80;
                                if (temp_v1_sign <= 0) {
                                    temp_v0 = 0x100;
                                    if (temp_v1_sign < 0) {
                                        temp_v0 = 0x200;
                                    }
                                }
                                ((S_80089AA0_7_pre *)copy_dst)[-1].unk_00 = (s16) temp_v0;
                                ASM_CLOBBER("$2");   /* MATCH pin: keeps a constant in a register as retail does */
                                if (!(D_80013714 & 8)) {
                                    status_or_base = &D_80083460;
                                    ((S_80089AA0_8 *)status_or_base)->unk_1E = (u16) (((S_80089AA0_8 *)status_or_base)->unk_1E + 1);
                                    temp_v0_2 = ((S_80089AA0_9 *)(&D_800E3D70))->unk_00 + (*(u8 *)((u8 *)arg0_copy + 0x29));
                                    D_800E3D70 = (s32)temp_v0_2;
                                    var_v1_3 = (*(u8 *)((u8 *)arg0_copy + 0x28));
                                    if (temp_v0_2 >= 0x101U) {
                                        do {
                                            temp_v0_3 = (u32)D_800E3D70 - 0x100;
                                            D_800E3D70 = (s32)temp_v0_3;
                                            var_v1_3 += 1;
                                        } while (temp_v0_3 >= 0x101U);
                                    }
                                    temp_a0_2 = (*(u8 *)((u8 *)arg0_copy + 0x29));
                                    if ((s32) temp_a0_2 < (s32) var_v1_3) {
                                        var_v1_3 = temp_a0_2;
                                    }
                                    (*(u8 *)((u8 *)arg0_copy + 0x28)) = var_v1_3;
                                    var_s6 = 1;
                                    page_8008 = &D_800E3D74;
                                    var_a2 = (u32 *)((u8 *)page_8008 + 4);
                                    var_a3 = arg0 + 4;
                                    do {
                                        temp_a1_2 = ((S_80089AA0_10 *)var_a3)->unk_AC;
                                        if ((temp_a1_2 != NULL) && (temp_a1_2->unk_25 != 0)) {
                                            temp_v0_4 = *var_a2 + temp_a1_2->unk_29;
                                            *var_a2 = temp_v0_4;
                                            var_v1_4 = temp_a1_2->unk_28;
                                            if (temp_v0_4 >= 0x101U) {
                                                do {
                                                    temp_v0_5 = *var_a2 - 0x100;
                                                    *var_a2 = temp_v0_5;
                                                    var_v1_4 += 1;
                                                } while (temp_v0_5 >= 0x101U);
                                            }
                                            temp_a0_3 = temp_a1_2->unk_29;
                                            if ((s32) temp_a0_3 < (s32) var_v1_4) {
                                                var_v1_4 = temp_a0_3;
                                            }
                                            temp_a1_2->unk_28 = var_v1_4;
                                        }
                                        var_a2 -= 1;
                                        var_s6 -= 1;
                                        var_a3 -= 4;
                                    } while (var_s6 >= 0);
                                }
                                if ((*(s32 *)((u8 *)arg0_copy + 0x1C)) & 0x800) {
                                    temp_v0_6 = (*(u16 *)((u8 *)arg0 + 0xF8));
                                    (*(u16 *)((u8 *)arg0 + 0xF8)) = (u16) (temp_v0_6 + 1);
                                    (*(s8 *)((u8 *)arg0_copy + 3)) = (s8) ((func_800644B8((s16) temp_v0_6) >> 8) + 0x30);
                                    goto local_89f78;
                                }
                                temp_v0_7 = (*(u16 *)((u8 *)arg0 + 0xF8));
                                (*(u16 *)((u8 *)arg0 + 0xF8)) = (u16) (temp_v0_7 + 1);
                                (*(s8 *)((u8 *)arg0_copy + 3)) = (s8) ((func_800644B8((s16) temp_v0_7) >> 7) + 0x40);
local_89f78:
                                (*(s32 *)((u8 *)arg0 + 0x128)) = (s32) (func_800A6D30() & 0xFFFF);
                                if (!(D_80013714 & 8)) {
                                    (*(u16 *)((u8 *)arg0 + 0x118)) = (u16) ((*(u16 *)((u8 *)arg0 + 0x118)) + 1);
                                }
                                func_800A4ACC(arg0_copy);
                                temp_v1_3 = (*(M2C_UNK (**)(void *, void *, void *, void *))((u8 *)arg0 + 0x8C));
                                if (temp_v1_3 == (Callback4)D_80096384) {
                                    var_v1_5 = &D_80083460;
                                    if ((func_80042900(arg0_copy, 0xA) << 0x10) == 0) {
                                        callback_status = (void *)0x80080000;
                                        ASM_KEEP_NV(callback_status);   /* MATCH pin: load-bearing for the whole function shape */
                                        temp_v0 = (s32)&D_8008ACDC;
                                        callback_status = (u8 *)callback_status + 0x3460;
                                        (*(Callback4 *)((u8 *)arg0 + 0x8C)) = (Callback4)temp_v0;
                                        goto local_a024;
                                    }
                                    goto local_a034;
                                }
                                var_v1_5 = (M2C_UNK *)0x80080000;
                                if (temp_v1_3 == (Callback4)&D_8008ACDC) {
                                    if ((func_80042900(arg0_copy, 0xA) << 0x10) != 0) {
                                        callback_status = (void *)0x80080000;
                                        ASM_KEEP_NV(callback_status);   /* MATCH pin: load-bearing for the whole function shape */
                                        callback_status = (u8 *)callback_status + 0x3460;
                                        (*(Callback4 *)((u8 *)arg0 + 0x8C)) = (Callback4)D_80096384;
                                        goto local_a024;
                                    }
                                    goto local_a034;
                                }
                                goto local_a034;
                            } else {
                                goto local_a034;
                            }
local_a024:
                            ((S_80089AA0_12 *)callback_status)->unk_02 =
                                (u16)(((S_80089AA0_12 *)callback_status)->unk_02 | 4);
local_a034:
                            callback_status = (void *)0x80080000;
                            ASM_KEEP_NV(callback_status);   /* MATCH pin: load-bearing for the whole function shape */
                            callback_status = (u8 *)callback_status + 0x3460;
                            ((S_80089AA0_12 *)callback_status)->unk_02 =
                                (u16)(((S_80089AA0_12 *)callback_status)->unk_02 & 0xBFFB);
                            (*(u32 *)((u8 *)arg0_copy + 0x14)) &= 0x7FFE7FFF;
                            goto after_status_or;
                        }
                        goto block_75;
                    }
                    goto block_74;
                }
                goto block_75;
            }
            goto block_74;
        }
        goto block_75;
    }
block_74:
block_75:
    status_or_base = &D_80083460;
    ((S_80089AA0_8 *)status_or_base)->unk_02 = (u16) (((S_80089AA0_8 *)status_or_base)->unk_02 | 4);
after_status_or:
    if (!(D_80013714 & 8)) {
        if (((*(u8 *)((u8 *)arg0 + 0x9A)) != 0x17) && (D_800DCF4F == 0) && ((u32) ((S_80089AA0_13 *)(&D_800DD160))->unk_00 >= 0x385U)) {
            var_a0 = D_800E3D7C;
            D_800DD160 = 0;
            do {
                var_a0->unk_6C = 0;
                var_a0->unk_71 = (u8) (var_a0->unk_71 & 0x7F);
                var_a0 = var_a0->unk_5C + 0x20;
            } while (var_a0 != D_800E3D7C);
            {
                S_80089AA0_15 *reset_base;
                reset_base = &D_80083460;
                reset_base->unk_08 = 0;
                reset_base->unk_0A = 0;
                reset_base->unk_14 = 0;
                reset_base->unk_0C = 0;
                reset_base->unk_10 = 0;
                reset_base->unk_02 = 0U;
            }
        }
        ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
        if (!(D_80013714 & 8) && (!(D_80083462 & 4) || (((S_80089AA0_6 *)(&D_800E296C))->unk_00 & 0x40) || ((*(u8 *)((u8 *)arg0 + 0x9A)) == 0x17))) {
            D_800E296C = (s32)(D_800E296C & ~0x40);
            if ((func_800C77D0(arg0_copy - 0x20, arg1, 8, D_800DCE60[3]) << 0x10) != 0) {
                D_800832B4[0] = 0;
                func_8004D7A8(1);
                func_8004D294(0, D_800DCE60, 2);
                goto local_a1c4;
            }
            D_800E3D20 = 0;
            goto block_90;
        }
        goto block_90;
    }
block_90:
local_a1c4:
    if (!((*(s32 *)((u8 *)arg0_copy + 0x1C)) & 0x20)) {
        if ((func_80042900(arg0_copy, 0xA) << 0x10) != 0) {
            func_800478B8(arg2);
            goto local_a21c;
        }
        func_80048AC8(arg2, 1);
        goto local_a21c;
    }
    ((S_80089AA0_16 *)arg2)->unk_14 = (u16) (((S_80089AA0_16 *)arg2)->unk_14 | 0x6000);
local_a21c:
    temp_v0_8 = (*(M2C_UNK (**)(void *, void *, void *, void *))((u8 *)arg0 + 0x8C));
    if (temp_v0_8 != NULL) {
        temp_v0_8(arg0, arg1, arg2, arg0_copy);
    }
    D_800DD168[(*(u8 *)((u8 *)arg0 + 0x9A))](arg0, arg1, arg2, arg0_copy);
    temp_s0_2 = ((s32) (D_80083228 + (*(s16 *)((u8 *)arg0_copy + 0x2A)) + 0x100) >> 9) & 7;
    if ((*(s16 *)((u8 *)arg0 + 0x94)) != temp_s0_2) {
        if ((func_80042900(arg0_copy, 0xA) << 0x10) != 0) {
            func_8003DB94(arg2, ((void **)((S_80089AA0_16 *)arg2)->unk_2C)[temp_s0_2], ((S_80089AA0_16 *)arg2)->unk_04);
            goto local_a2e8;
        }
        func_800489F4(arg2, ((u8 *)((S_80089AA0_16 *)arg2)->unk_2C)[temp_s0_2], ((S_80089AA0_16 *)arg2)->unk_04, 1);
local_a2e8:
        (*(s16 *)((u8 *)arg0 + 0x94)) = temp_s0_2;
        if (((*(u8 *)((u8 *)arg0 + 0x9A)) != 0x22) && (D_8006CCF8[temp_s0_2] != 0)) {
            ((S_80089AA0_16 *)arg2)->unk_14 = (u16)(((S_80089AA0_16 *)arg2)->unk_14 | 1);
            goto block_107;
        }
        ((S_80089AA0_16 *)arg2)->unk_14 = (u16) (((S_80089AA0_16 *)arg2)->unk_14 & 0xFFFE);
        goto block_107;
    }
block_107:
    temp_v0_9 = func_8009FB34(((S_80089AA0_16 *)arg2)->unk_24, ((S_80089AA0_16 *)arg2)->unk_25);
    {
        s32 table_index;
        void *table_base;
        S_80089AA0_17 *table_entry;
        ((S_80089AA0_16 *)arg2)->unk_26 = temp_v0_9;
        temp_v0_9 <<= 24;
        table_index = temp_v0_9 >> 24;
        if (table_index >= 0) {
            table_base = D_800E2970;
            table_entry = table_base + (table_index * 0x14);
            table_entry->unk_0C = (u16) (table_entry->unk_0C | 1);
        }
    }
    func_800A020C((*(s32 *)((u8 *)arg0_copy + 0x1C)), arg2 + 0xC);
    if (!((*(s32 *)((u8 *)arg0_copy + 0x14)) & 0x100000)) {
        ((S_80089AA0_18 *)arg1)->unk_00.at00.v = (s32) (((S_80089AA0_18 *)arg1)->unk_00.at00.v + ((S_80089AA0_18 *)arg1)->unk_0C);
        ((S_80089AA0_18 *)arg1)->unk_04.at00.v = (s32) (((S_80089AA0_18 *)arg1)->unk_04.at00.v + ((S_80089AA0_18 *)arg1)->unk_10);
        if (!((*(u16 *)((u8 *)arg0 + 0x98)) & 8)) {
            ((S_80089AA0_18 *)arg1)->unk_14 = (s32) (((S_80089AA0_18 *)arg1)->unk_14 + ((*(s8 *)((u8 *)arg0 + 0x9D)) * 0x14000));
            (*(s8 *)((u8 *)arg0 + 0x9D)) = (s8) ((u8) (*(s8 *)((u8 *)arg0 + 0x9D)) + 1);
        }
        (*(s32 *)((u8 *)arg0 + 0x90)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x90)) + ((S_80089AA0_18 *)arg1)->unk_14);
        temp_v0_10 = func_800BCB04(((S_80089AA0_18 *)arg1)->unk_00.at02.v, ((S_80089AA0_18 *)arg1)->unk_04.at02.v, (s16) ((*(u16 *)((u8 *)arg0_copy + 0x88)) - 0x20));
        if (temp_v0_10 < 0x200) {
            if (((*(s16 *)((u8 *)arg0 + 0x92)) + (s16) (*(u16 *)((u8 *)arg0_copy + 0x88))) >= temp_v0_10) {
                if (((*(u16 *)((u8 *)arg0 + 0x98)) & 4) || (((S_80089AA0_18 *)arg1)->unk_14 < 0)) {
                    shared_a2_flags =
                        (u16)((*(u16 *)((u8 *)arg0 + 0xA2)) & 0xFFEF);
                    goto store_a2_flags;
                }
                (*(s32 *)((u8 *)arg0 + 0x90)) = 0;
                ((S_80089AA0_18 *)arg1)->unk_14 = 0;
                (*(s8 *)((u8 *)arg0 + 0x9D)) = 0;
                if (!((*(u16 *)((u8 *)arg0 + 0xA2)) & 0x10)) {
                    if (!(((S_80089AA0_6 *)(&D_800E296C))->unk_00 & 0x80000)) {
                        func_800A56E0(0x508);
                    }
                    func_800B66C8(arg1);
                }
                shared_a2_flags = (u16) ((*(u16 *)((u8 *)arg0 + 0xA2)) | 0x10);
store_a2_flags:
                (*(volatile u16 *)((u8 *)arg0 + 0xA2)) = shared_a2_flags;
                (*(u16 *)((u8 *)arg0 + 0xA2)) =
                    (u16)((*(u16 *)((u8 *)arg0 + 0xA2)) & 0xF7FF);
                goto local_a514;
            }
            temp_v1_5 = (*(u16 *)((u8 *)arg0 + 0xA2));
            if (temp_v1_5 & 0x800) {
                (*(u16 *)((u8 *)arg0 + 0xA2)) = (u16) (temp_v1_5 & 0xFFEF);
            }
            (*(u16 *)((u8 *)arg0 + 0xA2)) = (u16) ((*(u16 *)((u8 *)arg0 + 0xA2)) | 0x800);
local_a514:
            temp_a0_4 = (*(s32 *)((u8 *)arg0_copy + 0x1C));
            if (temp_a0_4 & 0x40000000) {
                temp_v1_6 = (*(u16 *)((u8 *)arg0_copy + 0x88));
                temp_v0 = temp_a0_4 & 0xBFFFFFFF;
                (*(s32 *)((u8 *)arg0_copy + 0x1C)) = temp_v0;
                temp_a2_role = temp_v1_6;
                ASM_KEEP(temp_a2_role);   /* MATCH pin: retail delay-slot fill depends on it */
                temp_a2_role -= 0x20;
                temp_a2_role <<= 16;
                temp_a2_role >>= 16;
                (*(u16 *)((u8 *)arg0_copy + 0x8A)) = temp_v1_6;
                temp_a0_4 = (s16)func_800BCB04((((S_80089AA0_16 *)arg2)->unk_24 << 6) | 0x20, (((S_80089AA0_16 *)arg2)->unk_25 << 6) | 0x20, temp_a2_role);
                (*(s16 *)((u8 *)arg0 + 0x92)) = (s16) ((u16) (*(s16 *)((u8 *)arg0 + 0x92)) + ((*(u16 *)((u8 *)arg0_copy + 0x88)) - temp_a0_4));
                (*(u16 *)((u8 *)arg0_copy + 0x88)) = (u16) temp_a0_4;
                if (D_80083462 & 0x80) {
                    (*(s32 *)((u8 *)arg0 + 0x90)) = 0;
                    ((S_80089AA0_18 *)arg1)->unk_14 = 0;
                    (*(s8 *)((u8 *)arg0 + 0x9D)) = 0;
                    (*(u16 *)((u8 *)arg0 + 0xA2)) =
                        (u16)((*(u16 *)((u8 *)arg0 + 0xA2)) | 0x10);
                    goto block_133;
                }
            }
            goto block_133;
        }
        temp_v1_7 = (*(u16 *)((u8 *)arg0 + 0xA2));
        if (temp_v1_7 & 0x800) {
            (*(u16 *)((u8 *)arg0 + 0xA2)) = (u16) (temp_v1_7 & 0xFFEF);
        }
        (*(u16 *)((u8 *)arg0 + 0xA2)) = (u16) ((*(u16 *)((u8 *)arg0 + 0xA2)) | 0x800);
block_133:
        ((S_80089AA0_18 *)arg1)->unk_0A = (s16) ((*(u16 *)((u8 *)arg0_copy + 0x88)) + (u16) (*(s16 *)((u8 *)arg0 + 0x92)));
        goto block_134;
    }
block_134:
    func_80096100(arg0, arg1, arg2, arg0_copy);
    if (!((*(s32 *)((u8 *)arg0_copy + 0x14)) & 0x100000)) {
        if ((D_800DD258 != ((S_80089AA0_16 *)arg2)->unk_24) || (D_800DD25A != ((S_80089AA0_16 *)arg2)->unk_25)) {
            func_8009D3B0();
            if ((func_800A2C34(0) << 0x10) == 0) {
                if ((func_800A4474(((S_80089AA0_16 *)arg2)->unk_24, ((S_80089AA0_16 *)arg2)->unk_25) << 0x10) != 0) {
                    (*(u16 *)((u8 *)arg0 + 0xA2)) =
                        (u16)((*(u16 *)((u8 *)arg0 + 0xA2)) | 0x200);
                    goto block_142;
                }
                (*(u16 *)((u8 *)arg0 + 0xA2)) = (u16) ((*(u16 *)((u8 *)arg0 + 0xA2)) & 0xFDFF);
                goto block_142;
            }
        }
block_142:
        arg0 = func_8009B25C(arg0_copy, ((S_80089AA0_16 *)arg2)->unk_24, ((S_80089AA0_16 *)arg2)->unk_25, (s16) (*(u16 *)((u8 *)arg0_copy + 0x88)));
        if (arg0 != NULL) {
            func_8009A180(arg0, D_800814A8);
            (*(s32 *)((u8 *)arg0 + 0x1C)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x1C)) & 0x7FFFFFFF);
        }
        D_800DD258 = (u16) ((S_80089AA0_16 *)arg2)->unk_24;
        D_800DD25A = (u16) ((S_80089AA0_16 *)arg2)->unk_25;
        goto block_145;
    }
block_145:
    var_s1 = (*(void **)((u8 *)arg0_copy + 0x5C)) + 0x20;
    arg2 = arg0_copy;
    if (var_s1 != arg0_copy) {
        do {
            temp_v0_13 = ((S_80089AA0_19_pre *)var_s1)[-1].unk_00.p;
            temp_v0_13->unk_14 = (u16) (temp_v0_13->unk_14 & 0xFFBF);
            var_s1 = ((S_80089AA0_19 *)var_s1)->unk_5C.i + 0x20;
        } while (var_s1 != arg2);
    }
    early_status = &D_80083460;
    if (((S_80089AA0_21 *)early_status)->unk_02 & 0x800) {
        if ((func_800A2C34(0) << 0x10) == 0) {
            if ((s16) ((S_80089AA0_21 *)early_status)->unk_08 == 0) {
                if (((S_80089AA0_21 *)early_status)->unk_14 == 0) {
                    ((S_80089AA0_21 *)early_status)->unk_02 =
                        (u16) ((((S_80089AA0_21 *)early_status)->unk_02 & 0xF7FF) | 0x2000);
                }
            }
        }
    }
    var_v0_3 = &D_80083460;
    temp_v1_8 = ((S_80089AA0_22 *)var_v0_3)->unk_02;
    if (!(temp_v1_8 & 0x400)) {
        if (temp_v1_8 & 0x2000) {
            if ((func_800A2C34(0) << 0x10) == 0) {
                var_s1 = (*(void **)((u8 *)arg0_copy + 0x5C)) + 0x20;
                arg2 = arg0_copy;
                if (var_s1 != arg0_copy) {
                    do {
                        ((S_80089AA0_19 *)var_s1)->unk_8A = (u16) ((S_80089AA0_19 *)var_s1)->unk_88;
                        ((S_80089AA0_19 *)var_s1)->unk_6A = (u16) ((S_80089AA0_19 *)var_s1)->unk_2A;
                        var_s1 = ((S_80089AA0_19 *)var_s1)->unk_5C.i + 0x20;
                    } while (var_s1 != arg2);
                }
                arg2 = arg0_copy;
                do {
                    var_s0 = (*(void **)((u8 *)arg0_copy + 0x5C));
                    var_s1 = (u8 *)var_s0 + 0x20;
                    var_s6_2 = 0;
                    if (var_s1 != arg0_copy) {
                        do {
                            temp_v1_9 = ((S_80089AA0_1 *)var_s0)->unk_10;
                            D_800E3DE8 = ((S_80089AA0_19 *)var_s1)->unk_5C.p;
                            if (temp_v1_9 > 0) {
                                temp_v1_9 |= 0x80000000;
                                ((M2C_UNK (*)(void *, s32, s32)) temp_v1_9)((u8 *)var_s0 + 0x20, ((S_80089AA0_1 *)var_s0)->unk_08, ((S_80089AA0_1 *)var_s0)->unk_0C);
                                if (!(((S_80089AA0_1 *)var_s0)->unk_1E & 0x8000) && (((S_80089AA0_19 *)var_s1)->unk_71 < 0) && (((S_80089AA0_19 *)var_s1)->unk_6D != 0)) {
                                    var_s6_2 += 1;
                                }
                            }
                            var_s0 = D_800E3DE8;
                            var_s1 = (u8 *)var_s0 + 0x20;
                        } while (var_s1 != arg2);
                    }
                } while (var_s6_2 != 0);
                var_s1 = (*(void **)((u8 *)arg0_copy + 0x5C)) + 0x20;
                arg2 = arg0_copy;
                if (var_s1 != arg0_copy) {
                    do {
                        func_800A9AFC(((S_80089AA0_19_pre *)var_s1)[-1].unk_00.i, var_s1);
                        var_s1 = ((S_80089AA0_19 *)var_s1)->unk_5C.i + 0x20;
                    } while (var_s1 != arg2);
                }
                status_or_base = &D_80083460;
                ((S_80089AA0_8 *)status_or_base)->unk_02 =
                    (u16)((((S_80089AA0_8 *)status_or_base)->unk_02 & 0xDFFF) | 0x1000);
                goto block_176;
            }
            ((S_80089AA0_22 *)var_v0_3)->unk_02 = (u16) (((S_80089AA0_22 *)var_v0_3)->unk_02 & 0xDFFF);
            var_s1 = (*(void **)((u8 *)arg0_copy + 0x5C)) + 0x20;
            if (var_s1 != arg0_copy) {
                do {
                    var_s0 = var_s1 - 0x20;
                    temp_v1_10 = ((S_80089AA0_1 *)var_s0)->unk_10;
                    D_800E3DE8 = ((S_80089AA0_19 *)var_s1)->unk_5C.p;
                    if (temp_v1_10 > 0) {
                        temp_v1_10 |= 0x80000000;
                        ((M2C_UNK (*)(void *, s32, s32)) temp_v1_10)(var_s1, ((S_80089AA0_1 *)var_s0)->unk_08, ((S_80089AA0_1 *)var_s0)->unk_0C);
                    }
                    var_s1 = (u8 *)D_800E3DE8 + 0x20;
                } while (var_s1 != arg0_copy);
            }
            status_or_base = &D_80083460;
            ((S_80089AA0_8 *)status_or_base)->unk_02 =
                (u16) (((S_80089AA0_8 *)status_or_base)->unk_02 | 0x2000);
            goto block_176;
        }
    }
block_176:
    tail_status = &D_80083460;
    if (tail_status->unk_10 > 0) {
        tail_status->unk_10 = 0;
    }
    var_s6_2 = 0;
    next_page = (u8 *)0x800E0000;
    ASM_KEEP(next_page);   /* MATCH pin: load-bearing for the whole function shape */
    root_page = (u8 *)0x800E0000;
    sp10 = 0;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    var_v0_5 = tail_status->unk_02 | 1;
    var_v0_4 = tail_status;
loop_179:
    ((S_80089AA0_24 *)var_v0_4)->unk_02 = var_v0_5;
loop_180:
    stack_flag = (s32)0x800E0000;
    ASM_KEEP(stack_flag);   /* MATCH pin: keeps a constant in a register as retail does */
    if ((((S_80089AA0_25 *)((void *)stack_flag))->unk_296C & 0x100000) && ((func_800A2C34(0) << 0x10) == 0)) {
        arg0_copy = ((S_80089AA0_26 *)next_page)->unk_3D7C;
loop_183:
        temp_v1_11 = (*(u8 *)((u8 *)arg0_copy + 0x41));
        temp_a1_3 = (*(u8 *)((u8 *)arg0_copy + 0x42));
        (*(u8 *)((u8 *)arg0_copy + 0x42)) = 0U;
        (*(u8 *)((u8 *)arg0_copy + 0x41)) = 0U;
        (*(s32 *)((u8 *)arg0_copy + 0x18)) = (s32) ((*(s32 *)((u8 *)arg0_copy + 0x18)) + ((temp_v1_11 << 8) | temp_a1_3));
        if ((func_800A1C58(arg0_copy, temp_a1_3) << 0x10) == 0) {
            temp_v0_12 = (*(void **)((u8 *)arg0_copy + 0x5C));
            arg0_copy = (u8 *)temp_v0_12 + 0x20;
            if (arg0_copy == ((S_80089AA0_26 *)next_page)->unk_3D7C) {
                s32 clear_mask;
                clear_mask = (s32)0xFFEF0000;
                ASM_KEEP_NV(clear_mask);   /* MATCH pin: retail schedule: same instructions, different order without it */
                stack_flag = (s32)0x800E0000;
                clear_mask |= 0xFFFF;
                ((S_80089AA0_25 *)((void *)stack_flag))->unk_296C =
                    ((S_80089AA0_25 *)((void *)stack_flag))->unk_296C & clear_mask;
                goto block_186;
            }
            goto loop_183;
        }
        goto block_186_set_c;
    }
block_186:
    arg2 = ((S_80089AA0_26 *)next_page)->unk_3D7C;
    var_s0 = ((S_80089AA0_16 *)arg2)->unk_5C;
    arg0_copy = (u8 *)var_s0 + 0x20;
    arg1 = NULL;
    if (arg0_copy != arg2) {
loop_187:
        next_record = (*(void * volatile *)((u8 *)arg0_copy + 0x5C));
        stack_flag = sp10;
        ((S_80089AA0_27 *)root_page)->unk_3DE8 = next_record;
        if (((stack_flag == 0) || ((*(s8 *)((u8 *)arg0_copy + 0x6D)) != 0) || (((S_80089AA0_24 *)var_v0_4)->unk_14 != 0)) && (((S_80089AA0_1 *)var_s0)->unk_10 > 0)) {
            arg0 = (void *)(s32)(s16)func_800A2C34(0);
            if (((S_80089AA0_24 *)var_v0_4)->unk_14 != 0) {
                if (arg0 == NULL) {
                    if ((((S_80089AA0_1 *)var_s0)->unk_B8 & 0xFFFF0000) == 0x150000) {
                        ((S_80089AA0_24 *)var_v0_4)->unk_0C = (void *) ((u8 *)var_s0 + 0x20);
                        goto block_195;
                    }
                    goto block_201;
                }
                goto block_196;
            }
block_195:
block_196:
            temp_v0 = (s32)0x80000000;
            {
            s32 callback_a1;
            callback_a1 = ((S_80089AA0_1 *)var_s0)->unk_08;
            ASM_KEEP_NV(callback_a1);   /* MATCH pin: retail schedule: same instructions, different order without it */
            temp_v1_10 = ((S_80089AA0_1 *)var_s0)->unk_10;
            temp_v1_10 |= temp_v0;
            ((M2C_UNK (*)(void *, s32, s32)) temp_v1_10)((u8 *)var_s0 + 0x20, callback_a1, ((S_80089AA0_1 *)var_s0)->unk_0C);
            }
            if (!(((S_80089AA0_1 *)var_s0)->unk_1E & 0x8000)) {
                if ((*(s8 *)((u8 *)arg0_copy + 0x6D)) != 0) {
                    arg1 = (void *)((s32)arg1 + 1);
                }
                if ((arg0 == NULL) || ((func_800A2C34(0) << 0x10) != 0)) {
                    goto block_201;
                }
            }
        } else {
block_201:
            var_s0 = ((S_80089AA0_27 *)root_page)->unk_3DE8;
            arg0_copy = (u8 *)var_s0 + 0x20;
            if (arg0_copy != arg2) {
                goto loop_187;
            }
        }
    }
    temp_v1_12 = ((S_80089AA0_24 *)var_v0_4)->unk_02;
    if (temp_v1_12 & 0x1000) {
        if (((S_80089AA0_24 *)var_v0_4)->unk_08 == 0) {
            if (((S_80089AA0_24 *)var_v0_4)->unk_04 == 0) {
                ((S_80089AA0_24 *)var_v0_4)->unk_02 = (u16) ((temp_v1_12 & 0xEFF7) | 0x4000);
                if (arg1 != NULL) {
                    stack_flag = 1;
                    *(s32 *)&sp10 = stack_flag;
                    goto loop_180;
                }
                goto block_219;
block_186_set_c:
                ((S_80089AA0_24 *)var_v0_4)->unk_0C = arg0_copy;
                goto block_186;
            }
        } else {
            goto block_219;
        }
    } else {
        if (!(temp_v1_12 & 0x400)) {
            goto block_219;
        }
        if (temp_v1_12 & 0x800) {
            goto block_219;
        }
        if ((func_800A2C34(0) << 0x10) != 0) {
            goto block_219;
        }
        if ((func_800A2B28() << 0x10) != 0) {
            goto block_219;
        }
        if (var_s6_2 == 0) {
            var_s6_2 = 1;
            goto loop_180;
        }
        temp_v0_14 = ((S_80089AA0_24 *)var_v0_4)->unk_02;
            temp_v1_13 = temp_v0_14 & 0xFBFF;
            ((S_80089AA0_24 *)var_v0_4)->unk_02 = temp_v1_13;
            if (!(temp_v0_14 & 0x4000)) {
                ((S_80089AA0_24 *)var_v0_4)->unk_02 = (u16) (temp_v1_13 | 0x800);
                if (func_800A5C70() != 0) {
                    ((S_80089AA0_24 *)var_v0_4)->unk_02 =
                        (u16)(((S_80089AA0_24 *)var_v0_4)->unk_02 | 0x80);
                    goto function_end;
                }
            }
        goto function_end;
block_219:
        if ((arg0_copy == ((S_80089AA0_26 *)next_page)->unk_3D7C) && (arg1 == NULL)) {
            ((S_80089AA0_24 *)var_v0_4)->unk_02 = (u16) (((S_80089AA0_24 *)var_v0_4)->unk_02 & 0xFFFE);
        }
        temp_v1_14 = ((S_80089AA0_24 *)var_v0_4)->unk_02;
        if (!(temp_v1_14 & 0x80) || (((S_80089AA0_24 *)var_v0_4)->unk_0C != NULL) || (((S_80089AA0_24 *)var_v0_4)->unk_10 != 0) || (((S_80089AA0_24 *)var_v0_4)->unk_0A != 0) || (((S_80089AA0_24 *)var_v0_4)->unk_08 == 0)) {
            goto function_end;
        }
        var_v0_5 = temp_v1_14 & 0xFFF7;
        goto loop_179;
    }
function_end:
    return;
}
