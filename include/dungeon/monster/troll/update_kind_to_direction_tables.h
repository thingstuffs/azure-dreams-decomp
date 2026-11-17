#ifndef DUNGEON_OVL_D1CBC4_P02_H
#define DUNGEON_OVL_D1CBC4_P02_H
#include "common.h"
#include "dungeon/actor.h"
#include "shared/game_work.h"

extern void func_801604BC(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *state);
extern u8 D_80163DC4[8];
extern u8 D_80163DCC[8];
extern u8 D_80163DD4[8];
extern u8 D_80163E24[8];
extern u8 D_80163E2C[8];
extern u8 D_80163E34[8];
extern u8 D_80163E54[8];
extern u8 D_80163E5C[8];
extern u8 D_80163E64[8];

extern void select_sprite_entry(void *, u8, s32);
extern void func_80047784(void *, u8, s32);
extern s32 update_actor_transform_from_parent(void *, void *, void *, void *);


void update_kind_13_to_15_direction_tables(ActorRecord *owner, ObjectPosition *context, SpriteFrameState *display_arg, ActorRecord *state_arg);
#endif
