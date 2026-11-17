#ifndef DUNGEON_OVL_D10BC4_P02_H
#define DUNGEON_OVL_D10BC4_P02_H
#include "common.h"
#include "dungeon/actor.h"
#include "shared/game_work.h"

extern void func_8016C4BC(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *state);
extern u8 D_8016FDC4[8];
extern u8 D_8016FDCC[8];
extern u8 D_8016FDD4[8];
extern u8 D_8016FE24[8];
extern u8 D_8016FE2C[8];
extern u8 D_8016FE34[8];
extern u8 D_8016FE54[8];
extern u8 D_8016FE5C[8];
extern u8 D_8016FE64[8];

extern void select_sprite_entry(void *, u8, s32);
extern void func_80047784(void *, u8, s32);
extern s32 update_actor_transform_from_parent(void *, void *, void *, void *);


void update_troll_kind_frames(ActorRecord *owner, ObjectPosition *context, SpriteFrameState *display_arg, ActorRecord *state_arg);
#endif
