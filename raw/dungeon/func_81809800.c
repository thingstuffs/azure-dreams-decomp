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
extern s16 D_8002715C[5];
extern s16 D_80027156;
extern void func_800478B8(void *, s16, void *, void *);

#ifdef __mips__
void func_80025000(void *, void *, void *);
static const u32 prefix_words[] __asm__("func_80025000")
    __attribute__((section(".text.func_80025000"), aligned(4))) = {
    0x8002527C, 0x800252C0, 0x800253B4, 0x800257F0, 0x80025844,
};
__asm__(
    ".globl func_80025000\n"
    ".type func_80025000,@function\n"
    ".size func_80025000,368\n");
#define BODY_NAME func_80025014
#else
#define BODY_NAME func_80025000
#endif

void BODY_NAME(void *arg0, void *arg1, void *arg2)
    __attribute__((section(".text.func_80025000")));
void BODY_NAME(void *arg0, void *arg1, void *arg2) {
    s16 temp_a0;
    s32 temp_a1;
    s16 temp_v0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    void *temp_a2;
    void *temp_a2_base;
    void *temp_v1;
    s32 arg1_y;
    s32 index;
    s16 *counter;
    s16 gate;
    u16 remaining;

    temp_v1 = M2C_FIELD(arg0, void **, 0);
    index = M2C_FIELD(temp_v1, s16 *, 0x26);
    counter = D_8002715C;
    temp_a2_base = M2C_FIELD(((index * 4) + temp_v1), void **, 0xC);
    arg1_y = M2C_FIELD(arg1, s16 *, 2);
    temp_a2 = M2C_FIELD(temp_a2_base, void **, 8);
    temp_a1 = M2C_FIELD(temp_a2, s16 *, 2);
    counter[0] = (s16) ((u16) counter[0] + 1);
    if ((temp_a1 != arg1_y) || (M2C_FIELD(temp_a2, s16 *, 6) != M2C_FIELD(arg1, s16 *, 6))) {
        M2C_FIELD(arg0, s16 *, 0xA) = 2;
    }
    temp_a0 = M2C_FIELD(arg0, s16 *, 0xA);
    if (temp_a0 != 0) {
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + ((s32) (M2C_FIELD(temp_a2, s32 *, 0) - M2C_FIELD(arg1, s32 *, 0)) / temp_a0));
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + ((s32) (M2C_FIELD(temp_a2, s32 *, 4) - M2C_FIELD(arg1, s32 *, 4)) / (s16) M2C_FIELD(arg0, s16 *, 0xA)));
        temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0xA) - 1;
        M2C_FIELD(arg0, s16 *, 0xA) = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            M2C_FIELD(arg1, s16 *, 2) = (s16) (u16) M2C_FIELD(temp_a2, s16 *, 2);
            M2C_FIELD(arg1, s16 *, 6) = (s16) (u16) M2C_FIELD(temp_a2, s16 *, 6);
            M2C_FIELD(arg0, s16 *, 0xA) = 0;
        }
    }
    func_800478B8(arg2, temp_a1, temp_a2, arg1);
    gate = D_80027156;
    remaining = *(u16 *)&D_80027156;
    if (gate != 0) {
        *(u16 *)&D_80027156 = (u16) (remaining - 1);
    }
    if ((*(u16 *)&D_80027156) & 1) {
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x80);
    } else {
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xFF7F);
    }
}
