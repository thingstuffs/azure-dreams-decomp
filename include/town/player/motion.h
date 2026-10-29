#ifndef TOWN_PLAYER_MOTION_H
#define TOWN_PLAYER_MOTION_H
/* Prototypes of the functions defined in src/town/player/motion/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_func_80097D54_arg0.h"
#include "shared/entity.h"
#include "shared/position_views.h"

struct Position;
struct S_800981D4_0;
struct S_8009A58C_0;
struct SpriteFrameState;

/* clear_motion_along_blocked_directions_update_affected_axes.c */
void clear_motion_along_blocked_directions_update_affected_axes(MotionDeltaView *state);

/* clear_player_motion_entry.c */
void clear_player_motion_entry(struct S_8009A58C_0 *object, s32 value);

/* copy_motion_parameters_and_reset_flag.c */
void copy_motion_parameters_and_reset_flag(void *record, void *source);

/* forward_player_motion_state.c */
void forward_player_motion_state(void *state, s32 value, s32 mode);

/* forward_player_motion_update.c */
void forward_player_motion_update(void *object, s32 value_1, s32 value_2);

/* initialize_motion_action.c */
void initialize_motion_action(Rec_func_80094268_arg0 *entity, s32 motion, s32 value);

/* initialize_object_from_motion_data.c */
void initialize_object_from_motion_data(void *object, void *initializationData, void *ptr2);

/* initialize_player_motion_parameters.c */
void initialize_player_motion_parameters(void *record, s32 update_value, s32 init_context);

/* move_entity_in_current_direction.c */
void move_entity_in_current_direction(Rec_func_80097D54_arg0 *move_state, EntityRec *entity, s32 finish_arg);

/* move_player_halfway_to_target.c */
void move_player_halfway_to_target(Rec_func_80094268_arg0 *state, struct Position *position, s32 context);

/* move_player_toward_target_with_timer.c */
void move_player_toward_target_with_timer(Rec_func_80094268_arg0 *motion, EntityRec *position, s32 context);

/* move_the_actor_perpendicular_selected_direction_unless_step_changes_sides.c */
void move_the_actor_perpendicular_selected_direction_unless_step_changes_sides(void *position_data);

/* move_value_toward.c */
s32 move_value_toward_300(s32 value, struct S_800981D4_0 *field_ptr, s32 other_value);

/* process_player_motion_state.c */
void process_player_motion_state(Rec_func_80094268_arg0 *object, s32 forwardedArg1, s32 forwardedArg2);

/* set_motion_handler_and_copy_signed_byte.c */
void set_motion_handler_and_copy_signed_byte(void *record_data, void *placement, struct SpriteFrameState *unused_sprite);

#endif
