#ifndef TOWN_EVENT_OBJECT_SETUP_H
#define TOWN_EVENT_OBJECT_SETUP_H

struct SpriteFrameState;
struct Rec_D_800CFCB4;

void no_op_action_callback(void *unused_object, void *unused_position, struct SpriteFrameState *unused_sprite);
void initialize_record_pointers_and_clear_state(void *record_data, void *placement, struct SpriteFrameState *unused_sprite);
void initialize_variant_record_pointers_and_clear_state(void *record_data, void *placement, struct SpriteFrameState *unused_sprite);

void initialize_optional_object_state(void *object, void *position, void *state, void *data);
void select_object_state_by_mode(struct Rec_D_800CFCB4 *record, void *position,
                                struct SpriteFrameState *state, void *default_data,
                                void *alternate_data, void *bounds);
void initialize_actor_action_with_defaults(void *actor, void *position,
                                          struct SpriteFrameState *state, void *data);
void initialize_object_resource_table(void *object, void *position, struct SpriteFrameState *state);
void initialize_object_resource_tables(void *object, void *position, struct SpriteFrameState *state);
void initialize_object_resources_and_state(void *object, void *position, struct SpriteFrameState *state);
void initialize_object_state_from_selector(void *object, void *position, struct SpriteFrameState *state);
void initialize_object_action_with_default_data(void *object, void *position, struct SpriteFrameState *state);
void initialize_actor_action_with_default_data(void *object, void *position, struct SpriteFrameState *state);

#endif
