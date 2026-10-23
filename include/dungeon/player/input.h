#ifndef DUNGEON_PLAYER_INPUT_H
#define DUNGEON_PLAYER_INPUT_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void handle_carrying_player_input(void *object, void *aux_entity, SpriteFrameState *sprite, void *entity);

#endif
