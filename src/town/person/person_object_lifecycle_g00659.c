/* Person object lifecycle (G00659). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C5ABC, CL:town/func_800C6064, PD:town/engine:800D5028. */
#include "town/person/person_object_lifecycle_g00659.h"

/* Update the object motion or clear its state and clean it up when the position check fails. */
void update_object_position_or_cleanup(Rec_func_80094268_arg0 *object, void *position, void *motion) {
    s32 check_result;
    s8 *state_flag;

    check_result = classify_object_against_bounds(object, position);
    if (check_result != 0) {
        if ((check_result != 2) || (object->unk_50.as_s32 != &call_object_callback)) {
            unlink_scene_list_node(object);
            state_flag = object->unk_98;
            if (state_flag != 0) {
                *state_flag = 0;
            }
            unlink_node_if_registered(object);
            clear_object_slot_and_mark_removed(object);
            return;
        }
        update_object_motion_and_flags(object, position, motion);
        return;
    }
    update_object_motion_and_flags(object, position, motion);
}

/* Selects state data, invokes the object callback, and updates motion data and flags. */
void update_object_motion_and_flags(TargetObj *obj, void *callback_arg, void *motion_data) {
    s32 table_index;
    u8 state;

    void *motion = motion_data;

    u32 motion_flags;

    state = obj->state70;
    if (state == 0) {
        obj->field0c = &D_800D5028;
    } else if (state == 1) {
        obj->field0c = &D_800D5040;
    } else {
        obj->field0c = &D_800D5058;
    }

    obj->callback(obj, callback_arg, motion);
    if (!(*(u16 *)((u8 *)obj - 2) & 0x8000)) {
        table_index = quantize_heading_to_sector(obj->field72, obj->field64);
        if (obj->field74 != table_index) {
            clear_object_status_and_dispatch_target(obj, motion, (int)(obj->table78[table_index]), *(s8 *)((u8 *)motion + 4));
            obj->field74 = table_index;
        }
        if (!(obj->flags71 & 1)) {
            if ((check_heading_past_half_sector(obj->field72, obj->field64) << 0x10) == 0) {
                motion_flags = (u16)(*(u16 *)((u8 *)motion + 0x14) & 0xfffe);
            } else {
                motion_flags = *(u16 *)((u8 *)motion + 0x14) | 1;
            }
        } else if ((check_heading_past_half_sector(obj->field72, obj->field64) << 0x10) != 0) {
            motion_flags = *(u16 *)((u8 *)motion + 0x14);
            motion_flags &= 0xfffe;
        } else {
            motion_flags = *(u16 *)((u8 *)motion + 0x14) | 1;
        }
        *(u16 *)((u8 *)motion + 0x14) = motion_flags;
        dispatch_object_when_idle(obj, motion, 0, 0);
    }
}

/* Update the object's flag and dispatch its current state handler. */
void dispatch_object_state(void *object, void *context, void *dispatch_data) {
    u8 *object_bytes = (u8 *) object;
    u8 state;

    if (runtime_is_record_field_set(object) != 0) {
        object_bytes[0x15] = 1;
    }
    state = object_bytes[0x94];
    if (state == 0) {
        *(u16 *)(object_bytes + 0x72) = *(u16 *)(object_bytes + 0x6E);
        install_stored_value_handler(object, context, dispatch_data);
        return;
    }
    if (state == 1) {
        initialize_object_assigns_state_data(object, context, dispatch_data);
        return;
    }
    (*(FuncPtr *)((((u8 *) object_bytes)[0x94] * 4) + *(s32 *)(object_bytes + 0x58) - 8))(object, context,
        dispatch_data);
}

/* Initialize the object and its animation, then dispatch its current state. */
void initialize_person_object(Rec_func_80094268_arg0 *object, s32 context, void *animation) {
    register_node_if_unregistered(object, project_sprite_chain);
    object->unk_8C = 0x40;
    object->unk_8E = 0x40;
    clear_object_status_and_dispatch_target(object, animation, **object->unk_7C.as_pps32, 0);
    configure_the_set_mode_n_1((struct Rec_func_8008F074_arg0 *)(object), context, (s32)(&D_800D5028));
    dispatch_object_state(object, (void *)(context), animation);
}
