#include "common.h"
#include "frontend/card/message_display.h"
#include "frontend/card.h"

/* Set the linked coordinates to (160, 120) and reference the object's embedded data. */
void center_view_on_object(CardDevDialogDisplay *dialog) {
    CardMenuDisplayNode *item = (CardMenuDisplayNode *)dialog->entries[4];

    item->block->fields.x = 0xA0;
    item->block->fields.y = 0x78;
    item->payload.data = dialog->command_buffer;
}
