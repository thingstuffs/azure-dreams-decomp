#ifndef DUNGEON_MONSTER_PICKET_H
#define DUNGEON_MONSTER_PICKET_H
struct ActorRecord;
struct S_80174978_0;

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void update_picket_jump_to_tile(ActorRecord *jump_state, ObjectPosition *motion, SpriteFrameState *map_entity, ActorRecord *actor);
void update_picket_jump_attack(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);



void update_picket_item_drop_effect(struct S_80174978_0 *actor, ObjectPosition *motion, SpriteFrameState *visual);
void update_picket_dash_and_retreat(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "records/Rec_func_800AD058_arg2.h"
void create_picket_held_item_sprite(ObjectPosition *source, Rec_func_800AD058_arg2 *record, ActorRecord *appearance);

void * move_eligible_item(void *origin, ActorRecord *actor);
void * pick_up_adjacent_item(void *origin, struct ActorRecord *actor);
void update_picket_behavior(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);

void start_picket_action_if_idle(ActorRecord *entity, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);

#endif
