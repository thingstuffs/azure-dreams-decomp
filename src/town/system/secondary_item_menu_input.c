/* Secondary item menu input and its file-private helper. */
#include "shared/audio_commands.h"
#include "common.h"
#include "slus/sort_rank_81540.h"

#include "shared/game_work.h"
#include "town/shop.h"
#include "town/shop/resource_entry_initialization_g01156.h"
#include "town/shop/object.h"
#include "slus.h"
/* arg0 in handle_item_move_menu_input */


static void sort_selected_record_entries(ItemMenuInputObject *record);

/* Sort the currently selected carried or stored item list. */
static void sort_selected_record_entries(ItemMenuInputObject *record) {
    sort_entries_by_category(record->lists[record->source_index]);
}

/* Handles item moves, sorting, page changes, and repeated cursor input, then updates menu transitions. */
void handle_item_move_menu_input(ItemMenuInputObject *menu) {
    GameWork *pad_state = &g_game_work;
    s32 held_buttons = pad_state->buttons;
    s32 pressed_buttons;
    s32 cursor_step = 0;
    s32 select_result;
    s32 repeat_ticks;
    s32 held_directions;

    if (held_buttons != 0) {
        pressed_buttons = (pad_state->pressed_buttons);
        if (pressed_buttons & 0x20) {
            SD_Call(AUDIO_CANCEL);
            set_apply_record_values_callback(NODE_HEADER(menu));
        } else if (pressed_buttons & 0x40) {
            select_result = move_item_to_list(menu);
            if (select_result == 0) {
                SD_Call(AUDIO_MENU_CONFIRM);
                decrement_entry_and_notify_handlers(menu);
            } else if (select_result == 3) {
                SD_Call(0x506);
            }
        } else if (pressed_buttons & 0x80) {
            SD_Call(AUDIO_MENU_CONFIRM);
        } else if (pressed_buttons & 0x10) {
            SD_Call(AUDIO_MENU_CONFIRM);
            sort_selected_record_entries(menu);
            decrement_entry_and_notify_handlers(menu);
        } else if (pressed_buttons & 4) {
            store_shop_display_preset(menu, 0);
        } else if (pressed_buttons & 1) {
            store_shop_display_preset(menu, 1);
        } else if ((held_buttons & 0xF000) != 0) {
            if (pressed_buttons & 0xF000) {
                menu->input_repeat_ticks = 0;
                pressed_buttons = (pad_state->pressed_buttons);
                if (pressed_buttons & 0x8000) {
                    cursor_step = -5;
                } else if (pressed_buttons & 0x2000) {
                    cursor_step = 5;
                } else if (pressed_buttons & 0x1000) {
                    cursor_step = -1;
                } else if (pressed_buttons & 0x4000) {
                    cursor_step = 1;
                }
            } else {
                repeat_ticks = menu->input_repeat_ticks;
                if (repeat_ticks >= 5) {
                    if (held_buttons & 0x8000) {
                        cursor_step = -5;
                    } else if (held_buttons & 0x2000) {
                        cursor_step = 5;
                    } else {
                        held_directions = pad_state->buttons;
                        if (held_directions & 0x1000) {
                            cursor_step = -1;
                        } else if (held_directions & 0x4000) {
                            cursor_step = 1;
                        }
                    }
                    menu->input_repeat_ticks--;
                } else {
                    menu->input_repeat_ticks = repeat_ticks + 1;
                }
            }
            if (cursor_step != 0) {
                SD_Call(AUDIO_CURSOR_MOVE);
                update_active_entry_and_notify_handlers(menu, cursor_step);
            }
        }
    }

    ease_paired_objects_to_presets(menu);
}
