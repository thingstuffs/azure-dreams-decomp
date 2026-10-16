#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80019DFC(M2C_UNK *, M2C_UNK *, s32, s32); /* extern */
extern s32 D_8001B920;
extern M2C_UNK D_8001BA34;
extern M2C_UNK D_8001BA54;
extern M2C_UNK D_8001C354;

void func_80016D28(s32 arg0, s32 arg2) {
    M2C_UNK *var_a0;

    if (D_8001B920 != 0) {
        var_a0 = &D_8001BA54;
    } else {
        var_a0 = &D_8001BA34;
    }
    if (arg2 != 0x2D) {
        D_8001B920 = 1;
    }
    func_80019DFC(var_a0, &D_8001C354, arg0, arg2);
}
