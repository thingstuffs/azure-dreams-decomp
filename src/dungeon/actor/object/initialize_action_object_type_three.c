/* Actor action initializers that select handlers, counters, facing values, and sounds. */
#include "dungeon/actor/object/initialize_action_object_type_three.h"
#include "dungeon/actor/object.h"


/*
 * Selects type_three_action_handler_table, installs update_movement_and_expire_state, and sets the
 * action count to 3.
 */
void initialize_action_object_type_three(TownObjectRecord *object) {
    dispatch_selected_entry_if_nonzero(&type_three_action_handler_table, object);
    object->unk_00 = (void *)update_movement_and_expire_state;
    object->unk_0A = 3;
}

/*
 * Dispatches the mode-selected sound, sets flags14 to 0xFFEF0000, selects D_800D00B0, and installs
 * update_actor_and_dispatch_state with count zero.
 */
void initialize_actor_action_state(TownObjectRecord *object, EntityRec *state, s32 setupArg) {
    play_sound_by_height_range();
    state->flags14 = 0xFFEF0000;
    dispatch_selected_entry_if_nonzero(&D_800D00B0, object, setupArg);
    object->unk_00 = (void *)update_actor_and_dispatch_state;
    object->unk_0A = 0;
}

/* Installs update_airborne_object_with_land_timer and clears the action counter. */
void initialize_threshold_interaction_action(Rec_func_8009431C_arg0 *record) {
    record->unk_00.as_pm = (void *)update_airborne_object_with_land_timer;
    record->unk_0A = 0;
}

/* Selects D_800D00C0, installs update_countdown_and_fallback, and sets the action count to 6. */
void initialize_action_object_type_six(TownObjectRecord *object) {
    dispatch_selected_entry_if_nonzero(&D_800D00C0, object);
    object->unk_00 = (void *)update_countdown_and_fallback;
    object->unk_0A = 6;
}

/*
 * Selects action_object_handler_table and installs update_airborne_object_with_land_effects as the object
 * callback.
 */
void initialize_action_object(s32 **object) {
    dispatch_selected_entry_if_nonzero(&action_object_handler_table, object);
    *object = (void *)update_airborne_object_with_land_effects;
}

/*
 * Stores the shared angle, selects D_800D0108, and installs update_actor_movement_actions with
 * count 6.
 */
void initialize_movement_actions(TownObjectRecord *object, s32 setup_arg, s32 context, s32 setup_extra) {
    store_input_angle(object);
    dispatch_selected_entry_if_nonzero(&D_800D0108, object, context);
    object->unk_00 = (void *)update_actor_movement_actions;
    object->unk_0A = 6;
}

/*
 * Plays sound 0x50B, stores the shared angle, selects D_800D0110, and installs
 * update_actor_input_actions.
 */
void initialize_action_object_and_play_sound(s32 **object, s32 unused, s32 context) {
    SD_Call(0x50B);
    store_input_angle(object);
    dispatch_selected_entry_if_nonzero(&D_800D0110, object, context);
    *object = (void *)update_actor_input_actions;
}

/* Selects D_800D0118 and installs dispatch_actor_interaction_with_fallback with count 6. */
void initialize_interaction_fallback_action(ovl_16b08_local_7FFF6D14_InitState *state, void *unused, void *context) {
    dispatch_selected_entry_if_nonzero(D_800D0118, state, context);
    state->callback = (void *)dispatch_actor_interaction_with_fallback;
    state->count = 6;
}

/*
 * Plays sound 0x511, selects counted_action_handler_table, and installs
 * update_actor_with_interaction_state with count 6.
 */
void initialize_action_object_with_counter(TownObjectRecord *object, s32 unused, s32 context) {
    SD_Call(0x511);
    dispatch_selected_entry_if_nonzero(&counted_action_handler_table, object, context);
    object->unk_00 = (void *)update_actor_with_interaction_state;
    object->unk_0A = 6;
}

/* Selects movement_action_handler_table and installs update_actor_movement_and_interaction. */
void initialize_actor_movement_interaction_action(ovl_16b08_local_7FFF6DBC_InitState *state, void *unused, void *context) {
    dispatch_selected_entry_if_nonzero(movement_action_handler_table, state, context);
    state->callback = (void *)update_actor_movement_and_interaction;
}

/*
 * Sets the halfword at offset 0x3E to 6, stores the shared angle, selects D_800D0130, and installs
 * update_actor_position_and_interaction.
 */
void initialize_actor_position_interaction_action(TownObjectRecord *object, s32 setup_arg, s32 context, s32 setup_extra) {
    object->unk_3E = 6;
    store_input_angle(object);
    dispatch_selected_entry_if_nonzero(&D_800D0130, object, context);
    object->unk_00 = (void *)update_actor_position_and_interaction;
}

/*
 * Dispatches the mode-selected sound, sets flags14 to 0xFFEF0000, selects D_800D0140, and installs
 * update_town_object_from_input.
 */
void initialize_input_driven_scene_object(s32 **outputSlot, EntityRec *state, s32 initContext) {
    play_sound_by_height_range();
    state->flags14 = 0xFFEF0000;
    dispatch_selected_entry_if_nonzero(&D_800D0140, outputSlot, initContext);
    *outputSlot = (void *)update_town_object_from_input;
}

/* Selects D_800D0148 and installs update_threshold_object_with_interaction. */
void initialize_threshold_interaction_object(ovl_16b08_local_7FFF6EC0_InitState *state, void *unused, void *context) {
    dispatch_selected_entry_if_nonzero(D_800D0148, state, context);
    state->callback = (void *)update_threshold_object_with_interaction;
}

/* Selects action_object_handler_table and installs update_actor_movement_with_radial_effects. */
void init_radial_effects_action(ovl_16b08_local_7FFF6F00_InitState *state, void *unused, void *context) {
    dispatch_selected_entry_if_nonzero(action_object_handler_table, state, context);
    state->callback = (void *)update_actor_movement_with_radial_effects;
}

/*
 * Stores the shared angle, selects countdown_action_handler_table, and installs
 * update_ground_countdown_unless_busy with count 6.
 */
void initialize_busy_checked_countdown_action(ovl_16b08_local_7FFF6F40_InitState *state, void *argument, void *context) {
    store_input_angle(state);
    dispatch_selected_entry_if_nonzero(countdown_action_handler_table, state, context);
    state->callback = (void *)update_ground_countdown_unless_busy;
    state->count = 6;
}

/* Installs update_actor_interaction_actions and sets the action counter to 0x13. */
void install_actor_interaction_handler(TownObjectRecord *record) {
    record->unk_00 = (void *)update_actor_interaction_actions;
    record->unk_0A = 0x13;
}
