#ifndef DUNGEON_MONSTER_WEADOG_H
#define DUNGEON_MONSTER_WEADOG_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void advance_timed_actor_hop(void *action, void *motion, SpriteFrameState *sprite, void *actor);
void advance_timed_hop_and_recover(void *motion_state, void *motion, SpriteFrameState *sprite, void *actor);
void update_weadog_timed_move(void *action, void *motion, SpriteFrameState *sprite, void *actor);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void advance_timed_sprite_flashing_sequence(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

void *create_overlay_effect_object(s16 spawn_flags, s16 attr_a, s16 attr_b, s32 attr_c);
void create_random_color_offset_effect(void *parent_arg, s16 initial_14, s32 unused, s16 initial_32, s16 offset_x, s16 offset_y, s16 offset_z);
void update_actor_targeted_action(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

#endif
