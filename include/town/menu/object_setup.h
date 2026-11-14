#ifndef TOWN_MENU_OBJECT_SETUP_H
#define TOWN_MENU_OBJECT_SETUP_H
#include "shared/town_object.h"

/* Initialize scene objects with resource data and sprite callbacks. */
struct SpriteFrameState;

void initialize_effect_object(void *object, ObjectPosition *unused, struct SpriteFrameState *context);
void initialize_resource_object(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);
void initialize_washed_dish_effect(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);

void initialize_item_effect_sprite(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);

void initialize_emote_animation(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *state);
void initialize_emote_sprite_and_scene(void *object, void *position, struct SpriteFrameState *state);

#endif
