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
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
} M2C_BLOCK;

typedef struct {
    s8 unk0[8];
    M2C_BLOCK *data;
    s8 unkC[4];
    void *callback;
    s8 unk14[12];
    s32 arg0;
} M2C_OBJECT;

extern s32 D_8002445C[];
void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_800243F8;

void *func_81893024(s32 arg0, void *arg1, s16 arg2, s16 arg3) {
    M2C_BLOCK *src;
    M2C_OBJECT *temp_v0;
    s32 *temp_v0_2;
    M2C_BLOCK *temp_v1;
    void *var_v0;

    temp_v0 = func_8003FC64(0x212);
    do { var_v0 = NULL; } while (0);
    if (temp_v0 != NULL) {
        src = (M2C_BLOCK *)arg1;
        temp_v0->callback = &D_800243F8;
        temp_v0_2 = &temp_v0->arg0;
        temp_v0->arg0 = arg0;
        ((s16 *)temp_v0_2)[2] = 0;
        ((s16 *)temp_v0_2)[3] = arg2;
        temp_v1 = temp_v0->data;
        *temp_v1 = *src;
        M2C_FIELD(temp_v1, u16 *, 0xA) = (s16) (M2C_FIELD(temp_v1, u16 *, 0xA) + arg3);
        func_8004491C(temp_v0, D_8002445C);
        var_v0 = temp_v0;
    }
    return var_v0;
}
