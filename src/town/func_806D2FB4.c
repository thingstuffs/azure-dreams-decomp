#include "common.h"

extern void clear_indexed_flag_unless_identifier(s32);

/* Pass each signed 16-bit value in the input pairs to clear_indexed_flag_unless_identifier in order. */
void check_initial_query_zero_secondary(s16 *value_pairs, s32 pair_count)
{
    s32 frame_pad[2];
    s32 pair_index;
    s16 *current_pair;

    pair_index = 0;
    if (pair_count > 0) {
        current_pair = value_pairs;
        do {
            clear_indexed_flag_unless_identifier(current_pair[0]);
            pair_index++;
            clear_indexed_flag_unless_identifier(current_pair[1]);
            current_pair += 2;
        } while (pair_index < pair_count);
    }
}
