/* first_pass: swept 49 configs, best 2.7.2-cdk '-fno-delayed-branch' 89 words off — do NOT re-sweep by hand */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "engine/menu.h"
#include "slus.h"

typedef struct S_8004FA2C S_8004FA2C;

typedef struct S_8004FAA4_1 {
    u8 pad_00[0x24];
    s32 unk_24;
    s32 unk_28;
    u8 pad_2C[0x4];
    s32 unk_30;
    u8 pad_34[0x4];
    s32 unk_38;
} S_8004FAA4_1;   /* arg0 in handle_animated_selection_menu_input */

/* Update menu selection from directional and side-switch input, with key repeat and sound. */
void handle_animated_selection_menu_input(S_8004FAA4_1 *menu) {
    GameWork *input;
    s32 next_index;
    s32 repeat_ticks;
    s32 held_buttons;
    s32 index_delta;

    input = &g_game_work;
    index_delta = 0;
    if ((input->buttons != 0) && (menu->unk_24 >= 2)) {
        if (input->buttons & 0xA000) {
            if ((input->pressed_buttons) & 0x2000) {
                index_delta = 1;
                menu->unk_38 = 0;
                menu->unk_28 = 4;
            } else if ((input->pressed_buttons) & 0x8000) {
                index_delta = -1;
                menu->unk_38 = 0;
                menu->unk_28 = 4;
            } else {
                repeat_ticks = menu->unk_38;
                if (repeat_ticks >= 9) {
                    menu->unk_38 = (s32) (repeat_ticks - 2);
                    held_buttons = input->buttons;
                    if (held_buttons & 0x2000) {
                        index_delta = 1;
                        menu->unk_28 = 3;
                    } else if (held_buttons & 0x8000) {
                        index_delta = -1;
                        menu->unk_28 = 3;
                    }
                } else {
                    menu->unk_38 = (s32) (repeat_ticks + 1);
                }
            }
        }
        if (index_delta == 0) {
            if ((input->pressed_buttons) & 1) {
                if (((s32)primary_actor_record->unk_B0.address) != 0) {
                    next_index = find_resolved_selection_menu_index(menu, 1);
                    menu->unk_28 = 4;
                    index_delta = next_index - menu->unk_30;
                }
            } else if ((input->pressed_buttons) & 2) {
                if (((s32)primary_actor_record->unk_AC.address) != 0) {
                    next_index = find_resolved_selection_menu_index(menu, 0);
                    menu->unk_28 = 4;
                    index_delta = next_index - menu->unk_30;
                }
            }
        }
        if (index_delta != 0) {
            SD_Call(0x504);
            begin_selection_menu_index_change(menu, index_delta);
        }
    }
}
