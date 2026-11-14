#ifndef DUNGEON_OVL_18AC800_H
#define DUNGEON_OVL_18AC800_H
struct ActorRecord;
#include "shared/dungeon_moving_views.h"
#include "dungeon/effect/shade/staged_fade_data.h"
#include "shared/dungeon_status.h"
#include "shared/object_flags.h"
#include "sdk/abs.h"
#include "sdk/libgte.h"
#include "dungeon/effect/shade/row_quad_colors.h"
extern u8 radial_effect_colors[];
extern u8 D_80026474[];
extern u8 D_80026476[];
extern u8 D_80026484[];
extern u8 D_80026490[];
extern u8 particle_target_height[];
extern void draw_textured_ellipse(void *, void *, s32, s32);
extern s32 get_sprite_attachment_vector(void *, void *, void *, s32);
extern s32 func_8003DF74(void *, void *, void *, s32);
extern void register_node(void *, void *);
extern void func_8002495C(void *, void *);
extern s32 check_left_tile_and_center_height(u16, u16, s16);
extern s32 create_effect_object_groups(s16, s16, s16);
extern void apply_conditional_target_effect(struct ActorRecord *, u8, void *);
struct MovingEffectState;
void follow_brighten(struct MovingEffectState *, MovingMotion *, MovingSprite *);
void advance_object_and_global_counters(u16 *);
#endif
