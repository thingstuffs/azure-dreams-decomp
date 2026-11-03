#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"

s32 get_lower_probe_result_sampling_x_offset_displacement_exceeds_limit(ObjectPosition *);                           /* extern */
s16 handle_queries_large_offset_returns_larger_original_shifted_result(ObjectPosition *input);                           /* extern */
struct EntityRec; void set_global_800_cfceb_initialize_call_callee_800954_c_4(ObjectPosition *, s32);                  /* extern */
struct EntityRec; void set_global_800_cfcea_initialize_call_callee_800954_c_4(struct EntityRec *, s32);                  /* extern */
extern s32 town_primary_probe_offset;

/* Applies fixed-point boundary corrections according to D_800FE5CC. */
void apply_fixed_point_boundary_corrections_according_global_800_fe_5_cc(ObjectPosition *position) {
    s32 upper_bound;
    s32 neutral_upper_bound;
    s32 lower_bound;

    if (town_primary_probe_offset > 0) {
        upper_bound = get_lower_probe_result_sampling_x_offset_displacement_exceeds_limit(position) << 0x10;
        if (position->x.v >= upper_bound) {
            set_global_800_cfceb_initialize_call_callee_800954_c_4((position), upper_bound);
            return;
        }
    } else {
        if (town_primary_probe_offset >= 0) {
            neutral_upper_bound = get_lower_probe_result_sampling_x_offset_displacement_exceeds_limit(position) << 0x10;
            if (position->x.v >= neutral_upper_bound) {
                set_global_800_cfceb_initialize_call_callee_800954_c_4((position), neutral_upper_bound);
            }
        }
        lower_bound = (handle_queries_large_offset_returns_larger_original_shifted_result(position) << 0x10) - 1;
        if (lower_bound >= position->x.v) {
            set_global_800_cfcea_initialize_call_callee_800954_c_4((struct EntityRec *)(position), lower_bound);
        }
    }
}
