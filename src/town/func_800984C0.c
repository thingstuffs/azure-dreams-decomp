#include "common.h"

extern s16 evaluate_summed_position_minus_y_offset(s32 input_value, s32 value, s32 parameter);
extern s32 D_800D0418;

/* Call evaluate_summed_position_minus_y_offset with the input, D_800D0418, and parameter. */
s16 call_callee_8008_c_610_global_800_d_0418_parameter(s32 input_value, s32 parameter) {
    return evaluate_summed_position_minus_y_offset(input_value, D_800D0418, parameter);
}
