#ifndef DUNGEON_ITEM_CALLBACKS_API_H
#define DUNGEON_ITEM_CALLBACKS_API_H

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct EffectState;
struct EffectWork;
struct ObjectPosition;
struct RadialParticleBurstBody;
struct SpriteFrameState;
struct dungeon_return_magic_effect;
struct dungeon_return_magic_motion;
struct dungeon_return_magic_object;
void advance_or_block_fading_record(struct RadialParticleBurstBody *state, struct ObjectPosition *motion, struct SpriteFrameState *record);
void animate_orbiting_effect_particle(struct EffectState *state, struct EffectWork *work, struct SpriteFrameState *color);
void update_return_magic_ascent(struct dungeon_return_magic_object *obj, struct dungeon_return_magic_motion *motion, struct dungeon_return_magic_effect *effect);

#endif
