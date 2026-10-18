#include "common.h"
#include "shared/game_work.h"

extern s32 advance_index_with_directional_clamp(s32 current_selection, s32 selection_step, s32 value);
extern void SD_Call(s32 sound_id);
extern void store_record_check_result(s32 *menu);
extern void handle_selected_entry(s32 *menu);
extern void pass_indexed_record_to_loader(s32 *menu);
extern void close_twin_shop(void *shop_ptr);
extern void set_shop_subrecord_values(s32 menu_value, s32 row, s32 selection);
extern void store_shop_embedded_value(s32 menu_value, s32 selection);

extern s32 D_80082AB8;

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

    if (((s32)pad_state->unk_010) & 0x10) {
        SD_Call(0x514);
        store_record_check_result(menu);
        close_twin_shop((s8 *)menu - 0x20);
        return;
    }
    if (((s32)pad_state->unk_010) & 0x20) {
        SD_Call(0x515);
        D_80082AB8 = 0;
        close_twin_shop((s8 *)menu - 0x20);
        return;
    }
    if (((s32)pad_state->unk_010) & 0x40) {
        handle_selected_entry(menu);
        return;
    }
    if (!(held_buttons & 0xF000)) {
        return;
    }

    if (((s32)pad_state->unk_010) & 0xF000) {
        menu[5] = 0;
        if (((s32)pad_state->unk_010) & 0x8000)
            selection_step = -5;
        else if (((s32)pad_state->unk_010) & 0x2000)
            selection_step = 5;
        else if (((s32)pad_state->unk_010) & 0x1000)
            selection_step = -1;
        else if (((s32)pad_state->unk_010) & 0x4000)
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
    pass_indexed_record_to_loader(menu);
}
