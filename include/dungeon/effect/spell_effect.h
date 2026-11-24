#ifndef DUNGEON_EFFECT_SPELL_EFFECT_H
#define DUNGEON_EFFECT_SPELL_EFFECT_H

#include "common.h"
#include "shared/entity.h"

/* Common prefix initialized by create_actor_spell_effect.
 * Callback sets use separate bodies after this prefix, as in TrackingEffect. */
typedef struct SpellEffectHeader {
    ActorRecord *caster;
    u16 *context;
    u8 spell_id;
    u8 variant;
    s16 phase;
} SpellEffectHeader;

/* The orbit spells' view of the node's ObjectPosition (same 0x18 bytes; fold it into that record once the velocity
 * members settle). The three steps are added as whole units when the spell flies to a target, and as 16.16 words
 * when it flies along the caster's facing. */
typedef struct SpellMotion {
    Fixed1616 x;
    Fixed1616 y;
    Fixed1616 z;
    Fixed1616 step_x;
    Fixed1616 step_y;
    Fixed1616 step_z;
} SpellMotion;

#endif
