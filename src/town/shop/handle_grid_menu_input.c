#include "common.h"
#include "shared/game_work.h"

extern s32 advance_index_with_directional_clamp(s32 selection, s32 step, s32 count);
extern void SD_Call(s32 sound_id);
extern void pass_indexed_entry_address(void *menu);
extern void close_twin_shop(void *shop);
extern void set_shop_subrecord_values(s32 menu_context, s32 row, s32 selection);
extern void store_shop_embedded_value(s32 menu_context, s32 selection);
extern s32 script_status;

/* Handles grid menu navigation, confirmation, and cancellation. */
void handle_grid_menu_input(s32 *menu) {
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
    if (menu[2] == 0) {
        if ((pad_state->pressed_buttons) & 0x20) {
            SD_Call(0x515);
            script_status = 0;
            close_twin_shop((u8 *)menu - 0x20);
        }
        return;
    }
    pressed_buttons = (pad_state->pressed_buttons);
    if (pressed_buttons & 0x20) {
        SD_Call(0x515);
        script_status = 0;
        close_twin_shop((u8 *)menu - 0x20);
        return;
    }
    if (pressed_buttons & 0x40) {
        SD_Call(0x514);
        script_status = 1;
        close_twin_shop((u8 *)menu - 0x20);
        selected_entry = (u8 *)(menu[1] * 4 + menu[8]);
        selected_entry[3] |= 0x20;
        return;
    }
    if (!(held_buttons & 0xF000))
        return;
    if ((pad_state->pressed_buttons) & 0xF000) {
        menu[5] = 0;
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
        if (menu[5] >= 9) {
            if (held_buttons & 0x8000)
                selection_step = -5;
            else if (held_buttons & 0x2000)
                selection_step = 5;
            else if (held_buttons & 0x1000)
                selection_step = -1;
            else if (held_buttons & 0x4000)
                selection_step = 1;
            repeat_ticks = *(s32 *)&menu[5];
            menu[5] = repeat_ticks - 1;
        } else {
            menu[5]++;
            return;
        }
    }
    selection = advance_index_with_directional_clamp(menu[1], selection_step, menu[2]);
    row = selection / 5;
    if (selection == menu[1])
        return;
    SD_Call(0x502);
    menu[1] = selection;
    if (row != menu[3]) {
        menu[3] = row;
        set_shop_subrecord_values(menu[10], row, selection);
    }
    store_shop_embedded_value(menu[10], selection);
    pass_indexed_entry_address(menu);
}
