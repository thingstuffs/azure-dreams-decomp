#include "common.h"
#include "shared/game_work.h"

typedef struct S_800B0490_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_800B0490_1;   /* arg0 in handle_item_menu_input */


extern void SD_Call();
extern void set_item_menu_secondary_handler();
extern void change_item_menu_selection();
extern void dispatch_item_menu_request_result();


/* Handles menu actions and directional input with held-button repeat. */
void handle_item_menu_input(S_800B0490_1 *menu)
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

    pressed_buttons = ((s32)pad_state->unk_010);
    if (pressed_buttons & 0x20) {
        SD_Call(0x515, pad_state);
        set_item_menu_secondary_handler(menu->unk_08);
        return;
    }

    if (pressed_buttons & 0x40) {
        SD_Call(0x503, pad_state);
        dispatch_item_menu_request_result(menu);
        return;
    }

    if (!(held_buttons & 0x5000)) {
        return;
    }

    if (pressed_buttons & 0x4000) {
        menu->unk_10 = 0;
        move_mode = 4;
        direction = 1;
    } else if (pressed_buttons & 0x1000) {
        menu->unk_10 = 0;
        move_mode = 4;
        direction = -1;
    } else {
        repeat_ticks = menu->unk_10;
        if (repeat_ticks >= 5) {
            menu->unk_10 = repeat_ticks - 3;
            repeat_buttons = pad_state->buttons;
            if (repeat_buttons & 0x4000) {
                direction = 1;
                move_mode = 4;
            } else if (repeat_buttons & 0x1000) {
                direction = -1;
                move_mode = 4;
            }
        } else {
            menu->unk_10 = repeat_ticks + 1;
        }
    }

    if (direction == 0) {
        return;
    }
    SD_Call(0x502, pad_state);
    change_item_menu_selection(menu->unk_04, direction, move_mode);

    return;
}
