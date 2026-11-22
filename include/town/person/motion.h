#ifndef TOWN_PERSON_MOTION_H
#define TOWN_PERSON_MOTION_H
struct TownObjectRecord;
struct SpriteFrameState;
struct TownObjectRecord;
/* Prototypes of the functions defined in src/town/person/motion/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/town_object.h"
#include "records/Rec_func_800AAE98_arg0.h"
#include "records/Rec_func_800AB014_arg0.h"
#include "records/Rec_func_800C9B44_arg0.h"
#include "shared/dungeon_delay_views.h"
#include "shared/entity.h"

struct S_800CC070_1;

/* advance_bounded_motion.c */
void advance_bounded_motion(TownObjectRecord *entity, ObjectPosition *motion, struct SpriteFrameState *context, s32 check_param);

/* advance_mother_event_bounded_motion.c */
void advance_mother_event_bounded_motion(struct TownObjectRecord *entity, ObjectPosition *motion_state, struct SpriteFrameState *context);

/* advance_motion_and_clamp_limit.c */
void advance_motion_and_clamp_limit(TownObjectRecord *entity, ObjectPosition *motion, struct SpriteFrameState *context);

/* advance_motion_and_switch_handler.c */
void advance_motion_and_switch_handler(TownObjectRecord *object, ObjectPosition *motion, struct SpriteFrameState *context);

/* advance_reaction_motion_to_limit.c */
void advance_reaction_motion_to_limit(struct TownObjectRecord *state, struct ObjectPosition *motion, struct SpriteFrameState *context);

/* advance_vertical_motion_and_bounce.c */
void advance_vertical_motion_and_bounce(TownObjectRecord *actor, ObjectPosition *motion, struct SpriteFrameState *context);

/* expire_motion_timer.c */
void expire_motion_timer(struct TownObjectRecord *object, ObjectPosition *motion);

/* get_facing_sector.c */
u32 get_facing_sector(s32 angle);

/* initialize_object_animation_and_facing.c */
void initialize_object_animation_and_facing(TownObjectRecord *object, struct ObjectPosition *position, struct SpriteFrameState *sprite);

void move_reaction_toward_target(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *sprite);

/* move_coordinates_halfway_toward_target.c */
void move_coordinates_halfway_toward_target(struct TownObjectRecord *state, ObjectPosition *position);

/* move_mother_event_output_to_target.c */
void move_mother_event_output_to_target(TownObjectRecord *object, ObjectPosition *out, struct SpriteFrameState *sprite);

/* move_motion_value_halfway_toward.c */
void move_motion_value_halfway_toward(TownObjectRecord *actor, ObjectPosition *motion);

struct S_800AB5C0_1;
void approach_person_sample(TownObjectRecord *state, struct S_800AB5C0_1 *coords);

/* move_person_toward_sample.c */
void move_person_toward_sample(TownObjectRecord *object, ObjectPosition *position);

/* set_initial_jump_velocity.c */
void set_initial_jump_velocity(TownObjectRecord *jump_state, struct S_800CC070_1 *body, struct SpriteFrameState *sprite);

/* update_jump_motion.c */
void update_jump_motion(TownObjectRecord *actor, struct S_800CC070_1 *motion, struct SpriteFrameState *sprite, s16 jump_velocity);

/* update_spin_vertical_motion_and_bounces.c */
void update_spin_vertical_motion_and_bounces(TownObjectRecord *entity, ObjectPosition *motion, struct SpriteFrameState *context);

/* update_turning_motion_and_timer.c */
void update_turning_motion_and_timer(struct TownObjectRecord *actor, ObjectPosition *position, void *update_param, s32 check_param);

#endif
