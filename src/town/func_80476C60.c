#include "common.h"

extern void *func_80017BE8(s32, s32);
extern u8 D_800170C8[];
extern u8 D_8001BA8C[];
extern u8 D_8001BA91[];

void *func_80017C60(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 == 1) {
        return D_800170C8;
    }
    if (arg2 == 5) {
        return D_8001BA91;
    }
    if (arg2 == 4) {
        return D_8001BA8C;
    }
    return func_80017BE8(arg0, arg1);
}
