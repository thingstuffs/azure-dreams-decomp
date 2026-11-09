/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/object_flags.h"
#include "town.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"

/* Dims all three color channels and shrinks the effect, marking it for removal when brightness runs out. */
void fade_effect_and_mark_cleanup(void *record, s32 unused, void *effect) {
    SpriteFrameState *sprite = effect;
    s32 intensity;
    u16 size;

    intensity = sprite->color.c.b;
    intensity -= 0x10;
    if (intensity < 0) {
        NODE_HEADER(record)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    sprite->color.c.b = intensity;
    sprite->color.c.g = intensity;
    sprite->color.c.r = intensity;
    size = sprite->offset_x - 0x100;
    sprite->offset_x = size;
    sprite->scale_y = size;
    sprite->scale_x = size;
}
