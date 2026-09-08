#include "common.h"

extern s16 func_8008C570(s32, s32, s32);

/* Return the largest indexed lookup value, with a minimum result of zero. */
s16 func_8008CABC(s32 lookup_a, s32 lookup_b, s32 count) {
    s16 value;
    s16 max_value;
    s32 index;

    max_value = 0;
    index = 0;
    if (count > 0) {
        do {
            value = func_8008C570(lookup_a, lookup_b, index);
            if ((value << 0x10) > (max_value << 0x10)) {
                max_value = value;
            }
            index += 1;
        } while (index < count);
    }
    return max_value;
}
