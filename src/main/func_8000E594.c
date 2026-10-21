#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"










/* Dispatches a nonzero handler result through the current mode's callback table. */
s32 card_boot_dispatch_event_callbacks(void)
{
    CallbackWork callback_sets;
    card_event_callback_fn *first_callbacks;
    s32 mode;
    s32 result;

    callback_sets.first = card_software_handlers;
    callback_sets.second = D_80020048;
    result = 0;
    mode = card_event_backend_mode[0];
    first_callbacks = callback_sets.first.value;
    if (mode == 0) {
        result = card_boot_poll_software_events();
        if (result != 0) {
            result = first_callbacks[result]();
        }
    } else if (mode == 1) {
        result = card_boot_take_hardware_status();
        if (result != 0) {
            result = (*(card_event_callback_fn *)((u8 *)first_callbacks + (result * 4) + 0x18))();
        }
    }
    return result;
}
