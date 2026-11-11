#ifndef TOWN_MAP_EFFECT_H
#define TOWN_MAP_EFFECT_H
/* Prototypes of the functions defined in src/town/map/effect/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"
#include "shared/vector.h"
#include "shared/town_object.h"
#include "shared/sprite_frame_state.h"

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
void update_projected_effect_points(void *object, s32 phase, void *source_data, SpriteFrameState *extent);


typedef struct MapParticleEffect {
    u8 pad0[0x66];
    u16 angle;
    u8 pad68[0x2F];
    s8 index;
    s32 value;
    struct MapParticleEffect *parent;
} MapParticleEffect;

#endif
