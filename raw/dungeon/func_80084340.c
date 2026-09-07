#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
/*
 * This header contains macros emitted by m2c in "valid syntax" mode,
 * which can be enabled by passing `--valid-syntax` on the command line.
 *
 * In this mode, unhandled types and expressions are emitted as macros so
 * that the output is compilable without human intervention.
 */


/* Unknown types */
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Bitwise (reinterpret) cast */
#define M2C_BITWISE(type, expr) ((type)(expr))

/* Unaligned reads */
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)

/* Unhandled instructions */
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)

#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define ARM_RRX(x, carry) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)

/* Carry/overflow bits from partially-implemented instructions */
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)

/* Memcpy patterns */
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

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

void func_80089AA0(void *in_arg0, void *in_arg1, void *in_arg2) {
    register void *arg0 ASM_REG("$17");
    register void *arg2 ASM_REG("$18");
    register void *arg1 ASM_REG("$21");
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
    register s32 temp_v0 ASM_REG("$2");
    s16 temp_v0_10;
    s32 *temp_a1;
    register s32 temp_a0_4 ASM_REG("$4");
    register s32 temp_a2_role ASM_REG("$6");
    s32 temp_v1_10;
    register s32 temp_v1_sign ASM_REG("$3");
    s32 temp_v1_9;
    s32 var_s5;
    register s32 var_s6 ASM_REG("$22");
    register s32 var_s6_2 ASM_REG("$22");
    register s32 temp_v0_9 ASM_REG("$2");
    u16 temp_a0;
    u16 temp_v0_14;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v1_12;
    u16 temp_v1_13;
    u16 temp_v1_14;
    u16 temp_v1_2;
    u16 temp_v1_5;
    register u16 temp_v1_6 ASM_REG("$3");
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
    void *temp_a1_2;
    void *temp_s2;
    register void *temp_v0_12 ASM_REG("$2");
    void *temp_v0_13;
    void *temp_v1_4;
    void *var_a0;
    void *var_a3;
    void *var_s0_2;
    void *var_s0_3;
    void *var_s0_4;
    void *var_s1;
    register s32 stack_flag ASM_REG("$9");
    void *var_s1_3;
    void *var_s1_4;
    void *var_s1_5;
    void *var_s4;
    void *var_s4_2;
    register void *arg0_copy ASM_REG("$20");
    void *held_83178;
    void *page_8008;
    void *status_base;
    register void *status_or_base ASM_REG("$3");
    register void *callback_status ASM_REG("$3");
    void *tail_status;
    void *copy_dst;
    void *next_record;
    register u8 *root_page ASM_REG("$23");
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
        if ((D_800E3CD0 == 0) && (M2C_FIELD(base_83160, s32 *, 0x10) != 0)) {
            D_800E3CD0 = 1;
            func_80040AA0(3);
            goto function_end;
        }
        goto block_6;
    }
    var_s0 = (M2C_UNK *)0x80080000;
