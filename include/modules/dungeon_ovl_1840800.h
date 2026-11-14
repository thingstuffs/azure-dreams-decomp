#ifndef DUNGEON_OVL_1840800_H
#define DUNGEON_OVL_1840800_H
#include "shared/dungeon_height_query.h"
#include "shared/dungeon_trail_views.h"
#include "sdk/abs.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/rand.h"
void *allocate_list_node(s32, void *);
void register_node(void *, void *);
void apply_attack_power_and_element_effects(void *, s32, s32, s32, s32, void *, s32);
s32 get_spell_range(s16);
void transform_rotated_vertices(LocalPacket *);
void run_ground_trail_projectile(void *, TrailMotion *, void *);
void update_flickering_effect_vertices(DungeonObj *);
s32 draw_jittered_triangle_trails(void *);
#endif
