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

M2C_UNK func_80042B68();             /* extern */
M2C_UNK func_80048A44(); /* extern */
M2C_UNK func_8008CAEC();                      /* extern */
M2C_UNK func_80094E34();                            /* extern */
s32 func_800A6D30();                                /* extern */
extern s16 D_80083228;
extern u8 D_800DCFE0[];
extern u8 D_800DCFE8[];
extern u8 D_800E3E41;

void func_8008CAA0(void *arg0, s32 arg1, void *arg2, void *arg3) {
    register u8 *table ASM_REG("$5");
    M2C_FIELD(arg0, u16 *, 0x10C) = (s16) (M2C_FIELD(arg0, u16 *, 0x10C) & 0xFFFE);
    {
        register s32 mask ASM_REG("$3") = 0x20000000;
        if (M2C_FIELD(arg3, s32 *, 0x1C) & mask) {
            register u8 *page ASM_REG("$2");
#ifdef NON_MATCHING
            func_8008CAEC(arg2, D_800DCFE0);
#else
            page = (u8 *) 0x800E0000;
            ASM_KEEP(page);
            func_8008CAEC(arg2, page - 0x3020);
#endif
            return;
        }
        ASM_KEEP(mask);
    }
    {
        register u8 *page ASM_REG("$2");
#ifdef NON_MATCHING
        table = D_800DCFE8;
#else
        page = (u8 *) 0x800E0000;
        ASM_KEEP(page);
        table = page - 0x3018;
#endif
        ASM_KEEP(table);
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = table;
    {
        register u8 *entry ASM_REG("$2");
        entry = table + (((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7);
        ASM_KEEP_NV(entry);
        func_80048A44(arg2, *entry, 0, 1);
    }
    M2C_FIELD(arg0, s8 *, 0x9A) = 7;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    func_80094E34();
    if (!(func_800A6D30() & 1)) {
        func_80042B68(arg3, 1);
        func_80042B68(arg3, 4);
        func_80042B68(arg3, 2);
    }
    {
        register s32 mask ASM_REG("$3") = 0x20000000;
        if (M2C_FIELD(arg3, s32 *, 0x1C) & mask) {
            M2C_FIELD(arg0, s16 *, 0x96) = (s16) D_800E3E41;
        }
        ASM_KEEP(mask);
    }
}
