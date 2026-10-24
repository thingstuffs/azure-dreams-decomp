#include "engine/sprite.h"
/* Twin shop input (G00597). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B016C, CL:town/func_800B02BC, CL:town/func_800B03A4, CL:town/func_800B03D0. */
#include "town/shop/twin_shop_input_g00597.h"

/* Calls get_item_name_with_shared_text_table with record->unk_20 +(record->unk_04 * 4). */
void pass_indexed_record_to_loader(Rec_func_800AD7F8_arg0 *record) {
    get_item_name_with_shared_text_table(record->unk_20 + (record->unk_04 * 4));
}

/* Calls select_item_name_table_from_pair_check with entry_table->unk_20 +(entry_table->unk_04 * 4). */
void pass_indexed_entry_address(S_800ADB30_0 *entry_table) {
    select_item_name_table_from_pair_check(entry_table->unk_20 + (entry_table->unk_04 * 4));
}

/* Handles twin shop input and updates the selected item and row. */
void handle_twin_shop_input(s32 *menu) {
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
        SD_Call(0x514);
        store_record_check_result(menu);
        close_twin_shop((s8 *)menu - 0x20);
        return;
    }
    if ((pad_state->pressed_buttons) & 0x20) {
        SD_Call(0x515);
        script_status = 0;
        close_twin_shop((s8 *)menu - 0x20);
        return;
    }
    if ((pad_state->pressed_buttons) & 0x40) {
        handle_selected_entry(menu);
        return;
    }
    if (!(held_buttons & 0xF000)) {
        return;
    }

    if ((pad_state->pressed_buttons) & 0xF000) {
        menu[5] = 0;
        if ((pad_state->pressed_buttons) & 0x8000)
            selection_step = -5;
        else if ((pad_state->pressed_buttons) & 0x2000)
            selection_step = 5;
        else if ((pad_state->pressed_buttons) & 0x1000)
            selection_step = -1;
        else if ((pad_state->pressed_buttons) & 0x4000)
            selection_step = 1;
    } else {
        if (menu[5] >= 9) {
            if (held_buttons & 0x8000)
                selection_step = -5;
            else if (held_buttons & 0x2000)
                selection_step = 5;
            else if (held_buttons & 0x1000)
                selection_step = -1;
            else if (held_buttons & 0x4000)
                selection_step = 1;
            menu[5] = *(s32 *)&menu[5] - 1;
        } else {
            menu[5]++;
            return;
        }
    }

    selection = advance_index_with_directional_clamp(menu[1], selection_step, menu[2]);
    row = selection / 5;
    if (selection == menu[1]) {
        return;
    }

    SD_Call(0x502);
    menu[1] = selection;
    if (row != menu[3]) {
        menu[3] = row;
        set_shop_subrecord_values(menu[10], row, selection);
    }
    store_shop_embedded_value(menu[10], selection);
    if (pad_state->buttons & 0x40) {
        handle_selected_entry(menu);
    }
    pass_indexed_record_to_loader((Rec_func_800AD7F8_arg0 *)menu);
}
