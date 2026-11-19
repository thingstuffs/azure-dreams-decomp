#include "common.h"
#include "frontend/card.h"

#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"

/* Prepares processing, processes the embedded data, and updates the record. */
void card_boot_init_command_panel(void *record, ObjectNodeHeader *owner) {
    CardCommandPanelBody *panel = record;

    card_dev_store_word(&panel->owner, owner);
    func_80023730(&panel->display, &panel->display_block, &panel->display_vector);
    card_boot_layout_command_panel(panel);
}
