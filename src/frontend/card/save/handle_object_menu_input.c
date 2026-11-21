#include "common.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "frontend/card/save.h"
#include "frontend/card/service.h"
#include "frontend/card/server_imports.h"
#include "frontend/card/server_aliases.h"

extern s32 boot_pad_state;
extern s32 boot_pressed_buttons;

/* Handles menu navigation, button actions, and display refreshes. */
void handle_object_menu_input(void *menu_arg)
{
    CardDevSaveMenuBody *menu = menu_arg;
    s32 held_buttons;
    s32 pressed_buttons;
    s32 nav_result;
    s32 needs_refresh;
    s32 repeat_ticks;
    s32 *held_p = &boot_pad_state;
    s32 *press_p = &boot_pressed_buttons;

    held_buttons = boot_pad_state;
    nav_result = 0;
    needs_refresh = 0;
    if (held_buttons != 0) {
        pressed_buttons = boot_pressed_buttons;
        if (pressed_buttons & 0x40) {
            SD_Call_80063FF8(0x515);
            propagate_object_high_bit_flags(NODE_HEADER(menu));
            create_card_dev_slot_screen_effect(menu->unk_20, 0);
            return;
        } else if (pressed_buttons & 0x20) {
            SD_Call_80063FF8(0x514);
            if (menu->unk_48 == 0) {
                card_dev_set_save_menu_slot_mode(menu);
                needs_refresh = 1;
            } else {
                invoke_indexed_object_callback(menu);
            }
        } else if (held_buttons & 0x5000) {
            if (pressed_buttons & 0x5000) {
                menu->repeat_ticks = 0;
                if (*press_p & 0x1000) {
                    nav_result = -1;
                } else if (*press_p & 0x4000) {
                    nav_result = 1;
                }
            } else {
                repeat_ticks = menu->repeat_ticks;
                if (repeat_ticks >= 13) {
                    menu->repeat_ticks = repeat_ticks - 4;
                    if (*held_p & 0x1000) {
                        nav_result = -1;
                    } else if (*held_p & 0x4000) {
                        nav_result = 1;
                    }
                } else {
                    menu->repeat_ticks = repeat_ticks + 1;
                }
            }
        } else if (held_buttons & 0xA000) {
            if (held_buttons & 0x2000) {
                menu->unk_48 = 1;
            } else {
                menu->unk_48 = 0;
            }
            needs_refresh = 1;
        }

        if (nav_result != 0) {
            SD_Call_80063FF8(0x502);
            if (menu->unk_48 == 1) {
                menu->unk_28 = advance_card_menu_index_80058FF0(menu->unk_28, nav_result, 5);
            } else {
                menu->callback_index = advance_card_menu_index_80058FF0(menu->callback_index, nav_result, 4);
            }
            card_devkit_refresh_save_slot_selection(menu);
        }
    }

    nav_result = card_devkit_poll_stable_slot_state();
    card_dev_print_status();
    if (nav_result != 0) {
        if (nav_result != 1) {
            propagate_object_high_bit_flags(NODE_HEADER(menu));
            create_card_dev_slot_screen_effect(menu->unk_20, 0);
        }
    }
    if (needs_refresh != 0) {
        card_devkit_refresh_save_slot_selection(menu);
    }
}
