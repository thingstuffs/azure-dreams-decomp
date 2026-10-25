#ifndef DUNGEON_MONSTER_MANOEVA_H
#define DUNGEON_MONSTER_MANOEVA_H

/* Function contracts owned by src/dungeon/monster/manoeva/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"
#include "records/Rec_func_800A9E70_arg0.h"
void advance_actor_turn_path(Rec_func_800A9E70_arg0 *move_data_in, void *context, SpriteFrameState *tile_in, ActorRecord *actor_in);
void spawn_offset_motion_object(void *parent_data, MovingPosition *origin, Rec_D_80082E80 *source_data, s16 position_index);
void update_effect_visuals_and_lifetime();








void advance_actor_sprite_action(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void *spawn_manoeva(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_height);

#endif
