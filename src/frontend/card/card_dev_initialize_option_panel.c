#include "frontend/card.h"
#include "common.h"
#include "frontend/card/server_imports.h"

/*
 * Devkit-server build of card_boot_init_command_panel for the option panel: store the initial
 * word, lay out the templates at +0x210 from the display blocks at +0x1E8 / +0x1F8, then lay out the panel.
 */
void card_dev_initialize_option_panel(CardBackgroundBody *record, ObjectNodeHeader *owner)
{
    card_background_set_word(record, owner);
    func_80404708(&record->template_node, &record->primary, &record->secondary);
    card_background_init_components(record);
}
