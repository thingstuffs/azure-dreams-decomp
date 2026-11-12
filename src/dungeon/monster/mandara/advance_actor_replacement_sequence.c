#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/monster/mandara.h"


/* Fade the primitive as the effect countdown expires, then set completion flags. */
void advance_actor_replacement_sequence(RotateAndRestoreActorStateBody *effect, s32 unused, SpriteFrameState *primitive)
{
    s16 ticks_left;

    ticks_left = effect->ticks_remaining;
    if (ticks_left < 16) {
        s8 shade = ticks_left * 3;

        primitive->color.c.b = shade;
        primitive->color.c.g = shade;
        primitive->color.c.r = shade;
    } else {
        primitive->color.word = 0x808080;
    }
    ticks_left = (u16)effect->ticks_remaining - 1;
    effect->ticks_remaining = ticks_left;
    if (ticks_left <= 0) {
        *(u16 *)((u8 *)effect - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
