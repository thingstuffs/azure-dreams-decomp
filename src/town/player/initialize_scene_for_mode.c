#include "town/player/initialize_record_and_select_active_data.h"
#include "town/player/initialize_scene_for_mode_api.h"
#include "town/player/initialize_record_with_handler_table_api.h"
#include "town/player/effect.h"
#include "town/player.h"
/* Initializes the town player scene and updates movement, camera rotation, and facing animations. */
#include "shared/sprite_frame_state.h"
#include "script_symbols.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "town/player/initialize_scene_for_mode.h"
#include "shared/tile_object.h"
#include "town/shop/item_lookup.h"
#include "town/person/position.h"
#include "town/map/object.h"
#include "town/scene/motion.h"
#include "town/player/motion.h"
#include "engine/graphics.h"
#include "engine/scene.h"
#include "engine/script.h"
#include "town/player/record.h"
#include "town/player/input.h"
#include "town/player/position_handlers.h"
#include "town/scene/hooks.h"
#include "town/map.h"
#include "engine/object.h"

/* Initialize the town scene and configure its object for the current mode. */
void initialize_scene_for_mode(void)
{
    ObjectPosition *scene;
    TileObject *render;
    func_80092868_TownState *state;
    ObjectNodeHeader *object;
    func_80092868_TownWork *work;
    void *shared_data;
    s32 neutral_color;
    u16 x_offset;
    u16 x_coord;
    u16 y_offset;
    u16 y_coord;
    u16 frame;

    scene = &view_reference_entity;
    camera_height_mode[0] = 0;
    camera_turn_lock[0] = 0;
    zero_words(scene, 6);
    render = &reference_tile_object;
    zero_words(render, 0xC);
    render->render_attributes = loaded_sprite_bundle_attributes;
    initialize_circular_list_head();

    shared_data = D_800D0420;
    init_scene_list_node(town_actor_control, scene, shared_data);
    init_town_motion_list();
    init_secondary_list_record(town_motion_list, scene, shared_data);

    state = &map_runtime_state;
    if (state->mode == 0x37000C) {
        initialize_object_at_current_position();
        return;
    }

    object = initialize_scene_object_in_buffer(0, &scene_object_list_anchor, 0x22);
    object->position = scene;
    object->sprite = render;

    if (state->alternate != 0) {
        u16 *coords;

        object->update_callback = noop_at_8008_ffc_0;
        coords = state->coords;
        scene->x.w.i = state->x_offset + coords[0];
        scene->y.w.i = state->y_offset + coords[1];
        scene->z.w.i = 0;
        copy_entity_record_fields(town_position_reference_state, scene);
        return;
    }

    {
        u16 *coords;

        object->update_callback = rebuild_menu_node_list;
        register_node(object, draw_entry_overlays);
        neutral_color = 0x808080;
        render->scale_y = 0x1000;
        render->scale_x = 0x1000;

        coords = state->coords;
        x_offset = state->x_offset;
        x_coord = coords[0];
        render->primitive_color.word = neutral_color;
        scene->x.w.i = x_offset + x_coord;
        y_offset = state->y_offset;
        y_coord = coords[1];
        scene->z.w.i = -0x80;
        scene->y.w.i = y_offset + y_coord;
        scene->z.w.i = query_lowered_transform_position(scene);
        init_probe_sample_buffers();
        sync_collision_motion_xyz(scene);

        work = NODE_BODY(object);
        work->field12 = -1;
        frame = state->frame;
        work->frame0 = frame;
        work->frame1 = frame;
        clear_resident_bitmap_bit(F_t_attack_enable);

        if (test_resident_bitmap_bit(F_player_mizugi) == 0) {
            work->active = 0;
        } else {
            work->active = 1;
        }

        render->render_attributes = loaded_sprite_bundle_attributes;
        if ((map_scene_selector_alias[0] != 0xC) && (find_item_by_kind_and_type(2, 0x13) != 0)) {
            create_person_object();
        }
    }
}

