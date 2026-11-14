#include "common.h"
#include "town.h"
#include "town/scene/motion.h"

/* Pass the same value and context to both processing routines. */
void apply_bound_adjustments(s32 value, s32 context) {
    start_adjustment_at_value_bounds(value, context);
    clamp_position_y_to_bounds(value, context);
}
