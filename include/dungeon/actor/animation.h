#ifndef DUNGEON_ACTOR_ANIMATION_H
#define DUNGEON_ACTOR_ANIMATION_H

/* Function contracts owned by src/dungeon/actor/animation/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "dungeon/actor/motion.h"
void *reset_actor_animation_state(void *entity);


void update_trailing_effect_animation(ActorTrailWork *effect, TrailMotion *transform, SpriteFrameState *render_data);

#endif
