#ifndef TOWN_MINIGAME_H
#define TOWN_MINIGAME_H

#include "common.h"
#include "town/scene/collection.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"


/* initialize_minigame_display.c */
void initialize_minigame_display(void *context);

/* Object-pool callbacks: motion is the separate node +8 position record. */
void update_bouncing_pickup(void *pickup, ObjectPosition *motion, SpriteFrameState *sprite);
void update_bouncing_pickup_after_hit(void *object, ObjectPosition *motion, SpriteFrameState *sprite);
void update_snowball_minigame_actor(TownCollectionActor *object, ObjectPosition *motion, SpriteFrameState *sprite);
void update_minigame_approach_motion(void *motion_state, ObjectPosition *motion);

void count_entries_matching_search_path(TownCollectionSequence *scene);


void create_minigame_display_objects(void);

#endif
