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

void func_80024E5C(void *arg0, void *arg1, void *arg2) {
    register s32 temp_v0_3 ASM_REG("$2");
    register s16 temp_v0_8 ASM_REG("$2");
    register u8 *var_v0 ASM_REG("$2");
    register s32 var_v0_2 ASM_REG("$2");
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

    initial_state = M2C_FIELD(arg0, u16 *, 0x58);
    D_80025B60 = 1;
    if (initial_state < 3U) {
        M2C_FIELD(arg2, s8 *, 0xE) = 0x3C;
        M2C_FIELD(arg2, s8 *, 0xD) = 0x3C;
        M2C_FIELD(arg2, s8 *, 0xC) = 0x3C;
        temp_v1 = M2C_FIELD(arg0, u16 *, 0x72);
        temp_v0 = temp_v1 + 1;
        M2C_FIELD(arg0, u16 *, 0x72) = temp_v0;
        if (!(temp_v0 & 7)) {
            M2C_FIELD(arg0, u16 *, 0x72) = (u16) (temp_v1 + 2);
        }
        if (M2C_FIELD(arg0, u16 *, 0x72) & 1) {
            M2C_FIELD(arg2, u8 *, 0xC) = 0x80;
        }
        if (M2C_FIELD(arg0, u16 *, 0x72) & 2) {
            M2C_FIELD(arg2, u8 *, 0xD) = 0x80;
        }
        if (M2C_FIELD(arg0, u16 *, 0x72) & 4) {
            M2C_FIELD(arg2, u8 *, 0xE) = 0x80;
        }
    }
    if (M2C_FIELD(arg0, s16 *, 0x58) == 0) {
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x5A);
        M2C_FIELD(arg0, u16 *, 0x5A) = (u16) (temp_v0_2 + 1);
        if ((s16) temp_v0_2 >= 6) {
            effect_id = D_80025B38[0];
            M2C_FIELD(arg2, u8 **, 0x2C) = D_80025B38;
            func_80047784(arg2, effect_id, 0);
            M2C_FIELD(arg0, u16 *, 0x5A) = 0U;
            M2C_FIELD(arg0, u16 *, 0x58) = (u16) (M2C_FIELD(arg0, u16 *, 0x58) + 1);
            M2C_FIELD(arg1, u16 *, 0xA) = (u16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x5A);
        }
    }
    ASM_MEM_BARRIER();
    var_s0 = M2C_FIELD(arg0, s16 *, 0x58);
    if (var_s0 == 1) {
        if ((func_800A4778(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) M2C_FIELD(arg1, u16 *, 0xA), M2C_FIELD(arg0, void **, 0x88)) << 0x10) == 0) {
            if (M2C_FIELD(arg0, s16 *, 0x60) != 0) {
                temp_a1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x88), void **, -0x18);
                M2C_FIELD(arg2, s16 *, 6) = 8;
                if (M2C_FIELD(arg0, s16 *, 0x5A) == 0) {
                    temp_v0_3 = M2C_FIELD(temp_a1, s16 *, 2);
                    ASM_KEEP(temp_v0_3);
                    temp_v0_3 -= M2C_FIELD(arg1, s16 *, 2);
                    ASM_KEEP(temp_v0_3);
                    var_a0 = temp_v0_3;
                    if (temp_v0_3 < 0) {
                        var_a0 = 0 - var_a0;
                    }
                    if (var_a0 < 0) {
                        var_a0 += 0x3F;
                    }
                    temp_v0_3 = M2C_FIELD(temp_a1, s16 *, 6);
                    ASM_KEEP(temp_v0_3);
                    temp_v0_3 -= M2C_FIELD(arg1, s16 *, 6);
                    ASM_KEEP(temp_v0_3);
                    var_v0_2 = temp_v0_3;
                    if (temp_v0_3 < 0) {
                        ASM_SCHED_BARRIER();
                        var_v0_2 = 0 - var_v0_2;
                    }
                    ASM_SCHED_BARRIER();
                    if (var_v0_2 < 0) {
                        var_v0_2 += 0x3F;
                    }
                    var_v0_2 = (var_a0 >> 6) + (var_v0_2 >> 6);
                    M2C_FIELD(arg0, u16 *, 0x5A) = (u16) (((s32) (var_v0_2 << 0x10) >> 0xF) + 0xB);
                }
                var_v0 = D_800DDC40;
                temp_a0 = (s16) M2C_FIELD(arg0, u16 *, 0x5A);
                temp_a2 = M2C_FIELD(temp_a1, s32 *, 8) - (((u8) *(M2C_FIELD(M2C_FIELD(arg0, void **, 0x88), u8 *, 0x13) + var_v0) >> 1) << 0x10);
                var_v0_3 = temp_a0 < 0xE;
                ASM_SCHED_BARRIER();
                temp_v1_2 = M2C_FIELD(temp_a1, s32 *, 0);
                temp_a1_2 = M2C_FIELD(temp_a1, s32 *, 4);
                if (var_v0_3 == 0) {
                    ASM_SCHED_BARRIER();
                    current_x = M2C_FIELD(arg1, s32 *, 0);
                    ASM_USE(current_x);
                    M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((temp_v1_2 - current_x) / (s32) (temp_a0 - 0xB));
                    M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (temp_a1_2 - M2C_FIELD(arg1, s32 *, 4)) / (s32) ((s16) M2C_FIELD(arg0, u16 *, 0x5A) - 0xB));
                    ASM_SCHED_BARRIER();
                    temp_v1_2 = M2C_FIELD(arg1, s32 *, 8);
                    temp_v0_3 = M2C_FIELD(arg0, s16 *, 0x5A);
                    temp_v1_2 = temp_a2 - temp_v1_2;
                    temp_v0_3 -= 0xB;
                    ASM_USE(temp_v1_2);
                    ASM_TAILSLOT_PIN(temp_v0_3);
                    func_80025190(temp_a0, temp_a1_2, temp_a2);
                    return;
                }
                ASM_SCHED_BARRIER();
                if (temp_a0 >= 0xB) {
                    ASM_SCHED_BARRIER();
                    current_x = M2C_FIELD(arg1, s32 *, 0);
                    ASM_USE(current_x);
                    M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((temp_v1_2 - current_x) / (s32) (temp_a0 - 9));
                    M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (temp_a1_2 - M2C_FIELD(arg1, s32 *, 4)) / (s32) ((s16) M2C_FIELD(arg0, u16 *, 0x5A) - 9));
                    ASM_SCHED_BARRIER();
                    temp_v1_2 = M2C_FIELD(arg1, s32 *, 8);
                    temp_v0_3 = M2C_FIELD(arg0, s16 *, 0x5A);
                    temp_v1_2 = temp_a2 - temp_v1_2;
                    temp_v0_3 -= 9;
                    ASM_USE(temp_v1_2);
                    ASM_TAILSLOT_PIN(temp_v0_3);
                    func_80025190(temp_a0, temp_a1_2, temp_a2);
                    return;
                }
                ASM_SCHED_BARRIER();
                if (temp_a0 >= 5) {
                    ASM_SCHED_BARRIER();
                    current_x = M2C_FIELD(arg1, s32 *, 0);
                    ASM_USE(current_x);
                    M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((temp_v1_2 - current_x) / (s32) (temp_a0 - 4));
                    M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (temp_a1_2 - M2C_FIELD(arg1, s32 *, 4)) / (s32) ((s16) M2C_FIELD(arg0, u16 *, 0x5A) - 4));
                    M2C_FIELD(arg1, s32 *, 0x14) = (s32) ((s32) (temp_a2 - M2C_FIELD(arg1, s32 *, 8)) / (s32) ((s16) M2C_FIELD(arg0, u16 *, 0x5A) - 4));
                    func_800251F4(temp_a0, temp_a1_2, temp_a2);
                    return;
                }
                M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (temp_v1_2 - M2C_FIELD(arg1, s32 *, 0)) / temp_a0);
                M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (temp_a1_2 - M2C_FIELD(arg1, s32 *, 4)) / (s16) M2C_FIELD(arg0, u16 *, 0x5A));
                M2C_FIELD(arg1, s32 *, 0x14) = (s32) ((s32) (temp_a2 - M2C_FIELD(arg1, s32 *, 8)) / (s16) M2C_FIELD(arg0, u16 *, 0x5A));
                ASM_MEM_BARRIER();
                temp_a0_2 = M2C_FIELD(arg1, s32 *, 0x10);
                temp_a1_3 = M2C_FIELD(arg1, s32 *, 0x14);
                M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
                M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + temp_a0_2);
                M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + temp_a1_3);
                temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x5A) - 1;
                M2C_FIELD(arg0, u16 *, 0x5A) = temp_v0_4;
                if ((temp_v0_4 << 0x10) == 0) {
                    M2C_FIELD(arg0, u16 *, 0x58) = 2U;
                    M2C_FIELD(arg0, s16 *, 0x62) = 6;
                    M2C_FIELD(arg0, u16 *, 0x5A) = 0U;
                    M2C_FIELD(arg1, s32 *, 0x14) = 0;
                    M2C_FIELD(arg1, s32 *, 0x10) = 0;
                    M2C_FIELD(arg1, s32 *, 0xC) = 0;
                    M2C_FIELD(arg0, u16 *, 0x56) = 0x1E;
                    func_800252C4(temp_a0_2, temp_a1_3, temp_a2);
                    return;
                }
                goto block_38;
            }
            M2C_FIELD(arg0, u16 *, 0x5A) = 0xAU;
            M2C_FIELD(arg0, u16 *, 0x5C) = (u16) (M2C_FIELD(arg0, u16 *, 0x5C) - 1);
            M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x98));
            M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x9C));
            M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0xA0));
            if ((s16) M2C_FIELD(arg0, u16 *, 0x5C) > 0) {
block_38:
                if ((s16) M2C_FIELD(arg0, u16 *, 0x5A) >= 5) {
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
    temp_v1_3 = (s16) M2C_FIELD(arg0, u16 *, 0x58);
    if (temp_v1_3 == 2) {
        temp_v0_6 = M2C_FIELD(arg0, u16 *, 0x5A) + 1;
        M2C_FIELD(arg0, u16 *, 0x5A) = temp_v0_6;
        if ((s16) temp_v0_6 == temp_v1_3) {
            func_80024AEC(arg0, arg1, arg2);
            func_800A56E0(0x300);
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x5A) >= 0xA) {
            temp_v0_7 = M2C_FIELD(arg2, u16 *, 0x1C);
            if (temp_v0_7 != 0) {
                temp_v0_8 = temp_v0_7 - 0xC8;
                var_v1 = temp_v0_8;
                if (temp_v0_8 < 0) {
                    var_v1 = 0;
                }
                M2C_FIELD(arg2, u16 *, 0x1C) = var_v1;
                M2C_FIELD(arg2, u16 *, 0x1E) = var_v1;
            }
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x5A) >= 0x1E) {
            M2C_FIELD(arg0, u16 *, 0x56) = (u16) (M2C_FIELD(arg0, u16 *, 0x56) + 3);
            func_800247B8(arg0, arg1, arg2);
            if ((s16) M2C_FIELD(arg0, u16 *, 0x5A) >= 0x28) {
                func_800247B8(arg0, arg1, arg2);
            }
            if ((s16) M2C_FIELD(arg0, u16 *, 0x5A) >= 0x2D) {
                func_800247B8(arg0, arg1, arg2);
            }
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x5A) >= 0x32) {
            M2C_FIELD(arg0, u16 *, 0x58) = 3U;
            M2C_FIELD(arg0, u16 *, 0x5A) = 0U;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x80);
        }
    }
    if ((s16) M2C_FIELD(arg0, u16 *, 0x58) == 3) {
        temp_v0_9 = M2C_FIELD(arg0, u16 *, 0x5A) + 1;
        M2C_FIELD(arg0, u16 *, 0x5A) = temp_v0_9;
        if ((s16) temp_v0_9 < 0x12) {
            var_s0_3 = 0;
            M2C_FIELD(arg0, u16 *, 0x56) = (u16) (M2C_FIELD(arg0, u16 *, 0x56) - 3);
            do {
                func_800247B8(arg0, arg1, arg2);
                temp_v0_10 = var_s0_3 + 1;
                var_s0_3 = temp_v0_10;
            } while (temp_v0_10 < 5);
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x5A) == 0x10) {
            var_s0_4 = 0;
            do {
                func_800247B8(arg0, arg1, arg2);
                temp_v0_11 = var_s0_4 + 1;
                var_s0_4 = temp_v0_11;
            } while (temp_v0_11 < 2);
        }
        var_s0_5 = 0;
        if ((s16) M2C_FIELD(arg0, u16 *, 0x5A) == 0x11) {
            do {
                func_800247B8(arg0, arg1, arg2);
                temp_v0_12 = var_s0_5 + 1;
                var_s0_5 = temp_v0_12;
            } while (temp_v0_12 < 3);
        }
        var_s0_6 = 0;
        if ((s16) M2C_FIELD(arg0, u16 *, 0x5A) == 0x12) {
            do {
                func_800247B8(arg0, arg1, arg2);
                temp_v0_13 = var_s0_6 + 1;
                var_s0_6 = temp_v0_13;
            } while (temp_v0_13 < 4);
        }
        temp_v0_14 = (s16) M2C_FIELD(arg0, u16 *, 0x5A);
        var_s0 = 1;
        if (temp_v0_14 == 1) {
            func_800D4AB0(arg0, arg1, arg2);
            temp_v0_14 = M2C_FIELD(arg0, s16 *, 0x5A);
        }
        if (temp_v0_14 >= 0x1B) {
            goto destroy;
        }
    }
    goto normal_return;
destroy:
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x8C), s16 *, 0x86) = var_s0;
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    D_800814A0 |= 0x8000;
    func_800255B0();
normal_return:
    func_800478B8(arg2);
}
