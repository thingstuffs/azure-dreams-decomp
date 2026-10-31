#ifndef DUNGEON_PLAYER_STATE_H
#define DUNGEON_PLAYER_STATE_H

/* Function contracts owned by src/dungeon/player/state/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_item_entries.h"
void create_familiar_deployment_effect_with_owner_state(void *owner_body, ObjectPosition *source_pos, SpriteFrameState *owner);
void enter_directional_state_17(ActorRecord *state, void *unused, void *animation, ActorRecord *orientation);


void clear_slot_and_update_linked_state(DungeonItemEntry *slot);
s32 process_record_and_update_linked_state(DungeonItemEntry *request, void *record_data);

#endif
