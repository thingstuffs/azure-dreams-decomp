#include "common.h"

/* Copy the three low halves of the source's 32-bit coordinates. */
void copy_low_halfword_coordinates(u16 *destination, const u16 *source) {
    destination[0] = source[1];
    destination[1] = source[3];
    destination[2] = source[5];
}
