#ifndef DUNGEON_MONSTER_NYUEL_H
#define DUNGEON_MONSTER_NYUEL_H

/* Function contracts owned by src/dungeon/monster/nyuel/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
s32 check_movement_and_initialize_action(void *action_state, void *action_ctx, SpriteFrameState *sprite, ActorRecord *actor);
void start_directional_animation_if_allowed(void *action_state, void *action_context, SpriteFrameState *sprite, EntityRec *actor);
void update_actor_movement_and_tile_position(u8 *object, void *entry_context, u8 *tile, u8 *actor);


#endif
