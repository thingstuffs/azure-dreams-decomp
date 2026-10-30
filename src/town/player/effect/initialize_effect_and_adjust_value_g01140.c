#include "shared/sprite_frame_state.h"
/* Initialize effect and adjust value.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01140 - CL:town/func_800A7E6C, CL:town/func_800A8134.
 */
#include "town/player/effect/initialize_effect_and_adjust_value_g01140.h"
#include "shared/game_work.h"
#include "town/player/effect.h"
#include "town/player.h"
#include "town/player/position.h"
#include "town/map/object.h"
#include "town/scene/motion.h"
#include "town/player/motion.h"
#include "engine/graphics.h"
#include "engine/node.h"
#include "engine/window.h"

/* Initialize the object and adjust its record value before final setup. */
void initialize_effect_and_adjust_value(void *object, EntityRec *record, s32 init_value) {
    s32 delta;

    ((S_800A55CC_0_pre *)object)[-1].unk_00 = ((M2C_UNK *)D_800903FC);
    initialize_actor_action_state(object, record, init_value);
    {
        delta = 0x10000;
        init_value = record->z.v;
        record->z.v =
            (init_value + delta) - D_800D0CC0[0];
        register_node_if_unregistered(object, player_motion_draw_address);
    }
}

/* Updates the record, invokes its handler, clamps values, and dispatches follow-up processing. */
void update_effect_record_and_dispatch(void *handler, ObjectPosition *record, s32 context) {
    apply_the_enabled_movement_offsets_adding_z_offset_only_positive((struct IntVector3 *)(record));
    update_the_s_field_10_using_callee_8008_fe_90(&town_motion_list);
    add_motion_deltas_to_position(record);
    update_object_and_clear_status_fields(record);
    store_position_and_compute_delta((s32 *)(record));
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(&town_actor_control, record);
    ((Rec_func_8009431C_arg0 *)handler)->unk_00.as_x78b360(handler, record, context);
    if (!(((S_800A5638_0_pre *)handler)[-1].unk_0E & 0x8000)) {
        if (record->y.v <= 0x06500000) {
            record->y.v = 0x06500000;
            record->velocity_y = 0x180000;
            if (record->z.v > 0) {
                record->z.v = 0;
            }
        }
        if (((S_800A5638_0_pre *)handler)[-1].unk_00 == ((s32 *)D_800903FC)) {
            process_scene_record_update(handler, record, (void *)(context));
            return;
        }
        turn_entity_toward_target(handler, record, (void *)(context));
    }
}

/* Turn the entity toward its target angle and update its directional sprite. */
void turn_entity_toward_target(void *entity, void *transform, void *sprite) {
    GameWork *input_state;
    void *transform_arg;
    s32 direction;
    s32 current_angle;
    s32 target_angle;

    transform_arg = transform;
    input_state = &g_game_work;
    clear_motion_along_blocked_directions_update_affected_axes(transform_arg);
    {
        void *entity_type;

        entity_type = *(void **)entity;
        if (entity_type == (u8 *)&D_800A5A98 && (input_state->buttons & 0x2000)) {
            target_angle = *(s16 *)((u8 *)entity + 0x10);
            current_angle = *(s16 *)((u8 *)entity + 0x18);
            target_angle -= 0x200;
            *(s16 *)((u8 *)entity + 0x18) = step_angle_12_toward(current_angle, target_angle, 0x200);
        } else if (entity_type == (u8 *)&D_800A5A98 && (input_state->buttons & 0x8000)) {
            target_angle = *(s16 *)((u8 *)entity + 0x10);
            current_angle = *(s16 *)((u8 *)entity + 0x18);
            target_angle += 0x200;
            *(s16 *)((u8 *)entity + 0x18) = step_angle_12_toward(current_angle, target_angle, 0x200);
        } else {
            current_angle = *(s16 *)((u8 *)entity + 0x18);
            target_angle = *(s16 *)((u8 *)entity + 0x10);
            *(s16 *)((u8 *)entity + 0x18) = step_angle_12_toward(current_angle, target_angle, 0x200);
        }
    }
    direction = view_relative_angle_sector(*(s16 *)((u8 *)entity + 0x18));
    if (*(s16 *)((u8 *)entity + 0x12) != direction) {
        texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(sprite,
                      *(u8 *)(*(u8 **)((u8 *)entity + 0x1C) + direction),
                      *(s8 *)((u8 *)sprite + 4), 0);
        *(s16 *)((u8 *)entity + 0x12) = direction;
    }
    {
        s16 *flip_table = town_scene_effect_flips;
        u16 sprite_flags;

        if (flip_table[direction] != 0) {
            *(u16 *)((u8 *)sprite + 0x14) |= 1;
        } else {
            *(u16 *)((u8 *)sprite + 0x14) &= 0xFFFE;
        }
    }
    step_actor_animation(sprite, 0);
    {
        u8 *render_state = town_position_reference_state;

        copy_entity_record_fields(render_state, transform);
        *(s32 *)(render_state + 8) = 0;
    }
}

