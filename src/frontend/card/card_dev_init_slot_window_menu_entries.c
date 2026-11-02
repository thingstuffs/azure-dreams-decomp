#include "common.h"
#include "frontend/card/menu_defaults.h"
#include "frontend/card/server_menu.h"

/* The 10-entry menu table of the devkit server's init_card_window_slot_object object: shared settings at +0x1BC, then entry pointers,
 * entry blocks and primitive words. */
typedef struct CardDevMenu10 {
    u8 unk_000[0x1BC];
    s32 settings[3];
    u8 unk_settings_end[0x10];
    CardDevMenuEntry *entries[10];
    CardDevMenuEntry entry_blocks[10];
    CardDevMenuPrimitive primitives[10];
} CardDevMenu10;

/* Devkit-server build of init_menu_entry_pointers: link each entry to its block and primitive words, copy the
 * primitive and settings defaults. */
void card_dev_init_slot_window_menu_entries(CardDevMenu10 *state, s32 entry_count)
{
    s32 i;

    for (i = 0; i < entry_count; i++) {
        state->entries[i] = &state->entry_blocks[i];
        state->primitives[i].words[0] = menu_primitive_defaults[0];
        state->primitives[i].words[1] = menu_primitive_defaults[1];
        state->primitives[i].words[2] = menu_primitive_defaults[2];
        state->primitives[i].words[3] = menu_primitive_defaults[3];
        state->entry_blocks[i].primitive = state->primitives[i].words;
        state->entry_blocks[i].settings = state->settings;
    }
    state->settings[0] = menu_settings_defaults[0];
    state->settings[1] = menu_settings_defaults[1];
    state->settings[2] = menu_settings_defaults[2];
}
