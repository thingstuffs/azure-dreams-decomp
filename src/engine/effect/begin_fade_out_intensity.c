#include "common.h"

#include "common.h"
#include "engine/effect.h"
#include "engine/resource.h"

/* Prepares the manager state and installs its next callback. */
void begin_fade_out_intensity(void) {
    FadeManagerBody *manager = &fade_manager_state;
    SpriteFrameState *state = NODE_HEADER(manager)->sprite;

    if (state->color.c.r == 0x80) {
        state->color.c.b = 0x60;
        state->color.c.g = 0x60;
        state->color.c.r = 0x60;
        state->tpage_abr = 0x20;
        state->flags |= 0x1C;
    }

    fade_manager_state.step = fade_manager_step_out;
    runtime_set_destination_flag_from_source(manager, state);
}
