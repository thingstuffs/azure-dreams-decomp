#ifndef DUNGEON_OVL_19DE800_H
#define DUNGEON_OVL_19DE800_H
#include "common.h"
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
void create_shrinking_entry_particle_effect(s32, struct S_80024AE8_3 *);
void project_visible_textured_quad(struct S_80024BF4_4 *, struct S_80024BF4_1 *, struct S_80024BF4_2 *, s16);
void spawn_randomized_textured_particles(s32, s32, s16, s16);
/* Retail callers pass promoted scalar words; the callee reads their low halves. */
s32 func_80025CE8(s32, s32, s32, s32);
void copy_and_expand_effect_record(struct S_80025FB0_1 *, struct S_80025FB0_0 *);
void resolve_and_step_entry_index(void *, s16 *, s32, s32);
void set_mesh_entry_address(struct Bank19de800_19e092c_EntryCursor *, s16);
void create_offset_colored_effect(s32,s32,s32,s32,s32,s32,s32,s32,s32,s32);
void advance_particle_fade_and_cleanup(struct S_func_80026418_0 *);
s32 register_node(void *, s32, ...);
s32 func_8004491C(void *, s32, ...);
s32 func_8003DB94(void *, void *, s32);
void func_80064BC0(void *, void *);
s32 play_sound_if_enabled(s32);
extern s16 D_8002992E;
extern void *D_80028630;
void scale_effect_by_phase(void *);
void advance_effect_motion_and_animation(void *, void *, void *);
void shrink_effect_and_spawn_particles(void *, void *);
s32 draw_linked_meshes(void *, void *, void *);
void advance_rotating_ballistic_particle_and_expire(void *, void *, void *);
void update_owner_following_effect(void *, void *, void *);
void update_effect_motion_and_visual(void *, void *, void *);
#endif
