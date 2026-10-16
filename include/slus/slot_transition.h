#ifndef SLUS_SLOT_TRANSITION_H
#define SLUS_SLOT_TRANSITION_H
#include "common.h"
typedef struct { s32 field0; s32 pad4; s32 pad8; } SlotTransitionWords3;
#include "shared/transition_slots.h"
#include "shared/runtime_dispatch.h"
extern volatile s32 D_80081480;
extern volatile s32 D_8008148C;
extern s16 D_800814E8;
extern u8 D_80082E6E[];
extern void updateControllerButtonsAndTriggers(void);
extern void uploadDispatchEntryImages(s32);
extern void uploadDispatchEntryVramRows(s32);
extern void loadDispatchEntryFiles(s32);
extern s32 runDispatchEntryCallbacks(s32);
extern void sceneSavePreviousModeAndResetCallbacks(void);
extern s16 reserveRuntimeSlot(s16, s16);
extern void setScenePhaseCallback(s32);
extern void renderSceneFrameWithTiming(void);
extern void func_8003D92C(void);
void func_80041AE4(void);
void func_80041B98(void);
void func_80041BE4(void);
void func_80041C64(void);
extern s16 D_80081500;
extern void renderObjectSceneFrame(void);
void func_80043D04(void);
void func_80043DB8(void);
void func_80043E04(void);
void func_80043E60(void);
#endif
