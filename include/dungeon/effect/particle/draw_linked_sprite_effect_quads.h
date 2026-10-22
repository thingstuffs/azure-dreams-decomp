#ifndef DUNGEON_OVL_19D2800_H
#define DUNGEON_OVL_19D2800_H
#include "modules/dungeon_native_abi.h"
#include "shared/sprite_frame_state.h"

void update_animated_target_effect(void *);
void update_actor_movement_animation_collision(void *);
s32 draw_fading_radial_effect_grid(void *);

struct SpriteEffect;
s32 draw_linked_sprite_effect_quads(struct SpriteEffect *);
struct EffectRecord;
struct SpriteEntry;
void build_and_queue_interpolated_vertical_quads_around_five_perimeter_points(struct EffectRecord *, void *, SpriteFrameState *);

#endif
