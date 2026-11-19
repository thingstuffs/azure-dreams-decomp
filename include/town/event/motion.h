#ifndef TOWN_EVENT_MOTION_H
#define TOWN_EVENT_MOTION_H
/* Prototypes of the functions defined in src/town/event/motion/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_D_800CFCB4.h"
#include "shared/town_object.h"
#include "records/Rec_func_8009B828_arg0.h"
#include "shared/entity.h"
#include "shared/position_views.h"
#include "shared/town_state.h"

struct ColliderView;
struct Actor;
struct Motion;
struct Subject;

/* initialize_heading_motion.c */
void initialize_heading_motion(void *owner, void *object, void *motion);

/* initialize_target_motion.c */
void initialize_target_motion(TownObjectRecord *owner, struct ColliderView *target, ObjectPosition *parameters, void *unused);

/* initialize_target_motion_state.c */
void initialize_target_motion_state(TownObjectRecord *state, struct ColliderView *status, ObjectPosition *values, void *unused_extra_ptr);

/* set_actor_motion_state.c */
void set_actor_motion_state(TownObjectRecord *object, Rec_D_800CFCB4 *state, void *unused_update_context, void *unused_output);

/* update_actor_with_controlled_motion.c */
struct SpriteFrameState;
void update_actor_with_controlled_motion(TownObjectRecord *actor, struct ColliderView *subject, ObjectPosition *motion, struct SpriteFrameState *context);

/* update_input_motion_and_action.c */
void update_input_motion_and_action(void *controller, ObjectPosition *object, s32 update_arg);

/* update_motion_and_handle_terrain_contact.c */
void update_motion_and_handle_terrain_contact(void *object, struct ColliderView *collision, ObjectPosition *motion, s32 callback_arg);

/* update_motion_toward_shared_target.c */
void update_motion_toward_shared_target(TownObjectRecord *state, struct ColliderView *context, ObjectPosition *motion, struct SpriteFrameState *sprite);

/* update_motion_toward_town_target.c */
void update_motion_toward_town_target(TownObjectRecord *state, struct ColliderView *context, ObjectPosition *motion, struct SpriteFrameState *sprite);

#endif
