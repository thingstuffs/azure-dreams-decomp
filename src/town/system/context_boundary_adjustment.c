/* Context boundary adjustment and its file-private helper. */
#include "common.h"
#include "town/scene/motion/offset_queries.h"
static void start_adjustment_at_value_bounds(s32 context, s32 *value);
/* extern */
#include "m2c_compat.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"
/* extern */
/* extern */
/* extern */

/* Applies both sets of fixed-point boundary adjustments to the same value and context. */
void apply_bound_adjustments(s32 value, s32 context) {
    start_adjustment_at_value_bounds(value, context);
    clamp_position_y_to_bounds(value, context);
}

/*
 * Computes upper and lower fixed-point bounds and starts the corresponding boundary adjustment
 * when the value reaches either bound.
 */
static void start_adjustment_at_value_bounds(s32 context, s32 *value) {
    s32 upper_bound;
    s32 lower_bound;

    upper_bound = min_sampled_position_minus_x_offset(value) << 0x10;
    if (*value >= upper_bound) {
        stop_at_max_x(context, value, upper_bound);
    }
    lower_bound = (query_position_with_first_component_offset(value) << 0x10) - 1;
    if (lower_bound >= *value) {
        stop_at_min_x(context, value, lower_bound);
    }
}
