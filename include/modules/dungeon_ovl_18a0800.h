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
s32 func_800CEEFC(void *,s32,void *);
void func_80024050(u8 *,u8 *,u8 *);
void func_80024728(void *,void *);
void *func_80024968(s32,struct S_80024968_2 *,s16,s32);
void func_80024A00(void *,s32,void *);
void *func_80024A98(struct S_80024A98_2 *);
void func_80024B98(void *,void *,void *);
void *func_80024D90(void *,s16);
void func_80024EE0(void *,void *,void *);
void *func_80024FD8(struct S_80024FD8_2 *,s16,s16);
void func_800250E8(void *,struct S_800250E8_0 *,void *);
s32 func_800252E0(void *,void *,void *);
s32 func_800254C4(void *,s16,s16,s16);
void func_800255DC(u16 *,s32,EffectColor *);
void *func_80025654(struct S_80025654_2 *,struct S_80025654_4 *);
void func_80025760(s32,u8,void *);
void *func_8003FC64(s32);
s32 func_8003DB94(void *,void *,s32);
s32 func_8003DF74(void *,void *,s16 *,s32);
s32 func_800644B8(s32);
s32 func_80064584(s32);
s32 rand(void);
#endif
