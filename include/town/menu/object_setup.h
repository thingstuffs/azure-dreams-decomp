#ifndef TOWN_MENU_OBJECT_SETUP_H
#define TOWN_MENU_OBJECT_SETUP_H

/* Initialize scene objects with resource data and sprite callbacks. */
struct SpriteFrameState;

void initialize_effect_object(void *object, void *unused, struct SpriteFrameState *context);
void initialize_resource_object(void *object, void *unused, struct SpriteFrameState *context);
void initialize_timed_resource_object(void *object, void *unused, struct SpriteFrameState *context);

void initialize_indexed_resource_object(void *object, void *unused, struct SpriteFrameState *context);

void initialize_emote_animation(void *object, void *position, struct SpriteFrameState *state);
void initialize_emote_sprite_and_scene(void *object, void *position, struct SpriteFrameState *state);

#endif
