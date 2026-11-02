#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/effect/shade.h"
#include "shared/object_node.h"
#include "modules/dungeon_ovl_be1084.h"


/* Advance and damp effect motion, fade its colors, and flag expiration. */
void advance_damped_effect_and_expire(FadeEffect *effect, s32 *motion)
{
    s16 ticks_left;

    motion[0] += motion[3];
    motion[1] += motion[4];
    motion[2] += motion[5];
    motion[3] /= 2;
    motion[4] /= 2;
    motion[5] /= 2;

    effect->current.color.red = (effect->red * effect->remaining) /
                effect->total;
    effect->current.color.green = (effect->green * effect->remaining) /
                effect->total;
    effect->current.color.blue = (effect->blue * effect->remaining) /
                effect->total;

    ticks_left = (u16)effect->remaining - 1;
    effect->remaining = ticks_left;
    effect->output = effect->current.packed;
    if (ticks_left <= 0) {
        NODE_HEADER(effect)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
