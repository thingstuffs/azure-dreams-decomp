#include "common.h"
#include "frontend/card.h"
#include "frontend/card/command_panel.h"
#include "frontend/card/server_imports.h"

/*
 * Devkit-server build of card_boot_init_command_panel: store the initial word, lay out the
 * panel templates at +0x1A8 from the display blocks at +0x180 / +0x190, then lay out the panel.
 */
void card_dev_initialize_command_panel(struct CardDevCommandPanel *panel, void *init_value)
{
    func_80403B7C(panel, init_value);
    card_dev_init_command_panel_frame(panel->frame_templates, panel->primary_block, panel->secondary_block);
    card_dev_init_row_panel(panel);
}
