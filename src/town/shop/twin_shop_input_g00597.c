#include "shared/object_node.h"
#include "shared/audio_commands.h"
#include "engine/sprite.h"
/* Twin shop input. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B016C, CL:town/func_800B02BC, CL:town/func_800B03A4, CL:town/func_800B03D0. */
#include "town/shop/twin_shop_input_g00597.h"
#include "engine/message/data.h"
#include "engine/message.h"
#include "shared/game_work.h"

/* Look up the item selected by the grid. */
void refresh_selected_item_name(GridMenuObject *record) {
    get_item_name(&record->entry_base[record->selected_index]);
}

/* Look up the selected item with its fallback names. */
void refresh_selected_item_name_with_fallback(GridMenuObject *entry_table) {
    get_item_name_with_fallback_pair(&entry_table->entry_base[entry_table->selected_index]);
}

/* Handles twin shop input and updates the selected item and row. */
void handle_twin_shop_input(GridMenuObject *menu) {
    GameWork *pad_state;
    s32 held_buttons;
    s32 selection_step;
    s32 selection;
    s32 row;

    pad_state = &g_game_work;
    held_buttons = pad_state->buttons;
    selection_step = 0;
    if (held_buttons == 0) {
        return;
    }

    if ((pad_state->pressed_buttons) & 0x10) {
        SD_Call(AUDIO_ACCEPT);
        set_status_from_flagged_total(menu);
        close_twin_shop(NODE_HEADER(menu));
        return;
    }
    if ((pad_state->pressed_buttons) & 0x20) {
        SD_Call(AUDIO_CANCEL);
        runtime_script_state.variables[14] = 0;
        close_twin_shop(NODE_HEADER(menu));
        return;
    }
    if ((pad_state->pressed_buttons) & 0x40) {
        confirm_selected_entry(menu);
        return;
    }
    if (!(held_buttons & 0xF000)) {
        return;
    }

    if ((pad_state->pressed_buttons) & 0xF000) {
        menu->repeat_ticks = 0;
        if ((pad_state->pressed_buttons) & 0x8000)
            selection_step = -5;
        else if ((pad_state->pressed_buttons) & 0x2000)
            selection_step = 5;
        else if ((pad_state->pressed_buttons) & 0x1000)
            selection_step = -1;
        else if ((pad_state->pressed_buttons) & 0x4000)
            selection_step = 1;
    } else {
        if (menu->repeat_ticks >= 9) {
            if (held_buttons & 0x8000)
                selection_step = -5;
            else if (held_buttons & 0x2000)
                selection_step = 5;
            else if (held_buttons & 0x1000)
                selection_step = -1;
            else if (held_buttons & 0x4000)
                selection_step = 1;
            menu->repeat_ticks = *&menu->repeat_ticks - 1;
        } else {
            menu->repeat_ticks++;
            return;
        }
    }

    selection = advance_index_with_directional_clamp(menu->selected_index, selection_step, menu->entry_count);
    row = selection / 5;
    if (selection == menu->selected_index) {
        return;
    }

    SD_Call(AUDIO_CURSOR_MOVE);
    menu->selected_index = selection;
    if (row != menu->selected_row) {
        menu->selected_row = row;
        set_shop_page_and_selection(menu->subrecord, row, selection);
    }
    set_shop_selected_entry(menu->subrecord, selection);
    if (pad_state->buttons & 0x40) {
        confirm_selected_entry(menu);
    }
    refresh_selected_item_name(menu);
}
