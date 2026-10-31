#ifndef DUNGEON_ACTOR_ANIMATION_H
#define DUNGEON_ACTOR_ANIMATION_H

/* Function contracts owned by src/dungeon/actor/animation/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "dungeon/actor/motion.h"
void *reset_actor_animation_state(ActorRecord *body);
void finish_paralyzed_actor_action(ActorRecord *entity, void *unused_1, SpriteFrameState *unused_2, ActorRecord *context);


void update_trailing_effect_animation(ActorTrailWork *effect, TrailMotion *transform, SpriteFrameState *render_data);

/* dungeon/actor/animation/initialize_actor_sprite_and_animation.c */
void initialize_actor_sprite_and_animation(void *entity, void *position, SpriteFrameState *sprite, s32 init_flags);

#endif
