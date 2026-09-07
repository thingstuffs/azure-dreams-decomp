/* cfail-repair: tf7-phase1-cache-v3 */
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

M2C_UNK func_800175E0();
extern M2C_UNK D_8001624C;
extern M2C_UNK D_800177C8;
extern M2C_UNK *D_8001794C[3];
extern M2C_UNK D_8001802A;
extern u8 D_80010000[];

typedef void (*TownCall)(s32, s32, void *);

void func_8047E1C0(void) {
    void *first_value;
    s32 arg0;
    register void *dispatch ASM_REG("$3");

    arg0 = 0x3B0;
    first_value = &D_8001802A;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(D_80010000, void **, 0x6000), void **, 0x1C), M2C_UNK **, 0x40) = first_value;
    dispatch = M2C_FIELD(M2C_FIELD(D_80010000, void **, 0x6000), void **, 0x20);
    *(volatile M2C_UNK **)&D_8001794C[0] = &D_800177C8;
    M2C_FIELD(dispatch, TownCall *, 0x2EC)(arg0, 0x100, M2C_FIELD(D_80010000, void **, 0x6000));
    func_800175E0(0x98);
    *(void **)((s8 *)M2C_FIELD(M2C_FIELD(D_80010000, void **, 0x6000), s32 *, 0x40) + M2C_FIELD(M2C_FIELD(D_80010000, void **, 0x6000), s32 *, 8) * 8) = &D_8001624C;
}
