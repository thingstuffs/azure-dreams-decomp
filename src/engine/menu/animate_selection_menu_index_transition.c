#include "common.h"
#include "engine/effect.h"
#include "engine/menu.h"
#include "slus.h"

/*
 * Reorders and interpolates the menu entries, then installs the idle callback when the previous
 * counter value reaches the limit.
 */
void animate_selection_menu_index_transition(AnimatedSelectionMenuBody *state) {
    reorder_selection_menu_entries(state);
    if (state->transition_tick++ >= state->transition_frames) {
        state->animate = noop_selection_menu_animation_idle;
    }
}
