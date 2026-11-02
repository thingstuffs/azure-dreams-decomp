#include "shared/object_node.h"
#include "common.h"
#include "shared/widget_views.h"
#include "m2c_compat.h"

#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"
#include "frontend/libcard/state.h"

/* Update the record and switch its table when the status reaches four. */
void card_boot_poll_status_and_dismiss_dialog(Object_800128C8 *record_data) {
    card_boot_restore_saved_selection_callback(record_data);
    if (card_boot_debounce_card_status_events() >= 4) {
        card_boot_close_message_dialog(0);
        ((ObjectNodeHeader *)record_data - 1)->update_callback = build_install;
    }
}
