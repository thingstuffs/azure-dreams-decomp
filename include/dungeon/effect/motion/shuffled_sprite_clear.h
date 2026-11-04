#ifndef DUNGEON_EFFECT_MOTION_SHUFFLED_SPRITE_CLEAR_H
#define DUNGEON_EFFECT_MOTION_SHUFFLED_SPRITE_CLEAR_H

#include "common.h"

/* Body of a child effect that clears captured sprite columns in shuffled order. */
typedef struct ShuffledSpriteClearBody {
    union { s16 s; u16 u; u16 p; } unk_00;   /* accessed as both */
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x6];
    u16 unk_0A;
    u16 unk_0C;
    u8 pad_0E[0x1E];
    void *unk_2C;
    union { void * s; u8 * u; } unk_30;   /* accessed as both */
    void * unk_34;
} ShuffledSpriteClearBody;

#endif
