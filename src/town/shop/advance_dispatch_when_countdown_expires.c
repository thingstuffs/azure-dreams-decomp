#include "common.h"
#include "town/shop.h"

/* Decrement the countdown and select the next dispatch when it expires. */
void advance_dispatch_when_countdown_expires(void *state_data) {
    u8 *state = (u8 *)state_data;
    void *handler;

    if (--*(s32 *)(state + 0x14) == 0) {
        if (*(s32 *)(state + 0x1C) != 0) {
            handler = handle_twin_shop_input;
        } else {
            pass_indexed_entry_address(state);
            handler = handle_grid_menu_input;
        }
        *(void **)(state - 0x10) = handler;
    }
}
