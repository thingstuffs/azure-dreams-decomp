#include "common.h"

#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard/message.h"
#include "frontend/libcard/resource.h"
#include "frontend/libcard/save_menu.h"
#include "frontend/libcard.h"
#include "shared/object_node.h"

/* Save menu: create the window of the next of the five slots each frame; on a metadata failure show
 * the load failure notice, and after the fifth slot hand the menu to slot input. */
void create_next_save_slot_window(CardSaveMenuBody *menu) {
    s32 slot;

    slot = menu->state;
    if (slot < 5) {
        if (card_boot_load_slot_metadata(slot) != 0) {
            menu->slots[slot] = card_boot_create_slot_window(NODE_HEADER(menu), slot);
            menu->state = menu->state + 1;
        } else {
            menu->saved_callback = card_boot_return_from_save_menu;
            card_boot_show_load_failure_notice(NODE_HEADER(menu));
            NODE_HEADER(menu)->update_callback = card_boot_restore_save_slot_callback;
        }
    }
    if (slot == 5) {
        NODE_HEADER(menu)->update_callback = enter_save_slot_menu_input;
    }
}
