#include "common.h"

/* Writes a byte and returns the next destination address. */
void *write_text_byte_and_advance(s8 value, s8 *dest) {
    *dest = value;
    return dest + 1;
}
