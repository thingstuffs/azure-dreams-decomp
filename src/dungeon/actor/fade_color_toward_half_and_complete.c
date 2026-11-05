#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/actor.h"
#include "dungeon/actor/positioned_graphic_effect.h"


/* Waits, then fades the color channels toward 0x80 and flags completion. */
void fade_color_toward_half_and_complete(void *effect_arg, s32 unused, void *color_arg)
{
    SpriteFrameState *color = color_arg;
    PositionedGraphicEffectBody *effect = effect_arg;
    s16 phase;
    s32 frames_left;
    s32 intensity;

    phase = effect->phase;
    switch (phase) {
    default:
        return;

    case 0:
        frames_left = (u16)effect->frames_left - 1;
        effect->frames_left = frames_left;
        if ((frames_left << 16) <= 0) {
            effect->frames_left = 0x10;
            effect->phase = (u16)effect->phase + 1;
        }
        break;

    case 1:
        intensity = color->color.c.r;
        intensity = intensity + ((0x80 - intensity) / effect->frames_left);
        color->color.c.r = intensity;
        color->color.c.b = intensity;
        color->color.c.g = intensity;
        frames_left = (u16)effect->frames_left - 1;
        effect->frames_left = frames_left;
        if ((frames_left << 16) <= 0) {
            NODE_HEADER(effect)->flags |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;

    }
}
