#ifndef TOWN_PLAYER_POSITION_H
#define TOWN_PLAYER_POSITION_H
/* Prototypes of the functions defined in src/town/player/position/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
#include "shared/position_views.h"
#include "shared/vector.h"

struct S_800935BC_0;
struct TownObject;

/* add_motion_deltas_to_position.c */
void add_motion_deltas_to_position(ObjectPosition *motion);

/* advance_player_position.c */
void advance_player_position(s32 context, EntityRec *object, s32 update_data);

/* advance_player_position_and_angle.c */
void advance_player_position_and_angle(void *work_data, void *position_data, s32 context);

/* approach_linked_position_until_timeout.c */
void approach_linked_position_until_timeout(struct TownObject *object, IntVector3 *position, void *context);

/* approach_target_tile_until_timeout.c */
void approach_target_tile_until_timeout(Rec_func_80094268_arg0 *target, struct S_800935BC_0 *position, void *transition_arg);

/* clamp_coordinates_to_bounds.c */
s32 clamp_coordinates_to_bounds(s32 *x_ptr, s32 *y_ptr);

/* expand_bounds_to_inset_rectangle.c */
void expand_bounds_to_inset_rectangle(s32 *bounds, s16 *rect);

/* follow_linked_position_until_timeout.c */
void follow_linked_position_until_timeout(UnsignedCountdownView *state, IntVector3 *out, s32 handler_arg);

/* handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile.c */
void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(EntityRec *position);

/* initialize_actor_position_interaction_action.c */
void initialize_actor_position_interaction_action(Rec_func_80094268_arg0 *record, s32 unused, s32 setup_value);

/* interpolate_position_by_angle_offset.c */
void interpolate_position_by_angle_offset(void *motion, EntityRec *position);

/* move_position_toward_target_and_finish.c */
void move_position_toward_target_and_finish(u8 *motion, u8 *position, s32 callback_arg);

/* query_larger_position_result.c */
s16 query_larger_position_result(s32 *input);

/* refresh_object_position_and_initialize.c */
void refresh_object_position_and_initialize(void *context, void *object, s32 mode);

/* select_the_smaller_position_query_result_capped_writes_associated.c */
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated(void *position_data, s32 *out_value);

/* set_player_handler_and_position_value.c */
void set_player_handler_and_position_value(void *object, s32 value_arg, s32 handler_param);

/* store_position_and_compute_delta.c */
void store_position_and_compute_delta(s32 *newValue);

/* update_actor_position_and_interaction.c */
void update_actor_position_and_interaction(Rec_func_80094268_arg0 *actor, EntityRec *body, s32 context);

#endif
