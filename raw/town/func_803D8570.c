#include "common.h"
#include "m2c_compat.h"

void func_80019570(s32 arg0, u8 *arg1) {
    s32 *temp_v0;
    u8 *var_a1;

    var_a1 = arg1;
    if (*var_a1 != 0xFF) {
        do {
            temp_v0 = (*var_a1 * 0x1C) + arg0;
            *temp_v0 |= 0x8000;
            var_a1 += 1;
        } while (*var_a1 != 0xFF);
    }
}
