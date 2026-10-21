#include "common.h"

/* Clears one byte and returns a pointer to the next byte. */
void *clear_byte_and_advance(s8 *byte_ptr) {
    *byte_ptr = 0;
    return byte_ptr + 1;
}
