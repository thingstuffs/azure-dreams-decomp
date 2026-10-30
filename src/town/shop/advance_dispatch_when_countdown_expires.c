#include "common.h"
#include "town/shop.h"

/* Decrement the countdown and select the next dispatch when it expires. */
void advance_dispatch_when_countdown_expires(GridMenuObject *state_data) {
    u8 *state = (u8 *)state_data;
    void *handler;

    if (--state_data->repeat_ticks == 0) {
        if (state_data->dispatch_mode != 0) {
            handler = handle_twin_shop_input;
        } else {
            pass_indexed_entry_address(state_data);
            handler = handle_grid_menu_input;
        }
        *(void **)(state - 0x10) = handler;
    }
}
