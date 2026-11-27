/* Handles door collision, opening and closing, entrance interactions, and map changes. */
#include "script_symbols.h"
#include "shared/object_flags.h"
#include "town/map/door.h"
#include "town/menu/animation.h"
#include "town.h"
#include "town/map.h"
#include "engine/script.h"
#include "town/person.h"
#include "town/player/input.h"

/* Test the object status, reversing the result when the linked record has bit 3 set. */
s32 check_door_status_inverted(TownObjectRecord *door) {
    if ((((S_800A0668_1 *)door->spawn_active)->unk_01 & 8) != 0) {
        return door->item_slot == 0;
    }
    return door->item_slot != 0;
}

/* Initialize the record and select its handler according to its variant. */
void initialize_door_variant(TownObjectRecord *record_data, ObjectPosition *position, struct SpriteFrameState *unused_sprite) {
    u32 variant;

    variant = ((u8)(record_data->state_index));
    NODE_HEADER(record_data)->update_callback = update_door_object;
    {
        union { void (*callback)(); s32 value; } handler;

        if (variant == 1) {
            handler.value = 2;
            record_data->unk_90 = handler.value;
            handler.callback = &create_door_transition_objects;
            record_data->origin_heading = 0;
        } else if (variant == 0) {
            handler.callback = &check_door_entry_and_change_map;
        } else {
            handler.callback = &create_door_shared_object;
            record_data->origin_heading = 0;
        }
        record_data->state_callback.as_pm = handler.callback;
    }
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->position = position;
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_1C = &D_800D09E0;
    record_data->phase = 0;
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
void create_door_shared_object(TownObjectRecord *object, TownObjectRecord *unused_context, ObjectPosition *origin, SpriteFrameState *unused_data) {
    u8 *active_flag = object->spawn_active;
    u8 status_byte = ((u8)(object->state_index));

    if (create_default_display_object(object, active_flag, origin, status_byte) != 0) {
        object->state_callback.as_s32 = (s32) &check_door_entry_and_open;
    }
}

/* Set the entity effect and emit it at the supplied position when the checks pass. */
void check_door_entry_and_open(TownObjectRecord *entity, TownObjectRecord *collision_body, ObjectPosition *position) {
    s32 position_x;
    if ((s16)entity->phase == 0) {
        if (check_door_status_inverted(entity) != 0) {
            return;
        }
    } else if (check_door_status_inverted(entity) == 0) {
        return;
    }
    if (check_door_input_and_angle(entity, collision_body) != 0) {
        entity->state_callback.as_pm = open_door_to_target;
        position_x = position->x.w.i;
        initialize_player_entity_callbacks(entity->heading, position_x, position->y.w.i);
    }
}

// Increase the object's ramp value, then finalize and change state at the limit.
void open_door_to_target(TownObjectRecord *object, TownObjectRecord *context) {
    u16 rampValue;

    rampValue = object->origin_heading + 0x40;
    object->origin_heading = rampValue;
    if ((s16) rampValue >= 0x400) {
        object->origin_heading = 0x400U;
        change_door_map(object, context->creation_argument);
        object->state_callback.as_pm = &door_no_op;
    }
}

/* Returns without performing any work. */
void door_no_op(void) {
}

/* Increase the door opening angle and switch handlers when fully open. */
void advance_door_open_angle(TownObjectRecord *door) {
    u16 opening_angle;

    opening_angle = door->origin_heading + 0x40;
    door->origin_heading = opening_angle;
    if ((s16) opening_angle >= 0x400) {
        door->origin_heading = 0x400U;
        door->state_callback.as_pv = &tick_door_open_countdown;
    }
}

/* Decrement the countdown and switch to advance_door_close_angle when it expires. */
void tick_door_open_countdown(TownObjectRecord *state) {
    u16 countdown;

    countdown = state->timer - 1;
    state->timer = countdown;
    if ((countdown << 0x10) <= 0) {
        state->state_callback.as_pv = &advance_door_close_angle;
    }
}

/* Decrease the door opening angle and switch handlers when closed. */
void advance_door_close_angle(TownObjectRecord *door) {
    u16 opening_angle;

    opening_angle = door->origin_heading - 0x40;
    door->origin_heading = opening_angle;
    if ((opening_angle << 0x10) <= 0) {
        door->origin_heading = 0U;
        door->state_callback.as_pv = &check_door_entry_and_open;
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
            node_key = node->update_callback;
            next_node = node->next;
            if (node_key < 0) {
                if (!(node->flags & 0x400)) {
                    node_data = NODE_BODY(node);
                    if ((node_key == required_node_key) && (node_data->creation_argument == requested_value)) {
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
        door->state_callback.as_pv = &advance_door_open_angle;
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
        door->state_callback.as_pv = &start_door_transition_effect;
    }
}

/* Check interaction conditions, apply the target value, and trigger a positional effect. */
void check_door_entry_and_change_map(TownObjectRecord *actor, TownObjectRecord *target, ObjectPosition *position) {
    if ((s16)actor->phase == 0) {
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
    change_door_map(actor, target->creation_argument);
    actor->state_callback.as_pm = &door_no_op;
    initialize_entity_handlers_and_position(actor->heading, position->x.w.i, position->y.w.i);
}

/* Changes maps using direct map data or a selected table entry. */
void change_door_map(TownObjectRecord *door, s32 *map_table) {
    u8 selection_mode;
    struct InputRecord *destination;

    selection_mode = door->variant;
    if (selection_mode == 0) {
        destination = (struct InputRecord *)map_table;
    } else {
        s32 map_index;

        if (selection_mode == 1) {
            map_index = find_target_index_in_list();
        } else {
            map_index = get_player_homerank();
        }
        destination = (struct InputRecord *)map_table[map_index];
    }
    change_map(destination);
}

/* Update the entity step state and switch handlers when the result is zero. */
void create_door_transition_objects(TownObjectRecord *entity, TownObjectRecord *unused_context, ObjectPosition *origin, SpriteFrameState *unused_data) {
    s16 step_result;

    step_result = create_display_object_series(entity, entity->spawn_active, origin, entity->unk_90);
    entity->unk_90 = step_result;
    if ((step_result << 0x10) == 0) {
        entity->state_callback.as_pv = &start_door_entry_or_wait;
    }
}

/* Selects the door's entrance or waiting handler according to whether the entry count is below six. */
void start_door_entry_or_wait(TownObjectRecord *script_state, TownObjectRecord *collision_body, ObjectPosition *position) {
    if (check_door_input_and_angle(script_state, collision_body) != 0) {
        if (count_used_item_slots() < 6) {
            script_state->unk_90 = 6;
            script_state->state_callback.as_pm = &start_door_transition_effect;
            initialize_entity_handlers_and_position(script_state->heading, position->x.w.i, position->y.w.i);
            return;
        }
        script_state->state_callback.as_pm = &resume_door_entry_when_script_idle;
        set_player_block_value(script_state->heading);
    }
}

/* Set the object handler when service_script_controller returns zero. */
void resume_door_entry_when_script_idle(TownObjectRecord *object, TownObjectRecord *unused_context, ObjectPosition *unused_position, SpriteFrameState *unused_sprite) {
    if (service_script_controller() == 0) {
        object->state_callback.as_pm = &start_door_entry_or_wait;
    }
}

/* Updates the object's state and applies completion effects when it reaches zero. */
void start_door_transition_effect(TownObjectRecord *door, TownObjectRecord *unused_context, ObjectPosition *position, SpriteFrameState *sprite) {
    s16 state;

    state = initialize_object_items_in_reverse(&door_transition_state, position, door->unk_90);
    door->unk_90 = state;
    if ((s32)(state << 0x10) == 0) {
        no_op_callback_a(&door_transition_state, position, sprite);
        door->state_callback.as_pv = update_door_transition_spin;
        load_indexed_resource_package(0);
        sound_set_cd_cue_parameters(0, cd_cue_base, 0x0600065E, 0x030008B6);
        SD_Call(0x300);
    }
}

/* Advance the state counter and apply the next state when the check succeeds. */
void update_door_transition_spin(TownObjectRecord *state, TownObjectRecord *unused_context, ObjectPosition *position, SpriteFrameState *sprite) {
    step_door_transition_sprite(&door_transition_state, position, sprite);
    state->origin_heading = (u16)(state->origin_heading + 0x10);
    if (animate_spinning_shrinking_object(&door_transition_state, position, sprite) != 0) {
        state->timer = 0x20;
        state->state_callback.as_pv = &tick_door_countdown;
    }
}

/* Update the countdown and reset the object's state when it expires. */
void tick_door_countdown(TownObjectRecord *object, TownObjectRecord *source, ObjectPosition *position, SpriteFrameState *sprite) {
    u16 remaining_count;

    step_door_transition_sprite(&door_transition_state, position, sprite);
    remaining_count = object->timer - 1;
    object->timer = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        change_door_map(object, source->creation_argument);
        object->state_callback.as_pv = &door_no_op;
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
s32 check_door_input_and_angle(TownObjectRecord *object, TownObjectRecord *collision_body) {
    if (get_box_overlap_axis(collision_body, &town_actor_control) != 0) {
        s32 *global_base = &scene_object_payload_alias;
        s32 global_angle = ((u16)((TownObjectRecord *)global_base)->player_facing) & 0xFFF;
        s32 object_angle = object->heading & 0xFFF;

        if ((u32) ((object_angle - global_angle) + 0x3FF) < 0x7FFU) {
            if ((scene_object_payload_alias == (s32)dispatch_actor_input_actions) || (scene_object_payload_alias == (s32)update_actor_input_and_interaction)) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}
