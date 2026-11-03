#ifndef TOWN_PLAYER_INPUT_H
#define TOWN_PLAYER_INPUT_H
struct SpriteFrameState;
/* Prototypes of the functions defined in src/town/player/input/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"

struct S_80091260_2;

/* dispatch_actor_input_actions.c */

/* initialize_input_driven_scene_object.c */
void initialize_input_driven_scene_object(s32 **outputData, ObjectPosition *state, s32 setupValue);

/* update_actor_input_actions.c */
void update_actor_input_actions(void *context, ObjectPosition *entity, s32 update_arg);

/* update_actor_input_and_interaction.c */

void dispatch_actor_input_actions(struct S_80091260_2 *actor, ObjectPosition *position, struct SpriteFrameState *sprite);

void update_actor_input_and_interaction(void *action_state, ObjectPosition *actor, struct SpriteFrameState *sprite);

#endif
