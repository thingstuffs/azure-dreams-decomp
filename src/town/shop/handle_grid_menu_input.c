#include "shared/audio_commands.h"
#include "common.h"
#include "shared/game_work.h"
#include "engine/menu.h"
#include "slus.h"
#include "town/shop.h"

extern s32 script_status;

/* Handles grid menu navigation, confirmation, and cancellation. */
void handle_grid_menu_input(GridMenuObject *menu) {
    GameWork *pad_state;
    s32 held_buttons;
    s32 pressed_buttons;
    s32 selection_step;
    s32 repeat_ticks;
    s32 selection;
    s32 row;
    u8 *selected_entry;
    pad_state = &g_game_work;
    held_buttons = pad_state->buttons;
    selection_step = 0;
    if (held_buttons == 0)
        return;
    if (menu->entry_count == 0) {
        if ((pad_state->pressed_buttons) & 0x20) {
            SD_Call(AUDIO_CANCEL);
            script_status = 0;
            close_twin_shop((u8 *)menu - 0x20);
        }
        return;
    }
    pressed_buttons = (pad_state->pressed_buttons);
    if (pressed_buttons & 0x20) {
        SD_Call(AUDIO_CANCEL);
        script_status = 0;
        close_twin_shop((u8 *)menu - 0x20);
        return;
    }
    if (pressed_buttons & 0x40) {
        SD_Call(AUDIO_ACCEPT);
        script_status = 1;
        close_twin_shop((u8 *)menu - 0x20);
        selected_entry = (u8 *)(menu->selected_index * 4 + menu->entry_base);
        selected_entry[3] |= 0x20;
        return;
    }
    if (!(held_buttons & 0xF000))
        return;
    if ((pad_state->pressed_buttons) & 0xF000) {
        menu->repeat_ticks = 0;
        pressed_buttons = pad_state->pressed_buttons;
        if (pressed_buttons & 0x8000)
            selection_step = -5;
        else if (pressed_buttons & 0x2000)
            selection_step = 5;
        else if (pressed_buttons & 0x1000)
            selection_step = -1;
        else if (pressed_buttons & 0x4000)
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
            repeat_ticks = menu->repeat_ticks;
            menu->repeat_ticks = repeat_ticks - 1;
        } else {
            menu->repeat_ticks++;
            return;
        }
    }
    selection = advance_index_with_directional_clamp(menu->selected_index, selection_step, menu->entry_count);
    row = selection / 5;
    if (selection == menu->selected_index)
        return;
    SD_Call(AUDIO_CURSOR_MOVE);
    menu->selected_index = selection;
    if (row != menu->selected_row) {
        menu->selected_row = row;
        set_shop_subrecord_values(menu->subrecord, row, selection);
    }
    store_shop_embedded_value(menu->subrecord, selection);
    pass_indexed_entry_address(menu);
}
