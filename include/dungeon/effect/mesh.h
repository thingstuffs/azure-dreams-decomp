#ifndef DUNGEON_EFFECT_MESH_H
#define DUNGEON_EFFECT_MESH_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
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

void update_projectile_trail_and_hit_effect(ProjectileEffect *effect, ObjectPosition *motion, SpriteFrameState *sprite);

void create_random_radial_vector_effect(s32 radius, s32 initial_value, s16 extent, s32 x, s32 y, s32 z);
void clear_listed_tile_flags(void);
s32 count_flagged_tiles_along_direction_2(s16 scan_direction, s32 start_x, s32 start_y);






void follow_source_then_seek_target(void *effect, ObjectPosition *motion, void *visual);
void update_expanding_fade_effect(void *effect, ObjectPosition *position, SpriteFrameState *sprite);

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
void build_visible_tile_quads(u8 *tiles);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void transform_sprite_parts_to_quads(s32 context, ObjectPosition *position, SpriteFrameState *sprite, s16 depth_bias);
void render_map_cell_mesh(void);

#include "shared/dungeon_effect_views.h"
void raise_entity_to_ground(PointRecord *state, ObjectPosition *position);

#endif
