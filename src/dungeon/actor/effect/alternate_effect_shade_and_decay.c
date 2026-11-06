#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "dungeon/actor/effect.h"



typedef struct S_80026E3C_0 {
    u8 pad_00[0x66];
    u16 unk_66;
    u16 unk_68;
    union { u8 u8; u16 u16; } unk_6A;   /* accessed as both */
} S_80026E3C_0;   /* arg0 in alternate_effect_shade_and_decay */


/* Alternate the effect shade, decay its intensity, and flag expiration. */
void alternate_effect_shade_and_decay(void *effect_arg, s32 ticks_left, SpriteFrameState *color)
{
    S_80026E3C_0 *effect = effect_arg;
    u16 frame;
    u16 intensity;
    u32 shade;
    s32 decay;

    frame = effect->unk_68 + 1;
    effect->unk_68 = frame;
    if (frame & 1) {
        shade = effect->unk_6A.u8;
    } else {
        shade = effect->unk_6A.u16 >> 3;
    }
    color->color.c.b = (s8) shade;
    color->color.c.g = (s8) shade;
    color->color.c.r = (s8) shade;
    intensity = effect->unk_6A.u16;
    decay = (s16)intensity >> 4;
    effect->unk_6A.u16 = intensity - decay;
    ticks_left = effect->unk_66 - 1;
    effect->unk_66 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        NODE_HEADER(effect)->flags =
            (u16)(NODE_HEADER(effect)->flags | 0x8000);
        object_flag_block.flags = (s32)(object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
