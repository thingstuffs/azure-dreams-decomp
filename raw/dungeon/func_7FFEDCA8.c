#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
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
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

extern s32 func_8008B2E4(void *);
extern s32 func_8008B3AC(s32);
extern u8 D_800CF828[];
extern u8 D_800CF838[];

void func_8008B408(s32 arg0) {
    register s32 i ASM_REG("$4");
    register void **slot ASM_REG("$2");
    register u8 *table ASM_REG("$3");
    register u8 *entry ASM_REG("$2");

    i = 0;
    table = D_800CF838;
    slot = (void **)(table + (arg0 * 4));
    if (func_8008B2E4(*slot) == 0) {
        i = 0;
    } else {
        i = func_8008B3AC(i);
        if (i >= 0) {
            entry = D_800CF828;
            entry = (u8 *)(i + (s32)entry);
            *entry = arg0;
            return;
        }
        i = 0;
    }

    {
        u8 *scan;
        u8 *scan_base;

        s32 t;

        scan_base = D_800CF828;
        scan = (u8 *)(i + (s32)scan_base);
        do {
            t = *scan;
            if (t == 0) {
                t = (s32)scan_base + i;
                *scan = arg0;
                ((u8 *)t)[1] = 0;
                return;
            }
            i++;
            scan = (u8 *)(i + (s32)scan_base);
        } while (i < 15);
    }
}
