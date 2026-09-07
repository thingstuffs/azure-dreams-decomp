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

/* cfail-repair: tf7-phase1-cache-v3 */
extern volatile s16 D_80013714[8];
extern s32 D_80083460[3];
M2C_UNK __attribute__((noreturn)) func_80017344();  /* extern */
M2C_UNK __attribute__((noreturn)) func_80017390();  /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_800C7B38;

void func_800172A0(void *arg0, s16 arg1) {
    s16 temp_v0;
    s16 temp_v1;
    s16 temp_v1_2;
    u8 *state;
    void *temp_s1;
    s32 temp_s2;
    void *temp_s5;
    u16 *counter;
    s16 direction;
    s32 temp_rand;

    state = (u8 *)&D_80083178;
    temp_s5 = state + 0x1C4;
    temp_s1 = state + 0xB8;
    temp_s2 = (rand() & 0x1FFF) - 0x1000;
    if (!((u16) *D_80013714 & 2)) {
        temp_v1 = M2C_FIELD(arg0, u16 *, 2) + (func_80064584(temp_s2) * 2);
        M2C_FIELD(state, s16 *, 0xA4) = temp_v1;
        if (temp_v1 < 0) {
            M2C_FIELD(state, s16 *, 0xA4) = 0;
            func_80017344();
        }
        if (temp_v1 >= M2C_FIELD(temp_s5, s16 *, 0x1C)) {
            M2C_FIELD(state, s16 *, 0xA4) = (s16) ((u16) M2C_FIELD(temp_s5, s16 *, 0x1C) - 1);
        }
        temp_v1_2 = M2C_FIELD(arg0, u16 *, 6) + (func_800644B8(temp_s2) * 2);
        M2C_FIELD(state, s16 *, 0xA6) = temp_v1_2;
        if (temp_v1_2 < 0) {
            M2C_FIELD(state, s16 *, 0xA6) = 0;
            func_80017390();
        }
        if (temp_v1_2 >= M2C_FIELD(temp_s5, s16 *, 0x1E)) {
            M2C_FIELD(state, s16 *, 0xA6) = (s16) ((u16) M2C_FIELD(temp_s5, s16 *, 0x1E) - 1);
        }
        temp_v0 = (s16) (M2C_FIELD(arg0, u16 *, 0xA) - 0x400);
        M2C_FIELD(state, s16 *, 0xAC) = 0;
        M2C_FIELD(state, s16 *, 0xA8) = temp_v0;
        temp_rand = rand();
        direction = -0x800;
        if (temp_rand & 1) {
            direction = 0x800;
        }
        M2C_FIELD(state, s16 *, 0xB0) = direction;
        M2C_FIELD(temp_s1, void **, 0) = (void *) (temp_s1 + 4);
        M2C_FIELD(temp_s1, s32 *, 0x14) = 1;
        M2C_FIELD(temp_s1, s16 *, 0x24) = 0x40;
        M2C_FIELD(temp_s1, void **, 0xC) = arg0;
        M2C_FIELD(temp_s1, s32 *, 0x18) = 0;
        M2C_FIELD(temp_s1, s16 *, 0x26) = arg1;
        M2C_FIELD(state, M2C_UNK **, 0xB4) = &D_800C7B38;
        temp_v0 = arg1 + ((M2C_FIELD(temp_s1, s16 *, 0x24) + 1) * 0x30);
        M2C_FIELD(state, s16 *, 0x98) = temp_v0;
        M2C_FIELD(temp_s1, s32 *, 0x10) = (s32) temp_v0;
        counter = (u16 *)D_80083460;
        M2C_FIELD(counter, u16 *, 0xA) = (u16) (M2C_FIELD(counter, u16 *, 0xA) + 1);
    }
}
/* Warning: struct S_80083178 is not defined (only forward-declared) */
