#ifndef SLUS_SLOT_TRANSITION_H
#define SLUS_SLOT_TRANSITION_H
#include "common.h"
typedef struct { s32 field0; s32 pad4; s32 pad8; } SlotTransitionWords3;
typedef struct { s16 field0; s16 field2; s16 field4; s16 field6; } SlotTransitionSlot;
struct SlotTransitionState {
    s32 field_0; s32 field_4; u8 pad8[3]; u8 field_B;
    u8 field_C; u8 field_D; u8 pad_E[0xA]; u8 field_18;
};
extern volatile SlotTransitionWords3 D_80081480;
extern volatile SlotTransitionWords3 D_8008148C;
extern struct SlotTransitionState D_80082E60;
extern SlotTransitionSlot D_80083120[8];
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
