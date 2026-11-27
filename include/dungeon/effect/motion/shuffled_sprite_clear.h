#ifndef DUNGEON_EFFECT_MOTION_SHUFFLED_SPRITE_CLEAR_H
#define DUNGEON_EFFECT_MOTION_SHUFFLED_SPRITE_CLEAR_H

#include "common.h"

/* Body of a child effect that clears captured sprite columns in shuffled order. */
typedef struct ShuffledSpriteClearBody {
    s16 state;
    s16 timer;
    u8 pad_04[0x6];
    u16 unk_0A;
    u16 unk_0C;
    u8 pad_0E[0x1E];
    void *owner;
    u8 *target;
    void * parent;
} ShuffledSpriteClearBody;

#endif
