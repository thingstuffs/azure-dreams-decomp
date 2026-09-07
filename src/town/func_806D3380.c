#include "common.h"

void func_80016B80(s32 arg0, u8 *arg1) {
    s32 *temp_v0;
    s32 temp_v1;
    u8 *var_a1;

    var_a1 = arg1;
    if (*var_a1 != 0xFF) {
        do {
            temp_v0 = (*var_a1 * 0x1C) + arg0;
            temp_v1 = *temp_v0;
            var_a1 += 1;
            *temp_v0 = temp_v1 | 0x8000;
        } while (*var_a1 != 0xFF);
    }
}
