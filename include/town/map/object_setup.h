#ifndef TOWN_MAP_OBJECT_SETUP_H
#define TOWN_MAP_OBJECT_SETUP_H

struct SpriteFrameState;

void set_record_pointer_and_byte(void *record_data, void *placement, struct SpriteFrameState *unused_sprite);
void initialize_record_with_defaults(void *record_data, void *placement, struct SpriteFrameState *unused_sprite);
void initialize_object_header_and_state(void *body, void *placement, struct SpriteFrameState *unused_sprite);
void no_op_secondary_effect_callback(void *unused_object, void *unused_position, struct SpriteFrameState *unused_sprite);
void replace_active_table_callbacks(void *entry_data, void *unused_position, struct SpriteFrameState *unused_sprite);

void initialize_door_variant(void *record_data, void *position, struct SpriteFrameState *unused_sprite);

void initialize_object_motion_and_animation(void *object, void *position, struct SpriteFrameState *state);
void initialize_object_with_default_data(void *object, void *position, struct SpriteFrameState *state);
void initialize_record_resources(void *object, void *position, struct SpriteFrameState *state);

#endif
