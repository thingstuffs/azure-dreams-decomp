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
typedef struct {
    u8 field0;
    u8 field1;
    u8 field2;
    u8 field3;
} D_800E3648_entry;
typedef struct {
    u8 pad0[6];
    s8 field6;
    s8 field7;
    u32 field8;
    s32 fieldC;
    s16 field10;
    u8 pad12[2];
    s16 field14;
    u8 pad16[2];
} D_800E39C8_entry;
extern D_800E3648_entry D_800E3648[];
extern u8 D_800DF258[];
s32 func_800B500C();                   /* extern */
s32 func_800B5128();                                /* extern */
M2C_UNK func_800B5F80();                         /* extern */
extern void func_8009A21C();
extern D_800E39C8_entry D_800E39C8[];

s32 func_800B60B8(s16 arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4) {
    s32 temp_s1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s1;
    s32 temp_s4;
    D_800E39C8_entry *temp_s0;
    D_800E3648_entry *temp_base;
    D_800E3648_entry *temp_v1;

    temp_s4 = arg3;
    temp_s1 = func_800B500C(arg0, arg1, arg2);
    var_s1 = temp_s1 << 0x10;
    if (var_s1 < 0) {
        temp_s1 = func_800B5128();
        var_s1 = temp_s1 << 0x10;
        if (var_s1 < 0) {
            temp_s1 = 0x1F;
        }
    }
    temp_s1 = temp_s1 << 0x10;
    temp_s1 = temp_s1 >> 0x10;
    func_800B5F80(temp_s1);
    temp_base = D_800E3648;
    temp_v1 = &temp_base[temp_s1];
    temp_v1->field1 = 0x15;
    temp_v1->field3 = 0xC0;
    temp_v1->field0 = temp_s4;
    temp_v1->field2 = 0;
    D_800E39C8[temp_s1].field6 = (s8) arg0;
    D_800E39C8[temp_s1].field7 = (s8) arg1;
    func_8009A21C(arg0, arg1, 0x20);
    D_800E39C8[temp_s1].field10 = arg2;
    D_800E39C8[temp_s1].field14 = 0;
    D_800E39C8[temp_s1].fieldC = arg4;
    D_800E39C8[temp_s1].field8 = *(s32 *)(((s32) (temp_s4 << 0x10) >> 0xE) + D_800DF258);
    return temp_s1;
}
