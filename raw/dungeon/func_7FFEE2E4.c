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

extern M2C_UNK D_8008BC58;
extern s8 D_800CFC70[];
extern s32 D_800CFC7C[];

void func_8008BA44(void *arg0) {
    void *temp_v0;
    void *temp_v1;
    s32 temp_v2;

    temp_v0 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_v0, u16 *, 0xA) = (u16) (M2C_FIELD(temp_v0, u16 *, 0xA) - 0x100);
    temp_v1 = M2C_FIELD(arg0, void **, 0);
    if ((s16) M2C_FIELD(temp_v1, u16 *, 0xA) < 0) {
        M2C_FIELD(temp_v1, u16 *, 0xA) = 0U;
        M2C_FIELD(arg0, M2C_UNK **, 0x68) = &D_8008BC58;
        M2C_FIELD(arg0, volatile s16 *, 0x64) = (s16) (s8) D_800CFC70[M2C_FIELD(arg0, s16 *, 0x66)];
        temp_v2 = D_800CFC7C[M2C_FIELD(arg0, s16 *, 0x66)];
        M2C_FIELD(arg0, s16 *, 0x64) = 0x16;
        M2C_FIELD(arg0, s32 *, 0x6C) = temp_v2;
    }
}
