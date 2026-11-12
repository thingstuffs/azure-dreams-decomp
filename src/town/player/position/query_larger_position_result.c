#include "common.h"
#include "shared/entity.h"
#include "sdk/libc.h"
#include "town/player/position.h"
#include "dungeon/system.h"
#include "town/data.h"

#include "town/player/probe_offset_data.h"

/* Queries the input and, for a large offset, returns the larger original or shifted result. */
s16 query_larger_position_result(ObjectPosition *input)
{
    s32 sample[6];
    s32 original_result;
    s32 **map_slot;
    ObjectPosition *source;
    s32 shifted_result;
    s32 offset;

    map_slot = &town_position_entry_samples;
    source = input;
    sample[0] = source->x.v;
    sample[1] = source->y.v;
    sample[2] = source->z.v;
    original_result = get_maximum_sampled_offset_value(sample, *map_slot, 6);
    offset = town_secondary_probe_offset;
    if (abs(offset) <= 0x140000) {
        return (s16)original_result;
    }

    sample[1] = source->y.v - (offset / 2);
    shifted_result = get_maximum_sampled_offset_value(sample, *map_slot, 6);
    if ((s16)original_result < (s16)shifted_result) {
        return (s16)shifted_result;
    }
    return (s16)original_result;
}
