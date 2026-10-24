/* Update position displacement dispatch active entity handler.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01131 - CL:town/func_800A1A60, CL:town/func_800A1D2C, CL:town/func_800A1D60.
 */
#include "town/shop/position/update_position_displacement_dispatch_active_entity_handler_g01131.h"

/* Update position and displacement, then dispatch the active entity handler. */
void update_position_displacement_dispatch_active_entity_handler(Rec_func_8009EE9C_arg0 *entity, s32 entity_id, S_8009EE9C_0 *motion, s32 context) {
    s32 previous_pos;

    previous_pos = motion->unk_08;
    motion->unk_08 = (u32) (entity->unk_A0 + (rsin(entity->unk_6C) << 6) + 0xFFFC0000);
    entity->unk_6C = (s16) ((u16) entity->unk_6C + 0x40);
    motion->unk_14 = (s32) (motion->unk_08 - previous_pos);
    if (((s32 *)town_target_record)[0] == entity_id) {
        if (((s32 *)scene_object_payload_alias)[0] == &town_timed_state_address) {
            initialize_the_entity_s_action_copy_selected_state_hex_13(entity, ((s32 *)town_target_record)[0], motion, context);
            return;
        }
        if (((s32 *)scene_object_payload_alias)[0] == D_80093524) {
            call_callee_80033_d_08_set_handler(entity, ((s32 *)town_target_record)[0], motion, context);
        }
    }
}

/*
 * Moves halfway toward the view reference with a 0x200000 Z offset, then resolves the item after
 * countdown expiry. On success updates slot/type flags and clears the linked signal; otherwise
 * restores saved X/Y and initializes the type-dependent motion state.
 */
void update_motion_toward_target_resolves_entity_countdown_expires(void *entity, s32 context, ObjectPosition *motion, s32 mode) {
    s32 result[5];
    s8 *linked_flag;
    s8 *clear_flag;
    u16 ticks_left;
    u32 delta_y;
    s32 offset_z;
    u8 slot;

    motion->velocity_x = (s32)((s32)(view_reference_entity.x.v - motion->x.v) / 2);
    delta_y = view_reference_entity.y.v - motion->y.v;
    motion->velocity_y = (s32)((s32)(delta_y + (delta_y >> 31)) >> 1);
    offset_z = motion->z.v + 0x200000;
    motion->velocity_z = (s32)((s32)(view_reference_entity.z.v - offset_z) / 2);
    add_motion_deltas_to_position(motion);
    ticks_left = ((Rec_D_800CFCB4 *)entity)->unk_6C.as_u16 - 1;
    ((Rec_D_800CFCB4 *)entity)->unk_6C.as_u16 = ticks_left;
    if ((ticks_left << 16) <= 0) {
        slot = ((Rec_D_800CFCB4 *)entity)->unk_95;
        if (process_the_item_index_available_report_success(entity, context, motion, mode, result) != 0) {
            if (((Rec_D_800CFCB4 *)entity)->unk_4D.as_u8 == 0x13) {
                u8 *state_table = (u8 *)0x80010000;
                s32 record_index = state_table[slot * 4 + 0x983] & 0x3F;
                state_table[record_index * 0x54 + 0xAC4] = 1;
                linked_flag = ((Rec_D_800CFCB4 *)entity)->unk_98;
                if (linked_flag != NULL) {
                    *linked_flag = 0;
                }
                D_800D09C8[0] = 0;
                clear_flag = linked_flag;
            } else {
                (*(s32 *)((u8 *)((slot * 4)) + (0x80010980))) = 0;
                clear_flag = ((Rec_D_800CFCB4 *)entity)->unk_98;
                if (clear_flag != NULL) {
                    *clear_flag = 0;
                }
            }
            dispatch_paired_table_values(clear_flag);
            return;
        }
        motion->x.v = 0;
        motion->y.v = 0;
        motion->x.w.i = ((Rec_D_800CFCB4 *)entity)->unk_84;
        motion->y.w.i = ((Rec_D_800CFCB4 *)entity)->unk_86;
        initialize_entity_flags_transform_type_dependent_variant(entity, context, motion, mode);
    }
}

