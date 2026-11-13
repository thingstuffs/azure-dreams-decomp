#include "shared/audio_commands.h"
#include "common.h"
#include "shared/game_work.h"



#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"
#include "frontend/libcard/resource.h"
#include "slus.h"
#include "frontend/libcard/save_menu.h"

/* Handles menu navigation with button repeat and dispatches the selected action. */
void card_boot_update_save_slot_menu_input(CardSaveMenuBody *menu)
{
    s32 held_buttons;
    s32 pressed_buttons;
    s32 repeat_buttons;
    s32 status;
    s32 repeat_ticks;

    held_buttons = g_game_work.buttons;
    status = 0;
    if (held_buttons != 0) {
        pressed_buttons = (g_game_work.pressed_buttons);
        if (pressed_buttons & 0x20) {
            SD_Call(AUDIO_CANCEL);
            release_card_record_handles((u8 *)menu - 0x20);
            init_card_boot_request_object(menu->request, menu->mode);
            return;
        }
        if (pressed_buttons & 0x40) {
            SD_Call(AUDIO_MENU_CONFIRM);
            route_save_slot_validation(menu);
        } else {
            if (held_buttons & 0x5000) {
                if (pressed_buttons & 0x5000) {
                    menu->repeat_ticks = 0;
                    pressed_buttons = (g_game_work.pressed_buttons);
                    if (pressed_buttons & 0x1000) {
                        status = -1;
                    } else if (pressed_buttons & 0x4000) {
                        status = 1;
                    }
                } else {
                    repeat_ticks = menu->repeat_ticks;
                    if (repeat_ticks >= 13) {
                        menu->repeat_ticks = repeat_ticks - 4;
                        repeat_buttons = g_game_work.buttons;
                        if (repeat_buttons & 0x1000) {
                            status = -1;
                        } else if (repeat_buttons & 0x4000) {
                            status = 1;
                        }
                    } else {
                        menu->repeat_ticks = repeat_ticks + 1;
                    }
                }
            }
        }
        if (status != 0) {
            SD_Call(AUDIO_CURSOR_MOVE);
            menu->selection =
                advance_index_with_single_wrap(menu->selection, status, 5);
            card_boot_highlight_selected_load_slot(menu);
        }
    }

    status = card_boot_debounce_card_status_events();
    no_op_card_stub();
    if (status == 0) {
        return;
    }
    if (status == 1) {
        return;
    }

    release_card_record_handles((u8 *)menu - 0x20);
    init_card_boot_request_object(menu->request, menu->mode);
}
