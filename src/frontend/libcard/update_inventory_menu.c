#include "common.h"

#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard/message.h"
#include "frontend/libcard/resource.h"
#include "frontend/libcard.h"

/* Processes the current slot and selects callbacks when unavailable or all five are done. */
void update_inventory_menu(void *state_arg) {
    void *state;
    s32 slot;

    state = state_arg;
    slot = *(s32 *)((u8 *)state + 0x24);
    if (slot < 5) {
        if (card_boot_load_slot_metadata(slot) != 0) {
            *(s32 *)((u8 *)state + 4 + slot * 4) = card_boot_create_slot_window((u8 *)state - 0x20, slot);
            *(s32 *)((u8 *)state + 0x24) = *(s32 *)((u8 *)state + 0x24) + 1;
        } else {
            *(void (**)(void))((u8 *)state + 0x34) = card_boot_return_from_slot_menu;
            card_boot_show_load_failure_notice((u8 *)state - 0x20);
            *(void (**)(void))((u8 *)state - 0x10) = card_boot_restore_saved_selection_callback;
        }
    }
    if (slot == 5) {
        *(void (**)(void))((u8 *)state - 0x10) = card_boot_enter_slot_selection_input;
    }
}
