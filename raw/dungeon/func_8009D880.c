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

s32 func_8003AD08();                        /* extern */
s32 func_800990FC();                                /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
s32 func_80099734();                     /* extern */
s32 func_800A2DB8();                          /* extern */
M2C_UNK func_800A319C();                   /* extern */
M2C_UNK func_800A5720();                         /* extern */
extern void *D_8007359C;
extern M2C_UNK D_80089000;
extern M2C_UNK D_800E09CD;
extern M2C_UNK D_800E09D9;
extern M2C_UNK D_800E09E6;
extern M2C_UNK D_800E09EE;
extern M2C_UNK D_800E09FB;

void func_800A2FE0(void *arg0) {
    s32 temp_v0_3;
    s32 temp_v0_4;
    register s32 temp_v0_5 ASM_REG("$16");
    register s32 temp_v0_raw ASM_REG("$2");
    s32 temp_a;
    s32 temp_v1;
    s32 var_s2;
    s32 var_v1;
    void *temp_global;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1_2;

    var_s2 = 0;
    temp_v0 = M2C_FIELD(arg0, void **, 0x60);
    var_v1 = 0;
    if ((temp_v0 != NULL) && (M2C_FIELD(temp_v0, s32 *, 0x14) & 0x4000)) {
        temp_a = M2C_FIELD(arg0, s32 *, 0x14) & 0x4000;
        var_v1 = temp_a != 0;
    }
    if (var_v1 == 0) {
        var_s2 = func_800A2DB8(arg0);
    }
    temp_v1 = M2C_FIELD(arg0, s32 *, 0x14);
    if (!(temp_v1 & 0x20000000)) {
        if (!(temp_v1 & 0x4000)) {
            temp_v0_2 = M2C_FIELD(arg0, void **, 0x60);
            if ((temp_v0_2 != NULL) && (M2C_FIELD(temp_v0_2, s8 *, 0x13) >= 0)) {
                do { temp_v0_3 = func_800990FC(); } while (0);
                func_80099290(func_80099194(&D_80089000, func_80099734(arg0, func_80099194(&D_800E09CD, temp_v0_3))));
                func_800A5720(temp_v0_3);
            }
        }
        if ((var_s2 != 0) && (temp_v1_2 = M2C_FIELD(arg0, void **, 0x60), (temp_v1_2 != NULL))) {
            if (M2C_FIELD(temp_v1_2, s32 *, 0x14) & 0x4000) {
                if (!(M2C_FIELD(arg0, s32 *, 0x14) & 0x4000)) {
                    do { temp_v0_raw = func_800990FC(); } while (0);
                    temp_global = D_8007359C;
                    ASM_KEEP(temp_v0_raw);
                    temp_v0_5 = temp_v0_raw;
                    ASM_KEEP(temp_v0_5);
                    func_8003AD08(var_s2, func_80099194(&D_800E09D9, func_80099194(M2C_FIELD(temp_global, M2C_UNK **, 4), temp_v0_5)));
                    func_800A319C(&D_800E09E6);
                }
            } else if (M2C_FIELD(temp_v1_2, s8 *, 0x13) >= 0) {
                do { temp_v0_4 = func_800990FC(); } while (0);
                func_80099290(func_80099194(&D_800E09FB, func_8003AD08(var_s2, func_80099194(&D_800E09EE, func_80099734(M2C_FIELD(arg0, void **, 0x60), temp_v0_4)))));
                func_800A5720(temp_v0_4);
            }
        }
    }
}

/* MECHANISM: The seed's 0x20 frame, s1/s2/s0 roles, CFG, and 124-word shape were already exact.
   The middle func_800990FC result stays guarded in v0 through the D_8007359C load, then copies
   to guarded s0 in that load-delay slot; this fixes both equal-length register substitutions. */
