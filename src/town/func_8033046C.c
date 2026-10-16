typedef signed int s32;
typedef unsigned int u32;

extern u32 townSquaredDistance3s(s32 point_a, s32 point_b);

/* Test whether the computed value is below the squared threshold. */
u32 townPointsWithinSquaredThreshold(s32 input_1, s32 input_2, s32 threshold)
{
    s32 threshold_value;

    if (threshold_value) {
        threshold_value = threshold;
        return townSquaredDistance3s(input_1, input_2) < (u32)(threshold_value * threshold_value);
    } else {
        threshold_value = threshold;
        return townSquaredDistance3s(input_1, input_2) < (u32)(threshold_value * threshold_value);
    }
}
