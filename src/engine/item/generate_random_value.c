#include "common.h"
#include "engine/item.h"

extern s32 generate_random_value(void);

/* Shuffle a byte array in place using generate_random_value() for random swap indices. */
void shuffle_byte_array(u8 *bytes, s32 length) {
    s32 index;
    s32 swap_index;
    u8 saved_byte;
    for (index = length - 1; index > 0; index--) {
        swap_index = (generate_random_value() & 0xFFFF) / ((0x7FFF / (index + 1)) + 1);
        saved_byte = bytes[index];
        bytes[index] = bytes[swap_index];
        bytes[swap_index] = saved_byte;
    }
}
