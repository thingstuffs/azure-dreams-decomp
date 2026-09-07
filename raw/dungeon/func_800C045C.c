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
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083460;
extern M2C_UNK D_800C5A64;
extern M2C_UNK D_800DEA68;

void *func_800C5BBC(s16 arg0, s16 arg1, s16 arg2, s32 arg3, u16 arg4, s16 arg5) {
    M2C_UNK var_a0;
    s32 var_s2;
    s32 var_s3;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v0;
    void *temp_v1;
    void *var_s4;
    void *var_s5;

    var_s4 = NULL;
    if (arg5 != 0) {
        func_800A56E0(0x608);
    }
    var_s2 = 0;
    var_s3 = (rand() & 0xF) | 0x10;
    if (var_s3 >= 0) {
        var_s5 = &D_80083460;
        do {
            var_a0 = 0x12;
            if (var_s2 != 0) {
                var_a0 = 0x212;
            }
            temp_v0 = func_8003FC64(var_a0);
            if (temp_v0 != NULL) {
                M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800C5A64;
                func_8004491C(temp_v0, &D_80045340);
                temp_s0 = M2C_FIELD(temp_v0, void **, 8);
                M2C_FIELD(temp_s0, u16 *, 2) = (u16) arg0;
                M2C_FIELD(temp_s0, s16 *, 6) = arg1;
                M2C_FIELD(temp_s0, s16 *, 0xA) = arg2;
                M2C_FIELD(temp_s0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_s0, s32 *, 0xC) + (((rand() & 0x1F) - 0x10) << 0xE));
                M2C_FIELD(temp_s0, s32 *, 0x10) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x10) + (((rand() & 0x1F) - 0x10) << 0xE));
                M2C_FIELD(temp_s0, s32 *, 0x14) = (s32) ((0 - ((rand() & 0xF) + 0x18)) << 0xD);
                temp_s0_2 = M2C_FIELD(temp_v0, void **, 0xC);
                func_8003DB94(temp_s0_2, &D_800DEA68, 0);
                M2C_FIELD(temp_s0_2, s32 *, 0xC) = arg3;
                M2C_FIELD(temp_s0_2, s16 *, 0x1E) = 0x1000;
                M2C_FIELD(temp_s0_2, s16 *, 0x1C) = 0x1000;
                M2C_FIELD(temp_s0_2, u16 *, 0x10) = arg4;
                M2C_FIELD(temp_s0_2, s16 *, 0x12) = 3;
                M2C_FIELD(temp_s0_2, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0_2, u16 *, 0x14) | 0xC);
                temp_v1 = temp_v0 + 0x20;
                M2C_FIELD(temp_v1, s16 *, 0x10) = (s16) ((rand() & 0xF) | 0x10);
                M2C_FIELD(temp_v1, s16 *, 0xC) = var_s2;
                if (var_s2 == 0) {
                    var_s4 = temp_v0;
                    M2C_FIELD(var_s5, u16 *, 0xA) = (u16) (M2C_FIELD(var_s5, u16 *, 0xA) + 1);
                }
            }
            var_s3 -= 1;
            var_s2 += 1;
        } while (var_s3 >= 0);
    }
    return var_s4;
}
