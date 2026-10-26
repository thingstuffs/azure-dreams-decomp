#ifndef INCLUDE_TOWN_PLAYER_SCENE_ACTION_SETUP_H
#define INCLUDE_TOWN_PLAYER_SCENE_ACTION_SETUP_H

#include "common.h"

struct SceneActionReset;
struct EntityRec;

void update_actor_and_dispatch_state(void *actor, struct EntityRec *record, s32 context);
/* Registered code-address alias for update_actor_and_dispatch_state. */
void D_8009204C(void *actor, struct EntityRec *record, s32 context);

void initialize_flagged_actor_action_a(void *actor, void *action_id, void *action_state);
void initialize_flagged_actor_action_b(void *actor, void *action_id, void *action_state);
void initialize_flagged_actor_action_c(void *actor, void *action_id, void *action_state);
void initialize_flagged_actor_action_d(void *actor, void *action_id, void *action_state);
void initialize_optional_scene_state_a(void *object, s32 selector, void *state);
void initialize_optional_scene_state_b(void *object, s32 selector, void *state);
void initialize_optional_scene_state_c(void *object, s32 selector, void *state);
void initialize_scene_state_four(struct SceneActionReset *object, void *position, void *handler_context);
void initialize_scene_state_twenty_one(struct SceneActionReset *object, void *position, void *handler_context);


void forward_player_motion_state(void *state, s32 value, s32 mode);
/* Registered code-address alias for forward_player_motion_state. */
void player_slot_state_address(void *state, s32 value, s32 mode);

#endif
