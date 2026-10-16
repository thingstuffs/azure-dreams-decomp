#ifndef DUNGEON_OVL_1972800_H
#define DUNGEON_OVL_1972800_H
#include "modules/dungeon_native_abi.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dir_step.h"
void func_8002401C(void *, void *);
void updateSpiralingEffectGrowthAndFade(void *, void *, void *);
void func_80024654(void *, s16, s16, void *, s32);
void processEffectModesAndCompletion(void *);
void allocateAndInitializeEffectObject(s32, s16, s16, s32);
void dungeonDrawTexturedEllipse(s32, void *, u16, u16);
void dungeonCreateTimedModelEffect(s32, void *, s32, s32);
s32 func_800644B8(s32);
s32 func_80064584(s32);
extern u8 D_800DF334[];
extern u8 D_800CEEFC[];
extern u8 D_80024980[];
extern u8 D_80024998[];
extern s16 D_800249A4;
extern u16 D_800249A6[5];
#endif
