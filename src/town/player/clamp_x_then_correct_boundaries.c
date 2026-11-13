#include "common.h"
#include "town/player.h"

/* Pass the input to clamp_x_to_probe_bounds, then correct_fixed_point_value_at_boundaries. */
void clamp_x_then_correct_boundaries(ObjectPosition *input_value) {
    clamp_x_to_probe_bounds(input_value);
    correct_fixed_point_value_at_boundaries(input_value);
}
