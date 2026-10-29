#ifndef TOWN_PERSON_OBJECT_SETUP_H
#define TOWN_PERSON_OBJECT_SETUP_H

#include "common.h"

s16 clamp_transform_coordinate_deltas(s32 x, s32 y, void *origin);
s16 get_cached_or_coordinate_transform_value(void *object, void *lookup_mode);
void initialize_object_and_update(void *object, void *update_context, void *setup_context);
void apply_object_setup_update(void *object, void *callback_arg_1, void *callback_arg_2);
struct EntityRec;
void advance_object_position(void *context, struct EntityRec *object, void *finish_arg);
void move_position_toward_target(void *work_data, void *position_data, void *completion_arg);
void initialize_object_handlers(void *object, void *unused_context, void *unused_setup);
s32 select_object_setup_path(void *object, void *request_data, void *request_param);

struct Rec_func_80094268_arg0;
void initialize_two_value_adjustment_action(struct Rec_func_80094268_arg0 *actor, s32 unused, void *init_param);
void initialize_reaction_movement(void *object, void *movement_state, void *initialization_value);

void decrement_countdown_call(struct Rec_func_80094268_arg0 *object, s32 unused, void *callback_context);
void decrement_reaction_timer_and_reinitialize(struct Rec_func_80094268_arg0 *object, void *context, void *setup);

struct SpriteFrameState;
struct Rec_D_800CFCB4;

void initialize_reaction_context(void *object, void *position, struct SpriteFrameState *state);
void initialize_record_from_table_index(void *object, void *position, struct SpriteFrameState *state);
void initialize_object_sprite(struct Rec_D_800CFCB4 *object, void *position, struct SpriteFrameState *state);

void initialize_person_resources(void *object, void *position, struct SpriteFrameState *state);

#endif
