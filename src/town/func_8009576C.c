/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "shared/entity.h"

s32 initialize_actor_movement_interaction_action();        
s32 init_sound_threshold_action();        
void select_sound_command_from_mode(void);
#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"
void handle_adjust_vector_toward_selected_angle_limit_magnitude();                      
void add_hex_20000_s_signed_offset_hex_14(EntityRec *record);
#include "town/player/clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2_api.h"
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();               
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"
void spawn_person_radial_effects(void *);

/* Resolves actor movement, handles button 0x40, and starts an action with radial effects at a surface. */
void update_actor_movement_with_radial_effects(s32 object_id, EntityRec *object, s32 update_context) {
    s16 update_threshold;
    GameWork *town_state;

    town_state = &g_game_work;
    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(object);
    store_the_valid_shared_angle_in_offset_hex_10((void *)(object_id));
    handle_adjust_vector_toward_selected_angle_limit_magnitude(object);
    if ((town_state->pressed_buttons) & 0x40) {
        init_sound_threshold_action(object_id, object, update_context);
    }
    update_threshold = select_the_smaller_position_query_result_capped_n_64_writes_associated(object, &position_query_scratch);
    if (object->z.w.i >= update_threshold) {
        select_sound_command_from_mode();
        compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(object), update_threshold, (struct TownVec * *)(&position_query_scratch));
        spawn_person_radial_effects(object);
        initialize_actor_movement_interaction_action(object_id, object, update_context);
    } else if (town_action_state_flag != 0) {
        select_sound_command_from_mode();
        object->flags14 = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2((s32 *)(object));
        initialize_actor_movement_interaction_action(object_id, object, update_context);
    } else {
        add_hex_20000_s_signed_offset_hex_14(object);
    }
}
