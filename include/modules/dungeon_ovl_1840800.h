#ifndef DUNGEON_OVL_1840800_H
#define DUNGEON_OVL_1840800_H
#include "shared/dungeon_height_query.h"
#include "shared/dungeon_trail_views.h"
extern int abs(int);
void *allocate_list_node(s32, void *);
void *func_8003FD64(s32, void *);
void register_node(void *, void *);
void func_8004491C(void *, void *);
s32 rand(void);
void apply_attack_power_and_element_effects(void *, s32, s32, s32, s32, void *, s32);
void *scan_actor_along_heading(void *, s32, s32, s32, s32);
s32 get_definition_entry_byte_13(s16);
void play_sound_if_enabled(s32);
s32 rsin(s32);
s32 rcos(s32);
void transform_rotated_vertices(LocalPacket *);
s32 RotTransPers(void *, s16 *, void *, void *);
u16 GetTPage(s32, s32, s32, s32);
void SetSemiTrans(void *, s32);
void SetPolyF3(void *);
void SetDrawMode(void *, s32, s32, s32, s32);
void run_ground_trail_projectile(void *, TrailMotion *, void *);
void update_flickering_effect_vertices(DungeonObj *);
s32 draw_jittered_triangle_trails(void *);
#endif
