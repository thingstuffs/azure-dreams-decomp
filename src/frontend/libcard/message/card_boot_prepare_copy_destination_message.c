#include "common.h"
#include "frontend/libcard/state.h"

typedef struct S_800254E4_0_pre {
    u8 * unk_00;
    u8 pad_04[0xC];
} S_800254E4_0_pre;   /* the 0x10 bytes before base in card_boot_prepare_copy_destination_message, addressed as base[-1] */

typedef struct S_800254E4_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0x8];
    u8 * unk_34;
} S_800254E4_0;   /* base in card_boot_prepare_copy_destination_message */

typedef struct TableEntry {
    s32 value;
    u8 pad[0x7C];
} TableEntry;

#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"

extern TableEntry card_save_slot_metadata[];

/* Selects a record update based on its table entry and status and assigns data pointers. */
void card_boot_prepare_copy_destination_message(void *context)
{
    u8 *record;
    s32 table_index;
    s32 status;

    record = context;
    table_index = ((S_800254E4_0 *)record)->unk_28;
    context = record - 0x20;

    if (card_save_slot_metadata[table_index].value == 0) {
        status = card_boot_get_remaining_block_summary();
        context = 0;
        context = record - 0x20;
        if (status < 3) {
            ((S_800254E4_0 *)record)->unk_34 = card_boot_resume_menu_after_slot_refresh;
            card_boot_show_insufficient_space_card_advice(context);
        } else {
            card_boot_enter_copying_progress(record);
            return;
        }
    } else {
        ((S_800254E4_0 *)record)->unk_34 = card_boot_resume_menu_after_slot_refresh;
        card_boot_show_overwrite_protected_notice(context);
    }

    ((S_800254E4_0_pre *)record)[-1].unk_00 = card_boot_poll_status_and_dismiss_dialog;
}
