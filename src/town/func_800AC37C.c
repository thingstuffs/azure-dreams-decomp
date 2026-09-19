#include "common.h"

/* Check whether the entry passes its kind-specific value filter. */
s32 func_800A9ADC(s32 unused, u8 *entry) {
    s32 k = entry[1];

    if (k == 13) {
        if (entry[0] == 4) {
            return 1;
        }
        if (entry[0] == 3) {
            return 1;
        }
        return 0;
    }
    if (k == 1) {
        return entry[0] != 8;
    }
    return 1;
}
