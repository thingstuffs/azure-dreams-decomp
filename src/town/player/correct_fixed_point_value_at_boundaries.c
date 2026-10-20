#include "common.h"
#include "m2c_compat.h"

s32 query_lower_bound_with_x_offset(s32 *);                           /* extern */
s32 query_larger_position_result();                           /* extern */
struct S_80096728_0; void set_global_800_cfced_initialize_call_callee_800954_dc(struct S_80096728_0 *, s32);                  /* extern */
struct S_80096758_0; void set_global_800_cfcec_initialize_call_callee_800954_dc(struct S_80096758_0 *, s32);                  /* extern */
extern s32 D_800FE5D0;

/* Applies fixed-point boundary corrections according to D_800FE5D0. */
void correct_fixed_point_value_at_boundaries(s32 *value) {
    s32 upper_bound;
    s32 neutral_upper_bound;
    s32 lower_bound;

    if (D_800FE5D0 > 0) {
        upper_bound = query_lower_bound_with_x_offset(value) << 0x10;
        if (value[1] >= upper_bound) {
            set_global_800_cfced_initialize_call_callee_800954_dc((struct S_80096728_0 *)(value), upper_bound);
            return;
        }
    } else {
        if (D_800FE5D0 >= 0) {
            neutral_upper_bound = query_lower_bound_with_x_offset(value) << 0x10;
            if (value[1] >= neutral_upper_bound) {
                set_global_800_cfced_initialize_call_callee_800954_dc((struct S_80096728_0 *)(value), neutral_upper_bound);
            }
        }
        lower_bound = (query_larger_position_result(value) << 0x10) - 1;
        if (lower_bound >= value[1]) {
            set_global_800_cfcec_initialize_call_callee_800954_dc((struct S_80096758_0 *)(value), lower_bound);
        }
    }
}
