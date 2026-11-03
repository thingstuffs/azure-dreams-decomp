#ifndef DUNGEON_EFFECT_SPELL_EFFECT_H
#define DUNGEON_EFFECT_SPELL_EFFECT_H

#include "common.h"
#include "shared/entity.h"

/* Common prefix initialized by create_actor_spell_effect.
 * Callback sets use separate bodies after this prefix, as in TrackingEffect. */
typedef struct SpellEffectHeader {
    ActorRecord *caster;
    void *context;
    u8 spell_id;
    u8 variant;
    union { s16 s; u16 u; } phase;
} SpellEffectHeader;

#endif
