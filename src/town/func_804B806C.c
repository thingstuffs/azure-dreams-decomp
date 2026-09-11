#include "common.h"
#include "m2c_compat.h"

s32 func_8001894C();
void func_800168B8() __attribute__((noreturn));
s32 func_80018044();
extern M2C_UNK D_80018B18;
extern M2C_UNK D_80018E38;
extern u8 D_8001C59A[16];

void *func_8001686C(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    if (func_8001894C(0x510) == 0) {
        return (void *)func_80018044(&D_80018B18, &D_80018E38, arg0, arg2);
    }
    return D_8001C59A;
}
