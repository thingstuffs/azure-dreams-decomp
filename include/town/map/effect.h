#ifndef TOWN_MAP_EFFECT_H
#define TOWN_MAP_EFFECT_H
/* Prototypes of the functions defined in src/town/map/effect/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"
#include "shared/vector.h"

struct Core;
struct S_800A8CA8_2;
struct SpriteFrameState;

/* initialize_effect_with_child_sprites.c */
void initialize_effect_with_child_sprites(void *parent, ObjectPosition *position);

/* initialize_effect_with_random_angle.c */
void initialize_effect_with_random_angle(struct Core *effect, IntVector3 *origin);

/* initialize_random_particle_effect.c */
void initialize_random_particle_effect(struct Core *parent_core, IntVector3 *origin);

/* no_op_effect_callback.c */
void no_op_effect_callback(void);

/* no_op_secondary_effect_callback.c */
void no_op_secondary_effect_callback(void *unused_object, void *unused_position, struct SpriteFrameState *unused_sprite);

/* update_projected_effect_points.c */
void update_projected_effect_points(void *object, s32 phase, void *source_data, struct S_800A8CA8_2 *extent);

#endif
