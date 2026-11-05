#include "common.h"
#include "shared/object_flags.h"
#include "town/minigame.h"

typedef struct S_80022514_0 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    s32 unk_08;
} S_80022514_0;   /* arg0 in advance_timed_color_fade */


/* Advances a timed color fade and sets completion flags at the final threshold. */
void advance_timed_color_fade(void *effect_arg) {
    S_80022514_0 *effect = effect_arg;
    s32 phase;
    s32 frames_left;
    u16 phase_value;
    s32 color;

    phase = ((s16)effect->unk_00);
    phase_value = effect->unk_00;
    frames_left = effect->unk_02 - 1;
    effect->unk_02 = frames_left;
    switch (phase) {
    case 0:
        effect->unk_08 += 0x40404;
        if (((s16)effect->unk_02) < 0) {
            effect->unk_02 = 0x10E;
            effect->unk_00++;
        }
        break;
    case 1:
        if ((s16)frames_left < 0) {
            effect->unk_00 = phase_value + 1;
        }
        break;
    case 2:
        color = effect->unk_08 + 0xFFF7F7F8;
        effect->unk_08 = color;
        if (color <= 0x80808) {
            (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }
}
