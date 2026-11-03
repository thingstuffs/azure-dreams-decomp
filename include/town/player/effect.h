#ifndef TOWN_PLAYER_EFFECT_H
#define TOWN_PLAYER_EFFECT_H
struct SpriteFrameState;

#include "town/player/record.h"
/* Prototypes of the functions defined in src/town/player/effect/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"
#include "shared/town_object.h"

struct S_800A58CC_2;
struct S_800A5DF8_0;
struct S_800A5DF8_4;

/* create_colored_scaled_effect.c */
void create_colored_scaled_effect(s32 object_id);

/* effect.c */
void tick_random_radial_spawns(TownObjectRecord *object, s32 target);

/* fade_and_grow_effect.c */
void fade_and_grow_effect(void *record, s32 unused, void *effect);

/* initialize_effect_and_adjust_value_g01140.c */
void initialize_effect_and_adjust_value(void *object, ObjectPosition *record, s32 init_value);
s32 compute_height_based_offset(ObjectPosition *state);
void update_object_view_transition(struct S_800A58CC_2 *state_arg, ObjectPosition *object);
void update_actor_effect_transition(struct S_800A5DF8_4 *state, ObjectPosition *actor, s32 context);
void update_town_movement_and_actions(TownPlayerRecord *state, ObjectPosition *table, void *action_context);

void turn_entity_toward_target(TownPlayerRecord *entity, void *transform, struct SpriteFrameState *sprite);

void update_effect_record_and_dispatch(TownPlayerRecord *handler, ObjectPosition *record, struct SpriteFrameState *sprite);

#endif
