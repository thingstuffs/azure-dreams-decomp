#include "common.h"

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
    value++;
    value--;
    return value;
}

extern u32 D_800814A0[];
extern void func_7008AFF4(s32 timer, ColorEffect *effect, s32 initial_state,
                          ...);

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

    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        func_7008AFF4(timer, effect, initial_state, owner);
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    func_7008AFF4(timer, effect, initial_state, owner);
    return;

state_0:
    if ((s16)timer > 0) {
        goto shared_tail;
    }
    effect->color = 0xC0C0C0;
    effect->flags |= 1;
    effect->state++;
    func_7008AFF4(timer, effect, initial_state, owner);
    return;

state_1:
    effect->color -= 0x101010;
    if (effect->color == 0) {
        effect->timer = 60;
        effect->state++;
        func_7008AFF4(timer, effect, initial_state);
        return;
    }
    goto shared_tail;

state_2:
    if ((s16)timer <= 0) {
        effect->state = initial_state + 1;
        func_7008AFF4(timer, effect, initial_state, owner);
        return;
    }
    goto shared_tail;

state_3:
    effect->color += 0x101010;
    if (effect->color != 0xC0C0C0) {
        goto shared_tail;
    }
    effect->color = 0x808080;
    effect->timer = 90;
    effect->state = 0;
    effect->flags &= 0xFFFE;

shared_tail:
    if ((owner->flags & 0x8000) != 0) {
        ((u16 *)effect)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
