#include "common.h"
#include "shared/game_work.h"

typedef struct S_800265B8_0 {
    u8 pad_00[0x20];
    void *request;
    s32 unk_24;
    u8 pad_28[0x4];
    s32 unk_2C;
    s32 unk_30;
} S_800265B8_0;   /* menu in write_text_and_advance_selection */


#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"
#include "frontend/libcard/resource.h"
#include "slus.h"
extern void func_80026920(void *object);

/* Handles menu navigation with button repeat and dispatches the selected action. */
void write_text_and_advance_selection(u8 *menu)
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
            SD_Call(0x515);
            func_80026920(menu - 0x20);
            init_card_boot_request_object(((S_800265B8_0 *)menu)->request, ((S_800265B8_0 *)menu)->unk_24);
            return;
        }
        if (pressed_buttons & 0x40) {
            SD_Call(0x503);
            route_save_slot_validation(menu);
        } else {
            if (held_buttons & 0x5000) {
                if (pressed_buttons & 0x5000) {
                    ((S_800265B8_0 *)menu)->unk_30 = 0;
                    pressed_buttons = (g_game_work.pressed_buttons);
                    if (pressed_buttons & 0x1000) {
                        status = -1;
                    } else if (pressed_buttons & 0x4000) {
                        status = 1;
                    }
                } else {
                    repeat_ticks = ((S_800265B8_0 *)menu)->unk_30;
                    if (repeat_ticks >= 13) {
                        ((S_800265B8_0 *)menu)->unk_30 = repeat_ticks - 4;
                        repeat_buttons = g_game_work.buttons;
                        if (repeat_buttons & 0x1000) {
                            status = -1;
                        } else if (repeat_buttons & 0x4000) {
                            status = 1;
                        }
                    } else {
                        ((S_800265B8_0 *)menu)->unk_30 = repeat_ticks + 1;
                    }
                }
            }
        }
        if (status != 0) {
            SD_Call(0x502);
            ((S_800265B8_0 *)menu)->unk_2C =
                advance_index_with_single_wrap(((S_800265B8_0 *)menu)->unk_2C, status, 5);
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

    func_80026920(menu - 0x20);
    init_card_boot_request_object(((S_800265B8_0 *)menu)->request, ((S_800265B8_0 *)menu)->unk_24);
}
