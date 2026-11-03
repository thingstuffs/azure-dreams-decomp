#ifndef TOWN_PERSON_OBJECT_SETUP_H
#define TOWN_PERSON_OBJECT_SETUP_H
struct SpriteFrameState;

#include "common.h"
#include "shared/town_object.h"
#include "shared/entity.h"

s16 clamp_transform_coordinate_deltas(s32 x, s32 y, void *origin);
s16 get_cached_or_coordinate_transform_value(void *object, void *lookup_mode);
void initialize_object_and_update(TownObjectRecord *object, void *update_context, void *setup_context);
void apply_object_setup_update(void *object, void *callback_arg_1, struct SpriteFrameState *callback_arg_2);
struct EntityRec;
void advance_object_position(TownObjectRecord *context, struct EntityRec *object, struct SpriteFrameState *finish_arg);
void move_position_toward_target(void *work_data, void *position_data, void *completion_arg);
void initialize_object_handlers(TownObjectRecord *object, void *unused_context, void *unused_setup);
s32 select_object_setup_path(void *object, void *request_data, void *request_param);

struct TownObjectRecord;
void initialize_two_value_adjustment_action(struct TownObjectRecord *actor, s32 unused, void *init_param);
void initialize_reaction_movement(void *object, void *movement_state, void *initialization_value);

void decrement_countdown_call(struct TownObjectRecord *object, s32 unused, void *callback_context);
void decrement_reaction_timer_and_reinitialize(struct TownObjectRecord *object, void *context, void *setup);

struct Rec_D_800CFCB4;

void initialize_reaction_context(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *state);
void initialize_record_from_table_index(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *state);
void initialize_object_sprite(struct Rec_D_800CFCB4 *object, ObjectPosition *position, struct SpriteFrameState *state);

void initialize_person_resources(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *state);

#endif
