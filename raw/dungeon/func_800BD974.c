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
extern u8 *D_800E3D7C[];
extern u8 D_80083780[12];
extern u8 D_80082E80[];
extern u8 D_800DDE84[];
extern s32 D_80083460[3];
M2C_UNK func_8008D330(void *arg0, void *arg1, void *arg2, void *arg3);          /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_80099844();           /* extern */
s32 func_800A48F0();        /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8(void *arg0, s32 arg1, s16 arg2);   /* extern */
s32 func_800AD6FC();            /* extern */
M2C_UNK func_800C5BBC(); /* extern */
extern M2C_UNK D_800E1729;

s32 func_800C30D4(void *arg0, s32 arg1, s16 arg2) {
    void *temp_v0;

    if (arg0 == *D_800E3D7C) {
        M2C_FIELD(arg0, s32 *, 0x110) = arg1;
        func_8008D330(arg0, D_80083780, D_80082E80, arg0);
        return 0;
    }
    if ((u32) arg0 <= 0x9FFFFFFFU) {
        func_800A63B8(arg0, arg1, arg2);
        if (func_800AD6FC(arg0, (*((u16 *)(D_800DDE84 + M2C_FIELD(arg0, u8 *, 0x13) * 2)) >> 6) & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
    }
    temp_v0 = M2C_FIELD(arg0, void **, -0x14);
    func_800C5BBC((M2C_FIELD(temp_v0, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(temp_v0, u8 *, 0x25) << 6) | 0x20, M2C_FIELD(arg0, s16 *, 0x88), 0x802080, 0x20, 1);
    if (((func_800A48F0(arg0, 5, 8) << 0x10) != 0) && (M2C_FIELD(arg0, s32 *, 0x14) & 0x4000)) {
        func_80099844(arg0, &D_800E1729);
    }
    func_80098B38(arg1);
    {
        u16 *counter_base = (u16 *)D_80083460;
        counter_base[5] = (u16) (counter_base[5] - 1);
    }
    return 1;
}