block_6:
    if ((M2C_FIELD(var_s0, u8 *, 0xAA0) != 0) && (D_800E3CD0 == 0) && (func_80053EF0(1) == 0)) {
        func_80053DA8(0x200);
        M2C_FIELD(var_s0, s8 *, 0xAA0) = 0;
        D_80080A88 = 1;
    }
    ASM_CLOBBER("$2");
    if (D_80013714 & 4) {
        register s16 *dce_base ASM_REG("$2");
        s32 *dce_step_page;
        s32 dce_value;
        s32 reverse_step;
        dce_base = (s16 *)0x800E0000;
        ASM_KEEP_NV(dce_base);
        dce_step_page = (s32 *)0x80080000;
        ASM_KEEP_NV(dce_step_page);
        dce_base = (s16 *)((u8 *)dce_base - 0x31A0);
        reverse_step = *(s32 *)((u8 *)dce_step_page + 0x1468);
        dce_value = dce_base[2];
        ASM_KEEP(reverse_step);
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
    M2C_FIELD(arg0, s16 *, 0x9E) = (s16) (((u16) M2C_FIELD(held_83178, u16 *, 0xB0) >> 9) & 7);
    status_base = &D_80083460;
    M2C_FIELD(status_base, u16 *, 2) = (u16) (M2C_FIELD(status_base, u16 *, 2) & 0xFFCF);
    temp_a1 = &D_800E4948;
    if (M2C_FIELD(status_base, s32 *, 8) == D_800E4948) {
        if (M2C_FIELD(status_base, s32 *, 0xC) == M2C_FIELD(temp_a1, s32 *, 4)) {
            if (M2C_FIELD(status_base, s32 *, 0x10) == M2C_FIELD(temp_a1, s32 *, 8)) {
                if (M2C_FIELD(status_base, s16 *, 0x14) == M2C_FIELD(temp_a1, s16 *, 0xC)) {
                    if (!(D_80013714 & 8)) {
                        temp_v1 = M2C_FIELD(arg0, u8 *, 0x9A);
                        if ((temp_v1 != 0x17) && (temp_v1 != 0x27) && (temp_v1 != 0x29) && (D_800DCF4F == 0)) {
                            if (M2C_FIELD(status_base, s32 *, 0xC) == 0) {
                                if ((M2C_FIELD(status_base, s32 *, 0x10) == 0) && (M2C_FIELD(status_base, s16 *, 0x14) == 0)) {
                                    if (M2C_FIELD(status_base, s32 *, 8) != 0) {
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
    if (M2C_FIELD(var_v1_2, s32 *, 0xC) == 0) {
        if (M2C_FIELD(var_v1_2, s32 *, 0x10) == 0) {
            temp_a0 = M2C_FIELD(var_v1_2, u16 *, 2);
            if (!(temp_a0 & 8) && (M2C_FIELD(var_v1_2, s16 *, 8) == 0)) {
                if (M2C_FIELD(var_v1_2, s16 *, 0x14) == 0) {
                    if (!(M2C_FIELD(&D_800E296C, s32 *, 0) & 0x100000) && (M2C_FIELD(var_v1_2, s16 *, 0xA) == 0)) {
                        if (!(temp_a0 & 0x2E01)) {
                            if ((func_8009F5CC(temp_a0) << 0x10) != 0) {
                                func_800C6AB0();
                            }
                            temp_v1_2 = M2C_FIELD(var_v1_2, u16 *, 2);
                            if (temp_v1_2 & 2) {
                                M2C_FIELD(var_v1_2, u16 *, 2) = (u16) ((temp_v1_2 & 0xFFFD) | 0x20);
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
                                M2C_FIELD(copy_dst, s16 *, -8) = (s16) temp_v0;
                                ASM_CLOBBER("$2");
                                if (!(D_80013714 & 8)) {
                                    status_or_base = &D_80083460;
                                    ASM_KEEP(status_or_base);
                                    M2C_FIELD(status_or_base, u16 *, 0x1E) = (u16) (M2C_FIELD(status_or_base, u16 *, 0x1E) + 1);
                                    temp_v0_2 = M2C_FIELD(&D_800E3D70, s32 *, 0) + M2C_FIELD(arg0_copy, u8 *, 0x29);
                                    D_800E3D70 = (s32)temp_v0_2;
                                    var_v1_3 = M2C_FIELD(arg0_copy, u8 *, 0x28);
                                    if (temp_v0_2 >= 0x101U) {
                                        do {
                                            temp_v0_3 = (u32)D_800E3D70 - 0x100;
                                            D_800E3D70 = (s32)temp_v0_3;
                                            var_v1_3 += 1;
                                        } while (temp_v0_3 >= 0x101U);
                                    }
                                    temp_a0_2 = M2C_FIELD(arg0_copy, u8 *, 0x29);
                                    if ((s32) temp_a0_2 < (s32) var_v1_3) {
                                        var_v1_3 = temp_a0_2;
                                    }
                                    M2C_FIELD(arg0_copy, u8 *, 0x28) = var_v1_3;
                                    var_s6 = 1;
                                    page_8008 = &D_800E3D74;
                                    ASM_KEEP(page_8008);
                                    var_a2 = (u32 *)((u8 *)page_8008 + 4);
                                    var_a3 = arg0 + 4;
                                    do {
                                        temp_a1_2 = M2C_FIELD(var_a3, void **, 0xAC);
                                        if ((temp_a1_2 != NULL) && (M2C_FIELD(temp_a1_2, u8 *, 0x25) != 0)) {
                                            temp_v0_4 = *var_a2 + M2C_FIELD(temp_a1_2, u8 *, 0x29);
                                            *var_a2 = temp_v0_4;
                                            var_v1_4 = M2C_FIELD(temp_a1_2, u8 *, 0x28);
                                            if (temp_v0_4 >= 0x101U) {
                                                do {
                                                    temp_v0_5 = *var_a2 - 0x100;
                                                    *var_a2 = temp_v0_5;
                                                    var_v1_4 += 1;
                                                } while (temp_v0_5 >= 0x101U);
                                            }
                                            temp_a0_3 = M2C_FIELD(temp_a1_2, u8 *, 0x29);
                                            if ((s32) temp_a0_3 < (s32) var_v1_4) {
                                                var_v1_4 = temp_a0_3;
                                            }
                                            M2C_FIELD(temp_a1_2, u8 *, 0x28) = var_v1_4;
                                        }
                                        var_a2 -= 1;
                                        var_s6 -= 1;
                                        var_a3 -= 4;
                                    } while (var_s6 >= 0);
                                }
                                if (M2C_FIELD(arg0_copy, s32 *, 0x1C) & 0x800) {
                                    temp_v0_6 = M2C_FIELD(arg0, u16 *, 0xF8);
                                    M2C_FIELD(arg0, u16 *, 0xF8) = (u16) (temp_v0_6 + 1);
                                    M2C_FIELD(arg0_copy, s8 *, 3) = (s8) ((func_800644B8((s16) temp_v0_6) >> 8) + 0x30);
                                    goto local_89f78;
                                }
                                temp_v0_7 = M2C_FIELD(arg0, u16 *, 0xF8);
                                M2C_FIELD(arg0, u16 *, 0xF8) = (u16) (temp_v0_7 + 1);
                                M2C_FIELD(arg0_copy, s8 *, 3) = (s8) ((func_800644B8((s16) temp_v0_7) >> 7) + 0x40);
local_89f78:
                                M2C_FIELD(arg0, s32 *, 0x128) = (s32) (func_800A6D30() & 0xFFFF);
                                if (!(D_80013714 & 8)) {
                                    M2C_FIELD(arg0, u16 *, 0x118) = (u16) (M2C_FIELD(arg0, u16 *, 0x118) + 1);
                                }
                                func_800A4ACC(arg0_copy);
                                temp_v1_3 = M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *, void *), 0x8C);
                                if (temp_v1_3 == (Callback4)D_80096384) {
                                    var_v1_5 = &D_80083460;
                                    if ((func_80042900(arg0_copy, 0xA) << 0x10) == 0) {
                                        callback_status = (void *)0x80080000;
                                        ASM_KEEP_NV(callback_status);
                                        temp_v0 = (s32)&D_8008ACDC;
                                        ASM_KEEP_NV(temp_v0);
                                        callback_status = (u8 *)callback_status + 0x3460;
                                        M2C_FIELD(arg0, Callback4 *, 0x8C) = (Callback4)temp_v0;
                                        goto local_a024;
                                    }
                                    goto local_a034;
                                }
                                var_v1_5 = (M2C_UNK *)0x80080000;
                                if (temp_v1_3 == (Callback4)&D_8008ACDC) {
                                    if ((func_80042900(arg0_copy, 0xA) << 0x10) != 0) {
                                        callback_status = (void *)0x80080000;
                                        ASM_KEEP_NV(callback_status);
                                        callback_status = (u8 *)callback_status + 0x3460;
                                        M2C_FIELD(arg0, Callback4 *, 0x8C) = (Callback4)D_80096384;
                                        goto local_a024;
                                    }
                                    goto local_a034;
                                }
                                goto local_a034;
                            } else {
                                goto local_a034;
                            }
local_a024:
                            M2C_FIELD(callback_status, u16 *, 2) =
                                (u16)(M2C_FIELD(callback_status, u16 *, 2) | 4);
local_a034:
                            callback_status = (void *)0x80080000;
                            ASM_KEEP_NV(callback_status);
                            callback_status = (u8 *)callback_status + 0x3460;
                            M2C_FIELD(callback_status, u16 *, 2) =
                                (u16)(M2C_FIELD(callback_status, u16 *, 2) & 0xBFFB);
                            M2C_FIELD(arg0_copy, u32 *, 0x14) &= 0x7FFE7FFF;
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
    ASM_KEEP(status_or_base);
    M2C_FIELD(status_or_base, u16 *, 2) = (u16) (M2C_FIELD(status_or_base, u16 *, 2) | 4);
after_status_or:
    if (!(D_80013714 & 8)) {
        if ((M2C_FIELD(arg0, u8 *, 0x9A) != 0x17) && (D_800DCF4F == 0) && ((u32) M2C_FIELD(&D_800DD160, u32 *, 0) >= 0x385U)) {
            var_a0 = D_800E3D7C;
            D_800DD160 = 0;
            do {
                M2C_FIELD(var_a0, s16 *, 0x6C) = 0;
                M2C_FIELD(var_a0, u8 *, 0x71) = (u8) (M2C_FIELD(var_a0, u8 *, 0x71) & 0x7F);
                var_a0 = M2C_FIELD(var_a0, s32 *, 0x5C) + 0x20;
            } while (var_a0 != D_800E3D7C);
            {
                register void *reset_base ASM_REG("$2");
                reset_base = &D_80083460;
                M2C_FIELD(reset_base, s16 *, 8) = 0;
                M2C_FIELD(reset_base, s16 *, 0xA) = 0;
                M2C_FIELD(reset_base, s16 *, 0x14) = 0;
                M2C_FIELD(reset_base, s32 *, 0xC) = 0;
                M2C_FIELD(reset_base, s32 *, 0x10) = 0;
                M2C_FIELD(reset_base, u16 *, 2) = 0U;
            }
        }
        ASM_SCHED_BARRIER();
        if (!(D_80013714 & 8) && (!(D_80083462 & 4) || (M2C_FIELD(&D_800E296C, s32 *, 0) & 0x40) || (M2C_FIELD(arg0, u8 *, 0x9A) == 0x17))) {
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
    if (!(M2C_FIELD(arg0_copy, s32 *, 0x1C) & 0x20)) {
        if ((func_80042900(arg0_copy, 0xA) << 0x10) != 0) {
            func_800478B8(arg2);
            goto local_a21c;
        }
        func_80048AC8(arg2, 1);
        goto local_a21c;
    }
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
local_a21c:
    temp_v0_8 = M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *, void *), 0x8C);
    if (temp_v0_8 != NULL) {
        temp_v0_8(arg0, arg1, arg2, arg0_copy);
    }
    D_800DD168[M2C_FIELD(arg0, u8 *, 0x9A)](arg0, arg1, arg2, arg0_copy);
    temp_s0_2 = ((s32) (D_80083228 + M2C_FIELD(arg0_copy, s16 *, 0x2A) + 0x100) >> 9) & 7;
    if (M2C_FIELD(arg0, s16 *, 0x94) != temp_s0_2) {
        if ((func_80042900(arg0_copy, 0xA) << 0x10) != 0) {
            func_8003DB94(arg2, ((void **)M2C_FIELD(arg2, void **, 0x2C))[temp_s0_2], M2C_FIELD(arg2, s8 *, 4));
            goto local_a2e8;
        }
        func_800489F4(arg2, ((u8 *)M2C_FIELD(arg2, void **, 0x2C))[temp_s0_2], M2C_FIELD(arg2, s8 *, 4), 1);
local_a2e8:
        M2C_FIELD(arg0, s16 *, 0x94) = temp_s0_2;
        if ((M2C_FIELD(arg0, u8 *, 0x9A) != 0x22) && (D_8006CCF8[temp_s0_2] != 0)) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16)(M2C_FIELD(arg2, u16 *, 0x14) | 1);
            goto block_107;
        }
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xFFFE);
        goto block_107;
    }
block_107:
    temp_v0_9 = func_8009FB34(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    {
        register s32 table_index ASM_REG("$4");
        register void *table_base ASM_REG("$2");
        register void *table_entry ASM_REG("$3");
        M2C_FIELD(arg2, s8 *, 0x26) = temp_v0_9;
        temp_v0_9 <<= 24;
        table_index = temp_v0_9 >> 24;
        ASM_KEEP(table_index);
        if (table_index >= 0) {
            table_base = D_800E2970;
            table_entry = table_base + (table_index * 0x14);
            M2C_FIELD(table_entry, u16 *, 0xC) = (u16) (M2C_FIELD(table_entry, u16 *, 0xC) | 1);
        }
    }
    func_800A020C(M2C_FIELD(arg0_copy, s32 *, 0x1C), arg2 + 0xC);
    if (!(M2C_FIELD(arg0_copy, s32 *, 0x14) & 0x100000)) {
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
        if (!(M2C_FIELD(arg0, u16 *, 0x98) & 8)) {
            M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + (M2C_FIELD(arg0, s8 *, 0x9D) * 0x14000));
            M2C_FIELD(arg0, s8 *, 0x9D) = (s8) ((u8) M2C_FIELD(arg0, s8 *, 0x9D) + 1);
        }
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + M2C_FIELD(arg1, s32 *, 0x14));
        temp_v0_10 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg0_copy, u16 *, 0x88) - 0x20));
        if (temp_v0_10 < 0x200) {
            if ((M2C_FIELD(arg0, s16 *, 0x92) + (s16) M2C_FIELD(arg0_copy, u16 *, 0x88)) >= temp_v0_10) {
                if ((M2C_FIELD(arg0, u16 *, 0x98) & 4) || (M2C_FIELD(arg1, s32 *, 0x14) < 0)) {
                    shared_a2_flags =
                        (u16)(M2C_FIELD(arg0, u16 *, 0xA2) & 0xFFEF);
                    goto store_a2_flags;
                }
                M2C_FIELD(arg0, s32 *, 0x90) = 0;
                M2C_FIELD(arg1, s32 *, 0x14) = 0;
                M2C_FIELD(arg0, s8 *, 0x9D) = 0;
                if (!(M2C_FIELD(arg0, u16 *, 0xA2) & 0x10)) {
                    if (!(M2C_FIELD(&D_800E296C, s32 *, 0) & 0x80000)) {
                        func_800A56E0(0x508);
                    }
                    func_800B66C8(arg1);
                }
                shared_a2_flags = (u16) (M2C_FIELD(arg0, u16 *, 0xA2) | 0x10);
store_a2_flags:
                M2C_FIELD(arg0, volatile u16 *, 0xA2) = shared_a2_flags;
                M2C_FIELD(arg0, u16 *, 0xA2) =
                    (u16)(M2C_FIELD(arg0, u16 *, 0xA2) & 0xF7FF);
                goto local_a514;
            }
            temp_v1_5 = M2C_FIELD(arg0, u16 *, 0xA2);
            if (temp_v1_5 & 0x800) {
                M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (temp_v1_5 & 0xFFEF);
            }
            M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (M2C_FIELD(arg0, u16 *, 0xA2) | 0x800);
local_a514:
            temp_a0_4 = M2C_FIELD(arg0_copy, s32 *, 0x1C);
            if (temp_a0_4 & 0x40000000) {
                temp_v1_6 = M2C_FIELD(arg0_copy, u16 *, 0x88);
                temp_v0 = temp_a0_4 & 0xBFFFFFFF;
                M2C_FIELD(arg0_copy, s32 *, 0x1C) = temp_v0;
                temp_a2_role = temp_v1_6;
                ASM_KEEP(temp_a2_role);
                temp_a2_role -= 0x20;
                temp_a2_role <<= 16;
                temp_a2_role >>= 16;
                M2C_FIELD(arg0_copy, u16 *, 0x8A) = temp_v1_6;
                temp_a0_4 = (s16)func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, temp_a2_role);
                M2C_FIELD(arg0, s16 *, 0x92) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x92) + (M2C_FIELD(arg0_copy, u16 *, 0x88) - temp_a0_4));
                M2C_FIELD(arg0_copy, u16 *, 0x88) = (u16) temp_a0_4;
                if (D_80083462 & 0x80) {
                    M2C_FIELD(arg0, s32 *, 0x90) = 0;
                    M2C_FIELD(arg1, s32 *, 0x14) = 0;
                    M2C_FIELD(arg0, s8 *, 0x9D) = 0;
                    M2C_FIELD(arg0, u16 *, 0xA2) =
                        (u16)(M2C_FIELD(arg0, u16 *, 0xA2) | 0x10);
                    goto block_133;
                }
            }
            goto block_133;
        }
        temp_v1_7 = M2C_FIELD(arg0, u16 *, 0xA2);
        if (temp_v1_7 & 0x800) {
            M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (temp_v1_7 & 0xFFEF);
        }
        M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (M2C_FIELD(arg0, u16 *, 0xA2) | 0x800);
block_133:
        M2C_FIELD(arg1, s16 *, 0xA) = (s16) (M2C_FIELD(arg0_copy, u16 *, 0x88) + (u16) M2C_FIELD(arg0, s16 *, 0x92));
        goto block_134;
    }
block_134:
    func_80096100(arg0, arg1, arg2, arg0_copy);
    if (!(M2C_FIELD(arg0_copy, s32 *, 0x14) & 0x100000)) {
        if ((D_800DD258 != M2C_FIELD(arg2, u8 *, 0x24)) || (D_800DD25A != M2C_FIELD(arg2, u8 *, 0x25))) {
            func_8009D3B0();
            if ((func_800A2C34(0) << 0x10) == 0) {
                if ((func_800A4474(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25)) << 0x10) != 0) {
                    M2C_FIELD(arg0, u16 *, 0xA2) =
                        (u16)(M2C_FIELD(arg0, u16 *, 0xA2) | 0x200);
                    goto block_142;
                }
                M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (M2C_FIELD(arg0, u16 *, 0xA2) & 0xFDFF);
                goto block_142;
            }
        }
block_142:
        arg0 = func_8009B25C(arg0_copy, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) M2C_FIELD(arg0_copy, u16 *, 0x88));
        if (arg0 != NULL) {
            func_8009A180(arg0, D_800814A8);
            M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) & 0x7FFFFFFF);
        }
        D_800DD258 = (u16) M2C_FIELD(arg2, u8 *, 0x24);
        D_800DD25A = (u16) M2C_FIELD(arg2, u8 *, 0x25);
        goto block_145;
    }
