#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "shared/entity.h"

void initialize_actor_movement_interaction_action(s32 **record, void *ptr, void *ptr2);
void func_80094714(s32 **record, s32 unused, s32 setup_value);
void select_sound_command_from_mode(void);
void store_the_valid_shared_angle_in_offset_hex_10();                         /* extern */
void handle_adjust_vector_toward_selected_angle_limit_magnitude();                      /* extern */
void add_hex_20000_s_signed_offset_hex_14();                      /* extern */
void clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2();                      /* extern */
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();               /* extern */
void compute_and_clamps_vector_based_adjustment_updates_town();      /* extern */
void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile();                      /* extern */
void spawn_person_radial_effects();                      /* extern */


/* Updates a town object based on its threshold and the global update flag. */
void update_threshold_object_with_interaction(s32 object_id, EntityRec *object, s32 update_context) {
    s16 update_threshold;
    GameWork *town_state;

    town_state = &g_game_work;
    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(object);
    store_the_valid_shared_angle_in_offset_hex_10(object_id);
    handle_adjust_vector_toward_selected_angle_limit_magnitude(object);
    if (((s32)town_state->unk_010) & 0x40) {
        func_80094714(object_id, object, update_context);
    }
    update_threshold = select_the_smaller_position_query_result_capped_n_64_writes_associated(object, &D_800FE488);
    if (object->z.w.i >= update_threshold) {
        select_sound_command_from_mode();
        compute_and_clamps_vector_based_adjustment_updates_town(object, update_threshold, &D_800FE488);
        spawn_person_radial_effects(object);
        initialize_actor_movement_interaction_action(object_id, object, update_context);
    } else if (D_800CFCEF != 0) {
        select_sound_command_from_mode();
        object->flags14 = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(object);
        initialize_actor_movement_interaction_action(object_id, object, update_context);
    } else {
        add_hex_20000_s_signed_offset_hex_14(object);
    }
}
