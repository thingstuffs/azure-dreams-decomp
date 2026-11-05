#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/actor.h"
#include "dungeon/actor/positioned_graphic_effect.h"

typedef struct S_80026FB0_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80026FB0_1;   /* arg2 in fade_color_toward_half_and_complete */


/* Waits, then fades the color channels toward 0x80 and flags completion. */
void fade_color_toward_half_and_complete(void *effect_arg, s32 unused, void *color_arg)
{
    S_80026FB0_1 *color = color_arg;
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
        intensity = color->unk_0C;
        intensity = intensity + ((0x80 - intensity) / effect->frames_left);
        color->unk_0C = intensity;
        color->unk_0E = intensity;
        color->unk_0D = intensity;
        frames_left = (u16)effect->frames_left - 1;
        effect->frames_left = frames_left;
        if ((frames_left << 16) <= 0) {
            NODE_HEADER(effect)->flags |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;

    }
}
