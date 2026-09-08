#include "common.h"

s32 func_800AC7EC(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 value = arg3[7];

    if (value & 0x08000000) {
        if (arg3[5] & 0x40000) {
            arg3[7] = value | 0x40000;
        }
        return 1;
    }
    return 0;
}
