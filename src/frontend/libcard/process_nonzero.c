#include "common.h"
#include "shared/object_flags.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"

/* Processes a nonzero record and sets its flag and the global flag to include bit 15. */
void process_nonzero(s32 record) {
    void *record_data;

    if (record != 0) {
        record_data = (void *) (record + 0x20);
        card_boot_release_three_row_panel_text(record_data);
        *(u16 *) ((s8 *) record_data - 2) = *(u16 *) ((s8 *) record_data - 2) | NODE_REMOVE;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
