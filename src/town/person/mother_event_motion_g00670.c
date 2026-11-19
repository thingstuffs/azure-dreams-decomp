/* mother event motion. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/engine@4A4DC, CL:town/func_800CA30C, CL:town/func_800CA364, CL:town/func_800CA490, PD:town/engine:80113220. */
#include "town/person/mother_event_motion_g00670.h"
#include "town/scene/collision.h"
#include "engine/window.h"
#include "town/person/motion.h"

/* Applies a motion offset or interpolates the position toward the object coordinates. */
void apply_mother_event_motion_offset(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *update_arg) {
    CollisionOverlap *motion_entry;
    s32 state;
    s32 frames_left;

    motion_entry = get_box_overlap_axis(object, &town_actor_control);
    if (motion_entry != 0) {
        state = motion_entry->axis;
        if (state != 2) {
            if (state == 0) {
                position->x.v -= motion_entry->amount;
            } else if (state == 1) {
                position->y.v -= motion_entry->amount;
            }
            begin_mother_event_pause(object, position, update_arg);
            return;
        }
    }

    frames_left = --mother_event_ticks.value;
    if (frames_left <= 0) {
        install_stored_value_handler(object, position, update_arg);
        clear_mother_event_record_field(object, position, update_arg);
        position->x.w.i = object->unk_84;
        position->y.w.i = object->unk_86;
        return;
    }

    position->x.w.i +=
        (object->unk_84 -
         position->x.w.i) / frames_left;
    position->y.w.i +=
        (object->unk_86 -
         position->y.w.i) / frames_left;
}

/* Reset the object callback when the shared countdown expires after a zero check result. */
void reset_mother_event_callback_on_expiry(TownObjectRecord *object, ObjectPosition *motion, SpriteFrameState *init_data, s32 check_arg) {
    if (select_object_setup_path(object, motion, init_data) == 0) {
        if (--mother_event_ticks.value <= 0) {
            start_mother_event_ticks(object, motion, init_data);
        }
    }
}

/* Clear two state values, initialize the actor, and set its handler and randomized counter. */
void initialize_mother_event_actor(TownObjectRecord *actor, ObjectPosition *state, SpriteFrameState *init_param) {
    state->velocity_y = 0;
    state->velocity_x = 0;
    initialize_object_entries(actor, init_param, (s32 *)D_800D5FC4);
    actor->unk_50.as_pv = D_800C7604;
    actor->timer = (s16) (scale_random_by_limit(0x3F) + 0x15);
}

/* Try random directions against the bounds, then initialize the entity state. */
void choose_mother_event_direction(TownObjectRecord *entity, ObjectPosition *bounds_arg, SpriteFrameState *context)
{
    s32 attempts;
    s32 direction;

    attempts = 0;
    do {
        direction = scale_random_by_limit(4) & 0xFFFF;
        if (direction == 0) {
            s32 upper_edge;
            s32 bound_test;
            s32 extent;

            upper_edge = entity->unk_84;
            extent = entity->unk_8C;
            bound_test = bounds_arg->x.w.i;
            upper_edge += extent;
            bound_test = bound_test < upper_edge;
            if (bound_test != 0) {
                entity->heading = 0x400;
                break;
            }
        } else if (direction == 1) {
            s32 upper_edge;
            s32 bound_test;
            s32 extent;

            upper_edge = (entity->unk_86);
            extent = entity->unk_8E;
            bound_test = bounds_arg->y.w.i;
            upper_edge += extent;
            bound_test = bound_test < upper_edge;
            if (bound_test != 0) {
                entity->heading = 0;
                break;
            }
        } else if (direction == 2) {
            s32 lower_edge;
            s32 extent;
            s32 bound_coord;

            lower_edge = entity->unk_84;
            extent = entity->unk_8C;
            bound_coord = bounds_arg->x.w.i;
            lower_edge -= extent;
            lower_edge = lower_edge < bound_coord;
            if (lower_edge != 0) {
                entity->heading = 0xC00;
                break;
            }
        } else {
            s32 lower_edge;
            s32 extent;
            s32 bound_coord;

            lower_edge = (entity->unk_86);
            extent = entity->unk_8E;
            bound_coord = bounds_arg->y.w.i;
            lower_edge -= extent;
            lower_edge = lower_edge < bound_coord;
            if (lower_edge != 0) {
                entity->heading = 0x800;
                break;
            }
        }

        attempts++;
    } while (attempts < 0x10);

    initialize_object_entries(entity, context, &mother_event_object_entries);
    entity->unk_50.as_pv = advance_mother_event_bounded_motion;
}

/* Initialize the object callback and set the shared timer to 16. */
void start_mother_event_ticks(TownObjectRecord *object, ObjectPosition *unused, SpriteFrameState *init_data) {
    Timer *timer;

    initialize_object_entries(object, init_data, &mother_event_object_entries);
    object->unk_50.as_pm = D_800C78A8;
    timer = &mother_event_ticks;
    timer->value = 0x10;
}
