#include "common.h"
#include "shared/object_flags.h"

typedef struct S_80026FB0_0 {
    u8 pad_00[0x64];
    union { s16 s; u16 u; } unk_64;   /* accessed as both */
    s16 unk_66;
} S_80026FB0_0;   /* arg0 in fade_color_toward_half_and_complete */

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
    S_80026FB0_0 *effect = effect_arg;
    s16 phase;
    s32 frames_left;
    s32 intensity;

    phase = effect->unk_64.s;
    switch (phase) {
    default:
        return;

    case 0:
        frames_left = (u16)effect->unk_66 - 1;
        effect->unk_66 = frames_left;
        if ((frames_left << 16) <= 0) {
            effect->unk_66 = 0x10;
            effect->unk_64.u += 1;
        }
        break;

    case 1:
        intensity = color->unk_0C;
        intensity = intensity + ((0x80 - intensity) / effect->unk_66);
        color->unk_0C = intensity;
        color->unk_0E = intensity;
        color->unk_0D = intensity;
        frames_left = (u16)effect->unk_66 - 1;
        effect->unk_66 = frames_left;
        if ((frames_left << 16) <= 0) {
            (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;

    }
}
