#include "common.h"
#include "shared/object_flags.h"

typedef struct EffectOwner {
    u8 pad0[0x16];
    s16 flags;
} EffectOwner;

typedef struct ColorEffect {
    s16 state;
    u16 timer;
    u8 pad4[8];
    EffectOwner *owner;
    u32 color;
    u8 pad14[8];
    u16 flags;
} ColorEffect;

typedef struct SignedStateView {
    s16 value;
} SignedStateView;

static __inline__ s16 load_signed_state(ColorEffect *effect)
{
    s16 value;

    value = ((SignedStateView *)effect)->value;
    return value;
}

void func_7FDD3F8C(ColorEffect *effect)
{
    s16 state;
    s32 initial_state;
    s32 timer;
    u16 old_timer;
    EffectOwner *owner;

    old_timer = effect->timer;
    owner = effect->owner;
    state = load_signed_state(effect);
    initial_state = (u16)*(s16 *)effect;
    timer = old_timer - 1;
    effect->timer = timer;

    switch (state) {
    case 0:
        if ((s16)timer <= 0) {
            effect->color = 0xC0C0C0;
            effect->flags |= 1;
            effect->state++;
        }
        break;
    case 1:
        effect->color -= 0x101010;
        if (effect->color == 0) {
            effect->timer = 60;
            effect->state++;
        }
        break;
    case 2:
        if ((s16)timer <= 0) {
            effect->state = initial_state + 1;
        }
        break;
    case 3:
        effect->color += 0x101010;
        if (effect->color == 0xC0C0C0) {
            effect->color = 0x808080;
            effect->timer = 90;
            effect->state = 0;
            effect->flags &= 0xFFFE;
        }
        break;
    }

    if ((owner->flags & 0x8000) != 0) {
        ((u16 *)effect)[-1] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
