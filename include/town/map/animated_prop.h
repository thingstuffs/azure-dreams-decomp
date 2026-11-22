#ifndef TOWN_MAP_ANIMATED_PROP_H
#define TOWN_MAP_ANIMATED_PROP_H

#include "town/scene/list_setup.h"

struct SpriteSourceEntry;

/* The Yorozu and default prop initializers install the same three-source animation. */
typedef struct TownPropAnimationActor {
    TownSceneListNode scene;
    u8 pad_18[0x30];
    const u8 *interaction_script;
    u8 pad_4C[4];
    s32 unk_50;
    u8 pad_54[0x14];
    s16 state;
    u8 pad_6A[0x36];
    struct SpriteSourceEntry *sources[3];
} TownPropAnimationActor;

#endif
