#ifndef DUNGEON_OVL_19C6800_H
#define DUNGEON_OVL_19C6800_H
#include "modules/dungeon_native_abi.h"
struct S_800244BC_2;
void func_800244BC(void *, struct S_800244BC_2 *, s32);
struct JitteredBoltSegmentBody;
void update_jittered_effect_points(struct JitteredBoltSegmentBody *);
s32 update_segment(void *);
struct IntermediatePointEffectBody;
void update_randomized_intermediate_points(struct IntermediatePointEffectBody *);
/* Texture-page and palette identifiers are 16-bit values; both signed and
 * unsigned caller views preserve the same low halfword stored by retail. */
u16 GetTPage(s32, s32, s32, s32);
u16 GetClut(s32, s32);
#endif
