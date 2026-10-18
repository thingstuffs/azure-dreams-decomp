#include "shared/position_query.h"
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
#include "shared/town_handler.h"

M2C_UNK initialize_action_object_type_six();     /* extern */
M2C_UNK select_sound_command_from_mode();                            /* extern */
void store_the_valid_shared_angle_in_offset_hex_10();                      /* extern */
void handle_adjust_vector_toward_selected_angle_limit_magnitude();                      /* extern */
void add_hex_20000_s_signed_offset_hex_14();                      /* extern */
void clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2();                      /* extern */
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();               /* extern */
void compute_and_clamps_vector_based_adjustment_updates_town();      /* extern */
void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile();                      /* extern */
void spawn_person_radial_effects();                      /* extern */
extern u8 D_800CFCEF;
extern M2C_UNK D_800D00B8;

/* Advance the state counter and update the entity, handling threshold and flag transitions. */
void update_threshold_and_interaction(Rec_func_80094268_arg0 *state, EntityRec *entity, s32 context) {
    s16 threshold;
    u16 counter;

    counter = state->unk_0A.as_u16 + 1;
    state->unk_0A.as_u16 = counter;
    if ((s16) counter == 6) {
        call_the_handler_selects_nonzero_entry((s32 *) &D_800D00B8, state, (void *) context);
    }
    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(entity);
    store_the_valid_shared_angle_in_offset_hex_10(state);
    handle_adjust_vector_toward_selected_angle_limit_magnitude(entity);
    threshold = select_the_smaller_position_query_result_capped_n_64_writes_associated(entity, &D_800FE488);
    if (entity->z.w.i >= threshold) {
        select_sound_command_from_mode();
        compute_and_clamps_vector_based_adjustment_updates_town(entity, threshold, &D_800FE488);
        spawn_person_radial_effects(entity);
        initialize_action_object_type_six(state, entity, context);
        return;
    }
    if (D_800CFCEF != 0) {
        select_sound_command_from_mode();
        entity->flags14 = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(entity);
        initialize_action_object_type_six(state, entity, context);
        return;
    }
    add_hex_20000_s_signed_offset_hex_14(entity);
}
