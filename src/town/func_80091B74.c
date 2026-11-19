#include "common.h"
#include "m2c_compat.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"
#include "town.h"

#include "town/scene/motion/offset_queries.h"

/*
 * Computes the upper and lower fixed-point bounds and starts the corresponding boundary adjustment
 * when the value reaches either bound.
 */
void start_adjustment_at_value_bounds(struct ColliderView *collider, ObjectPosition *position) {
    s32 upper_bound;
    s32 lower_bound;

    upper_bound = min_sampled_position_minus_x_offset(position) << 0x10;
    if (position->x.v >= upper_bound) {
        stop_at_max_x(collider, position, upper_bound);
    }
    lower_bound = (query_position_with_first_component_offset(position) << 0x10) - 1;
    if (lower_bound >= position->x.v) {
        stop_at_min_x(collider, position, lower_bound);
    }
}
