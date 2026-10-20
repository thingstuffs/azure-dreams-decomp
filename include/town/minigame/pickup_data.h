#ifndef TOWN_MINIGAME_PICKUP_DATA_H
#define TOWN_MINIGAME_PICKUP_DATA_H

#include "common.h"

/* Input records prepared by update_betting_effect. The source x halfword
 * at +0x54 is signed. These input views do not describe ObjectNodeHeader
 * or the separate SpriteFrameState rendering subrecord. */
typedef struct minigame_pickup_source {
    s16 kind;
    s16 unused;
    void *owner;
    u8 pad08[0x4C];
    s16 x;
    s16 y;
} minigame_pickup_source;

typedef struct minigame_pickup_initial {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 f;
} minigame_pickup_initial;

void initialize_source_and_initial_data(minigame_pickup_source *, minigame_pickup_initial *);

#endif
