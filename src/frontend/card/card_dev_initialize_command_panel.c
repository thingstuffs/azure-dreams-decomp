#include "common.h"
#include "frontend/card/server_imports.h"

/*
 * Devkit-server build of card_boot_initialize_three_row_command_panel: store the initial word, lay out the
 * panel templates at +0x1A8 from the display blocks at +0x180 / +0x190, then lay out the panel.
 */
void card_dev_initialize_command_panel(u8 *record, void *init_value)
{
    func_80403B7C(record, init_value);
    func_804039F8(record + 0x1A8, record + 0x180, record + 0x190);
    func_804038C8(record);
}