/*
 * Returns the integer Z coordinate times 0xC00 plus 0x30000 when fixed-point Z exceeds -0x400000;
 * returns zero otherwise.
 */
s32 compute_height_based_offset(EntityRec *state) {
    if (state->z.v > -0x400000) {
        return (state->z.w.i * 0xC00) + 0x30000;
    }
    return 0;
}

/* Updates the object and interpolates town angles before advancing the state. */
void update_object_view_transition(S_800A58CC_2 *state_arg, void *object) {
    s16 threshold;
    s32 pitch_step;
    s16 yaw;
    u8 * object_ref;
    s32 target_yaw;
    s32 yaw_delta;
    s32 pitch;
    u16 ticks;
    GameWork *town;
    ObjectPosition *coords;

         /* MATCH: Order the s2 parameter copy before the s0 copy. */
    object_ref = (u8 *)object;
    town = &g_game_work;
    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile((void *) object_ref);
    threshold = select_the_smaller_position_query_result_capped_n_64_writes_associated((void *) object_ref, &position_query_scratch);
    if (((S_800A58CC_0 *)((void *) object_ref))->unk_0A >= threshold) {
        compute_and_clamps_vector_based_adjustment_updates_town((void *) object_ref, threshold, (struct TownVec **)(&position_query_scratch));
    } else {
        if (D_800D0000[-0x311] != 0) {
            ((S_800A58CC_0 *)((void *) object_ref))->unk_14 = 0;
            clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2((void *) object_ref);
        } else {
            add_hex_20000_s_signed_offset_hex_14((void *) object_ref);
        }
    }
    coords = &view_reference_entity;
    if (check_masked_value_in_current_range(read_map_cell_at_world_position(coords->x.w.i, coords->y.w.i) & 0xFFFF) != 0) {
        pitch_step = ((S_800A58CC_0 *)((void *) object_ref))->unk_14 - compute_height_based_offset((void *) object_ref);
        ((S_800A58CC_0 *)((void *) object_ref))->unk_14 = pitch_step;
    }
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero((void *) object_ref);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero((void *) object_ref);
    target_yaw = (state_arg->unk_10 - 0x800) & 0xFFF;
    yaw = step_angle_12_toward(town->view.camera_rotation.parts.viewAngle, target_yaw, 0x80);
    town->view.camera_rotation.parts.viewAngle = yaw;
    yaw_delta = abs((yaw & 0xFFF) - target_yaw);
    if (yaw_delta < 0x80) {
        town->view.camera_rotation.parts.viewAngle = target_yaw;
    }
    ticks = state_arg->unk_0A.s - 1;
    state_arg->unk_0A.s = ticks;
    {
        s32 shifted_ticks;
        s32 ticks_left;
        shifted_ticks = (s32) ticks << 16;
        ticks_left = shifted_ticks >> 16;
        pitch_step = -0x2B0;
        if (ticks_left <= 0) {
            state_arg->unk_0A.u = 0;
        }
        pitch = ticks_left > 0
            ? (pitch_step -= town->view.camera_rotation.parts.camera_rotation_x, pitch_step /= ticks_left,
               ((u16)town->view.camera_rotation.parts.camera_rotation_x) + pitch_step)
        : -0x2B0;
        town->view.camera_rotation.parts.camera_rotation_x = pitch;
    }
    if ((state_arg->unk_0A.u == 0) && (town->view.camera_rotation.parts.viewAngle == target_yaw)) {
        state_arg->unk_0A.u = 0;
        state_arg->unk_00 = &D_800A5A98;
    }
}

