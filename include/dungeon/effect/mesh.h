#ifndef DUNGEON_EFFECT_MESH_H
#define DUNGEON_EFFECT_MESH_H
#include "common.h"
#include "shared/sprite_part_command.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

typedef struct MeshEffectOrigin {
    Fixed1616 x;
    Fixed1616 y;
    Fixed1616 z;
} MeshEffectOrigin;

/* The interpolated line publishes its three 16.16 coordinates to its mesh and sprite effects. */
extern MeshEffectOrigin *effect_position_source;

/* One four-byte coordinate record in the mesh renderer's variable-length tile list. */
typedef struct MeshEffectObjectBody {
    u8 x;
    u8 y;
    u16 height;
} MeshEffectObjectBody;
/* Owner link stored by the vertically-offset sprite effect's updater. */
typedef struct OwnerLinkedSpriteEffectBody {
    void *owner;
} OwnerLinkedSpriteEffectBody;
typedef struct TerrainSeekingColoredPointBody {
    u32 color;
    s16 direction;
    u8 pad_06[0xA];
    s16 intensity;
    s16 divisor;
    u8 pad_14[0xA0];
    s32 z_velocity;
} TerrainSeekingColoredPointBody;
void advance_colored_point_toward_terrain(TerrainSeekingColoredPointBody *object, ObjectPosition *position);
s32 project_colored_point_to_ordering_table(TerrainSeekingColoredPointBody *render_data, ObjectPosition *position);
/* Projectile callback work at node +0x20. The +0x98 sprite template is
 * installed in sprite->source and its +8 byte is alternated during impact. */
typedef struct ProjectileEffect {
    ActorRecord *owner;
    struct { u16 flags; } *animation;
    u8 pad_08;
    u8 variant;
    s16 state;
    u8 pad_0C[0x68];
    s16 target_x;
    s16 target_y;
    s16 target_z;
    u8 flags;
    s8 travel_ticks;
    u8 pad_7C[2];
    s16 direction;
    u8 pad_80[2];
    s16 timer;
    u8 pad_84[0xC];
    u8 red, green, blue;
    u8 pad_93[3];
    s16 impact_phase;
    struct { u8 pad_98[8]; u8 unk_A0; u8 pad_A1[3]; } sprite_data;
    u8 next_tile_x;
    u8 next_tile_y;
} ProjectileEffect;

/* State used by the expanding fade callback and its angle/height creator. */
typedef struct ExpandingFadeEffectBody {
    u8 pad_00[0x4];
    u16 age;
    s16 radius;
    union { s16 s; u16 u; } angle;
    u16 height_offset;
    u8 pad_0C[0xF8];
} ExpandingFadeEffectBody;

/* Three 23-entry coordinate arrays followed by the point-cloud lifetime data. */
typedef struct RandomRadialVectorEffectBody {
    s32 color;
    u8 pad_04[0xC];
    union { s16 s; u16 u; } intensity;
    s16 divisor;
    s16 point_count;
    s16 point_x[23];
    s16 point_y[23];
    s16 point_z[23];
    u16 spin_rate;
} RandomRadialVectorEffectBody;

void update_projectile_trail_and_hit_effect(ProjectileEffect *effect, ObjectPosition *motion, SpriteFrameState *sprite);

void create_random_radial_vector_effect(s32 radius, s32 initial_value, s16 extent, s32 x, s32 y, s32 z);
void clear_listed_tile_flags(void);
s32 scan_flagged_tiles_along_direction(s16 scan_direction, s32 start_x, s32 start_y);

/* Callback work and the fields installed by create_linked_effect_controller. */
typedef struct LinkedEffectControllerBody {
    void *field00;
    void *field04;
    void *field08;
    void *animation;
    SpritePartCommand *command;
    ObjectPosition *last_position;
    u8 pad_18[0x10];
    union { s16 s; volatile u16 u; u16 p; } state;
    u8 pad_2A[0x4];
    union { volatile s16 s; s16 u; u16 p; } arc_steps_left;
    u16 delay_ticks;
    u8 pad_32[0x6];
    s16 ground_height;
} LinkedEffectControllerBody;






struct S_81976850_0;
void follow_source_then_seek_target(struct S_81976850_0 *effect, ObjectPosition *motion, void *visual);
void update_expanding_fade_effect(ExpandingFadeEffectBody *effect, ObjectPosition *position, SpriteFrameState *sprite);

/* Work passed to the target-tint sequence. The elapsed counter advances on
 * entry, phase selects the callback state and timer controls its two waits.
 * create_linked_effect_controller receives the same owner and animation. */
typedef struct TargetTintWork {
    void *owner;
    struct { u16 flags; } *animation;
    u8 variant;
    u8 pad_09;
    s16 phase;
    u8 pad_0C[8];
    u16 facing;
    u16 elapsed;
    s16 timer;
} TargetTintWork;

void update_directional_actor_effect(TargetTintWork *state);

s16 mark_tiles_beside_direction(s16 direction, s16 origin_x, s16 origin_y);
void mark_tiles_in_view_direction(void);

/* Base address view used by clear_listed_tile_flags; cells start at +0x4000. */
extern u8 shared_decode_staging_buffer[16400];

/* Callback entry points. */
s32 queue_projected_mesh_points_and_texture_packets(u8 *node_data, u16 *position);
void build_visible_tile_quads(MeshEffectObjectBody *tiles);
void update_owner_linked_sprite_effect(OwnerLinkedSpriteEffectBody *object, ObjectPosition *unused, SpriteFrameState *state);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void transform_sprite_parts_to_quads(s32 context, ObjectPosition *position, SpriteFrameState *sprite, s16 depth_bias);
void render_map_cell_mesh(void);

#include "shared/dungeon_effect_views.h"
void raise_entity_to_ground(PointRecord *state, ObjectPosition *position);

void try_apply_wind_protection(ActorRecord *target, s32 effect_arg, ActorRecord *caster);

void create_interpolated_line_effect(s32 object_arg, s32 *start_pos, s32 *end_pos);

void append_coordinate_record(s32 x, s32 y, s32 value, s32 store_value);
s16 round_sampled_height_to_cell_boundary(s32 grid_x, s32 grid_y);

void *create_five_point_orbit_effect(s32 state_value, ObjectPosition *source_data, s16 initial_setting);

extern const u8 no_effect_target_prefix[48];
extern const u8 no_effect_target_period[4];
#endif
