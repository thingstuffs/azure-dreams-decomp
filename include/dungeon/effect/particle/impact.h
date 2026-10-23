#ifndef DUNGEON_OVL_19DE800_H
#define DUNGEON_OVL_19DE800_H


struct SpriteFrameState;
struct ObjectPosition;
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
typedef struct {
    s16 x;
    u16 y;
} OffsetPair;
typedef struct {
    OffsetPair entries[8];
} OffsetTable;
extern const OffsetTable D_80024028;
struct S_80024AE8_3;
struct S_80024BF4_1;
struct S_80024BF4_2;
struct S_80024BF4_4;
struct S_80025FB0_0;
struct S_80025FB0_1;
struct Bank19de800_19e092c_EntryCursor;
struct S_func_80026418_0;
void *func_80024064(s32, s32, s16);
s32 update_palette_particle_transition(s32);
void create_shrinking_entry_particle_effect(s32 effect_value, struct S_80024AE8_3 *position);
void project_visible_textured_quad(struct S_80024BF4_4 *quad, struct ObjectPosition *position, struct SpriteFrameState *render_state, s16 depth_bias);
void spawn_randomized_textured_particles(s32, s32, s16, s16);
/* Retail callers pass promoted scalar words; the callee reads their low halves. */
s32 func_80025CE8(s32, s32, s32, s32);
void copy_and_expand_effect_record(struct S_80025FB0_1 *dst, struct S_80025FB0_0 *src);
void resolve_and_step_entry_index(void *, s16 *, s32, s32);
void set_mesh_entry_address(struct Bank19de800_19e092c_EntryCursor *object, s16 entry_index);
void create_offset_colored_effect(s32,s32,s32,s32,s32,s32,s32,s32,s32,s32);
void advance_particle_fade_and_cleanup(struct S_func_80026418_0 *effect);
s32 register_node(void *, s32, ...);
s32 func_8004491C(void *, s32, ...);
s32 select_record_entry_and_value(void *, void *, s32);
void ScaleMatrix(void *, void *);
s32 play_sound_if_enabled(s32);
extern s16 impact_effect_update_flag;
extern void *D_80028630;
void scale_effect_by_phase(void *);
void advance_effect_motion_and_animation(void *, void *, struct SpriteFrameState *);
void shrink_effect_and_spawn_particles(void *, void *);
s32 draw_linked_meshes(void *, void *, void *);
void advance_rotating_ballistic_particle_and_expire(void *, void *, struct SpriteFrameState *);
void update_owner_following_effect(void *, void *, void *);
void update_effect_motion_and_visual(void *, void *, struct SpriteFrameState *);
#endif
