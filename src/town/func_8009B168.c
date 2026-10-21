/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"

extern void copy_motion_parameters_and_reset_flag(s32 record, s32 source);
extern void initialize_target_and_handler_table(s32 record, s32 setup_value, s32 init_value);
extern s32 D_80093D48;
extern s32 *town_player_action_callback;

void func_800988C8(s32 record, s32 setup_value, s32 init_value) {
    copy_motion_parameters_and_reset_flag(record, setup_value);
    initialize_target_and_handler_table(record, setup_value, init_value);
    town_player_action_callback = &D_80093D48;
}
