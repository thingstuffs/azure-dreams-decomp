#include "common.h"

/* Write a nibble into packed data at a wrapped index. */
void write_wrapped_packed_nibble(s32 nibble, s32 index, s32 nibble_count, u8 *packed_data)
{
    s32 wrapped_index;
    s32 packed_byte;

    wrapped_index = index % nibble_count;
    nibble &= 0xF;
    packed_data += wrapped_index / 2;

    if (!(wrapped_index & 1)) {
        packed_byte = (*packed_data & 0xF0) | nibble;
    } else {
        packed_byte = (*packed_data & 0xF) | (nibble << 4);
    }

    *packed_data = packed_byte;
}
