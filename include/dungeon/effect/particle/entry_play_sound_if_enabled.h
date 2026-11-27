#ifndef DUNGEON_EFFECT_PARTICLE_ENTRY_PLAY_SOUND_IF_ENABLED_H
#define DUNGEON_EFFECT_PARTICLE_ENTRY_PLAY_SOUND_IF_ENABLED_H

#include "dungeon/effect/spell_effect.h"

/* Spell state for attachment tracking and directional particle spawning. */
typedef struct AttachedParticleChainSpellBody {
    SpellEffectHeader spell;
    u8 pad_0C[0x72];
    s16 direction;
    u8 pad_80[0x2];
    u16 frame_count;
    s16 phase_timer;
    s16 end_time;
    s16 lead_marker;
    u8 pad_8A[0x6];
    u8 *lead_node;
    ObjectPosition *lead_position;
    u8 pad_98[0x10];
    u8 front_tile_x;
    u8 front_tile_y;
    u8 pad_AA[0x6];
    s32 spawn_x;
    s32 spawn_y;
    s32 spawn_z;
} AttachedParticleChainSpellBody;

#endif
