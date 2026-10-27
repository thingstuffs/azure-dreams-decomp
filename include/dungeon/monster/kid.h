#ifndef DUNGEON_MONSTER_KID_H
#define DUNGEON_MONSTER_KID_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void advance_stored_actor_path(void *motion, ObjectPosition *context, SpriteFrameState *sprite, void *move_state);

void advance_entity_animation_actions(ActorRecord *action, ObjectPosition *context, SpriteFrameState *sprite, void *entity);
void update_actor_action_and_animation(void *controller_in, ObjectPosition *motion, SpriteFrameState *sprite, EntityRec *actor);



void advance_fading_directional_entity(void *anim_state, ObjectPosition *motion, SpriteFrameState *sprite, void *entity);
void update_staged_actor_movement(void *action, ObjectPosition *motion, SpriteFrameState *tile, void *actor);

/* Callback entry points. */
void animate_effect_colors(void *effect_state, s32 unused, void *primitive);
void initialize_counted_entity_action(void *entity_data, ObjectPosition *unused_1, s32 unused_2, void *other_data);

#endif
