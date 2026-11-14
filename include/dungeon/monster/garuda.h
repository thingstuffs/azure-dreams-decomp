#ifndef DUNGEON_MONSTER_GARUDA_H
#define DUNGEON_MONSTER_GARUDA_H

/* Function contracts owned by src/dungeon/monster/garuda/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
void update_garuda_actor(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite);




void wait_garuda_mp_and_animate(void *entity, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor);

void update_creature_animation_action(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite_arg, ActorRecord *creature);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void begin_garuda_walk(ActorRecord *owner, ObjectPosition *unused, SpriteFrameState *part, ActorRecord *actor);
void *spawn_garuda_slot_a(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c);
void *spawn_garuda_slot_f(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);

void complete_timed_tile_movement(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity);

#endif
