#include "common.h"

/* Expands six-bit values into runs of one to four bytes until the 1, 1 terminator. */
void texture_handle_expands_six_bit_values_runs_one_four_bytes_until_n_1(u8 *source, u8 *output)
{
    u32 encoded_byte;
    s32 run_limit;
    s32 remaining;

    while ((encoded_byte = *source) != 1 || source[1] != 1) {
        run_limit = encoded_byte >> 6;
        encoded_byte &= 0x3F;
        for (remaining = run_limit; remaining != -1; remaining--) {
            *output++ = encoded_byte;
        }
        source++;
    }
}
