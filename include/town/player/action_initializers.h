#ifndef INCLUDE_TOWN_PLAYER_ACTION_INITIALIZERS_H
#define INCLUDE_TOWN_PLAYER_ACTION_INITIALIZERS_H

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

void initialize_scene_action_record(Rec_func_80094268_arg0 *record, void *unused, void *handler_context);

void init_threshold_countdown_action(Rec_func_80094268_arg0 *record, void *unused, void *handler_context);
void init_movement_action(Rec_func_80094268_arg0 *record, s32 unused, s32 setup_value);
void init_sound_threshold_action(s32 **record, s32 unused, s32 setup_value);
void init_timed_dispatch_action(Rec_func_80094268_arg0 *record, void *unused, void *handler_context);
void init_actor_action_state(Rec_func_80094268_arg0 *record, void *unused, void *handler_context);
void init_record_target_approach(Rec_func_80094268_arg0 *record, s32 setup_value, s32 init_context);
void init_linked_position_action(Rec_func_80094268_arg0 *record, s32 unused, s32 setup_value);
void init_ground_input_fallback(s32 **record, void *unused, void *handler_context);
void init_button_transition_action(s32 **record, void *unused, void *handler_context);
void init_unchanged_action_fallback(s32 **record, void *unused, void *handler_context);
void init_periodic_effect_action(Rec_func_80094268_arg0 *object, s32 motion, s32 table_arg);
void init_flagged_entity_action(Rec_func_80094268_arg0 *record, void *unused, void *handler_context);
void init_height_interpolation_action(Rec_func_80094268_arg0 *record, void *unused, void *handler_context);
void init_target_tile_action(Rec_func_80094268_arg0 *record, void *unused, void *handler_context);
void init_flagged_action_fallback(s32 **record, void *unused, void *handler_context);
void init_input_action_fallback(s32 **record, void *unused, void *handler_context);
void init_negative_x_step_action(Rec_func_80094268_arg0 *object, void *unused, void *handler_context);
void init_eased_value_action(Rec_func_80094268_arg0 *object, s32 context, void *handler_context);
void init_player_countdown_action(Rec_func_80094268_arg0 *object, void *unused, void *handler_context);
void init_countdown_handler_action(Rec_func_80094268_arg0 *record, void *unused, void *handler_context);
void init_four_tick_record_action(Rec_func_80094268_arg0 *object, s32 motion_context, void *handler_context);
void init_quarter_turn_motion_action(Rec_func_80094268_arg0 *object, void *unused, void *handler_context);
void init_object_countdown_action(Rec_func_80094268_arg0 *object, void *unused, void *handler_context);
void init_four_tick_target_action(Rec_func_80094268_arg0 *object, s32 motion_context, void *handler_context);
void init_positive_x_step_action(Rec_func_80094268_arg0 *object, void *unused, void *handler_context);
void init_twenty_one_tick_record_action(Rec_func_80094268_arg0 *object, void *unused, void *handler_context);
void init_seven_tick_record_action(Rec_func_80094268_arg0 *object, s32 motion_context, void *handler_context);
void init_twenty_one_tick_target_action(Rec_func_80094268_arg0 *record, void *unused, void *handler_context);
void init_half_turn_motion_action(Rec_func_80094268_arg0 *object, void *unused, void *handler_context);
void init_sixty_tick_target_action(Rec_func_80094268_arg0 *object, s32 motion_context, void *handler_context);
void init_three_quarter_turn_motion_action(Rec_func_80094268_arg0 *object, void *unused, void *handler_context);
void init_positive_y_step_action(Rec_func_80094268_arg0 *object, void *unused, void *handler_context);
void init_sixteen_tick_record_action(Rec_func_80094268_arg0 *object, s32 motion_context, void *handler_context);
void init_twenty_one_tick_record_action_b(Rec_func_80094268_arg0 *record, void *unused, void *handler_context);
void init_twenty_one_tick_record_action_c(Rec_func_80094268_arg0 *object, void *unused, void *handler_context);
void init_motion_action_callback(s32 record, s32 setup_value, s32 init_value);

#endif
