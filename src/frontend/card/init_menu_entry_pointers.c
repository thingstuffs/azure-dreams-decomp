#include "frontend/card/message_display.h"
#include "common.h"
#include "frontend/card/menu_defaults.h"
#include "frontend/card.h"




/* Initialize entry pointers, per-entry defaults, and shared state defaults. */
void init_menu_entry_pointers(CardDevDialogDisplay *state, s32 entry_count) {
    s32 entry_index;

    for (entry_index = 0; entry_index < entry_count; entry_index++) {
        state->entries[entry_index] = &state->display_nodes[entry_index];
        state->blocks[entry_index].words[0] = menu_primitive_defaults[0];
        state->blocks[entry_index].words[1] = menu_primitive_defaults[1];
        state->blocks[entry_index].words[2] = menu_primitive_defaults[2];
        state->blocks[entry_index].words[3] = menu_primitive_defaults[3];
        state->display_nodes[entry_index].block = &state->blocks[entry_index];
        state->display_nodes[entry_index].vector = &state->settings;
    }
    state->settings.unk0 = menu_settings_defaults[0];
    state->settings.unk4 = menu_settings_defaults[1];
    state->settings.unk8 = menu_settings_defaults[2];
}
