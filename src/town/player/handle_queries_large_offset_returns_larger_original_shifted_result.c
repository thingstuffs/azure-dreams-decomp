#include "common.h"


extern s32 max_adjusted_x_query_at_least_zero();
extern int abs(int);
extern s32 *town_probe_adjustment_samples;
extern s32 town_primary_probe_offset;

/* Queries the input and, for a large offset, returns the larger original or shifted result. */
s16 handle_queries_large_offset_returns_larger_original_shifted_result(s32 *input)
{
    s32 sample[6];
    s32 original_result;
    s32 **map_slot;
    s32 *source;
    s32 shifted_result;
    s32 offset;

    map_slot = &town_probe_adjustment_samples;
    source = input;
    sample[0] = source[0];
    sample[1] = source[1];
    sample[2] = source[2];
    original_result = max_adjusted_x_query_at_least_zero(sample, *map_slot, 6);
    offset = town_primary_probe_offset;
    if (abs(offset) <= 0x140000) {
        return (s16)original_result;
    }

    sample[0] = source[0] - (offset / 2);
    shifted_result = max_adjusted_x_query_at_least_zero(sample, *map_slot, 6);
    if ((s16)original_result < (s16)shifted_result) {
        return (s16)shifted_result;
    }
    return (s16)original_result;
}
