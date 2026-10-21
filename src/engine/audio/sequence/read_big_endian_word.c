#include "common.h"
#include "engine/audio/sequence.h"
#include "slus.h"

extern s32 read_next_byte_and_finish(s32 a0);

/* Reads four bytes from the stream and packs them into a word. */
u32 read_big_endian_word(s32 stream)
{
    s32 first_byte, second_byte, third_byte, fourth_byte;

    first_byte = read_next_byte_and_finish(stream);
    second_byte = read_next_byte_and_finish(stream);
    third_byte = read_next_byte_and_finish(stream);
    fourth_byte = read_next_byte_and_finish(stream);
    return pack_big_endian_word(first_byte & 0xFF, second_byte & 0xFF, third_byte & 0xFF, fourth_byte & 0xFF);
}