block_145:
    var_s1 = M2C_FIELD(arg0_copy, void **, 0x5C) + 0x20;
    arg2 = arg0_copy;
    if (var_s1 != arg0_copy) {
        do {
            temp_v0_13 = M2C_FIELD(var_s1, void **, -0x14);
            M2C_FIELD(temp_v0_13, u16 *, 0x14) = (u16) (M2C_FIELD(temp_v0_13, u16 *, 0x14) & 0xFFBF);
            var_s1 = M2C_FIELD(var_s1, s32 *, 0x5C) + 0x20;
        } while (var_s1 != arg2);
    }
    ASM_CLOBBER("$2");
    early_status = &D_80083460;
    if (M2C_FIELD(early_status, u16 *, 2) & 0x800) {
        if ((func_800A2C34(0) << 0x10) == 0) {
            if ((s16) M2C_FIELD(early_status, s32 *, 8) == 0) {
                if (M2C_FIELD(early_status, s16 *, 0x14) == 0) {
                    M2C_FIELD(early_status, u16 *, 2) =
                        (u16) ((M2C_FIELD(early_status, u16 *, 2) & 0xF7FF) | 0x2000);
                }
            }
        }
    }
    var_v0_3 = &D_80083460;
    temp_v1_8 = M2C_FIELD(var_v0_3, u16 *, 2);
    if (!(temp_v1_8 & 0x400)) {
        if (temp_v1_8 & 0x2000) {
            if ((func_800A2C34(0) << 0x10) == 0) {
                var_s1 = M2C_FIELD(arg0_copy, void **, 0x5C) + 0x20;
                arg2 = arg0_copy;
                if (var_s1 != arg0_copy) {
                    do {
                        M2C_FIELD(var_s1, u16 *, 0x8A) = (u16) M2C_FIELD(var_s1, u16 *, 0x88);
                        M2C_FIELD(var_s1, u16 *, 0x6A) = (u16) M2C_FIELD(var_s1, u16 *, 0x2A);
                        var_s1 = M2C_FIELD(var_s1, s32 *, 0x5C) + 0x20;
                    } while (var_s1 != arg2);
                }
                ASM_CLOBBER("$18");
                arg2 = arg0_copy;
                do {
                    var_s0 = M2C_FIELD(arg0_copy, void **, 0x5C);
                    var_s1 = (u8 *)var_s0 + 0x20;
                    var_s6_2 = 0;
                    if (var_s1 != arg0_copy) {
                        do {
                            temp_v1_9 = M2C_FIELD(var_s0, s32 *, 0x10);
                            D_800E3DE8 = M2C_FIELD(var_s1, void **, 0x5C);
                            if (temp_v1_9 > 0) {
                                temp_v1_9 |= 0x80000000;
                                ((M2C_UNK (*)(void *, s32, s32)) temp_v1_9)((u8 *)var_s0 + 0x20, M2C_FIELD(var_s0, s32 *, 8), M2C_FIELD(var_s0, s32 *, 0xC));
                                if (!(M2C_FIELD(var_s0, u16 *, 0x1E) & 0x8000) && (M2C_FIELD(var_s1, s8 *, 0x71) < 0) && (M2C_FIELD(var_s1, s8 *, 0x6D) != 0)) {
                                    var_s6_2 += 1;
                                }
                            }
                            var_s0 = D_800E3DE8;
                            var_s1 = (u8 *)var_s0 + 0x20;
                        } while (var_s1 != arg2);
                    }
                } while (var_s6_2 != 0);
                var_s1 = M2C_FIELD(arg0_copy, void **, 0x5C) + 0x20;
                ASM_CLOBBER("$18");
                arg2 = arg0_copy;
                if (var_s1 != arg0_copy) {
                    do {
                        func_800A9AFC(M2C_FIELD(var_s1, s32 *, -0x14), var_s1);
                        var_s1 = M2C_FIELD(var_s1, s32 *, 0x5C) + 0x20;
                    } while (var_s1 != arg2);
                }
                status_or_base = &D_80083460;
                M2C_FIELD(status_or_base, u16 *, 2) =
                    (u16)((M2C_FIELD(status_or_base, u16 *, 2) & 0xDFFF) | 0x1000);
                goto block_176;
            }
            M2C_FIELD(var_v0_3, u16 *, 2) = (u16) (M2C_FIELD(var_v0_3, u16 *, 2) & 0xDFFF);
            var_s1 = M2C_FIELD(arg0_copy, void **, 0x5C) + 0x20;
            if (var_s1 != arg0_copy) {
                do {
                    var_s0 = var_s1 - 0x20;
                    temp_v1_10 = M2C_FIELD(var_s0, s32 *, 0x10);
                    D_800E3DE8 = M2C_FIELD(var_s1, void **, 0x5C);
                    if (temp_v1_10 > 0) {
                        temp_v1_10 |= 0x80000000;
                        ((M2C_UNK (*)(void *, s32, s32)) temp_v1_10)(var_s1, M2C_FIELD(var_s0, s32 *, 8), M2C_FIELD(var_s0, s32 *, 0xC));
                    }
                    var_s1 = (u8 *)D_800E3DE8 + 0x20;
                } while (var_s1 != arg0_copy);
            }
            status_or_base = &D_80083460;
            M2C_FIELD(status_or_base, u16 *, 2) =
                (u16) (M2C_FIELD(status_or_base, u16 *, 2) | 0x2000);
            goto block_176;
        }
    }
