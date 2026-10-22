/* Actor action initializers that select handlers, counters, facing values, and sounds. */
#include "dungeon/actor/object/initialize_action_object_type_three.h"


void initialize_action_object_type_three(Rec_func_80094268_arg0 *object) {
    call_the_handler_selects_nonzero_entry(&D_800D00A0, object);
    object->unk_00.as_pm = (void *)update_movement_and_expire_state;
    object->unk_0A.as_s16 = 3;
}

void initialize_actor_action_state(Rec_func_80094268_arg0 *object, EntityRec *state, s32 setupArg) {
    dispatch_sound_by_global_flag();
    state->flags14 = 0xFFEF0000;
    call_the_handler_selects_nonzero_entry(&D_800D00B0, object, setupArg);
    object->unk_00.as_pm = (void *)update_actor_and_dispatch_state;
    object->unk_0A.as_s16 = 0;
}

void initialize_threshold_interaction_action(Rec_func_8009431C_arg0 *record) {
    record->unk_00.as_pm = (void *)update_threshold_and_interaction;
    record->unk_0A = 0;
}

void initialize_action_object_type_six(Rec_func_80094268_arg0 *object) {
    call_the_handler_selects_nonzero_entry(&D_800D00C0, object);
    object->unk_00.as_pm = (void *)update_countdown_and_fallback;
    object->unk_0A.as_s16 = 6;
}

void initialize_action_object(s32 **object) {
    call_the_handler_selects_nonzero_entry(&D_800D00B8, object);
    *object = (void *)update_threshold_bound_object;
}

void initialize_movement_action_count_six(Rec_func_80094268_arg0 *object, s32 setup_arg, s32 context, s32 setup_extra) {
    store_the_valid_shared_angle_in_offset_hex_10(object);
    call_the_handler_selects_nonzero_entry(&D_800D0108, object, context);
    object->unk_00.as_pm = (void *)update_actor_movement_actions;
    object->unk_0A.as_s16 = 6;
}

void initialize_action_object_and_play_sound(s32 **object, s32 unused, s32 context) {
    SD_Call(0x50B);
    store_the_valid_shared_angle_in_offset_hex_10(object);
    call_the_handler_selects_nonzero_entry(&D_800D0110, object, context);
    *object = (void *)update_actor_input_actions;
}

void initialize_action_handler_with_count_six(ovl_16b08_local_7FFF6D14_InitState *state, void *unused, void *context) {
    call_the_handler_selects_nonzero_entry(D_800D0118, state, context);
    state->callback = (void *)dispatch_actor_interaction_with_fallback;
    state->count = 6;
}

void initialize_action_object_with_counter(Rec_func_80094268_arg0 *object, s32 unused, s32 context) {
    SD_Call(0x511);
    call_the_handler_selects_nonzero_entry(&D_800D0120, object, context);
    object->unk_00.as_pm = (void *)update_actor_with_interaction_state;
    object->unk_0A.as_s16 = 6;
}

void initialize_actor_movement_interaction_action(ovl_16b08_local_7FFF6DBC_InitState *state, void *unused, void *context) {
    call_the_handler_selects_nonzero_entry(D_800D0128, state, context);
    state->callback = (void *)update_actor_movement_and_interaction;
}

void initialize_actor_position_interaction_action(Rec_func_80094268_arg0 *object, s32 setup_arg, s32 context, s32 setup_extra) {
    object->unk_3E.as_s16 = 6;
    store_the_valid_shared_angle_in_offset_hex_10(object);
    call_the_handler_selects_nonzero_entry(&D_800D0130, object, context);
    object->unk_00.as_pm = (void *)update_actor_position_and_interaction;
}

void initialize_input_driven_scene_object(s32 **outputSlot, EntityRec *state, s32 initContext) {
    dispatch_sound_by_global_flag();
    state->flags14 = 0xFFEF0000;
    call_the_handler_selects_nonzero_entry(&D_800D0140, outputSlot, initContext);
    *outputSlot = (void *)update_town_object_from_input;
}

void initialize_threshold_interaction_object(ovl_16b08_local_7FFF6EC0_InitState *state, void *unused, void *context) {
    call_the_handler_selects_nonzero_entry(D_800D0148, state, context);
    state->callback = (void *)update_threshold_object_with_interaction;
}

void initialize_action_callback_from_entry(ovl_16b08_local_7FFF6F00_InitState *state, void *unused, void *context) {
    call_the_handler_selects_nonzero_entry(D_800D00B8, state, context);
    state->callback = (void *)update_actor_movement_with_radial_effects;
}

void initialize_busy_checked_countdown_action(ovl_16b08_local_7FFF6F40_InitState *state, void *argument, void *context) {
    store_the_valid_shared_angle_in_offset_hex_10(state, argument, context);
    call_the_handler_selects_nonzero_entry(D_800D0138, state, context);
    state->callback = (void *)update_threshold_countdown_with_busy_check;
    state->count = 6;
}

void initialize_actor_interaction_state_19(Rec_func_80094268_arg0 *record) {
    record->unk_00.as_pm = (void *)update_actor_interaction_actions;
    record->unk_0A.as_s16 = 0x13;
}
