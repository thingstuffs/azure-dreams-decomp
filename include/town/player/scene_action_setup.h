#ifndef INCLUDE_TOWN_PLAYER_SCENE_ACTION_SETUP_H
#define INCLUDE_TOWN_PLAYER_SCENE_ACTION_SETUP_H
struct SpriteFrameState;
struct ObjectPosition;

#include "common.h"

struct SceneActionReset;
struct EntityRec;

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
void init_target_action_clearing_slot_one(struct SceneActionReset *object, void *position, void *handler_context);


/* Registered code-address alias for forward_player_motion_state. */


struct TownObjectRecord;
void initialize_player_linked_record(struct TownObjectRecord *object, void *unused, void *output);
void advance_player_state(struct TownObjectRecord *actor, struct EntityRec *position, struct SpriteFrameState *output);

#endif
