#ifndef DUNGEON_MODULES_H
#define DUNGEON_MODULES_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void func_8014E9A8(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void func_8015A9A8(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void func_801609A8(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void func_8016C9A8(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/tile_object.h"
void choose_block_move_slot_a(Rec_func_800A9E70_arg0 *move_data, void *context, TileObject *position_data, ActorRecord *actor_data);

#endif
