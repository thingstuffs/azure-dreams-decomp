#ifndef TOWN_PLAYER_MOTION_H
#define TOWN_PLAYER_MOTION_H
struct SpriteFrameState;
struct TownObjectRecord;
/* Prototypes of the functions defined in src/town/player/motion/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/town_object.h"
#include "records/Rec_func_80097D54_arg0.h"
#include "shared/entity.h"
#include "shared/position_views.h"
#include "town/player/record.h"

struct Position;

/* clear_motion_along_blocked_directions_update_affected_axes.c */
void clear_motion_along_blocked_directions_update_affected_axes(ObjectPosition *state);

/* clear_player_motion_entry.c */
void clear_player_motion_entry(TownPlayerRecord *object, ObjectPosition *value);

/* copy_motion_parameters_and_reset_flag.c */
void copy_motion_parameters_and_reset_flag(void *record, ObjectPosition *source);

/* forward_player_motion_state.c */

/* forward_player_motion_update.c */

/* initialize_motion_action.c */

/* initialize_object_from_motion_data.c */
void initialize_object_from_motion_data(void *object, ObjectPosition *initializationData, void *ptr2);

/* initialize_player_motion_parameters.c */

/* move_entity_in_current_direction.c */
void move_entity_in_current_direction(Rec_func_80097D54_arg0 *move_state, ObjectPosition *entity, struct SpriteFrameState *finish_arg);

/* move_player_halfway_to_target.c */
void move_player_halfway_to_target(TownObjectRecord *state, ObjectPosition *position, struct SpriteFrameState *context);

/* move_player_toward_target_with_timer.c */

/* move_the_actor_perpendicular_selected_direction_unless_step_changes_sides.c */
void move_the_actor_perpendicular_selected_direction_unless_step_changes_sides(void *position_data);

/* move_value_toward.c */
s32 move_value_toward_300(s32 value, ObjectPosition *field_ptr, struct SpriteFrameState *other_value);

/* process_player_motion_state.c */

/* set_motion_handler_and_copy_signed_byte.c */
void set_motion_handler_and_copy_signed_byte(TownObjectRecord *record_data, ObjectPosition *placement, struct SpriteFrameState *unused_sprite);

void step_actor_positive_y_until_timer_expires(TownObjectRecord *state, ObjectPosition *object, struct SpriteFrameState *sprite);

void step_actor_negative_x_until_timer_expires(TownObjectRecord *state, ObjectPosition *object, struct SpriteFrameState *sprite);

void step_actor_positive_x_until_timer_expires(TownObjectRecord *state, ObjectPosition *object, struct SpriteFrameState *sprite);

void forward_player_motion_state(void *state, ObjectPosition *value, struct SpriteFrameState *sprite);

void forward_player_motion_update(void *object, ObjectPosition *value_1, struct SpriteFrameState *sprite);

void move_player_toward_target_with_timer(TownObjectRecord *motion, ObjectPosition *position, struct SpriteFrameState *sprite);

void process_player_motion_state(TownObjectRecord *object, ObjectPosition *forwardedArg1, struct SpriteFrameState *sprite);

void initialize_player_motion_parameters(void *record, ObjectPosition *update_value, struct SpriteFrameState *sprite);

void initialize_motion_action(TownObjectRecord *entity, void *motion, struct SpriteFrameState *sprite);

#endif
