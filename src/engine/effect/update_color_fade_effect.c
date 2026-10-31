#include "common.h"

#include "common.h"
#include "engine/effect.h"
#include "slus/data.h"

typedef struct S_80051F58_a2 {
    u8 pad00[0xC];
    u8 unk0C;
    u8 unk0D;
    u8 unk0E;
} S_80051F58_a2;

/* Fade the color in, hold it, then fade it out and mark the effect complete. */
void update_color_fade_effect(CdCueEffectBody *effect, void *unused_1, S_80051F58_a2 *color, void *unused_3)
{
    u16 timer = effect->timer.u;
    u16 advance_state;
    int next_timer;
    int state = effect->state.s;
    u16 state_bits = effect->state.s;

    next_timer = timer + 1;
    effect->timer.u = next_timer;
    switch (state) {
    case 0:
        if (effect->completion == 0) {
            return;
        }
        effect->completion = 0;
        advance_state = effect->state.s;
        effect->timer.u = 0;
        effect->state.s = advance_state + 1;
        return;
    case 1:
    {
        u8 intensity = color->unk0E + 2;
        color->unk0E = intensity;
        color->unk0D = intensity;
        color->unk0C = intensity;
    }
        if ((s16)effect->timer.u < 0x40) {
            return;
        }
        advance_state = effect->state.s;
        effect->timer.u = 0;
        effect->state.s = advance_state + 1;
        return;
    case 2:
        if ((s16)next_timer < 0x100) {
            return;
        }
        {
            u16 next_state = state_bits + 1;
            effect->state.s = next_state;
        }
        effect->timer.u = 0;
        return;
    case 3:
    {
        u8 intensity = color->unk0E - 2;
        color->unk0E = intensity;
        color->unk0D = intensity;
        color->unk0C = intensity;
    }
        if ((s16)effect->timer.u < 0x40) {
            return;
        }
        break;
    default:
        color->unk0E = 0;
        color->unk0D = 0;
        color->unk0C = 0;
        break;
    }
    effect->owner.color->status = 0;
    effect->owner.color->count += 1;
    *((u16 *)effect - 1) |= 0x8000;
    D_800814A0_abs |= 0x8000;
}
