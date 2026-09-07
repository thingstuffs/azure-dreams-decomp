#include "common.h"

extern u8 D_800170C8[];
extern u8 D_8001BAB6[];

void *func_800177B0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 1) {
        return D_8001BAB6;
    }
    return D_800170C8;
}
