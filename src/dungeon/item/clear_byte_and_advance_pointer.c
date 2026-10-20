#include "common.h"

/* Clears one byte and returns a pointer to the next byte. */
void *func_80099290(s8 *byte_ptr) {
    *byte_ptr = 0;
    return byte_ptr + 1;
}
