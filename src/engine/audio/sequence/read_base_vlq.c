#include "common.h"
#include "engine/audio/sequence.h"

extern int read_sequence_byte(void *a0);

/* Reads a variable-length integer from the stream, most significant 7-bit group first. */
s32 read_base_128_vlq(void *stream)
{
    s32 byte;
    s32 value;

    byte = read_sequence_byte(stream);
    if (byte == 0) {
        return 0;
    }
    value = byte;
    if (!(value & 0x80)) {
        return value;
    }
    value = value & 0x7F;
    do {
        byte = read_sequence_byte(stream);
        value = (value << 7) + (byte & 0x7F);
    } while (byte & 0x80);
    return value;
}
