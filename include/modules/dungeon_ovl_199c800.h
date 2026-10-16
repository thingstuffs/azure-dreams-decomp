#ifndef DUNGEON_OVL_199C800_H
#define DUNGEON_OVL_199C800_H
#include "modules/dungeon_native_abi.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
struct Actor;
struct Vec3;
struct Sprite;
void dungeonBuildAndEnqueueFiveTranslucentQuadsBetweenInterpolatedPoints(struct Actor *, struct Vec3 *, struct Sprite *);
void func_80024BB8(void *, void *, void *);
void dungeonUpdateRisingLandingEffect(void *, void *, void *);
#endif
