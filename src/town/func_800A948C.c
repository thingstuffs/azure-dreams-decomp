/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "town.h"
#include "shared/object_node.h"

/* Dims all three color channels and shrinks the effect, marking it for removal when brightness runs out. */
void fade_effect_and_mark_cleanup(void *record, s32 unused, SpriteFrameState *effect) {
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
    size = effect->offset_x - 0x100;
    effect->offset_x = size;
    effect->scale_y = size;
    effect->scale_x = size;
}
