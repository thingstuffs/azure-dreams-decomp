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

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern M2C_UNK D_80044BB0;
extern s32 D_800814A0;
extern M2C_UNK D_80088790;
extern M2C_UNK D_800887B8;
extern M2C_UNK D_800887CC;
extern M2C_UNK D_80089A14;

typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
} __attribute__((packed)) Packed12;
typedef struct {
    s32 w0;
    s32 w1;
} __attribute__((packed)) Packed8;
typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 w4;
} __attribute__((packed)) Packed20;
typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} Words4;
typedef struct {
    s32 w0;
    s32 w1;
} Words2;

void func_80089608(void *arg0) {
    unsigned char stack_data[104];
    Words4 *var_a2;
    Words4 *var_a2_2;
    Words4 *var_a3;
    s8 *var_s4;
    s8 *var_s5;
    s16 temp_a0;
    s32 temp_v1;
    s32 var_s2;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a1;
    s32 temp_lo;
    s32 temp_lo_2;
    void *temp_v0;
    void *var_sub;
    void *temp_s1;
    void *temp_t1;
    void *callback;

    var_a3 = (Words4 *)&stack_data[0];
    var_a2 = (Words4 *)&D_80088790;
    temp_t1 = M2C_FIELD(arg0, void **, 0);
    do {
        *var_a3 = *var_a2;
        var_a2++;
        var_a3++;
    } while (var_a2 != ((Words4 *)&D_80088790 + 2));
    *(Words2 *)var_a3 = *(Words2 *)var_a2;
    *(Packed20 *)(stack_data + 40) = *(Packed20 *)&D_800887B8;
    var_a3 = (Words4 *)&stack_data[64];
    var_a2_2 = &D_800887CC;
    do {
        *var_a3 = *var_a2_2;
        var_a2_2++;
        var_a3++;
    } while (var_a2_2 != ((Words4 *)&D_800887CC + 2));
    *(Words2 *)var_a3 = *(Words2 *)var_a2_2;
    if (M2C_FIELD(temp_t1, u16 *, 0x26) & 1) {
        M2C_FIELD(arg0, s16 *, 8) = 0xFF;
    }
    if (M2C_FIELD(temp_t1, s16 *, 0x20) >= 2) {
        M2C_FIELD(arg0, s16 *, 8) = 0xFF;
        goto epilogue;
    }
    temp_v1 = M2C_FIELD(arg0, s16 *, 8);
    switch (temp_v1) {
    case 1:
        goto angle_mode;
    case 0:
        M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + 0x20202);
        if (M2C_FIELD(temp_t1, s16 *, 0x20) == 1) {
            M2C_FIELD(arg0, s16 *, 8)++;
            goto set_spawn_count;
        }
        var_s2 = 9;
        goto spawn_setup;
    case 0xFF:
        goto error_mode;
    default:
        var_s2 = 9;
        goto spawn_setup;
    }

angle_mode:
    temp_a0 = M2C_FIELD(arg0, u16 *, 0xA) + 1;
    M2C_FIELD(arg0, u16 *, 0xA) = (u16) temp_a0;
    if (temp_a0 < 0x80) {
        if (!(temp_a0 & 3)) {
            M2C_FIELD(arg0, s32 *, 4) += 0x10101;
        }
        goto pre_spawn_angle;
    }
    if (temp_a0 < 0x91) {
        temp_a0_2 = M2C_FIELD(arg0, s32 *, 4);
        var_s2 = ((s32) (~temp_a0_2 & 0xFF) >> 1);
        var_s2 = ((var_s2 << 8) + (var_s2 << 16)) + var_s2;
        M2C_FIELD(arg0, s32 *, 4) = temp_a0_2 + var_s2;
        goto pre_spawn_angle;
    }
    if (temp_a0 < 0xA0) {
        temp_a0_3 = M2C_FIELD(arg0, s32 *, 4);
        var_s2 = ((s32) (temp_a0_3 & 0xFF) >> 3);
        var_s2 = ((var_s2 << 8) + (var_s2 << 16)) + var_s2;
        M2C_FIELD(arg0, s32 *, 4) = temp_a0_3 - var_s2;
        goto pre_spawn_angle;
    }
    M2C_FIELD(arg0, s16 *, 8) = 0xFF;
    M2C_FIELD(arg0, s32 *, 4) = 0;
pre_spawn_angle:
    M2C_FIELD(arg0, u16 *, 0xE) -= 12;
    goto set_spawn_count;

error_mode:
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    D_800814A0 |= 0x8000;
    goto epilogue;
set_spawn_count:
    var_s2 = 9;
spawn_setup:
    callback = &D_80089A14;
    var_s5 = (M2C_UNK *)&stack_data[36];
    var_s4 = (M2C_UNK *)&stack_data[18];
    do {
        temp_v0 = func_8003FC64(0x111);
        if (temp_v0 != NULL) {
            temp_s1 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_v0, void **, 0x10) = callback;
            func_8004491C(temp_v0, &D_80044BB0);
            temp_lo = func_80064584(M2C_FIELD(arg0, s16 *, 0xE)) * M2C_FIELD(var_s4, s16 *, 0x28);
            temp_a1 = temp_lo >> 0xC;
            M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 2) = (s16) ((temp_a1 - (temp_lo >> 0xD)) + 0xA0);
            var_sub = (void *)((s8 *)temp_v0 + 0x20);
            temp_lo_2 = func_800644B8(M2C_FIELD(arg0, s16 *, 0xE)) * M2C_FIELD(var_s4, s16 *, 0x28);
            temp_a1 = temp_lo_2 >> 0xC;
            M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 6) = (s16) ((temp_a1 + (temp_lo_2 >> 0xE)) + 0x78);
            M2C_FIELD(temp_s1, s16 *, 0x1E) = 0x1000;
            M2C_FIELD(temp_s1, s16 *, 0x1C) = 0x1000;
            if (var_s2 == 0) {
                M2C_FIELD(temp_s1, s16 *, 0x1A) = M2C_FIELD(arg0, s16 *, 0xE);
                goto configure_spawn;
            }
            if (var_s2 == 1) {
                M2C_FIELD(temp_s1, s16 *, 0x1A) = (s16) (0 - (u16) M2C_FIELD(arg0, s16 *, 0xE));
            }
configure_spawn:
            M2C_FIELD(temp_s1, s16 *, 0x10) = 0x60;
            M2C_FIELD(temp_s1, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s1, u16 *, 0x14) | 0xC);
            M2C_FIELD(temp_s1, s32 *, 8) = (s32) M2C_FIELD(var_s5, s32 *, 0);
            M2C_FIELD(temp_s1, s8 *, 4) = 0;
            M2C_FIELD(temp_s1, s8 *, 5) = 0;
            M2C_FIELD(temp_s1, s32 *, 0xC) = (s32) (M2C_FIELD(arg0, s32 *, 4) & M2C_FIELD(var_s5, s32 *, 0x40));
            M2C_FIELD(var_sub, s16 *, 0xC) = var_s2;
            goto block_43;
        }
block_43:
        var_s5 -= 4;
        var_s2 -= 1;
        var_s4 -= 2;
    } while (var_s2 >= 0);
    return;
epilogue:
    return;
}
