#ifndef R108_BANK19_H
#define R108_BANK19_H
#include "common.h"
#include "modules/dungeon_native_abi.h"
struct S_80024968_2;
struct S_80024A98_2;
struct S_80024FD8_2;
struct S_800250E8_0;
struct S_80025654_2;
struct S_80025654_4;
typedef struct EffectColor { u8 pad[12]; u8 red,green,blue; } EffectColor;
extern u16 D_800257CE[];
extern s16 D_800257CC[];
extern u8 D_80025854[];
struct S_80045C34;
s32 func_80045C34(u8 *,s32,struct S_80045C34 *);
s32 dungeonProcessLinkedMeshStatesMode0(void *,s32,void *);
void func_80024050(u8 *,u8 *,u8 *);
void dungeonTintEffectAndAdvanceMotion(void *,void *);
void *dungeonCreateInitializedEffectObject(s32,struct S_80024968_2 *,s16,s32);
void func_80024A00(void *,s32,void *);
void *dungeonCreateRadialEffectNode(struct S_80024A98_2 *);
void func_80024B98(void *,void *,void *);
void *dungeonSpawnRingEffects(void *,s16);
void dungeonMoveAndFadeEffect(void *,void *,void *);
void *dungeonCreateEffectRenderObject(struct S_80024FD8_2 *,s16,s16);
void func_800250E8(void *,struct S_800250E8_0 *,void *);
s32 dungeonQueueProjectedPointPrimitives(void *,void *,void *);
s32 dungeonAllocateJitteredEffectNode(void *,s16,s16,s16);
void dungeonFadeEffectColorBelowEight(u16 *,s32,EffectColor *);
void *dungeonCreateEffectFromEndpoints(struct S_80025654_2 *,struct S_80025654_4 *);
void dungeonApplyIndexedEffectCondition(s32,u8,void *);
s32 func_8003DB94(void *,void *,s32);
s32 func_8003DF74(void *,void *,s16 *,s32);
s32 func_800644B8(s32);
s32 func_80064584(s32);
s32 rand(void);
#endif
