#include "dungeon/effect/orbit_ring_spell.h"
#include "dungeon/effect.h"

/* Selector 25 reads the first word. The zero word aligns the following case table. */
const struct {
    void (*entry)(OrbitRingSpell *, SpellMotion *, SpriteFrameState *);
    u32 padding;
} orbit_ring_bank_header = { update_orbit_ring_spell, 0 };
