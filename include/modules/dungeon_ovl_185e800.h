#ifndef DUNGEON_OVL_185E800_H
#define DUNGEON_OVL_185E800_H
#include "dungeon/effect/sprite/fading_entries.h"
#include "shared/dungeon_height_query.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_delay_views.h"
#include "shared/slus_callbacks.h"
#include "sdk/rand.h"
#include "dungeon/effect/sprite/landing_entries.h"
void *allocate_list_node(s32, void *);
s32 get_definition_entry_byte_13(s16);
s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
void register_node(void *, void *);
void advance_sprite_animation_and_textures(void *);
void apply_attack_power_and_element_effects(void *, s32, s32, s32, s32, void *, s32);
void run_delayed_sprite_projectile(DelayedTargetEffect *, ObjectPosition *);
void advance_delayed_fading_sprite(DelayParticle *, DelayPosition *, SpriteFrameState *);
void brighten_accelerate_and_fade_effect(void *, DelayMotion *, DelaySpriteColor *);
#endif
