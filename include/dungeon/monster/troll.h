#ifndef DUNGEON_MONSTER_TROLL_H
#define DUNGEON_MONSTER_TROLL_H

/* Function contracts owned by src/dungeon/monster/troll/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"
s32 check_and_prepare_actor_move(ActorRecord *action_state, ObjectPosition *facing, SpriteFrameState *origin, ActorRecord *actor);
void prepare_actor_path_movement(ActorRecord *action_input, ObjectPosition *x_offset_input, SpriteFrameState *position_input, ActorRecord *actor_input);
void select_and_advance_actor_move(ActorRecord *move_input, ObjectPosition *action_context, SpriteFrameState *position, ActorRecord *actor);










struct SegmentedLineState;
void draw_segmented_motion_lines(struct SegmentedLineState *state, ObjectPosition *position, SpriteFrameState *sprite, s32 depth_bias);
void advance_timed_directional_action(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity);



void advance_actor_action_and_effects(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void advance_actor_action_effects(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void advance_actor_timed_action_sequence_updating(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void advance_the_actor_s_action_animation_triggers_timed_effects(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *anim, ActorRecord *actor);
void advance_timed_action_and_effects(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *animation, ActorRecord *actor);
void advance_timed_action_and_play_sounds(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

#endif
