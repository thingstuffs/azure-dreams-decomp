#ifndef TOWN_PLAYER_OBJECT_H
#define TOWN_PLAYER_OBJECT_H
struct SpriteFrameState;
/* Prototypes of the functions defined in src/town/player/object/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "shared/position_views.h"

struct S_80098B30_0;
struct S_func_800A6C4C_0;
struct TownObject;

/* bind_handler_and_initialize_entity.c */
void bind_handler_and_initialize_entity(struct S_80098B30_0 *state, ObjectPosition *record, void *unused_action_data);

/* clear_entity_record_fields.c */
void clear_entity_record_fields(ObjectPosition *record);

/* clear_handled_object_or_callback.c */
void clear_handled_object_or_callback(struct S_func_800A6C4C_0 *object, s32 input, s32 callback_data);

/* initialize_action_object_and_play_sound.c */
void initialize_action_object_and_play_sound(s32 **record, ObjectPosition *unused, s32 setup_value);

/* initialize_entry_object_and_play_sound.c */
void initialize_entry_object_and_play_sound(struct TownObject *object, ObjectPosition *table_target, void *ptr2);

/* initialize_global_player_object.c */
void initialize_global_player_object(void);

/* initialize_indexed_object_and_clear_flags.c */
void initialize_indexed_object_and_clear_flags(TownObjectRecord *object, ObjectPosition *setupValue, struct SpriteFrameState *initializationValue);

/* initialize_indexed_object_and_lookup_value.c */
void initialize_indexed_object_and_lookup_value(void *object, s32 lookup_arg, s32 handler_param);

/* initialize_object_and_reset_value.c */
void initialize_object_and_reset_value(TownObjectRecord *object, ObjectPosition *setupArgument, void *ptr2);

/* initialize_object_and_run_follow_up.c */
void initialize_object_and_run_follow_up(TownObjectRecord *object, ObjectPosition *followUpArg, void *ptr2);

/* initialize_object_transform_and_handler.c */
void initialize_object_transform_and_handler(TownObjectRecord *object, ObjectPosition *transform, void *ptr2);

/* initialize_player_entity_callbacks.c */
void initialize_player_entity_callbacks(s32 entity_id, s32 x, s32 y);

/* initialize_player_object.c */
void initialize_player_object(void *object);

/* initialize_player_object_data.c */
void initialize_player_object_data(void);

/* initialize_randomized_object_action.c */

/* initialize_scaled_effect_object.c */
void initialize_scaled_effect_object(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *transform);

/* initialize_unit_scale_object.c */
void initialize_unit_scale_object(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *transform);

/* reset_indexed_object_and_process_context.c */
void reset_indexed_object_and_process_context(TownObjectRecord *object, ObjectPosition *context, void *ptr2);

/* reset_indexed_object_and_set_handler.c */
void reset_indexed_object_and_set_handler(TownObjectRecord *object, ObjectPosition *context, void *ptr2);

/* retire_object_on_check_or_callback.c */
void retire_object_on_check_or_callback(void *object, void *input, void *context);

/* tick_countdown_and_initialize_object.c */
void tick_countdown_and_initialize_object(UnsignedCountdownView *state, ObjectPosition *context, s32 mode);

/* update_entity_and_handle_flagged_action.c */

/* update_entity_countdown_transition.c */

/* update_object_and_countdown.c */

/* update_threshold_bound_object.c */
void update_threshold_bound_object(void *context, ObjectPosition *object, void *update_arg);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/sprite_frame_state.h"

void update_object_and_countdown(TownObjectRecord *state, ObjectPosition *object, SpriteFrameState *sprite);

void initialize_randomized_object_action(TownObjectRecord *object, ObjectPosition *motion, SpriteFrameState *sprite);

void update_entity_and_handle_flagged_action(void *record_arg, void *context, SpriteFrameState *sprite);

void update_entity_countdown_transition(void *record_arg, void *context, SpriteFrameState *sprite);

/* Retail motion-handler callback address used by the object binder. */
void adjust_object_motion_at_threshold(s32 context, ObjectPosition *record, s32 action_data);

#endif
