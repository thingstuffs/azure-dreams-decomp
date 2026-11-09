#include "common.h"
#include "engine/effect.h"
#include "engine/script/vm.h"

/* Increases the sprite's horizontal scale by 0x200, clamps it to 0x1000, and switches steps at the limit. */
void ramp_fade_up_slow(FadeManagerBody *manager, ObjectPosition *unused, SpriteFrameState *state) {
    state->scale_x += 0x200;
    if (state->scale_x < 0x1000) {
        return;
    }
    state->scale_x = 0x1000;
    manager->step = noop_after_fade_ramp_completion;
}
