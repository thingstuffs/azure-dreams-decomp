#ifndef DUNGEON_MONSTER_PICKET_H
#define DUNGEON_MONSTER_PICKET_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void update_a_jump_toward_target_tile_restores_actor_finishes(ActorRecord *jump_state, ObjectPosition *motion, SpriteFrameState *map_entity, ActorRecord *actor);
void update_movement_animation_settles_actor_target_tile(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);



void update_a_timed_movement_animation_marks_completion(void *actor, ObjectPosition *motion, SpriteFrameState *visual);
void update_movement_destination_selection_recovery_animation(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "records/Rec_func_800AD058_arg2.h"
void create_and_initializes_display_source_position_appearance(void *source, Rec_func_800AD058_arg2 *record, ActorRecord *appearance);

void * move_eligible_item(void *origin, ActorRecord *actor);
void * pick_up_adjacent_item(void *origin, void *actor);
void update_dungeon_actor_behavior_facing_animation_state(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);

#endif
