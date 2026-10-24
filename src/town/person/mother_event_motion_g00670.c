/* G00670: mother event motion. */
/* Original-file evidence (G00670): inferred (adjacency/recipe/locality), inferred-strong - CL:town/engine@4A4DC, CL:town/func_800CA30C, CL:town/func_800CA364, CL:town/func_800CA490, PD:town/engine:80113220. */
#include "town/person/mother_event_motion_g00670.h"

/* Applies a motion offset or interpolates the position toward the object coordinates. */
void apply_mother_event_motion_offset(void *object, void *position, s32 update_arg) {
    s32 *motion_entry;
    s32 state;
    s32 frames_left;

    motion_entry = get_smallest_signed_overlap_axis_amount_two_intersecting_boxes(object, town_actor_control);
    if (motion_entry != 0) {
        state = motion_entry[0];
        if (state != 2) {
            if (state == 0) {
                ((s32 *)position)[0] -= motion_entry[1];
            } else if (state == 1) {
                ((s32 *)position)[1] -= motion_entry[1];
            }
            func_800C7C3C(object, position, update_arg);
            return;
        }
    }

    frames_left = --mother_event_ticks.value;
    if (frames_left <= 0) {
        install_stored_value_handler(object, position, update_arg);
        clear_mother_event_record_field(object, position, update_arg);
        *(u16 *)((u8 *)position + 2) = *(u16 *)((u8 *)object + 0x84);
        *(u16 *)((u8 *)position + 6) = *(u16 *)((u8 *)object + 0x86);
        return;
    }

    *(u16 *)((u8 *)position + 2) +=
        ((s16)*(u16 *)((u8 *)object + 0x84) -
         *(s16 *)((u8 *)position + 2)) / frames_left;
    *(u16 *)((u8 *)position + 6) +=
        ((s16)*(u16 *)((u8 *)object + 0x86) -
         *(s16 *)((u8 *)position + 6)) / frames_left;
}

/* Reset the object callback when the shared countdown expires after a zero check result. */
void reset_mother_event_callback_on_expiry(s32 object, s32 motion, s32 init_data, s32 check_arg) {
    if (select_object_setup_path(object, motion, init_data, check_arg) == 0) {
        if (--mother_event_ticks.value <= 0) {
            initialize_mother_event_with_timer_16((void *)object, motion, init_data);
        }
    }
}

/* Clear two state values, initialize the actor, and set its handler and randomized counter. */
void initialize_mother_event_actor(void *actor, void *state, s32 init_param) {
    *(s32 *)((u8 *)state + 0x10) = 0;
    *(s32 *)((u8 *)state + 0xC) = 0;
    initialize_object_entries((Struct800C5724 *)actor, (s8 *)init_param, (s32 *)D_800D5FC4);
    *(void **)((u8 *)actor + 0x50) = D_800C7604;
    *(s16 *)((u8 *)actor + 0x6C) = (s16) (scale_random_to_unsigned_halfword_limit(0x3F) + 0x15);
}

/* Try random directions against the bounds, then initialize the entity state. */
void choose_mother_event_direction(Rec_func_80094268_arg0 *entity, void *bounds_arg, s32 context_arg)
{
    s32 context;
    s32 attempts;
    s32 direction;

    context = context_arg;
    attempts = 0;
    do {
        direction = scale_random_to_unsigned_halfword_limit(4) & 0xFFFF;
        if (direction == 0) {
            s32 upper_edge;
            s32 bound_test;
            s32 extent;

            upper_edge = entity->unk_84.as_s16;
            extent = entity->unk_8C;
            bound_test = ((S_800C7AC4_1 *)bounds_arg)->unk_02;
            upper_edge += extent;
            bound_test = bound_test < upper_edge;
            if (bound_test != 0) {
                entity->unk_72.as_s16 = 0x400;
                break;
            }
        } else if (direction == 1) {
            s32 upper_edge;
            s32 bound_test;
            s32 extent;

            upper_edge = entity->unk_86.as_s16;
            extent = entity->unk_8E;
            bound_test = ((S_800C7AC4_1 *)bounds_arg)->unk_06;
            upper_edge += extent;
            bound_test = bound_test < upper_edge;
            if (bound_test != 0) {
                entity->unk_72.as_s16 = 0;
                break;
            }
        } else if (direction == 2) {
            s32 lower_edge;
            s32 extent;
            s32 bound_coord;

            lower_edge = entity->unk_84.as_s16;
            extent = entity->unk_8C;
            bound_coord = ((S_800C7AC4_1 *)bounds_arg)->unk_02;
            lower_edge -= extent;
            lower_edge = lower_edge < bound_coord;
            if (lower_edge != 0) {
                entity->unk_72.as_s16 = 0xC00;
                break;
            }
        } else {
            s32 lower_edge;
            s32 extent;
            s32 bound_coord;

            lower_edge = entity->unk_86.as_s16;
            extent = entity->unk_8E;
            bound_coord = ((S_800C7AC4_1 *)bounds_arg)->unk_06;
            lower_edge -= extent;
            lower_edge = lower_edge < bound_coord;
            if (lower_edge != 0) {
                entity->unk_72.as_s16 = 0x800;
                break;
            }
        }

        attempts++;
    } while (attempts < 0x10);

    initialize_object_entries((Struct800C5724 *)entity, (s8 *)context, &mother_event_object_entries);
    entity->unk_50.as_pv = &D_800C7674;
}

/* Initialize the object callback and set the shared timer to 16. */
void initialize_mother_event_with_timer_16(void *object, s32 unused, s32 init_data) {
    Timer *timer;

    initialize_object_entries(object, (s8 *)(init_data), &mother_event_object_entries);
    *(s32 **)((u8 *)object + 0x50) = &D_800C78A8;
    timer = &mother_event_ticks;
    timer->value = 0x10;
}
