#include "shared/entity.h"
#ifndef DUNGEON_OVL_7F0F7800_P01_H
#define DUNGEON_OVL_7F0F7800_P01_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_trail_views.h"
#include "dungeon/actor.h"
#include "dungeon/system.h"
#include "engine/texture.h"
#include "dungeon/level.h"


typedef void (*T_80170AA4_EntityCallback)(void *, void *, void *, void *);




typedef struct T_80170AA4_S_80170AA4_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} T_80170AA4_S_80170AA4_1;   /* entity in func_80170AA4 */

   /* arg1 in func_80170AA4 */

extern void func_80042984(void *entity);
extern void advance_sprite_animation_and_textures(void *entity);
extern s32 refresh_actor_facing_and_lifecycle();
extern T_80170AA4_EntityCallback tyrant_callbacks[];
void update_entity_callbacks_directional_animation_movement_ground_contact(ActorRecord *body, TrailMotion *motion, SpriteFrameState *sprite);
void update_dungeon_actor_behavior(ActorRecord *actor_arg, ObjectPosition *context_arg, SpriteFrameState *map_object_arg, ActorRecord *actor_state_arg);
#endif
