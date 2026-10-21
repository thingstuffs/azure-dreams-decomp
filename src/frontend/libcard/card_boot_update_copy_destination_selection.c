#include "common.h"
#include "shared/game_work.h"

typedef struct S_80025584_0_pre {
    s32 * unk_00;
    u8 pad_04[0xC];
} S_80025584_0_pre;   /* the 0x10 bytes before menu in card_boot_update_copy_destination_selection, addressed as menu[-1] */

typedef struct S_80025584_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x4];
    s32 unk_28;
    u8 pad_2C[0x4];
    s32 unk_30;
} S_80025584_0;   /* menu in card_boot_update_copy_destination_selection */


extern s32 D_80024FFC;

#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"
#include "slus.h"

/* Handle menu input, selection repeat, and transition completion. */
void card_boot_update_copy_destination_selection(u8 *menu)
{
    s32 selection_delta;
    s32 transition_status;
    s32 repeat_timer;
    s32 buttons;

    selection_delta = 0;
    if (g_game_work.buttons != 0) {
        if (((s32)g_game_work.pressed_buttons) & 0x20) {
            SD_Call(0x515);
            ((S_80025584_0_pre *)menu)[-1].unk_00 = &D_80024FFC;
        }
        buttons = ((s32)g_game_work.pressed_buttons);
        if (buttons & 0x40) {
            SD_Call(0x503);
            card_boot_prepare_copy_destination_message(menu);
        } else if (g_game_work.buttons & 0x5000) {
            if (buttons & 0x5000) {
                ((S_80025584_0 *)menu)->unk_30 = 0;
                buttons = ((s32)g_game_work.pressed_buttons);
                if (buttons & 0x1000) {
                    selection_delta = -1;
                } else if (buttons & 0x4000) {
                    selection_delta = 1;
                }
            } else {
                repeat_timer = ((S_80025584_0 *)menu)->unk_30;
                if (repeat_timer >= 13) {
                    ((S_80025584_0 *)menu)->unk_30 = repeat_timer - 2;
                    buttons = g_game_work.buttons;
                    if (buttons & 0x1000) {
                        selection_delta = -1;
                    } else if (buttons & 0x4000) {
                        selection_delta = 1;
                    }
                } else {
                    ((S_80025584_0 *)menu)->unk_30 = repeat_timer + 1;
                }
            }
        }

        if (selection_delta != 0) {
            SD_Call(0x502);
            ((S_80025584_0 *)menu)->unk_28 =
                advance_index_with_single_wrap(((S_80025584_0 *)menu)->unk_28, selection_delta, 5);
            update_spark_effect(menu);
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
    card_boot_destroy_slot_selection_menu(menu - 0x20);
    init_card_boot_request_object(((S_80025584_0 *)menu)->unk_20, 0);
}
