#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "town/player/effect.h"



/* Fade and enlarge the effect, marking it finished when its intensity falls below zero. */
void fade_and_grow_effect(void *record, s32 unused, SpriteFrameState *effect) {
    s32 intensity;
    u16 size;

    intensity = effect->color.c.b;
    intensity -= 0x10;
    if (intensity < 0) {
        NODE_HEADER(record)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    effect->color.c.b = intensity;
    effect->color.c.g = intensity;
    effect->color.c.r = intensity;
    size = effect->offset_x + 0x100;
    effect->offset_x = size;
    effect->scale_y = size;
    effect->scale_x = size;
}
