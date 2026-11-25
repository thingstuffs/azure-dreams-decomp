#include "dungeon/effect/orbit_burst_spell.h"

/* Selector 10 reads the first word. The zero word aligns the following case table. */
const struct {
    void (*entry)(OrbitBurstSpell *, SpellMotion *, SpriteFrameState *);
    u32 padding;
} orbit_burst_bank_header = { update_orbit_burst_spell, 0 };
