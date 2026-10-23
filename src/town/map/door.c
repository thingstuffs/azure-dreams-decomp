/* Handles door collision, opening and closing, entrance interactions, and map changes. */
#include "script_symbols.h"
#include "shared/object_flags.h"
#include "town/map/door.h"



/* Test the object status, reversing the result when the linked record has bit 3 set. */
s32 check_door_status_inverted(void *object) {
    if ((((S_800A0668_1 *)(((Rec_func_800A0668_arg0 *)object)->unk_98))->unk_01 & 8) != 0) {
        return ((Rec_func_800A0668_arg0 *)object)->unk_95 == 0;
    }
    return ((Rec_func_800A0668_arg0 *)object)->unk_95 != 0;
}

/* Initialize the record and select its handler according to its variant. */
void initialize_door_variant(void *record_data, s32 initial_value) {
    u32 variant;

    variant = ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_A4;
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_00 = &handle_door_check_result;
    {
        union { s32 *pointer; s32 value; } handler;

        if (variant == 1) {
            handler.value = 2;
            ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_A0 = handler.value;
            handler.pointer = &advance_door_step;
            ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_7E = 0;
        } else if (variant == 0) {
            handler.pointer = &trigger_door_interaction_effect;
        } else {
            handler.pointer = &install_next_door_handler;
            ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_7E = 0;
        }
        ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_60 = handler.pointer;
    }
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_18 = initial_value;
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_1C = &D_800D09E0;
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_78 = 0;
}

/* Clear and flag the object on a nonzero check result, or invoke its callback. */
void handle_door_check_result(S_func_800A0708_0 *object, void *callback_arg, s32 callback_data)
{
    s8 *linked_flag;
    s32 check_result;
    void (*callback)(void *, void *, void *, s32);

    check_result = classify_object_against_bounds(object, callback_arg);
    {
        register S_func_800A0708_0 *callback_object = object;

        if (check_result != 0) {
            linked_flag = object->unk_98;
            if (linked_flag != 0) {
                *linked_flag = 0;
            }
            unlink_node_if_registered(object);
            ((S_func_800A0708_1 *)((u8 *)object - 2))->unk_00 =
                (u16)(((S_func_800A0708_1 *)((u8 *)object - 2))->unk_00 | 0x8000);
            object_flag_block.flags = (s32)(object_flag_block.flags | OBJECT_REMOVE_PENDING);
            return;
        } else {
            register void *object_arg = callback_object;

            callback = callback_object->unk_50;
            callback(callback_object, object_arg, callback_arg, callback_data);
        }
    }
}

/* Install the next object handler when the update call succeeds. */
void install_next_door_handler(void *object, s32 unused_value, s32 update_context, u8 unused_flags) {
    s32 linked_record = *(s32 *)((u8 *)object + 0x98);
    u8 status_byte = *(u8 *)((u8 *)object + 0x94);

    if (create_object_with_shared_data(object, linked_record, update_context, status_byte) != 0) {
        *(s32 *)((u8 *)object + 0x50) = (s32) &emit_door_position_effect;
    }
}

/* Set the entity effect and emit it at the supplied position when the checks pass. */
void emit_door_position_effect(S800A3088Arg0 *entity, s32 action, S800A3088Arg2 *position) {
    if (entity->unk68 == 0) {
        if (check_door_status_inverted(entity) != 0) {
            return;
        }
    } else if (check_door_status_inverted(entity) == 0) {
        return;
    }
    if (check_door_input_and_angle(entity, action) != 0) {
        entity->unk50 = open_door_to_target;
        action = position->unk2;
        initialize_player_entity_callbacks(entity->unk72, action, position->unk6);
    }
}

// Increase the object's ramp value, then finalize and change state at the limit.
void open_door_to_target(void *object, void *context) {
    u16 rampValue;

    rampValue = *(u16 *)((u8 *)object + 0x6E) + 0x40;
    *(u16 *)((u8 *)object + 0x6E) = rampValue;
    if ((s16) rampValue >= 0x400) {
        *(u16 *)((u8 *)object + 0x6E) = 0x400U;
        change_door_map(object, *(s32 *)((u8 *)context + 0x48));
        *(void **)((u8 *)object + 0x50) = &door_no_op;
    }
}

/* Returns without performing any work. */
void door_no_op(void) {
}

/* Increase the door opening angle and switch handlers when fully open. */
void advance_door_open_angle(S_800A08F0_0 *door) {
    u16 opening_angle;

    opening_angle = door->unk_6E + 0x40;
    door->unk_6E = opening_angle;
    if ((s16) opening_angle >= 0x400) {
        door->unk_6E = 0x400U;
        door->unk_50 = &tick_door_open_countdown;
    }
}

