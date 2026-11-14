#include "common.h"
#include "town/shop.h"
#include "shared/object_node.h"

/* Decrement the countdown and select the next dispatch when it expires. */
void advance_dispatch_when_countdown_expires(GridMenuObject *state_data) {
    void *handler;

    if (--state_data->repeat_ticks == 0) {
        if (state_data->dispatch_mode != 0) {
            handler = handle_twin_shop_input;
        } else {
            refresh_selected_item_name_with_fallback(state_data);
            handler = handle_grid_menu_input;
        }
        NODE_HEADER(state_data)->update_callback = handler;
    }
}
