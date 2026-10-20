#include "common.h"

void card_boot_layout_three_row_command_panel();                         /* extern */
void func_80023730(s32, s32, s32);               /* extern */
void card_dev_store_word();                            /* extern */

/* Prepares processing, processes the embedded data, and updates the record. */
void card_boot_initialize_three_row_command_panel(s32 record) {
    card_dev_store_word();
    func_80023730(record + 0x190, record + 0x168, record + 0x178);
    card_boot_layout_three_row_command_panel(record);
}
