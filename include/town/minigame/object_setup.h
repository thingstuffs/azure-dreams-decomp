#ifndef TOWN_MINIGAME_OBJECT_SETUP_H
#define TOWN_MINIGAME_OBJECT_SETUP_H
#include "shared/town_object.h"

struct SpriteFrameState;

void spawn_cursor_animation_object(TownObjectRecord *caller_data, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);
void spawn_state_position_object(TownObjectRecord *caller_data, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void initialize_actor_with_visual_child(void *object, ObjectPosition *position, struct SpriteFrameState *state);

#endif
