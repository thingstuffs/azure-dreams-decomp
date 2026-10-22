#ifndef DUNGEON_EFFECT_MOTION_H
#define DUNGEON_EFFECT_MOTION_H
#include "common.h"
#include "shared/dungeon_moving_views.h"
struct S_7FFE83DC_3;
struct S_80024EF8_0;
void create_positioned_color_sprite(struct S_7FFE83DC_3 *source, s32 color);
s32 create_indexed_color_sprite(MovingPosition *origin, u16 index);
s32 draw_counter_rotating_cylinders(struct S_80024EF8_0 *effect, s32 draw_arg1, s32 draw_arg2);
void spawn_jittered_child_effect( void *source, s16 field_34, s32 field_28, s16 field_52, s16 offset_x, s16 offset_y, s16 offset_z);
void spawn_variant_effect_with_random_motion(s32 pos_x, s32 pos_y, s32 pos_z, u32 variant);
#endif
