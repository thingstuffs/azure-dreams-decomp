#ifndef DUNGEON_EFFECT_ORBIT_RING_SPELL_H
#define DUNGEON_EFFECT_ORBIT_RING_SPELL_H

#include "dungeon/effect/spell_effect.h"
#include "shared/object_node.h"

/* Body of the spell node: a sprite that flies to the target (or along the facing) and then opens a ring of ten
 * orbiting sprites around it. */
typedef struct OrbitRingSpell {
    SpellEffectHeader effect;
    s16 reserved_0c;
    s16 direction;
    s16 timer;
    s16 duration;
    s16 busy;
    s16 spin;
    s16 orbit;
    s16 reserved_1a;
    ObjectNodeHeader *trail;
    ObjectNodeHeader *ring;
    ObjectNodeHeader *orbs[10];
} OrbitRingSpell;

#endif
