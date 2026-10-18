#ifndef DUNGEON_OVL_199C800_H
#define DUNGEON_OVL_199C800_H
#include "modules/dungeon_native_abi.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
struct Actor;
struct Vec3;
struct Sprite;
void build_and_enqueue_five_translucent_quads_between_interpolated_points(struct Actor *, struct Vec3 *, struct Sprite *);
void func_80024BB8(void *, void *, void *);
void update_rising_landing_effect(void *, void *, void *);
#endif
