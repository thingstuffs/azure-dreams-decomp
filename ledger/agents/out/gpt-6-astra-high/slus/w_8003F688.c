#include "common.h"

/* Convert eight packed BCD digits to an integer. */
s32 bcdToInt(s32 packed_bcd) {
    s32 sum;
    s32 place_value;
    s32 digit_index;
    s32 shift;
    s32 product;

    sum = 0;
    place_value = 1;
    digit_index = sum;
    do {
        shift = digit_index * 4;
        product = place_value * (packed_bcd & (0xF << shift));
        place_value *= 10;
        digit_index += 1;
        sum += product >> shift;
    } while (digit_index < 8);
    return sum;
}
