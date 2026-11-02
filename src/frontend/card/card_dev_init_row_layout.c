#include "frontend/card/command_panel.h"
#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"










/* Initializes values in four groups of four linked records. */
void card_dev_init_row_layout(void *record_groups, s32 unused_row_y, s32 unused_lower_y, s32 unused_row) {
    CardDevCommandPanel *panel = record_groups;
    s32 slot_index;


    for (slot_index = 0; slot_index < 4; slot_index++) {
        panel->middle[slot_index]->block->fields.x = 0x24;
        panel->middle[slot_index]->block->color.r = 0x68;
        panel->middle[slot_index]->block->color.g = 0x68;
        panel->middle[slot_index]->block->color.b = 0x60;
        panel->left[slot_index]->block->fields.x = 9;
        panel->right[slot_index]->block->fields.x = 0x42;
        panel->lower[slot_index]->block->fields.x = 0x8F;
    }
}
