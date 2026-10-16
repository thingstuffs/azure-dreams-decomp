#ifndef DUNGEON_OVL_7F0F7800_P04_H
#define DUNGEON_OVL_7F0F7800_P04_H
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"



extern void func_80047784(void *, u8, s32);
extern void dungeonPrepareDirectionalAttack(void *, void *, s16, s32, s32);
extern s32 dungeonGetActorHeightDifference(s32, void *);
extern s32 dungeonPlaceActorAtDirectionalNeighbor(void *, u8, u8, s16);
extern s32 func_800A2B5C(void *);
extern s32 func_800A2CB8(void *, s32);
extern void dungeonApplyCameraOffsetAndSelectTarget(void *, s32, s32, s32);
extern u8 D_80173FB8[];
s32 dungeonCheckActionEligibilityUpdatesActorStateDirectionalAnimationSuccess(void *action_state, s32 action_id, void *sprite, EntityRec *actor);
#endif
