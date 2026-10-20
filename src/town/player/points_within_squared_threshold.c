typedef signed int s32;
typedef unsigned int u32;

extern u32 squared_distance_3s(s32 point_a, s32 point_b);

/* Test whether the computed value is below the squared threshold. */
u32 points_within_squared_threshold(s32 input_1, s32 input_2, s32 threshold)
{
    s32 threshold_value;

    if (threshold_value) {
        threshold_value = threshold;
        return squared_distance_3s(input_1, input_2) < (u32)(threshold_value * threshold_value);
    } else {
        threshold_value = threshold;
        return squared_distance_3s(input_1, input_2) < (u32)(threshold_value * threshold_value);
    }
}
