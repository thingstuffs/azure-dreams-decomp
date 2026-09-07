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
extern void func_8008ADBC();
extern void func_8008AE20();

void func_8008AD58(ColorRampEffect *effect)
{
    u16 masks[2];
    EffectOwner *owner;
    s32 active;
    s32 color;
    u32 loaded_active;
    u16 flags;

    owner = effect->owner;
    masks[0] = 2;
    masks[1] = 1;
    active = 0;
    flags = owner->flags;
    flags &= *(u16 *)((unsigned long)(effect->selector * 2)
                      + (unsigned long)masks);

    if (flags != 0) {
        loaded_active = effect->active;
        switch (loaded_active) {
        case 0:
            active = 0;
            break;
        default:
            active = 1;
            break;
        }
        func_8008ADBC(active, effect, owner);
        return;
    }

    if (effect->active == 0) {
        active = 1;
    }
    if (active != 0) {
        color = effect->color + 0x101010;
        effect->color = color;
        if (color > 0x808080) {
            color = 0x808080;
            effect->color = color;
            func_8008AE20(color, effect, owner);
            return;
        }
    } else {
        effect->color -= 0x101010;
        if (effect->color <= 0x30302F) {
            effect->color = 0x303030;
        }
    }

    loaded_active = (s16)owner->flags;
    if ((loaded_active & 0x8000) != 0) {
        ((u16 *)effect)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
