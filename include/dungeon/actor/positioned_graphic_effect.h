#ifndef DUNGEON_ACTOR_POSITIONED_GRAPHIC_EFFECT_H
#define DUNGEON_ACTOR_POSITIONED_GRAPHIC_EFFECT_H

#include "common.h"

/* Body allocated by create_positioned_graphic_object and faded by its update callback. */
typedef struct PositionedGraphicEffectBody {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x5C];
    s16 phase;
    s16 frames_left;
} PositionedGraphicEffectBody;

#endif
