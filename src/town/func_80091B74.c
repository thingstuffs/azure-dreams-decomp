#include "common.h"
#include "m2c_compat.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"

s32 query_position_with_first_component_offset();                           /* extern */

/*
 * Computes the upper and lower fixed-point bounds and starts the corresponding boundary adjustment
 * when the value reaches either bound.
 */
void apply_upper_lower_boundary_adjustments_fixed_point(s32 context, s32 *value) {
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
