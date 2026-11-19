#include "common.h"
#include "town.h"
#include "town/scene/motion.h"

/* Pass the same value and context to both processing routines. */
void apply_bound_adjustments(struct ColliderView *collider, ObjectPosition *position) {
    start_adjustment_at_value_bounds(collider, position);
    clamp_position_y_to_bounds(collider, position);
}
