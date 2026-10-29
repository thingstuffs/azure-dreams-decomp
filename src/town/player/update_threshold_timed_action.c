#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/town_handler_entries.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */


#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"
#include "town/player/move_both_components_toward_zero_direction_dependent_steps_clamping_zero_api.h"
#include "town/player/coordinates.h"
#include "town.h"
#include "town/player.h"
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"
#include "town/player/call_the_handler_selects_nonzero_entry_api.h"
void init_actor_action_state(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2);



/* Update the entity, handle a large value change, and advance the state countdown. */
void update_threshold_timed_action(Rec_func_80094268_arg0 *state, EntityRec *entity, s32 context) {
    s16 sampled_value;
    s16 ticks_left;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(entity);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(entity);
    sampled_value = select_the_smaller_position_query_result_capped_n_64_writes_associated(entity, &position_query_scratch);
    if ((sampled_value - entity->z.w.i) >= 4) {
        if (town_action_state_flag == 0) {
            initialize_action_object(state, entity, context);
            return;
        }
    } else if (town_action_state_flag == 0) {
        compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(entity), sampled_value, (struct TownVec * *)(&position_query_scratch));
    }
    if (state->unk_0A.as_s16 == 0) {
        call_the_handler_selects_nonzero_entry(D_800D00E0, state, (void *)(context));
    }
    ticks_left = (u16) state->unk_0A.as_s16 - 1;
    state->unk_0A.as_s16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        init_actor_action_state(state, entity, context);
    }
}
