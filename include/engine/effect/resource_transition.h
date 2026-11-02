#ifndef ENGINE_EFFECT_RESOURCE_TRANSITION_H
#define ENGINE_EFFECT_RESOURCE_TRANSITION_H
#include "common.h"
#include "shared/object_node.h"
/* Common readiness prefix for both resource-transition kinds. */
typedef struct ResourceTransitionBody {
    u8 pad_00[4];
    s32 callback_index;
    u8 image_ready;
    u8 data_ready;
} ResourceTransitionBody;
#endif
