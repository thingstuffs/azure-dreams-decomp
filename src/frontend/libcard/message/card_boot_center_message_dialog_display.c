#include "frontend/libcard/message_dialog.h"
#include "frontend/libcard/display_node.h"
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8002290C_arg0.h"
#include "frontend/libcard/message.h"

/* Set the linked coordinates to (160, 120) and bind the object's data. */
void card_boot_center_message_dialog_display(void *object) {
    CardMessageDialogBody *dialog = object;
    CardMenuDisplayNode *linked_state;

    linked_state = dialog->entries[5];
    linked_state->block->fields.x = 0xA0;
    linked_state->block->fields.y = 0x78;
    linked_state->payload.data = dialog->window_packets;
}
