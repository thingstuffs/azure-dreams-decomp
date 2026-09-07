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

M2C_UNK func_8008D330(); /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_80099844();           /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
void func_800C3D24();                               /* extern */
M2C_UNK func_800D4FC8();    /* extern */
extern M2C_UNK D_80082E80[];
extern s32 D_80083460;
extern M2C_UNK D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E1843[];
extern s32 D_800E3D7C[];

s32 func_800C3C08(void *arg0, s32 arg1, s16 arg2) {
    u8 *global_base;
    u8 temp_v1;

    if (arg0 == D_800E3D7C[0]) {
        M2C_FIELD(arg0, s32 *, 0x110) = arg1;
        func_8008D330(arg0, D_80083780, D_80082E80, arg0);
        func_800C3D24();
        return 0;
    }
    if ((u32) arg0 <= 0x9FFFFFFFU) {
        func_800A63B8(arg0, arg1, arg2);
        if (func_800AD6FC(arg0, (D_800DDE84[M2C_FIELD(arg0, u8 *, 0x13)] >> 6) & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            func_800C3D24();
            return 1;
        }
    }
    temp_v1 = M2C_FIELD(arg0, u8 *, 3);
    if (temp_v1 < 0xFFU) {
        M2C_FIELD(arg0, u8 *, 3) = (u8) (temp_v1 + 1);
        if (M2C_FIELD(arg0, s32 *, 0x14) & 0x4000) {
            func_80099844(arg0, D_800E1843);
        }
    }
    func_800D4FC8(arg0 - 0x20, 0x202020, 0x616);
    func_80098B38(arg1);
    global_base = (u8 *)&D_80083460;
    
    M2C_FIELD(global_base, u16 *, 0xA) = (u16) (M2C_FIELD(global_base, u16 *, 0xA) - 1);
    return 1;
}
/* MECHANISM: The natural args produce the 0x20 frame and s0/s1 holds; the first callee needs four args.
   A void dispatcher plus explicit 0/1 returns gives the two LEAD-22 SHAPE-C jump delay values.
   ASM_KEEP holds &D_80083460 so its addiu base and 0xA lhu/sh displacements remain split. */
