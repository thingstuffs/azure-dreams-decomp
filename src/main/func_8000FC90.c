#include "common.h"

extern void card_boot_bind_message_dialog_record(s32 record, s32 value_14, s32 entry_index, s32 value_0c, s32 value_20);
extern void card_boot_initialize_message_render_templates(s32 entity, s32 primary_data, s32 secondary_data);
extern void card_boot_initialize_dialog_packets_and_display(s32 record);

/* Sets record fields, processes its embedded data, and updates the record. */
void card_boot_initialize_message_dialog_layout(s32 record, s32 value_14, s32 entry_index, s32 value_0c, s32 value_20) {
    card_boot_bind_message_dialog_record(record, value_14, entry_index, value_0c, value_20);
    card_boot_initialize_message_render_templates(record + 0x8BC, record + 0x894, record + 0x8A4);
    card_boot_initialize_dialog_packets_and_display(record);
}