block_176:
    tail_status = &D_80083460;
    if (M2C_FIELD(tail_status, s32 *, 0x10) > 0) {
        M2C_FIELD(tail_status, s32 *, 0x10) = 0;
    }
    var_s6_2 = 0;
    next_page = (u8 *)0x800E0000;
    ASM_KEEP(next_page);
    root_page = (u8 *)0x800E0000;
    ASM_KEEP(root_page);
    sp10 = 0;
    ASM_SCHED_BARRIER();
    var_v0_5 = M2C_FIELD(tail_status, u16 *, 2) | 1;
    var_v0_4 = tail_status;
loop_179:
    M2C_FIELD(var_v0_4, u16 *, 2) = var_v0_5;
loop_180:
    ASM_SCHED_BARRIER();
    stack_flag = (s32)0x800E0000;
    ASM_KEEP(stack_flag);
    if ((M2C_FIELD((void *)stack_flag, s32 *, 0x296C) & 0x100000) && ((func_800A2C34(0) << 0x10) == 0)) {
        arg0_copy = M2C_FIELD(next_page, void **, 0x3D7C);
loop_183:
        temp_v1_11 = M2C_FIELD(arg0_copy, u8 *, 0x41);
        temp_a1_3 = M2C_FIELD(arg0_copy, u8 *, 0x42);
        M2C_FIELD(arg0_copy, u8 *, 0x42) = 0U;
        M2C_FIELD(arg0_copy, u8 *, 0x41) = 0U;
        M2C_FIELD(arg0_copy, s32 *, 0x18) = (s32) (M2C_FIELD(arg0_copy, s32 *, 0x18) + ((temp_v1_11 << 8) | temp_a1_3));
        if ((func_800A1C58(arg0_copy, temp_a1_3) << 0x10) == 0) {
            temp_v0_12 = M2C_FIELD(arg0_copy, void **, 0x5C);
            ASM_CLOBBER("$20");
            arg0_copy = (u8 *)temp_v0_12 + 0x20;
            if (arg0_copy == M2C_FIELD(next_page, void **, 0x3D7C)) {
                s32 clear_mask;
                clear_mask = (s32)0xFFEF0000;
                ASM_KEEP_NV(clear_mask);
                stack_flag = (s32)0x800E0000;
                ASM_KEEP(stack_flag);
                clear_mask |= 0xFFFF;
                M2C_FIELD((void *)stack_flag, s32 *, 0x296C) =
                    M2C_FIELD((void *)stack_flag, s32 *, 0x296C) & clear_mask;
                goto block_186;
            }
            goto loop_183;
        }
        goto block_186_set_c;
    }
