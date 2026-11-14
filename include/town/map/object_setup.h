#ifndef TOWN_MAP_OBJECT_SETUP_H
#define TOWN_MAP_OBJECT_SETUP_H
#include "shared/town_object.h"
struct TownObjectRecord;

struct SpriteFrameState;

void start_raised_position_pair(TownObjectRecord *record_data, ObjectPosition *placement, struct SpriteFrameState *unused_sprite);
void initialize_record_with_defaults(TownObjectRecord *record_data, ObjectPosition *placement, struct SpriteFrameState *unused_sprite);
void initialize_white_points_effect(void *body, ObjectPosition *placement, struct SpriteFrameState *unused_sprite);
void no_op_secondary_effect_callback(TownObjectRecord *unused_object, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);
void replace_active_table_callbacks(TownObjectRecord *entry_data, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void initialize_door_variant(TownObjectRecord *record_data, ObjectPosition *position, struct SpriteFrameState *unused_sprite);

void init_random_wander_object(void *object, ObjectPosition *position, struct SpriteFrameState *state);
void init_default_sprite_object(void *object, ObjectPosition *position, struct SpriteFrameState *state);
void init_directional_sprite_loop(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *state);

#endif
