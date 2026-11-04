#ifndef DUNGEON_EFFECT_SPRITE_H
#define DUNGEON_EFFECT_SPRITE_H
struct B22_81893474_EffectState;
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_node.h"

/* Owner and saved angle for the sprite that follows its source node. */
typedef struct OwnerPositionedSpriteBody {
    u8 pad_00[0x8];
    ObjectNodeHeader *owner;
    u8 pad_0C[0x2A];
    s16 angle;
} OwnerPositionedSpriteBody;

/* Pulse state, fade countdown, and phase for the fixed-tile color effect. */
typedef struct FixedTileEffectIfAvailableBody {
    union { s16 s; u16 u; } phase;
    s16 fade_ticks;
    s16 angle;
} FixedTileEffectIfAvailableBody;

/* Timer, duration, and anchor used by the Baloon directional template callbacks. */
typedef struct AnchoredDirectionalObjectBody {
    u8 pad_00[0x96];
    u16 remaining;
    u8 pad_98[0x12];
    u16 duration;
    u8 pad_AC[0x4];
    void *source_position;
} AnchoredDirectionalObjectBody;

/* Orbit and anchor fields shared by the jittered point sequence callbacks. */
typedef struct JitteredPointSequenceBody {
    void *unk_00;
    u8 pad_04[0x8];
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u8 pad_12[0x36];
    u16 unk_48;
    u8 pad_4A[0x2];
    union { s16 s; u16 u; } unk_4C;
} JitteredPointSequenceBody;

/* Body shared by the ramping-color updater and its four-quad draw callback. */
typedef struct OffsetColorEffectBody {
    void *unk_00;
    union { u16 u16; s16 s16; u8 u8; } unk_04;
    s16 unk_06;
    union { s16 s; u16 u; } unk_08;
    s16 unk_0A;
    u16 unk_0C;
    union { u8 u; s8 s; } unk_0E;
    u8 pad_0F[0xF1];
} OffsetColorEffectBody;

/* Shared countdown and render fields for jittered shaded point particles. */
typedef struct RandomOffsetEffectObjectBody {
    u8 pad_00[0x8];
    union { void *p; u32 u; } unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    union { s16 s; u16 u; } unk_32;
    u8 pad_34[0x1C];
    s32 unk_50;
    u8 pad_54[0x8C];
} RandomOffsetEffectObjectBody;

/* Owner, phase counters, and lifetime for the tinted sprite updater. */
typedef struct OwnerTintedEffectBody {
    void *unk_00;
    u8 pad_04[0xC];
    union { u16 s; s16 u; } unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    u8 pad_16[0xEE];
} OwnerTintedEffectBody;

/* Eight-segment grid body shared by its update and surface-render callbacks. */
typedef struct DirectionalGridEffectBody {
    void *unk_00;
    s16 unk_04;
    s16 unk_06;
    union { void *p32; u16 u16; } unk_08;
    union { void *p; s32 word; } unk_0C;
    struct {
        s16 unk_00;
        s16 unk_02;
        s16 unk_04;
    } entries[8];
    union { s16 s; u16 u; } unk_40;
    union { s16 s; u16 u; } unk_42;
} DirectionalGridEffectBody;

/* Position, angle, velocity, and fade phase for radial spiral particles. */
typedef struct RadialEffectBody {
    u8 pad_00[0xC];
    u16 unk_0C;
    u16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x6];
    union { s16 s; u16 u; } unk_18;
    u8 pad_1A[0x2];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_1C;
    u8 pad_20[0x8];
    s32 unk_28;
    u8 pad_2C[0x8];
    s32 unk_34;
    u8 pad_38[0x14];
    union { s16 s; u16 u; } unk_4C;
} RadialEffectBody;

/* Rotating sprite state initialized by create_scaled_rotation_effect. */
typedef struct ScaledRotationEffectBody {
    void *unk_00;
    u8 pad_04[0xC];
    u16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    u8 pad_16[0xEE];
} ScaledRotationEffectBody;

/* Body used by the ring-effect update callback. Runtime observations place
 * this object through +0x102; the callback's named fields occupy its prefix. */
typedef struct FollowingColorBlendEffectBody {
    u8 pad_00[0x14];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    u8 pad_22[0xA];
    union { s16 s; u16 u; } unk_2C;
    u8 pad_2E[0x2];
    s16 unk_30;
    u8 pad_32[0x6];
    s16 unk_38;
    u8 pad_3A[0x2];
    s16 unk_3C;
    u8 pad_3E[0xC6];
} FollowingColorBlendEffectBody;

