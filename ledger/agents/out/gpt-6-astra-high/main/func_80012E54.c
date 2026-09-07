#include "common.h"

s32 func_80033B2C();                             /* extern */
extern s16 D_80028010[8];

/* Return a bitmask of the eight entries for which func_80033B2C is nonzero. */
s32 func_80025E54(void) {
    s16 *entry;
    s32 index;
    s32 result_mask;
    s32 bit;

    result_mask = 0;
    index = 0;
    bit = 1;
    entry = D_80028010;
    do {
        if (func_80033B2C(*entry) != 0) {
            result_mask += bit << index;
        }
        index += 1;
        entry += 1;
    } while (index < 8);
    return result_mask;
}
