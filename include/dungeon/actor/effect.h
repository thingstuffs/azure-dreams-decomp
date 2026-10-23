#ifndef DUNGEON_ACTOR_EFFECT_H
#define DUNGEON_ACTOR_EFFECT_H

/* Function contracts owned by src/dungeon/actor/effect/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
void *create_owner_linked_pulsing_effect(void *spawn_pos, EntityRec *source_state, void *owner);




void advance_damage_effect_and_particles(void *effect, s32 context, SpriteFrameState *record, void *actor);



void update_dropped_object_motion(void *object, register ObjectPosition *motion, void *tile);

#endif
