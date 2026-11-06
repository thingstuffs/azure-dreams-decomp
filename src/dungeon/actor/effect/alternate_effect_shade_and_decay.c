#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "dungeon/actor/effect.h"
#include "dungeon/actor/alternating_shade.h"



/* Alternate the effect shade, decay its intensity, and flag expiration. */
void alternate_effect_shade_and_decay(AlternatingShadeBody *effect_arg, s32 ticks_left, SpriteFrameState *color)
{
    AlternatingShadeBody *effect = effect_arg;
    u16 frame;
    u16 intensity;
    u32 shade;
    s32 decay;

    frame = effect->frame + 1;
    effect->frame = frame;
    if (frame & 1) {
        shade = (*(u8 *)&effect->intensity);
    } else {
        shade = effect->intensity >> 3;
    }
    color->color.c.b = (s8) shade;
    color->color.c.g = (s8) shade;
    color->color.c.r = (s8) shade;
    intensity = effect->intensity;
    decay = (s16)intensity >> 4;
    effect->intensity = intensity - decay;
    ticks_left = effect->ticks_left - 1;
    effect->ticks_left = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        NODE_HEADER(effect)->flags =
            (u16)(NODE_HEADER(effect)->flags | 0x8000);
        object_flag_block.flags = (s32)(object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