struct S_800244BC_2;
s32 ground_items_lack_special_pair(void);
void update_effect_countdown(AnchoredDirectionalObjectBody *object, MovingPosition *output, void *update_arg);
void advance_target_chasing_emitter(void *object, struct S_800244BC_2 *position, SpriteFrameState *context);
void *create_an_copies_three_source_fields_child_runs_n_16_child_setup(s32 value, void *source, s32 unused, s32 context);
void *draw_sprite_effect_quads(u8 *sprite_list, ObjectPosition *position, SpriteFrameState *render_state_addr, u8 *placement, u8 *packet_buf);
void process_effect_block_entries(void *block);
struct Inner;
void process_effect_record(OwnerPositionedSpriteBody *body, struct Inner *fields_target, struct Inner *field_c_target);
void add_hex_200_s_field_64_runs_callbacks_mode_n_2_check_returns_zero(ActorRecord *object, s32 unused, ActorRecord *record);







void advance_damped_animated_sprite(void *entry, ObjectPosition *motion, SpriteFrameState *object);
void update_spiral_effect(RadialEffectBody *effect, ObjectPosition *motion, SpriteFrameState *sprite);

/* Callback entry points. */
struct LinkedMonsterEffectBody;
void update_linked_monster_effect(struct LinkedMonsterEffectBody *effect_in, ObjectPosition *motion_in, void *sprite_in);

struct S_func_800D7FB8_0;
void update_effect_controller(struct S_func_800D7FB8_0 *controller);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/dungeon_moving_views.h"
s32 draw_shaded_textured_cylinder(struct B22_81893474_EffectState *unused_data, MovingPosition *center, s32 unused_value, s16 rotation, s32 height, s16 radius, u8 blend_mode, u8 brightness);

struct EffectColor;
struct S_func_81886800_1;
struct S_func_81886800_11;
struct S_func_81886800_3;
void check_the_target_using_scaled_low_byte_conditionally_applies_global_800_e_1_d_01(ActorRecord *target, s32 value, void *record);
void create_a_sprite_effect_position_randomized_rotation(s16 x, s16 y, s16 z);
void create_quad_fragments_vertex_grid_randomized_motion_rotation(void);
void handle_retail_n_81887570_callee_80024_d_70_fade_colour_n_1_n_8_per_call_mark(void *effect, ObjectPosition *unused, struct EffectColor *color);
struct JitteredPointSequenceState;
void run_jittered_point_sequence(struct JitteredPointSequenceState *sequence, void *out_position);
void run_radial_sprite_sequence(struct S_func_81886800_1 *effect, struct S_func_81886800_11 *motion, struct S_func_81886800_3 *sprite);
struct JitteredTrailSegmentBody;
void update_jittered_effect_points(struct JitteredTrailSegmentBody *effect);
void update_pulsing_actor_color(FixedTileEffectIfAvailableBody *state_data, ObjectPosition *unused, SpriteFrameState *actor_data);
struct IntermediatePointEffectBody;
void update_randomized_intermediate_points(struct IntermediatePointEffectBody *self);

s32 build_and_enqueue_interpolated_depth_sorted_shaded_lines_linked_list(void *first_owner, void *first_vertices, void *first_line);

struct Row_818A4E74_S_func_818A4E74_1;
s32 draw_animated_shaded_lines(void *effect_data, void *unused_render_data);
s32 draw_linked_shaded_tiles(RandomOffsetEffectObjectBody *first_point, void *first_position);
void randomize_counted_sprite_angle(void **object_ref, s32 unused, struct Row_818A4E74_S_func_818A4E74_1 *target);

struct ParticleCleanupEffectBody;
void advance_timed_visual_effect(struct ParticleCleanupEffectBody *state, void *position_arg, void *visual_arg);
void update_tiled_fade_effect(struct ParticleCleanupEffectBody *effect, void *offset_state_arg, void *render_state);

void *create_linked_object_chain(s16 x, s16 y, s16 z, s16 angle);
void create_random_offset_sprite_effect(s32 effect_param, ObjectPosition *source_pos);
void *spawn_ring_sparks(s16 x, s16 y, s16 z);

#endif
