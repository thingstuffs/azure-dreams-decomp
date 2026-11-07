#ifndef DUNGEON_EFFECT_PARTICLE_ENTRY_PLAY_SOUND_IF_ENABLED_H
#define DUNGEON_EFFECT_PARTICLE_ENTRY_PLAY_SOUND_IF_ENABLED_H

#include "dungeon/effect/spell_effect.h"

/* Spell state for attachment tracking and directional particle spawning. */
typedef struct AttachedParticleChainSpellBody {
    SpellEffectHeader spell;
    u8 pad_0C[0x72];
    s16 unk_7E;
    u8 pad_80[0x2];
    u16 unk_82;
    s16 unk_84;
    s16 unk_86;
    s16 unk_88;
    u8 pad_8A[0x6];
    u8 *unk_90;
    ObjectPosition *unk_94;
    u8 pad_98[0x10];
    u8 unk_A8;
    u8 unk_A9;
    u8 pad_AA[0x6];
    s32 unk_B0;
    s32 unk_B4;
    s32 unk_B8;
} AttachedParticleChainSpellBody;

#endif
