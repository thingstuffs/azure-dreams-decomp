#ifndef TOWN_PLAYER_OBJECT_SETUP_H
#define TOWN_PLAYER_OBJECT_SETUP_H

struct SpriteFrameState;

void initialize_scaled_effect_object(void *object, void *position, struct SpriteFrameState *transform);
void initialize_unit_scale_object(void *object, void *position, struct SpriteFrameState *transform);

#endif
