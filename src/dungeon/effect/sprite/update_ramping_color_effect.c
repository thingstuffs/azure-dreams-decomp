#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/effect/sprite.h"

typedef struct S_818BC888_0_pre {
    u16 unk_00;
} S_818BC888_0_pre;   /* the 0x2 bytes before arg0 in update_ramping_color_effect, addressed as arg0[-1] */


typedef struct S_818BC888_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818BC888_1;




/* Advances the effect timer and updates its interpolated and cycling values. */
void update_ramping_color_effect(OffsetColorEffectBody *effect) {
    s16 phase;
    s32 cycle_value;
    s32 scaled_step;
    u16 tick;
    s32 ticks;
    u32 scaled_value;
    u32 product;
    S_818BC888_1 *owner;

    owner = effect->unk_00;
    owner->unk_14 = owner->unk_14 + 1;
    tick = effect->unk_04.u16 + 1;
    effect->unk_04.u16 = tick;
    ticks = (s16)tick;
    scaled_step = effect->unk_0A << 0xB;
    if (ticks >= 0x20) {
        product = (0x40 - ticks) * scaled_step;
        scaled_value = product >> 0x10;
    } else {
        product = ticks * scaled_step;
        scaled_value = product >> 0x10;
    }

    effect->unk_08.s = scaled_value;
    phase = effect->unk_04.s16;
    if (phase >= 0x40) {
        ((S_818BC888_0_pre *)effect)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    if (phase < 0x10) {
        effect->unk_0E.u = effect->unk_04.u8 << 3;
    } else if (phase < 0x30) {
        effect->unk_0E.u = 0x80;
    } else {
        effect->unk_0E.u = -0x80 - ((phase - 0x30) * 8);
    }

    phase = effect->unk_04.s16 % 4;
    switch (phase) {
    case 0:
        cycle_value = 0x7DCF;
        break;
    case 1:
        cycle_value = 0x7E00;
        break;
    case 2:
        cycle_value = 0x7E01;
        break;
    case 3:
        cycle_value = 0x7E02;
        break;
    default:
        return;
    }
    effect->unk_0C = cycle_value;
}
