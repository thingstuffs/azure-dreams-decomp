#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "town/player/position.h"

s32 query_lower_bound_with_x_offset(ObjectPosition *);                           /* extern */
void set_global_800_cfced_initialize_call_callee_800954_dc(ObjectPosition *, s32);                  /* extern */
void set_global_800_cfcec_initialize_call_callee_800954_dc(void *, s32);                  /* extern */
extern s32 town_secondary_probe_offset;

/* Applies fixed-point boundary corrections according to D_800FE5D0. */
void correct_fixed_point_value_at_boundaries(ObjectPosition *position) {
    s32 upper_bound;
    s32 neutral_upper_bound;
    s32 lower_bound;

    if (town_secondary_probe_offset > 0) {
        upper_bound = query_lower_bound_with_x_offset(position) << 0x10;
        if (position->y.v >= upper_bound) {
            set_global_800_cfced_initialize_call_callee_800954_dc((position), upper_bound);
            return;
        }
    } else {
        if (town_secondary_probe_offset >= 0) {
            neutral_upper_bound = query_lower_bound_with_x_offset(position) << 0x10;
            if (position->y.v >= neutral_upper_bound) {
                set_global_800_cfced_initialize_call_callee_800954_dc((position), neutral_upper_bound);
            }
        }
        lower_bound = (query_larger_position_result(position) << 0x10) - 1;
        if (lower_bound >= position->y.v) {
            set_global_800_cfcec_initialize_call_callee_800954_dc((void *)(position), lower_bound);
        }
    }
}
