#ifndef TOWN_PERSON_OBJECT_SETUP_H
#define TOWN_PERSON_OBJECT_SETUP_H

#include "common.h"

s16 clamp_transform_coordinate_deltas(s32 x, s32 y, void *origin);
s16 get_cached_or_coordinate_transform_value(void *object, void *lookup_mode);
void initialize_object_and_update(void *object, void *update_context, void *setup_context);
void apply_object_setup_and_update(void *object, void *update_context, void *setup_context);
void apply_object_setup_update(void *object, void *callback_arg_1, void *callback_arg_2);
struct EntityRec;
void advance_object_position(void *context, struct EntityRec *object, void *finish_arg);
void move_position_toward_target(void *work_data, void *position_data, void *completion_arg);
s32 select_object_setup_path(void *object, void *request_data, void *request_param, s32 check_param);

#endif
