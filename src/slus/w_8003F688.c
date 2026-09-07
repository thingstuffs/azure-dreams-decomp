#include "common.h"

/* Convert a packed (4-bit-per-digit) hex-nibble encoded decimal number into
 * a normal base-10 integer: for each of the 8 nibbles of arg0, treat it as a
 * decimal digit and accumulate digit * 10^i. */
s32 bcdToInt(s32 arg0) {
    s32 sum;
    s32 pow10;
    s32 i;
    s32 shift;
    s32 product;

    sum = 0;
    pow10 = 1;
    i = sum;
    do {
        shift = i * 4;
        product = pow10 * (arg0 & (0xF << shift));
        pow10 *= 10;
        i += 1;
        sum += product >> shift;
    } while (i < 8);
    return sum;
}
