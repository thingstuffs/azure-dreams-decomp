/* cfail-repair: tf7-phase1-cache-v3 */
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

typedef void (*TownFunc3)(s32, s32, s32);
typedef void (*TownFunc1)(s32);
typedef struct {
    u8 unk0[0x64];
    TownFunc3 func_64;
    u8 unk68[8];
    TownFunc1 func_70;
} TownState;
typedef struct {
    u8 unk0[0x10];
    u8 *ptr_10;
} TownData;
extern void func_80000DC8(void);
extern s32 D_00001020[];
extern s32 D_00001020_store[] asm("D_00001020");
extern TownState *D_00001040[];
extern TownData *D_00001034[];
extern s32 *D_0000103C[];
extern u8 D_00000694[];
extern u8 D_000006BC[];
extern u8 D_00000FE4[];

void func_808BB5EC(void) {
    register u8 *var_a0 ASM_REG("$4");
    u8 *temp_a0;

    if (D_00001020[0] != 0) {
        D_00001040[0]->func_64(D_00000694, D_000006BC, 0x4B);
        D_00001040[0]->func_70(1);
    }
    D_00001020_store[0] = 1;
    func_80000DC8();
    D_00001034[0]->ptr_10 = D_00000FE4;
    temp_a0 = D_00001034[0]->ptr_10;
    if (temp_a0[1] != 0x80) {
        register s32 end ASM_REG("$5");
        end = 0x80;
        var_a0 = temp_a0 + 1;
        ASM_KEEP(var_a0);
        do {
            *(s32 *)(var_a0 + 0xB) = D_0000103C[0][*(s32 *)(var_a0 + 0xB)];
            var_a0 += 0x14;
        } while (*var_a0 != end);
    }
}
