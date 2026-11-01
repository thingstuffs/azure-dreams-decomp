#ifndef DUNGEON_MONSTER_MANOEVA_ACTION_SPRITE_EFFECT_H
#define DUNGEON_MONSTER_MANOEVA_ACTION_SPRITE_EFFECT_H

#include "common.h"
#include "shared/dungeon_moving_views.h"
#include "shared/sprite_frame_state.h"

typedef struct ActionSpriteEffectBody {
    u8 pad_00[0x18];
    void *source;
    union { void *pointer; s32 value; } linked_position;
} ActionSpriteEffectBody;

void copy_linked_position_and_check_status(ActionSpriteEffectBody *object, MovingPosition *dest, SpriteFrameState *status);

#endif
