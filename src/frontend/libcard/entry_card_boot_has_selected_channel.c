#include "common.h"
#include "m2c_compat.h"

#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard.h"

/* Store the supplied field values and capture the helper result. */
void card_boot_init_channel_record(CardChooserBody *record, ObjectNodeHeader *request, s32 value_00) {
    record->request = request;
    record->mode = value_00;
    record->selected_channel = card_boot_has_selected_channel();
}
