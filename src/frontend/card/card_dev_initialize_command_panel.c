#include "common.h"
#include "frontend/card.h"
#include "frontend/card/command_panel.h"
#include "frontend/card/server_imports.h"

/*
 * Devkit-server build of card_boot_init_command_panel: store the initial word, lay out the
 * panel templates at +0x1A8 from the display blocks at +0x180 / +0x190, then lay out the panel.
 */
void card_dev_initialize_command_panel(CardDevCommandPanel *panel, struct ObjectNodeHeader *owner)
{
    card_dev_set_word(panel, owner);
    card_dev_init_command_panel_frame(&panel->template_node, &panel->primary, &panel->secondary);
    card_dev_init_row_panel(panel);
}
