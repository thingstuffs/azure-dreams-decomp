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

M2C_UNK func_80048A44(void *, u8, s32, s32); /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
M2C_UNK func_8008CAA0(); /* extern */
M2C_UNK func_8008CBD4(); /* extern */
M2C_UNK func_8008E0A4();                            /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800AD4D0();                      /* extern */
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_8008ACDC;
extern u8 D_800DCFB0[8];
extern u8 D_800DCFE0[8];
extern s32 D_800E296C;

void func_8008DDE8(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_a0;
    s32 temp_a1;
    s32 temp_v1;
    u16 temp_v0;
    u16 temp_v0_3;
    u16 temp_timer;
    u32 temp_v0_2;
    register u32 temp_page ASM_REG("$2");
    u8 *temp_table;
    register s32 *temp_global ASM_REG("$4");

    if (M2C_FIELD(arg0, u8 *, 0x9B) == 0) {
        func_800AD4D0(arg3);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        M2C_FIELD(arg1, u32 *, 0xC) = (u32) (func_80064584(M2C_FIELD(arg3, s16 *, 0x6A)) << 9);
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (func_800644B8(M2C_FIELD(arg3, s16 *, 0x6A)) << 9);
        M2C_FIELD(arg0, u16 *, 0x96) = 0xCU;
    }
    if (M2C_FIELD(arg0, u16 *, 0x10C) & 1) {
        func_8008CAA0(arg0, arg1, arg2, arg3);
        func_8008E0A4();
        return;
    }
    if ((M2C_FIELD(arg2, u8 **, 0x2C) == D_800DCFE0) && (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000)) {
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
        if ((temp_v0 << 0x10) > 0) {
            func_80048A44(arg2, M2C_FIELD(arg2, u8 **, 0x2C)[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
        }
    }
    temp_a0 = (s16) M2C_FIELD(arg0, u16 *, 0x96);
    if (temp_a0 > 0) {
        temp_v1 = M2C_FIELD(arg1, s32 *, 0);
        temp_a1 = M2C_FIELD(arg1, s32 *, 4);
        M2C_FIELD(arg1, s32 *, 0) = (s32) (temp_v1 + ((s32) ((((M2C_FIELD(arg2, u8 *, 0x24) << 6) + 0x20) << 0x10) - temp_v1) / temp_a0));
        M2C_FIELD(arg1, s32 *, 4) = (s32) (temp_a1 + ((s32) ((((M2C_FIELD(arg2, u8 *, 0x25) << 6) + 0x20) << 0x10) - temp_a1) / (s16) M2C_FIELD(arg0, u16 *, 0x96)));
        temp_v0_2 = M2C_FIELD(arg1, u32 *, 0xC);
        M2C_FIELD(arg1, u32 *, 0xC) = (u32) ((s32) (temp_v0_2 + (temp_v0_2 >> 0x1F)) >> 1);
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) M2C_FIELD(arg1, s32 *, 0x10) / 2);
        temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_3;
        if ((temp_v0_3 << 0x10) == 0) {
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, u32 *, 0xC) = 0U;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        }
    }
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
        temp_table = D_800DCFB0;
        M2C_FIELD(arg2, u8 **, 0x2C) = temp_table;
        func_80048A44(arg2, temp_table[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
        temp_page = 0x80080000;
        ASM_KEEP(temp_page);
        temp_global = (s32 *)(temp_page + 0x3460);
        ASM_KEEP(temp_global);
        if (M2C_FIELD(temp_global, s32 *, 0x10) == (arg3 - 0x20)) {
            M2C_FIELD(temp_global, s32 *, 0x10) = (s32) (M2C_FIELD(temp_global, s32 *, 0x10) & 0x7FFFFFFF);
        }
        if (M2C_FIELD(arg3, u8 *, 0x28) == 0) {
            if (D_800E296C & 0x08000000) {
                M2C_FIELD(arg3, u8 *, 0x28) = 1U;
                goto assign_timer;
            }
            M2C_FIELD(arg3, u8 *, 0x28) = 0U;
            func_8008CBD4(arg0, arg1, arg2, arg3);
            func_8008E0A4();
            return;
        }
        temp_timer = 8U;
        goto store_timer;
assign_timer:
        temp_timer = 8U;
store_timer:
        M2C_FIELD(arg0, u16 *, 0x96) = temp_timer;
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8008ACDC;
    }
}

/* MECHANISM: Byte-table typing plus X/Y-before-scale statement order aligns the body.
   The true-space 0x8008E090 edge is a local two-predecessor timer join, not a callee.
   Held $v0 page and $a0 base reconstruct D_80083460; cdk closes the final lui reorder. */
