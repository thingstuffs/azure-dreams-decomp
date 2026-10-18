#include "common.h"
#include "m2c_compat.h"

void apply_upper_lower_boundary_adjustments_fixed_point(s32, M2C_UNK);                            /* extern */
M2C_UNK adjust_fixed_point_value_at_bounds();                /* extern */

/* Pass the same value and context to both processing routines. */
void call_the_same_context_both_processing_routines(s32 value, M2C_UNK context) {
    apply_upper_lower_boundary_adjustments_fixed_point(value, context);
    adjust_fixed_point_value_at_bounds(value, context);
}
