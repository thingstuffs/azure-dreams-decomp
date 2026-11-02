#include "common.h"
#include "frontend/card/menu_defaults.h"

/* One menu entry of the devkit card-slot screen: its primitive words and the shared settings. */
typedef struct CardDevSlotEntry {
    s32 unk_00;
    s32 *primitive;
    s32 *settings;
    s32 unk_0C;
} CardDevSlotEntry;

/* The menu block of the devkit card-slot screen object (offsets of the server build). */
typedef struct CardDevSlotMenu {
    u8 pad_00[0x44];
    s32 settings[3];
    u8 pad_50[0x10];
    CardDevSlotEntry **entry_table;
    CardDevSlotEntry entries[4];
    s32 primitives[4][4];
} CardDevSlotMenu;

/*
 * Devkit-server build of card_background_init_entry_tables: point every entry at its primitive words (copied from
 * the defaults) and at the shared settings, then copy the settings defaults.
 */
void card_dev_init_slot_entry_tables(CardDevSlotMenu *menu, s32 entry_count)
{
    s32 i;

    for (i = 0; i < entry_count; i++) {
        menu->entry_table[i] = &menu->entries[i];
        menu->primitives[i][0] = menu_primitive_defaults[0];
        menu->primitives[i][1] = menu_primitive_defaults[1];
        menu->primitives[i][2] = menu_primitive_defaults[2];
        menu->primitives[i][3] = menu_primitive_defaults[3];
        menu->entries[i].primitive = menu->primitives[i];
        menu->entries[i].settings = menu->settings;
    }
    menu->settings[0] = menu_settings_defaults[0];
    menu->settings[1] = menu_settings_defaults[1];
    menu->settings[2] = menu_settings_defaults[2];
}
