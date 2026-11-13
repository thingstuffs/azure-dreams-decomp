#include "common.h"
#include "engine/audio/sequence.h"
#include "slus.h"

extern s32 read_sequence_byte(void *a0);

/* Reads four bytes from the stream and packs them into a word. */
u32 read_big_endian_word(void *stream)
{
    s32 first_byte, second_byte, third_byte, fourth_byte;

    first_byte = read_sequence_byte(stream);
    second_byte = read_sequence_byte(stream);
    third_byte = read_sequence_byte(stream);
    fourth_byte = read_sequence_byte(stream);
    return pack_big_endian_word(first_byte & 0xFF, second_byte & 0xFF, third_byte & 0xFF, fourth_byte & 0xFF);
}
