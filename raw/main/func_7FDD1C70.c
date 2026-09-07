/* cfail-repair: tf7-phase1-cache-v3 */
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

M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64(); /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_80044BB0;
extern s32 D_80053A88;
extern s8 D_80080A84;
extern M2C_UNK D_80088760;
extern M2C_UNK D_8008896C;
void func_80088B48();  /* extern */
void func_80088EDC();  /* extern */
void func_800890EC();  /* extern */
void func_80089608();  /* extern */
void func_80089A38();  /* extern */
extern M2C_UNK D_8008B230;
extern M2C_UNK D_8008B270;

typedef struct { s32 a, b, c; } Desc3;

void func_80088BD0(void) {
    s32 stack_desc[3];
    s32 var_s2;
    s32 var_s6;
    s32 var_s7;
    s32 const_1000;
    s32 idxval;
    void *temp_s3;
    void *temp_s1;
    void *temp_v0;
    void *temp_v1;
    void *var_fp;
    void *var_s4;
    void *var_s5;

    var_fp = NULL;
    *(Desc3 *)stack_desc = *(Desc3 *)&D_80088760;
    D_80080A84 = 1;
    temp_v0 = func_8003FC64(0x11);
    if (temp_v0 != NULL) {
        var_fp = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = (void *)func_800890EC;
        func_8004491C(temp_v0, &D_8008896C);
        M2C_FIELD(var_fp, s16 *, 0x22) = 0x708;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 6) = 0xF0;
        M2C_FIELD(var_fp, s16 *, 0x1A) = 0;
        M2C_FIELD(var_fp, s16 *, 0x1C) = 0x40;
    }
    var_s2 = 2;
    var_s7 = 0x3C;
    var_s6 = 0xC8;
    const_1000 = 0x1000;
    var_s5 = var_fp + 8;
    do {
        temp_v0 = func_8003FC64(0x111);
        M2C_FIELD(var_s5, void **, 4) = temp_v0;
        var_s4 = (void *)(var_s2 << 2);
        if (temp_v0 != NULL) {
            temp_s3 = temp_v0 + 0x20;
            temp_s1 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = (void *)func_80088EDC;
            func_8004491C(temp_v0, &D_80044BB0);
            M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 2) = -0x40;
            M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 6) = var_s6;
            M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0xC) = 0x150000;
            M2C_FIELD(temp_s1, s16 *, 0x1E) = const_1000;
            M2C_FIELD(temp_s1, s16 *, 0x1C) = const_1000;
            idxval = M2C_FIELD((s8 *)stack_desc + (s32)var_s4, s32 *, 0);
            M2C_FIELD(temp_s1, s8 *, 4) = 0;
            M2C_FIELD(temp_s1, s8 *, 5) = 0;
            M2C_FIELD(temp_s1, s32 *, 0xC) = 0x808080;
            M2C_FIELD(temp_s1, s32 *, 8) = idxval;
            M2C_FIELD((s8 *)temp_s3 - 0x20, void **, 0x20) = var_fp;
            M2C_FIELD(temp_s3, s16 *, 0xC) = var_s2;
            M2C_FIELD(temp_s3, s16 *, 0xA) = var_s7;
        }
        var_s7 -= 0x1E;
        var_s6 -= 0x10;
        var_s2 -= 1;
        var_s5 -= 4;
    } while (var_s2 >= 0);
    temp_v0 = func_8003FC64(1);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = (void *)func_80088B48;
        func_8004491C(temp_v0, &D_80053A88);
        temp_v1 = temp_v0 + 0x20;
        M2C_FIELD(temp_v1, s16 *, 0xC) = 0x60;
        M2C_FIELD(temp_v1, s16 *, 0xE) = -0x100;
        M2C_FIELD(temp_v1, s16 *, 0x10) = 0x80;
        M2C_FIELD(temp_v1, s16 *, 0x12) = 0x10;
        M2C_FIELD(temp_v1, s16 *, 0x14) = 0;
        M2C_FIELD(temp_v1, s16 *, 0x16) = 3;
        M2C_FIELD(temp_v1, s32 *, 8) = 0x606060;
        M2C_FIELD(temp_v0, s16 *, 0x20) = 0;
        M2C_FIELD(temp_v1, void **, 4) = var_fp;
    }
    var_s2 = 1;
    do {
        temp_v0 = func_8003FC64(0x111);
        M2C_FIELD((s8 *)var_fp + (var_s2 << 2), void **, 0x10) = temp_v0;
        if (temp_v0 != NULL) {
            temp_s3 = temp_v0 + 0x20;
            temp_s1 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = (void *)func_80089A38;
            func_8004491C(temp_v0, &D_80044BB0);
            M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 6) = 0xE9;
            if (var_s2 != 0) {
                M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 2) = -0x15;
                M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0xC) = 0x160000;
                func_8003DB94(temp_s1, &D_8008B270, 0);
                goto common_tail;
            }
            M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 2) = 0x155;
            M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0xC) = 0xFFEA0000;
            func_8003DB94(temp_s1, &D_8008B230, 0);
common_tail:
            M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0x10) = 0xFFF80000;
            M2C_FIELD(temp_s1, s16 *, 0x1E) = 0x1000;
            M2C_FIELD(temp_s1, s16 *, 0x1C) = 0x1000;
            M2C_FIELD(temp_s1, s32 *, 0xC) = 0x808080;
            M2C_FIELD(temp_s3, void **, 0) = var_fp;
            M2C_FIELD(temp_s3, s16 *, 0xC) = var_s2;
        }
        var_s2 -= 1;
    } while (var_s2 >= 0);
    temp_v0 = func_8003FC64(1);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = (void *)func_80089608;
        M2C_FIELD(temp_v0, void **, 0x20) = var_fp;
        M2C_FIELD(temp_v0, s16 *, 0x2E) = 0xE00;
    }
}
