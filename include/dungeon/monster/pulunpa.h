#ifndef DUNGEON_MONSTER_PULUNPA_H
#define DUNGEON_MONSTER_PULUNPA_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 pulunpa_direction_frames[];








void advance_directional_action_and_reset(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *anim, ActorRecord *actor);



void animate_hop_to_actor_tile(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void select_variant_object_data(void *object, void *motion, void *params, void *extra);
void select_variant_object_data_when_positive(void *object, ObjectPosition *unused, SpriteFrameState *source, ActorRecord *target);

void display_record_name_message(void *record);
void build_and_display_encoded_message(void *source);

#endif