/*
 * Sets both state bytes, clears all motion deltas, sets Z to -0x200000, and installs D_8009EE9C
 * with a random 12-bit phase. Selects variant 0x58 for type 0x12 or 0x59 otherwise.
 */
void initialize_entity_flags_transform_type_dependent_variant(void *entity, void *state, void *transform, s32 unused)
{
    s32 variant_id;
    u8 *entity_bytes = entity;
    *(((s8 *) state) + 0x14) = 1;
    *(((s8 *) state) + 0x15) = 1;
    *((s32 *) (((u8 *) transform) + 0xC)) = 0;
    *((s32 *) (((u8 *) transform) + 0x10)) = 0;
    *((s32 *) (((u8 *) transform) + 0x14)) = 0;
    *((s32 *) (entity_bytes + 0xA0)) = 0xFFE00000;
    *((s32 *) (((u8 *) transform) + 8)) = 0xFFE00000;
    *((u8 **) (entity_bytes + 0x50)) = D_8009EE9C;
    *((s16 *) (entity_bytes + 0x6C)) = scale_random_to_unsigned_halfword_limit(0x1000);
    variant_id = 0x12;
    if ((*((u8 *) (entity_bytes + 0x4D))) != variant_id) {
        *((s32 *) (entity + 0x60)) = 0x59;
    }
    else {
        *((s32 *) (entity + 0x60)) = 0x58;
    }
}

/* Initialize the entity's action and copy its selected record for state 0x13. */
void initialize_the_entity_s_action_copy_selected_state_hex_13(Rec_func_8009EE9C_arg0 *entity, S_8009F1C0_0 *action, void *unused_motion, s32 unused_context)
{
    u8 state;
    void *callback;

    action->unk_14 = 4;
    callback = &D_8009EF88;
    action->unk_15 = 0;
    state = entity->unk_4D;
    entity->unk_50.as_pv = callback;
    entity->unk_6C = 8;

    if (state == 0x13) {
        Record84 *records = (Record84 *)0x80010A80;
        u8 *record_map = (u8 *)0x80010000;

        (*((Record84 *)town_slot_snapshot)) = records
        [record_map[entity->unk_95 * 4 + 0x983] & 0x3F];
    }
}

/* get_target_itemp: Prepares the target item and returns its item data pointer, or zero. */
s32 get_target_itemp(void) {
    u8 *target_object = (u8 *)((void * *)town_target_record)[0];

    if (target_object != 0) {
        s32 item_type = 4;

        if (target_object[0x14] == item_type) {
            return (s32)(target_object + 0x4C);
        }
        return 0;
    }
    return 0;
}

/*
 * Sets target Z from the saved origin plus a sine offset and advances phase by 0x40. For the
 * matching active event and D_800935BC payload, processes input, allocates callbacks, plays sound
 * 0x513, and synchronizes town state.
 */
void update_the_target_offset_advance_phase_handle_active_event(void *state, s32 event_id, DelayMotionZ *target, s32 context) {
    s32 active_event;

    target->unk_08 = (s32) (((Rec_func_80094268_arg0 *)state)->unk_A0
        + (rsin(((Rec_func_80094268_arg0 *)state)->unk_6C.as_s16) << 7));
    (*(s16 *)((u8 *)state + 0x6C)) = (s16) ((u16) ((Rec_func_80094268_arg0 *)state)->unk_6C.as_s16 + 0x40);
    active_event = (*((s32 *)town_target_record));
    if ((active_event == event_id) && ((*((s32 *)scene_object_payload_alias)) == &D_800935BC)) {
        check_adjusted_input_indices(target);
        allocate_object_with_callbacks(target);
        SD_Call(0x513);
        initialize_the_town_entity_synchronize_slot_state(state, active_event, (s32)(target), (void *)(context));
    }
}

/*
 * Jitters Z by -8 through 7 fixed-point units and pulses opposite X/Y scales around 0x1000 using a
 * countdown-driven sine wave. Restores both scales and initializes type-dependent motion when the
 * countdown expires.
 */
