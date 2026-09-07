#include "common.h"

typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;

extern s8 D_80082668[9];
extern s32 D_80097D2C[3];

void func_80098834(void *arg0, void *arg1) {
    u16 temp_v0;
    u16 temp_v1;

    *(s32 *)((s8 *)arg0 + 0) = (s32)&D_80097D2C[0];
    *(u16 *)((s8 *)arg0 + 0x30) = *(u16 *)((s8 *)arg1 + 2);
    temp_v0 = *(u16 *)((s8 *)arg0 + 0x10);
    temp_v1 = *(u16 *)((s8 *)arg1 + 6);
    *(u16 *)((s8 *)arg0 + 0x0e) = temp_v0;
    *(u16 *)((s8 *)arg0 + 0x32) = temp_v1;
    D_80082668[0] = 0;
}
