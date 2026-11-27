#ifndef SLUS_GP_SHARED_81510_H
#define SLUS_GP_SHARED_81510_H
#include "common.h"
typedef struct Entry Entry;
struct ObjectPosition;
struct SpriteFrameState;
void project_sprite_commands(void *context, struct ObjectPosition *position, struct SpriteFrameState *sprite, s16 depth_bias);
#endif
