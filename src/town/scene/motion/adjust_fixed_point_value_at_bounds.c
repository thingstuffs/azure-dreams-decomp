#include "common.h"
#include "m2c_compat.h"
#include "town/scene/motion/offset_queries.h"

s16 check_the_position_second_coordinate_adjusted_stored_offset(void *source_record);                           /* extern */
struct S_8008F534_0; struct S_8008F534_1; void set_the_flag_store_state_clear_state_s_secondary_field(struct S_8008F534_0 *, struct S_8008F534_1 *, s32);             /* extern */
struct S_8008F548_0; struct S_8008F548_1; void set_the_flag_initialize_associated_state(struct S_8008F548_0 *, struct S_8008F548_1 *, s32);             /* extern */

/* Apply upper and lower boundary adjustments to a fixed-point value. */
void adjust_fixed_point_value_at_bounds(s32 context, s32 *value) {
    s32 upper_bound;
    s32 lower_bound;

    upper_bound = check_the_position_second_coordinate_adjusted_stored_offset(value) << 0x10;
    if (value[1] >= upper_bound) {
        set_the_flag_store_state_clear_state_s_secondary_field((struct S_8008F534_0 *)(context), (struct S_8008F534_1 *)(value), upper_bound);
    }
    lower_bound = (query_position_with_second_component_offset(value) << 0x10) - 1;
    if (lower_bound >= value[1]) {
        set_the_flag_initialize_associated_state((struct S_8008F548_0 *)(context), (struct S_8008F548_1 *)(value), lower_bound);
    }
}
