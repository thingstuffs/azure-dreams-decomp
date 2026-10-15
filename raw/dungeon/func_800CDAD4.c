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

M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800AAA54(); /* extern */
M2C_UNK func_800AD4D0();                      /* extern */
M2C_UNK func_800D34AC();                         /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_80083460;
extern M2C_UNK D_800D3140;

void func_800CDAD4(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK *var_v0;
    s16 temp_a0;
    s16 temp_v0;
    s16 temp_v0_2;
    s32 temp_a0_2;
    s32 temp_v1_2;
    s32 var_v0_2;
    s32 var_v0_3;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 != 1) {
        if ((s32) temp_v1 < 2) {
            if (temp_v1 != 0) {
                func_800D34AC();
                return;
            }
            func_800AD4D0(arg3);
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*((((u16) M2C_FIELD(arg3, u16 *, 0x6A) >> 8) & 0xE) + &D_8006CCD8) << 0xF);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (*((((u16) M2C_FIELD(arg3, u16 *, 0x6A) >> 8) & 0xE) + &D_8006CCE8) << 0xF);
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            if (M2C_FIELD(arg3, u8 *, 0x28) != 0) {
                if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
                    M2C_FIELD(arg0, s16 *, 0x96) = 0;
                    func_800D34AC();
                    return;
                }
                M2C_FIELD(arg0, s16 *, 0x96) = 8;
                goto block_13;
            }
            /* Duplicate return node #19. Try simplifying control flow for better match */
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800AAA54(arg0, arg1, arg2, 0);
            func_800D34AC();
            return;
        }
        if (temp_v1 != 2) {
            func_800D34AC();
            return;
        }
        temp_a0 = M2C_FIELD(arg0, s16 *, 0x96);
        if (temp_a0 != 0) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x24) << 6) - (M2C_FIELD(arg1, s16 *, 2) - 0x20)) << 0xF) / temp_a0);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x25) << 6) - (M2C_FIELD(arg1, s16 *, 6) - 0x20)) << 0xF) / (s16) M2C_FIELD(arg0, s16 *, 0x96));
        }
        temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
        M2C_FIELD(arg0, s16 *, 0x96) = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            var_v0 = (M2C_UNK *)0x800D0000;
            if (M2C_FIELD(&D_80083460, s32 *, 0x10) == (arg3 - 0x20)) {
                M2C_FIELD(&D_80083460, s32 *, 0x10) = (s32) (M2C_FIELD(&D_80083460, s32 *, 0x10) & 0x7FFFFFFF);
                var_v0 = &D_800D3140;
            }
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = var_v0;
            M2C_FIELD(arg0, s8 *, 0x9A) = 0xE;
        }
    } else {
block_13:
        temp_v1_2 = M2C_FIELD(arg1, s32 *, 0xC);
        var_v0_2 = temp_v1_2;
        if (temp_v1_2 < 0) {
            var_v0_2 = temp_v1_2 + 3;
        }
        temp_a0_2 = M2C_FIELD(arg1, s32 *, 0x10);
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_v1_2 - (var_v0_2 >> 2));
        var_v0_3 = temp_a0_2;
        if (temp_a0_2 < 0) {
            var_v0_3 = temp_a0_2 + 3;
        }
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_a0_2 - (var_v0_3 >> 2));
        temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
        M2C_FIELD(arg0, s16 *, 0x96) = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            if (M2C_FIELD(arg3, u8 *, 0x28) == 0) {
                M2C_FIELD(arg1, s32 *, 0x14) = 0;
                M2C_FIELD(arg1, s32 *, 0x10) = 0;
                M2C_FIELD(arg1, s32 *, 0xC) = 0;
                func_800AAA54(arg0, arg1, arg2, 0);
                func_800D34AC();
                return;
            }
            M2C_FIELD(arg0, s16 *, 0x96) = 8;
            func_800D34AC(temp_a0_2);
        }
    }
}
