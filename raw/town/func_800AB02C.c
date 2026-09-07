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

s32 func_800374F4();                         /* extern */
M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64(s32);               /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                           /* extern */
extern M2C_UNK D_80045340;
extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern M2C_UNK D_800A86BC;
extern M2C_UNK D_800F15AC;

void *func_800A878C(void *arg0, u32 arg1) {
    s16 *temp_a0_2;
    s16 temp_s0_3;
    s16 temp_v0_2;
    s32 temp_a0;
    s32 temp_s0_2;
    s32 var_v0;
    s32 var_v0_2;
    u32 temp_a1;
    void *temp_s0;
    void *temp_s1;
    void *temp_s3;
    void *temp_v0;

    temp_a1 = (arg1 >> 9) & 7;
    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s1 = M2C_FIELD(temp_v0, void **, 8);
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800A86BC;
        func_8004491C(temp_v0, &D_80045340);
        temp_a0 = temp_a1;
        M2C_FIELD(temp_s1, s16 *, 2) = (s16) (M2C_FIELD(arg0, u16 *, 2) - (D_8006CCD8[temp_a0] * 0x10));
        temp_a0_2 = &D_8006CCE8[temp_a0];
        M2C_FIELD(temp_s1, s16 *, 6) = (s16) (M2C_FIELD(arg0, u16 *, 6) - (*temp_a0_2 * 0x10));
        M2C_FIELD(temp_s1, u16 *, 0xA) = (u16) M2C_FIELD(arg0, u16 *, 0xA);
        var_v0 = 0 - (M2C_FIELD(arg0, s32 *, 0xC) * ((rand(temp_a0_2) & 1) + 2));
        temp_s3 = temp_v0 + 0x20;
        if (var_v0 < 0) {
            var_v0 += 0xF;
        }
        M2C_FIELD(temp_s1, s32 *, 0xC) = (s32) (var_v0 >> 4);
        var_v0_2 = 0 - (M2C_FIELD(arg0, s32 *, 0x10) * ((rand() & 1) + 2));
        if (var_v0_2 < 0) {
            var_v0_2 += 0xF;
        }
        M2C_FIELD(temp_s1, s32 *, 0x10) = (s32) (var_v0_2 >> 4);
        M2C_FIELD(temp_s1, s32 *, 0x14) = (s32) ((~rand() & 1) << 0xF);
        func_8003DB94(temp_s0, &D_800F15AC, 0);
        M2C_FIELD(temp_s0, u8 *, 0xE) = 0xFF;
        M2C_FIELD(temp_s0, u8 *, 0xD) = 0xFF;
        M2C_FIELD(temp_s0, u8 *, 0xC) = 0xFF;
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_s0, s16 *, 0x10) = 0x60;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
        temp_s0_2 = func_800374F4(7);
        temp_s0_3 = temp_s0_2 + func_800374F4(7);
        M2C_FIELD(temp_s3, s16 *, 2) = temp_s0_3;
        M2C_FIELD(temp_s1, s32 *, 0x14) = (s32) (0 - (temp_s0_3 << 0x10));
        temp_v0_2 = M2C_FIELD(temp_s3, s16 *, 2);
        M2C_FIELD(temp_s3, s32 *, 4) = (s32) ((s32) (temp_v0_2 * temp_v0_2) / 2);
    }
    return temp_v0;
}

/* MECHANISM: The one-argument allocator ABI and pre-call masked index recover the 0x28 frame and s3 role.
   Sized s16 direction tables and unsigned byte stores recover the scaled lh accesses and li 0xff.
   Spelling the first-table read before the second-table pointer delays the shared sll past lui/addiu. */
