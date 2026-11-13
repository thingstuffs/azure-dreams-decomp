#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"

/* Releases a three-row panel's text and flags its node and the object list for removal, when the panel exists. */
void card_boot_destroy_three_row_panel(ObjectNodeHeader *record) {
    void *record_data;

    if (record != 0) {
        record_data = record + 1;
        card_boot_release_three_row_panel_text(record_data);
        *(u16 *) ((s8 *) record_data - 2) = *(u16 *) ((s8 *) record_data - 2) | NODE_REMOVE;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
