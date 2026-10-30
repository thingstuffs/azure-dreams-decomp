#ifndef DUNGEON_PLAYER_MOTION_H
#define DUNGEON_PLAYER_MOTION_H

/* Function contracts owned by src/dungeon/player/motion/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
void set_linked_actor_octant_facing(s32 index, s32 value);
void try_move_carrying_player(void *controller, s32 actor_id, SpriteFrameState *actor, EntityRec *actor_data);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
s32 resolve_player_input_facing(s16 direction_offset, u16 *flags, u16 *angle);

#endif
