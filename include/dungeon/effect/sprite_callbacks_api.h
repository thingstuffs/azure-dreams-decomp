#ifndef DUNGEON_EFFECT_SPRITE_CALLBACKS_API_H
#define DUNGEON_EFFECT_SPRITE_CALLBACKS_API_H

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct ObjectPosition;
struct ParticleCleanupEffectBody;
struct S_800D81D4_0;
struct S_800D81D4_1;
void expire_effect_at_unit_scale(struct ParticleCleanupEffectBody *state_data, struct ObjectPosition *unused, void *scale_data);
void update_orbiting_effect_particle(struct S_800D81D4_0 *effect, struct S_800D81D4_1 *motion, void *primitive_data);

#endif
