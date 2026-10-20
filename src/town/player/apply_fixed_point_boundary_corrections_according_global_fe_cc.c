#include "common.h"
#include "m2c_compat.h"

s32 get_lower_probe_result_sampling_x_offset_displacement_exceeds_limit(s32 *);                           /* extern */
s32 handle_queries_large_offset_returns_larger_original_shifted_result();                           /* extern */
struct EntityRec; void set_global_800_cfceb_initialize_call_callee_800954_c_4(struct EntityRec *, s32);                  /* extern */
struct EntityRec; void set_global_800_cfcea_initialize_call_callee_800954_c_4(struct EntityRec *, s32);                  /* extern */
extern s32 D_800FE5CC;

/* Applies fixed-point boundary corrections according to D_800FE5CC. */
void apply_fixed_point_boundary_corrections_according_global_800_fe_5_cc(s32 *value) {
    s32 upper_bound;
    s32 neutral_upper_bound;
    s32 lower_bound;

    if (D_800FE5CC > 0) {
        upper_bound = get_lower_probe_result_sampling_x_offset_displacement_exceeds_limit(value) << 0x10;
        if (*value >= upper_bound) {
            set_global_800_cfceb_initialize_call_callee_800954_c_4((struct EntityRec *)(value), upper_bound);
            return;
        }
    } else {
        if (D_800FE5CC >= 0) {
            neutral_upper_bound = get_lower_probe_result_sampling_x_offset_displacement_exceeds_limit(value) << 0x10;
            if (*value >= neutral_upper_bound) {
                set_global_800_cfceb_initialize_call_callee_800954_c_4((struct EntityRec *)(value), neutral_upper_bound);
            }
        }
        lower_bound = (handle_queries_large_offset_returns_larger_original_shifted_result(value) << 0x10) - 1;
        if (lower_bound >= *value) {
            set_global_800_cfcea_initialize_call_callee_800954_c_4((struct EntityRec *)(value), lower_bound);
        }
    }
}
