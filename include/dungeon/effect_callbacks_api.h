#ifndef DUNGEON_EFFECT_CALLBACKS_API_H
#define DUNGEON_EFFECT_CALLBACKS_API_H

#include "common.h"

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct ObjectPosition;
struct dungeon_long_lived_trap_effect;
void update_actor_motion_and_rendering(u8 *actor, struct ObjectPosition *motion, u8 *render);
void update_long_lived_trap_effect(struct dungeon_long_lived_trap_effect *effect);

#endif
