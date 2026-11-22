#include "common.h"
#include "town/menu.h"
#include "town/menu/motion.h"

/* Initialize state values and install the next handler. */
void initialize_animated_menu_ring(MenuRingAnimationState *state) {
    state->delta_a = 0xC0;
    state->delta_b = 0x60;
    state->timer = 0x14;
    state->radius_a = 0;
    state->radius_b = 0;
    state->update = &tick_menu_motion_fade;
}
