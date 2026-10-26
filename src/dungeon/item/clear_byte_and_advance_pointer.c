#include "dungeon/item/message.h"

/* Clears one byte and returns a pointer to the next byte. */
u8 *clear_byte_and_advance(u8 *byte_ptr) {
    *byte_ptr = 0;
    return byte_ptr + 1;
}
