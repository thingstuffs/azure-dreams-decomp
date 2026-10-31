#ifndef DUNGEON_EFFECT_PARTICLE_H
#define DUNGEON_EFFECT_PARTICLE_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
struct S_81832FE8_0;
void fade_timed_quad_vertices(void *fade_data);
void try_apply_attached_actor_status(struct S_81832FE8_0 *owner);


void advance_centered_fading_effect(void *effect, ObjectPosition *position, void *color);
void advance_projectile_burst_and_impact(void *effect, ObjectPosition *motion, SpriteFrameState *sprite);
struct RibbonLineGeometry;
void draw_ribbon_center_lines(struct RibbonLineGeometry *geometry, ObjectPosition *position, SpriteFrameState *render_data, s32 depth_bias);
void draw_gouraud_textured_ribbon_quad(void *quad, ObjectPosition *position, void *render_state, s16 depth_bias);
void emit_parent_relative_particles(void *emitter, ObjectPosition *position, s32 spawn_context);
void spawn_scattered_emitter_particles(void *emitter, ObjectPosition *position, s32 spawn_context);
void update_converging_fading_particle(void *effect, ObjectPosition *position);
typedef struct TwoRowObjectGroupBody {
    union { s16 s; u16 u; } unk_00;
    union { u16 s; u16 u; s16 signed_value; } unk_02;
    union { s16 s; u16 u; } unk_04;
    u16 unk_06;
    s16 unk_08;
    union { u16 s; s16 u; } unk_0A;
    s32 unk_0C;
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x3]; u8 v; } at03;
    } unk_10;
    u8 pad_14[0xC];
    union {
        u32 initial_payload[2];
        struct {
            u16 unk_20;
            u16 unk_22;
            u16 unk_24;
            u8 pad_26[0x2];
        } motion;
    } unk_20;
    struct {
        u16 unk_00;
        u16 unk_02;
        u16 unk_04;
        u16 unk_06;
    } points[4];
} TwoRowObjectGroupBody;
void create_two_row_object_group(void *payload, s16 value_scale);
void update_rotating_effect_vertices(TwoRowObjectGroupBody *effect_data);
s32 draw_linked_textured_quads(TwoRowObjectGroupBody *first_quad);
typedef struct EmitAttachedDirectionalParticleChainBody {
    s16 unk_00;
    union { s16 s; u16 u; } unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    union { s16 s; u16 u; } unk_0A;
    u8 pad_0C[0x9];
    u8 unk_15;
    u16 unk_16;
    u8 pad_18[0x14];
    union { s32 s; void *p; } unk_2C;
    union { s32 s; void *p; } unk_30;
    u8 pad_34[0x24];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} EmitAttachedDirectionalParticleChainBody;
void update_spark_emitter_effect(EmitAttachedDirectionalParticleChainBody *effect, ObjectPosition *position);
void update_timed_effect_animation(void *effect, ObjectPosition *motion, SpriteFrameState *visual);

struct DirectionalEffectWork;
void update_directional_actor_effect(struct DirectionalEffectWork *effect, ObjectPosition *motion, void *context);

void create_owner_linked_mirrored_sprite(void *effect, ObjectPosition *source_position, SpriteFrameState *source_sprite);

/* Callback entry points. */
void expire_ribbon_segment(void *record_data);
void tick_rotating_rect_effect(void *effect, s32 unused, void *phase_state);
void update_color_cycling_pulse(void *state_data, void *unused, void *color);
void update_reverse_rotating_clipped_sprite(void *effect, s32 unused, void *rotation);
void update_staged_particle_emitter(void *effect_data);

struct DirectionalEffectWork;
typedef struct UpdateDirectionalActorEffectBody {
    struct DirectionalEffectWork *owner;
    u8 pad_04[0x8];
    union { s16 s; u16 u; } x;
    union { s16 s; u16 u; } y;
    union { s16 s; u16 u; } z;
    u8 pad_12[0x2E];
    union { u8 byte; s8 signed_byte; u16 halfword; s16 signed_halfword; } texture_u;
    union { u8 byte; s8 signed_byte; u16 halfword; s16 signed_halfword; } texture_v;
    union { u8 byte; s8 signed_byte; u16 halfword; s16 signed_halfword; } texture_u_step;
    union { u8 byte; s8 signed_byte; u16 halfword; s16 signed_halfword; } texture_v_step;
    u16 frame;
    union { s16 s; u16 u; } z_offset;
    union { s16 s; u16 u; } state;
    u16 timer;
} UpdateDirectionalActorEffectBody;

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/dungeon_effect_views.h"
struct D_800DB420_Obj;
struct D_800DB420_RngOut;
struct S_func_81856800_1;
struct S_func_81856800_2;
struct S_func_818DA800_1;
struct S_func_818DA800_2;
void advance_jittered_effect_modes(struct D_800DB420_Obj *state, struct D_800DB420_RngOut *position, SpriteFrameState *effect);
s32 draw_flagged_particle_points(PointRecord *first_point, ObjectPosition *first_position);
void fade_linked_display_sprite(void *effect, void *unused_context, void *effect_params);
void fade_packed_object_color_to_zero(void *object);
void fade_tinted_display_sprite(void *effect, void *unused, void *primitive);
void run_fading_sprite_projectile(struct S_func_81856800_1 *action, struct S_func_81856800_2 *motion_arg);
void run_growing_target_effect(struct S_func_818DA800_1 *effect_state, struct S_func_818DA800_2 *motion);
void spawn_scattered_timed_objects(void *source_owner, void *spawn_params);
void update_animated_textured_ribbon(u8 *effect, void *origin, void *color_in);
void update_flickering_layer_sprite(void *effect_data, void *unused, SpriteFrameState *effect);
void update_landing_particle_fade(u8 *object, u8 *motion, u8 *sprite);

void transform_rotated_vertices(void *transform_data);

struct ObjectNodeHeader;
struct ParticleCleanupWork;
void create_forward_layered_sprite_pulse(void);
void create_layered_sprite_pulse(EntityRec *origin);
void create_random_velocity_child_effect(struct ObjectNodeHeader *parent, s32 state_value, s16 pair_value, s16 offset_x, s16 offset_y, s16 offset_z);
void create_short_lived_child_particle(struct ObjectNodeHeader *source, s16 effect_param, s32 state_value, s16 offset_x, s16 offset_y, s16 offset_z, s32 motion_z);
void update_effect_particles_and_cleanup(struct ParticleCleanupWork *effect, void *motion, void *sprite);

#endif
