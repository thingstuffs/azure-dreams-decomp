#include "dungeon/level/generate.h"

s32 is_value_within_inclusive_bounds(s16 value, s32 lower_bound, s16 upper_bound)
{
    s32 in_range;
    s32 scaled_lower_bound;
    in_range = 0;
    scaled_lower_bound = lower_bound << 0x10;
    if ((value << 0x10) >= scaled_lower_bound) {
        in_range = upper_bound >= value;
    }
    return in_range;
}
