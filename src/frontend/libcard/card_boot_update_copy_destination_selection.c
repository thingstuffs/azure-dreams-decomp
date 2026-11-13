#include "frontend/libcard_callbacks_api.h"
#include "frontend/libcard/slot_menu.h"
#include "shared/object_node.h"
#include "shared/audio_commands.h"
#include "common.h"
#include "shared/game_work.h"



#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"
#include "slus.h"

/* Handle menu input, selection repeat, and transition completion. */
void card_boot_update_copy_destination_selection(u8 *menu_data)
{
    CardSlotMenuState *menu = (void *)menu_data;
    s32 selection_delta;
    s32 transition_status;
    s32 repeat_timer;
    s32 buttons;

    selection_delta = 0;
    if (g_game_work.buttons != 0) {
        if ((g_game_work.pressed_buttons) & 0x20) {
            SD_Call(AUDIO_CANCEL);
            ((ObjectNodeHeader *)menu - 1)->update_callback = card_boot_resume_menu_after_slot_refresh;
        }
        buttons = (g_game_work.pressed_buttons);
        if (buttons & 0x40) {
            SD_Call(AUDIO_MENU_CONFIRM);
            card_boot_prepare_copy_destination_message(menu);
        } else if (g_game_work.buttons & 0x5000) {
            if (buttons & 0x5000) {
                menu->unk_30 = 0;
                buttons = (g_game_work.pressed_buttons);
                if (buttons & 0x1000) {
                    selection_delta = -1;
                } else if (buttons & 0x4000) {
                    selection_delta = 1;
                }
            } else {
                repeat_timer = menu->unk_30;
                if (repeat_timer >= 13) {
                    menu->unk_30 = repeat_timer - 2;
                    buttons = g_game_work.buttons;
                    if (buttons & 0x1000) {
                        selection_delta = -1;
                    } else if (buttons & 0x4000) {
                        selection_delta = 1;
                    }
                } else {
                    menu->unk_30 = repeat_timer + 1;
                }
            }
        }

        if (selection_delta != 0) {
            SD_Call(AUDIO_CURSOR_MOVE);
            menu->unk_28 =
                advance_index_with_single_wrap(menu->unk_28, selection_delta, 5);
            card_boot_refresh_copy_slot_markers(menu);
        }
    }

    transition_status = card_boot_debounce_card_status_events();
    no_op_card_stub();
    if (transition_status == 0) {
        return;
    }
    if (transition_status == 1) {
        return;
    }
    card_boot_destroy_slot_selection_menu((ObjectNodeHeader *)menu - 1);
    init_card_boot_request_object(menu->request, 0);
}
