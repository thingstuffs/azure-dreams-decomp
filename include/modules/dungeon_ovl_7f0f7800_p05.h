#ifndef DUNGEON_OVL_7F0F7800_P05_H
#define DUNGEON_OVL_7F0F7800_P05_H
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"


typedef struct {
    u8 pad0[0x8C];
    s32 *field8C;
    u8 pad90[6];
    u16 field96;
    u16 field98;
    u8 pad9A;
    u8 field9B;
} T_801727CC_Obj0;

typedef struct {
    u8 pad0[0x14];
    u16 field14;
    u8 pad16[0x0E];
    u8 field24;
    u8 field25;
    u8 pad26[6];
    u8 *field2C;
} T_801727CC_Obj2;

typedef struct {
    u8 pad0[0x2A];
    s16 field2A;
    u8 pad2C[0x1A];
    u16 field46;
    u8 pad48[0x25];
    s8 field6D;
} T_801727CC_Obj3;


extern void func_80047784(T_801727CC_Obj2 *, u8, s32);
extern void func_8009C12C(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(T_801727CC_Obj3 *);
extern void func_800A56E0(s32);
extern void func_800AD594(T_801727CC_Obj3 *, s32);
extern void * D_800E3DE8[];
extern u8 D_80173FE8[];
extern u8 D_80174010[];
void func_801727CC(T_801727CC_Obj0 *action, s32 context, T_801727CC_Obj2 *sprite, T_801727CC_Obj3 *actor);
extern void func_80170F68();
#endif
