#ifndef DUNGEON_EFFECT_SHADE_CALLBACKS_API_H
#define DUNGEON_EFFECT_SHADE_CALLBACKS_API_H
#include "shared/sprite_frame_state.h"

struct EffectObjectGroupsBody;
struct ObjectPosition;
struct RotatingFadeWork;
struct S_80025E48_1;
struct SpriteFrameState;
void advance_decaying_effect_state(void *effect_arg, void *state_data);
void update_attached_effect(void *effect_arg, struct ObjectPosition *position_arg, SpriteFrameState *appearance);
void update_effect_until_animation_ends(void *data_after_flags, void *unused, struct SpriteFrameState *object);
void update_phased_jitter_effect(void *effect, struct ObjectPosition *motion, struct SpriteFrameState *color);
void update_rotating_effect_fade(struct RotatingFadeWork *effect, struct ObjectPosition *motion, struct SpriteFrameState *rotation);
void update_staged_effect_fade(struct EffectObjectGroupsBody *effect, struct S_80025E48_1 *points, SpriteFrameState *tint);

#endif
