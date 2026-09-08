#include "common.h"

typedef s32 M2C_UNK;

extern s32 func_8008CABC();
extern M2C_UNK *D_800D0414;
extern s32 D_800FE5CC;

/* Queries the input and, for a large offset, returns the larger original or shifted result. */
s16 func_80096440(s32 *input)
{
    s32 sample[6];
    s32 original_result;
    M2C_UNK **map_slot;
    s32 *source;
    s32 shifted_result;
    s32 offset;
    u32 offset_magnitude;
    u32 limit_bias;
    s32 limit;

    map_slot = &D_800D0414;
    source = input;
    sample[0] = source[0];
    sample[1] = source[1];
    sample[2] = source[2];
    original_result = func_8008CABC(sample, *map_slot, 6);
    offset = D_800FE5CC;
    limit = 0x140000;
    limit_bias = (u32)limit;
    offset_magnitude = (u32)offset;
    offset_magnitude += limit_bias;
    offset_magnitude -= limit_bias;
    if (offset < 0) {
        offset_magnitude = (u32)limit - (offset_magnitude + (u32)limit);
    }
    if ((s32)offset_magnitude <= limit) {
        return (s16)original_result;
    }

    sample[0] = source[0] - (offset / 2);
    shifted_result = func_8008CABC(sample, *map_slot, 6, offset);
    if ((s16)original_result < (s16)shifted_result) {
        return (s16)shifted_result;
    }
    return (s16)original_result;
}
