#ifndef DUNGEON_OVL_1858800_H
#define DUNGEON_OVL_1858800_H
#include "shared/dungeon_height_query.h"
#include "shared/dungeon_projectile_views.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "sdk/abs.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/rand.h"
extern void *allocate_list_node(s32, void *);
extern s32 resolve_record_orientation_or_fallback(void *, void *, s16 *, s32);
extern void register_node(void *, void *);
extern s32 get_spell_range(s16 entry_index);
extern void apply_attack_power_and_element_effects(void *, s32, s32, s32, s32, void *, s32);
extern void unlink_node(void *);
void advance_sprite_animation_and_textures(void *);                 /* extern */
#include "dungeon/effect/sprite/shared_entries.h"
#include "dungeon/effect/sprite/timed_projectile_entries.h"
void run_timed_sprite_projectile(ProjectileState *, ProjectileMotion *, ProjectileSprite *);
s32 draw_animated_projectile_quads(RenderRecord *, ObjectPosition *);
void update_timed_sprite_effect(void *, void *, void *);
#endif
