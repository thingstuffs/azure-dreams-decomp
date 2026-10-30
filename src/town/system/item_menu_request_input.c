/* Item menu request input and its file-private helper. */
#include "shared/audio_commands.h"
#include "common.h"
#include "town/shop/item_menu_actions.h"
#include "town/shop/item_menu_cursor_transition_g00601.h"
extern s32 invoke_item_menu_offset_handler();
#include "shared/game_work.h"
#include "town/shop/item.h"

/* arg0 in handle_item_menu_input */


extern void SD_Call(); /* Unprototyped: one or two arguments; the retail audio queue reads only the command. */

/* Routes a menu request result of 1 to its secondary handler and 2 to its data pointer. */
static void dispatch_item_menu_request_result(ItemMenuInput *request) {
    s32 result_code;

    result_code = invoke_item_menu_offset_handler(request->object, request->callback_arg);
    if (result_code == 1) {
        set_item_menu_secondary_handler(request->owner);
        return;
    }
    if (result_code == 2) {
        set_item_menu_data_pointer(request->owner);
        return;
    }
}

/* Handles menu confirmation, cancellation, and repeated horizontal cursor movement with sound effects. */
void handle_item_menu_input(ItemMenuInput *menu)
{
    s32 direction;
    s32 move_mode;
    s32 repeat_ticks;
    s32 held_buttons;
    s32 repeat_buttons;
    s32 pressed_buttons;
    GameWork *pad_state;

    direction = 0;
    move_mode = direction;
    pad_state = &g_game_work;
    held_buttons = pad_state->buttons;
    if (held_buttons == 0) {
        return;
    }

    pressed_buttons = (pad_state->pressed_buttons);
    if (pressed_buttons & 0x20) {
        SD_Call(AUDIO_CANCEL);
        set_item_menu_secondary_handler(menu->owner);
        return;
    }

    if (pressed_buttons & 0x40) {
        SD_Call(AUDIO_MENU_CONFIRM);
        dispatch_item_menu_request_result(menu);
        return;
    }

    if (!(held_buttons & 0x5000)) {
        return;
    }

    if (pressed_buttons & 0x4000) {
        menu->repeat_ticks = 0;
        move_mode = 4;
        direction = 1;
    } else if (pressed_buttons & 0x1000) {
        menu->repeat_ticks = 0;
        move_mode = 4;
        direction = -1;
    } else {
        repeat_ticks = menu->repeat_ticks;
        if (repeat_ticks >= 5) {
            menu->repeat_ticks = repeat_ticks - 3;
            repeat_buttons = pad_state->buttons;
            if (repeat_buttons & 0x4000) {
                direction = 1;
                move_mode = 4;
            } else if (repeat_buttons & 0x1000) {
                direction = -1;
                move_mode = 4;
            }
        } else {
            menu->repeat_ticks = repeat_ticks + 1;
        }
    }

    if (direction == 0) {
        return;
    }
    SD_Call(AUDIO_CURSOR_MOVE, pad_state);
    change_item_menu_selection(menu->object, direction, move_mode);

    return;
}