/* Decrement the countdown and switch to advance_door_close_angle when it expires. */
void tick_door_open_countdown(S_800A092C_0 *state) {
    u16 countdown;

    countdown = state->unk_6C - 1;
    state->unk_6C = countdown;
    if ((countdown << 0x10) <= 0) {
        state->unk_50 = &advance_door_close_angle;
    }
}

/* Decrease the door opening angle and switch handlers when closed. */
void advance_door_close_angle(S_800A0958_0 *door) {
    u16 opening_angle;

    opening_angle = door->unk_6E - 0x40;
    door->unk_6E = opening_angle;
    if ((opening_angle << 0x10) <= 0) {
        door->unk_6E = 0U;
        door->unk_50 = &emit_door_position_effect;
    }
}

/* Finds the first node with the required key and value whose 0x400 flag is clear. */
void *find_door_keyed_node(s32 requested_value)
{
    Node *node;
    Node *next_node;
    s32 node_key;
    s32 required_node_key;
    NodeData *node_data;
    void *result;

    node = active_node_list_head.head;
    if (node != 0) {
        required_node_key = (s32)&handle_door_check_result;
        do {
            node_key = node->field_10;
            next_node = node->next;
            if (node_key < 0) {
                if (!(node->flags & 0x400)) {
                    node_data = (NodeData *)((u8 *)node + 0x20);
                    if ((node_key == required_node_key) && (node_data->field_48 == requested_value)) {
                        result = node;
                        return result;
                    }
                }
            }
            node = next_node;
        } while (node != 0);
    }
    result = 0;
    return result;
}

/* door_open_demo_set_sub: Set the door opening demo handler and angle. */
void door_open_demo_set_sub(s32 door_id, s16 demo_angle) {
    void *door_object;
    EntityStruct *door;

    door_object = find_door_keyed_node(door_id);
    door = (EntityStruct *)((u8 *)door_object + 0x20);
    if (door_object != 0) {
        door->unk50 = &advance_door_open_angle;
        door->unk6C = demo_angle;
    }
}

/* door_open_demo_set: Run the shared town script handler with argument 8. */
void door_open_demo_set(s32 script_context) {
    door_open_demo_set_sub(script_context, 8);
}

/* door_atari_on_off: Set the collision flag for the selected door. */
void door_atari_on_off(s32 door_id, s16 collision_enabled) {
    S_800A0A54_0 *door;

    door = find_door_keyed_node(door_id);
    if (door != NULL) {
        door->unk_88 = collision_enabled;
    }
}

/* into_dn_door_demo_set: Initialize the dungeon entrance door demo state and handler. */
void into_dn_door_demo_set(void) {
    void *door_object;
    S_800A0A88_0 *door;

    door_object = find_door_keyed_node(&D_800D4404);
    door = (void *)((u8 *)door_object + 0x20);
    if (door_object != 0) {
        door->unk_90 = 6;
        door->unk_50 = &update_door_completion_state;
    }
}

/* Check interaction conditions, apply the target value, and trigger a positional effect. */
void trigger_door_interaction_effect(void *actor, void *target, void *position) {
    if (*(s16 *)((u8 *)actor + 0x68) == 0) {
        if (check_door_status_inverted(actor) != 0) {
            return;
        }
    } else {
        if (check_door_status_inverted(actor) == 0) {
            return;
        }
    }
    if (check_door_input_and_angle(actor, target) == 0) {
        return;
    }
    change_door_map(actor, *(s32 *)((u8 *)target + 0x48));
    *(void **)((u8 *)actor + 0x50) = &door_no_op;
    initialize_entity_handlers_and_position(*(s16 *)((u8 *)actor + 0x72), *(s16 *)((u8 *)position + 2), *(s16 *)((u8 *)position + 6));
}

/* Changes maps using direct map data or a selected table entry. */
void change_door_map(void *map_source, s32 *map_table) {
    u8 selection_mode;

    selection_mode = *((u8 *)((s8 *)map_source + 0x96));
    if (selection_mode == 0) {
        map_source = map_table;
    } else {
        s32 map_index;

        if (selection_mode == 1) {
            map_index = find_target_byte_index_in_list();
        } else {
            map_index = get_player_homerank();
        }
        map_source = (void *)map_table[map_index];
    }
    change_map(map_source);
}

