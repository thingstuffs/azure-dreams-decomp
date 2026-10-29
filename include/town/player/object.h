#ifndef TOWN_PLAYER_OBJECT_H
#define TOWN_PLAYER_OBJECT_H
/* Prototypes of the functions defined in src/town/player/object/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
#include "shared/position_views.h"

struct S_80098B30_0;
struct S_func_800A6C4C_0;
struct SpriteFrameState;
struct TownObject;

/* bind_handler_and_initialize_entity.c */
void bind_handler_and_initialize_entity(struct S_80098B30_0 *state, EntityRec *record);

/* clear_entity_record_fields.c */
void clear_entity_record_fields(EntityRec *record);

/* clear_handled_object_or_callback.c */
void clear_handled_object_or_callback(struct S_func_800A6C4C_0 *object, s32 input, s32 callback_data);

/* initialize_action_object_and_play_sound.c */
void initialize_action_object_and_play_sound(s32 **record, s32 unused, s32 setup_value);

/* initialize_entry_object_and_play_sound.c */
void initialize_entry_object_and_play_sound(struct TownObject *object, s32 table_target, void *ptr2);

/* initialize_global_player_object.c */
void initialize_global_player_object(void);

/* initialize_indexed_object_and_clear_flags.c */
void initialize_indexed_object_and_clear_flags(Rec_func_80094268_arg0 *object, s32 setupValue, s32 initializationValue);

/* initialize_indexed_object_and_lookup_value.c */
void initialize_indexed_object_and_lookup_value(void *object, s32 lookup_arg, s32 handler_param);

/* initialize_object_and_reset_value.c */
void initialize_object_and_reset_value(Rec_func_80094268_arg0 *object, s32 setupArgument, void *ptr2);

/* initialize_object_and_run_follow_up.c */
void initialize_object_and_run_follow_up(Rec_func_80094268_arg0 *object, s32 followUpArg, void *ptr2);

/* initialize_object_transform_and_handler.c */
void initialize_object_transform_and_handler(Rec_func_80094268_arg0 *object, EntityRec *transform, void *ptr2);

/* initialize_player_entity_callbacks.c */
void initialize_player_entity_callbacks(s32 entity_id, s32 x, s32 y);

/* initialize_player_object.c */
void initialize_player_object(void *object);

/* initialize_player_object_data.c */
void initialize_player_object_data(void);

/* initialize_randomized_object_action.c */
void initialize_randomized_object_action(Rec_func_80094268_arg0 *object, s32 motion, s32 table_arg);

/* initialize_scaled_effect_object.c */
void initialize_scaled_effect_object(void *object, void *position, struct SpriteFrameState *transform);

/* initialize_unit_scale_object.c */
void initialize_unit_scale_object(void *object, void *position, struct SpriteFrameState *transform);

/* reset_indexed_object_and_process_context.c */
void reset_indexed_object_and_process_context(Rec_func_80094268_arg0 *object, s32 context, void *ptr2);

/* reset_indexed_object_and_set_handler.c */
void reset_indexed_object_and_set_handler(Rec_func_80094268_arg0 *object, s32 context, void *ptr2);

/* retire_object_on_check_or_callback.c */
void retire_object_on_check_or_callback(void *object, void *input, void *context);

/* tick_countdown_and_initialize_object.c */
void tick_countdown_and_initialize_object(UnsignedCountdownView *state, void *context, s32 mode);

/* update_entity_and_handle_flagged_action.c */
void update_entity_and_handle_flagged_action(void *record, s32 context, s32 update_arg);

/* update_entity_countdown_transition.c */
void update_entity_countdown_transition(void *record, void *context, s32 update_arg);

/* update_object_and_countdown.c */
void update_object_and_countdown(Rec_func_80094268_arg0 *state, EntityRec *object, s32 context);

/* update_threshold_bound_object.c */
void update_threshold_bound_object(void *context, struct TownObject *object, void *update_arg);

#endif
