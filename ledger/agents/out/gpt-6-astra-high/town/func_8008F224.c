#include "common.h"
#include "m2c_compat.h"

s16 func_8008C420();               /* extern */

/* Returns the maximum evaluated value across count entries, starting at -0x7FFF. */
s16 func_8008C984(s32 context, M2C_UNK data, s32 count) {
    s16 value;
    s16 max_value;
    s32 index;

    max_value = -0x7FFF;
    index = 0;
    if (count > 0) {
        do {
            value = func_8008C420(context, data, index);
            if ((value << 0x10) > (max_value << 0x10)) {
                max_value = value;
            }
            index += 1;
        } while (index < count);
    }
    return max_value;
}
