#include "common.h"



extern s32 dungeonGetMaximumSampledOffsetValue();
extern int abs(int);
extern s32 *D_800D041C;
extern s32 D_800FE5D0;

/* Queries the input and, for a large offset, returns the larger original or shifted result. */
s16 func_800965F0(s32 *input)
{
    s32 sample[6];
    s32 original_result;
    s32 **map_slot;
    s32 *source;
    s32 shifted_result;
    s32 offset;

    map_slot = &D_800D041C;
    source = input;
    sample[0] = source[0];
    sample[1] = source[1];
    sample[2] = source[2];
    original_result = dungeonGetMaximumSampledOffsetValue(sample, *map_slot, 6);
    offset = D_800FE5D0;
    if (abs(offset) <= 0x140000) {
        return (s16)original_result;
    }

    sample[1] = source[1] - (offset / 2);
    shifted_result = dungeonGetMaximumSampledOffsetValue(sample, *map_slot, 6);
    if ((s16)original_result < (s16)shifted_result) {
        return (s16)shifted_result;
    }
    return (s16)original_result;
}
