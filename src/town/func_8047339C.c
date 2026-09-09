typedef signed int s32;
typedef unsigned int u32;

extern u32 func_8001A250(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* Tests whether the computed value is below the squared threshold. */
u32 func_8047339C(s32 input_a, s32 input_b, s32 threshold, s32 input_d)
{
    s32 threshold_copy;

    if (threshold_copy) {
        threshold_copy = threshold;
        return func_8001A250(input_a, input_b, threshold, input_d) < (u32)(threshold_copy * threshold_copy);
    } else {
        threshold_copy = threshold;
        return func_8001A250(input_a, input_b, threshold, input_d) < (u32)(threshold_copy * threshold_copy);
    }
}
