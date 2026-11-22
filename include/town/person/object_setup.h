#ifndef TOWN_PERSON_OBJECT_SETUP_H
#define TOWN_PERSON_OBJECT_SETUP_H
struct TownObjectRecord;
struct SpriteFrameState;

#include "common.h"
#include "shared/town_object.h"
#include "shared/entity.h"

s16 clamp_transform_coordinate_deltas(s32 x, s32 y, struct ObjectPosition *origin);
s16 get_cached_or_coordinate_transform_value(TownObjectRecord *object, ObjectPosition *position);
void reset_heading_and_update_object(TownObjectRecord *object, ObjectPosition *update_context, struct SpriteFrameState *setup_context);
void apply_object_setup_update(TownObjectRecord *object, ObjectPosition *callback_arg_1, struct SpriteFrameState *callback_arg_2);
struct EntityRec;
void advance_object_position(TownObjectRecord *context, struct ObjectPosition *object, struct SpriteFrameState *finish_arg);
void move_position_toward_target(struct TownObjectRecord *work, struct ObjectPosition *position_data, struct SpriteFrameState *sprite);
void initialize_object_handlers(TownObjectRecord *object, ObjectPosition *unused_context, struct SpriteFrameState *unused_setup);
s32 select_object_setup_path(TownObjectRecord *object, ObjectPosition *request_data, struct SpriteFrameState *request_param);

struct TownObjectRecord;
void initialize_two_value_adjustment_action(struct TownObjectRecord *actor, struct ObjectPosition *unused_position, struct SpriteFrameState *sprite);
void initialize_reaction_movement(struct TownObjectRecord *object, struct ObjectPosition *position, struct SpriteFrameState *sprite);

void start_adjustment_when_timer_ends(struct TownObjectRecord *object, struct ObjectPosition *position, struct SpriteFrameState *sprite);
void restart_reaction_when_timer_ends(struct TownObjectRecord *object, struct ObjectPosition *position, struct SpriteFrameState *sprite);

struct Rec_D_800CFCB4;

void initialize_reaction_context(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *state);
void initialize_record_from_table_index(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *state);
void initialize_object_sprite(struct Rec_D_800CFCB4 *object, ObjectPosition *position, struct SpriteFrameState *state);

void initialize_person_resources(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *state);

#endif
