#ifndef DUNGEON_EFFECT_SHADE_CALLBACKS_API_H
#define DUNGEON_EFFECT_SHADE_CALLBACKS_API_H

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct EffectObjectGroupsBody;
struct ObjectPosition;
struct RotatingFadeWork;
struct S_80025E48_1;
struct S_80025E48_2;
struct S_800D4954_2;
struct S_800D4954_4;
struct SpriteFrameState;
void advance_decaying_effect_state(void *effect_arg, void *state_data);
void update_attached_effect(void *effect_arg, struct S_800D4954_2 *position, struct S_800D4954_4 *appearance);
void update_effect_and_retain_flags(void *data_after_flags, void *unused, struct SpriteFrameState *object);
void update_effect_motion_and_color(void *effect, struct ObjectPosition *motion, struct SpriteFrameState *color);
void update_rotating_effect_fade(struct RotatingFadeWork *effect, struct ObjectPosition *motion, struct SpriteFrameState *rotation);
void update_staged_effect_fade(struct EffectObjectGroupsBody *effect, struct S_80025E48_1 *points, struct S_80025E48_2 *tint);

#endif