/* Update actor movement, height, turning, and action state from input. */
void update_actor_movement_and_actions(State *state, Actor *actor) {
    GameWork *input;
    s32 speed;
    s16 height_limit;
    s32 direction;
    s32 world_value;
    s32 sound_period;

    input = &g_game_work;
    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile((struct EntityRec *)(actor));

    state->timer--;
    if ((s16)state->timer <= 0) {
        state->timer = scale_random_to_unsigned_halfword_limit(3) + 5;
        spawn_directional_effects(actor, (u16)scale_random_to_unsigned_halfword_limit(2) + 2);
    }

    direction = (((u16)input->view.camera_rotation.parts.viewAngle) + 0x800) & 0xFFF;
    *(u16 *)((u8 *)state + 0x10) = direction;

    if (((u32)input->buttons) & 0x20) {
        add_a_directional_step_vector_scale_down_exceeds_length_limit(direction, (*((s32 *)town_movement_speed)), actor);
        spawn_directional_effects(actor, (u16)scale_random_to_unsigned_halfword_limit(1));
    }

    if (((u32)input->buttons) & 0x10) {
        move_both_components_toward_zero_direction_dependent_steps_clamping_zero((struct EntityRec *)(actor));
        if ((((u32)input->buttons) & 0x30) == 0x20) {
            move_both_components_toward_zero_direction_dependent_steps_clamping_zero((struct EntityRec *)(actor));
        }
    } else {
        move_both_components_toward_zero_direction_dependent_steps_clamping_zero((struct EntityRec *)(actor));
    }
    height_limit = select_the_smaller_position_query_result_capped_n_64_writes_associated(actor, &position_query_scratch);
    if (actor->height >= height_limit) {
        compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(actor), height_limit, (struct TownVec **)(&position_query_scratch));
    } else if ((&(*((u8 *)town_blocked_directions)))[1] != 0) {
        actor->value = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2((s32 *)(actor));
    } else {
        add_hex_20000_s_signed_offset_hex_14(actor);
    }
    world_value = read_map_cell_at_world_position(view_reference_entity.x.w.i, view_reference_entity.y.w.i);
    if (check_masked_value_in_current_range((u16)world_value) != 0) {
        actor->value -= compute_height_based_offset((struct EntityRec *)(actor));
    }

    speed = runtime_estimate_vector_length(actor->x, actor->y);
    if ((*((s32 *)town_movement_speed)) != 0) {
        {
            s32 speed_delta;
            speed_delta = (*((s32 *)town_movement_speed)) - speed;
            sound_period = (((speed_delta < 0 ? -speed_delta : speed_delta) * 7) / (*((s32 *)town_movement_speed))) + 2;
        }
        {
            u16 tick_count;
            tick_count = input->unk_004;
            if ((tick_count % sound_period) == 0) {
                SD_Call(0x60A);
            }
        }
    }

    if (speed == 0) {
        input->view.camera_rotation.parts.viewAngle = (((u16)input->view.camera_rotation.parts.viewAngle) + 8) & 0xFFF0;
    } else {
        if ((((u32)input->buttons) & 0x30) == 0x10) {
            speed = ((*((s32 *)town_movement_speed)) * 3) / 2;
        }
    }
    {
        s32 rounded_speed;
        rounded_speed = speed;
        if (speed < 0) {
            s32 rounding_bias;
            rounding_bias = 0xFFFF;
            rounded_speed = speed + rounding_bias;
        }
        speed = rounded_speed >> 16;
    }

    if ((*(u32 *)&input->buttons) & 0x2000) {
        {
            s32 angle;
            angle = ((u16)input->view.camera_rotation.parts.viewAngle);
            angle = angle - 0x10;
            angle = angle - speed;
            input->view.camera_rotation.parts.viewAngle = angle;
        }
        spawn_directional_effects(actor, (u16)scale_random_to_unsigned_halfword_limit(1));
    }

    if ((*(u32 *)&input->buttons) & 0x8000) {
        {
            s32 angle;
            angle = ((u16)input->view.camera_rotation.parts.viewAngle);
            angle = angle + 0x10;
            angle = angle + speed;
            input->view.camera_rotation.parts.viewAngle = angle;
        }
        spawn_directional_effects(actor, (u16)scale_random_to_unsigned_halfword_limit(1));
    }

    if ((((u32)input->pressed_buttons) & 0x10) && ((*((u8 *)town_blocked_directions)) == 0)) {
        state->callback = &D_800A5DF8;
        state->timer = 8;
        state->mode = 1;
        return;
    }

    if (((u32)input->pressed_buttons) & 0x100) {
        state->callback = &D_800A5DF8;
        state->timer = 8;
        state->mode = 0;
    }
}