void handle_jitter_position_pulse_scale_until_countdown_expires(Rec_D_800CFCB4 *state, s32 context, EntityRec *position, S_8009F374_2 *scale) {
    s16 ticks_left;
    s32 scale_x_wave;
    s32 scale_y_wave;

    position->z.v = (s32) (state->unk_A0 + (((scale_random_to_unsigned_halfword_limit(0x10) & 0xFFFF) - 8) << 0x10));
    scale_x_wave = rsin(state->unk_6C.as_s16 * 0x199);
    scale->unk_1C = (s16) ((scale_x_wave / 4) + 0x1000);
    scale_y_wave = rsin(state->unk_6C.as_s16 * 0x199);
    scale->unk_1E = (s16) (0x1000 - (scale_y_wave / 4));
    ticks_left = (u16) state->unk_6C.as_s16 - 1;
    state->unk_6C.as_s16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        scale->unk_1E = 0x1000;
        scale->unk_1C = 0x1000;
        initialize_entity_flags_transform_type_dependent_variant(state, context, position, scale);
    }
}

/* Call unlink_node_if_registered and set the record handler. */
void call_callee_80033_d_08_set_handler(Rec_func_8009EE9C_arg0 *record, s32 value, void *unused_motion, s32 unused_context) {
    unlink_node_if_registered(record);
    record->unk_50.as_pm = &D_8009F2A8;
}

/*
 * Builds an 0x54-byte actor snapshot and packed entry for the selected town slot, synchronizes
 * type/index fields, and applies the mode-selected object state. Installs the jitter/pulse
 * callback with a ten-tick countdown.
 */
void initialize_the_town_entity_synchronize_slot_state(Rec_func_80094268_arg0 *entity, s32 unused_arg1, s32 unused_arg2, void *context) {
    void *stored_entry;
    s32 unused_value;
    s32 record_offset;
    s32 record_value;
    s32 slot_index;
    register s32 record_index;
    void *source_entry;
    S_8009F4C0_2 *slot_flags;
    S_8009F4C0_1 *slot_state;
    void *data_base;

    slot_index = entity->unk_95;
    register_node_if_unregistered(entity, (project_sprite_chain));
    slot_state = (slot_index * 4) + 0x80010000;
    slot_state->unk_981 = 0x13;
    memset(&town_actor_scratch, 0, 0x54);
    func_80042640(&town_actor_scratch, entity->unk_4C);
    record_index = slot_index;
    apply_actor_template_and_direction(&town_actor_scratch, entity->unk_4C, 0);
    build_entity_slot_snapshot(&(*((struct TownCopy84 *)town_slot_snapshot)), &town_actor_scratch);
    *(struct TownCopy84 *)((u8 *)0x80010A80 + (record_index * 0x54)) = (*((struct TownCopy84 *)town_slot_snapshot));
    stored_entry = (void *) 0x80010AB4;
    record_offset = record_index * 0x54;
    stored_entry = (u8 *)stored_entry + record_offset;
    source_entry = runtime_get_mode_indexed_value(entity->unk_4C);
    *(struct PackedTownEntry *)stored_entry = *(struct PackedTownEntry *)source_entry;
    data_base = (void *) 0x80010000;
    slot_flags = (slot_index * 4) + (u8 *)data_base;
    slot_flags->unk_983 = (u8) ((slot_flags->unk_983 & 0xC0) | record_index);
    ((S_8009F4C0_3 *)((record_offset + (u8 *)data_base)))->unk_AC3 = slot_index;
    entity->unk_4D = (u8) slot_flags->unk_981;
    entity->unk_4F = (u8) slot_flags->unk_983;
    record_index = (u8) (((S_8009F4C0_4 *)(((entity->unk_95 * 4) + (u8 *)data_base)))->unk_983 & 0x3F);
    record_value = ((S_8009F4C0_5 *)(((record_index * 0x54) + (u8 *)data_base)))->unk_A94;
    func_8003E188(entity->unk_4C, 1);
    set_object_state_for_mode(entity, context, entity->unk_4C, record_value);
    entity->unk_50.as_pm = &handle_jitter_position_pulse_scale_until_countdown_expires;
    entity->unk_6C.as_s16 = 0xA;
}
