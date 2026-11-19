#include "frontend/card.h"
#include "common.h"
#include "frontend/card/server_imports.h"

/*
 * Devkit-server build of card_boot_init_command_panel for the option panel: store the initial
 * word, lay out the templates at +0x210 from the display blocks at +0x1E8 / +0x1F8, then lay out the panel.
 */
void card_dev_initialize_option_panel(CardBackgroundBody *record, ObjectNodeHeader *owner)
{
    func_80404C3C(record, owner);
    func_80404708(&record->template_node, &record->primary, &record->secondary);
    func_80404B10(record);
}
