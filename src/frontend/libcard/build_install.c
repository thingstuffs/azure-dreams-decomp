#include "common.h"
#include "shared/game_work.h"

#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard.h"
#include "slus.h"

/* Handle menu selection, directional repeat, and closing from controller input and update status. */
void build_install(u8 *object)
{
    s32 held_buttons;
    s32 pressed_buttons;
    s32 repeat_buttons;
    s32 selection_step;
    s32 repeat_ticks;
    s32 needs_refresh;
    s32 update_status;

    held_buttons = g_game_work.buttons;
    selection_step = 0;
    needs_refresh = selection_step;
    if (held_buttons != 0) {
        pressed_buttons = ((s32)g_game_work.pressed_buttons);
        if (pressed_buttons & 0x20) {
            SD_Call(0x515);
            card_boot_destroy_slot_selection_menu(object - 0x20);
            init_card_boot_request_object(((CardSlotMenuState *)object)->request, 0);
            return;
        }
        if (pressed_buttons & 0x40) {
            SD_Call(0x503);
            if (((CardSlotMenuState *)object)->unk_48 == 0) {
                set_record_pair_to_one(object);
                needs_refresh = 1;
            } else {
                card_boot_dispatch_selected_menu_action(object);
            }
        } else if (held_buttons & 0x5000) {
            if (pressed_buttons & 0x5000) {
                ((CardSlotMenuState *)object)->unk_30 = 0;
                pressed_buttons = ((s32)g_game_work.pressed_buttons);
                if (pressed_buttons & 0x1000) {
                    selection_step = -1;
                } else if (pressed_buttons & 0x4000) {
                    selection_step = 1;
                }
            } else {
                repeat_ticks = ((CardSlotMenuState *)object)->unk_30;
                if (repeat_ticks >= 13) {
                    ((CardSlotMenuState *)object)->unk_30 = repeat_ticks - 4;
                    repeat_buttons = g_game_work.buttons;
                    if (repeat_buttons & 0x1000) {
                        selection_step = -1;
                    } else if (repeat_buttons & 0x4000) {
                        selection_step = 1;
                    }
                } else {
                    ((CardSlotMenuState *)object)->unk_30 = repeat_ticks + 1;
                }
            }
        } else if (held_buttons & 0xA000) {
            if (held_buttons & 0x2000) {
                ((CardSlotMenuState *)object)->unk_48 = 1;
            } else {
                ((CardSlotMenuState *)object)->unk_48 = 0;
            }
            needs_refresh = 1;
        }

        if (selection_step != 0) {
            SD_Call(0x502);
            if (((CardSlotMenuState *)object)->unk_48 == 1) {
                ((CardSlotMenuState *)object)->unk_28 =
                    advance_index_with_single_wrap(((CardSlotMenuState *)object)->unk_28, selection_step, 5);
            } else {
                ((CardSlotMenuState *)object)->unk_44 =
                    advance_index_with_single_wrap(((CardSlotMenuState *)object)->unk_44, selection_step, 3);
            }
            card_boot_refresh_five_slot_selection(object);
        }
    }

    update_status = card_boot_debounce_card_status_events();
    no_op_card_stub();
    if (update_status != 0) {
        if (update_status != 1) {
            card_boot_destroy_slot_selection_menu(object - 0x20);
            init_card_boot_request_object(((CardSlotMenuState *)object)->request, 0);
        }
    }

    if (needs_refresh != 0) {
        card_boot_refresh_five_slot_selection(object);
    }
    return;
}
