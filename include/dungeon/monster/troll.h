#ifndef DUNGEON_MONSTER_TROLL_H
#define DUNGEON_MONSTER_TROLL_H

/* Function contracts owned by src/dungeon/monster/troll/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"
s32 try_begin_troll_attack(ActorRecord *action_state, ObjectPosition *facing, SpriteFrameState *origin, ActorRecord *actor);
void begin_troll_attack(ActorRecord *action_input, ObjectPosition *x_offset_input, SpriteFrameState *position_input, ActorRecord *actor_input);
void choose_troll_move(ActorRecord *move_input, ObjectPosition *action_context, SpriteFrameState *position, ActorRecord *actor);










struct SegmentedLineState;
void draw_segmented_motion_lines(struct SegmentedLineState *state, ObjectPosition *position, SpriteFrameState *sprite, s32 depth_bias);
void advance_timed_directional_action(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity);



void advance_actor_action_and_effects(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void advance_actor_action_effects(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void advance_troll_attack_sequence(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void advance_troll_attack_animation(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *anim, ActorRecord *actor);
void advance_timed_action_and_effects(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *animation, ActorRecord *actor);
void advance_timed_action_and_play_sounds(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void spawn_growing_rotating_flash(ActorRecord *unused, ObjectPosition *position, SpriteFrameState *unused_sprite);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void create_actor_action_effect(ActorRecord *source_object, ObjectPosition *source_pos, SpriteFrameState *sprite_template, ActorRecord *actor);
void create_targeted_motion_effect(ActorRecord *body, ObjectPosition *position, SpriteFrameState *unused, ActorRecord *target);

void spawn_random_color_burst_particle(void *source, ObjectPosition *position, void *unused_sprite, void *unused_actor);

#endif
