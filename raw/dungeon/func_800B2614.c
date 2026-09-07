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
extern void *D_80089340[];
struct S_80083178__jr {
    /* 0x00 */ char pad0[0xB0];
    /* 0xB0 */ s16 unkB0;                           /* inferred */
    /* 0xB2 */ char padB2[2];
    /* 0xB4 */ void (*callback)();
    /* 0xB8 */ void *field_B8;
    /* 0xBC */ char padBC[0x1C];                    /* maybe part of field_B8[8]? */
    /* 0xD8 */ void *ptr;
};                                                  /* size = 0xDC */

void func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
s32 func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006E24C;
extern M2C_UNK D_8006E258;
extern M2C_UNK D_8006E51C;
extern M2C_UNK D_8006E57C;
extern M2C_UNK D_8006E5D4;
extern M2C_UNK D_800B7C14;

void func_800B7D74(s32 arg0, s32 arg1, s32 arg2, u32 arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    struct S_80083178 *global = &D_80083178;
    s32 var_v0;
    void *temp_s0;
    void *temp_s1;
    void *temp_s2;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 == NULL) {
        goto block_12;
    }
    M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800B7C14;
    func_8004491C(temp_v0, &D_80045340);
    temp_s1 = M2C_FIELD(temp_v0, void **, 8);
    M2C_FIELD(temp_s1, s16 *, 2) = arg0;
    temp_s2 = temp_v0 + 0x20;
    M2C_FIELD(temp_s1, s16 *, 6) = arg1;
    M2C_FIELD(temp_s1, s16 *, 0xA) = arg2;
    temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
    if (arg3 >= 5U) {
        goto block_10;
    }
    (void)jt_keep; goto *D_80089340[(u32)(arg3)];
jt_c0:
    M2C_FIELD(temp_s1, s16 *, 0xE) = (s16) ((rand() & 0x1F) - 0x10);
    M2C_FIELD(temp_s1, s16 *, 0x12) = (s16) ((rand() & 0x1F) - 0x10);
    M2C_FIELD(temp_s1, s16 *, 0x16) = (s16) (-8 - (rand() & 0x1F));
    M2C_FIELD(temp_s2, M2C_UNK **, 8) = &D_8006E5D4;
    func_8003DB94(temp_s0, &D_8006E5D4, 0);
    goto block_11;
jt_c1:
    M2C_FIELD(temp_s0, M2C_UNK **, 8) = &D_8006E24C;
    M2C_FIELD(temp_s1, s16 *, 0x16) = (s16) (-0x10 - (rand() & 0xF));
    M2C_FIELD(temp_s1, s32 *, 0xC) = (s32) (func_80064584(M2C_FIELD(global, s16 *, 0xB0) - 0x300) << 7);
    M2C_FIELD(temp_s1, s32 *, 0x10) = (s32) (func_800644B8(M2C_FIELD(global, s16 *, 0xB0) - 0x300) << 7);
    goto block_6;
    goto block_6;
jt_c2:
    M2C_FIELD(temp_s0, M2C_UNK **, 8) = &D_8006E258;
    M2C_FIELD(temp_s1, s16 *, 0x16) = (s16) (-8 - (rand() & 0xF));
    M2C_FIELD(temp_s1, s32 *, 0xC) = (s32) (func_80064584(M2C_FIELD(global, s16 *, 0xB0) + 0x500) << 7);
    M2C_FIELD(temp_s1, s32 *, 0x10) = (s32) (func_800644B8(M2C_FIELD(global, s16 *, 0xB0) + 0x500) << 7);
block_6:
    M2C_FIELD(temp_s2, s16 *, 0x12) = 1;
    goto block_10;
jt_c3:
    M2C_FIELD(temp_s2, M2C_UNK **, 8) = &D_8006E51C;
    func_8003DB94(temp_s0, &D_8006E51C, 0);
    M2C_FIELD(temp_s1, s32 *, 0xC) = (s32) (func_80064584(M2C_FIELD(global, s16 *, 0xB0)) << 7);
    var_v0 = func_800644B8(M2C_FIELD(global, s16 *, 0xB0)) << 7;
    goto block_9;
jt_c4:
    M2C_FIELD(temp_s2, M2C_UNK **, 8) = &D_8006E57C;
    func_8003DB94(temp_s0, &D_8006E57C, 0);
    M2C_FIELD(temp_s1, s32 *, 0xC) = (s32) ((0 - func_80064584(M2C_FIELD(global, s16 *, 0xB0))) << 7);
    var_v0 = (0 - func_800644B8(M2C_FIELD(global, s16 *, 0xB0))) << 7;
block_9:
    M2C_FIELD(temp_s1, s32 *, 0x10) = var_v0;
    M2C_FIELD(temp_s1, s16 *, 0x16) = (s16) (-0xC - (rand() & 0xF));
block_10:
block_11:
    M2C_FIELD(temp_s0, u8 *, 0xE) = 0x80;
    M2C_FIELD(temp_s0, u8 *, 0xD) = 0x80;
    M2C_FIELD(temp_s0, u8 *, 0xC) = 0x80;
    M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
    M2C_FIELD(temp_s2, s16 *, 0x14) = (s16) ((rand() & 0x1FF) - 0x100);
    M2C_FIELD(temp_s2, s16 *, 0x16) = (s16) ((rand() & 0x1FF) - 0x100);
    M2C_FIELD(temp_s2, s16 *, 0x10) = (s16) ((rand() & 0x1F) + 0x20);
block_12:
    return;
}
