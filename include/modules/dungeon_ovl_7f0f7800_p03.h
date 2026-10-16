#ifndef DUNGEON_OVL_7F0F7800_P03_H
#define DUNGEON_OVL_7F0F7800_P03_H
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))



extern s32 dungeonCheckEntityRelation();
extern void func_8009A21C();
extern void func_8009A3D0();
extern s32 dungeonCheckDiagonalSideHeight();
extern s32 dungeonCheckMovementClearanceAndHeight();
extern s32 dungeonCompareMonsterNeighborValues();
extern void * dungeonFindValidMonsterNeighbor();
extern void * dungeonPlaceActorAtDirectionalNeighbor();
extern u16 dungeonGetRoundedFacingAndRoundingFlag();
extern void dungeonRebuildMonsterReachableTiles();
extern void dungeonUpdateActorProximityFlag();
extern s32 func_800A6D30();
extern void func_800A9A0C();
extern s16 func_800BCB04();
extern s32 dungeonCheckActionEligibilityUpdatesActorStateDirectionalAnimationSuccess();
extern s16 D_8006CD00[8];
extern u8 D_80082E80[];
extern s8 D_80082EA4;
void dungeonUpdateActorMovementChoosingDirectionRecordingPath(u8 *move_work, void *entry_context, u8 *position, u8 *actor);
#endif
