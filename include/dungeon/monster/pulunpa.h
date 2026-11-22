#ifndef DUNGEON_MONSTER_PULUNPA_H
#define DUNGEON_MONSTER_PULUNPA_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 pulunpa_direction_frames[];








void advance_directional_action_and_reset(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *anim, ActorRecord *actor);



void animate_hop_to_actor_tile(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void finish_pulunpa_hop_and_grow(ActorRecord *object, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *extra);
void finish_pulunpa_floor_trap_check(ActorRecord *object, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);

void display_record_name_message(void *record);
void display_actor_message(ActorRecord *source);

struct S_8017405C_1;
void choose_heading_and_advance_actor(ActorRecord *body, s32 action, struct S_8017405C_1 *actor, ActorRecord *movement);
void advance_selected_item_action(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_pulunpa_behavior(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *creature);

void *spawn_pulunpa_in_slot_g(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);

#endif
