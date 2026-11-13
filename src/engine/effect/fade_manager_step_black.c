#include "common.h"

#include "engine/effect.h"
#include "engine/resource.h"

/* Fades the sprite to black and clears the manager's step when the timer expires. */
void fade_manager_step_black(
    FadeManagerBody *manager,
    ObjectPosition *unused_state,
    SpriteFrameState *fade_state
    ) {
    s32 intensity;
    u16 timer;

    intensity = fade_state->color.c.b - 0x10;
    timer = fade_state->scale_x - 0x200;
    fade_state->scale_x = timer;

    if (intensity < 0) {
        intensity = 0;
    }

    fade_state->color.c.b = intensity;
    fade_state->color.c.g = intensity;
    fade_state->color.c.r = intensity;

    if ((s16)fade_state->scale_x <= 0) {
        fade_state->scale_y = 0;
        manager->step = 0;
        clear_fade_has_source(manager, fade_state);
    }
}
