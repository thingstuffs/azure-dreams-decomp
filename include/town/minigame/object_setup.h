#ifndef TOWN_MINIGAME_OBJECT_SETUP_H
#define TOWN_MINIGAME_OBJECT_SETUP_H

struct SpriteFrameState;

void spawn_fixed_effect_object(void *caller_data, void *unused_position, struct SpriteFrameState *unused_sprite);
void spawn_effect_object_with_packet(void *caller_data, void *unused_position, struct SpriteFrameState *unused_sprite);

void create_positioned_linked_visual_child(void *object, void *position, struct SpriteFrameState *state);

#endif
