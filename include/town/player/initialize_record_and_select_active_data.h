#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

#ifndef TOWN_PLAYER_INITIALIZE_RECORD_AND_SELECT_ACTIVE_DATA_H
#define TOWN_PLAYER_INITIALIZE_RECORD_AND_SELECT_ACTIVE_DATA_H
struct ObjectPosition;

struct SpriteFrameState;

void initialize_record_and_select_active_data(void *record, ObjectPosition *position, SpriteFrameState *sprite);

#endif
