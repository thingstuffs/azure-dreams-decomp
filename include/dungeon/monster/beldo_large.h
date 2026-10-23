#ifndef DUNGEON_MONSTER_BELDO_LARGE_H
#define DUNGEON_MONSTER_BELDO_LARGE_H

/* Function contracts owned by src/dungeon/monster/beldo_large/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
void create_multi_form_segment_ring(EntityRec *origin);
void advance_linked_actor_motion_script(void *state_in, ObjectPosition *motion_in, struct SpriteFrameState *sprite_in);




void update_actor_callbacks_and_motion(void *owner_arg, ObjectPosition *motion, SpriteFrameState *data);
void update_vertical_motion_and_effect(void *motion, ObjectPosition *position, void *effect);

#endif
