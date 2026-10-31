/* Timed settings-screen color fading and cleanup when the owning object is removed. */
#include "common.h"
#include "shared/object_flags.h"
#include "frontend/settings.h"

typedef struct SignedStateView {
    s16 value;
} SignedStateView;

/* Reads the effect through SignedStateView and returns its signed 16-bit value. */
static __inline__ s16 load_signed_state(ColorEffect *effect)
{
    s16 value;

    value = effect->state;
    return value;
}

/* Cycles a timed color fade and marks the effect for removal when its owner is flagged. */
void update_settings_color_cycle(ColorEffect *effect)
{
    s16 state;
    s32 initial_state;
    s32 timer;
    u16 old_timer;
    SettingsColorEffectOwnerBody *owner;

    old_timer = effect->timer;
    owner = effect->owner;
    state = load_signed_state(effect);
    initial_state = (u16)effect->state;
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
        ((u16 *)effect)[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