/* Synchronizes the mode flag, updates state, and runs the pending callback. */
void synchronize_mode_and_pending_callback(void) {
    s32 disabled_flag;
    s32 enabled_flag;
    s32 mode_result; /* MATCH: Keep the merged call result in v0 for the shared stores. */
    ObjectPosition *work_state = (void *)&view_reference_entity.x.v;
    SpriteFrameState *update_state = (void *)&reference_tile_object;
    u8 *handler_state = (u8 *)&scene_object_payload_alias;
    void (*callback)();

    if ((s32)NODE_HEADER(handler_state)->update_callback != (s32)noop_at_8008_ffc_0) {
        if (test_resident_bitmap_bit(F_player_mizugi) == 0) {
            ((func_80092AB0_S_80090210_0 *)(handler_state - 0x10))->unk_26 = 0;
            disabled_flag = test_resident_bitmap_bit(F_player_mizugi);
            if (disabled_flag != test_resident_bitmap_bit(F_player_mizugi_old)) {
                mode_result = load_town_sprite_bundle();
                loaded_sprite_bundle_attributes = mode_result;
                update_state->animation_resource = mode_result;
            }
        } else {
            ((func_80092AB0_S_80090210_0 *)(handler_state - 0x10))->unk_26 = 1;
            enabled_flag = test_resident_bitmap_bit(F_player_mizugi);
            if (enabled_flag != test_resident_bitmap_bit(F_player_mizugi_old)) {
                s32 selected_mode;
                selected_mode = load_alternate_town_sprite_bundle();
                loaded_sprite_bundle_attributes = selected_mode;
                update_state->animation_resource = selected_mode;
            }
        }
        if (test_resident_bitmap_bit(F_player_mizugi) != 0) {
            set_resident_bitmap_bit(F_player_mizugi_old);
        } else {
            clear_resident_bitmap_bit(F_player_mizugi_old);
        }
        dispatch_selected_entry_if_nonzero(town_scene_record_handlers, handler_state, update_state);
        initialize_player_object(handler_state);
        initialize_record_and_select_active_data(handler_state, (work_state), update_state);
        initialize_record_with_handler_table(handler_state, (work_state), update_state);
        callback = (void (*)())town_scene_init_callback;
        ((func_80092AB0_S_80090210_0 *)(handler_state - 0x10))->unk_14 = advance_timed_script_controller;
        ((func_80092AB0_S_80090210_0 *)(handler_state - 0x10))->unk_1A = 0x10;
        if (callback != NULL) {
            callback();
            town_scene_init_callback = 0;
        }
    }
}

/* Initialize the global record using its preceding value and D_800D0178. */
void initialize_global_scene_record(void) {
    s32 *record = &scene_object_payload_alias;
    dispatch_selected_entry_if_nonzero(&D_800D0178, record, *(s32 *)&NODE_HEADER(record)->sprite);
}

/* plt_init_sleep_set: set the sleep initialization pointer. */
void plt_init_sleep_set(void) {
    town_scene_init_callback = &initialize_global_scene_record;
}

/* Invokes initialize_scene_for_mode with no arguments. */
void initialize_scene_render_state(void) {
    initialize_scene_for_mode();
}

/* Invokes initialize_scene_for_mode with no arguments. */
void initialize_scene_render_object(void) {
    initialize_scene_for_mode();
}

