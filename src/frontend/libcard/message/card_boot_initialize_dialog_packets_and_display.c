#include "common.h"
#include "m2c_compat.h"

void card_boot_center_message_dialog_display();                         /* extern */
void *card_boot_build_paired_dialog_packets();                    /* extern */

/* Processes the embedded data and then updates the record. */
void card_boot_initialize_dialog_packets_and_display(s32 record) {
    card_boot_build_paired_dialog_packets(record + 0x24, record);
    card_boot_center_message_dialog_display(record);
}
