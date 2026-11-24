#include "dungeon/effect/orbit_burst_spell.h"

/* Selector 10 reads the first word. The zero word aligns the following case table. */
static const struct {
    void (*entry)(OrbitBurstSpell *, SpellMotion *, SpriteFrameState *);
    u32 padding;
} D_80024000 __attribute__((unused)) = { update_orbit_burst_spell, 0 };
