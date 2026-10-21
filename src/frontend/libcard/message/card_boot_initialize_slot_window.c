#include "common.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"

void card_boot_initialize_slot_window_frame();      /* extern */

/* Configures the record, processes its embedded data, and updates the record. */
void card_boot_initialize_slot_window(s32 record, s32 setup_value, s32 processing_value) {
    card_boot_set_slot_index_and_owner(record, setup_value, processing_value);
    card_boot_initialize_slot_window_frame(record + 0x24C, record + 0x224, record + 0x234, processing_value);
    card_boot_populate_slot_window_display((s32 *)(record));
}
