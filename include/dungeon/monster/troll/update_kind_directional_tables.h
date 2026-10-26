#ifndef DUNGEON_OVL_D28BC4_P02_H
#define DUNGEON_OVL_D28BC4_P02_H
#include "common.h"
#include "dungeon/actor.h"
#include "shared/game_work.h"

typedef struct {
    u8 pad00[0x8c];
    void *field8c;
} Obj0;

typedef struct {
    u8 pad00[0x2c];
    u8 *table2c;
} Obj2;

typedef struct {
    u8 pad00[0x1c];
    u32 flags1c;
    u8 pad20[5];
    u8 flag25;
    u8 pad26[4];
    s16 value2a;
    u8 pad2c[0x1c];
    u8 kind48;
} Obj3;

extern void func_801544BC(void *actor, s32 context, SpriteFrameState *sprite, ActorRecord *state);
extern u8 D_80157DC4[8];
extern u8 D_80157DCC[8];
extern u8 D_80157DD4[8];
extern u8 D_80157E24[8];
extern u8 D_80157E2C[8];
extern u8 D_80157E34[8];
extern u8 D_80157E54[8];
extern u8 D_80157E5C[8];
extern u8 D_80157E64[8];

extern void select_sprite_entry(void *, u8, s32);
extern void func_80047784(void *, u8, s32);
extern s32 update_actor_transform_from_parent(Obj0 *, void *, void *, void *);


void update_kind_directional_tables(Obj0 *owner, void *context, Obj2 *display_arg, Obj3 *state_arg);
#endif
