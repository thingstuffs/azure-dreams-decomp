#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK D_8001DCD4;
extern M2C_UNK D_8001DF1B;

M2C_UNK *func_800162A4(s32 arg0, s32 arg1, s32 arg2) {
#ifndef NON_MATCHING
    if (arg2 == 1) {
        return &D_8001DF1B;
#else
    if (arg2 != 1) {
        (void)D_8001DCD4;
#endif
    }
#ifndef NON_MATCHING
    return &D_8001DCD4;
#else
    return &D_8001DF1B;
#endif
}
