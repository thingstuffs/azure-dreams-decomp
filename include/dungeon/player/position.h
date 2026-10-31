#ifndef DUNGEON_PLAYER_POSITION_H
#define DUNGEON_PLAYER_POSITION_H

/* Function contracts owned by src/dungeon/player/position/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "records/Rec_func_8008D024_arg0.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
s32 begin_front_tile_attack(ActorRecord *body, void *unused, void *position_arg, void *entity_arg);
void begin_special_tile_transition(Rec_func_8008D024_arg0 *state, s32 unused, SpriteFrameState *entity, ActorRecord *actor);
void reset_actor_motion_at_sprite_tile(void *actor_state, void *map_entry, void *sprite, void *entity);




void advance_alternate_tile_center_motion(void *actor, ObjectPosition *motion, SpriteFrameState *sprite, EntityRec *facing);
void advance_normal_tile_center_motion(void *entity, ObjectPosition *motion, SpriteFrameState *sprite, EntityRec *facing);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
s16 check_tile_entry_at_adjusted_height(void *context, s32 data, SpriteFrameState *tile, void *state_data);

s16 find_flagged_tile_entry(ActorRecord *body, s32 unused, void *position, void *lookup_context);

#endif
