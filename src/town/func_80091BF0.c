#include "common.h"
#include "m2c_compat.h"

s32 check_the_position_second_coordinate_adjusted_stored_offset();                           /* extern */
s32 query_position_with_second_component_offset();                           /* extern */
void set_the_flag_store_state_clear_state_s_secondary_field();             /* extern */
void set_the_flag_initialize_associated_state();             /* extern */

/* Apply upper and lower boundary adjustments to a fixed-point value. */
void adjust_fixed_point_value_at_bounds(s32 context, s32 *value) {
    s32 upper_bound;
    s32 lower_bound;

    upper_bound = check_the_position_second_coordinate_adjusted_stored_offset(value) << 0x10;
    if (value[1] >= upper_bound) {
        set_the_flag_store_state_clear_state_s_secondary_field(context, value, upper_bound);
    }
    lower_bound = (query_position_with_second_component_offset(value) << 0x10) - 1;
    if (lower_bound >= value[1]) {
        set_the_flag_initialize_associated_state(context, value, lower_bound);
    }
}
