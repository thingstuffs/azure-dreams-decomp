#ifndef DUNGEON_EFFECT_ORBIT_BURST_SPELL_H
#define DUNGEON_EFFECT_ORBIT_BURST_SPELL_H

#include "dungeon/effect/spell_effect.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"

/* Body of the spell node: a sprite that flies to the target (or along the facing), then a core sprite with
 * thirty-two orbiting sprites at the target, then the hit. */
typedef struct OrbitBurstSpell {
    SpellEffectHeader effect;
    u16 flags;
    s16 direction;
    s16 timer;
    s16 duration;
    s16 age;
    s16 busy;
    ObjectNodeHeader *core;
    ObjectNodeHeader *orbs[32];
} OrbitBurstSpell;

void update_orbit_burst_spell(OrbitBurstSpell *spell, SpellMotion *motion, SpriteFrameState *sprite);

#endif
