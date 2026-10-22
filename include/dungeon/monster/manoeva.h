#ifndef DUNGEON_MONSTER_MANOEVA_H
#define DUNGEON_MONSTER_MANOEVA_H

/* Function contracts owned by src/dungeon/monster/manoeva/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"
void advance_actor_turn_path(void *move_data_in, void *context, void *tile_in, void *actor_in);
void spawn_offset_motion_object(void *parent_data, MovingPosition *origin, Rec_D_80082E80 *source_data, s16 position_index);
void update_effect_visuals_and_lifetime();


#endif