/* Update the entity step state and switch handlers when the result is zero. */
void advance_door_step(void *entity) {
    s16 step_result;
    s32 uninitialized_arg;

    step_result = create_objects_descending_by_count(entity, *(s32 *)((u8 *)entity + 0x98), uninitialized_arg, *(s16 *)((u8 *)entity
        + 0x90));
    *(s16 *)((u8 *)entity + 0x90) = step_result;
    if ((step_result << 0x10) == 0) {
        *(void **)((u8 *)entity + 0x50) = &select_tower_entry_handler_by_item_count;
    }
}

/* Selects the door's entrance or waiting handler according to whether the entry count is below six. */
void select_tower_entry_handler_by_item_count(S_800A0C30_0 *script_state, void *unused_context, S_800A0C30_1 *event_params) {
    if (check_door_input_and_angle(script_state, unused_context) != 0) {
        if (count_consecutive_nonzero_entries_up_twenty() < 6) {
            script_state->unk_90 = 6;
            script_state->unk_50 = &update_door_completion_state;
            initialize_entity_handlers_and_position(script_state->unk_72, event_params->unk_02, event_params->unk_06);
            return;
        }
        script_state->unk_50 = &set_door_handler_if_ready;
        set_player_block_value(script_state->unk_72);
    }
}

/* Set the object handler when service_script_controller returns zero. */
void set_door_handler_if_ready(S_800A0CC0_0 *object, s32 value_1, s32 value_2, s32 value_3) {
    if (service_script_controller() == 0) {
        object->unk_50 = &select_tower_entry_handler_by_item_count;
    }
}

/* Updates the object's state and applies completion effects when it reaches zero. */
void update_door_completion_state(u8 *object, s32 unused, s32 state_id, s32 state_arg) {
    s16 state;

    state = initialize_object_items_in_reverse(door_transition_state, state_id, *(s16 *)(object + 0x90));
    *(s16 *)(object + 0x90) = state;
    if ((s32)(state << 0x10) == 0) {
        no_op_callback_a(door_transition_state, state_id, state_arg);
        *(void **)(object + 0x50) = advance_door_state_counter;
        load_indexed_resource_package(0);
        sound_set_cd_cue_parameters(0, cd_cue_base[0], 0x0600065E, 0x030008B6);
        SD_Call(0x300);
    }
}

/* Advance the state counter and apply the next state when the check succeeds. */
void advance_door_state_counter(S_800A0DAC_0 *state, s32 unused, s32 context_a, s32 context_b) {
    decrease_value_and_advance_counter(&door_transition_state, context_a, context_b);
    state->unk_6E = (u16)(state->unk_6E + 0x10);
    if (animate_spinning_shrinking_object(&door_transition_state, context_a, context_b) != 0) {
        state->unk_6C = 0x20;
        state->unk_50 = &tick_door_countdown;
    }
}

/* Update the countdown and reset the object's state when it expires. */
void tick_door_countdown(Rec_func_800A0668_arg0 *object, S_800A0E3C_1 *source, s32 update_arg_a, s32 update_arg_b) {
    u16 remaining_count;

    decrease_value_and_advance_counter(&door_transition_state, update_arg_a, update_arg_b);
    remaining_count = object->unk_6C - 1;
    object->unk_6C = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        change_door_map(object, source->unk_48);
        object->unk_50 = &door_no_op;
        into_dn_door_jobs();
    }
}

/* into_dn_door_jobs: Run dungeon entrance setup and reset entry flags. */
void into_dn_door_jobs(void) {
    clear_resident_bit_patterns();
    clear_resident_bitmap_bit(sn_mam_pan_give);
    apply_building_pending_updates();
    dispatch_conditional_table_pairs();
    current_dungeon_floor = 1;
    runtime_dispatch_state.flags16 = 0;
    system_update_flags &= 0xFFF8;
}

/* Tests the input and object angle against either supported global state. */
s32 check_door_input_and_angle(Rec_func_800A0668_arg0 *object, s32 test_value) {
    if (get_smallest_signed_overlap_axis_amount_two_intersecting_boxes(test_value, &town_actor_control) != 0) {
        s32 *global_base = &scene_object_payload_alias;
        s32 global_angle = ((S_800A0F10_0 *)global_base)->unk_10 & 0xFFF;
        s32 object_angle = object->unk_72 & 0xFFF;

        if ((u32) ((object_angle - global_angle) + 0x3FF) < 0x7FFU) {
            if ((scene_object_payload_alias == (s32)&D_80091260) || (scene_object_payload_alias == (s32)&D_80091528)) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}
