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
extern void func_8003E2D8(void);
extern void func_80040FDC(s32);
extern void func_80041038(s32);
extern void func_800411FC(s32);
extern s32 func_80040F2C(s32);
extern void func_80040B88(void);
extern s16 func_8003F794(s16, s16);
extern void func_80040A88(s32);
extern void func_80041CBC(void);
extern void func_8003D92C(void);
void func_80041AE4(void);
void func_80041B98(void);
void func_80041BE4(void);
void func_80041C64(void);
extern s16 D_80081500;
extern void func_80043EB8(void);
void func_80043D04(void);
void func_80043DB8(void);
void func_80043E04(void);
void func_80043E60(void);
#endif
