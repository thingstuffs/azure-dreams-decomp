#include "common.h"
#include "shared/game_work.h"

typedef struct S_800B260C_1 {
    u8 pad_00[0x10];
    union { s32 s; s32 u; } unk_10;   /* accessed as both */
} S_800B260C_1;   /* arg0 in handle_item_menu_input_2 */


extern void SD_Call(s32);
extern void interpolate_paired_object_positions_and_shades(void *);
extern void update_active_entry_and_notify_handlers(s8 *state, s32 input);
extern void decrement_entry_and_notify_handlers(void *);
extern void store_table_index_and_entry_bytes(void *, s32);
extern s32 move_item_to_list(void *);
extern void func_800B25D8(void *);
extern void set_object_data_pointer_if_present(void *);

/* Handles menu button actions and directional cursor movement with key repeat. */
void handle_item_menu_input_2(u8 *menu) {
    GameWork *pad_state = &g_game_work;
    s32 held_buttons = pad_state->buttons;
    s32 pressed_buttons;
    s32 cursor_step = 0;
    s32 select_result;
    s32 repeat_ticks;
    s32 held_directions;

    if (held_buttons != 0) {
        pressed_buttons = ((s32)pad_state->unk_010);
        if (pressed_buttons & 0x20) {
            SD_Call(0x515);
            set_object_data_pointer_if_present(menu - 0x20);
        } else if (pressed_buttons & 0x40) {
            select_result = move_item_to_list(menu);
            if (select_result == 0) {
                SD_Call(0x503);
                decrement_entry_and_notify_handlers(menu);
            } else if (select_result == 3) {
                SD_Call(0x506);
            }
        } else if (pressed_buttons & 0x80) {
            SD_Call(0x503);
        } else if (pressed_buttons & 0x10) {
            SD_Call(0x503);
            func_800B25D8(menu);
            decrement_entry_and_notify_handlers(menu);
        } else if (pressed_buttons & 4) {
            store_table_index_and_entry_bytes(menu, 0);
        } else if (pressed_buttons & 1) {
            store_table_index_and_entry_bytes(menu, 1);
        } else if ((held_buttons & 0xF000) != 0) {
            if (pressed_buttons & 0xF000) {
                ((S_800B260C_1 *)menu)->unk_10.s = 0;
                pressed_buttons = ((s32)pad_state->unk_010);
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
                repeat_ticks = ((S_800B260C_1 *)menu)->unk_10.s;
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
                    ((S_800B260C_1 *)menu)->unk_10.u--;
                } else {
                    ((S_800B260C_1 *)menu)->unk_10.s = repeat_ticks + 1;
                }
            }
            if (cursor_step != 0) {
                SD_Call(0x502);
                update_active_entry_and_notify_handlers(menu, cursor_step);
            }
        }
    }

    interpolate_paired_object_positions_and_shades(menu);
}
