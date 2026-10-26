#ifndef DUNGEON_OVL_D16BC4_P02_H
#define DUNGEON_OVL_D16BC4_P02_H
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

extern void func_801664BC(void *actor, s32 context, SpriteFrameState *sprite, ActorRecord *state);
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
extern s32 update_actor_transform_from_parent(Obj0 *, void *, void *, void *);


void update_direction_table_for_entity_kinds(Obj0 *owner, void *context, Obj2 *sprite_arg, Obj3 *entity_arg);
#endif
