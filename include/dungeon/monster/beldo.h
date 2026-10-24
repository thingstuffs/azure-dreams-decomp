#ifndef DUNGEON_MONSTER_BELDO_H
#define DUNGEON_MONSTER_BELDO_H

/* Function contracts owned by src/dungeon/monster/beldo/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"
void create_attached_sprite_with_offset(void *owner_data, MovingPosition *base_position, SpriteFrameState *sprite_template, s16 offset_id);


void run_actor_callbacks_and_adjust_global_flag(void *entity_ptr, void *motion, void *check_arg, void *actor_arg);

#endif
