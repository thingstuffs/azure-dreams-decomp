#ifndef DUNGEON_OVL_19C6800_H
#define DUNGEON_OVL_19C6800_H
#include "modules/dungeon_native_abi.h"
struct S_800244BC_2;
void func_800244BC(void *, struct S_800244BC_2 *, s32);
void dungeonUpdateJitteredEffectPoints(void *);
s32 func_80024B20(void *);
void dungeonUpdateRandomizedIntermediatePoints(void *);
/* Texture-page and palette identifiers are 16-bit values; both signed and
 * unsigned caller views preserve the same low halfword stored by retail. */
u16 func_80066460(s32, s32, s32, s32);
u16 func_8006649C(s32, s32);
#endif
