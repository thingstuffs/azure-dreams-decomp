#ifndef DUNGEON_MONSTER_KID_H
#define DUNGEON_MONSTER_KID_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void advance_stored_actor_path(void *motion, void *context, SpriteFrameState *sprite, void *move_state);

void advance_entity_animation_actions(void *action, void *context, SpriteFrameState *sprite, void *entity);
void update_actor_action_and_animation(void *controller_in, EntityRec *motion, SpriteFrameState *sprite, EntityRec *actor);



void advance_fading_directional_entity(void *anim_state, ObjectPosition *motion, void *sprite, void *entity);
void update_staged_actor_movement(void *action, ObjectPosition *motion, SpriteFrameState *tile, void *actor);

#endif
