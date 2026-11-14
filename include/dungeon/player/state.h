#ifndef DUNGEON_PLAYER_STATE_H
#define DUNGEON_PLAYER_STATE_H

/* Function contracts owned by src/dungeon/player/state/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_item_entries.h"
void create_familiar_deployment_effect_with_owner_state(void *owner_body, ObjectPosition *source_pos, SpriteFrameState *owner);
void enter_idle_timeout_pose(ActorRecord *state, ObjectPosition *unused, void *animation, ActorRecord *orientation);


void clear_item_slot(DungeonItemEntry *slot);
s32 resolve_item_attack(DungeonItemEntry *request, void *record_data);

#endif
