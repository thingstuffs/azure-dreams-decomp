#ifndef DUNGEON_OVL_1840800_H
#define DUNGEON_OVL_1840800_H
#include "shared/dungeon_height_query.h"
#include "shared/dungeon_trail_views.h"
extern int abs(int);
void *func_8003FD64(s32, void *);
void func_8004491C(void *, void *);
s32 func_80069EF8(void);
void func_8009CE1C(void *, s32, s32, s32, s32, void *, s32);
void *dungeonScanMonsterAlongHeading(void *, s32, s32, s32, s32);
s32 dungeonGetDefinitionEntryByte13(s16);
s32 dungeonCheckEnabledNeighborHeight(s32, s32, s16, u32, s32);
void func_800A56E0(s32);
s32 func_800644B8(s32);
s32 func_80064584(s32);
void dungeonTransformRotatedVertices(LocalPacket *);
s32 func_80065420(void *, s16 *, void *, void *);
u16 func_80066460(s32, s32, s32, s32);
void func_80066640(void *, s32);
void func_80066690(void *);
void func_80067F20(void *, s32, s32, s32, s32);
void func_80024020(void *, TrailMotion *, void *);
void dungeonUpdateFlickeringEffectVertices(DungeonObj *);
s32 func_80024A1C(void *);
#endif
