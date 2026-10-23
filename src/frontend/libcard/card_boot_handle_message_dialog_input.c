#include "common.h"
#include "shared/game_work.h"
#include "engine/menu.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"
#include "slus.h"

typedef struct S_80022524_0 {
    s32 unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    u8 pad_14[0xC];
    s32 * unk_20;
} S_80022524_0;   /* arg0 in card_boot_handle_message_dialog_input */

typedef struct S_800280B4 {
    u8 pad_00[0x14];
    u8 unk_14;
    u8 pad_15[0x3];
} S_800280B4;   /* 0x18-byte entries */

extern S_800280B4 card_menu_entry_values[];

/* Handles menu exit buttons and repeated left/right selection changes. */
void card_boot_handle_message_dialog_input(S_80022524_0 *menu)
{
    s32 direction;
    s32 held_buttons;
    s32 pressed_buttons;
    s32 repeat_delay;
    s32 right_pressed;
    s32 next_delay;
    s32 *input;

    input = ((s32 *)(&g_game_work));
    direction = 0;
    held_buttons = input[2];
    if (held_buttons == 0) {
        return;
    }
    pressed_buttons = input[4];
    if (pressed_buttons & 0x20) {
        s32 *exit_status;

        SD_Call(0x515);
        card_boot_close_message_dialog(1);
        exit_status = menu->unk_20;
        if (exit_status != 0) {
            *exit_status = 1;
        }
    } else if (pressed_buttons & 0x40) {
        s32 *exit_status;
        s32 *updated_status;
        s32 exit_result;

        SD_Call(0x514);
        exit_status = menu->unk_20;
        if (exit_status != 0) {
            exit_result = card_boot_close_message_dialog(1);
            updated_status = menu->unk_20;
            *updated_status = exit_result;
        } else {
            card_boot_close_message_dialog(1);
        }
    } else if ((held_buttons & 0xA000) != 0 && (pressed_buttons & 0xA000) != 0) {
        menu->unk_10 = 0;
        pressed_buttons = input[4];
        if (pressed_buttons & 0x8000) {
            direction = -1;
        } else {
            if (pressed_buttons & 0x2000) {
                direction = 1;
            }
        }
    } else if (held_buttons & 0xA000) {
        repeat_delay = menu->unk_10;
        if (repeat_delay >= 3) {
            if (held_buttons & 0x8000) {
                direction = -1;
            } else if (held_buttons & 0x2000) {
                direction = 1;
            }
        } else {
            next_delay = repeat_delay + 1;
            menu->unk_10 = next_delay;
        }
    }

    if (direction != 0) {
        s32 new_selection;

        new_selection = advance_index_with_directional_clamp(
            menu->unk_00,
            direction,
            card_menu_entry_values[menu->unk_08].unk_14);
        if (new_selection != menu->unk_00) {
            menu->unk_00 = new_selection;
            SD_Call(0x502);
        }
        card_boot_update_message_choice_highlight(menu);
    }
}
