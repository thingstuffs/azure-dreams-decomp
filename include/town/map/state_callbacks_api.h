#ifndef TOWN_MAP_STATE_CALLBACKS_API_H
#define TOWN_MAP_STATE_CALLBACKS_API_H

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct MapParticleEffect;
struct ObjectPosition;
struct SpriteFrameState;
void spin_object_until_flag_clears(struct MapParticleEffect *effect, struct ObjectPosition *unused_position, struct SpriteFrameState *sprite);

#endif
