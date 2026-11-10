#ifndef TOWN_PLAYER_GROUND_INPUT_FALLBACK_G00532_H
#define TOWN_PLAYER_GROUND_INPUT_FALLBACK_G00532_H
/* shared declarations for ground input fallback. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - town/func_800938A0. */

#include "common.h"
#include "shared/town_object.h"
#include "shared/position_query.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "town/player/coordinates.h"

void initialize_actor_action_state();
/* extern */
void initialize_action_object();
/* extern */
/* extern */
void move_both_components_toward_zero_direction_dependent_steps_clamping_zero(ObjectPosition *record);
/* extern */
/* extern */
/* extern */
void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(ObjectPosition *position);
extern void init_input_action_fallback(void *, void *, s32);

/* Functions defined in this translation unit. */
void update_actor_ground_and_input(s32 controller, ObjectPosition *actor, s32 context);
void update_and_fallback_on_input(s32 *value, ObjectPosition *context, s32 update_arg);
void update_input_and_fallback_action(s32 *value, ObjectPosition *input_a, s32 input_b);

#endif
