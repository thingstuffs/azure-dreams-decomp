/* Dispatches town actor scripts and updates actor surface motion, slot state, and output values. */
/* inferred-strong actor_script_motion_g00549; joins CL:town/func_8009DB64; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8009DB64. */
#include "town/event/actor_script_motion_g00549.h"
#include "shared/entity_height_offsets.h"
#include "town/scene/flags.h"
#include "town/scene.h"
#include "town/scene/motion.h"
#include "town/event.h"
#include "town/event/motion_callbacks_api.h"
#include "town/event/state.h"
#include "town/event/motion.h"
#include "town/player/state.h"

/* Dispatches town object actions for the active script and owner state. */
s32 dispatch_active_town_object_script(TownObjectRecord *object, ColliderView *owner, ObjectPosition *context, struct SpriteFrameState *extra_ptr) {
    TownVtable *vtable;
    TownControl *control;
    TownControl *control_page;
    TownControl *owner_control;
    u8 *entry;
    s32 active_script;

    control = &town_actor_control;

    if (control->selected_entry == owner) {
        s32 index = control->index;
        if (((u8 *)owner + D_800CFDD8[index])[0x3A] != 0) {
            entry = (index + (u8 *)control);
            if (entry[0x3A] == 1) {
                if (scene_object_payload_alias == (s32)&D_800924EC) {
                    vtable = object->state_handlers;
                    vtable->func0(object, owner, context, extra_ptr);
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
        ((owner->pending_flags[1] != 0) &&
         (owner->slots[1] == owner_control))) {
        active_script = scene_object_payload_alias;
        if ((active_script == (s32)&D_80091F64) ||
            (active_script == (s32)&D_800920F4) ||
            (active_script == (s32)&D_8009204C)) {
            vtable = object->state_handlers;
            vtable->func18(object, owner, context, extra_ptr);
        }
    }
    return 0;
}

/* Update movement and height, transition the actor state, and copy its value to the context. */
void update_actor_surface_motion(TownObjectRecord *actor, void *subject, ObjectPosition *motion, SpriteFrameState *context) {
    s16 surface_height;
    void *actor_callback;
    HeightBandValues *values;

    surface_height = get_min_surface_probe_capped(motion, ((u8 *)&position_query_scratch));
    apply_bound_adjustments(subject, motion);
    resolve_collider_overlaps(subject, motion);
    if (*((u8 *)subject + 0x3B) == 0) {
        if (surface_height - motion->z.w.i >= 4) {
            set_actor_drop_state(actor, subject, motion, context);
        } else {
            stop_at_max_z(subject, motion, surface_height);
            motion->velocity_x = 0;
            motion->velocity_y = 0;
            motion->velocity_z = 0;
            actor->state_callback.as_pv = actor_output_update_address;
        }
    }
    dispatch_active_town_object_script(actor, subject, motion, context);
    actor_callback = actor->state_callback.as_pv;
    if (actor_callback != actor_surface_callback_address && actor_callback != actor_output_update_address && actor_callback != update_actor_with_controlled_motion) {
        values = actor->animation_tables.as_pv;
        if (values != 0)
            context->source = values->sources[0];
    }
}

/* Runs handlers when any slot flag is set and copies the stored value for eligible states. */
void update_actor_slots_and_output(TownObjectRecord *state_owner, void *update_target, ObjectPosition *update_context, SpriteFrameState *output) {
    Rec_D_800CFCB4 *target;
    s32 slot;
    void *current_state;
    HeightBandValues *values;

    for (slot = 0; slot < 6; slot++) {
        u8 *slot_flags = (u8 *)&town_actor_control + slot;

        if (slot_flags[0x3A] != 0 || slot_flags[0x40] != 0) {
            break;
        }
    }
    if (slot < 6) {
        target = update_target;
        if (target->unk_3B == 0) {
            set_actor_motion_state(state_owner, update_target, update_context, output);
        }
        resolve_collider_overlaps(update_target, update_context);
        dispatch_active_town_object_script(state_owner, update_target, update_context, output);
    }
    current_state = state_owner->state_callback.as_pm;
    if (current_state != actor_surface_callback_address && current_state != actor_output_update_address && current_state != update_actor_with_controlled_motion) {
        values = state_owner->animation_tables.as_pv;
        if (values != 0) {
            output->source = values->sources[0];
        }
    }
}
