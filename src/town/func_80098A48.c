#include "common.h"

void apply_fixed_point_boundary_corrections_according_global_800_fe_5_cc(s32);                            /* extern */
void correct_fixed_point_value_at_boundaries(s32 *value);

/* Pass the input to apply_fixed_point_boundary_corrections_according_global_800_fe_5_cc, then correct_fixed_point_value_at_boundaries. */
void call_the_callee_80096208_callee_800962_b_8(s32 input_value) {
    apply_fixed_point_boundary_corrections_according_global_800_fe_5_cc(input_value);
    correct_fixed_point_value_at_boundaries(input_value);
}
