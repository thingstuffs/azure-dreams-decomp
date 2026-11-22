#ifndef INCLUDE_TOWN_MENU_TARGET_ADJUSTMENT_H
#define INCLUDE_TOWN_MENU_TARGET_ADJUSTMENT_H
struct SpriteFrameState;

#include "common.h"
#include "shared/entity.h"

struct DoorProjectionChild;
struct ObjectPosition;
void decrement_sprite_angle_y(struct DoorProjectionChild *unused_child, struct ObjectPosition *unused_position, struct SpriteFrameState *target);

#endif
