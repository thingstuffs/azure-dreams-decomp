#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

__asm__(".set D_80028418, 0x80028418");
__asm__(".set D_80028430, 0x80028430");
extern M2C_UNK D_80028418;
extern M2C_UNK D_80028430;

void func_80026C94(void *arg0) {
    register void *temp_a2 ASM_REG("$6");
    register void *temp_a2_2 ASM_REG("$6");

    temp_a2 = M2C_FIELD(arg0, void **, 0x60);
    M2C_FIELD(M2C_FIELD(temp_a2, void **, 4), s16 *, 8) = 0x40;
    M2C_FIELD(M2C_FIELD(temp_a2, void **, 4), s16 *, 0xA) = 0x20;
    M2C_FIELD(temp_a2, M2C_UNK **, 0) = &D_80028418;
    temp_a2_2 = M2C_FIELD(arg0, void **, 0x64);
    M2C_FIELD(M2C_FIELD(temp_a2_2, void **, 4), s16 *, 8) = 0xC0;
    M2C_FIELD(M2C_FIELD(temp_a2_2, void **, 4), s16 *, 0xA) = 0x20;
    M2C_FIELD(temp_a2_2, M2C_UNK **, 0) = &D_80028430;
}
