#include "common.h"

s32 func_8003FC64();                         /* extern */

/* Add 0x20 to a nonzero result from func_8003FC64(0), preserving zero. */
s32 func_800B12F4(void) {
    s32 value;
    s32 adjusted_value;

    value = func_8003FC64(0);
    adjusted_value = 0;
    if (value != 0) {
        adjusted_value = value + 0x20;
    }
    return adjusted_value;
}
