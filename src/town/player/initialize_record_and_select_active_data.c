#include "town/player/initialize_record_and_select_active_data.h"
#include "town/player/initialize_record_with_handler_table_api.h"
#include "common.h"
#include "town/player.h"
#include "town/player/motion.h"
#include "shared/sprite_frame_state.h"


extern s32 *town_player_action_callback;

/*
 * Copies motion parameters and initializes the handler table, then selects
 * town_motion_action_address as the player action callback.
 */
void initialize_record_and_select_active_data(void *record, ObjectPosition *position, SpriteFrameState *sprite) {
    copy_motion_parameters_and_reset_flag(record, position);
    initialize_record_with_handler_table(record, position, sprite);
    town_player_action_callback = initialize_scene_action_record;
}
