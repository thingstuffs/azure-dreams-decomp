#ifndef TOWN_PLAYER_POSITION_H
#define TOWN_PLAYER_POSITION_H
struct TownObjectRecord;
struct SpriteFrameState;
/* Prototypes of the functions defined in src/town/player/position/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "shared/position_views.h"
#include "shared/vector.h"

struct S_800935BC_0;
struct TownObject;

/* add_motion_deltas_to_position.c */
void add_motion_deltas_to_position(ObjectPosition *motion);

/* advance_player_position.c */

/* advance_player_position_and_angle.c */

/* approach_linked_position_until_timeout.c */
void approach_linked_position_until_timeout(struct TownObject *object, IntVector3 *position, void *context);

/* approach_target_tile_until_timeout.c */
void approach_target_tile_until_timeout(TownObjectRecord *target, struct S_800935BC_0 *position, void *transition_arg);

/* clamp_coordinates_to_bounds.c */
s32 clamp_coordinates_to_bounds(s32 *x_ptr, s32 *y_ptr);

/* expand_bounds_to_inset_rectangle.c */
void expand_bounds_to_inset_rectangle(s32 *bounds, s16 *rect);

/* follow_linked_position_until_timeout.c */
void follow_linked_position_until_timeout(UnsignedCountdownView *state, IntVector3 *out, struct SpriteFrameState *handler_arg);

/* resolve_collision_axis_order.c */
void resolve_collision_axis_order(ObjectPosition *position);

/* initialize_actor_position_interaction_action.c */
void initialize_actor_position_interaction_action(TownObjectRecord *record, ObjectPosition *unused, s32 setup_value);

/* interpolate_position_by_angle_offset.c */
void interpolate_position_by_angle_offset(void *motion, ObjectPosition *position);

/* move_position_toward_target_and_finish.c */

/* query_larger_position_result.c */
s16 query_larger_position_result(ObjectPosition *input);

/* refresh_object_position_and_initialize.c */

/* select_the_smaller_position_query_result_capped_writes_associated.c */
s16 query_capped_surface_height(void *position_data, s32 *out_value);

/* set_player_handler_and_position_value.c */
void set_player_handler_and_position_value(TownObjectRecord *object, s32 value_arg, struct SpriteFrameState *handler_param);

/* store_position_and_compute_delta.c */
void store_position_and_compute_delta(s32 *newValue);

/* update_actor_position_and_interaction.c */
void update_actor_position_and_interaction(TownObjectRecord *actor, ObjectPosition *body, s32 context);

void advance_player_position_and_angle(void *work_data, ObjectPosition *position_data, struct SpriteFrameState *sprite);

void advance_player_position(struct TownObjectRecord *context, ObjectPosition *object, struct SpriteFrameState *sprite);

void move_position_toward_target_and_finish(u8 *motion, ObjectPosition *position, struct SpriteFrameState *sprite);

void refresh_object_position_and_initialize(void *context, ObjectPosition *object, struct SpriteFrameState *sprite);

#endif
