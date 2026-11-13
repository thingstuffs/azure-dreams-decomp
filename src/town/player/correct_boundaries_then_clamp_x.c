#include "common.h"
#include "town/player.h"


/* Pass the input to correct_fixed_point_value_at_boundaries, then clamp_x_to_probe_bounds. */
void correct_boundaries_then_clamp_x(ObjectPosition *input_value) {
    correct_fixed_point_value_at_boundaries(input_value);
    clamp_x_to_probe_bounds((input_value));
}
