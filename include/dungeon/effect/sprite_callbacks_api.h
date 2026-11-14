#ifndef DUNGEON_EFFECT_SPRITE_CALLBACKS_API_H
#define DUNGEON_EFFECT_SPRITE_CALLBACKS_API_H
#include "shared/sprite_frame_state.h"

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct ObjectPosition;
struct SpriteFrameState;
struct ParticleCleanupEffectBody;
struct S_800D81D4_0;
struct S_800D81D4_1;
void update_orbiting_effect_particle(struct S_800D81D4_0 *effect, struct S_800D81D4_1 *motion, SpriteFrameState *primitive_data);
void expire_effect_at_unit_scale(struct ParticleCleanupEffectBody *state_data, struct ObjectPosition *unused, struct SpriteFrameState *scale_data);

#endif
