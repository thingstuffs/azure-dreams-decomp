#include "common.h"

typedef struct EffectOwner {
    u8 pad0[0x16];
    u16 flags;
} EffectOwner;

typedef struct ColorRampEffect {
    u8 pad0[0x0C];
    EffectOwner *owner;
    s32 color;
    u8 pad14[0x0C];
    s32 selector;
    u32 active;
} ColorRampEffect;

extern u32 D_800814A0[];

/* Ramp the effect color using owner flags and active state, then propagate the owner high bit. */
void func_8008AD58(ColorRampEffect *effect)
{
    u16 flag_masks[2];
    EffectOwner *owner;
    s32 brighten;
    s32 next_color;
    u32 state_bits;
    u16 selected_flags;

    owner = effect->owner;
    flag_masks[0] = 2;
    flag_masks[1] = 1;
    brighten = 0;
    selected_flags = owner->flags;
    selected_flags &= *(u16 *)((unsigned long)(effect->selector * 2)
                      + (unsigned long)flag_masks);

    if (selected_flags != 0) {
        state_bits = effect->active;
        switch (state_bits) {
        case 0:
            brighten = 0;
            break;
        default:
            brighten = 1;
            break;
        }
        goto update_color;
    }

    if (effect->active == 0) {
        brighten = 1;
    }
update_color:
    if (brighten != 0) {
        next_color = effect->color + 0x101010;
        effect->color = next_color;
        if (next_color > 0x808080) {
            next_color = 0x808080;
            effect->color = next_color;
            goto propagate_flag;
        }
    } else {
        effect->color -= 0x101010;
        if (effect->color <= 0x30302F) {
            effect->color = 0x303030;
        }
    }

propagate_flag:
    state_bits = (s16)owner->flags;
    if ((state_bits & 0x8000) != 0) {
        ((u16 *)effect)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
