#ifndef DUNGEON_EFFECT_SCREEN_ACTOR_LINKED_PARTICLE_H
#define DUNGEON_EFFECT_SCREEN_ACTOR_LINKED_PARTICLE_H

#include "common.h"
#include "shared/entity.h"

/* Body of the actor-linked node whose callback fills particle values. */
typedef struct ActorLinkedParticleEffectBody {
    ActorRecord *owner;
    u8 pad_04[6];
    s16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    s8 unk_10;
    u8 unk_11;
    u8 particle_values[0x40];
} ActorLinkedParticleEffectBody;

#endif
