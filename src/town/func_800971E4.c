#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80053DA8();                     /* extern */
extern s32 D_800D0460;

void func_80094944(s32 arg0, s32 arg1) {
    if (((arg0 % arg1) == 0) && (D_800D0460 != 0)) {
        func_80053DA8(0x519);
    }
}
