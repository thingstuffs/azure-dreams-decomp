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

void func_8003DB94(void *, void *, s32, void *);
void *func_8003FD64(s32, void *);
void func_8004491C(void *, void *);
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800BD688;
extern M2C_UNK D_800BD898;
extern M2C_UNK D_800E9E14;

typedef struct {
    s32 words[4];
} Copy16;

typedef struct {
    s32 words[2];
} Copy8;

s32 func_800BD980(void *arg0) {
    void *src;
    s32 var_s1;
    s32 var_s4;
    void *temp_a0;
    void *temp_a3;
    void *temp_v0;
    void *temp_v1;
    void *var_s3;
    M2C_UNK *bd898;

    src = arg0;
    var_s3 = NULL;
    temp_v0 = func_8003FD64(0x202, &D_80083498);
    if (temp_v0 != NULL) {
        var_s3 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800BD688;
        M2C_FIELD(temp_v0, Copy16 *, 0x28) = M2C_FIELD(src, Copy16 *, 0);
        M2C_FIELD(temp_v0, Copy8 *, 0x38) = M2C_FIELD(src, Copy8 *, 0x10);
    }
    var_s1 = 1;
    bd898 = &D_800BD898;
    var_s4 = 0x300000;
    var_s3 = var_s3 + 4;
    do {
        temp_v0 = func_8003FD64(0x312, &D_80083498);
        if (temp_v0 != NULL) {
            register s32 xoff ASM_REG("$8");
            register s32 color ASM_REG("$9");
            u16 first;
            u16 second;
            s32 offset0;
            s32 offset4;
            s32 offset8;

            func_8004491C(temp_v0, &D_80045340);
            xoff = 0xFFF88000;
            color = 0x800000;
            ASM_KEEP_NV(color);
            temp_a3 = M2C_FIELD(temp_v0, void **, 8);
            ASM_KEEP(temp_a3);
            color |= 0x8080;
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = bd898;
            *(void **)var_s3 = temp_a3;
            temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
            ASM_KEEP(temp_a0);
            first = M2C_FIELD(src, u16 *, 2);
            ASM_KEEP(first);
            temp_v1 = temp_v0 + 0x20;
            M2C_FIELD(temp_v1, volatile u16 *, 0xC) = first;
            ASM_KEEP(first);
            second = M2C_FIELD(src, volatile u16 *, 6);
            ASM_KEEP_NV(second);
            M2C_FIELD(temp_v1, volatile u16 *, 0xE) = second;
            M2C_FIELD(temp_v1, volatile u16 *, 0x10) = M2C_FIELD(src, volatile u16 *, 0xA);
            offset0 = var_s4 + 0x01400000;
            M2C_FIELD(temp_a3, s32 *, 0) = (s32) (M2C_FIELD(src, s32 *, 0) + offset0);
            {
                s32 input4;
                input4 = M2C_FIELD(src, s32 *, 4);
                offset4 = var_s1 << 0x15;
                M2C_FIELD(temp_a3, s32 *, 4) = (s32) (input4 + offset4);
            }
            offset8 = (var_s1 << 0x13) + 0xFF800000;
            M2C_FIELD(temp_a3, s32 *, 8) = (s32) (M2C_FIELD(src, s32 *, 8) + offset8);
            ASM_KEEP_NV(xoff);
            M2C_FIELD(temp_a3, s32 *, 0xC) = (s32) (xoff - (var_s1 << 0x10));
            M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x1000;
            M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x1000;
            ASM_KEEP_NV(color);
            M2C_FIELD(temp_a0, s32 *, 0xC) = color;
            func_8003DB94(temp_a0, &D_800E9E14, 0, temp_a3);
        }
        var_s4 += 0xFFD00000;
        var_s1 -= 1;
        var_s3 = (void *)((s8 *)var_s3 - 4);
    } while (var_s1 >= 0);
    return 0;
}
