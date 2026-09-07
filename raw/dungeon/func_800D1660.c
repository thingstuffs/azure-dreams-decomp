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
extern u8 D_80083498[];
extern s16 D_80083228[5];
void *func_8003FD64(s32, void *);       /* extern */
void func_8004491C(void *, void *, void *, void *); /* extern */
s32 func_800644B8(s32);                           /* extern */
s32 func_80064584(s32);                           /* extern */
void func_80047784(void *, u8, s32);              /* extern */
extern M2C_UNK D_800D67B0;
extern M2C_UNK D_800D6C18[2];
extern M2C_UNK D_800E23D8;

typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} CopyQuad;

typedef struct {
    u8 pad[8];
    void *field8;
    void *fieldc;
    void *field10;
} AllocBlock;

void func_800D6DC0(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 temp_lo;
    s32 temp_s1;
    s32 temp_t0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 var_s5;
    s32 var_s4;
    void *temp_s0;
    void *temp_s2;
    void *temp_s3;
    void *temp_v0;
    void *var_a2;
    void *var_a3;
    u8 *page;
    s32 scale = 3;

    var_s4 = 0;
    page = (u8 *)&D_800E23D8;
    var_s5 = 0x200;
    do {
        temp_v0 = func_8003FD64(0x112, D_80083498);
        temp_s2 = temp_v0 + 0x20;
        if (temp_v0 != NULL) {
            var_a3 = arg2;
            M2C_FIELD(temp_s2, s16 *, 0xC) = 0x1E;
            M2C_FIELD(temp_s2, s16 *, 0xE) = 0x1E;
            M2C_FIELD(temp_s2, void **, 0x14) = arg1;
            M2C_FIELD(temp_s2, s16 *, 0x10) = var_s4;
            temp_s3 = ((AllocBlock *)temp_v0)->fieldc;
            ((AllocBlock *)temp_v0)->field10 = &D_800D6C18;
            temp_t0 = (s32)((u8 *)var_a3 + 0x30);
            var_a2 = temp_s3;
            do {
                *(CopyQuad *)var_a2 = *(CopyQuad *)var_a3;
                var_a3 += 0x10;
                var_a2 += 0x10;
            } while (var_a3 != (void *)temp_t0);
            M2C_FIELD(temp_s3, s16 *, 0x10) = 0x20;
            M2C_FIELD(temp_s3, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s3, u16 *, 0x14) | 0xC);
            func_8004491C(temp_v0, &D_800D67B0, var_a2, var_a3);
            temp_s0 = ((AllocBlock *)temp_v0)->field8;
            M2C_FIELD(temp_s0, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
            temp_s1 = var_s4 << 9;
            M2C_FIELD(temp_s0, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
            M2C_FIELD(temp_s0, s16 *, 0xA) = (s16) (M2C_FIELD(arg1, u16 *, 0xA) + 0x28);
            M2C_FIELD(temp_s3, s16 *, 0x1E) = 0x1000;
            M2C_FIELD(temp_s3, s16 *, 0x1C) = 0x1000;
            M2C_FIELD(temp_s3, u8 *, 0xE) = 0xFA;
            M2C_FIELD(temp_s3, u8 *, 0xD) = 0xFA;
            M2C_FIELD(temp_s3, u8 *, 0xC) = 0xFA;
            temp_v0_2 = (s32) (scale * func_80064584(temp_s1)) >> 0xC;
            M2C_FIELD(temp_s2, s16 *, 0x48) = (s16) temp_v0_2;
            M2C_FIELD(temp_s2, s16 *, 0x44) = (s16) temp_v0_2;
            temp_v0_3 = (s32) (scale * func_80064584(var_s5)) >> 0xC;
            M2C_FIELD(temp_s2, s16 *, 0x4A) = (s16) temp_v0_3;
            M2C_FIELD(temp_s2, s16 *, 0x46) = (s16) temp_v0_3;
            temp_v0_4 = (s32) (scale * func_800644B8(temp_s1)) >> 0xC;
            M2C_FIELD(temp_s2, s16 *, 0x50) = (s16) temp_v0_4;
            M2C_FIELD(temp_s2, s16 *, 0x4C) = (s16) temp_v0_4;
            temp_lo = scale * func_800644B8(var_s5);
            M2C_FIELD(temp_s2, s16 *, 0x5A) = 0;
            M2C_FIELD(temp_s2, s16 *, 0x58) = 0;
            M2C_FIELD(temp_s2, s16 *, 0x56) = 0;
            M2C_FIELD(temp_s2, s16 *, 0x54) = 0;
            temp_v0_5 = temp_lo >> 0xC;
            M2C_FIELD(temp_s2, s16 *, 0x52) = (s16) temp_v0_5;
            M2C_FIELD(temp_s2, s16 *, 0x4E) = (s16) temp_v0_5;
            M2C_FIELD(temp_s0, s16 *, 0x16) = 0;
            M2C_FIELD(temp_s3, M2C_UNK **, 0x2C) = page;
            func_80047784(temp_s3, *((u8 *) (((((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + (s32) page))), 0);
        }
        var_s4 += 1;
        var_s5 += 0x200;
    } while (var_s4 < 8);
    return;
}
