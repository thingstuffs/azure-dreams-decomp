#include "common.h"
#include "m2c_compat.h"

s16 func_8008C4C8();               /* extern */

/* Returns the minimum indexed value, or 0x7FFF if the count is nonpositive. */
s16 func_8008CA20(s32 context, M2C_UNK data, s32 count) {
    s16 value;
    s16 minimum;
    s32 index;

    minimum = 0x7FFF;
    index = 0;
    if (count > 0) {
        do {
            value = func_8008C4C8(context, data, index);
            if ((value << 0x10) < (minimum << 0x10)) {
                minimum = value;
            }
            index += 1;
        } while (index < count);
    }
    return minimum;
}
