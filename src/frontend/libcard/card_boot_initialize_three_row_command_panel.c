#include "common.h"
#include "frontend/card.h"

#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"

/* Prepares processing, processes the embedded data, and updates the record. */
void card_boot_initialize_three_row_command_panel(void *record, void *init_value) {
    card_dev_store_word(record, init_value);
    func_80023730(record + 0x190, record + 0x168, record + 0x178);
    card_boot_layout_three_row_command_panel(record);
}
