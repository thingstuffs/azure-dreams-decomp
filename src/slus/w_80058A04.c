#include "common.h"

extern int read_next_byte_and_finish(int a0);

/* Reads a variable-length integer from the stream, most significant 7-bit group first. */
s32 read_base_128_vlq(s32 stream)
{
    s32 byte;
    s32 value;

    byte = read_next_byte_and_finish(stream);
    if (byte == 0) {
        return 0;
    }
    value = byte;
    if (!(value & 0x80)) {
        return value;
    }
    value = value & 0x7F;
    do {
        byte = read_next_byte_and_finish(stream);
        value = (value << 7) + (byte & 0x7F);
    } while (byte & 0x80);
    return value;
}
