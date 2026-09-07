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

void *func_8003FC64(s32);
void func_8004491C(void *, void *);
extern M2C_UNK D_800248BC;
extern M2C_UNK D_80025238;
extern s8 D_8002745C[];

void func_8195FB34(s16 arg0, s16 arg1, s16 arg2) {
    s16 var_a1;
    s16 var_v1;
    s16 temp_v0;
    s16 temp_v0_2;
    s32 var_v0;
    s8 *base;
    s8 *row;
    void *call_arg;
    void *callback;
    void *temp_a0;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v1;

    var_a1 = 0;
    base = D_8002745C;
    do {
        var_v1 = 0;
        row = (s8 *)(((s32) (var_a1 << 0x10) >> 0xC) + (u32)base);
loop_2:
        var_v0 = var_v1 << 0x10;
        *(s16 *)((var_v0 >> 0xF) + (u32)row) = 0;
        temp_v0_2 = var_v1 + 1;
        var_v1 = temp_v0_2;
        if (temp_v0_2 < 8) {
            goto loop_2;
        }
        temp_v0 = var_a1 + 1;
        var_a1 = temp_v0;
    } while (temp_v0 < 8);
    temp_v0_3 = func_8003FC64(0x202);
    if (temp_v0_3 != NULL) {
        call_arg = temp_v0_3;
        
        callback = &D_800248BC;
        
        M2C_FIELD(temp_v0_3, void **, 0x10) = callback;
        func_8004491C(call_arg, &D_80025238);
        temp_v0_4 = M2C_FIELD(temp_v0_3, void **, 8);
        M2C_FIELD(temp_v0_4, s16 *, 2) = arg0;
        M2C_FIELD(temp_v0_4, s16 *, 6) = arg1;
        M2C_FIELD(temp_v0_4, s16 *, 0xA) = arg2;
        temp_a0 = M2C_FIELD(temp_v0_3, void **, 0xC);
        M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x2000;
        M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x2000;
        M2C_FIELD(temp_a0, s32 *, 0xC) = 0x808080;
        temp_v1 = temp_v0_3 + 0x20;
        M2C_FIELD(temp_a0, s16 *, 0x10) = 0x20;
        M2C_FIELD(temp_v0_3, s32 *, 0x20) = 0xF8F82CC0;
        M2C_FIELD(temp_v1, s16 *, 4) = 0x13D;
        M2C_FIELD(temp_a0, void **, 8) = temp_v1;
        M2C_FIELD(temp_v1, s16 *, 0x4C) = 0x10;
    }
}

/* MECHANISM: The one-argument allocator ABI releases a1/a2 for retail's loop roles.
   Initializing the inner counter inside the outer body fixes the save/init schedule.
   Integer-form offset-plus-base sums preserve both retail addu operand orders. */