/* Rebuild the town menu's node list for the current mode and hand it to the drawing pass. */
void rebuild_menu_node_list(TownPlayerRecord *owner, ObjectPosition *node_in, SpriteFrameState *sprite) {
    func_80092C9C_S_800903FC_3 *node;
    void *handler;
    func_80092C9C_S_800903FC_2 *base;
    u8 *object;
    func_80092C9C_S_800903FC_1 *work;
    s16 value;

    handler = owner->unk_00;
    if (handler != town_position_callback_address || handler != noop_player_scene_action) {
        apply_actor_control_offsets(node_in);
    }
    add_motion_deltas_to_position(node_in);

    handler = owner->unk_00;
    if (handler != town_position_callback_address || handler != noop_player_scene_action) {
        update_object_and_clear_status_fields(node_in);
    }

    if (node_in->z.v > 0 && map_scene_selector_alias[0] != 12 &&node_in->y.v > 0x03FFFFFF) {
        if (check_masked_value_in_current_range((u16)read_map_cell_at_world_position(node_in->x.w.i,
                                                  node_in->y.w.i)) == 0) {
            node_in->z.v = 0;
        }
    }

    store_position_and_compute_delta(node_in);

    work = (func_80092C9C_S_800903FC_1 *)&town_motion_list;
    work->unk_16 = (u16)owner->unk_10;
    update_record_overlap_node(work);
    if (has_attached_state_type_1_or_3(work) != 0) {
        owner->unk_2C = 0;
        submit_object_resource_data(work->unk_10);

        object = window_node_list_storage;
        (*(func_80092C9C_ObjectCallback *)(object + (0x10)))(object + 0x20, 0, 0);

        if (service_script_controller() != 0) {
            base = (func_80092C9C_S_800903FC_2 *)&town_actor_control;
            if (base->unk_3B == 0 ||
                (node = ((func_80092C9C_S_800903FC_4 *)(base->unk_20))->unk_08)->unk_0C != 0 ||
                node->unk_10 != 0 || node->unk_14 != 0) {
                {
                    s32 *update_work;

                    update_work = &position_query_scratch;
                    value = query_capped_surface_height(node_in, update_work);
                    set_height_and_slope_velocity(node_in, value, update_work);
                }
            }
            sync_collision_motion_xyz(node_in);
            if (owner->unk_00 != town_position_callback_address) {
                initialize_record_and_select_active_data(owner, (node_in), sprite);
            }
        }
    }

    resolve_collider_overlaps(&town_actor_control, node_in);
    (*(func_80092C9C_ActorCallback *)((u8 *)owner + (0)))(owner, node_in, (s32)sprite);

    if ((*(void **)((u8 *)owner + (-0x10))) == D_800A5638) {
        turn_entity_toward_target(owner, node_in, sprite);
        return;
    }
    process_scene_record_update(owner, node_in, sprite);
}

/* MECHANISM: The 0x28 frame and s2/s1/s3 argument holds preserve the retail prologue.
   A block-local update_work separates D_800FE488 from the earlier work lifetime.
   GCC coalesces both to s0 and emits the two-edge lui/addiu held base. */

