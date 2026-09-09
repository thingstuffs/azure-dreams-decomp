#include "common.h"

/* Check whether the entry passes its kind-specific value filter. */
s32 func_800A9ADC(s32 unused, u8 *entry) {
    register s32 result ASM_REG("$2");
    s32 kind;

    kind = entry[1];

    if (kind == 13) {
        u8 value = entry[0];

        result = 1;
        if (value != 4) {
            result = value == 3;
        }
    } else {
        result = 1;
        if (kind == result) {
            result = entry[0] != 8;
        }
    }
    return result;
}
