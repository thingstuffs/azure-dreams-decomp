#include "modules/town_player_init.h"

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

        if (func_800352FC() != 0) {
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
