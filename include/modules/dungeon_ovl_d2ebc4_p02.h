#ifndef DUNGEON_OVL_D2EBC4_P02_H
#define DUNGEON_OVL_D2EBC4_P02_H
#include "common.h"
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

extern void func_8014E4BC();
extern u8 D_80151DC4[8];
extern u8 D_80151DCC[8];
extern u8 D_80151DD4[8];
extern u8 D_80151E24[8];
extern u8 D_80151E2C[8];
extern u8 D_80151E34[8];
extern u8 D_80151E54[8];
extern u8 D_80151E5C[8];
extern u8 D_80151E64[8];

extern void func_80047784(Obj2 *, u8, s32);
extern s32 update_actor_transform_from_parent(Obj0 *, void *, Obj2 *, Obj3 *);
extern s32 check_actor_floor_trap(Obj2 *, Obj3 *);

void select_directional_object_effect_tables(Obj0 *owner, void *context, Obj2 *render_arg, Obj3 *state_arg);
#endif
