#ifndef DUNGEON_OVL_19DE800_H
#define DUNGEON_OVL_19DE800_H


struct SpriteFrameState;
struct ObjectPosition;
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "sdk/libgte.h"
typedef struct {
    s16 x;
    u16 y;
} OffsetPair;
typedef struct {
    OffsetPair entries[8];
} OffsetTable;
extern const OffsetTable D_80024028;
struct S_80024BF4_1;
struct S_80024BF4_2;
struct S_80024BF4_4;
struct S_80025FB0_0;
struct S_80025FB0_1;
struct S_func_80026418_0;
void *find_impact_surface_polygon(s32, s32, s16);
s32 random_below_limit(s32);
void create_shrinking_entry_particle_effect(struct ObjectNodeHeader *target, ObjectPosition *position);
void project_visible_textured_quad(struct S_80024BF4_4 *quad, struct ObjectPosition *position, struct SpriteFrameState *render_state, s16 depth_bias);
struct OwnerFollowingWork;
void spawn_randomized_textured_particles(struct OwnerFollowingWork *source, s32 center_x, s16 center_y, s16 center_z);
/* Retail callers pass promoted scalar words; the callee reads their low halves. */
s32 func_80025CE8(s32, s32, s32, s32);
void copy_effect_transform(struct S_80025FB0_1 *dst, struct S_80025FB0_0 *src);
void step_entry_index_clamped(SpriteFrameState *sprite, s16 *index_step, s32 min_index, s32 max_index);
void select_mesh_entry(SpriteFrameState *sprite, s16 entry_index);
void create_impact_particle_at_offset(s32,s32,s32,s32,s32,s32,s32,s32,s32,s32);
void advance_particle_fade_and_cleanup(struct S_func_80026418_0 *effect);
s32 register_node(void *, void *, ...);
void select_record_entry_and_value(void *state, void *entries, short index);
extern s16 impact_effect_update_flag;
extern void *D_80028630;
/* Pooled particle callback work shared by the shrinking and rotating variants.
 * The constructors seed accelerations at +0x88..+0x90; each update integrates
 * them into velocity, advances sprite animation and decrements the lifetime. */
typedef struct ImpactParticleWork {
    u8 pad_00[0x28];
    u16 ticks_left;
    u16 anim_ticks;
    s16 rotation_axis; /* rotating variant: 0 rotates X, 1 rotates Z */
    u8 pad_2E[0x4E];
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    s32 accel_x;
    s32 accel_y;
    s32 accel_z;
} ImpactParticleWork;

void scale_effect_by_phase(void *);
void update_impact_particle_slow_shrink(ImpactParticleWork *, struct ObjectPosition *, struct SpriteFrameState *);
struct ShrinkingEntryEffectBody;
void shrink_effect_and_spawn_particles(struct ShrinkingEntryEffectBody *, ObjectPosition *);
s32 draw_linked_meshes(void *, void *, void *);
void advance_rotating_ballistic_particle_and_expire(ImpactParticleWork *, struct ObjectPosition *, struct SpriteFrameState *);
void update_owner_following_effect(struct OwnerFollowingWork *, struct ObjectPosition *, struct SpriteFrameState *);
void update_impact_particle_fast_shrink(ImpactParticleWork *, struct ObjectPosition *, struct SpriteFrameState *);
#endif
