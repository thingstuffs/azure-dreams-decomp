#ifndef TOWN_PLAYER_OBJECT_SETUP_H
#define TOWN_PLAYER_OBJECT_SETUP_H
#include "shared/town_object.h"

struct SpriteFrameState;

void initialize_scaled_effect_object(TownObjectRecord *object, void *position, struct SpriteFrameState *transform);
void initialize_unit_scale_object(TownObjectRecord *object, void *position, struct SpriteFrameState *transform);

#endif
