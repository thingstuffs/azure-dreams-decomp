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

extern s32 D_80126A10[];
extern s32 D_80126A60;
extern s32 D_80126AD0;

void func_801237A4(void *arg0) {
    D_80126A60 = D_80126A10[M2C_FIELD(arg0, u8 *, 0x16)];
    D_80126AD0 = D_80126A10[M2C_FIELD(arg0, u8 *, 0x16) ^ 1];
}
