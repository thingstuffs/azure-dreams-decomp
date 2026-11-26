#ifndef TOWN_MAP_EFFECT_H
#define TOWN_MAP_EFFECT_H
/* Prototypes of the functions defined in src/town/map/effect/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"
#include "shared/vector.h"
#include "shared/town_object.h"
#include "shared/sprite_frame_state.h"

/* draw_shaded_quad_ring owns this scratchpad while constructing the ring.
 * RotTransPers writes each packed screen coordinate, and the packet builder
 * clips its two halves and submits them with the corresponding packed color. */
typedef struct TownRingProjection {
    u8 pad_00[0x24];
    u32 *ordering_table;
    u8 pad_28[0x4C];
    SVECTOR start_point;
    SVECTOR mid_point;
    SVECTOR end_point;
    u8 pad_8C[8];
    s32 projection_scale;
    s32 projection_flags;
    u8 pad_9C[0x28];
    s32 depth_index;
    u8 pad_C8[0x20];
    s32 inner_xy;
    s32 middle_xy;
    s32 previous_inner_xy;
    s32 previous_middle_xy;
    u8 pad_F8[0x1C];
    SpriteColor color;
    SpriteColor previous_color;
    u8 pad_11C[8];
    s32 outer_xy;
    s32 previous_outer_xy;
} TownRingProjection;

struct MapParticleEffect;
struct SpriteFrameState;

/* initialize_effect_with_child_sprites.c */
void initialize_effect_with_child_sprites(TownObjectRecord *parent, ObjectPosition *position, struct SpriteFrameState *sprite_unused);

/* initialize_effect_with_random_angle.c */
void initialize_effect_with_random_angle(struct MapParticleEffect *effect, ObjectPosition *origin, struct SpriteFrameState *sprite_unused);

/* initialize_random_particle_effect.c */
void initialize_random_particle_effect(struct MapParticleEffect *parent_core, ObjectPosition *origin, struct SpriteFrameState *sprite_unused);

/* no_op_effect_callback.c */
void no_op_effect_callback(void);

/* no_op_secondary_effect_callback.c */
void no_op_secondary_effect_callback(TownObjectRecord *unused_object, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

/* update_projected_effect_points.c */
void update_projected_effect_points(TownRingProjection *object, s32 phase, ObjectPosition *source, SpriteFrameState *extent);


typedef struct MapParticleEffect {
    u8 pad0[0x66];
    s16 angle;
    u8 pad68[0x2F];
    s8 index;
    u8 *active_flag;
    struct MapParticleEffect *parent;
} MapParticleEffect;

#endif