block_186:
    arg2 = M2C_FIELD(next_page, void **, 0x3D7C);
    var_s0 = M2C_FIELD(arg2, void **, 0x5C);
    arg0_copy = (u8 *)var_s0 + 0x20;
    arg1 = NULL;
    if (arg0_copy != arg2) {
loop_187:
        next_record = M2C_FIELD(arg0_copy, void * volatile *, 0x5C);
        stack_flag = sp10;
        ASM_KEEP(stack_flag);
        M2C_FIELD(root_page, void **, 0x3DE8) = next_record;
        if (((stack_flag == 0) || (M2C_FIELD(arg0_copy, s8 *, 0x6D) != 0) || (M2C_FIELD(var_v0_4, s16 *, 0x14) != 0)) && (M2C_FIELD(var_s0, s32 *, 0x10) > 0)) {
            arg0 = (void *)(s32)(s16)func_800A2C34(0);
            if (M2C_FIELD(var_v0_4, s16 *, 0x14) != 0) {
                if (arg0 == NULL) {
                    if ((M2C_FIELD(var_s0, s32 *, 0xB8) & 0xFFFF0000) == 0x150000) {
                        M2C_FIELD(var_v0_4, void **, 0xC) = (void *) ((u8 *)var_s0 + 0x20);
                        goto block_195;
                    }
                    goto block_201;
                }
                goto block_196;
            }
block_195:
block_196:
            temp_v0 = (s32)0x80000000;
            ASM_KEEP_NV(temp_v0);
            ASM_SCHED_BARRIER();
            {
            register s32 callback_a1 ASM_REG("$5");
            callback_a1 = M2C_FIELD(var_s0, s32 *, 8);
            ASM_KEEP_NV(callback_a1);
            temp_v1_10 = M2C_FIELD(var_s0, s32 *, 0x10);
            temp_v1_10 |= temp_v0;
            ((M2C_UNK (*)(void *, s32, s32)) temp_v1_10)((u8 *)var_s0 + 0x20, callback_a1, M2C_FIELD(var_s0, s32 *, 0xC));
            }
            if (!(M2C_FIELD(var_s0, u16 *, 0x1E) & 0x8000)) {
                if (M2C_FIELD(arg0_copy, s8 *, 0x6D) != 0) {
                    arg1 = (void *)((s32)arg1 + 1);
                }
                if ((arg0 == NULL) || ((func_800A2C34(0) << 0x10) != 0)) {
                    goto block_201;
                }
            }
        } else {
block_201:
            var_s0 = M2C_FIELD(root_page, void **, 0x3DE8);
            arg0_copy = (u8 *)var_s0 + 0x20;
            if (arg0_copy != arg2) {
                goto loop_187;
            }
        }
    }
    temp_v1_12 = M2C_FIELD(var_v0_4, u16 *, 2);
    if (temp_v1_12 & 0x1000) {
        if (M2C_FIELD(var_v0_4, s16 *, 8) == 0) {
            if (M2C_FIELD(var_v0_4, s16 *, 4) == 0) {
                M2C_FIELD(var_v0_4, u16 *, 2) = (u16) ((temp_v1_12 & 0xEFF7) | 0x4000);
                if (arg1 != NULL) {
                    stack_flag = 1;
                    ASM_KEEP(stack_flag);
                    *(s32 *)&sp10 = stack_flag;
                    goto loop_180;
                }
                goto block_219;
block_186_set_c:
                M2C_FIELD(var_v0_4, void **, 0xC) = arg0_copy;
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
        temp_v0_14 = M2C_FIELD(var_v0_4, u16 *, 2);
            temp_v1_13 = temp_v0_14 & 0xFBFF;
            M2C_FIELD(var_v0_4, u16 *, 2) = temp_v1_13;
            if (!(temp_v0_14 & 0x4000)) {
                M2C_FIELD(var_v0_4, u16 *, 2) = (u16) (temp_v1_13 | 0x800);
                if (func_800A5C70() != 0) {
                    M2C_FIELD(var_v0_4, u16 *, 2) =
                        (u16)(M2C_FIELD(var_v0_4, u16 *, 2) | 0x80);
                    goto function_end;
                }
            }
        goto function_end;
block_219:
        if ((arg0_copy == M2C_FIELD(next_page, void **, 0x3D7C)) && (arg1 == NULL)) {
            M2C_FIELD(var_v0_4, u16 *, 2) = (u16) (M2C_FIELD(var_v0_4, u16 *, 2) & 0xFFFE);
        }
        temp_v1_14 = M2C_FIELD(var_v0_4, u16 *, 2);
        if (!(temp_v1_14 & 0x80) || (M2C_FIELD(var_v0_4, void **, 0xC) != NULL) || (M2C_FIELD(var_v0_4, s32 *, 0x10) != 0) || (M2C_FIELD(var_v0_4, s16 *, 0xA) != 0) || (M2C_FIELD(var_v0_4, s16 *, 8) == 0)) {
            goto function_end;
        }
        var_v0_5 = temp_v1_14 & 0xFFF7;
        goto loop_179;
    }
function_end:
    return;
}
