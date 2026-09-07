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

M2C_UNK func_800181C8();
M2C_UNK func_80018B58();
s32 func_80018C50();
extern M2C_UNK D_80018EF4;
extern M2C_UNK D_80018F0C;
extern M2C_UNK D_8001925C;

void func_80016800(s32 arg0, s32 unused, M2C_UNK arg2) {
    register void *arg ASM_REG("$4");

    func_80018B58(0xFE2);
    if (func_80018C50(0xFB1) == 0) {
        arg = &D_80018EF4;
    } else {
        arg = &D_80018F0C;
    }
    ASM_KEEP(arg);
    func_800181C8(arg, &D_8001925C, arg0, arg2);
}
