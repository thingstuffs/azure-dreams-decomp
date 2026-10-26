#include "dungeon/item/message.h"
#include "common.h"

/* Writes a byte and returns the next destination address. */
u8 *write_text_byte_and_advance(s8 value, u8 *dest) {
    *dest = value;
    return dest + 1;
}
