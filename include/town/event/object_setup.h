#ifndef TOWN_EVENT_OBJECT_SETUP_H
#define TOWN_EVENT_OBJECT_SETUP_H
#include "shared/town_object.h"
#include "shared/entity.h"

struct SpriteFrameState;
struct Rec_D_800CFCB4;

void no_op_action_callback(TownObjectRecord *unused_object, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);
void init_trigger_action_object(TownObjectRecord *record_data, ObjectPosition *placement, struct SpriteFrameState *unused_sprite);
void init_item_flag_check_object(TownObjectRecord *record_data, ObjectPosition *placement, struct SpriteFrameState *unused_sprite);

void select_object_state_by_mode(struct Rec_D_800CFCB4 *record, ObjectPosition *position,
                                struct SpriteFrameState *state, void *default_data,
                                void *alternate_data, void *bounds);
void initialize_actor_action_with_defaults(void *actor, ObjectPosition *position,
                                          struct SpriteFrameState *state, void *data);
void initialize_object_resource_table(void *object, ObjectPosition *position, struct SpriteFrameState *state);
void initialize_object_resource_tables(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *state);
void initialize_object_resources_and_state(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *state);
void initialize_object_state_from_selector(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *state);
void initialize_object_action_with_default_data(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *state);
void initialize_actor_action_with_default_data(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *state);

#endif
