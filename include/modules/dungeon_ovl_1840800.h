#ifndef DUNGEON_OVL_1840800_H
#define DUNGEON_OVL_1840800_H
#include "shared/dungeon_height_query.h"
#include "shared/dungeon_trail_views.h"
extern int abs(int);
void *allocate_list_node(s32, void *);
void *func_8003FD64(s32, void *);
void register_node(void *, void *);
void func_8004491C(void *, void *);
s32 func_80069EF8(void);
void apply_attack_power_and_element_effects(void *, s32, s32, s32, s32, void *, s32);
void *scan_monster_along_heading(void *, s32, s32, s32, s32);
s32 get_definition_entry_byte_13(s16);
s32 check_enabled_neighbor_height(s32, s32, s16, u32, s32);
void play_sound_if_enabled(s32);
s32 func_800644B8(s32);
s32 func_80064584(s32);
void transform_rotated_vertices(LocalPacket *);
s32 func_80065420(void *, s16 *, void *, void *);
u16 func_80066460(s32, s32, s32, s32);
void func_80066640(void *, s32);
void func_80066690(void *);
void func_80067F20(void *, s32, s32, s32, s32);
void func_80024020(void *, TrailMotion *, void *);
void update_flickering_effect_vertices(DungeonObj *);
s32 draw_jittered_triangle_trails(void *);
#endif
