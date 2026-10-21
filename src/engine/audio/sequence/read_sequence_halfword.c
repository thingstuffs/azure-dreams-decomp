#include "common.h"
#include "engine/audio/sequence.h"
#include "slus.h"

extern int read_next_byte_and_finish(int a0);

/* Combines the low bytes of two successive calls with the same input and returns the low 16 bits. */
int read_sequence_halfword(int input)
{
    int first_result;
    int second_result;

    first_result = read_next_byte_and_finish(input);
    second_result = read_next_byte_and_finish(input);
    return pack_big_endian_halfword(first_result & 0xFF, second_result & 0xFF) & 0xFFFF;
}
