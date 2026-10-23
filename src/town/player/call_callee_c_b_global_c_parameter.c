#include "common.h"

extern s16 adjust_summed_vector_by_entry_component(s32 input_value, s32 value, s32 parameter);
extern s32 town_position_entry_samples;

/* Call adjust_summed_vector_by_entry_component with the input, D_800D041C, and parameter. */
s16 call_callee_8008_c_6_b_8_global_800_d_041_c_parameter(s32 input_value, s32 parameter) {
    return adjust_summed_vector_by_entry_component(input_value, town_position_entry_samples, parameter);
}
