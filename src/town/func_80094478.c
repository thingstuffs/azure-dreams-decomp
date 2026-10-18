#include "shared/position_query.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */


void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile();
void move_both_components_toward_zero_direction_dependent_steps_clamping_zero();
s32 select_the_smaller_position_query_result_capped_n_64_writes_associated();
void initialize_action_object(s32 **record, void *ptr, void *ptr2);
void compute_and_clamps_vector_based_adjustment_updates_town();
void call_the_handler_selects_nonzero_entry();
void func_800941D8(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2);

extern u8 D_800CFCEF;
extern M2C_UNK D_800D00E0;


/* Update the entity, handle a large value change, and advance the state countdown. */
void update_threshold_timed_action(Rec_func_80094268_arg0 *state, EntityRec *entity, s32 context) {
    s16 sampled_value;
    s16 ticks_left;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(entity);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(entity);
    sampled_value = select_the_smaller_position_query_result_capped_n_64_writes_associated(entity, &D_800FE488);
    if ((sampled_value - entity->z.w.i) >= 4) {
        if (D_800CFCEF == 0) {
            initialize_action_object(state, entity, context);
            return;
        }
    } else if (D_800CFCEF == 0) {
        compute_and_clamps_vector_based_adjustment_updates_town(entity, sampled_value, &D_800FE488);
    }
    if (state->unk_0A.as_s16 == 0) {
        call_the_handler_selects_nonzero_entry(&D_800D00E0, state, context);
    }
    ticks_left = (u16) state->unk_0A.as_s16 - 1;
    state->unk_0A.as_s16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        func_800941D8(state, entity, context);
    }
}
