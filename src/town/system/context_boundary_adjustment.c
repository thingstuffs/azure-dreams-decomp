/* Context boundary adjustment and its file-private helper. */
#include "common.h"
static void apply_upper_lower_boundary_adjustments_fixed_point(s32 context, s32 *value);
/* extern */
void adjust_fixed_point_value_at_bounds(s32 context, s32 *value);
#include "m2c_compat.h"
s32 handle_evaluate_position_after_subtracting_stored_offset_first_component();
/* extern */
s32 query_position_with_first_component_offset();
/* extern */
void set_the_control_flag_initializes_cleared_trailing_field();
/* extern */
void set_the_flag_initializes_state();

/* Applies both sets of fixed-point boundary adjustments to the same value and context. */
void call_the_same_context_both_processing_routines(s32 value, s32 context) {
    apply_upper_lower_boundary_adjustments_fixed_point(value, context);
    adjust_fixed_point_value_at_bounds(value, context);
}

/*
 * Computes upper and lower fixed-point bounds and starts the corresponding boundary adjustment
 * when the value reaches either bound.
 */
static void apply_upper_lower_boundary_adjustments_fixed_point(s32 context, s32 *value) {
    s32 upper_bound;
    s32 lower_bound;

    upper_bound = handle_evaluate_position_after_subtracting_stored_offset_first_component(value) << 0x10;
    if (*value >= upper_bound) {
        set_the_control_flag_initializes_cleared_trailing_field(context, value, upper_bound);
    }
    lower_bound = (query_position_with_first_component_offset(value) << 0x10) - 1;
    if (lower_bound >= *value) {
        set_the_flag_initializes_state(context, value, lower_bound);
    }
}
