#ifndef DUNGEON_EFFECT_MESH_H
#define DUNGEON_EFFECT_MESH_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* One four-byte coordinate record in the mesh renderer's variable-length tile list. */
typedef struct MeshEffectObjectBody {
    u8 x;
    u8 y;
    u16 height;
} MeshEffectObjectBody;
/* Owner link stored by the vertically-offset sprite effect's updater. */
typedef struct AnOwnerLinkedSpriteEffectPositionVerticalOffsetBody {
    void *owner;
} AnOwnerLinkedSpriteEffectPositionVerticalOffsetBody;
typedef struct TerrainSeekingColoredPointBody {
    u32 color;
    s16 unk_04;
    u8 pad_06[0xA];
    s16 intensity;
    s16 divisor;
    u8 pad_14[0xA0];
    s32 z_velocity;
} TerrainSeekingColoredPointBody;
void advance_colored_point_toward_terrain(TerrainSeekingColoredPointBody *object, s16 *position);
s32 project_colored_point_to_ordering_table(u8 *render_data, u8 *source_vertex);
/* Projectile callback work at node +0x20. The +0x98 sprite template is
 * installed in sprite->source and its +8 byte is alternated during impact. */
typedef struct ProjectileEffect {
    ActorRecord *owner;
    struct { u16 flags; } *animation;
    u8 pad_08;
    u8 variant;
    union { s16 s; u16 u; } state;
    u8 pad_0C[0x68];
    union { s16 s; u16 u; } target_x;
    union { s16 s; u16 u; } target_y;
    union { s16 s; u16 u; } target_z;
    u8 flags;
    union { s8 s; u8 u; } travel_ticks;
    u8 pad_7C[2];
    union { s16 s; u16 u; } direction;
    u8 pad_80[2];
    union { s16 s; u16 u; } timer;
    u8 pad_84[0xC];
    u8 red, green, blue;
    u8 pad_93[3];
    union { s16 s; u16 u; } impact_phase;
    struct { u8 pad_98[8]; u8 unk_A0; u8 pad_A1[3]; } sprite_data;
    u8 next_tile_x;
    u8 next_tile_y;
} ProjectileEffect;

/* State used by the expanding fade callback and its angle/height creator. */
typedef struct AnRandomAngleHeightOffsetAroundReferencePositionBody {
    u8 pad_00[0x4];
    union { s16 s; u16 u; } unk_04;
    union { s16 s; u16 u; } unk_06;
    union { s16 s; u16 u; } unk_08;
    u16 unk_0A;
    u8 pad_0C[0xF8];
} AnRandomAngleHeightOffsetAroundReferencePositionBody;

/* Three 23-entry coordinate arrays followed by the point-cloud lifetime data. */
typedef struct RandomRadialVectorEffectBody {
    s32 unk_00;
    u8 pad_04[0xC];
    union { s16 s; u16 u; } unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16[23];
    s16 unk_44[23];
    s16 unk_72[23];
    u16 unk_A0;
} RandomRadialVectorEffectBody;

void update_projectile_trail_and_hit_effect(ProjectileEffect *effect, ObjectPosition *motion, SpriteFrameState *sprite);

void create_random_radial_vector_effect(s32 radius, s32 initial_value, s16 extent, s32 x, s32 y, s32 z);
void clear_listed_tile_flags(void);
s32 count_flagged_tiles_along_direction_2(s16 scan_direction, s32 start_x, s32 start_y);

/* Callback work and the fields installed by create_linked_effect_controller. */
typedef struct LinkedEffectControllerBody {
    void *field00;
    void *field04;
    void *field08;
    void *field0C;
    union { s32 s; u8 *u; } field10;
    s32 field14;
    u8 pad_18[0x10];
    union { s16 s; volatile u16 u; u16 p; } field28;
    u8 pad_2A[0x4];
    union { volatile s16 s; s16 u; u16 p; } field2E;
    union { s16 s; u16 u; } field30;
    u8 pad_32[0x6];
    s16 field38;
} LinkedEffectControllerBody;






void follow_source_then_seek_target(void *effect, ObjectPosition *motion, void *visual);
void update_expanding_fade_effect(AnRandomAngleHeightOffsetAroundReferencePositionBody *effect, ObjectPosition *position, SpriteFrameState *sprite);

/* Work passed to the target-tint sequence. The elapsed counter advances on
 * entry, phase selects the callback state and timer controls its two waits.
 * create_linked_effect_controller receives the same owner and animation. */
typedef struct TargetTintWork {
    void *owner;
    struct { u16 flags; } *animation;
    u8 variant;
    u8 pad_09;
    union { s16 s; u16 u; } phase;
    u8 pad_0C[8];
    u16 facing;
    u16 elapsed;
    union { s16 s; u16 u; } timer;
} TargetTintWork;

void update_directional_actor_effect(TargetTintWork *state);

s16 process_perpendicular_eligible_tiles(s16 direction, s16 origin_x, s16 origin_y);
void process_current_facing_directions(void);

/* Base address view used by clear_listed_tile_flags; cells start at +0x4000. */
extern u8 shared_decode_staging_buffer[16400];

/* Callback entry points. */
s32 queue_projected_mesh_points_and_texture_packets(u8 *node_data, u16 *position);
void build_visible_tile_quads(MeshEffectObjectBody *tiles);
void handle_increment_s_counter_update_state_propagate_status_flags(AnOwnerLinkedSpriteEffectPositionVerticalOffsetBody *object, ObjectPosition *unused, SpriteFrameState *state);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void transform_sprite_parts_to_quads(s32 context, ObjectPosition *position, SpriteFrameState *sprite, s16 depth_bias);
void render_map_cell_mesh(void);

#include "shared/dungeon_effect_views.h"
void raise_entity_to_ground(PointRecord *state, ObjectPosition *position);

void try_apply_wind_protection(ActorRecord *target, s32 effect_arg, SpriteFrameState *unused);

#endif
