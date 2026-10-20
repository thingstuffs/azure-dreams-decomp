#include "script_symbols.h"
#include "town/player/initialize_scene_for_mode.h"



/* Initialize the town scene and configure its object for the current mode. */
void initialize_scene_for_mode(void)
{
    EntityRec *scene;
    TileObject *render;
    func_80092868_TownState *state;
    func_80092868_TownObject *object;
    func_80092868_TownWork *work;
    void *shared_data;
    s32 neutral_color;
    u16 x_offset;
    u16 x_coord;
    u16 y_offset;
    u16 y_coord;
    u16 frame;

    scene = &D_80083780;
    D_80100E18[0] = 0;
    D_80100DB0[0] = 0;
    zero_words(scene, 6);
    render = &D_80082E80;
    zero_words(render, 0xC);
    render->render_attributes = D_80080A80;
    initialize_circular_list_head();

    shared_data = D_800D0420;
    handle_insert_initialize_two_values_status_flags(D_800CFCB4, scene, shared_data);
    initialize_pointer_table_self_links();
    initialize_the_store_two_values_set_state_flags(D_800FE490, scene, shared_data);

    state = &D_8006ADBC;
    if (state->mode == 0x37000C) {
        initialize_object_at_current_position();
        return;
    }

    object = initialize_scene_object_in_buffer(0, ((u8 *)(&D_80083498)), 0x22);
    object->scene = scene;
    object->render = render;

    if (state->alternate != 0) {
        u16 *coords;

        object->callback = D_8008FFC0;
        coords = state->coords;
        scene->x.w.i = state->x_offset + coords[0];
        scene->y.w.i = state->y_offset + coords[1];
        scene->z.w.i = 0;
        copy_entity_record_fields(D_80100D98, scene);
        return;
    }

    {
        u16 *coords;

        object->callback = rebuild_menu_node_list;
        register_node(object, D_800970FC);
        neutral_color = 0x808080;
        render->scale_y = 0x1000;
        render->scale_x = 0x1000;

        coords = state->coords;
        x_offset = state->x_offset;
        x_coord = coords[0];
        *(s32 *)(&render->primitive_color.parts.color_r) = neutral_color;
        scene->x.w.i = x_offset + x_coord;
        y_offset = state->y_offset;
        y_coord = coords[1];
        scene->z.w.i = -0x80;
        scene->y.w.i = y_offset + y_coord;
        scene->z.w.i = query_lowered_transform_position(scene);
        initialize_six_global_pointers_corresponding_storage_blocks();
        run_the_three_update_routines_context(scene);

        work = (func_80092868_TownWork *)((u8 *)object + 0x20);
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

        render->render_attributes = D_80080A80;
        if ((D_8006ADD4[0] != 0xC) && (find_item_by_kind_and_type(2, 0x13) != 0)) {
            create_person_object();
        }
    }
}

/* Synchronizes the mode flag, updates state, and runs the pending callback. */
void synchronize_mode_and_pending_callback(void) {
    s32 disabled_flag;
    s32 enabled_flag;
    s32 mode_result; /* MATCH: Keep the merged call result in v0 for the shared stores. */
    u8 *work_state = (u8 *)&D_80083780.x.v;
    TileObject *update_state = &D_80082E80;
    u8 *handler_state = (u8 *)&D_800834B8;
    void (*callback)();

    if (((func_80092AB0_S_80090210_0 *)((u8 *)handler_state - 0x10))->unk_00 != D_8008FFC0) {
        if (test_resident_bitmap_bit(F_player_mizugi) == 0) {
            ((func_80092AB0_S_80090210_0 *)((u8 *)handler_state - 0x10))->unk_26 = 0;
            disabled_flag = test_resident_bitmap_bit(F_player_mizugi);
            if (disabled_flag != test_resident_bitmap_bit(F_player_mizugi_old)) {
                mode_result = func_80048D20();
                D_80080A80 = mode_result;
                update_state->render_attributes = mode_result;
            }
        } else {
            ((func_80092AB0_S_80090210_0 *)((u8 *)handler_state - 0x10))->unk_26 = 1;
            enabled_flag = test_resident_bitmap_bit(F_player_mizugi);
            if (enabled_flag != test_resident_bitmap_bit(F_player_mizugi_old)) {
                s32 mode_result;
                mode_result = func_80048D40();
                D_80080A80 = mode_result;
                update_state->render_attributes = mode_result;
            }
        }
        if (test_resident_bitmap_bit(F_player_mizugi) != 0) {
            set_resident_bitmap_bit(F_player_mizugi_old);
        } else {
            clear_resident_bitmap_bit(F_player_mizugi_old);
        }
        call_the_handler_selects_nonzero_entry(D_800D0078, handler_state, update_state);
        initialize_player_object(handler_state);
        initialize_record_and_select_active_data(handler_state, work_state, update_state);
        initialize_record_with_handler_table(handler_state, work_state, update_state);
        callback = (void (*)())D_800D0438;
        ((func_80092AB0_S_80090210_0 *)((u8 *)handler_state - 0x10))->unk_14 = (s32 *)&D_80097D54;
        ((func_80092AB0_S_80090210_0 *)((u8 *)handler_state - 0x10))->unk_1A = 0x10;
        if (callback != NULL) {
            callback();
            D_800D0438 = 0;
        }
    }
}

