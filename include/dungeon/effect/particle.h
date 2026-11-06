#ifndef DUNGEON_EFFECT_PARTICLE_H
#define DUNGEON_EFFECT_PARTICLE_H
struct ScatterLandingSparksOnGridBody;
struct LayeredSpritePulseBody;
struct ProjectileBurstImpactBody;
struct ScatteredTimedEffectBody;
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
struct S_81832FE8_0;
void fade_timed_quad_vertices(void *fade_data);
void try_apply_attached_actor_status(struct S_81832FE8_0 *owner);


void advance_centered_fading_effect(void *effect, ObjectPosition *position, void *color);
void advance_projectile_burst_and_impact(struct ProjectileBurstImpactBody *effect, ObjectPosition *motion, SpriteFrameState *sprite);
struct RibbonLineGeometry;
void draw_ribbon_center_lines(struct RibbonLineGeometry *geometry, ObjectPosition *position, SpriteFrameState *render_data, s32 depth_bias);
void draw_gouraud_textured_ribbon_quad(void *quad, ObjectPosition *position, SpriteFrameState *render_state, s16 depth_bias);
void emit_parent_relative_particles(void *emitter, ObjectPosition *position, s32 spawn_context);
void spawn_scattered_emitter_particles(void *emitter, ObjectPosition *position, s32 spawn_context);
void update_converging_fading_particle(void *effect, ObjectPosition *position);
/* Countdown state and the copied starting position for the clipped rotating sprites. */
typedef struct RotatingClippedSpriteBody {
    u8 pad_00[0x18];
    u16 ticks_remaining;
    u16 unk_1A;
    u8 pad_1C[0xC];
    u8 initial_position[0xC];
} RotatingClippedSpriteBody;

typedef struct TwoRowObjectGroupBody {
    s16 unk_00;
    u16 unk_02;
    s16 unk_04;
    u16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s32 unk_0C;
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x3]; u8 v; } at03;
    } unk_10;
    u8 pad_14[0xC];
    struct {
        u16 unk_20;
        u16 unk_22;
        u16 unk_24;
        u8 pad_26[0x2];
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
typedef struct DirectionalParticleChainBody {
    s16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    u16 unk_0A;
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
} DirectionalParticleChainBody;
void update_spark_emitter_effect(DirectionalParticleChainBody *effect, ObjectPosition *position);
void update_timed_effect_animation(struct ScatteredTimedEffectBody *effect, ObjectPosition *motion, SpriteFrameState *visual);

struct DirectionalEffectWork;
void update_directional_actor_effect(struct DirectionalEffectWork *effect, ObjectPosition *motion, void *context);

void create_owner_linked_mirrored_sprite(void *effect, ObjectPosition *source_position, SpriteFrameState *source_sprite);

/* Callback entry points. */
void expire_ribbon_segment(void *record_data);
void tick_rotating_rect_effect(RotatingClippedSpriteBody *effect, ObjectPosition *unused, void *phase_state);
typedef struct ColorCyclingPulseBody {
    u8 pad_00[0x18];
    u16 ticks_remaining;
    u8 pad_1A[0x2];
    u16 phase_index;
} ColorCyclingPulseBody;
void update_color_cycling_pulse(ColorCyclingPulseBody *state_data, void *unused, SpriteFrameState *color);
void update_reverse_rotating_clipped_sprite(RotatingClippedSpriteBody *effect, ObjectPosition *unused, void *rotation);
void update_staged_particle_emitter(void *effect_data);

struct DirectionalEffectWork;
typedef struct DirectionalActorEffectBody {
    struct DirectionalEffectWork *owner;
    u8 pad_04[0x8];
    u16 x;
    u16 y;
    s16 z;
    u8 pad_12[0x2E];
    s16 texture_u;
    s16 texture_v;
    s16 texture_u_step;
    s16 texture_v_step;
    u16 frame;
    s16 z_offset;
    u16 state;
    u16 timer;
} DirectionalActorEffectBody;

/* Countdown, owning slot, and source record for a linked display sprite. */
typedef struct FreeSlotDisplayEffectBody {
    u8 pad_00[0x2A];
    u16 remaining;
    s16 fade_step;
    u8 pad_2E[0x4];
    s16 slot_index;
    u8 pad_34[0x2C];
    void *owner;
    u8 pad_64[0x16];
    u8 unk_7A;
    u8 unk_7B;
} FreeSlotDisplayEffectBody;

/* Timer, slot flags, source owner, and copied sprite data for the high display updater. */
typedef struct DisplaySpawnerEffectBody {
    u8 pad_00[0x2A];
    s16 timer;
    u8 pad_2C[0x1A];
    s16 slot_flags[8];
    u8 pad_56[0xA];
    void *source_owner;
    u8 pad_64[0xE];
    u8 initial_sprite_data[0xC];
} DisplaySpawnerEffectBody;

/* Shared countdown, phase, position toggle, and linked child records for staged effects. */
typedef struct ParticleCleanupEffectBody {
    union { s16 s; u16 u; } unk_00;
    union { u16 s; s16 u; } unk_02;
    u8 pad_04[0x6];
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x1E];
    void *unk_2C;
    void *unk_30;
    void *unk_34;
    void *unk_38;
    void *unk_3C;
    void *unk_40;
} ParticleCleanupEffectBody;

