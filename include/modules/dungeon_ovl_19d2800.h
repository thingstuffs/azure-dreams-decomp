#ifndef DUNGEON_OVL_19D2800_H
#define DUNGEON_OVL_19D2800_H
#include "modules/dungeon_native_abi.h"

void dungeonUpdateAnimatedTargetEffect(void *);
void func_80024B48(void *);
s32 dungeonDrawFadingRadialEffectGrid(void *);

struct SpriteEffect;
s32 dungeonDrawLinkedSpriteEffectQuads(struct SpriteEffect *);
struct EffectRecord;
struct SpriteEntry;
void dungeonBuildAndQueueInterpolatedVerticalQuadsAroundFivePerimeterPoints(struct EffectRecord *, void *, struct SpriteEntry *);

#endif