/* Initialize the global record using its preceding value and D_800D0178. */
void initialize_global_scene_record(void) {
    s32 *record = &D_800834B8;
    call_the_handler_selects_nonzero_entry(&D_800D0178, record, ((func_80092C18_S_80090378_0 *)((u8 *)record - 0x14))->unk_00);
}

/* plt_init_sleep_set: set the sleep initialization pointer. */
void plt_init_sleep_set(void) {
    D_800D0438 = &initialize_global_scene_record;
}

/* Initialize the town scene and its render state. */
void initialize_scene_render_state(void) {
    initialize_scene_for_mode();
}

/* Initialize the town scene and its render object. */
void initialize_scene_render_object(void) {
    initialize_scene_for_mode();
}

/* Rebuild the town menu's node list for the current mode and hand it to the drawing pass. */
void rebuild_menu_node_list(void *owner, EntityRec *node_in, s32 mode) {
    func_80092C9C_S_800903FC_3 *node;
    void *handler;
    u8 *base;
    u8 *object;
    u8 *work;
    s16 value;

    handler = (*(void * *)((u8 *)owner + (0)));
    if (handler != D_80097D2C || handler != func_80090A64) {
        apply_the_enabled_movement_offsets_adding_z_offset_only_positive(node_in);
    }
    add_motion_deltas_to_position(node_in);

    handler = (*(void * *)((u8 *)owner + (0)));
    if (handler != D_80097D2C || handler != func_80090A64) {
        update_object_and_clear_status_fields(node_in);
    }

    if (node_in->z.v > 0 && D_8006ADD4[0] != 12 &&node_in->y.v > 0x03FFFFFF) {
        if (check_masked_value_in_current_range((u16)read_map_cell_at_world_position(node_in->x.w.i,
                                                  node_in->y.w.i)) == 0) {
            node_in->z.v = 0;
        }
    }

    store_position_and_compute_delta(node_in);

    work = (u8 *)&D_800FE490;
    ((func_80092C9C_S_800903FC_1 *)work)->unk_16 = (*(u16 *)((u8 *)owner + (0x10)));
    update_the_s_field_10_using_callee_8008_fe_90(work);
    if (get_whether_has_attached_state_type_n_1_n_3(work) != 0) {
        (*(s32 *)((u8 *)owner + (0x2C))) = 0;
        submit_object_resource_data(((func_80092C9C_S_800903FC_1 *)work)->unk_10);

        object = D_80082BC0;
        (*(func_80092C9C_ObjectCallback *)((u8 *)object + (0x10)))(object + 0x20, 0, 0);

        if (service_script_controller() != 0) {
            base = (u8 *)&D_800CFCB4;
            if (((func_80092C9C_S_800903FC_2 *)base)->unk_3B == 0 ||
                (node = ((func_80092C9C_S_800903FC_4 *)(((func_80092C9C_S_800903FC_2 *)base)->unk_20))->unk_08)->unk_0C != 0 ||
                node->unk_10 != 0 || node->unk_14 != 0) {
                {
                    u8 *update_work;

                    update_work = ((u8 *)&D_800FE488);
                    value = select_the_smaller_position_query_result_capped_n_64_writes_associated(node_in, update_work);
                    compute_and_clamps_vector_based_adjustment_updates_town(node_in, value, update_work);
                }
            }
            run_the_three_update_routines_context(node_in);
            if ((*(void * *)((u8 *)owner + (0))) != D_80097D2C) {
                initialize_record_and_select_active_data(owner, node_in, mode);
            }
        }
    }

    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(&D_800CFCB4, node_in);
    (*(func_80092C9C_ActorCallback *)((u8 *)owner + (0)))(owner, node_in, mode);

    if ((*(void * *)((u8 *)owner + (-0x10))) == D_800A5638) {
        turn_entity_toward_target(owner, node_in, mode);
        return;
    }
    process_scene_record_update(owner, node_in, mode);
}

