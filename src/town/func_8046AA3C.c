#include "common.h"

extern void func_80019730(s32, s32);
extern u8 D_8001601C[];
extern u8 D_80017774[];
extern u8 D_80022E7E[];

void *func_8001BA3C(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 == 1) {
        func_80019730(arg0, arg1);
        return D_80022E7E;
    } else if (arg2 == 4) {
        return D_8001601C;
    } else {
        return D_80017774;
    }
}
