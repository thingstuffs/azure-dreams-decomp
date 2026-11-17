#ifndef DUNGEON_OVL_D16BC4_P02_H
#define DUNGEON_OVL_D16BC4_P02_H
#include "common.h"
#include "dungeon/actor.h"
#include "shared/game_work.h"

extern void func_801664BC(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *state);
extern u8 D_80169DC4[8];
extern u8 D_80169DCC[8];
extern u8 D_80169DD4[8];
extern u8 D_80169E24[8];
extern u8 D_80169E2C[8];
extern u8 D_80169E34[8];
extern u8 D_80169E54[8];
extern u8 D_80169E5C[8];
extern u8 D_80169E64[8];

extern void select_sprite_entry(void *, u8, s32);
extern void func_80047784(void *, u8, s32);
extern s32 update_actor_transform_from_parent(void *, void *, void *, void *);


void update_direction_table_for_entity_kinds(ActorRecord *owner, ObjectPosition *context, SpriteFrameState *sprite_arg, ActorRecord *entity_arg);
#endif
