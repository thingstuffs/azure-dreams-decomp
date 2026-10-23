#include "common.h"
#include "shared/widget_views.h"
#include "m2c_compat.h"

#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard.h"
extern M2C_UNK D_8002593C;

/* Update the record, run the shared follow-up, and install its next table. */
void card_boot_enter_slot_selection_input(void *record_data) {
    card_boot_refresh_five_slot_selection(record_data);
    card_boot_recheck_selected_channel();
    ((CardCallbackState *)((u8 *)record_data - 0x10))->callback = &D_8002593C;
}
