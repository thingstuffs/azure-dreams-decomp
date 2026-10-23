#include "common.h"

extern void copy_motion_parameters_and_reset_flag(s32 record, s32 source);
extern void initialize_record_with_handler_table(s32 record, s32 setup_value, s32 init_value);
extern s32 town_motion_action_address;
extern s32 *town_player_action_callback;

/*
 * Copies motion parameters and initializes the handler table, then selects
 * town_motion_action_address as the player action callback.
 */
void initialize_record_and_select_active_data(s32 record, s32 setup_value, s32 init_value) {
    copy_motion_parameters_and_reset_flag(record, setup_value);
    initialize_record_with_handler_table(record, setup_value, init_value);
    town_player_action_callback = &town_motion_action_address;
}