/* Indexed parent state and segment shape used by the animated ribbon updater. */
typedef struct EightPartTexturedRibbonBody {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x0F];
    u16 unk_12;
    u8 pad_14[0x4];
    s16 unk_18;
    u16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    ObjectPosition *unk_24;
    u8 pad_28[0x34];
    s32 unk_5C;
    s32 unk_60;
    u8 pad_64[0x10];
    u16 unk_74;
    u16 unk_76;
    u16 unk_78;
    u16 unk_7A;
    u16 unk_7C;
    u16 unk_7E;
    u16 unk_80;
    u16 unk_82;
    u16 unk_84;
    u16 unk_86;
    u16 unk_88;
    u16 unk_8A;
} EightPartTexturedRibbonBody;

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
void fade_linked_display_sprite(struct FreeSlotDisplayEffectBody *effect, void *unused_context, void *effect_params);
void fade_packed_object_color_to_zero(void *object);
void fade_tinted_display_sprite(struct FreeSlotDisplayEffectBody *effect, void *unused, void *primitive);
void run_fading_sprite_projectile(struct S_func_81856800_1 *action, struct S_func_81856800_2 *motion_arg);
void run_growing_target_effect(struct S_func_818DA800_1 *effect_state, struct S_func_818DA800_2 *motion);
void spawn_scattered_timed_objects(void *source_owner, void *spawn_params);
void update_animated_textured_ribbon(EightPartTexturedRibbonBody *effect, void *origin, void *color_in);
void update_flickering_layer_sprite(struct LayeredSpritePulseBody *effect_data, void *unused, SpriteFrameState *effect);
void update_landing_particle_fade(struct ScatterLandingSparksOnGridBody *object, u8 *motion, u8 *sprite);

void transform_rotated_vertices(void *transform_data);

struct ObjectNodeHeader;
struct ParticleCleanupWork;
void create_forward_layered_sprite_pulse(s32 unused_phase, void *unused_target_state);
void create_layered_sprite_pulse(EntityRec *origin);
void create_random_velocity_child_effect(struct ObjectNodeHeader *parent, s32 state_value, s16 pair_value, s16 offset_x, s16 offset_y, s16 offset_z);
void create_short_lived_child_particle(struct ObjectNodeHeader *source, s16 effect_param, s32 state_value, s16 offset_x, s16 offset_y, s16 offset_z, s32 motion_z);
void update_effect_particles_and_cleanup(struct ParticleCleanupWork *effect, ObjectPosition *motion, SpriteFrameState *sprite);

/* Lifetime and original position for a short-lived red spark. */
typedef struct ShortLivedRedSparkBody {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u8 pad_36[0xC];
    u16 unk_42;
    u16 unk_44;
    u16 unk_46;
} ShortLivedRedSparkBody;

/* Phase, timer, and launch parameters shared by landing sparks. */
typedef struct ScatterLandingSparksOnGridBody {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1];
    u8 phase;
    u8 pad_18[0x1A];
    u16 ticks;
    s16 unk_34;
    u8 pad_36[0xC];
    u16 unk_42;
    u16 unk_44;
    u16 unk_46;
    u8 pad_48[0xC];
    s32 unk_54;
    u8 pad_58[0x8];
    s32 gravity;
} ScatterLandingSparksOnGridBody;

/* The two countdown values used by the layered sprite pulse callback. */
typedef struct LayeredSpritePulseBody {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
} LayeredSpritePulseBody;

void clear_circular_list_flags(void);
void process_entries_at_coordinates(void *list_head, s32 x, s32 y, s16 upper_bound, s16 lower_bound);

#include "records/Rec_func_80167A98_arg0.h"
#include "records/Rec_func_80167A98_arg1.h"
void create_ribbon_head_sprite(Rec_func_80167A98_arg0 *source, Rec_func_80167A98_arg1 *origin, void *unused_color);

void create_terrain_seeking_point_effect(void *source, s32 property_34, s32 property_28, s16 property_52, s16 x_offset, s16 y_offset, s16 z_offset);
void draw_textured_sphere_mesh(void *mesh, void *position, void *material, u16 depth_bias);
void project_textured_quad_or_callback(void *quad_arg, ObjectPosition *position, SpriteFrameState *material, s16 depth_bias);
struct TargetParticleStatusSpellBody;
void update_animated_effect_sprite(struct TargetParticleStatusSpellBody *effect, ObjectPosition *entity, SpriteFrameState *sprite);
void create_eight_part_textured_ribbon(ActorRecord *source, void *origin, SpriteFrameState *unused, ObjectPosition *effect_position);
void subtract_limit_or_flag_record(void *record);

void create_source_positioned_object(ObjectPosition *source_pos, s16 initial_value);

#endif
