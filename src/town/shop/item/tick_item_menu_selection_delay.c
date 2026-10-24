#include "common.h"
#include "shared/item_menu.h"
#include "town/shop/item_menu_cursor_transition_g00601.h"

/* Animate the selection, advance its counter, and clear the callback after the delay. */
void tick_item_menu_selection_delay(ItemMenuTransition *state) {
    s32 counter;
    s32 previous_counter;

    animate_item_menu_cursor_transition(state);
    counter = state->progress;
    previous_counter = counter;
    counter = counter + 1;
    state->progress = counter;
    if (previous_counter >= state->duration) {
        state->callback = 0;
    }
}
