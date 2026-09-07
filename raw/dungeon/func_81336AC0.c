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

extern void func_80047784(void *, u8, s32);
extern void func_800A4ACC(void *);
extern s16 D_80083228[8];
extern u8 D_801739E0[];

void func_8016DAC0(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 temp_v1;
    u32 temp_v0;
    u8 *temp_a1;

    M2C_FIELD(arg3, u8 *, 0x71) = (s8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    temp_v1 = M2C_FIELD(arg0, u8 *, 0xAC);
    M2C_FIELD(arg0, s8 *, 0x9A) = 0x18;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    if (temp_v1 != 1) {
        if ((s32) temp_v1 < 2) {
            if (temp_v1 == 0) {
                goto table_0;
            }
            goto done;
        } else {
            if (temp_v1 == 2) {
                goto table_2;
            }
            if (temp_v1 == 3) {
                goto table_3;
            }
            goto done;
        }
    }
    goto table_1;

table_0:
    temp_a1 = (u8 *)0x80170000;
    ASM_KEEP(temp_a1);
    temp_a1 += 0x39E0;
    goto dispatch;
table_1:
    temp_a1 = (u8 *)0x80170000;
    ASM_KEEP(temp_a1);
    temp_a1 += 0x39E8;
    goto dispatch;
table_2:
    temp_a1 = (u8 *)0x80170000;
    ASM_KEEP(temp_a1);
    temp_a1 += 0x39F0;
    goto dispatch;
table_3:
    temp_a1 = (u8 *)0x80170000;
    ASM_KEEP(temp_a1);
    temp_a1 += 0x39F8;

dispatch:
    ASM_MEM_BARRIER();
    *(volatile void **)((u8 *)arg2 + 0x2C) = temp_a1;
    temp_v0 = (((D_80083228[0] + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7);
    temp_v0 = temp_v0 + (u32)temp_a1;
    func_80047784(arg2, *(u8 *)temp_v0, 0);

done:
    func_800A4ACC(arg3);
    M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
}
