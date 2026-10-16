#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800170C8;
extern M2C_UNK D_8001BAB6;

M2C_UNK *func_800177B0(s32 arg2) {
    if (arg2 == 1) {
        return &D_800170C8;
    }
    return &D_8001BAB6;
}
