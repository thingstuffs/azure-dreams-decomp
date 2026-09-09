#include "common.h"

s32 func_800A9ADC(s32 arg0, u8 *arg1) {
    register s32 result ASM_REG("$2");
    s32 kind;

    kind = arg1[1];

    if (kind == 13) {
        u8 value = arg1[0];

        result = 1;
        if (value != 4) {
            result = value == 3;
        }
    } else {
        result = 1;
        if (kind == result) {
            result = arg1[0] != 8;
        }
    }
    return result;
}
