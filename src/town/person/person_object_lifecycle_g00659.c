/* Person object lifecycle. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C5ABC, CL:town/func_800C6064, PD:town/engine:800D5028. */
#include "town/person/person_object_lifecycle_g00659.h"
#include "shared/object_node.h"
#include "town/person.h"
#include "town/scene/object.h"
#include "engine/node.h"

/* Update the object motion or clear its state and clean it up when the position check fails. */
void update_object_position_or_cleanup(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *motion) {
    s32 check_result;
    u8 *state_flag;

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
void update_object_motion_and_flags(TownObjectRecord *obj, ObjectPosition *callback_arg, SpriteFrameState *motion) {
    TownSceneListNode *node = (TownSceneListNode *)obj;
    TargetObj *movement;
    s32 table_index;
    u8 state;

    u32 motion_flags;

    state = obj->unk_70;
    if (state == 0) {
        node->bounds = &D_800D5028;
    } else if (state == 1) {
        node->bounds = &D_800D5040;
    } else {
        node->bounds = &D_800D5058;
    }

    ((FuncPtr)obj->unk_50.as_pm)(obj, callback_arg, motion);
    if (!(NODE_HEADER(obj)->flags & 0x8000)) {
        table_index = quantize_heading_to_sector(obj->heading, obj->unk_64);
        movement = (TargetObj *)obj;
        if (movement->field74 != table_index) {
            clear_object_status_and_dispatch_target(obj, motion, obj->unk_78[table_index], motion->unk_04);
            movement->field74 = table_index;
        }
        if (!(obj->unk_71 & 1)) {
            if ((check_heading_past_half_sector(obj->heading, obj->unk_64) << 0x10) == 0) {
                motion_flags = (u16)(motion->flags & 0xfffe);
            } else {
                motion_flags = motion->flags | 1;
            }
        } else if ((check_heading_past_half_sector(obj->heading, obj->unk_64) << 0x10) != 0) {
            motion_flags = motion->flags;
            motion_flags &= 0xfffe;
        } else {
            motion_flags = motion->flags | 1;
        }
        motion->flags = motion_flags;
        advance_object_animation_when_idle(obj, motion, 0, 0);
    }
}

/* Update the object's flag and dispatch its current state handler. */
void dispatch_object_state(TownObjectRecord *object, ObjectPosition *context, SpriteFrameState *dispatch_data) {
    TownObjectRecord *object_bytes = object;
    FuncPtr *handlers;
    u8 state;

    if (is_node_registered(object) != 0) {
        object_bytes->unk_15 = 1;
    }
    state = (u8)object_bytes->unk_94;
    if (state == 0) {
        object_bytes->heading = object_bytes->unk_6E;
        install_stored_value_handler(object, context, dispatch_data);
        return;
    }
    if (state == 1) {
        initialize_object_assigns_state_data(object, context, dispatch_data);
        return;
    }
    handlers = object_bytes->state_handlers;
    handlers[(u8)object_bytes->unk_94 - 2](object, context, dispatch_data);
}

/* Initialize the object and its animation, then dispatch its current state. */
void initialize_person_object(TownObjectRecord *object, ObjectPosition *context, SpriteFrameState *animation) {
    register_node_if_unregistered(object, project_sprite_chain);
    object->unk_8C = 0x40;
    object->unk_8E = 0x40;
    clear_object_status_and_dispatch_target(object, animation, **object->unk_7C.as_pps32, 0);
    init_scene_node_mode_1(object, context, &D_800D5028);
    dispatch_object_state(object, context, animation);
}
