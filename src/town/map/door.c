/* Handles door collision, opening and closing, entrance interactions, and map changes. */
#include "script_symbols.h"
#include "shared/object_flags.h"
#include "town/map/door.h"
#include "town.h"
#include "town/map.h"
#include "engine/script.h"
#include "town/person.h"
#include "town/player/input.h"

/* Test the object status, reversing the result when the linked record has bit 3 set. */
s32 check_door_status_inverted(S800A3088Arg0 *door) {
    if ((((S_800A0668_1 *)door->unk98)->unk_01 & 8) != 0) {
        return door->unk95 == 0;
    }
    return door->unk95 != 0;
}

/* Initialize the record and select its handler according to its variant. */
void initialize_door_variant(TownObjectRecord *record_data, ObjectPosition *position, struct SpriteFrameState *unused_sprite) {
    u32 variant;

    variant = ((u8)(record_data->unk_94));
    NODE_HEADER(record_data)->update_callback = update_door_object;
    {
        union { s32 *pointer; s32 value; } handler;

        if (variant == 1) {
            handler.value = 2;
            record_data->unk_90 = handler.value;
            handler.pointer = &create_door_transition_objects;
            record_data->unk_6E = 0;
        } else if (variant == 0) {
            handler.pointer = &check_door_entry_and_change_map;
        } else {
            handler.pointer = &create_door_shared_object;
            record_data->unk_6E = 0;
        }
        record_data->unk_50.as_pm = handler.pointer;
    }
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->position = position;
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_1C = &D_800D09E0;
    record_data->unk_68 = 0;
}

/* Clear and flag the object on a nonzero check result, or invoke its callback. */
void update_door_object(S_func_800A0708_0 *object, ObjectPosition *position, SpriteFrameState *sprite)
{
    s8 *linked_flag;
    s32 check_result;
    void (*callback)(void *, void *, ObjectPosition *, SpriteFrameState *);

    check_result = classify_object_against_bounds(object, position);
    {
        register S_func_800A0708_0 *callback_object = object;

        if (check_result != 0) {
            linked_flag = object->unk_98;
            if (linked_flag != 0) {
                *linked_flag = 0;
            }
            unlink_node_if_registered(object);
            NODE_HEADER(object)->flags |= NODE_REMOVE;
            object_flag_block.flags = (s32)(object_flag_block.flags | OBJECT_REMOVE_PENDING);
            return;
        } else {
            callback = callback_object->unk_50;
            callback(callback_object, callback_object, position, sprite);
        }
    }
}

/* Install the next object handler when the update call succeeds. */
void create_door_shared_object(TownObjectRecord *object, TownObjectRecord *unused_context, void *update_context, SpriteFrameState *unused_data) {
    s8 *active_flag = object->unk_98;
    u8 status_byte = ((u8)(object->unk_94));

    if (create_default_display_object(object, active_flag, update_context, status_byte) != 0) {
        object->unk_50.as_s32 = (s32) &check_door_entry_and_open;
    }
}

/* Set the entity effect and emit it at the supplied position when the checks pass. */
void check_door_entry_and_open(S800A3088Arg0 *entity, TownObjectRecord *collision_body, ObjectPosition *position) {
    s32 position_x;
    if (entity->unk68 == 0) {
        if (check_door_status_inverted(entity) != 0) {
            return;
        }
    } else if (check_door_status_inverted(entity) == 0) {
        return;
    }
    if (check_door_input_and_angle(entity, collision_body) != 0) {
        entity->unk50 = open_door_to_target;
        position_x = position->x.w.i;
        initialize_player_entity_callbacks(entity->unk72, position_x, position->y.w.i);
    }
}

// Increase the object's ramp value, then finalize and change state at the limit.
void open_door_to_target(TownObjectRecord *object, TownObjectRecord *context) {
    u16 rampValue;

    rampValue = object->unk_6E + 0x40;
    object->unk_6E = rampValue;
    if ((s16) rampValue >= 0x400) {
        object->unk_6E = 0x400U;
        change_door_map(object, context->unk_48);
        object->unk_50.as_pm = &door_no_op;
    }
}

/* Returns without performing any work. */
void door_no_op(void) {
}

/* Increase the door opening angle and switch handlers when fully open. */
void advance_door_open_angle(TownObjectRecord *door) {
    u16 opening_angle;

    opening_angle = door->unk_6E + 0x40;
    door->unk_6E = opening_angle;
    if ((s16) opening_angle >= 0x400) {
        door->unk_6E = 0x400U;
        door->unk_50.as_pv = &tick_door_open_countdown;
    }
}

/* Decrement the countdown and switch to advance_door_close_angle when it expires. */
void tick_door_open_countdown(TownObjectRecord *state) {
    u16 countdown;

    countdown = state->timer - 1;
    state->timer = countdown;
    if ((countdown << 0x10) <= 0) {
        state->unk_50.as_pv = &advance_door_close_angle;
    }
}

/* Decrease the door opening angle and switch handlers when closed. */
void advance_door_close_angle(TownObjectRecord *door) {
    u16 opening_angle;

    opening_angle = door->unk_6E - 0x40;
    door->unk_6E = opening_angle;
    if ((opening_angle << 0x10) <= 0) {
        door->unk_6E = 0U;
        door->unk_50.as_pv = &check_door_entry_and_open;
    }
}

