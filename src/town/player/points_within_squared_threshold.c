#include "town/player/coordinates.h"
typedef signed int s32;
typedef unsigned int u32;


/* Test whether the computed value is below the squared threshold. */
u32 points_within_squared_threshold(struct GteShortVector *input_1, struct GteShortVector *input_2, s32 threshold)
{
    s32 threshold_value;

    threshold_value = threshold;
    return squared_distance_3s(input_1, input_2) < (u32)(threshold_value * threshold_value);
}
