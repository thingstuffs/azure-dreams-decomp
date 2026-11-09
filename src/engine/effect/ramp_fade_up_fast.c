#include "common.h"

#include "common.h"
#include "engine/effect.h"

// Increase the sprite's vertical scale by 0x400, clamping at 0x1000 and advancing the step when reached.
void ramp_fade_up_fast(FadeManagerBody *manager, ObjectPosition *unused, SpriteFrameState *state) {
    u32 incrementedValue;

    incrementedValue = state->scale_y;
    incrementedValue += 0x400;
    state->scale_y = incrementedValue;
    if ((incrementedValue & 0xffff) < 0x1000) {
        return;
    }
    state->scale_y = 0x1000;
    manager->step = ramp_fade_up_slow;
}