/* Finds the first node with the required key and value whose 0x400 flag is clear. */
void *find_door_keyed_node(s32 requested_value)
{
    Node *node;
    Node *next_node;
    s32 node_key;
    s32 required_node_key;
    TownObjectRecord *node_data;
    void *result;

    node = active_node_list_head.head;
    if (node != 0) {
        required_node_key = (s32)&update_door_object;
        do {
            node_key = node->field_10;
            next_node = node->next;
            if (node_key < 0) {
                if (!(node->flags & 0x400)) {
                    node_data = NODE_BODY(node);
                    if ((node_key == required_node_key) && (node_data->unk_48 == requested_value)) {
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
    TownObjectRecord *door;

    door_object = find_door_keyed_node(door_id);
    door = NODE_BODY(door_object);
    if (door_object != 0) {
        door->unk_50.as_pv = &advance_door_open_angle;
        door->timer = demo_angle;
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
    TownObjectRecord *door;

    door_object = find_door_keyed_node(&D_800D4404);
    door = NODE_BODY(door_object);
    if (door_object != 0) {
        door->unk_90 = 6;
        door->unk_50.as_pv = &start_door_transition_effect;
    }
}

/* Check interaction conditions, apply the target value, and trigger a positional effect. */
void check_door_entry_and_change_map(void *actor, void *target, void *position_arg) {
    ObjectPosition *position;

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
    position = position_arg;
    initialize_entity_handlers_and_position(*(s16 *)((u8 *)actor + 0x72), position->x.w.i, position->y.w.i);
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
            map_index = find_target_index_in_list();
        } else {
            map_index = get_player_homerank();
        }
        map_source = (void *)map_table[map_index];
    }
    change_map(map_source);
}

/* Update the entity step state and switch handlers when the result is zero. */
void create_door_transition_objects(void *entity_arg, TownObjectRecord *unused_context, void *update_context, SpriteFrameState *unused_data) {
    TownObjectRecord *entity = entity_arg;
    s16 step_result;

    step_result = create_display_object_series(entity, entity->unk_98, update_context, entity->unk_90);
    entity->unk_90 = step_result;
    if ((step_result << 0x10) == 0) {
        entity->unk_50.as_pv = &start_door_entry_or_wait;
    }
}

/* Selects the door's entrance or waiting handler according to whether the entry count is below six. */
void start_door_entry_or_wait(S_800A0C30_0 *script_state, TownObjectRecord *collision_body, ObjectPosition *position) {
    if (check_door_input_and_angle(script_state, collision_body) != 0) {
        if (count_used_item_slots() < 6) {
            script_state->unk_90 = 6;
            script_state->unk_50 = &start_door_transition_effect;
            initialize_entity_handlers_and_position(script_state->unk_72, position->x.w.i, position->y.w.i);
            return;
        }
        script_state->unk_50 = &resume_door_entry_when_script_idle;
        set_player_block_value(script_state->unk_72);
    }
}

/* Set the object handler when service_script_controller returns zero. */
void resume_door_entry_when_script_idle(S_800A0CC0_0 *object, s32 value_1, s32 value_2, s32 value_3) {
    if (service_script_controller() == 0) {
        object->unk_50 = &start_door_entry_or_wait;
    }
}

/* Updates the object's state and applies completion effects when it reaches zero. */
void start_door_transition_effect(u8 *object, s32 unused, s32 state_id, s32 state_arg) {
    TownObjectRecord *door = (TownObjectRecord *)object;
    s16 state;

    state = initialize_object_items_in_reverse(&door_transition_state, state_id, door->unk_90);
    door->unk_90 = state;
    if ((s32)(state << 0x10) == 0) {
        no_op_callback_a(&door_transition_state, state_id, state_arg);
        door->unk_50.as_pv = update_door_transition_spin;
        load_indexed_resource_package(0);
        sound_set_cd_cue_parameters(0, cd_cue_base, 0x0600065E, 0x030008B6);
        SD_Call(0x300);
    }
}

/* Advance the state counter and apply the next state when the check succeeds. */
void update_door_transition_spin(TownObjectRecord *state, TownObjectRecord *unused_context, s32 context_a, s32 context_b) {
    step_door_transition_sprite(&door_transition_state, context_a, context_b);
    state->unk_6E = (u16)(state->unk_6E + 0x10);
    if (animate_spinning_shrinking_object(&door_transition_state, context_a, context_b) != 0) {
        state->timer = 0x20;
        state->unk_50.as_pv = &tick_door_countdown;
    }
}

/* Update the countdown and reset the object's state when it expires. */
void tick_door_countdown(TownObjectRecord *object, TownObjectRecord *source, s32 update_arg_a, s32 update_arg_b) {
    u16 remaining_count;

    step_door_transition_sprite(&door_transition_state, update_arg_a, update_arg_b);
    remaining_count = object->timer - 1;
    object->timer = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        change_door_map(object, source->unk_48);
        object->unk_50.as_pv = &door_no_op;
        into_dn_door_jobs();
    }
}

/* into_dn_door_jobs: Run dungeon entrance setup and reset entry flags. */
void into_dn_door_jobs(void) {
    clear_resident_bit_patterns();
    clear_resident_bitmap_bit(sn_mam_pan_give);
    apply_building_pending_updates();
    sync_resident_flag_pairs();
    current_dungeon_floor = 1;
    runtime_dispatch_state.flags16 = 0;
    system_update_flags &= 0xFFF8;
}

/* Tests the input and object angle against either supported global state. */
s32 check_door_input_and_angle(Rec_func_800A0668_arg0 *object, TownObjectRecord *collision_body) {
    if (get_box_overlap_axis(collision_body, &town_actor_control) != 0) {
        s32 *global_base = &scene_object_payload_alias;
        s32 global_angle = ((u16)((TownObjectRecord *)global_base)->unk_10) & 0xFFF;
        s32 object_angle = object->unk_72 & 0xFFF;

        if ((u32) ((object_angle - global_angle) + 0x3FF) < 0x7FFU) {
            if ((scene_object_payload_alias == (s32)dispatch_actor_input_actions) || (scene_object_payload_alias == (s32)update_actor_input_and_interaction)) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}
