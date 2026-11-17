#ifndef DUNGEON_OVL_D2EBC4_P02_H
#define DUNGEON_OVL_D2EBC4_P02_H
#include "common.h"
#include "dungeon/actor.h"
#include "shared/game_work.h"

extern void func_8014E4BC(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *state);
extern u8 D_80151DC4[8];
extern u8 D_80151DCC[8];
extern u8 D_80151DD4[8];
extern u8 D_80151E24[8];
extern u8 D_80151E2C[8];
extern u8 D_80151E34[8];
extern u8 D_80151E54[8];
extern u8 D_80151E5C[8];
extern u8 D_80151E64[8];

extern void select_sprite_entry(void *, u8, s32);
extern void func_80047784(void *, u8, s32);
extern s32 update_actor_transform_from_parent(void *, void *, void *, void *);


void select_directional_object_effect_tables(ActorRecord *owner, ObjectPosition *context, SpriteFrameState *display_arg, ActorRecord *state_arg);
#endif
