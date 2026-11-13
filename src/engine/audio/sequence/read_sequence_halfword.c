#include "common.h"
#include "engine/audio/sequence.h"
#include "slus.h"

extern int read_sequence_byte(void *a0);

/* Combines the low bytes of two successive calls with the same input and returns the low 16 bits. */
int read_sequence_halfword(void *input)
{
    int first_result;
    int second_result;

    first_result = read_sequence_byte(input);
    second_result = read_sequence_byte(input);
    return pack_big_endian_halfword(first_result & 0xFF, second_result & 0xFF) & 0xFFFF;
}