/* MECHANISM: The 0x28 frame and s2/s1/s3 argument holds preserve the retail prologue.
   A block-local update_work separates D_800FE488 from the earlier work lifetime.
   GCC coalesces both to s0 and emits the two-edge lui/addiu held base. */

void process_scene_record_update(void *context, void *input, void *record) {
    GameWork *work = &g_game_work;
    void *callback;
    s32 initial_flags;
    s32 flags;
    s32 movement;
    s32 index;

    clear_motion_along_blocked_directions_update_affected_axes(input);

    if (D_80100DB0[0] == 0) {
        if (((u16)work->view.camera_rotation.parts.viewAngle) >= 0x800) {
            work->view.camera_rotation.parts.viewAngle |= 0xF000;
        }

        callback = *(void **)context;
                /* garbage-passthru: a1/a2/a3 are caller-saved residue after clear_motion_along_blocked_directions_update_affected_axes. */
        if (callback == (void *)D_80097D2C || callback == (void *)&func_80090A64 ||
            service_script_controller() != 0) {
            if (D_8006ADD4[0] == 12) {
                func_800909A0();
            } else if (*(s16 *)((u8 *)input + 6) < 0x400) {
                clear_record_state_or_update(input);
            }
        } else if (D_8006ADD4[0] == 12) {
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
                func_800909A0();
            }
        } else if (*(s16 *)((u8 *)input + 6) < 0x400) {
            clear_record_state_or_update(input);
        } else {
            movement = runtime_estimate_vector_length(*(s32 *)((u8 *)input + 0xC),
                                     *(s32 *)((u8 *)input + 0x10));
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

    callback = *(void **)context;
    if ((callback == (void *)&D_80091260) ||
        (callback == (void *)&D_80091528)) {
        *(s16 *)((u8 *)context + 0x18) =
            step_angle_12_toward(*(s16 *)((u8 *)context + 0x18),
                          *(s16 *)((u8 *)context + 0x10), 0x200);
    } else {
        *(s16 *)((u8 *)context + 0x18) = *(u16 *)((u8 *)context + 0x10);
    }
    index = view_relative_angle_sector(*(s16 *)((u8 *)context + 0x18));
    if (*(s16 *)((u8 *)context + 0x12) != index) {
        texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(record,
                      *(u8 *)(*(u8 **)((u8 *)context + 0x1C) + index),
                      *(s8 *)((u8 *)record + 4), 0);
        *(s16 *)((u8 *)context + 0x12) = index;
    }

    {

        if (D_800D01F8[index] != 0) {
            *(u16 *)((u8 *)record + 0x14) |= 1;
        } else {
            *(u16 *)((u8 *)record + 0x14) &= 0xFFFE;
        }
    }
    dispatch_to_matching_fallback_handler_using_sentinel_terminated_key_lists(context, input, record);
    step_actor_animation(record, 0);

    {
        u8 *state = D_80100D98;

        copy_entity_record_fields(state, input);
        if (D_80100E18[0] == 0) {
            *(s32 *)(state + 8) = 0;
            return;
        }
        if (D_80100E18[0] == 2) {
            *(s32 *)(state + 8) /= 2;
        }
    }
}

/* MECHANISM: The three arguments stay in s1/s2/s3 and D_80083160 in s0, yielding the retail 0x28 frame.
   A one-sided schedule barrier preserves both clamp tails; ASM_TAILSLOT_PIN sinks the dead OR into its j slot.
   Memory fences retain the clear/store call sequence and force the post-store signed-halfword reload. */

/* func_800909A0: Moves the camera offset toward zero in steps of 16. */
s32 func_800909A0() {
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
void clear_record_state_or_update(void *record) {
    s16 threshold_value = *(s16 *)((u8 *)record + 6);
    GameWork *state = &g_game_work;

    if (threshold_value < 0x200) {
        state->view.camera_rotation.parts.viewAngle = 0;
        return;
    }
    if (threshold_value < 0x300) {
        func_800909A0(state);
        func_800909A0();
    }
    func_800909A0();
    func_800909A0();
}

/* Returns without performing any work. */
void func_80090A64(void) {
}

/* Return without performing any work. */
void no_op_scene_callback_b(void) {
}
