#ifndef R108_BANK19_H
#define R108_BANK19_H
#include "common.h"
#include "dungeon/effect/travel.h"
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_native_abi.h"
#include "shared/dungeon_moving_views.h"



struct S_800250E8_0;
struct S_80025654_2;
struct S_80025654_4;
typedef struct EffectColor { u8 pad[12]; u8 red,green,blue; } EffectColor;
extern u16 tint_effect_update_count[];
extern s16 tint_effect_phase_counts[];
extern u8 tinted_travel_sprite_data[];
struct S_80045C34;
s32 draw_linked_sprites_clipped(u8 *first_data, s32 link_value, SpriteFrameState *value_record);
s32 func_80045C34(u8 *,s32,struct S_80045C34 *);
void tint_effect_and_advance_motion(void *,void *);
void *create_initialized_effect_object(s32,MovingPosition *,s16,s32);
void advance_sprite_on_alternate_ticks_until_complete(void *,s32,void *);
void *create_radial_effect_node(MovingPosition *);

void *spawn_ring_effects(void *,s16);
void move_and_fade_effect(void *,void *,void *);
void update_spark_effect(void *,struct S_800250E8_0 *,void *);
s32 queue_projected_point_primitives(void *,void *,void *);
void allocate_jittered_effect_node(void *,s16,s16,s16);
void fade_effect_color_below_eight(u16 *,s32,EffectColor *);
void *create_effect_from_endpoints(struct S_80025654_2 *,struct S_80025654_4 *);
void apply_indexed_effect_condition(void *,u8,void *);
s32 select_record_entry_and_value(void *,void *,s32);
s32 get_sprite_attachment_vector(void *,void *,s16 *,s32);
s32 func_8003DF74(void *,void *,s16 *,s32);
s32 rsin(s32);
s32 rcos(s32);
s32 rand(void);
#endif
