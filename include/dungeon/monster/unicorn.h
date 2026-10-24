#ifndef DUNGEON_MONSTER_UNICORN_H
#define DUNGEON_MONSTER_UNICORN_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void update_actor_move_animation_and_recovery(void *action, ObjectPosition *motion, SpriteFrameState *sprite, void *actor);

void *spawn_unicorn(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_height);

/* Frame tables the spawn factory installs: the default set, and the set used
 * when it starts the monster asleep. */
extern u8 unicorn_frame_set[];
extern u8 unicorn_sleep_direction_frames[];
/* Action continuation installed in ActorRecord.unk_8C by the spawn and move handlers. */
extern u8 unicorn_action_continuation_address;

#endif
