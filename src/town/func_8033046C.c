typedef signed int s32;
typedef unsigned int u32;

extern u32 func_8001AB20(s32 point_a, s32 point_b);

/* Test whether the computed value is below the squared threshold. */
u32 func_8001AC6C(s32 input_1, s32 input_2, s32 threshold)
{
    s32 threshold_value;

    if (threshold_value) {
        threshold_value = threshold;
        return func_8001AB20(input_1, input_2) < (u32)(threshold_value * threshold_value);
    } else {
        threshold_value = threshold;
        return func_8001AB20(input_1, input_2) < (u32)(threshold_value * threshold_value);
    }
}
