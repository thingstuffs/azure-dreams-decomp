#ifndef DUNGEON_ITEM_CALLBACKS_API_H
#define DUNGEON_ITEM_CALLBACKS_API_H

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct EffectColor;
struct EffectState;
struct EffectWork;
struct RadialParticleBurstBody;
struct S_80099B18_2;
struct SpriteFrameState;
struct dungeon_return_magic_effect;
struct dungeon_return_magic_motion;
struct dungeon_return_magic_object;
void advance_or_block_fading_record(struct RadialParticleBurstBody *state, struct S_80099B18_2 *motion, struct SpriteFrameState *record);
void animate_orbiting_effect_particle(struct EffectState *state, struct EffectWork *work, struct EffectColor *color);
void update_return_magic_ascent(struct dungeon_return_magic_object *obj, struct dungeon_return_magic_motion *motion, struct dungeon_return_magic_effect *effect);

#endif
