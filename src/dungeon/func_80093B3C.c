#include "common.h"

/* Writes a byte and returns the next destination address. */
void *func_8009929C(s8 value, s8 *dest) {
    *dest = value;
    return dest + 1;
}