/* Updates the actor effect and eases scene values before advancing the state. */
void update_actor_effect_transition(S_800A5DF8_4 *state, S_800A5DF8_0 *actor, s32 context) {
    s16 threshold;
    s32 offset_step;
    s16 angle;
    s32 next_offset;
    u16 ticks_left;
    register GameWork *scene_state;
    register s32 *effect_data;

    scene_state = &g_game_work;
    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile((struct EntityRec *)(actor));
    effect_data = &position_query_scratch;
    threshold = select_the_smaller_position_query_result_capped_n_64_writes_associated(actor, effect_data);
    if (actor->unk_0A >= threshold) {
        compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(actor), threshold, (struct TownVec **)(effect_data));
    } else if (((S_800A5DF8_1 *)(&town_action_state_flag))->unk_00 != 0) {
        actor->unk_14 = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2((s32 *)(actor));
    } else {
        add_hex_20000_s_signed_offset_hex_14(actor);
    }

    if (check_masked_value_in_current_range(read_map_cell_at_world_position(view_reference_entity.x.w.i, view_reference_entity.y.w.i) & 0xFFFF) != 0) {
        offset_step = actor->unk_14 - compute_height_based_offset((struct EntityRec *)(actor));
        actor->unk_14 = offset_step;
    }
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero((struct EntityRec *)(actor));
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero((struct EntityRec *)(actor));
    angle = step_angle_12_toward(scene_state->view.camera_rotation.parts.viewAngle, 0, 0x80);
    scene_state->view.camera_rotation.parts.viewAngle = angle;
    if ((angle & 0xFFF) < 0x80) {
        scene_state->view.camera_rotation.parts.viewAngle = 0;
    }
    ticks_left = state->unk_0A.s - 1;
    state->unk_0A.s = ticks_left;
    {
        s32 shifted_ticks;
        s32 ticks;
        shifted_ticks = (s32) ticks_left << 16;
        ticks = shifted_ticks >> 16;
        offset_step = -0x280;
        if (ticks <= 0) {
            state->unk_0A.u = 0;
        }
        next_offset = ticks > 0
            ? (offset_step -= scene_state->view.camera_rotation.parts.camera_rotation_x, offset_step /= ticks,
               ((u16)scene_state->view.camera_rotation.parts.camera_rotation_x) + offset_step)
        : -0x280;
        scene_state->view.camera_rotation.parts.camera_rotation_x = next_offset;
    }
    if ((state->unk_0A.u == 0) &&
        (scene_state->view.camera_rotation.parts.viewAngle == 0)) {
        if (state->unk_08 != 0) {
            initialize_effect_and_adjust_value(state, (struct EntityRec *)(actor), context);
        } else {
            state->unk_0A.u = 0;
            state->unk_00 = D_800A5FDC;
        }
    }

    return;
}

