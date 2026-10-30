#ifndef DUNGEON_MONSTER_DEATH_H
#define DUNGEON_MONSTER_DEATH_H

/* Function contracts owned by src/dungeon/monster/death/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
void update_entity_movement_animation_and_ground(void *entity, ObjectPosition *motion, void *sprite);








void advance_effect_toward_target(void *effect, ObjectPosition *position);
void finish_staged_jump_at_tile_center(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);



void advance_actor_states_and_entity_flags(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *animation, ActorRecord *entity);

struct S_80173C40_0;
void initialize_object_and_clear_state(struct S_80173C40_0 *object, void *init_data, SpriteFrameState *init_context, void *render);

/* Directional frame entries; the full allocation extent is not inferred. */
extern u8 death_frame_set[];

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void create_parent_return_effect(void *parent_obj, s16 effect_param, s32 initial_value, s16 duration, s16 offset_x, s16 offset_y, s16 offset_z);
void spawn_parent_offset_random_motion_effect(void *parent_arg, register s16 effect_param_arg, register s32 state_value_arg, register s32 unused_arg, register s32 offset_x_arg, register s32 offset_y_arg, register s32 offset_z_arg);

#endif
