#ifndef DUNGEON_OVL_18AC800_H
#define DUNGEON_OVL_18AC800_H
#include "shared/dungeon_moving_views.h"
#include "shared/dungeon_status.h"
#include "shared/object_flags.h"
extern int abs(int);
extern u8 D_80026470[];
extern u8 D_80026474[];
extern u8 D_80026476[];
extern u8 D_80026484[];
extern u8 D_80026490[];
extern u8 D_800265C0[];
extern u8 D_800265C4[];
extern u8 D_800269C8[];
extern void draw_textured_ellipse(void *, void *, s32, s32);
extern s32 get_sprite_attachment_vector(void *, void *, void *, s32);
extern s32 func_8003DF74(void *, void *, void *, s32);
extern void register_node(void *, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800644B8(u32);
extern void func_8002495C(void *, void *);
extern s32 check_left_tile_and_center_height(u16, u16, s16);
extern void func_80065F90(s16, s16);
extern s32 create_effect_object_groups(s16, s16, s16);
extern void play_sound_if_enabled(s32);
extern void apply_conditional_target_effect(void *, u8, void *);
extern BankEffectCounter D_80026472;
void follow_brighten(u8 *, u8 *, u8 *);
void advance_object_and_global_counters(u16 *);
#endif
