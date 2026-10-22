#ifndef DUNGEON_PLAYER_STATE_H
#define DUNGEON_PLAYER_STATE_H

/* Function contracts owned by src/dungeon/player/state/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
void create_familiar_deployment_effect_with_owner_state(s32 priority, EntityRec *source_pos, Rec_D_80082E80 *owner);
void enter_directional_state_17(void *state, void *unused, void *animation, void *orientation);


#endif
