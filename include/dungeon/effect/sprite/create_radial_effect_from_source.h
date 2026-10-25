#ifndef DUNGEON_OVL_18A6800_H
#define DUNGEON_OVL_18A6800_H
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "modules/dungeon_native_abi.h"
struct FadeEndpoints; struct FadeSettings;
 struct S_80025160_1;
struct Actor; struct Motion;
/* The effect's colour record: three bytes fading toward black. */
typedef struct EffectColor {
    u8 pad_00[12];
    u8 red;
    u8 green;
    u8 blue;
} EffectColor;
ObjectNodeHeader *handle_retail_n_818875_e_8_callee_80024_de_8_creates_fade_updated_each_frame_callee_80024_d_70_start(struct FadeEndpoints *, struct FadeSettings *);
void *create_object_offset(MovingPosition *, s16, s16, s16, s32);
void advance_the_effect_state_updates_motion_sets_display_color(void *, s32, struct S_80025160_1 *);
s32 build_and_enqueue_interpolated_depth_sorted_shaded_lines_linked_list(void *, void *, void *);
void advance_and_fade_effect_flagging_expiration_timer_runs_out(struct Actor *, struct Motion *, SpriteFrameState *);
struct RadialQuadWork;
void handle_rotate_move_effect_quad_fade_colors_flag_lifetime_ends(struct RadialQuadWork *, ObjectPosition *, SpriteFrameState *);
s32 handle_project_linked_quads_queue_shaded_primitives_draw_modes_depth(void *);
#include "modules/dungeon_native_abi.h"
#include "m2c_compat.h"
extern u16 D_80026324[];
extern u16 D_80026326;
extern s16 D_80026328[];
extern s16 D_8002632A;
extern u8 radial_effect_colors[];
extern u8 D_80026474[];
extern u8 staged_glow_data[];

void create_radial_effect_from_source(); /* Slot contract: loading images do not establish one callee contract. */
s32 build_shaded_quads_adjacent_vertex_rows_adds_them_ordering_table(void);

s32 GetTPage(s32, s32, s32, s32);
void AddPrim();
void SetDrawMode(void *, s32, s32, u16, s32);

#endif
