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

void func_80048A44(void *, u8, s32, s32);
s32 func_8004CAE8(s32, s32);
void func_80091934(void *, s32, void *, void *);
s32 func_800990FC(void);
s32 func_80099194(void *, s32);
void func_80099290(s32);
s32 func_8009929C(s32, s32);
s32 func_80099368(s32, s32);
s32 func_8009965C(s32, s32);
s32 func_80099734(void *, s32);
void func_800A56E0(s32);
void func_800A5720(s32);
void *func_800A8608(void *, s32, s32, s32, s32);
extern s32 D_80081484;
extern s16 D_80083160[];
extern s32 D_8008ACDC;
extern s32 D_8008D470;
extern u8 D_800DD100[];
extern u8 D_800E06E3[];
extern u8 D_800E06EB[];

void func_8009255C(void *arg0, s32 arg1, void *arg2, void *arg3) {
    s32 temp_s0;
    s32 temp_v0_2;
    s32 temp_v1;
    void *temp_v0;
    void *temp_v1_2;
    void *temp_v1_3;
    void *page;
    volatile s16 *base;
    register void *call_arg ASM_REG("$4");
    u8 *entry;
    register u8 *table ASM_REG("$3");

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 == 1) {
        goto state_1;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto state_0;
        }
        goto end;
    }
    if (temp_v1 == 2) {
        goto state_2;
    }
    goto end;

state_0:
    page = (void *)0x80080000;
    ASM_KEEP(page);
    base = (volatile s16 *)(page + 0x3160);
    ASM_KEEP(base);
    if ((((M2C_FIELD(base, s16 *, 0xC8) +
             M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) == 2) {
        call_arg = arg2;
        ASM_KEEP(call_arg);
        table = D_800DD100;
        ASM_KEEP(table);
        M2C_FIELD(call_arg, u8 **, 0x2C) = table;
        entry = (u8 *)((s32)(((M2C_FIELD(base, s16 *, 0xC8) +
                                M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) &
                              7) +
                       (s32)table);
        func_80048A44(
            call_arg,
            *entry,
            0,
            1);
        goto increment;
    }
    M2C_FIELD(arg3, s16 *, 0x2A) =
        (u16)M2C_FIELD(arg3, s16 *, 0x2A) + 0x200;
    goto end;

state_1:
    if (func_8004CAE8(M2C_FIELD(arg2, s32 *, 8), 0) == 0) {
        goto end;
    }
    if (M2C_FIELD(arg0, s32 *, 0x110) == (s32)&D_80081484) {
        M2C_FIELD(arg0, s32 *, 0x124) = 0;
        M2C_FIELD(arg0, s32 *, 0x1C) &= 0xFFEFFFFF;
    }
    temp_v0 = func_800A8608(
        arg0 - 0x20, M2C_FIELD(arg0, s32 *, 0x110), 0, 0, 0);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x10) = (s32)&D_8008D470;
        temp_v1_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1_2, s16 *, 2) =
            (M2C_FIELD(arg2, u8 *, 0x24) << 6) + 0x20;
        M2C_FIELD(temp_v1_2, s16 *, 6) =
            (M2C_FIELD(arg2, u8 *, 0x25) << 6) + 0x20;
        M2C_FIELD(temp_v1_2, s16 *, 0xA) =
            M2C_FIELD(arg3, u16 *, 0x88) - 0x30;
        temp_v1_3 = temp_v0 + 0x20;
        M2C_FIELD(temp_v1_3, s16 *, 0xA8) = 0x1E;
        M2C_FIELD(temp_v1_3, s16 *, 0xAA) = 2;
        M2C_FIELD(temp_v1_3, void **, 0x90) = arg2;
        M2C_FIELD(temp_v1_3, s32 *, 0x8C) = arg1;
        M2C_FIELD(temp_v1_3, void **, 0x9C) = arg0 + 0x108;
        temp_v0_2 = func_800990FC();
        temp_s0 = temp_v0_2;
        temp_v0_2 = func_8009929C(8, temp_v0_2);
        temp_v0_2 = func_80099734(arg3, temp_v0_2);
        temp_v0_2 = func_80099194(D_800E06E3, temp_v0_2);
        temp_v0_2 = func_80099368(
            M2C_FIELD(arg0, s32 *, 0x110), temp_v0_2);
        temp_v0_2 = func_80099194(D_800E06EB, temp_v0_2);
        temp_v0_2 = func_8009965C(
            M2C_FIELD(arg0, s32 *, 0x110), temp_v0_2);
        func_80099290(temp_v0_2);
        func_800A5720(temp_s0);
        func_800A56E0(0x509);
    }

increment:
    M2C_FIELD(arg0, u8 *, 0x9B)++;
    goto end;

state_2:
    if ((M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) == 0) {
        goto end;
    }
    if (M2C_FIELD(arg0, s32 *, 0x110) != 0) {
        func_80091934(arg0, arg1, arg2, arg3);
        goto end;
    }
    M2C_FIELD(arg0, s32 *, 0x8C) = (s32)&D_8008ACDC;

end:
    return;
}

/* MECHANISM: True-space local joins restore retail block order and the increment path.
   A volatile held 0x80083160 base reproduces both loads; short-lived a0/v1 roles
   plus index-first entry arithmetic preserve the final addu destination. */
