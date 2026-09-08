#include "common.h"

s32 rand();                                /* extern */

/* Return a random sign of either -1 or 1. */
s32 func_80024EA4(void) {
    s32 sign;

    sign = rand() & 1;
    if (sign == 0) {
        sign = -1;
    }
    return sign;
}
