#ifndef DUNGEON_MONSTER_VIPER_H
#define DUNGEON_MONSTER_VIPER_H

#include "dungeon/monster/viper/effect.h"
#include "shared/sprite_frame_state.h"

void update_timed_effect_size_and_position(struct ViperTimedEffectBody *effect, ObjectPosition *position, SpriteFrameState *visual, void *unused_actor);

#endif
