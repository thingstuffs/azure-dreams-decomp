#include "common.h"
#include "town/shop/item_menu_cursor_transition_g00601.h"

/* Invoke the display payload's selection-delay callback when present. */
void invoke_item_menu_node_callback(ItemMenuTransition *state) {
    if (state->callback != 0) {
        state->callback(state);
    }
}
