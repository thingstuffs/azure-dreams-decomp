#include "common.h"
void apply_upper_lower_boundary_adjustments_fixed_point(s32 context, s32 *value);                            /* extern */
void adjust_fixed_point_value_at_bounds(s32 context, s32 *value);                /* extern */

/* Pass the same value and context to both processing routines. */
void call_the_same_context_both_processing_routines(s32 value, s32 context) {
    apply_upper_lower_boundary_adjustments_fixed_point(value, context);
    adjust_fixed_point_value_at_bounds(value, context);
}
