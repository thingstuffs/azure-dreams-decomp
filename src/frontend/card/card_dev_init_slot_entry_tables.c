#include "frontend/card/choice_panel.h"
#include "common.h"
#include "frontend/card/menu_defaults.h"

/*
 * Devkit-server build of card_background_init_entry_tables: point every entry at its primitive words (copied from
 * the defaults) and at the shared settings, then copy the settings defaults.
 */
void card_dev_init_slot_entry_tables(CardDevSlotMenu *menu, s32 entry_count)
{
    s32 i;

    for (i = 0; i < entry_count; i++) {
        menu->entry_table[i] = &menu->entries[i];
        menu->primitives[i].words[0] = menu_primitive_defaults[0];
        menu->primitives[i].words[1] = menu_primitive_defaults[1];
        menu->primitives[i].words[2] = menu_primitive_defaults[2];
        menu->primitives[i].words[3] = menu_primitive_defaults[3];
        menu->entries[i].display.block = &menu->primitives[i];
        menu->entries[i].settings = menu->settings;
    }
    menu->settings[0] = menu_settings_defaults[0];
    menu->settings[1] = menu_settings_defaults[1];
    menu->settings[2] = menu_settings_defaults[2];
}