/* Updates camera rotation and facing after collision adjustment, then saves the reference position. */
void process_scene_record_update(TownPlayerRecord *context, ObjectPosition *input, SpriteFrameState *sprite) {
    GameWork *work = &g_game_work;
    void *callback;
    s32 initial_flags;
    s32 flags;
    s32 movement;
    s32 index;

    clear_blocked_motion(input);

    if (camera_turn_lock[0] == 0) {
        if (((u16)work->view.camera_rotation.parts.viewAngle) >= 0x800) {
            work->view.camera_rotation.parts.viewAngle |= 0xF000;
        }

        callback = context->unk_00;
                /* garbage-passthru: a1/a2/a3 are caller-saved residue after clear_blocked_motion. */
        if (callback == (void *)town_position_callback_address || callback == (void *)&noop_player_scene_action ||
            service_script_controller() != 0) {
            if (map_scene_selector_alias[0] == 12) {
                to_camera_zero_00();
            } else if (input->y.w.i < 0x400) {
                clear_record_state_or_update(input);
            }
        } else if (map_scene_selector_alias[0] == 12) {
            initial_flags = work->buttons;
            if (initial_flags & 8) {
                work->view.camera_rotation.parts.viewAngle -= 0x20;
                if (work->view.camera_rotation.parts.viewAngle < -0x1E0) {
                    work->view.camera_rotation.parts.viewAngle = -0x1E0;
                }
            } else if (initial_flags & 4) {
                work->view.camera_rotation.parts.viewAngle += 0x20;
                if (work->view.camera_rotation.parts.viewAngle > 0x1E0) {
                    work->view.camera_rotation.parts.viewAngle = 0x1E0;
                }
            } else {
                to_camera_zero_00();
            }
        } else if (input->y.w.i < 0x400) {
            clear_record_state_or_update(input);
        } else {
            movement = runtime_estimate_vector_length(input->velocity_x,
                                     input->velocity_y);
            if (movement == 0) {
                work->view.camera_rotation.parts.viewAngle =
                    (((u16)work->view.camera_rotation.parts.viewAngle) + 8) & 0xFFF0;
            }
            movement /= 0x10000;
            flags = work->buttons;
            if (flags & 8) {
                work->view.camera_rotation.parts.viewAngle -= 0x10 + movement;
            }
            if (flags & 4) {
                work->view.camera_rotation.parts.viewAngle += 0x10 + movement;
            }
        }
    }

    callback = context->unk_00;
    if ((callback == (void *)dispatch_actor_input_actions) ||
        (callback == (void *)update_actor_input_and_interaction)) {
        context->unk_18 =
            step_angle_12_toward(context->unk_18,
                          context->unk_10, 0x200);
    } else {
        context->unk_18 = (u16)context->unk_10;
    }
    index = view_relative_angle_sector(context->unk_18);
    if (context->unk_12 != index) {
        texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags((void *)sprite,
                      *(*(u8 **)((u8 *)context + 0x1C) + index),
                      sprite->unk_04, 0);
        context->unk_12 = index;
    }

    {

        if (town_scene_effect_flips[index] != 0) {
            sprite->flags |= 1;
        } else {
            sprite->flags &= 0xFFFE;
        }
    }
    dispatch_fallback_position(context, input, sprite);
    step_actor_animation(sprite, 0);

    {
        u8 *state = town_position_reference_state;

        copy_entity_record_fields(state, input);
        if (camera_height_mode[0] == 0) {
            *(s32 *)(state + 8) = 0;
            return;
        }
        if (camera_height_mode[0] == 2) {
            *(s32 *)(state + 8) /= 2;
        }
    }
}

/*
 * to_camera_zero_00: Moves the camera offset toward zero in steps of 16.
 *
 * MECHANISM: The three arguments stay in s1/s2/s3 and g_game_work in s0, yielding the retail 0x28
 * frame. A one-sided schedule barrier preserves both clamp tails; ASM_TAILSLOT_PIN sinks the dead
 * OR into its j slot. Memory fences retain the clear/store call sequence and force the post-store
 * signed-halfword reload.
 */
s32 to_camera_zero_00(void) {
    GameWork *camera_state = &g_game_work;
    s16 camera_offset = camera_state->view.camera_rotation.parts.viewAngle;
    u16 next_offset = ((u16)camera_state->view.camera_rotation.parts.viewAngle);

    if (camera_offset != 0) {
        if (camera_offset > 0) {
            next_offset -= 0x10;
            camera_state->view.camera_rotation.parts.viewAngle = next_offset;
            if ((s16)next_offset < 0) {
                camera_state->view.camera_rotation.parts.viewAngle = 0;
            }
        } else if (camera_offset < 0) {
            next_offset += 0x10;
            camera_state->view.camera_rotation.parts.viewAngle = next_offset;
            if ((s16)next_offset > 0) {
                camera_state->view.camera_rotation.parts.viewAngle = 0;
            }
        }
    }

    return camera_state->view.camera_rotation.parts.viewAngle;
}

/* Clear the state field or invoke updates according to the record value. */
void clear_record_state_or_update(ObjectPosition *record) {
    s16 threshold_value = record->y.w.i;
    GameWork *state = &g_game_work;

    if (threshold_value < 0x200) {
        state->view.camera_rotation.parts.viewAngle = 0;
        return;
    }
    if (threshold_value < 0x300) {
        to_camera_zero_00();
        to_camera_zero_00();
    }
    to_camera_zero_00();
    to_camera_zero_00();
}

/* Returns without performing any work. */
void noop_player_scene_action(void) {
}

/* Return without performing any work. */
void no_op_scene_callback_b(void) {
}
