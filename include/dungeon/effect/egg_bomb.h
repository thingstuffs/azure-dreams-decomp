#ifndef DUNGEON_EFFECT_EGG_BOMB_H
#define DUNGEON_EFFECT_EGG_BOMB_H

#include "shared/entity.h"

/* Body of the object that spawns and tracks the egg bomb monster. */
typedef struct EggBombBody {
    u8 unk_00;
    u8 pad_01[3];
    ActorRecord *unk_04;
    u8 pad_08[2];
    u16 unk_0A;
    u16 unk_0C;
    s16 unk_0E;
} EggBombBody;

#endif
