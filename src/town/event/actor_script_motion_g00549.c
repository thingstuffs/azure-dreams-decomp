/* Dispatches town actor scripts and updates actor surface motion, slot state, and output values. */
/* inferred-strong G00549: actor_script_motion_g00549; joins CL:town/func_8009DB64; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8009DB64. */
#include "town/event/actor_script_motion_g00549.h"
#include "town/scene/flags.h"
#include "town/scene.h"

/* Dispatches town object actions for the active script and owner state. */
s32 dispatch_active_town_object_script(TownObject *object, void *owner, void *context, void *extra_ptr) {
    TownControl *control;
    TownControl *control_page;
    TownControl *owner_control;
    u8 *entry;
    s32 active_script;

    control = &town_actor_control;

    if (control->field_10 == owner) {
        s32 index = control->index;
        if (((S_8009B2C4_0 *)((u8 *)owner + D_800CFDD8[index]))->unk_3A != 0) {
            entry = (u8 *)(index + (u8 *)control);
            if (((S_8009B2C4_1 *)entry)->unk_3A == 1) {
                if (scene_object_payload_alias == (s32)&D_800924EC) {
                    object->vtable->func0(object, owner, context, extra_ptr);
                    return 1;
                }
            }
            if (scene_object_payload_alias == (s32)&D_80092698) {
                initialize_target_motion_state(object, owner, context, extra_ptr);
                return 1;
            }
            if (scene_object_payload_alias == (s32)&tracked_actor_callback_address) {
                if (D_800CFCCC == 0) {
                    initialize_target_motion(object, owner, context, extra_ptr);
                    return 1;
                }
            }
        }
        control_page = (TownControl *)0x800D0000;
    } else {
        control_page = (TownControl *)0x800D0000;
    }
    owner_control = (TownControl *)((u8 *)control_page - 0x34C);
    if (((owner_control->state != 0) && (owner_control->owner == owner)) ||
        ((((Rec_D_800CFCB4 *)owner)->unk_3B != 0) &&
         (((Rec_D_800CFCB4 *)owner)->unk_20 == owner_control))) {
        active_script = scene_object_payload_alias;
        if ((active_script == (s32)&D_80091F64) ||
            (active_script == (s32)&D_800920F4) ||
            (active_script == (s32)&D_8009204C)) {
            object->vtable->func18(object, owner, context, extra_ptr);
        }
    }
    return 0;
}

/* Update movement and height, transition the actor state, and copy its value to the context. */
void update_actor_surface_motion(void *actor, void *subject, void *motion, void *context) {
    s16 surface_height;
    void *actor_callback;
    s32 *actor_value;

    surface_height = get_smaller_query_result_capped_hex_80_writes_associated_output(motion, ((u8 *)&position_query_scratch));
    call_the_same_context_both_processing_routines(subject, motion);
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(subject, motion);
    if (*(u8 *)((u8 *)subject + 0x3B) == 0) {
        if (surface_height - *(s16 *)((u8 *)motion + 0xA) >= 4) {
            set_actor_drop_state(actor, subject, motion, context);
        } else {
            set_the_state_flag_initialize_s_fixed_point_clear_paired_field(subject, motion, surface_height);
            *(s32 *)((u8 *)motion + 0xC) = 0;
            *(s32 *)((u8 *)motion + 0x10) = 0;
            *(s32 *)((u8 *)motion + 0x14) = 0;
            *(void **)((u8 *)actor + 0x50) = actor_output_update_address;
        }
    }
    dispatch_active_town_object_script(actor, subject, motion, context);
    actor_callback = *(void **)((u8 *)actor + 0x50);
    if (actor_callback != actor_surface_callback_address && actor_callback != actor_output_update_address && actor_callback != actor_moving_target_address) {
        actor_value = *(s32 **)((u8 *)actor + 0x7C);
        if (actor_value != 0)
            *(s32 *)((u8 *)context + 8) = *actor_value;
    }
}

/* Runs handlers when any slot flag is set and copies the stored value for eligible states. */
void update_actor_slots_and_output(void *state_owner, void *update_target, void *update_context, void *output) {
    s32 slot;
    void *current_state;
    s32 *stored_value;

    for (slot = 0; slot < 6; slot++) {
        u8 *slot_flags = (u8 *)&town_actor_control + slot;

        if (slot_flags[0x3A] != 0 || slot_flags[0x40] != 0) {
            break;
        }
    }
    if (slot < 6) {
        if (*(u8 *)((u8 *)update_target + 0x3B) == 0) {
            set_actor_motion_state(state_owner, update_target, update_context, output);
        }
        handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(update_target, update_context);
        dispatch_active_town_object_script(state_owner, update_target, update_context, output);
    }
    current_state = *(void **)((u8 *)state_owner + 0x50);
    if (current_state != actor_surface_callback_address && current_state != actor_output_update_address && current_state != actor_moving_target_address) {
        stored_value = *(s32 **)((u8 *)state_owner + 0x7C);
        if (stored_value != 0) {
            *(s32 *)((u8 *)output + 8) = *stored_value;
        }
    }
}
