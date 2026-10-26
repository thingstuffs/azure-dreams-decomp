#ifndef DUNGEON_MONSTER_BALOON_H
#define DUNGEON_MONSTER_BALOON_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"




void advance_actor_hop_animation(void *motion, void *position, SpriteFrameState *sprite, void *actor);



void advance_actor_animation_and_fall(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_approach_descent_return(void *action, ObjectPosition *motion, SpriteFrameState *sprite, void *actor);
void update_monster_staged_motion(void *state, ObjectPosition *motion, SpriteFrameState *monster, void *actor_ptr);

void update_actor_turn_behavior(void *motion_arg, void *actor_index_arg, SpriteFrameState *actor_arg, void *move_data_arg);

typedef struct {
    u8 pad_00[2];
    u16 x;
    u8 pad_04[2];
    u16 y;
    u8 pad_08[2];
    u16 z;
    u8 pad_0C[0xA];
    u16 height;
} BaloonTemplateAnchor;

typedef struct {
    u8 pad_00[0x2A];
    s16 facing;
} BaloonTemplateFacing;

/* Directional template constructor used by the Baloon rise effect. */
void create_directional_template_effect(void *unused, BaloonTemplateAnchor *anchor,
    SpriteFrameState *object_template, BaloonTemplateFacing *facing_source);

#endif
