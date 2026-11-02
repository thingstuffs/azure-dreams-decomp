#ifndef TOWN_MINIGAME_OBJECT_SETUP_H
#define TOWN_MINIGAME_OBJECT_SETUP_H
#include "shared/town_object.h"

struct SpriteFrameState;

void spawn_fixed_effect_object(TownObjectRecord *caller_data, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);
void spawn_effect_object_with_packet(TownObjectRecord *caller_data, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void create_positioned_linked_visual_child(void *object, ObjectPosition *position, struct SpriteFrameState *state);

#endif
