#ifndef TOWN_PERSON_MOTION_H
#define TOWN_PERSON_MOTION_H
/* Prototypes of the functions defined in src/town/person/motion/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_func_800AAE98_arg0.h"
#include "records/Rec_func_800AB014_arg0.h"
#include "records/Rec_func_800C9B44_arg0.h"
#include "shared/dungeon_delay_views.h"
#include "shared/entity.h"

struct S_800C355C_1;
struct S_800C3FC8_0;
struct S_800C5B48_1;
struct S_800C7674_0;
struct S_800CC070_0;
struct S_800CC070_1;

/* advance_bounded_motion.c */
void advance_bounded_motion(struct S_800C355C_1 *entity, void *motion, void *context, s32 check_param);

/* advance_mother_event_bounded_motion.c */
void advance_mother_event_bounded_motion(struct S_800C7674_0 *entity, EntityRec *motion_state, void *context);

/* advance_motion_and_clamp_limit.c */
void advance_motion_and_clamp_limit(Rec_func_80094268_arg0 *entity, EntityRec *motion, void *context);

/* advance_motion_and_switch_handler.c */
void advance_motion_and_switch_handler(Rec_func_80094268_arg0 *object, EntityRec *motion, void *context);

/* advance_reaction_motion_to_limit.c */
void advance_reaction_motion_to_limit(Rec_func_800C9B44_arg0 *state, EntityRec *motion, s32 context);

/* advance_vertical_motion_and_bounce.c */
void advance_vertical_motion_and_bounce(Rec_func_80094268_arg0 *actor, EntityRec *motion, void *context);

/* expire_motion_timer.c */
void expire_motion_timer(struct S_800C3FC8_0 *object, ObjectPosition *motion);

/* get_facing_sector.c */
u32 get_facing_sector(s32 angle);

/* initialize_object_animation_and_facing.c */
void initialize_object_animation_and_facing(void *object, void *position, void *animation_state);

/* move_coordinates_halfway_toward_target.c */
void move_coordinates_halfway_toward_target(void *state, s32 *coords);

/* move_mother_event_output_to_target.c */
void move_mother_event_output_to_target(void *object, void *out, void *setup_context);

/* move_motion_value_halfway_toward.c */
void move_motion_value_halfway_toward(struct S_800C5B48_1 *actor, DelayMotionZ *motion);

/* move_person_toward_sample.c */
void move_person_toward_sample(Rec_func_800AB014_arg0 *object, Rec_func_800AAE98_arg0 *position);

/* set_initial_jump_velocity.c */
void set_initial_jump_velocity(struct S_800CC070_0 *jump_state, struct S_800CC070_1 *body, void *context);

/* update_jump_motion.c */
void update_jump_motion(struct S_800CC070_0 *actor, struct S_800CC070_1 *motion, void *animation_id, s16 jump_velocity);

/* update_spin_vertical_motion_and_bounces.c */
void update_spin_vertical_motion_and_bounces(Rec_func_80094268_arg0 *entity, EntityRec *motion, void *context);

/* update_turning_motion_and_timer.c */
void update_turning_motion_and_timer(void *actor, void *position, void *update_param, s32 check_param);

#endif
