#include "frontend/libcard/paired_choice.h"
#include "common.h"
#include "shared/widget_views.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "main/data.h"
#include "frontend/libcard/message.h"


/* Set the positions and data pointers for the left and right entries. */
void card_boot_layout_left_right_labels(CardChoiceOwner *owner) {
    CardChoiceDisplayNode *left_entry;

    left_entry = owner->pointers[0];
    left_entry->block->fields.x = 0x40;
    left_entry->block->fields.y = 0x20;
    left_entry->payload.data = &D_80028418;
    left_entry = (owner->pointers[1]);
    left_entry->block->fields.x = 0xC0;
    left_entry->block->fields.y = 0x20;
    left_entry->payload.data = &D_80028430;
}
