#ifndef TOWN_EVENT_MOTION_H
#define TOWN_EVENT_MOTION_H
/* Prototypes of the functions defined in src/town/event/motion/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_D_800CFCB4.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_func_8009B828_arg0.h"
#include "shared/entity.h"
#include "shared/position_views.h"
#include "shared/town_state.h"

struct Actor;
struct Motion;
struct S_8009C120_0;
struct S_8009C120_2;
struct Subject;

/* initialize_heading_motion.c */
void initialize_heading_motion(void *owner, void *object, void *motion);

/* initialize_target_motion.c */
void initialize_target_motion(Rec_func_8009B828_arg0 *owner, Rec_D_800CFCB4 *target, EntityRec *parameters);

/* initialize_target_motion_state.c */
void initialize_target_motion_state(struct S_8009C120_2 *state, struct S_8009C120_0 *status, MotionDeltaView *values);

/* set_actor_motion_state.c */
void set_actor_motion_state(Rec_func_80094268_arg0 *object, Rec_D_800CFCB4 *state);

/* update_actor_with_controlled_motion.c */
void update_actor_with_controlled_motion(struct Actor *actor, struct Subject *subject, struct Motion *motion, TownMovementOutput *context);

/* update_input_motion_and_action.c */
void update_input_motion_and_action(void *controller, void *object, s32 update_arg);

/* update_motion_and_handle_terrain_contact.c */
void update_motion_and_handle_terrain_contact(void *object, Rec_D_800CFCB4 *collision, ObjectPosition *motion, s32 callback_arg);

/* update_motion_toward_shared_target.c */
void update_motion_toward_shared_target(Rec_func_8009B828_arg0 *state, s32 context, ObjectPosition *motion, s32 transition_arg);

/* update_motion_toward_town_target.c */
void update_motion_toward_town_target(void *state, s32 context, void *motion, s32 next_arg);

#endif
