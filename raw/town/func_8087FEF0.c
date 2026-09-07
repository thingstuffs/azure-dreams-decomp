/* cfail-repair baseline: preserve the selected draft's recovered shape. */
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
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
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
#define CARRY 0
#define OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

typedef struct {
    u8 pad00[0x68];
    void (*func68)(void *, void *, s32);
} CallbackTable;

extern void func_80700BC4(s32 arg0);
extern void func_80700C54(s32 arg0);
extern s32 func_80700E3C(void);
extern void func_80700E98(void);
extern void func_80701298(s32 arg0, s32 arg1);

extern s32 D_807013A4[];
extern volatile s32 D_807009B0;
extern volatile s32 D_807009B4;
extern CallbackTable *volatile D_807013B4;
extern u8 D_80700B30[];
extern u8 D_80700B44[];

s32 func_8087FEF0(void) {
    s32 *base = D_807013A4;
    register s32 zero ASM_REG("$0");

#ifdef NON_MATCHING
    zero = 0;
#endif
    func_80700BC4(base[0]);
    func_80700C54(zero);
    func_80700E98();
    {
        s32 value = func_80700E3C();
        CallbackTable *table = D_807013B4;

        D_807009B0 = value;
        table->func68(D_80700B30, D_80700B44, zero | 0xC9);
    }
    func_80700BC4(base[0]);
    func_80701298(D_807009B0, D_807009B4);
    return D_807009B0;
}
