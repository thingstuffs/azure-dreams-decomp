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
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

extern struct S_8003E2D8 D_80083160;
extern u8 D_80089660[];
extern void *memcpy(void *dst, const void *src, u32 n);

void func_800BDC98(s16 arg0, s16 arg1, s16 arg2, s32 arg3) {
    u16 sp[8];
    s32 var_t1;
    register s32 arg3_hold ASM_REG("$8");
    register s32 temp_t5;
    s32 var_t7;
    s32 var_a2;
    s32 var_a3;
    register s32 temp_v1 ASM_REG("$3");
    register s32 zero_test ASM_REG("$2");
    register s32 arg1_shift ASM_REG("$5");
    register s32 outer_end ASM_REG("$12");
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 mode_offset;
    s8 *base;
    s8 *row_src;
    register s8 *temp_t2 ASM_REG("$10");
    register s8 *dst ASM_REG("$11");

    arg3_hold = arg3;
    var_t1 = arg3_hold;
    M2C_MEMCPY_UNALIGNED(sp, D_80089660, 0x10);
    base = (s8 *)&D_80083160;
    temp_t2 = base + 0x1DC;
    dst = M2C_FIELD(base, s8 **, 0x1DC);
    var_t7 = 1;
    if ((arg2 == 2) || (var_t1 = 3, zero_test = arg3_hold << 0x10, (zero_test == 0))) {
        var_a3 = arg0;
        temp_v1 = var_a3;
        temp_v1 += 2;
        if (var_a3 < temp_v1) {
            arg1_shift = arg1 << 0x10;
            mode_offset = ((s32)(var_t1 << 0x10) >> 0xE);
            row_src = (s8 *)((long)mode_offset + (long)sp);
            temp_t5 = var_a3;
            ASM_KEEP_NV(temp_t5);
            outer_end = temp_v1;
            while (var_a3 < outer_end) {
                var_a2 = arg1_shift >> 0x10;
                temp_v1_2 = var_a2 + var_t7;
                if (var_a2 < temp_v1_2) {
                    s8 *pixel_src;
                    s32 inner_end;
                    pixel_src = (s8 *)((long)((var_a3 - temp_t5) * 2) + (long)row_src);
                    inner_end = temp_v1_2;
                    do {
                        temp_v1_3 = var_a2 & M2C_FIELD(temp_t2, s16 *, 0x1A);
                        var_a2 += 1;
                        *(u16 *)((long)((s32) (((M2C_FIELD(temp_t2, u16 *, 0x18) & var_a3) + (temp_v1_3 << M2C_FIELD(temp_t2, s16 *, 0x14))) << 0x10) >> 0xF) + (long)dst) = *(u16 *)pixel_src;
                    } while (var_a2 < inner_end);
                }
                var_a3 += 1;
            }
        }
    }
}
