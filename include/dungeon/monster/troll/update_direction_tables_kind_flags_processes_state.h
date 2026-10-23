#ifndef DUNGEON_OVL_D10BC4_P02_H
#define DUNGEON_OVL_D10BC4_P02_H
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

extern void func_8016C4BC();
extern u8 D_8016FDC4[8];
extern u8 D_8016FDCC[8];
extern u8 D_8016FDD4[8];
extern u8 D_8016FE24[8];
extern u8 D_8016FE2C[8];
extern u8 D_8016FE34[8];
extern u8 D_8016FE54[8];
extern u8 D_8016FE5C[8];
extern u8 D_8016FE64[8];

extern void select_sprite_entry(Obj2 *, u8, s32);
extern void func_80047784(Obj2 *, u8, s32);
extern s32 update_actor_transform_from_parent(Obj0 *, void *, Obj2 *, Obj3 *);


void update_direction_tables_kind_flags_processes_state(Obj0 *owner, void *context, Obj2 *display_arg, Obj3 *state_arg);
#endif
