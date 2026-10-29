#include "common.h"
#include "town/player.h"

extern s16 evaluate_summed_vector_minus_base(s32 input_value, s32 value, s32 parameter);
extern s32 town_primary_probe_samples;

/* Call evaluate_summed_vector_minus_base with the input, D_800D0410, and parameter. */
s16 call_callee_8008_c_4_c_8_global_800_d_0410_parameter(s32 input_value, s32 parameter) {
    return evaluate_summed_vector_minus_base(input_value, town_primary_probe_samples, parameter);
}
