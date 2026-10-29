#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
#include "shared/town_handler.h"
#include "town/person/effects.h"
#include "town/player/coordinates.h"
#include "town.h"
#include "town/player.h"
#include "town/system.h"
#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"                      /* extern */
void handle_adjust_vector_toward_selected_angle_limit_magnitude();                      /* extern */
#include "town/player/clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2_api.h"                      /* extern */
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"      /* extern */
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"                      /* extern */

/* Advance the state counter and update the entity, handling threshold and flag transitions. */
void update_threshold_and_interaction(Rec_func_80094268_arg0 *state, EntityRec *entity, s32 context) {
    s16 threshold;
    u16 counter;

    counter = state->unk_0A.as_u16 + 1;
    state->unk_0A.as_u16 = counter;
    if ((s16) counter == 6) {
        call_the_handler_selects_nonzero_entry((s32 *) action_object_handler_table, state, (void *) context);
    }
    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(entity);
    store_the_valid_shared_angle_in_offset_hex_10(state);
    handle_adjust_vector_toward_selected_angle_limit_magnitude(entity);
    threshold = select_the_smaller_position_query_result_capped_n_64_writes_associated(entity, &position_query_scratch);
    if (entity->z.w.i >= threshold) {
        select_sound_command_from_mode();
        compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(entity), threshold, (struct TownVec * *)(&position_query_scratch));
        spawn_person_radial_effects(entity);
        initialize_action_object_type_six(state, entity, context);
        return;
    }
    if (town_action_state_flag != 0) {
        select_sound_command_from_mode();
        entity->flags14 = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2((s32 *)(entity));
        initialize_action_object_type_six(state, entity, context);
        return;
    }
    add_hex_20000_s_signed_offset_hex_14(entity);
}
