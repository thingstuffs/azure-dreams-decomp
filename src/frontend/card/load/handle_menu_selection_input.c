#include "common.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "frontend/card/load.h"
#include "frontend/card/service.h"
#include "frontend/card/server_imports.h"
#include "shared/pad_state.h"
#include "frontend/card/server_aliases.h"


extern s32 boot_pressed_buttons;

extern void func_804070C4(void *object);


/* Handles menu selection, held-button repeats, and menu exit. */
void handle_menu_selection_input(CardDevLoadSlotScreen *screen)
{
    s32 held_buttons;
    s32 pressed_buttons;
    s32 direction;
    s32 repeat_ticks;
    s32 repeat_buttons;
    s32 *buttons;

    buttons = &boot_pad_state.held;
    held_buttons = buttons[0];
    direction = 0;
    if (held_buttons != 0) {
        buttons = &boot_pressed_buttons;
        pressed_buttons = buttons[0];
        if (pressed_buttons & 0x40) {
            SD_Call_80063FF8(0x515);
            func_804070C4(NODE_HEADER(screen));
            create_card_dev_slot_screen_effect(screen->request, screen->mode);
            return;
        }
        if (pressed_buttons & 0x20) {
            SD_Call_80063FF8(0x514);
            select_load_slot_callback(screen);
        } else if (held_buttons & 0x5000) {
            if (pressed_buttons & 0x5000) {
                buttons = &screen->repeat_ticks;
                *buttons = 0;
                buttons = &boot_pressed_buttons;
                pressed_buttons = buttons[0];
                if (pressed_buttons & 0x1000) {
                    direction = -1;
                } else if (pressed_buttons & 0x4000) {
                    direction = 1;
                }
            } else {
                repeat_ticks = screen->repeat_ticks;
                if (repeat_ticks >= 13) {
                    buttons = &screen->repeat_ticks;
                    *buttons = repeat_ticks - 4;
                    buttons = &boot_pad_state.held;
                    repeat_buttons = buttons[0];
                    if (repeat_buttons & 0x1000) {
                        direction = -1;
                    } else if (repeat_buttons & 0x4000) {
                        direction = 1;
                    }
                } else {
                    screen->repeat_ticks = repeat_ticks + 1;
                }
            }
        }
        if (direction != 0) {
            SD_Call_80063FF8(0x502);
            screen->selection =
                advance_card_menu_index_80058FF0(screen->selection, direction, 5);
            card_devkit_highlight_selected_load_slot(screen);
        }
    }

    direction = card_devkit_poll_stable_slot_state();
    card_dev_print_status();
    if (direction == 0) {
        return;
    }
    if (direction == 1) {
        return;
    }
    func_804070C4(NODE_HEADER(screen));
    create_card_dev_slot_screen_effect(screen->request, screen->mode);
}
