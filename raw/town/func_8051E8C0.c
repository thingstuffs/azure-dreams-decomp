#include "common.h"
#include "m2c_compat.h"

extern s32 D_80019170;
extern s32 D_80019174;

void func_8051E8C0(s32 arg0, s32 arg1) {
    D_80019170 = arg0;
    D_80019174 = arg1;
}
