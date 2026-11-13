#ifndef TOWN_MAP_OBJECT_SETUP_H
#define TOWN_MAP_OBJECT_SETUP_H
#include "shared/town_object.h"
struct TownObjectRecord;

struct SpriteFrameState;

void start_raised_position_pair(TownObjectRecord *record_data, ObjectPosition *placement, struct SpriteFrameState *unused_sprite);
void initialize_record_with_defaults(TownObjectRecord *record_data, ObjectPosition *placement, struct SpriteFrameState *unused_sprite);
void initialize_object_header_and_state(void *body, ObjectPosition *placement, struct SpriteFrameState *unused_sprite);
void no_op_secondary_effect_callback(TownObjectRecord *unused_object, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);
void replace_active_table_callbacks(TownObjectRecord *entry_data, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void initialize_door_variant(TownObjectRecord *record_data, ObjectPosition *position, struct SpriteFrameState *unused_sprite);

void initialize_object_motion_and_animation(void *object, ObjectPosition *position, struct SpriteFrameState *state);
void initialize_object_with_default_data(void *object, ObjectPosition *position, struct SpriteFrameState *state);
void initialize_record_resources(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *state);

#endif
