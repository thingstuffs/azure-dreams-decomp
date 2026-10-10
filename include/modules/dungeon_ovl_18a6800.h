#ifndef DUNGEON_OVL_18A6800_H
#define DUNGEON_OVL_18A6800_H
#include "common.h"
#include "m2c_compat.h"
#include "modules/dungeon_native_abi.h"
struct FadeEndpoints; struct FadeSettings;
struct S_8002569C_2; struct S_80025160_1;
struct Actor; struct Motion; struct EffectColor;
ObjectNodeHeader *func_80024DE8(struct FadeEndpoints *, struct FadeSettings *);
void *func_8002569C(struct S_8002569C_2 *, s16, s16, s16, s32);
void func_80025160(void *, s32, struct S_80025160_1 *);
s32 func_80025340(void *, void *, void *);
void func_80025868(struct Actor *, struct Motion *, struct EffectColor *);
void func_80025A58(void *, void *, void *);
s32 func_80025E4C(void *);
#include "modules/dungeon_native_abi.h"
#include "m2c_compat.h"
extern u16 D_80026324[];
extern u16 D_80026326;
extern s16 D_80026328[];
extern s16 D_8002632A;
extern u8 D_80026470[];
extern u8 D_80026474[];
extern u8 D_80026478[];

void *func_80024C80();
void func_80024804();
s32 func_80024EF4(void);

s32 func_80066460(s32, s32, s32, s32);
void func_8006658C();
void func_80067F20(void *, s32, s32, u16, s32);

#endif
