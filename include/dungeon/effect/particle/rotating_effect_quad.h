#ifndef DUNGEON_EFFECT_PARTICLE_ROTATING_EFFECT_QUAD_H
#define DUNGEON_EFFECT_PARTICLE_ROTATING_EFFECT_QUAD_H

#include "common.h"

/* Quad body allocated by the animated target travel effect. */
typedef struct RotatingEffectQuadBody {
    u8 pad_00[0xA];
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x36];
    void *unk_44;
    void *unk_48;
    void *unk_4C;
    u16 unk_50;
    s16 unk_52;
    u16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    u16 unk_60;
    u16 unk_62;
    s16 unk_64;
    s16 unk_66;
} RotatingEffectQuadBody;

#endif