/* Updates town movement, terrain response, facing, and action state from input. */
void update_town_movement_and_actions(u8 *state, EntityRec *table, void *action_context)
{
    u8 *context;
    GameWork *globals;
    s32 random_choice;
    s32 tile_id;
    s32 speed;
    s32 speed_delta;
    s32 sound_interval;
    s32 input_flags;
    s32 turn_angle;
    s16 direction;
    s16 ground_height;

    context = action_context;
    globals = &g_game_work;
    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(table);

    ((S_800A5FDC_0 *)state)->unk_0A.s--;
    if (((S_800A5FDC_0 *)state)->unk_0A.u <= 0) {
        ((S_800A5FDC_0 *)state)->unk_0A.s = scale_random_to_unsigned_halfword_limit(3) + 5;
        random_choice = scale_random_to_unsigned_halfword_limit(2);
        spawn_directional_effects(table, (u16)random_choice + 2);
    }

    input_flags = globals->buttons;
    if (input_flags & 0xF000) {
        store_the_valid_shared_angle_in_offset_hex_10(state);
        direction = input_angle_with_offset(globals->buttons,
                                  globals->view.camera_rotation.parts.viewAngle);
        if (direction != -1) {
            add_a_directional_step_vector_scale_down_exceeds_length_limit(direction, ((s32 *)town_movement_speed)[0], table);
        }
        random_choice = scale_random_to_unsigned_halfword_limit(1);
        spawn_directional_effects(table, (u16)random_choice);
    } else {
        if (input_flags & 0x10) {
            move_both_components_toward_zero_direction_dependent_steps_clamping_zero(table);
        }
        move_both_components_toward_zero_direction_dependent_steps_clamping_zero(table);
    }

    ground_height = select_the_smaller_position_query_result_capped_n_64_writes_associated(table, &position_query_scratch);
    if (table->z.w.i >= ground_height) {
        compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(table), ground_height, (struct TownVec **)(&position_query_scratch));
    } else if (((u8 *)town_blocked_directions)[1] != 0) {
        table->flags14 = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2((s32 *)(table));
    } else {
        add_hex_20000_s_signed_offset_hex_14(table);
    }
    tile_id = read_map_cell_at_world_position(view_reference_entity.x.w.i,
                            view_reference_entity.y.w.i);
    if (check_masked_value_in_current_range((u16)tile_id) != 0) {
        table->flags14 -= compute_height_based_offset(table);
    }

    speed = runtime_estimate_vector_length(table->unk_0C,
                          table->unk_10);
    if (((s32 *)town_movement_speed)[0] != 0) {
        speed_delta = abs(((s32 *)town_movement_speed)[0] - speed);
        sound_interval = (s32)((u32)speed_delta * 7U) / ((s32 *)town_movement_speed)[0];
        if ((globals->unk_004 % (sound_interval + 2)) == 0) {
            SD_Call(0x60A);
        }
    }

    if (speed == 0) {
        globals->view.camera_rotation.parts.viewAngle =
            (((u16)globals->view.camera_rotation.parts.viewAngle) + 8) & 0xFFF0;
    }

    speed /= 0x10000;
    if (globals->buttons & 4) {
        turn_angle = ((u16)globals->view.camera_rotation.parts.viewAngle) + 0x10;
        globals->view.camera_rotation.parts.viewAngle = turn_angle + speed;
    }
    if (globals->buttons & 8) {
        turn_angle = ((u16)globals->view.camera_rotation.parts.viewAngle) - 0x10;
        globals->view.camera_rotation.parts.viewAngle = turn_angle - speed;
    }

    if (((globals->pressed_buttons) & 0x10) &&
        (((u8 *)town_blocked_directions)[0] == 0)) {
        initialize_effect_and_adjust_value(state, table, (s32)(context));
        return;
    }

    if ((globals->pressed_buttons) & 0x100) {
        ((S_800A5FDC_0 *)state)->unk_00 = (s32)&map_view_transition_address;
        ((S_800A5FDC_0 *)state)->unk_0A.u = 8;
    }
    return;
}
