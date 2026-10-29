#include "shared/position_query.h"
#include "town/scene/collision.h"
#include "common.h"
#include "shared/town_state.h"
#include "records/Rec_D_800CFCB4.h"
#include "town/scene/flags.h"

typedef struct Actor Actor;
typedef struct Subject Subject;
typedef struct Motion Motion;


typedef void (*TownCallback)(Actor *, Subject *, Motion *, TownMovementOutput *);

struct Motion {
    u16 field_00;
    u16 x;
    u16 field_04;
    u16 y;
    u16 field_08;
    s16 height;
};

struct Subject {
    u8 pad_00[0x3B];
    u8 state;
};

struct Actor {
    u8 pad_00[0x50];
    TownCallback state;
    u8 pad_54[0x28];
    s32 *value;
};


typedef struct TownControl {
    u8 pad_00[0x10];
    Subject *subject;
    u8 pad_14[4];
    s32 index;
    u8 pad_1C[0x80];
} TownControl;

typedef struct TownState {
    u8 pad_00[8];
    Motion *target;
    u8 pad_0C[0x14];
    TownCallback current;
} TownState;

typedef struct MotionDelta {
    u16 x;
    u16 y;
} MotionDelta;

extern s32 get_smaller_query_result_capped_hex_80_writes_associated_output(EntityRec *source, s32 *out_detail);
extern void call_the_same_context_both_processing_routines(Subject *, Motion *);
extern void select_object_value_by_height_band(Actor *, Subject *, Motion *, TownMovementOutput *);
extern void set_actor_drop_state(Actor *, Subject *, Motion *, TownMovementOutput *);

extern void D_800924EC(void *context, EntityRec *entity, s32 update_arg);
extern void actor_surface_callback_address(void *actor, void *subject, void *motion, void *context);
extern void actor_output_update_address(void *state_owner, void *update_target, void *update_context, void *output);
extern void update_actor_with_controlled_motion(Actor *, Subject *, Motion *, TownMovementOutput *);

extern TownState scene_object_list_anchor;
extern TownControl town_actor_control;
extern MotionDelta D_800CFDF0[];
extern MotionDelta D_800CFE08[];

/* Update town movement and height, then copy the actor value into the context. */
void update_actor_with_controlled_motion(Actor *actor, Subject *subject, Motion *motion,
                   TownMovementOutput *context)
{
    TownControl *control = &town_actor_control;
    TownState *town_state;
    TownCallback *town_callback;
    MotionDelta *x_deltas;
    MotionDelta *y_deltas;
    TownCallback actor_callback;
    s16 surface_height;
    s32 control_index;
    s32 *actor_value;

    if ((control->subject != subject) || ((control_index = control->index), ((u8 *)control)[control_index + 0x3A] != 1)
        || ((town_callback = &scene_object_list_anchor.current), (*town_callback != D_800924EC))) {
        select_object_value_by_height_band(actor, subject, motion, context);
    } else {
        town_state = &scene_object_list_anchor;
        x_deltas = D_800CFDF0;
        motion->x += x_deltas[control_index].x;
        y_deltas = D_800CFE08;
        motion->y += y_deltas[control->index].x;
        town_state->target->x += x_deltas[control->index].x;
        town_state->target->y += y_deltas[control->index].x;
    }
    surface_height = get_smaller_query_result_capped_hex_80_writes_associated_output(motion, ((u8 *)&position_query_scratch));
    call_the_same_context_both_processing_routines(subject, motion);
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(subject, motion);
    if (subject->state == 0) {
        if (surface_height - motion->height >= 4) {
            set_actor_drop_state(actor, subject, motion, context);
        } else {
            set_the_state_flag_initialize_s_fixed_point_clear_paired_field(subject, motion, surface_height);
        }
    }

    actor_callback = actor->state;
    if ((actor_callback != actor_surface_callback_address) &&
        (actor_callback != actor_output_update_address) &&
        (actor_callback != update_actor_with_controlled_motion)) {
        actor_value = actor->value;
        if (actor_value != 0) {
            context->value = *actor_value;
        }
    }
}
