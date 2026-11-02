#include "common.h"
#include "frontend/libcard/interfaces.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"

/* Initialize three entries in each of the four object groups. */
void card_boot_reset_three_row_highlight(CardCommandPanelBody *panel) {
    s32 i;

    for (i = 0; i < 3; i++) {
        panel->highlight[i]->block->fields.x = 0x24;
        panel->highlight[i]->block->color.r = 0x68;
        panel->highlight[i]->block->color.g = 0x68;
        panel->highlight[i]->block->color.b = 0x60;
        panel->left[i]->block->fields.x = 9;
        panel->right[i]->block->fields.x = 0x42;
        panel->labels[i]->block->fields.x = 0x8F;
    }
}
