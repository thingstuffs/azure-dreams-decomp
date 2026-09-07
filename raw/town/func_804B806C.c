#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

s32 func_8001894C();
void func_800168B8() __attribute__((noreturn));
s32 func_80018044();
extern M2C_UNK D_80018B18;
extern M2C_UNK D_80018E38;
extern u8 D_8001C59A[16];

void func_8001686C(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    if (func_8001894C(0x510) != 0) {
        u8 *hidden = D_8001C59A;
        ASM_TAILSLOT_PIN(hidden);
        func_800168B8();
        return;
    }
    ASM_SCHED_BARRIER();
    func_80018044(&D_80018B18, &D_80018E38, arg0, arg2);
}
