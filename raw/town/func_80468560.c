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

typedef s32 (*M2C_CALLBACK2)(s32, s32);
typedef s32 (*M2C_CALLBACK0)(void);

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

M2C_UNK func_800195AC();                            /* extern */
M2C_UNK func_8001960C();                            /* extern */
extern void func_80019618(void) __attribute__((noreturn));
M2C_UNK func_800196A4();                            /* extern */
M2C_UNK func_8001D048();                            /* extern */
M2C_UNK func_8001E578();                     /* extern */
M2C_UNK func_8001E5F0();                     /* extern */
s32 func_8001E670();                             /* extern */
extern s8 D_80016000[0x10];
extern s16 D_800178BA[0x10];
extern M2C_CALLBACK0 D_800178E8[0x100];
extern s32 D_8001E95C[0x10];

void func_80019560(void) {
    s32 temp_v0;
    register u32 page_value ASM_REG("$2");
    register u8 *page ASM_REG("$16");
    M2C_CALLBACK0 *callback_table;

    func_8001D048();
    if (func_8001E670(0xA3) != 0) {
        if (func_8001E670(0xAB) == 0) {
            func_8001E578(0x409);
            func_800195AC();
            return;
        }
        func_8001E5F0(0x409);
        if (func_8001E670(0xAD) == 0) {
            if (((M2C_CALLBACK2 *)((u8 *)M2C_FIELD(*(void **)D_80016000, void **, 0x20) + 0x350))[0](1, 0x12) != 0) {
                func_8001E578(0xAD);
                func_8001960C();
                return;
        }
        func_8001E578(0x40A);
        {
            register u32 tail_page ASM_REG("$2");
            tail_page = 0x80020000;
            ASM_PAGEBASE_PIN(tail_page);
            func_80019618();
        }
        return;
        }
        goto block_11;
    }
    func_8001E5F0(0x409);
block_11:
    func_8001E5F0(0x40A);
    page_value = 0x80020000;
    ASM_KEEP(page_value);
    page = (u8 *)page_value;
    ASM_KEEP(page);
    callback_table = D_800178E8;
    *(u8 **)(page - 0x16B0) = M2C_FIELD(*(void **)D_80016000, s32 *, 0x40) + 8;
    do {
        temp_v0 = callback_table[**(u8 **)(page - 0x16B0)]();
    } while (temp_v0 == 0);
    D_8001E95C[0] = temp_v0;
    if (func_8001E670(D_800178BA[0]) == 0) {
        func_800196A4();
    }
}
