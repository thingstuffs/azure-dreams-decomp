#include "common.h"

extern u32 *D_801131EC[3];

/* Look up a value by three packed key fields in the zero-value-terminated table. */
s32 func_8008AF2C(s32 flag_bit, s32 high_key, s32 low_key) {
    volatile u32 *flags;
    volatile u32 *value;
    u32 bits;
    u32 high_mask;
    u32 low_mask;

    flags = D_801131EC[0];
    if (flags[1] != 0) {
        high_mask = 0x3F000000;
        low_mask = 0x007F0000;
        value = flags + 1;
        do {
            bits = *flags;
            if (flag_bit == ((bits >> 23) & 1) &&
                high_key == ((bits & high_mask) >> 24) &&
                low_key == ((bits & low_mask) >> 16)) {
                return (*value);
            }

            value += 2;
            flags += 2;
        } while (*value != 0);
    }

    return 0;
}
