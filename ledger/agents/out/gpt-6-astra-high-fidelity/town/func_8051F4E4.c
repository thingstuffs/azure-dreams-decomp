#include "common.h"

extern s32 func_800162F8(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_8001C9C7[];
extern u8 D_8001D244[];

void *func_80016CE4(s32 arg0, s32 arg1, s32 arg2) {
    if (func_800162F8(arg0, arg1, arg2) != 0) {
        return D_8001D244;
    }
    return D_8001C9C7;
}
