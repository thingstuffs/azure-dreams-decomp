#include "town/scene/flags.h"
#include "shared/entity.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene/motion/offset_queries.h"
#include "town/scene/motion.h"

/* Apply upper and lower boundary adjustments to a fixed-point value. */
void clamp_position_y_to_bounds(struct ColliderView *collider, ObjectPosition *position) {
    s32 upper_bound;
    s32 lower_bound;

    upper_bound = min_sampled_position_minus_y_offset(position) << 0x10;
    if (position->y.v >= upper_bound) {
        stop_at_max_y(collider, position, upper_bound);
    }
    lower_bound = (query_position_with_second_component_offset(position) << 0x10) - 1;
    if (lower_bound >= position->y.v) {
        stop_at_min_y(collider, position, lower_bound);
    }
}
